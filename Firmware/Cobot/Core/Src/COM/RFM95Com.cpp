#include "../AppMain/Defines.h"
#include "RFM95Com.h"
#include <map>


#include "usbd_cdc_if.h"

struct dataChangeStruct {
     uint8_t addres;
     uint16_t command;
};


bool RFM95Com::Transmitt(uint8_t* data, uint8_t length)
{
     uint8_t* txData;

     static dataChangeStruct commandChangeCommands[] =
     {
          {CLOSE_ADDR, CLOSE_CHANGE},
          {OPEN_ADDR, OPEN_CHANGE},
          {TEACH_ADDR, TEACH_CHANGE},
          {RESET_ADDR, RESET_CHANGE},
          {ENABLE_ADDR, ENABLE_CHANGE},
          {DISABLE_ADDR, DISABLE_CHANGE},
          {STOP_ADDR, STOP_CHANGE},
          {ERROR_ADDR, ERROR_CHANGE},
     };

     static const dataChangeStruct settingsChangedCommands[] =
     {
          {TEACH_TORQUE_ADDR ,TEACH_TORQUE_CHANGE},
          {TEACH_SPEED_ADDR ,TEACH_SPEED_CHANGE},
          {CLAMPING_TORQUE_ADDR ,CLAMPING_TORQUE_CHANGE},
          {CLAMPING_SPEED_ADDR ,CLAMPING_SPEED_CHANGE},
          {SELF_SHUTDOWN_DELAY_ADDR ,SELF_SHUTDOWN_DELAY_CHANGE},
          {IN_POS_DIFF_ADDR ,IN_POS_DIFF_CHANGE},
          {OPENING_DISTANCE_ADDR ,OPENING_DISTANCE_CHANGE},
          {UNDERVOLTAGE_WARNING_ADDR ,UNDERVOLTAGE_WARNING_CHANGE},
          {UNDERVOLTAGE_ERROR_ADDR ,UNDERVOLTAGE_ERROR_CHANGE},
          {OVER_CURRENT_WARNING_ADDR ,OVER_CURRENT_WARNING_CHANGE},
          {OVER_CURRENT_ERROR_ADDR ,OVER_CURRENT_ERROR_CHANGE},
     };

     if (this->driveCommand->isCommandChanged() != 0)
     {
          uint8_t command = driveCommand->getCommandChangedReg();
          bool commandFound = false;
          for (const auto& changeCommand : commandChangeCommands) {
               if ((changeCommand.command & command) != 0) {
                    txData = this->GetCommand(changeCommand.addres);
                    driveCommand->ResetCommandChanged(changeCommand.command);
                    commandFound = true;
                    break;
               }
          }

          if (!commandFound) {
               driveStatus->setError(DriveStatus::E_UNKOWN_COMMAND_OR_ADDR_ERROR);
               return false;
          }

          txData[2] = SEND_COMMAND;
     }
     else if (driveSettings->isSettingsChanged() != 0)
     {
          uint16_t command = driveSettings->getSettingsChangedReg();
          bool commandFound = false;
          for (const auto& changeCommand : settingsChangedCommands) {
               if ((changeCommand.command & command) != 0) {
                    txData = this->GetSettings(changeCommand.addres);
                    driveSettings->ResetSettingsChanged(changeCommand.command);
                    commandFound = true;
                    break;
               }
          }

          if (!commandFound) {
               driveStatus->setError(DriveStatus::E_UNKOWN_COMMAND_OR_ADDR_ERROR);
               return false;
          }

          txData[2] = SEND_SETTINGS;
     }
     else
     {
          uint8_t dataTemp[] =
          { 0x1F, driveSettings->getDeviceAddress(), REQUEST_STATUS, READ_ALL_STATUS, 0x00, 0x00, 0x00 };
          txData = dataTemp;
     }
     txData[6] = CRC8(txData, 6);

     rfm95->beginPacket();
     rfm95->write(txData, 7);
     rfm95->endPacket();
     return true;
}


bool RFM95Com::Receive(uint8_t* data, uint8_t length)
{
     //data[0] = 0x1F
     //data[1] = deviceAddress
     //data[2] = command (readCommand, readSettings, readStatus, writeCommand...)
     //data[3] = reg addr (close, open, setTeach...)
     //data[4..n] = Payload
     //data[5] = crc

     uint8_t* txDataTemp;
     uint8_t rxData[7]{};

     uint8_t packetSize = rfm95->parsePacket();
     if (packetSize == 0)
     {
          receiveErrorCounter++;
          if (receiveErrorCounter >= 200) {
               driveStatus->setError(DriveStatus::E_CONNECTION_LOST_ERROR);
               receiveErrorCounter = 0;
          }
          return false;
     }
     
     receiveErrorCounter = 0;
     driveStatus->ResetError(DriveStatus::E_CONNECTION_LOST_ERROR);

     uint8_t counter = 0;
     while (rfm95->available())
     {
          rxData[counter] = rfm95->read();
          if (counter > MAX_PACKET_2_RECEIVE)
          {
               return false;
          }
          counter++;
     }


     //check CRC
     if (CRC8(rxData, 6) != rxData[6])
     {
          driveStatus->setError(DriveStatus::E_CRC_ERROR);
          return false;
     }

     switch (rxData[2])
     {
     case RECEIVE_SETTINGS:
          this->SetSettings(rxData);
          break;
     case RECEIVE_COMMAND:
          this->SetCommand(rxData);
          break;
     case RECEIVE_STATUS:
          this->SetStatus(rxData);
          break;
     default:
          rxData[2] = 0;
          break;
     }

     return true;
}

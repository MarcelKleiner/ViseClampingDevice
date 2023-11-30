#include "RFM95Com.h"
#include "../AppMain/Defines.h"
#include "usbd_cdc_if.h"

bool RFM95Com::Transmitt(uint8_t* data, uint8_t length)
{
     if (data == NULL) {
          return false;
     }

     rfm95->beginPacket();
     rfm95->write(data, length);
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
          return false;
     }

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

     HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

     if (CRC8(rxData, 6) != rxData[6])
     {
          driveStatus->setError(DriveStatus::E_CRC_ERROR);
          return false;
     }

     uint8_t txData[] =
     {
               0x1F,
               driveSettings->getDeviceAddress(),
               rxData[2],
               rxData[3],
               0x01,
               0x01,
               0x00
     };
     txData[6] = CRC8(txData, 6);


     switch (rxData[2])
     {
     case RECEIVE_SETTINGS:
          this->SetSettings(rxData);
          txDataTemp = txData;
          break;
     case RECEIVE_COMMAND:
          this->SetCommand(rxData);
          txDataTemp = txData;
          break;
     case SEND_SETTINGS:
          txDataTemp = this->GetSettings(rxData[3]);
          txDataTemp[2] = SEND_SETTINGS;
          break;
     case RECEIVE_STATUS_REQUEST:
          txDataTemp = this->GetStatus(rxData[3]);
          txDataTemp[2] = SEND_STATUS;
          break;
     case RECEIVE_SETTINGS_REQUEST:
          txDataTemp = this->GetSettings(rxData[3]);
          txDataTemp[2] = SEND_STATUS;
          break;
     default:
          //not sported command
          txDataTemp = txData;
          txDataTemp[4] = 0;
          txDataTemp[5] = 0;
          break;
     }

     Transmitt(txDataTemp, 7);
     return true;
}

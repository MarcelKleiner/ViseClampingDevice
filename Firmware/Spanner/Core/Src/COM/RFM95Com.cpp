#include "RFM95Com.h"
#include "../AppMain/Defines.h"

bool RFM95Com::Transmitt(uint8_t* data, uint8_t length)
{
     if (data == NULL) {
          return false;
     }

     rfm95->beginPacket();
     rfm95->write(data, 7);
     rfm95->endPacket();
     return true;
}

uint8_t tempData[50][7];
uint8_t tempCounter = 0;

bool RFM95Com::Receive(uint8_t* data, uint8_t length)
{
     //data[0] = 0x1F
     //data[1] = deviceAddress
     //data[2] = command (readCommand, readSettings, readStatus, writeCommand...)
     //data[3] = reg addr (close, open, setTeach...)
     //data[4..n] = Payload
     //data[5] = crc

     uint8_t* txDataTemp;
     uint8_t rxData[7];

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

     //check CRC
     if (CRC8(rxData, 6) != rxData[6])
     {
          //error crc
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

     if (tempCounter < 50) {
          tempData[tempCounter][0] = rxData[0];
          tempData[tempCounter][1] = rxData[1];
          tempData[tempCounter][2] = rxData[2];
          tempData[tempCounter][3] = rxData[3];
          tempData[tempCounter][4] = rxData[4];
          tempData[tempCounter][5] = rxData[5];
          tempData[tempCounter][6] = rxData[6];
          tempCounter++;
     }
     else {
          tempCounter = 0;
     }



     switch (rxData[2])
     {
     case SEND_SETTINGS:
          this->SetSettings(rxData);
          txDataTemp = txData;
          break;
     case SEND_COMMAND:
          this->SetCommand(rxData);
          txDataTemp = txData;
          break;
     case SEND_STATUS:
          this->SetStatus(rxData);
          txDataTemp = txData;
          break;
     case GET_SETTINGS:
          txDataTemp = this->GetSettings(rxData[3]);
          break;
     case GET_COMMAND:
          txDataTemp = this->GetCommand(rxData[3]);
          break;
     case GET_STATUS:
          txDataTemp = this->GetStatus(rxData[3]);
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

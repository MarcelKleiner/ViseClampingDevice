/*
 * RFM95Com.cpp
 *
 *  Created on: 26.12.2022
 *      Author: marce
 */

#include "RFM95Com.h"
#include "../AppMain/Defines.h"
#include "usbd_cdc_if.h"

bool RFM95Com::Transmitt(uint8_t *data, uint8_t length)
{
	if(data == NULL){
		return false;
	}

	rfm95->beginPacket();
	rfm95->write(data, length);
	rfm95->endPacket();
	return true;
}

bool RFM95Com::Receive(uint8_t *data, uint8_t length)
{
	//data[0] = 0x1F
	//data[1] = deviceAddress
	//data[2] = command (readCommand, readSettings, readStatus, writeCommand...)
	//data[3] = reg addr (close, open, setTeach...)
	//data[4..5] = Payload
	//data[6] = crc




	uint8_t* txDataTemp;

	uint8_t rxData[7];

	uint8_t packetSize = rfm95->parsePacket();
	if (packetSize != 0)
	{
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

		rxData[7] = '\n';

//		uint8_t delay = 5;
//		HAL_StatusTypeDef result = HAL_ERROR;
//
//		while(delay > 1 && result != HAL_OK){
//			result = (HAL_StatusTypeDef)CDC_Transmit_FS((uint8_t*) rxData, 8);
//			delay--;
//			HAL_Delay(1);
//		}

		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
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

		if(rxData[2] != 19){
			txData[0] = 1;
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
			case GET_STATUS:
				txDataTemp = this->GetStatus(rxData[3]);
				break;
			default:
				//not sported command
				txData[4] = 0;
				txData[5] = 0;
				break;
		}


		Transmitt(txDataTemp , 7);
		return true;
	}
	return false;
}

/*
 * Communication.cpp
 *
 *  Created on: 09.12.2022
 *      Author: marce
 */

#include "Communication.h"
#include "../AppMain/Defines.h"

Communication::Communication(DriveStatus *driveStatus, DriveSettings *driveSettings, RFM95_LoRa *rfm95)
{
	this->driveSettings = driveSettings;
	this->driveStatus = driveStatus;
	this->rfm95 = rfm95;
}


/*
 * Communication function with clamping modul
 * 1. Priority -> write Status (
 *
 *
 */
bool Communication::UpdateCom()
{
	uint8_t data2send[6] =
	{ 0 };

	return true;
}



void Communication::ReadData()
{
	uint8_t packetSize = rfm95->parsePacket();
	if (packetSize != 0)
	{
		uint8_t counter = 0;
		while (rfm95->available())
		{
			rxData[counter] = rfm95->read();
			if (counter > MAX_PACKET_2_RECEIVE)
			{
				return;
			}
			counter++;
		}

		uint8_t addr = rxData[0];

		if(addr != this->driveSettings->getDeviceAddress()){
			//wrong device address
			return;
		}



		uint8_t command = rxData[2];
		//data = rxData[2...(counter-1)]
		//uint8_t size = rxData[counter-1];
		uint8_t crc8 = rxData[counter];

		if (CRC8(rxData, counter - 1) != crc8)
		{
			//error crc error //ToDO
			return;
		}


		if(command == 0x1A){
			HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin, GPIO_PIN_SET);
		}

		switch (command)
		{
			case RCV_STATUS:
				//digitalInOut->WriteOutput(rxData[2]);
				break;
			case CLOSE_ADDR:

				break;
			case OPEN_ADDR:
				break;
			case TEACH_ADDR:
				break;
			case  RESET_ADDR:
				break;
			case DISABLE_ADDR:
				break;
			case STOP_ADDR:
				break;
			case ERROR_ADDR:
				break;
			case TEACH_TORQUE_ADDR:
				break;
			case TEACH_SPEED_ADDR:

				break;
			case CLAMPING_TORQUE_ADDR:
				break;
			case CLAMPING_SPEED_ADDR:
				break;
			case SELF_SHUTDOWN_DELAY_ADDR:
				break;
			case IN_POS_DIFF_ADDR:
				break;
			case OPENING_DISTANCE_ADDR:
				break;
			case UNDERVOLTAGE_WARNING_ADDR:
				break;
			case UNDERVOLTAGE_ERROR_ADDR:
				break;
			case OVER_CURRENT_WARNING_ADDR:
				break;
			case OVER_CURRENT_ERROR_ADDR:
				break;
			case DEVICE_ADDRESS_ADDR:
				break;

			default:
				//error no supported command //ToDO
				break;
		}
	}
}

bool Communication::SendData()
{

}


uint8_t Communication::CRC8(uint8_t *data, uint8_t length)
{
	uint8_t crc = 0xff;
	size_t i, j;
	for (i = 0; i < length; i++)
	{
		crc ^= data[i];
		for (j = 0; j < 8; j++)
		{
			if ((crc & 0x80) != 0)
				crc = (uint8_t) ((crc << 1) ^ 0x31);
			else
				crc <<= 1;
		}
	}
	return crc;
}

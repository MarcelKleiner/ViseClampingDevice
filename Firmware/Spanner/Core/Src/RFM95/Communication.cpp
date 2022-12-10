/*
 * Communication.cpp
 *
 *  Created on: 09.12.2022
 *      Author: marce
 */

#include "Communication.h"

Communication::Communication(DriveStatus *driveStatus,
		DriveSettings *driveSettings, RFM95_LoRa *rfm95,
		Digitll_IN_OUT *digitalInOut)
{

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
		}

		uint8_t addr = rxData[0];

		if(addr != this->driveSettings->getDeviceAddress()){
			//wrong device address
			return;
		}



		uint8_t command = rxData[1];
		//data = rxData[2...(counter-1)]
		//uint8_t size = rxData[counter-1];
		uint8_t crc8 = rxData[counter];

		if (CRC8(rxData, counter - 1) != crc8)
		{
			//error crc error //ToDO
			return;
		}

		switch (command)
		{
			case RCV_STATUS:
				digitalInOut->WriteOutput(rxData[2]);
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

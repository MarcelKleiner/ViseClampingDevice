/*
 * DI.cpp
 *
 *  Created on: Nov 5, 2022
 *      Author: marce
 */

#include "DI.h"



void DigitalIN::DigitalIN()
{

}

void DigitalIN::Read()
{

	configeWriteStatus = CONFIG_WRITE;

	if (configeWriteStatus && !previousConfigeWriteStatus)
	{
		//read digial config
		uint8_t data = ((uint8_t) CONFIG_ADDR_7 << 7)
				+ ((uint8_t) CONFIG_ADDR_6 << 6)
				+ ((uint8_t) CONFIG_ADDR_5 << 5)
				+ ((uint8_t) CONFIG_ADDR_4 << 4)
				+ ((uint8_t) CONFIG_ADDR_3 << 3)
				+ ((uint8_t) CONFIG_ADDR_2 << 2)
				+ ((uint8_t) CONFIG_ADDR_1 << 1);

		queue.Enqueue(config);

		if (isAddressReceived)
		{

		}
		else
		{
			CheckAddress(config);
		}

	}

	previousConfigeWriteStatus = configeWriteStatus;
}


void DigitalIN::CheckAddress(uint8_t data)
{
	receivedAddress = data;
	switch (data)
			{
				case CLOSE:
				case OPEN:
				case TEACH:
				case RESET:
				case ENABLE:
				case DISABLE:
				case STOP:
				case TEACH_TORQUE:
				case TEACH_SPEED:
				case CLAMPING_TORQUE:
				case CLAMPING_SPEED:
				case IN_POS_DIFF:
				case OPENING_DISTANCE:
				case OVER_CURRENT_WARNING:
				case OVER_CURRENT_ERROR:
					expectedDataSize = 1;
					break;
				case SELF_SHUTDOWN_DELAY:
				case UNDERVOLTAGE_WARNING:
				case UNDERVOLTAGE_ERROR:
					expectedDataSize = 2;
					break;
				default:
					receivedAddress = 0;
					expectedDataSize = 0;
					break;
			}
}

void DigitalIN::CheckData(uint8_t data)
{
	switch (receivedAddress)
			{
				case CLOSE:

				case OPEN:
				case TEACH:
				case RESET:
				case ENABLE:
				case DISABLE:
				case STOP:
				case TEACH_TORQUE:
				case TEACH_SPEED:
				case CLAMPING_TORQUE:
				case CLAMPING_SPEED:
				case IN_POS_DIFF:
				case OPENING_DISTANCE:
				case OVER_CURRENT_WARNING:
				case OVER_CURRENT_ERROR:
					expectedDataSize = 1;
					break;
				case SELF_SHUTDOWN_DELAY:
				case UNDERVOLTAGE_WARNING:
				case UNDERVOLTAGE_ERROR:
					expectedDataSize = 2;
					break;
			}
}




uint8_t DigitalIN::GetData()
{
	return queue.Dequeue();
}

bool DigitalIN::IsDataReady()
{
	return !queue.IsEmpty();
}

bool DigitalIN::IsQueueOverflow()
{
//not implemented
	return false;
}

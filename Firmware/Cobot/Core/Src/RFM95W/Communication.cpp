/*
 * Communication.cpp
 *
 *  Created on: 26.11.2022
 *      Author: marce
 */

#include "Communication.h"

Communication::Communication(DriveStatus *driveStatus,
		DriveSettings *driveSettings, RFM95_LoRa *rfm95, Digitll_IN_OUT *digitalInOut)
{
	this->driveSettings = driveSettings;
	this->driveStatus = driveStatus;
	this->rfm95 = rfm95;
	this->digitalInOut = digitalInOut;
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

	if (digitalInOut->isStatusChanged())
	{
		uint8_t data = ((uint8_t) driveStatus->isClose() << 8)
				| ((uint8_t) driveStatus->isDisable() << 8)
				| ((uint8_t) driveStatus->isEnable() << 8)
				| ((uint8_t) driveStatus->isOpen() << 8)
				| ((uint8_t) driveStatus->isReset() << 8)
				| ((uint8_t) driveStatus->isStop() << 8)
				| ((uint8_t) driveStatus->isTeach() << 8)
				| ((uint8_t) driveStatus->isWriteConfig() << 8);

		data2send[0] = driveSettings->getDeviceAddress();
		data2send[1] = SEND_COMMAND;
		data2send[2] = data;
		data2send[3] = 5;
		data2send[4] = CRC8(data2send, data2send[3] - 1);
	}
	else if (digitalInOut->isSettingsChanged() != 0)
	{
		uint16_t commands = digitalInOut->isSettingsChanged();
		data2send[0] = driveSettings->getDeviceAddress();
		data2send[1] = SEND_SETTINGS;

		if (commands & TEACH_TORQUE_CHANGE)
		{
			data2send[2] = TEACH_TORQUE;
			uint16_t value = driveSettings->getTeachTroque();
			data2send[3] = value >> 8;
			data2send[4] = value;
			digitalInOut->ResetSettingsChanged(TEACH_TORQUE_CHANGE);
		}
		else if (commands & TEACH_SPEED_CHANGE)
		{
			uint16_t value = driveSettings->getTeachSpeed();
			data2send[2] = TEACH_SPEED;
			data2send[3] = value >> 8;
			data2send[4] = value;
			digitalInOut->ResetSettingsChanged(TEACH_SPEED_CHANGE);
		}
		else if (commands & CLAMPING_TORQUE_CHANGE)
		{
			uint16_t value = driveSettings->getClampingTorque();
			data2send[2] = CLAMPING_TORQUE;
			data2send[3] = value >> 8;
			data2send[4] = value;
			digitalInOut->ResetSettingsChanged(CLAMPING_TORQUE_CHANGE);
		}
		else if (commands & CLAMPING_SPEED_CHANGE)
		{
			uint16_t value = driveSettings->getClampingSpeed();
			data2send[2] = CLAMPING_SPEED;
			data2send[3] = value >> 8;
			data2send[4] = value;
			digitalInOut->ResetSettingsChanged(CLAMPING_SPEED_CHANGE);
		}
		else if (commands & SELF_SHUTDOWN_DELAY_CHANGE)
		{
			uint16_t value = driveSettings->getSelfShutdownDelay();
			data2send[2] = SELF_SHUTDOWN_DELAY;
			data2send[3] = value >> 8;
			data2send[4] = value;
			digitalInOut->ResetSettingsChanged(SELF_SHUTDOWN_DELAY_CHANGE);
		}
		else if (commands & IN_POS_DIFF_CHANGE)
		{
			uint16_t value = driveSettings->getInPosDiff();
			data2send[2] = IN_POS_DIFF;
			data2send[3] = value >> 8;
			data2send[4] = value;
			digitalInOut->ResetSettingsChanged(IN_POS_DIFF_CHANGE);
		}
		else if (commands & OPENING_DISTANCE_CHANGE)
		{
			uint16_t value = driveSettings->getOpeningDistance();
			data2send[2] = OPENING_DISTANCE;
			data2send[3] = value >> 8;
			data2send[4] = value;
			digitalInOut->ResetSettingsChanged(OPENING_DISTANCE_CHANGE);
		}
		else if (commands & UNDERVOLTAGE_WARNING_CHANGE)
		{
			uint16_t value = driveSettings->getUnderVoltageWarning();
			data2send[2] = UNDERVOLTAGE_WARNING;
			data2send[3] = value >> 8;
			data2send[4] = value;
			digitalInOut->ResetSettingsChanged(UNDERVOLTAGE_WARNING_CHANGE);
		}
		else if (commands & UNDERVOLTAGE_ERROR_CHANGE)
		{
			uint16_t value = driveSettings->getUnderVoltageError();
			data2send[2] = UNDERVOLTAGE_ERROR;
			data2send[3] = value >> 8;
			data2send[4] = value;
			digitalInOut->ResetSettingsChanged(UNDERVOLTAGE_ERROR_CHANGE);
		}
		else if (commands & OVER_CURRENT_WARNING_CHANGE)
		{
			uint16_t value = driveSettings->getOverCurrentWarning();
			data2send[2] = OVER_CURRENT_WARNING;
			data2send[3] = value >> 8;
			data2send[4] = value;
			digitalInOut->ResetSettingsChanged(OVER_CURRENT_WARNING_CHANGE);
		}
		else if (commands & OVER_CURRENT_ERROR_CHANGE)
		{
			uint16_t value = driveSettings->getOverCurrentError();
			data2send[2] = OVER_CURRENT_ERROR;
			data2send[3] = value >> 8;
			data2send[4] = value;
			digitalInOut->ResetSettingsChanged(OVER_CURRENT_ERROR_CHANGE);
		}

		data2send[4] = 6;
		data2send[5] = CRC8(data2send, data2send[4]-1);
	}
	else
	{
		data2send[0] = driveSettings->getDeviceAddress();
		data2send[1] = SEND_STATUS_REQ;
		data2send[2] = 4;
		data2send[3] = CRC8(data2send, data2send[2]-1);
	}

	rfm95->write(data2send, 6);
	return true;
}


void Communication::ReadData(){

	uint8_t packetSize = rfm95->parsePacket();
	if(packetSize != 0){
		uint8_t counter = 0;
		while(rfm95->available()){
			rxData[counter] = rfm95->read();
			if(counter > MAX_PACKET_2_RECEIVE){
				return;
			}
		}

		//uint8_t addr = rxData[0];
		uint8_t command = rxData[1];
		//data = rxData[2...(counter-1)]
		//uint8_t size = rxData[counter-1];
		uint8_t crc8 = rxData[counter];

		if(CRC8(rxData, counter-1) != crc8){
			//error crc error //ToDO
			return;
		}

		switch (command) {
			case RCV_STATUS:
				digitalInOut->WriteOutput(rxData[2]);
				break;
			default:
				//error no supported command //ToDO
				break;
		}
	}
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


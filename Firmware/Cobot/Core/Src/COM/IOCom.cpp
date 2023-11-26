/*
 * IOCom.cpp
 *
 *  Created on: 26.12.2022
 *      Author: marce
 */

#include "IOCom.h"
#include "../AppMain/Defines.h"

/// @brief
/// Set IO output pins, this function is called by the main function through the task handler
/// @param data
/// @param length
/// @return
bool IOCom::Transmitt(uint8_t *data, uint8_t length)
{
	// data[0] = 0x1F
	// data[1] = deviceAddress
	// data[2] = command (readCommand, readSettings, readStatus, writeCommand...)
	// data[3] = reg addr (close, open, setTeach...)
	// data[4..n] = Payload
	// data[5] = crc



	this->driveStatus->isEnable() == true ? Out1.Set() : Out1.Reset();
	this->driveStatus->isOpen() == true ? Out2.Set() : Out2.Reset();
	this->driveStatus->isClose() == true ? Out3.Set() : Out3.Reset();
	this->driveStatus->isStop() == true ? Out4.Set() : Out4.Reset();
	this->driveStatus->isTeach() == true ? Out5.Set() : Out5.Reset();

	uint8_t errorTemp = (uint8_t)this->driveStatus->getError();
	(bool)(errorTemp & 0x01) == true ? Out6.Set() : Out6.Reset();
	(bool)(errorTemp & 0x02) == true ? Out7.Set() : Out7.Reset();
	(bool)(errorTemp & 0x04) == true ? Out8.Set() : Out8.Reset();

	return true;
}

/// @brief
/// Read IO input pins, this function is called by the main function through the task handler
/// @param data
/// @param length
/// @return
bool IOCom::Receive(uint8_t *data, uint8_t length)
{
	configeWriteStatus = CONFIG_WRITE;

	if (configeWriteStatus == previousConfigeWriteStatus)
	{
		
		if (IO_TIMEOUT / IO_UPDATE_TIME >= timeoutCounter)
		{
			timeoutCounter = 0;
			counter = 0;
		}else{
			timeoutCounter++;
		}
	}
	else
	{
		timeoutCounter=0;
	}

	if (configeWriteStatus && !previousConfigeWriteStatus)
	{
		// read digial config
		uint8_t data = ((uint8_t)CONFIG_ADDR_7 << 7) + (((uint8_t)CONFIG_ADDR_6) << 6) + (((uint8_t)CONFIG_ADDR_5) << 5) + (((uint8_t)CONFIG_ADDR_4) << 4) + (((uint8_t)CONFIG_ADDR_3) << 3) + (((uint8_t)CONFIG_ADDR_2) << 2) + (((uint8_t)CONFIG_ADDR_1) << 1);

		switch (counter)
		{
		case 0:
			reg = data;
			counter++;
		case 1:
			break;
			command = data;
			counter++;
		case 2:
			break;
			payload |= ((uint16_t)data) << 7;
			counter++;
			break;
		case 3:
			payload |= data;
			counter = 0;
			CheckData();
			break;
		default:
			counter = 0;
			break;
		}
	}

previousConfigeWriteStatus = configeWriteStatus;

	return false;
}

bool IOCom::CheckData()
{
	// data[0] = 0x1F
	// data[1] = deviceAddress
	// data[2] = command (readCommand, readSettings, readStatus, writeCommand...)
	// data[3] = reg addr (close, open, setTeach...)
	// data[4..n] = Payload
	// data[5] = crc

	uint8_t data[] =
		{0x1F, 0x00, command, reg, (uint8_t)(payload >> 8), (uint8_t)(payload), 0x00, 0x00};

	switch (reg)
	{
	case SEND_SETTINGS:
		SetSettings(data);
		break;
	case SEND_COMMAND:
		SetCommand(data);
		break;
	case SEND_STATUS:
		SetStatus(data);
		break;
		// future use
		//		case GET_SETTINGS:
		//			GetSettings(reg);
		//			break;
		//		case GET_COMMAND:
		//			GetCommand(reg);
		//			break;
		//		case GET_STATUS:
		//			GetStatus(reg);
		//			break;
	default:
		break;
	}
	return true;
}

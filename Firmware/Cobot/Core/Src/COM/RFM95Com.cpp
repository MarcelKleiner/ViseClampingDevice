/*
 * RFM95Com.cpp
 *
 *  Created on: 26.12.2022
 *      Author: marce
 */

#include "RFM95Com.h"
#include "../AppMain/Defines.h"

bool RFM95Com::Transmitt(uint8_t *data, uint8_t length)
{
	uint8_t *txData;

	if (this->driveCommand->isCommandChanged() != 0)
	{
		uint8_t command = driveCommand->getCommandChangedReg();

		if (command & CLOSE_CHANGE)
		{
			txData = this->GetCommand(CLOSE_ADDR);
			driveCommand->ResetCommandChanged(CLOSE_CHANGE);
		}
		else if (command & OPEN_CHANGE)
		{
			txData = this->GetCommand(OPEN_ADDR);
			driveCommand->ResetCommandChanged(OPEN_CHANGE);
		}
		else if (command & TEACH_CHANGE)
		{
			txData = this->GetCommand(TEACH_ADDR);
			driveCommand->ResetCommandChanged(TEACH_CHANGE);
		}
		else if (command & RESET_CHANGE)
		{
			txData = this->GetCommand(RESET_ADDR);
			driveCommand->ResetCommandChanged(RESET_CHANGE);
		}
		else if (command & ENABLE_CHANGE)
		{
			txData = this->GetCommand(ENABLE_ADDR);
			driveCommand->ResetCommandChanged(ENABLE_CHANGE);
		}
		else if (command & DISABLE_CHANGE)
		{
			txData = this->GetCommand(DISABLE_ADDR);
			driveCommand->ResetCommandChanged(DISABLE_CHANGE);
		}
		else if (command & STOP_CHANGE)
		{
			txData = this->GetCommand(STOP_ADDR);
			driveCommand->ResetCommandChanged(STOP_CHANGE);
		}
	}
	else if (driveSettings->isSettingsChanged() != 0)
	{
		uint16_t commands = driveSettings->getSettingsChangedReg();

		if (commands & TEACH_TORQUE_CHANGE)
		{
			txData = this->GetSettings(TEACH_TORQUE_ADDR);
			driveSettings->ResetSettingsChanged(TEACH_TORQUE_CHANGE);
		}
		else if (commands & TEACH_SPEED_CHANGE)
		{
			txData = this->GetSettings(TEACH_SPEED_ADDR);
			driveSettings->ResetSettingsChanged(TEACH_SPEED_CHANGE);
		}
		else if (commands & CLAMPING_TORQUE_CHANGE)
		{
			txData = this->GetSettings(CLAMPING_TORQUE_ADDR);
			driveSettings->ResetSettingsChanged(CLAMPING_TORQUE_CHANGE);
		}
		else if (commands & CLAMPING_SPEED_CHANGE)
		{
			txData = this->GetSettings(CLAMPING_SPEED_ADDR);
			driveSettings->ResetSettingsChanged(CLAMPING_SPEED_CHANGE);
		}
		else if (commands & SELF_SHUTDOWN_DELAY_CHANGE)
		{
			txData = this->GetSettings(SELF_SHUTDOWN_DELAY_ADDR);
			driveSettings->ResetSettingsChanged(SELF_SHUTDOWN_DELAY_CHANGE);
		}
		else if (commands & IN_POS_DIFF_CHANGE)
		{
			txData = this->GetSettings(IN_POS_DIFF_ADDR);
			driveSettings->ResetSettingsChanged(IN_POS_DIFF_CHANGE);
		}
		else if (commands & OPENING_DISTANCE_CHANGE)
		{
			txData = this->GetSettings(OPENING_DISTANCE_ADDR);
			driveSettings->ResetSettingsChanged(OPENING_DISTANCE_CHANGE);
		}
		else if (commands & UNDERVOLTAGE_WARNING_CHANGE)
		{
			txData = this->GetSettings(UNDERVOLTAGE_WARNING_ADDR);
			driveSettings->ResetSettingsChanged(UNDERVOLTAGE_WARNING_CHANGE);
		}
		else if (commands & UNDERVOLTAGE_ERROR_CHANGE)
		{
			txData = this->GetSettings(UNDERVOLTAGE_ERROR_ADDR);
			driveSettings->ResetSettingsChanged(UNDERVOLTAGE_ERROR_CHANGE);
		}
		else if (commands & OVER_CURRENT_WARNING_CHANGE)
		{
			txData = this->GetSettings(OVER_CURRENT_WARNING_ADDR);
			driveSettings->ResetSettingsChanged(OVER_CURRENT_WARNING_CHANGE);
		}
		else if (commands & OVER_CURRENT_ERROR_CHANGE)
		{
			txData = this->GetSettings(OVER_CURRENT_ERROR_ADDR);
			driveSettings->ResetSettingsChanged(OVER_CURRENT_ERROR_CHANGE);
		}
	}
	else
	{
		uint8_t dataTemp[] = {0x1F, driveSettings->getDeviceAddress(),GET_STATUS,0x00,0x00};
		dataTemp[5] = CRC8(dataTemp, 4);
		txData = dataTemp;
	}

	rfm95->beginPacket();
	rfm95->write(txData, 5);
	rfm95->endPacket();
	return true;
}

bool RFM95Com::Receive(uint8_t *data, uint8_t length)
{
	//data[0] = 0x1F
	//data[1] = deviceAddress
	//data[2] = command (readCommand, readSettings, readStatus, writeCommand...)
	//data[3] = reg addr (close, open, setTeach...)
	//data[4..n] = Payload
	//data[5] = crc

	uint8_t packetSize = rfm95->parsePacket();
	if (packetSize != 0)
	{
		uint8_t counter = 0;
		while (rfm95->available())
		{
			data[counter] = rfm95->read();
			if (counter > MAX_PACKET_2_RECEIVE)
			{
				return false;
			}
		}

		//check CRC
		if (CRC8(data, 4) != data[5])
		{
			//error crc error //ToDO
			return false;
		}

		switch (data[2])
		{
			case SEND_SETTINGS:
				this->SetSettings(data);
				break;
			case SEND_COMMAND:
				this->SetCommand(data);
				break;
			case SEND_STATUS:
				this->SetStatus(data);
				break;
			default:
				//not sported command
				data[2] = 0;
				break;
		}
	}
	return true;
}

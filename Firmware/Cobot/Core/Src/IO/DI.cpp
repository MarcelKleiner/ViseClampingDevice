/*
 * DI.cpp
 *
 *  Created on: Nov 5, 2022
 *      Author: marce
 */

#include "DI.h"

Digitll_IN_OUT::Digitll_IN_OUT(DriveSettings *driveSettings, DriveStatus *driveStatus,DriveCommand *driveCommand)
{
	this->driveSettings = driveSettings;
	this->driveStatus = driveStatus;
	this->driveCommand = driveCommand;
	timeoutCounter = 0;

}

void Digitll_IN_OUT::Read()
{

	configeWriteStatus = CONFIG_WRITE;

	if (configeWriteStatus && !previousConfigeWriteStatus)
	{
		//read digial config
		uint8_t data = ((uint8_t) CONFIG_ADDR_7 << 7)
				+ (((uint8_t) CONFIG_ADDR_6) << 6)
				+ (((uint8_t) CONFIG_ADDR_5) << 5)
				+ (((uint8_t) CONFIG_ADDR_4) << 4)
				+ (((uint8_t) CONFIG_ADDR_3) << 3)
				+ (((uint8_t) CONFIG_ADDR_2) << 2)
				+ (((uint8_t) CONFIG_ADDR_1) << 1);

		//Data/Adress check
		if (isAddressReceived)
		{
			queue.Enqueue(data);
			expectedDataSize--;
			if (expectedDataSize == 0)
			{
				CheckData();
			}
		}
		else
		{
			CheckAddress(data);
		}
		timeoutCounter = 0;
	}

	//Timeoutcounter handling
	if (timeoutCounter >= READ_TIMEOUT)
	{
		timeoutCounter = 0;
		isAddressReceived = false;
		expectedDataSize = 0;
	}
	else
	{
		timeoutCounter++;
	}

	previousConfigeWriteStatus = configeWriteStatus;
}

bool Digitll_IN_OUT::CheckAddress(uint8_t data)
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
			return false;
			break;
	}
	return true;
}

void Digitll_IN_OUT::CheckData()
{
	switch (receivedAddress)
	{
		case CLOSE:
			driveCommand->setClose(queue.Dequeue() == 0x01);
			statusChangedReg = true;
			break;
		case OPEN:
			driveCommand->setOpen(queue.Dequeue() == 0x01);
			statusChangedReg = true;
			statusChangedReg = true;
			break;
		case TEACH:
			driveCommand->setTeach(queue.Dequeue() == 0x01);
			statusChangedReg = true;
			break;
		case RESET:
			driveCommand->setReset(queue.Dequeue() == 0x01);
			statusChangedReg = true;
			break;
		case ENABLE:
			driveCommand->setEnable(queue.Dequeue() == 0x01);
			statusChangedReg = true;
			break;
		case DISABLE:
			driveCommand->setDisable(queue.Dequeue() == 0x01);
			statusChangedReg = true;
			break;
		case STOP:
			driveCommand->setStop(queue.Dequeue() == 0x01);
			statusChangedReg = true;
			break;
		case TEACH_TORQUE:
			dataTemp[0] = queue.Dequeue();
			dataTemp[1] = queue.Dequeue();
			value = ((uint16_t) dataTemp[1]) << 7 | dataTemp[0];
			driveSettings->setTeachTroque(value);
			settingsChangedReg |= TEACH_TORQUE_CHANGE;
			break;
		case TEACH_SPEED:
			dataTemp[0] = queue.Dequeue();
			dataTemp[1] = queue.Dequeue();
			value = ((uint16_t) dataTemp[1]) << 7 | dataTemp[0];
			driveSettings->setTeachSpeed(value);
			settingsChangedReg |= TEACH_SPEED_CHANGE;
			break;
		case CLAMPING_TORQUE:
			dataTemp[0] = queue.Dequeue();
			dataTemp[1] = queue.Dequeue();
			value = ((uint16_t) dataTemp[1]) << 7 | dataTemp[0];
			driveSettings->setClampingTorque(value);
			settingsChangedReg |= CLAMPING_TORQUE_CHANGE;
			break;
		case CLAMPING_SPEED:
			dataTemp[0] = queue.Dequeue();
			dataTemp[1] = queue.Dequeue();
			value = ((uint16_t) dataTemp[1]) << 7 | dataTemp[0];
			driveSettings->setClampingSpeed(value);
			settingsChangedReg |= CLAMPING_SPEED_CHANGE;
			break;
		case IN_POS_DIFF:
			dataTemp[0] = queue.Dequeue();
			dataTemp[1] = queue.Dequeue();
			value = ((uint16_t) dataTemp[1]) << 7 | dataTemp[0];
			driveSettings->setInPosDiff(value);
			settingsChangedReg |= IN_POS_DIFF_CHANGE;
			break;
		case OPENING_DISTANCE:
			dataTemp[0] = queue.Dequeue();
			dataTemp[1] = queue.Dequeue();
			value = ((uint16_t) dataTemp[1]) << 7 | dataTemp[0];
			driveSettings->setOpeningDistance(value);
			settingsChangedReg |= OPENING_DISTANCE_CHANGE;
			break;
		case OVER_CURRENT_WARNING:
			dataTemp[0] = queue.Dequeue();
			dataTemp[1] = queue.Dequeue();
			value = ((uint16_t) dataTemp[1]) << 7 | dataTemp[0];
			driveSettings->setOverCurrentWarning(value);
			settingsChangedReg |= OVER_CURRENT_WARNING_CHANGE;
			break;
		case OVER_CURRENT_ERROR:
			dataTemp[0] = queue.Dequeue();
			dataTemp[1] = queue.Dequeue();
			value = ((uint16_t) dataTemp[1]) << 7 | dataTemp[0];
			driveSettings->setOverCurrentError(value);
			settingsChangedReg |= OVER_CURRENT_ERROR_CHANGE;
			break;
		case SELF_SHUTDOWN_DELAY:
			dataTemp[0] = queue.Dequeue();
			dataTemp[1] = queue.Dequeue();
			value = ((uint16_t) dataTemp[1]) << 7 | dataTemp[0];
			driveSettings->setSelfShutdownDelay(value);
			settingsChangedReg |= SELF_SHUTDOWN_DELAY_CHANGE;
			break;
		case UNDERVOLTAGE_WARNING:
			dataTemp[0] = queue.Dequeue();
			dataTemp[1] = queue.Dequeue();
			value = ((uint16_t) dataTemp[1]) << 7 | dataTemp[0];
			driveSettings->setUnderVoltageWarning(value);
			settingsChangedReg |= UNDERVOLTAGE_WARNING_CHANGE;
			break;
		case UNDERVOLTAGE_ERROR:
			dataTemp[0] = queue.Dequeue();
			dataTemp[1] = queue.Dequeue();
			value = ((uint16_t) dataTemp[1]) << 7 | dataTemp[0];
			driveSettings->setUnderVoltageError(value);
			settingsChangedReg |= UNDERVOLTAGE_ERROR_CHANGE;
			break;
	}
}


uint16_t Digitll_IN_OUT::isSettingsChanged(){
	settingsChangedReg |= UNDERVOLTAGE_ERROR_CHANGE;
	settingsChangedReg |= UNDERVOLTAGE_WARNING_CHANGE;
	return settingsChangedReg;
}

void Digitll_IN_OUT::ResetSettingsChanged(uint16_t bit){
	settingsChangedReg &= ~bit;
}

bool Digitll_IN_OUT::isStatusChanged(){
	bool statusChangedRegTemp = statusChangedReg;
	statusChangedReg = false;
	return statusChangedRegTemp;
}





void Digitll_IN_OUT::WriteOutput(uint8_t data){

	data & 0x01 ? Out1.Set() : Out1.Reset();
	data & 0x02 ? Out2.Set() : Out2.Reset();
	data & 0x04 ? Out3.Set() : Out3.Reset();
	data & 0x08 ? Out4.Set() : Out4.Reset();
	data & 0x10 ? Out5.Set() : Out5.Reset();
	data & 0x20 ? Out6.Set() : Out6.Reset();
	data & 0x40 ? Out7.Set() : Out7.Reset();
	data & 0x80 ? Out8.Set() : Out7.Reset();
}





/*
 * DriveSettings.cpp
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#include "DriveSettings.h"
#include "../AppMain/Defines.h"


DriveSettings::DriveSettings()
{
	settingsChangedReg = 0;
}


/****************************************************************************************
 / * 	Clamping speed get/set
 ****************************************************************************************/
uint16_t DriveSettings::getClampingSpeed() const
{
	return clampingSpeed;
}

void DriveSettings::setClampingSpeed(uint16_t clampingSpeed)
{
	if (this->clampingSpeed != clampingSpeed)
	{
		this->clampingSpeed = clampingSpeed;
		this->settingsChangedReg |= CLAMPING_SPEED_CHANGE;
	}
}

/****************************************************************************************
 / * 	Clamping torque get/set
 ****************************************************************************************/
uint16_t DriveSettings::getClampingTorque() const
{
	return clampingTorque;
}

void DriveSettings::setClampingTorque(uint16_t clampingTorque)
{
	if (this->clampingTorque != clampingTorque)
	{
		this->clampingTorque = clampingTorque;
		this->settingsChangedReg |= CLAMPING_TORQUE_CHANGE;
	}
}

/****************************************************************************************
 / * 	clamping position difference get/set
 ****************************************************************************************/
uint16_t DriveSettings::getInPosDiff() const
{
	return inPosDiff;
}

void DriveSettings::setInPosDiff(uint16_t inPosDiff)
{
	if (this->inPosDiff != inPosDiff)
	{
		this->inPosDiff = inPosDiff;
		this->settingsChangedReg |= IN_POS_DIFF_CHANGE;
	}

}

/****************************************************************************************
 / * 	opening distance get/set
 ****************************************************************************************/
uint16_t DriveSettings::getOpeningDistance() const
{
	return openingDistance;
}

void DriveSettings::setOpeningDistance(uint16_t openingDistance)
{
	if (this->openingDistance != openingDistance)
	{
		this->openingDistance = openingDistance;
		this->settingsChangedReg |= OPENING_DISTANCE_CHANGE;
	}
}

/****************************************************************************************
 / * 	overcurrent time threshold get/set
 ****************************************************************************************/
//uint16_t DriveSettings::getOverCurrentTimeThreshold() const
//{
//	return overCurrentTimeThreshold;
//}
//
//void DriveSettings::setOverCurrentTimeThreshold(
//		uint16_t overCurrentTimeThreshold)
//{
//	if (this->overCurrentTimeThreshold != overCurrentTimeThreshold)
//	{
//		this->overCurrentTimeThreshold = overCurrentTimeThreshold;
//		this->settingsChangedReg |= OVER_CURRENT_TIME_TH_CHANGE;
//	}
//}

/****************************************************************************************
 / * 	overcurrent warning get/set
 ****************************************************************************************/
uint16_t DriveSettings::getOverCurrentWarning() const
{
	return overCurrentWarning;
}

void DriveSettings::setOverCurrentWarning(uint16_t overCurrentWarning)
{
	if (this->overCurrentWarning != overCurrentWarning)
	{
		this->overCurrentWarning = overCurrentWarning;
		this->settingsChangedReg |= OVER_CURRENT_WARNING_CHANGE;
	}
}
/****************************************************************************************
 / * 	self shutdown delay get/set
 ****************************************************************************************/
uint16_t DriveSettings::getSelfShutdownDelay() const
{
	return selfShutdownDelay;
}

void DriveSettings::setSelfShutdownDelay(uint16_t selfShutdownDelay)
{
	if (this->selfShutdownDelay != selfShutdownDelay)
	{
		this->selfShutdownDelay = selfShutdownDelay;
		this->settingsChangedReg |= SELF_SHUTDOWN_DELAY_CHANGE;
	}
}

/****************************************************************************************
 / * 	teach speed get/set
 ****************************************************************************************/
uint16_t DriveSettings::getTeachSpeed() const
{
	return teachSpeed;
}

void DriveSettings::setTeachSpeed(uint16_t teachSpeed)
{
	if (this->teachSpeed != teachSpeed)
	{
		this->teachSpeed = teachSpeed;
		this->settingsChangedReg |= TEACH_SPEED_CHANGE;
	}
}
/****************************************************************************************
 / * 	teach torque get/set
 ****************************************************************************************/
uint16_t DriveSettings::getTeachTroque() const
{
	return teachTroque;
}

void DriveSettings::setTeachTroque(uint16_t teachTroque)
{
	if (this->teachTroque != teachTroque)
	{
		this->teachTroque = teachTroque;
		this->settingsChangedReg |= TEACH_TORQUE_CHANGE;
	}
}
/****************************************************************************************
 / * 	undervoltage error get/set
 ****************************************************************************************/
uint16_t DriveSettings::getUnderVoltageError() const
{
	return underVoltageError;
}

void DriveSettings::setUnderVoltageError(uint16_t underVoltageError)
{
	if (this->underVoltageError != underVoltageError)
	{
		this->underVoltageError = underVoltageError;
		this->settingsChangedReg |= UNDERVOLTAGE_ERROR_CHANGE;
	}
}

/****************************************************************************************
 / * 	undervoltage warning get/set
 ****************************************************************************************/
uint16_t DriveSettings::getUnderVoltageWarning() const
{
	return underVoltageWarning;
}

void DriveSettings::setUnderVoltageWarning(uint16_t underVoltageWarning)
{
	if (this->underVoltageWarning != underVoltageWarning)
	{
		this->underVoltageWarning = underVoltageWarning;
		this->settingsChangedReg |= UNDERVOLTAGE_WARNING_CHANGE;
	}
}
/****************************************************************************************
 / * 	overcurrent error get/set
 ****************************************************************************************/
uint16_t DriveSettings::getOverCurrentError() const
{
	return overCurrentError;
}

void DriveSettings::setOverCurrentError(uint16_t overCurrentError)
{
	if (this->overCurrentError != overCurrentError)
	{
		this->overCurrentError = overCurrentError;
		this->settingsChangedReg |= OVER_CURRENT_ERROR_CHANGE;
	}
}
/****************************************************************************************
 / * 	device address get/set
 ****************************************************************************************/
uint8_t DriveSettings::getDeviceAddress() const
{
	return deviceAddress;
}

void DriveSettings::setDeviceAddress(uint8_t deviceAddress = 0)
{
	this->deviceAddress = deviceAddress;
}

/****************************************************************************************
 / * 	device address get/set
 ****************************************************************************************/
bool DriveSettings::isSaveSettings()
{
	bool saveSettingsTemp = this->saveSettings;
	this->saveSettings = false;
	return saveSettingsTemp;
}

void DriveSettings::setSaveSettings(bool saveSettings)
{
	this->saveSettings = saveSettings;
}


bool DriveSettings::isSettingsChanged() const
{
	return (settingsChangedReg != 0);
}

uint16_t DriveSettings::getSettingsChangedReg() const
{
	return this->settingsChangedReg;
}

void DriveSettings::ResetSettingsChanged(uint16_t bit){
	settingsChangedReg &= ~bit;

	if(bit != 0)
	{
		saveSettings = true;
	}
}

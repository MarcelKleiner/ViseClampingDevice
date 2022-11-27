/*
 * DriveSettings.cpp
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#include "DriveSettings.h"

/****************************************************************************************
 / * 	Clamping speed get/set
 ****************************************************************************************/
uint16_t DriveSettings::getClampingSpeed() const
{
	return clampingSpeed;
}

void DriveSettings::setClampingSpeed(uint16_t clampingSpeed)
{
	this->clampingSpeed = clampingSpeed;
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
	this->clampingTorque = clampingTorque;
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
	this->inPosDiff = inPosDiff;
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
	this->openingDistance = openingDistance;
}

/****************************************************************************************
 / * 	overcurrent time threshold get/set
 ****************************************************************************************/
uint16_t DriveSettings::getOverCurrentTimeThreshold() const
{
	return overCurrentTimeThreshold;
}

void DriveSettings::setOverCurrentTimeThreshold(uint16_t overCurrentTimeThreshold)
{
	this->overCurrentTimeThreshold = overCurrentTimeThreshold;
}

/****************************************************************************************
 / * 	overcurrent warning get/set
 ****************************************************************************************/
uint16_t DriveSettings::getOverCurrentWarning() const
{
	return overCurrentWarning;
}

void DriveSettings::setOverCurrentWarning(uint16_t overCurrentWarning)
{
	this->overCurrentWarning = overCurrentWarning;
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
	this->selfShutdownDelay = selfShutdownDelay;
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
	this->teachSpeed = teachSpeed;
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
	this->teachTroque = teachTroque;
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
	this->underVoltageError = underVoltageError;
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
	this->underVoltageWarning = underVoltageWarning;
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
	this->overCurrentError = overCurrentError;
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

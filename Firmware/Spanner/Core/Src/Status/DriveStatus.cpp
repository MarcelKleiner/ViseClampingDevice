/*
 * DriveStatus.cpp
 *
 *  Created on: 22.10.2022
 *      Author: marce
 */

#include "DriveStatus.h"

DriveStatus::DriveStatus() {
	zeroCurrentValue = 1538;
}


/****************************************************************************************
 / * 	close get/set
 ****************************************************************************************/
bool DriveStatus::isClose()
{
	return close;
}

void DriveStatus::setClose(bool close)
{
	if (this->close != close)
	{
		this->close = close;
		statusChanged = true;
	}
}

/****************************************************************************************
 / * 	open get/set
 ****************************************************************************************/
bool DriveStatus::isOpen()
{
	return open;
}

void DriveStatus::setOpen(bool open)
{
	if (this->open != open)
	{
		this->open = open;
		statusChanged = true;
	}
}


/****************************************************************************************
 / * 	enable get/set
 ****************************************************************************************/
bool DriveStatus::isEnable()
{
	return enable;
}

void DriveStatus::setEnable(bool enable)
{
	if (this->enable != enable)
	{
		this->enable = enable;
		statusChanged = true;
	}
}

/****************************************************************************************
 / * 	reset get/set
 ****************************************************************************************/
bool DriveStatus::isReset()
{
	return reset;
}

void DriveStatus::setReset(bool reset)
{
	if (this->reset != reset)
	{
		this->reset = reset;
		statusChanged = true;
	}
}

/****************************************************************************************
 / * 	stop get/set
 ****************************************************************************************/
bool DriveStatus::isStop()
{
	return stop;
}

void DriveStatus::setStop(bool stop)
{
	if (this->stop != stop)
	{
		this->stop = stop;
		statusChanged = true;
	}
}

/****************************************************************************************
 / * 	teach get/set
 /****************************************************************************************/
bool DriveStatus::isTeach()
{
	return teach;
}

void DriveStatus::setTeach(bool teach)
{
	if (this->teach != teach)
	{
		this->teach = teach;
		statusChanged = true;
	}
}

/****************************************************************************************
 / * 	write config get/set
 ****************************************************************************************/
DriveStatus::_ERROR DriveStatus::getError()
{
	return this->error;
}

void DriveStatus::setError(_ERROR error)
{
	if (this->error != error)
	{
		this->error = error;
		statusChanged = true;
	}
}

void DriveStatus::ResetError(_ERROR error) {

	if (this->error == error) {
		this->error = E_NO_ERROR;
	}

}


/*******************************************************************
 * Current settings
 ******************************************************************/

uint16_t DriveStatus::getCurrent() const
{
	if (zeroCurrentValue > current)
	{
		return (zeroCurrentValue - current) * ADC_2_CURRENT;
	}
	else
	{
		return (current - zeroCurrentValue) * ADC_2_CURRENT;
	}
}

void DriveStatus::setCurrent(uint16_t current)
{
	this->current = current;
}

/*******************************************************************
 * 0 Current settings
 ******************************************************************/

uint16_t DriveStatus::getZCurrent() const
{
	return zeroCurrentValue;
}

void DriveStatus::setZCurrent(uint16_t zeroCurrentValueADC)
{
	this->zeroCurrentValue = zeroCurrentValue;
}

/*******************************************************************
 * Voltage settings
 ******************************************************************/

uint16_t DriveStatus::getVoltage() const
{
	return voltage * ADC_2_VOLTAGE;
}

void DriveStatus::setVoltage(uint16_t voltageADC)
{
	this->voltage = voltageADC;
}

/*******************************************************************
 * Position settings
 ******************************************************************/

int32_t DriveStatus::getPosition() const
{
	return position;
}

void DriveStatus::setPosition(int32_t position)
{
	this->position = position;
}

bool DriveStatus::isInPos() const
{
	return this->inPos;
}

void DriveStatus::setInPos(bool flag)
{
	this->inPos = flag;
}

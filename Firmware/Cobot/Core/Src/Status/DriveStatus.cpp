/*
 * DriveStatus.cpp
 *
 *  Created on: Nov 24, 2022
 *      Author: marce
 */

#include "DriveStatus.h"

DriveStatus::DriveStatus()
{
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
	this->close = close;
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
	this->open = open;
}

/****************************************************************************************
 / * 	disable get/set
 ****************************************************************************************/
bool DriveStatus::isDisable()
{
	return disable;
}

void DriveStatus::setDisable(bool disable)
{
	this->disable = disable;
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
	this->enable = enable;
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
	this->reset = reset;
}

/****************************************************************************************
 / * 	stop get/set
 /****************************************************************************************/
bool DriveStatus::isStop()
{
	return stop;
}

void DriveStatus::setStop(bool stop)
{
	this->stop = stop;
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
	this->teach = teach;
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
	this->error = error;
}

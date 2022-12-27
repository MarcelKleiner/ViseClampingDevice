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
 / * 	disable get/set
 ****************************************************************************************/
bool DriveStatus::isDisable()
{
	return disable;
}

void DriveStatus::setDisable(bool disable)
{
	if (this->disable != disable)
	{
		this->disable = disable;
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
 /****************************************************************************************/
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
	if (this->error = error)
	{
		statusChanged = true;
	}
}

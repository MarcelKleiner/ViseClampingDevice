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
bool DriveStatus::IsClose() const
{
	return close;
}

void DriveStatus::SetClose(bool close)
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
bool DriveStatus::IsOpen() const
{
	return open;
}

void DriveStatus::SetOpen(bool open)
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
bool DriveStatus::IsDisable() const
{
	return disable;
}

void DriveStatus::SetDisable(bool disable)
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
bool DriveStatus::IsEnable() const
{
	return enable;
}

void DriveStatus::SetEnable(bool enable)
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
bool DriveStatus::IsReset() const
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
bool DriveStatus::IsStop() const
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
bool DriveStatus::IsTeach() const
{
	return teach;
}

void DriveStatus::SetTeach(bool teach)
{
	if (this->teach != teach)
	{
		this->teach = teach;
		statusChanged = true;
	}
}

/****************************************************************************************
 / * 	self reset
 ****************************************************************************************/

void DriveStatus::SetSelfReset() 
{
	selfReset = true;
}

void DriveStatus::ResetSelfReset() 
{
	selfReset = false;
}

bool DriveStatus::IsSelfReset() const 
{
	return this->selfReset;
}


/****************************************************************************************
 / * 	write config get/set
 ****************************************************************************************/
DriveStatus::_ERROR DriveStatus::GetError() const
{
	return this->error;
}

void DriveStatus::ResetError() {
	this->error = _ERROR::E_NO_ERROR;
}

void DriveStatus::ResetError(_ERROR error) {
	if (this->error == error) {
		this->error = _ERROR::E_NO_ERROR;
	}
}

void DriveStatus::setError(_ERROR error)
{
	if (this->error != error)
	{
		this->error = error;
		statusChanged = true;
	}
}

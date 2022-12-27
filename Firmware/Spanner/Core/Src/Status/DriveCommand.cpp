/*
 * DriveCommand.cpp
 *
 *  Created on: 11.12.2022
 *      Author: marce
 */

#include "DriveCommand.h"

DriveCommand::DriveCommand()
{
}

/****************************************************************************************
 / * 	close get/set (read reset)
 ****************************************************************************************/
bool DriveCommand::isClose()
{
	return close;
}

void DriveCommand::setClose(bool close)
{
	this->close = close;
}

/****************************************************************************************
 / * 	open get/set (read reset)
 ****************************************************************************************/
bool DriveCommand::isOpen()
{
	return open;
}

void DriveCommand::setOpen(bool open)
{
	this->open = open;
}

/****************************************************************************************
 / * 	disable get/set (read reset)
 ****************************************************************************************/
bool DriveCommand::isDisable()
{
	return disable;
}

void DriveCommand::setDisable(bool disable)
{
	this->disable = disable;
}

/****************************************************************************************
 / * 	enable get/set (read reset)
 ****************************************************************************************/
bool DriveCommand::isEnable()
{
	return enable;
}

void DriveCommand::setEnable(bool enable)
{
	this->enable = enable;
}

/****************************************************************************************
 / * 	reset get/set (read reset)
 ****************************************************************************************/
bool DriveCommand::isReset()
{
	return reset;
}

void DriveCommand::setReset(bool reset)
{
	this->reset = reset;
}

/****************************************************************************************
 * 	stop get/set (read reset)
 ****************************************************************************************/
bool DriveCommand::isStop()
{
	return stop;
}

void DriveCommand::setStop(bool stop)
{
	this->stop = stop;
}

/****************************************************************************************
 * 	teach get/set (read reset)
 ****************************************************************************************/
bool DriveCommand::isTeach()
{
	return teach;
}

void DriveCommand::setTeach(bool teach)
{
	if (this->teach != teach)
	{
		this->teach = teach;
	}

}

/****************************************************************************************
 * 	write config get/set (read reset)
 ****************************************************************************************/
bool DriveCommand::isWriteConfig()
{
	bool writeConfigTemp = writeConfig;
	writeConfig = false;
	return writeConfigTemp;
}

void DriveCommand::setWriteConfig(bool status)
{
	writeConfig = status;
}

/****************************************************************************************
 * 	has commands changed get/set (read reset)
 ****************************************************************************************/

bool DriveCommand::isCommandChanged() const
{
	return (commandChangeReg != 0);
}

uint8_t DriveCommand::getCommandChangedReg() const
{
	return this->commandChangeReg;
}

void DriveCommand::ResetCommandChanged(uint8_t bit)
{
	this->commandChangeReg &= ~bit;
}


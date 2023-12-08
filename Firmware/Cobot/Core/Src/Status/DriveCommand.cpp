/*
 * DriveCommand.cpp
 *
 *  Created on: 11.12.2022
 *      Author: marce
 */

#include "../AppMain/Defines.h"
#include "DriveCommand.h"

DriveCommand::DriveCommand()
{
}

/****************************************************************************************
 / * 	close get/set (read reset)
 ****************************************************************************************/
bool DriveCommand::isClose()
{
	bool closeTemp = close;
	close = false;
	return closeTemp;
}

void DriveCommand::setClose(bool close)
{
	this->close = close;
	 commandChangeReg |= CLOSE_CHANGE;
}

/****************************************************************************************
 / * 	open get/set (read reset)
 ****************************************************************************************/
bool DriveCommand::isOpen()
{
	bool openTemp = open;
	open = false;
	return openTemp;
}

void DriveCommand::setOpen(bool open)
{
	this->open = open;
	 commandChangeReg |= OPEN_CHANGE;
}

/****************************************************************************************
 / * 	disable get/set (read reset)
 ****************************************************************************************/
bool DriveCommand::isDisable()
{
	bool disableTemp = disable;
	disable = false;
	return disableTemp;
}

void DriveCommand::setDisable(bool disable)
{
	this->disable = disable;
	 commandChangeReg |= DISABLE_CHANGE;
}

/****************************************************************************************
 / * 	enable get/set (read reset)
 ****************************************************************************************/
bool DriveCommand::isEnable()
{
	bool enableTemp = enable;
	enable = false;
	return enableTemp;
}

void DriveCommand::setEnable(bool enable)
{
	this->enable = enable;
	 commandChangeReg |= ENABLE_CHANGE;
}

/****************************************************************************************
 / * 	reset get/set (read reset)
 ****************************************************************************************/
bool DriveCommand::isReset()
{
	bool resetTemp = reset;
	reset = false;
	return resetTemp;
}

void DriveCommand::setReset(bool reset)
{
	this->reset = reset;
	 commandChangeReg |= RESET_CHANGE;
}

/****************************************************************************************
 * 	stop get/set (read reset)
 ****************************************************************************************/
bool DriveCommand::isStop()
{
	bool stopTemp = stop;
	stop = false;
	return stopTemp;
}

void DriveCommand::setStop(bool stop)
{
	this->stop = stop;
	 commandChangeReg |= STOP_CHANGE;
}

/****************************************************************************************
 * 	teach get/set (read reset)
 ****************************************************************************************/
bool DriveCommand::isTeach()
{
	bool teachTemp = teach;
	teach = false;
	return teachTemp;
}

void DriveCommand::setTeach(bool teach)
{
	if (this->teach != teach)
	{
		this->teach = teach;
		 commandChangeReg |= TEACH_CHANGE;
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


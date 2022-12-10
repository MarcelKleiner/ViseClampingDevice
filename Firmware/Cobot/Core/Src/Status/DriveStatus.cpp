/*
 * DriveStatus.cpp
 *
 *  Created on: Nov 24, 2022
 *      Author: marce
 */

#include "DriveStatus.h"

DriveStatus::DriveStatus() {
}

/****************************************************************************************
 / * 	close get/set (read reset)
 ****************************************************************************************/
bool DriveStatus::isClose() {
	bool closeTemp = close;
	close = false;
	return closeTemp;
}

void DriveStatus::setClose(bool close) {
	this->close = close;
}

/****************************************************************************************
 / * 	open get/set (read reset)
 ****************************************************************************************/
bool DriveStatus::isOpen() {
	bool openTemp = open;
	open = false;
	return openTemp;
}

void DriveStatus::setOpen(bool open) {
	this->open = open;
}

/****************************************************************************************
 / * 	disable get/set (read reset)
 ****************************************************************************************/
bool DriveStatus::isDisable() {
	bool disableTemp = disable;
	disable = false;
	return disableTemp;
}

void DriveStatus::setDisable(bool disable) {
	this->disable = disable;
}

/****************************************************************************************
 / * 	enable get/set (read reset)
 ****************************************************************************************/
bool DriveStatus::isEnable() {
	bool enableTemp = enable;
	enable = false;
	return enableTemp;
}

void DriveStatus::setEnable(bool enable) {
	this->enable = enable;
}

/****************************************************************************************
 / * 	reset get/set (read reset)
 ****************************************************************************************/
bool DriveStatus::isReset() {
	bool resetTemp = reset;
	reset = false;
	return resetTemp;
}

void DriveStatus::setReset(bool reset) {
	this->reset = reset;
}

/****************************************************************************************
 / * 	stop get/set (read reset)
 /****************************************************************************************/
bool DriveStatus::isStop() {
	bool stopTemp = stop;
	stop = false;
	return stopTemp;
}

void DriveStatus::setStop(bool stop) {
	this->stop = stop;
}

/****************************************************************************************
 / * 	teach get/set (read reset)
 /****************************************************************************************/
bool DriveStatus::isTeach() {
	bool teachTemp = teach;
	teach = false;
	return teachTemp;
}

void DriveStatus::setTeach(bool teach) {
	this->teach = teach;
}

/****************************************************************************************
 / * 	write config get/set (read reset)
<<<<<<< HEAD
 /****************************************************************************************/
bool DriveStatus::isWriteConfig()
{
	bool writeConfigTemp = writeConfig;
	writeConfig = false;
	return writeConfigTemp;
=======
 ****************************************************************************************/
bool DriveStatus::isWriteConfig() {
	return writeConfig;
>>>>>>> origin/main
}

void DriveStatus::setWriteConfig(bool writeConfig) {
	this->writeConfig = writeConfig;
}

/****************************************************************************************
 / * 	write config get/set (read reset)
 ****************************************************************************************/
_ERROR DriveStatus::getError() {
	return this->error;
}

void DriveStatus::setError(_ERROR error) {
	error
}

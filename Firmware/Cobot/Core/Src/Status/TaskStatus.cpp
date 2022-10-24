/*
 * DriveStatus.cpp
 *
 *  Created on: Oct 20, 2022
 *      Author: marcel
 */
#include "TaskStatus.h"



bool TaskHandler::isDigitalInTask() const {
	return DigitalInTask;
}

void TaskHandler::setDigitalInTask(bool digitalInTask) {
	DigitalInTask = digitalInTask;
}




bool TaskHandler::isDigitalOutTask() const {
	return DigitalOutTask;
}

void TaskHandler::setDigitalOutTask(bool digitalOutTask) {
	DigitalOutTask = digitalOutTask;
}





bool TaskHandler::isLedTask() const{
	return LEDTask;
}

void TaskHandler::setLedTask(bool ledTask) {
	LEDTask = ledTask;
}





bool TaskHandler::isRfmTask() const {
	return RFMTask;
}

void TaskHandler::setRfmTask(bool rfmTask) {
	RFMTask = rfmTask;
}



bool TaskHandler::isErrorTask() const {
	return ErrorTask;
}

void TaskHandler::setErrorTask(bool errorTask) {
	ErrorTask = errorTask;
}

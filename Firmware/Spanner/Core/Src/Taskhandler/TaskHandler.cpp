/*
 * TaskStatus.cpp
 *
 *  Created on: Oct 23, 2022
 *      Author: marce
 */

#include "TaskHandler.h"
#include "main.h"


//update tasks, should be called every 1ms
void TaskHandler::UpdateTasks() {


	//15ms
	if(counter % 15 == 0){
		driveTask = true;
	}

	//100ms
	if(counter % 100 == 0){
		errorTask = true;
	}

	//250ms
	if(counter % 250 == 0){
		comTask = true;
	}

	if(counter % 500 == 0){
		ledTask = true;
	}

	//increment counter
	if(counter > 2999){
		counter = 1;
	}else{
		counter++;
	}

}



bool TaskHandler::isComTask()  {
	bool comTaskTemp = (comTask & comTaskEnable);
	comTask = false;
	return comTaskTemp;
}

bool TaskHandler::isDriveTask()  {
	bool driveTaskTemp = (driveTask & driveTaskEnable);
	driveTask = false;
	return driveTaskTemp;
}

bool TaskHandler::isErrorTask()  {
	bool errorTaskTemp = (errorTask & errorTaskEnable);
	errorTask = false;
	return errorTaskTemp;
}


bool TaskHandler::isLEDTask(){
	bool ledTaskTemp = (ledTask & ledTaskEnable);
	ledTask = false;
	return ledTaskTemp;
}





void TaskHandler::setComTaskEnable(bool comTaskEnable ) {
	this->comTaskEnable = comTaskEnable;
}


void TaskHandler::setDriveTaskEnable(bool driveTaskEnable ) {
	this->driveTaskEnable = driveTaskEnable;
}


void TaskHandler::setErrorTaskEnable(bool errorTaskEnable ) {
	this->errorTaskEnable = errorTaskEnable;
}



void TaskHandler::setLEDTaskEnable(bool ledTaskEnable){
	this->ledTaskEnable = ledTaskEnable;
}

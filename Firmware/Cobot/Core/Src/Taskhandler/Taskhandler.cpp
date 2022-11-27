/*
 * Taskhandler.cpp
 *
 *  Created on: 30.10.2022
 *      Author: marce
 */


/*
 * TaskStatus.cpp
 *
 *  Created on: Oct 23, 2022
 *      Author: marce
 */

#include "TaskHandler.h"
#include "gpio.h"

//update tasks, should be called every 1ms
void TaskHandler::UpdateTasks() {

	//1ms

	//2ms
	if(counter % 2 == 0){
		adcUpdateTask = true;
	}


	//15ms
	if(counter % 15 == 0){
		ioUpdateTask = true;
	}


	//50ms
	if(counter % 50 == 0){

	}



	//100ms
	if(counter % 100 == 0){
		errorTask = true;
	}


	//500ms
	if(counter % 500 == 0){
		ledUpdateTask = true;
		comTask = true;
	}


	//1000ms
	if(counter % 1000 == 0){

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


bool TaskHandler::isErrorTask()  {
	bool errorTaskTemp = (errorTask & errorTaskEnable);
	errorTask = false;
	return errorTaskTemp;
}

bool TaskHandler::isIoUpdateTask()  {
	bool ioUpdateTaskTemp = (ioUpdateTask & ioUpdateTaskEnable);
	ioUpdateTask = false;
	return ioUpdateTaskTemp;
}


bool TaskHandler::isADCUpdateTask() {
	bool adcUpdateTaskTemp = (adcUpdateTask & adcUpdateTaskEnable);
	adcUpdateTask = false;
	return adcUpdateTaskTemp;
}


bool TaskHandler::isLEDUpdateTask(){
	bool ledUpdateTaskTemp = (ledUpdateTask & ledUpdateTaskEnable);
	ledUpdateTask = false;
	return ledUpdateTaskTemp;
}


void TaskHandler::setAdcUpdateTaskEnable(bool adcUpdateTaskEnable ) {
	this->adcUpdateTaskEnable = adcUpdateTaskEnable;
}


void TaskHandler::setComTaskEnable(bool comTaskEnable ) {
	this->comTaskEnable = comTaskEnable;
}


void TaskHandler::setErrorTaskEnable(bool errorTaskEnable ) {
	this->errorTaskEnable = errorTaskEnable;
}


void TaskHandler::setIoUpdateTaskEnable(bool ioUpdateTaskEnable ) {
	this->ioUpdateTaskEnable = ioUpdateTaskEnable;
}

void TaskHandler::setLEDUpdateTaskEnable(bool ledUpdateTaskEnable){
	this->ledUpdateTaskEnable = ledUpdateTaskEnable;
}


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
#include "../AppMain/Defines.h"

//update tasks, should be called every 1ms
void TaskHandler::UpdateTasks() {

	//1ms

	//2ms
	if(counter % ADC_UPDATE_TIME == 0){
		adcUpdateTask = true;
	}


	//15ms
	if(counter % IO_UPDATE_TIME == 0){
		ioUpdateTask = true;
	}


	//50ms
	if(counter % 50 == 0){

	}



	//100ms
	if(counter % ERROR_UPDATE_TIME == 0){
		errorTask = true;
	}

	if(counter % COM_UPDATE_TIME == 0){
		comTask = true;
	}


	//500ms
	if(counter % LED_UPDATE_TIME == 0){
		ledUpdateTask = true;
	}


	//1000ms
	if(counter % SAVE_UPDATE_TIME == 0){
		saveTask = true;
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

bool TaskHandler::isSaveTask(){
	bool saveTaskTemp = (saveTask & saveTaskEnable);
	saveTask = false;
	return saveTaskTemp;
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

void TaskHandler::setSaveTaskEnable(bool saveTaskEnable){
	this->saveTaskEnable = saveTaskEnable;
}


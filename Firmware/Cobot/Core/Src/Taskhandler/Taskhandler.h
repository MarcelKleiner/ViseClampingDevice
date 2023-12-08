/*
 * Taskhandler.h
 *
 *  Created on: 30.10.2022
 *      Author: marce
 */

#ifndef SRC_TASKHANDLER_TASKHANDLER_H_
#define SRC_TASKHANDLER_TASKHANDLER_H_


#include "../AppMain/Defines.h"
#include "stdint.h"


class TaskHandler{



public:

	void UpdateTasks();

	bool isComTask();
	bool isComTaskRx();
	bool isSaveTask();
	bool isErrorTask();
	bool isIoUpdateTask() ;
	bool IsADCUpdateTask();
	bool IsResetUpdateTask();
	bool IsLEDUpdateTask();



	void setAdcUpdateTaskEnable(bool adcUpdateTaskEnable = true);
	void setComTaskEnable(bool comTaskEnable = true);
	void setErrorTaskEnable(bool errorTaskEnable = true);
	void setIoUpdateTaskEnable(bool ioUpdateTaskEnable = true);
	void setLEDUpdateTaskEnable(bool ledUpdateTaskEnable = true);
	void setSaveTaskEnable(bool ledUpdateTaskEnable = true);

private:


	volatile bool errorTask = false;
	volatile bool comTask = false;
	volatile bool comTaskRx = false;
	volatile bool ioUpdateTask = false;
	volatile bool adcUpdateTask = false;
	volatile bool ledUpdateTask = false;
	volatile bool saveTask = false;
	volatile bool resetTask = false;


	volatile bool errorTaskEnable = true;
	volatile bool comTaskEnable = true;
	volatile bool ioUpdateTaskEnable = true;
	volatile bool adcUpdateTaskEnable = true;
	volatile bool ledUpdateTaskEnable = true;
	volatile bool saveTaskEnable = true;
	uint16_t counter;
};



#endif /* SRC_TASKHANDLER_TASKHANDLER_H_ */

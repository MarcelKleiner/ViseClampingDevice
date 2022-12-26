/*
 * Taskhandler.h
 *
 *  Created on: 30.10.2022
 *      Author: marce
 */

#ifndef SRC_TASKHANDLER_TASKHANDLER_H_
#define SRC_TASKHANDLER_TASKHANDLER_H_


#include "stdint.h"


class TaskHandler{



public:

	void UpdateTasks();

	bool isComTask();
	bool isSaveTask();
	bool isErrorTask();
	bool isIoUpdateTask() ;
	bool isADCUpdateTask();
	bool isAdcUpdateTask();
	bool isLEDUpdateTask();



	bool isAdcUpdateTaskEnable() const;
	void setAdcUpdateTaskEnable(bool adcUpdateTaskEnable = true);

	bool isComTaskEnable() const;
	void setComTaskEnable(bool comTaskEnable = true);

	bool isErrorTaskEnable() const;
	void setErrorTaskEnable(bool errorTaskEnable = true);

	bool isIoUpdateTaskEnable() const;
	void setIoUpdateTaskEnable(bool ioUpdateTaskEnable = true);

	bool isLedUpdateTaskEnable() const;
	void setLEDUpdateTaskEnable(bool ledUpdateTaskEnable = true);

	bool isSaveTaskEnable() const;
	void setSaveTaskEnable(bool ledUpdateTaskEnable = true);

private:


	volatile bool errorTask = false;
	volatile bool comTask = false;
	volatile bool ioUpdateTask = false;
	volatile bool adcUpdateTask = false;
	volatile bool ledUpdateTask = false;
	volatile bool saveTask = false;


	volatile bool errorTaskEnable = true;
	volatile bool comTaskEnable = true;
	volatile bool ioUpdateTaskEnable = true;
	volatile bool adcUpdateTaskEnable = true;
	volatile bool ledUpdateTaskEnable = true;
	volatile bool saveTaskEnable = true;
	uint16_t counter;
};



#endif /* SRC_TASKHANDLER_TASKHANDLER_H_ */

/*
 * TaskStatus.h
 *
 *  Created on: Oct 23, 2022
 *      Author: marce
 */

#ifndef SRC_STATUS_TASKHANDLER_H_
#define SRC_STATUS_TASKHANDLER_H_

#include "stdint.h"


class TaskHandler{



public:

	void UpdateTasks();

	bool isComTask();
	bool isDriveTask();
	bool isErrorTask();
	bool isIoUpdateTask() ;
	bool isADCUpdateTask();
	bool isAdcUpdateTask();
	bool isLEDTask();

	bool isAdcUpdateTaskEnable() const;
	void setAdcUpdateTaskEnable(bool adcUpdateTaskEnable = true);

	bool isComTaskEnable() const;
	void setComTaskEnable(bool comTaskEnable = true);

	bool isDriveTaskEnable() const;
	void setDriveTaskEnable(bool driveTaskEnable = true);

	bool isErrorTaskEnable() const;
	void setErrorTaskEnable(bool errorTaskEnable = true);

	bool isIoUpdateTaskEnable() const;
	void setIoUpdateTaskEnable(bool ioUpdateTaskEnable = true);

	bool isLEDTaskEnable() const;
	void setLEDTaskEnable(bool ledTaskEnable = true);

private:


	bool errorTask = false;
	bool comTask = false;
	bool driveTask = false;
	bool ioUpdateTask = false;
	bool adcUpdateTask = false;
	bool ledTask = false;

	bool errorTaskEnable = true;
	bool comTaskEnable = true;
	bool driveTaskEnable = true;
	bool ioUpdateTaskEnable = true;
	bool adcUpdateTaskEnable = true;
	bool ledTaskEnable = true;

	uint16_t counter;

};



#endif /* SRC_STATUS_TASKHANDLER_H_ */

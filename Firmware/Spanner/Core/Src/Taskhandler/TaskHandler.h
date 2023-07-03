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
	bool isLEDTask();


	bool isComTaskEnable() const;
	void setComTaskEnable(bool comTaskEnable = true);

	bool isDriveTaskEnable() const;
	void setDriveTaskEnable(bool driveTaskEnable = true);

	bool isErrorTaskEnable() const;
	void setErrorTaskEnable(bool errorTaskEnable = true);

	bool isLEDTaskEnable() const;
	void setLEDTaskEnable(bool ledTaskEnable = true);

private:


	bool errorTask = false;
	bool comTask = false;
	bool driveTask = false;
	bool ledTask = false;

	bool errorTaskEnable = true;
	bool comTaskEnable = true;
	bool driveTaskEnable = true;
	bool ledTaskEnable = true;

	uint16_t counter;

};



#endif /* SRC_STATUS_TASKHANDLER_H_ */

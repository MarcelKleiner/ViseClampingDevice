/*
 * DriveStatus.h
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#ifndef SRC_STATUS_TASKSTATUS_H_
#define SRC_STATUS_TASKSTATUS_H_

class TaskHandler{

public:
	bool isDigitalInTask() const;
	void setDigitalInTask(bool digitalInTask);

	bool isDigitalOutTask() const;
	void setDigitalOutTask(bool digitalOutTask);

	bool isLedTask() const;
	void setLedTask(bool ledTask);

	bool isRfmTask() const;
	void setRfmTask(bool rfmTask);

	bool isErrorTask() const;
	void setErrorTask(bool errorTask);

private:

	bool DigitalInTask;
	bool DigitalOutTask;
	bool RFMTask;
	bool LEDTask;
	bool ErrorTask;




};



#endif /* SRC_STATUS_DRIVESTATUS_H_ */

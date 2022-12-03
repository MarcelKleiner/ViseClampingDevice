/*
 * DriveStatus.h
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#ifndef SRC_STATUS_DRIVESTATUS_H_
#define SRC_STATUS_DRIVESTATUS_H_

class DriveStatus
{

	public:

		DriveStatus();

		enum _ERROR{
			E_FLASH_ERROR,
		};


		bool isClose();
		void setClose(bool close);

		bool isOpen();
		void setOpen(bool open);

		bool isDisable();
		void setDisable(bool disable);

		bool isEnable();
		void setEnable(bool enable);

		bool isReset();
		void setReset(bool reset);

		bool isStop();
		void setStop(bool stop);

		bool isTeach();
		void setTeach(bool teach);

		bool isWriteConfig();
		void setWriteConfig(bool writeConfig);

		_ERROR getError();
		void setError(_ERROR error);

	private:



		_ERROR error;
		//reset by read
		bool close;
		bool open;
		bool teach;
		bool reset;
		bool enable;
		bool stop;
		bool disable;

		bool writeConfig;

		uint8_t error;
};

#endif /* SRC_STATUS_DRIVESTATUS_H_ */

/*
 * DriveCommand.h
 *
 *  Created on: 11.12.2022
 *      Author: marce
 */

#ifndef SRC_STATUS_DRIVECOMMAND_H_
#define SRC_STATUS_DRIVECOMMAND_H_

class DriveCommand
{
	public:

		DriveCommand();

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

	private:

		bool close = false;
		bool open = false;
		bool teach = false;
		bool reset = false;
		bool enable = false;
		bool stop = false;
		bool disable = false;

		bool writeConfig = false;
};



#endif /* SRC_STATUS_DRIVECOMMAND_H_ */

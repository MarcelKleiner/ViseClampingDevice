/*
 * DriveStatus.h
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#ifndef SRC_STATUS_DRIVESTATUS_H_
#define SRC_STATUS_DRIVESTATUS_H_

#include "main.h"

class DriveStatus
{

	public:

		DriveStatus();

		enum _ERROR {
			E_NO_ERROR = 0x00,
			E_FLASH_ERROR = 0x01,
			E_COM_ERROR = 0x02,
			E_USB_ERROR = 0x03,
			E_UNKOWN_COMMAND_OR_ADDR_ERROR = 0x04,
			E_CONNECTION_LOST_ERROR = 0x05
		};


		bool IsClose() const;
		void SetClose(bool close);

		bool IsOpen() const;
		void SetOpen(bool open);

		bool IsDisable() const;
		void SetDisable(bool disable);

		bool IsEnable() const;
		void SetEnable(bool enable);

		bool IsReset() const;
		void setReset(bool reset);

		bool IsStop() const;
		void setStop(bool stop);

		bool IsTeach() const;
		void SetTeach(bool teach);

		bool isWriteConfig();
		void setWriteConfig(bool writeConfig);

		_ERROR GetError() const;
		void setError(_ERROR error);
		void ResetError(_ERROR error);
		void ResetError();


		bool isStatusChanged();

		void SetSelfReset();
		void ResetSelfReset();
		bool IsSelfReset() const;

	private:

		_ERROR error;
		bool close;
		bool open;
		bool teach;
		bool reset;
		bool enable;
		bool stop;
		bool disable;

		bool statusChanged = false;

		bool selfReset = false;
};

#endif /* SRC_STATUS_DRIVESTATUS_H_ */

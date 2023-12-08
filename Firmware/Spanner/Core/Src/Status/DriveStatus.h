/*
 * DriveStatus.h
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#ifndef SRC_STATUS_DRIVESTATUS_H_
#define SRC_STATUS_DRIVESTATUS_H_

#include "stdint.h"

#define ADC_2_VOLTAGE		8
#define ADC_2_CURRENT		2


class DriveStatus
{

	public:

		enum _ERROR
		{
			E_NO_ERROR = 0x00,
			E_FLASH_ERROR = 0x01,
			E_COM_ERROR = 0x02,
			E_USB_ERROR = 0x03,
			E_UNKOWN_COMMAND_OR_ADDR_ERROR = 0x04,
			E_CONNECTION_LOST_ERROR = 0x05,
			E_CRC_ERROR = 0x06,
			E_UNDERVOLTAGE_ERROR= 0x07,
			E_UNDERVOLTAGE_WARNING = 0x08,
			E_OVERCURRENT_WARNING= 0x09,
			E_OVERCURRENT_ERROR= 0x0A,
			E_ENCODER_ERROR = 0x0B
		};

		DriveStatus();

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
		void ResetError(_ERROR error);

		uint16_t getCurrent() const;
		void setCurrent(uint16_t current);

		int32_t getPosition() const;
		void setPosition(int32_t position);

		bool isInPos() const;
		void setInPos(bool flag);

		uint16_t getZCurrent() const;
		void setZCurrent(uint16_t zeroCurrentValue);

		uint16_t getVoltage() const;
		void setVoltage(uint16_t voltage);

		uint8_t getStatus() const;

		bool isStatusChanged();

	private:

		_ERROR error;
		bool close;
		bool open;
		bool teach;
		bool reset;
		bool enable;
		bool stop;
		bool disable;
		uint16_t current;
		uint16_t zeroCurrentValue;
		uint16_t voltage;
		int32_t position;

		bool inPos = false;

		uint16_t autoShutdownCounter;


		bool statusChanged = false;
};

#endif /* SRC_STATUS_DRIVESTATUS_H_ */

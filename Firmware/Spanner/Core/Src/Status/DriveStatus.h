/*
 * DriveStatus.h
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#ifndef SRC_STATUS_DRIVESTATUS_H_
#define SRC_STATUS_DRIVESTATUS_H_

#include "stdint.h"

#define ADC_2_VOLTAGE		2
#define ADC_2_CURRENT		2


class DriveStatus
{

	public:

		enum _ERROR
		{
			E_NO_ERROR = 0x0000,
			E_FLASH_ERROR = 0x0001,
			E_COM_ERROR = 0x0002,
			E_UNDERVOLTAGE_ERROR= 0x004,
			E_UNDERVOLTAGE_WARNING = 0x0008,
			E_OVERCURRENT_WARNING= 0x0010,
			E_OVERCURRENT_ERROR= 0x020,
			E_CRC_ERROR = 0x040,
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

		uint16_t getCurrent() const;
		void setCurrent(uint16_t current);

		uint16_t getPosition() const;
		void setPosition(uint16_t position);

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
		uint16_t position;

		bool inPos = false;

		uint16_t autoShutdownCounter;


		bool statusChanged = false;
};

#endif /* SRC_STATUS_DRIVESTATUS_H_ */

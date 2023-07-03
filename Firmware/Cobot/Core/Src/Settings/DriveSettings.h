/*
 * DriveSettings.h
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#ifndef SRC_SETTINGS_DRIVESETTINGS_H_
#define SRC_SETTINGS_DRIVESETTINGS_H_

#include "stdint.h"
#include "main.h"

class DriveSettings{

public:
		uint16_t getClampingSpeed() const;
		void setClampingSpeed(uint16_t clampingSpeed);

		uint16_t getClampingTorque() const;
		void setClampingTorque(uint16_t clampingTorque);

		uint16_t getInPosDiff() const;
		void setInPosDiff(uint16_t inPosDiff = 20);

		uint16_t getOpeningDistance() const;
		void setOpeningDistance(uint16_t openingDistance = 100);

		uint16_t getOverCurrentTimeThreshold() const;
		void setOverCurrentTimeThreshold(uint16_t overCurrentTimeThreshold = 1000);

		uint16_t getOverCurrentWarning() const;
		void setOverCurrentWarning(uint16_t overCurrentWarning = 50);

		uint16_t getSelfShutdownDelay() const;
		void setSelfShutdownDelay(uint16_t selfShutdownDelay = 600);

		uint16_t getTeachSpeed() const;
		void setTeachSpeed(uint16_t teachSpeed = 0);

		uint16_t getTeachTroque() const;
		void setTeachTroque(uint16_t teachTroque = 0);

		uint16_t getUnderVoltageError() const;
		void setUnderVoltageError(uint16_t underVoltageError = 12000);

		uint16_t getUnderVoltageWarning() const;
		void setUnderVoltageWarning(uint16_t underVoltageWarning = 14000);

		uint16_t getOverCurrentError() const;
		void setOverCurrentError(uint16_t overCurrentError = 100);

		uint8_t getDeviceAddress();
		void setDeviceAddress(uint8_t deviceAddress);

		bool isSaveSettings();
		void setSaveSettings(bool saveSettings);
		
		bool isSettingsChanged();
		uint16_t getSettingsChangedReg() const;
		void ResetSettingsChanged(uint16_t bit);

private:

		uint8_t deviceAddress = 0x1F;

		uint16_t teachTroque = 0;
		uint16_t clampingTorque = 0;					//torque in nm

		uint16_t teachSpeed = 0;
		uint16_t clampingSpeed = 0;

		uint16_t selfShutdownDelay = 600;	//delay in seconds
		uint16_t inPosDiff = 20;			//position difference in 1/10mm
		uint16_t openingDistance = 100;		//vice opening width in 1/10mm

		uint16_t underVoltageWarning = 14000;	//in mV
		uint16_t underVoltageError = 12000;		//self shutdown undervoltage threshold

		uint16_t overCurrentWarning = 50;		//in A
		uint16_t overCurrentError = 100;
		uint16_t overCurrentTimeThreshold = 1000; 	//delay for overcurrent shutdown in ms

		bool saveSettings = false;

		uint16_t settingsChangedReg = 0;
};



#endif /* SRC_SETTINGS_DRIVESETTINGS_H_ */

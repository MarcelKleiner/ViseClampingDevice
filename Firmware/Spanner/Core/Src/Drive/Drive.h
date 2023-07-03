/*
 * Drive.h
 *
 *  Created on: 23.10.2022
 *      Author: marce
 */

#ifndef SRC_DRIVE_DRIVE_H_
#define SRC_DRIVE_DRIVE_H_

#include "stdint.h"
#include "../Settings/DriveSettings.h"
#include "../Status/DriveStatus.h"
#include "../Status/DriveCommand.h"
#include "../Encoder/Encoder.h"
#include "../IO/LED.h"

class Drive
{

	public:

		Drive(DriveSettings *driveSettings, DriveStatus *driveStatus,
				DriveCommand *driveCommand, Encoder *encoder, LED *led);

		enum EDRIVE_MODE
		{
			TEACH_MODE, OP_MODE
		};

		enum TEACH_STATE
		{
			TEACH_MODE_ENTER,
			TEACH_RDY,
			DRIVE_OUT,
			DRIVE_IN,
			TEACH_END,
		};

		enum DIRECTION
		{
			IN, OUT, STOP,
		};

		void updateDrive();
		void Stop();
		EDRIVE_MODE getDriveMode();
		void setDriveMode(EDRIVE_MODE driveMode);

	private:

		DriveSettings *driveSettings;
		DriveStatus *driveStatus;
		DriveCommand *driveCommand;
		Encoder *encoder;
		LED *led;

		EDRIVE_MODE driveMode;

		TEACH_STATE currentState = TEACH_MODE_ENTER;
		TEACH_STATE nextState;

		bool isDriveStoped = false;

		bool torqueOutReached = false;

		void OpMode();
		void TeachMode();

		void Open();
		void Close();

		bool MoveDrive(DIRECTION direction, uint16_t torque, uint16_t speed);

};

#endif /* SRC_DRIVE_DRIVE_H_ */

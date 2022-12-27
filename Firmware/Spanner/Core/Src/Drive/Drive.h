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

class Drive
{

	public:

		Drive(DriveSettings *driveSettings, DriveStatus *driveStatus,
				DriveCommand *driveCommand, Encoder *encoder);

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
			CHECK_CLK,
			CLK_1,
			CLK_2,
		};

		enum DIRECTION
		{
			IN, OUT,
		};

		void updateDrive();
		void Reset();
		void Stop();
		EDRIVE_MODE getDriveMode() const;
		void setDriveMode(EDRIVE_MODE driveMode);

	private:

		DriveSettings *driveSettings;
		DriveStatus *driveStatus;
		DriveCommand *driveCommand;
		Encoder *encoder;

		EDRIVE_MODE driveMode;

		TEACH_STATE currentState = TEACH_MODE_ENTER;
		TEACH_STATE nextState;

		bool isDriveStoped = false;

		void OpMode();
		void TeachMode();

		void Open();
		void Close();

		void MoveDrive(DIRECTION direction, uint16_t torque, uint16_t speed);

};

#endif /* SRC_DRIVE_DRIVE_H_ */

/*
 * Drive.h
 *
 *  Created on: 23.10.2022
 *      Author: marce
 */

#ifndef SRC_DRIVE_DRIVE_H_
#define SRC_DRIVE_DRIVE_H_

#include "../Encoder/Encoder.h"
#include "../IO/LED.h"
#include "../Settings/DriveSettings.h"
#include "../Status/DriveCommand.h"
#include "../Status/DriveStatus.h"
#include "stdint.h"

class Drive
{

	public:

		Drive(DriveSettings *driveSettings, DriveStatus *driveStatus,
				DriveCommand *driveCommand, Encoder *encoder, LED *led);

		enum EDRIVE_MODE
		{
			TEACH_MODE, OP_MODE, STOP_MODE
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
		bool InternalDelay(uint16_t delay);
		bool DriveOutToInitializePosition();

	private:

		DriveSettings *driveSettings;
		DriveStatus *driveStatus;
		DriveCommand *driveCommand;
		Encoder *encoder;
		LED *led;

		EDRIVE_MODE driveMode;

		TEACH_STATE currentState = TEACH_MODE_ENTER;
		TEACH_STATE nextState;


		int32_t initialPosition = 0;
		int32_t currentPosition = 0;
		int32_t lastPosition = 0;
		uint8_t stateChangeDelay = 0;

		bool isDriveStoped = false;

		bool torqueOutReached = false;
		bool positionReached = false;

		bool isLocalDelayInitialized = false;

		void OpMode();
		void TeachMode();

		void Open();
		void Close();

		bool MoveDrive(DIRECTION direction, uint16_t torque, uint16_t speed, bool ignoreTorque);

		void ResetTeachState();
};

#endif /* SRC_DRIVE_DRIVE_H_ */

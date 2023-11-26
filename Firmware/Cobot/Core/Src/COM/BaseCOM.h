/*
 * BaseCOM.h
 *
 *  Created on: 25.12.2022
 *      Author: marce
 */

#ifndef SRC_COM_BASECOM_H_
#define SRC_COM_BASECOM_H_

#include "../Status/DriveStatus.h"
#include "../Status/DriveCommand.h"
#include "../Settings/DriveSettings.h"



class BaseCOM{


	protected:

		BaseCOM(DriveStatus *driveStatus, DriveSettings *driveSettings,
				DriveCommand *driveCommand);

		uint8_t *GetSettings(uint8_t addr = 0);
		uint8_t* GetStatus(uint8_t addr);
		uint8_t* GetCommand(uint8_t addr);

		void SetSettings(uint8_t* data);
		void SetStatus(uint8_t* data);
		void SetCommand(uint8_t* data);

		uint8_t CRC8(uint8_t *data, uint8_t length);

		DriveSettings *driveSettings;

<<<<<<< HEAD
	private:


=======
		DriveSettings *driveSettings;
>>>>>>> origin/main
		DriveStatus *driveStatus;
		DriveCommand *driveCommand;

	private:




		uint8_t data2send[7];
};



#endif /* SRC_COM_BASECOM_H_ */

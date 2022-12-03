/*
 * Flash.h
 *
 *  Created on: 27.11.2022
 *      Author: marce
 */

#ifndef SRC_FLASH_FLASH_H_
#define SRC_FLASH_FLASH_H_

#include "../Status/DriveStatus.h"
#include "../Settings/DriveSettings.h"
#include "stm32l4xx_hal.h"

#define FLASH_STAR_PAGE_ADDR		0x08030000
#define FLASH_SIZE					42


class Flash{

public:

	Flash(DriveSettings *driveSettings, DriveStatus *driveStatus);

	HAL_StatusTypeDef Flash::WriteFlash();
	void ReadFlash();


private:

	DriveSettings *driveSettings;
	DriveStatus *driveStatus;
	bool factoryResetFlag;


	uint16_t flashBuffer[FLASH_SIZE];

};

#endif /* SRC_FLASH_FLASH_H_ */

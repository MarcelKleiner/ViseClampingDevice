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

#define FLASH_PAGES 				((FLASH_SIZE) / FLASH_PAGE_SIZE)
#define UFLASH_DATA_SIZE			64

#define FLASH_STAR_PAGE_ADDR		0x0803F800
#define UFLASH_SIZE					20
#define UFLASH_PAGE					127
#define UFLASH_NPAGES				1



#define CLAMPING_SPEED_ADDR			0x00
#define CLAMPING_TORQUE_ADDR		0x01
#define TEACH_SPEED_ADDR			0x02
#define TEACH_TROQUE_ADDR			0x03
#define OVERCURRENT_ERROR_ADDR		0x04
#define OVERCURRENT_WARNING_ADDR	0x05
#define UNDERVOLTAGE_ERROR_ADDR		0x06
#define UNDERVOLTAGE_WARNING_ADDR	0x07
#define SELF_SHUTDOWN_DELAY_ADDR	0x08
#define IN_POS_DIFF_ADDR			0x09
#define OPENING_DISTANCE_ADDR		0x0A



//#if UFLASH_PAGE > 200
//#error "UFLASH_PAGE cannot be larger than the maximum number of flash pages"
//#endif
//
//#if (FLASH_PAGE_SIZE / UFLASH_DATA_SIZE) > UFLASH_SIZE
//	#error "UFLASH_SIZE is too large"
//#endif



class Flash
{

public:

	Flash(DriveSettings *driveSettings, DriveStatus *driveStatus);

	HAL_StatusTypeDef WriteFlash();
	void ReadFlash();
	void SaveFlash();

private:

	DriveSettings *driveSettings;
	DriveStatus *driveStatus;

	uint64_t tmpFlashArray[UFLASH_SIZE];
};


#endif /* SRC_FLASH_FLASH_H_ */

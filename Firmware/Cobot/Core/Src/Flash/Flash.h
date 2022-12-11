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
#define UFLASH_PAGE					128
#define UFLASH_NPAGES				1


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

private:

	DriveSettings *driveSettings;
	DriveStatus *driveStatus;
	bool factoryResetFlag;

	uint64_t tmpFlashArray[UFLASH_SIZE];
};


#endif /* SRC_FLASH_FLASH_H_ */

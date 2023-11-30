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
constexpr auto UFLASH_DATA_SIZE = 64;

constexpr auto FLASH_STAR_PAGE_ADDR = 0x0803F800;
constexpr auto UFLASH_SIZE = 20;
constexpr auto UFLASH_PAGE = 127;
constexpr auto UFLASH_NPAGES = 1;



class Flash
{

public:

     Flash(DriveSettings* driveSettings, DriveStatus* driveStatus);

     HAL_StatusTypeDef Save();
     void ReadFlash();
     void WriteFlash();
     void SaveDefault();

private:

     DriveSettings* driveSettings;
     DriveStatus* driveStatus;

     uint64_t tmpFlashArray[UFLASH_SIZE];
};


#endif /* SRC_FLASH_FLASH_H_ */

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

constexpr auto CLAMPING_SPEED_ADDR = 0x00;
constexpr auto CLAMPING_TORQUE_ADDR = 0x01;
constexpr auto TEACH_SPEED_ADDR = 0x02;
constexpr auto TEACH_TROQUE_ADDR = 0x03;
constexpr auto OVERCURRENT_ERROR_ADDR = 0x04;
constexpr auto OVERCURRENT_WARNING_ADDR = 0x05;
constexpr auto UNDERVOLTAGE_ERROR_ADDR = 0x06;
constexpr auto UNDERVOLTAGE_WARNING_ADDR = 0x07;
constexpr auto SELF_SHUTDOWN_DELAY_ADDR = 0x08;
constexpr auto IN_POS_DIFF_ADDR = 0x09;
constexpr auto OPENING_DISTANCE_ADDR = 0x0A;

class Flash
{

public:

     Flash(DriveSettings* driveSettings, DriveStatus* driveStatus);

     HAL_StatusTypeDef Save();
     void ReadFlash();
     void WriteFlash();

private:

     DriveSettings* driveSettings;
     DriveStatus* driveStatus;

     uint64_t tmpFlashArray[UFLASH_SIZE];
};


#endif /* SRC_FLASH_FLASH_H_ */

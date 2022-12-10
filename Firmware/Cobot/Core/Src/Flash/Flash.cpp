/*
 * Flash.cpp
 *
<<<<<<< HEAD
 *  Created on: 09.12.2022
 *      Author: marce
 */

#include "Flash.h"


=======
 *  Created on: 27.11.2022
 *      Author: marce
 */


#include "Flash.h"


Flash::Flash(DriveSettings *driveSettings, DriveStatus *driveStatus) {

	this->driveSettings = driveSettings;
	this->driveStatus = driveStatus;

	this->factoryResetFlag = false;

}

void Flash::clearFlash() {

}

/*
 * Auslesen vom Flash und speichern in tmpFlashArray
 *
 * @param None
 * @return None
 */
void Flash::ReadFlash() {

	for (int i = 0; i < FLASH_SIZE; i++) {
		tmpFlashArray[i] = *(uint16_t*) (FLASH_STAR_PAGE_ADDR + 16 * i);
	}
	//write flash to config and status file
}

/*
 * Speichert das tmpFlashArry in's Flash
 *
 * @param None
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef Flash::WriteFlash() {

	FLASH_EraseInitTypeDef EraseinitStruct;
	uint32_t sectorError = 0;
	//ToDo write settings to flashBuffer

	if (HAL_FLASH_Unlock() != HAL_OK) {
		HAL_FLASH_Lock();
		driveStatus->setError(DriveStatus::E_FLASH_ERROR);
		return HAL_ERROR;
	}

	EraseinitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseinitStruct.PageAddress = FLASH_STAR_PAGE_ADDR;
	EraseinitStruct.NbPages = 1;


	if (HAL_FLASHEx_Erase(&EraseinitStruct, &sectorError) != HAL_OK) {
		HAL_FLASH_Lock();
		antriebStatus->setAntriebErrorCode(AntriebStatus::E_FLASH_ERROR);
		return HAL_ERROR;
	}

	for (int i = 0; i < FLASH_SIZE; i++) {
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (FLASH_STAR_PAGE_ADDR + 32 * i), tmpFlashArray[i]);
	}


	if (HAL_FLASH_Lock() != HAL_OK) {
		HAL_FLASH_Lock();
		antriebStatus->setAntriebErrorCode(AntriebStatus::E_FLASH_ERROR);
		return HAL_ERROR;
	}

	return HAL_OK;
}


void Flash::SystemReboot() {
	NVIC_SystemReset(); //System Reset
}

void Flash::SystemFactoryReset() {
	this->factoryResetFlag = true;
	this->flashSchreiben();
	this->systemReboot();
}
>>>>>>> origin/main

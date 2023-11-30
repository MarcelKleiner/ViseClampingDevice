#include "Flash.h"
#include "stm32l4xx_hal.h"

Flash::Flash(DriveSettings *driveSettings, DriveStatus *driveStatus)
{
	this->driveSettings = driveSettings;
	this->driveStatus = driveStatus;
}

void Flash::ReadFlash()
{

	for (int i = 0; i < UFLASH_SIZE; i++)
	{
		tmpFlashArray[i] = *(uint64_t*) (FLASH_STAR_PAGE_ADDR + 64 * i);
	}

	driveSettings->setClampingSpeed(tmpFlashArray[0]);
	driveSettings->setClampingTorque(tmpFlashArray[1]);
	driveSettings->setTeachSpeed(tmpFlashArray[2]);
	driveSettings->setTeachTroque(tmpFlashArray[3]);

	driveSettings->setOverCurrentError(tmpFlashArray[4]);
	driveSettings->setOverCurrentWarning(tmpFlashArray[5]);
	driveSettings->setUnderVoltageError(tmpFlashArray[6]);
	driveSettings->setUnderVoltageWarning(tmpFlashArray[7]);

	driveSettings->setSelfShutdownDelay(tmpFlashArray[8]);
	driveSettings->setInPosDiff(tmpFlashArray[9]);
	driveSettings->setOpeningDistance(tmpFlashArray[10]);

	driveSettings->setDeviceAddress(tmpFlashArray[11]);
}

void Flash::SaveDefault() {
	tmpFlashArray[0] = 10;
	tmpFlashArray[1] = 30;
	tmpFlashArray[2] = 10;
	tmpFlashArray[3] = 2;

	tmpFlashArray[4] = 100;
	tmpFlashArray[5] = 50;
	tmpFlashArray[6] = 12000;
	tmpFlashArray[7] = 14000;

	tmpFlashArray[8] = 600;
	tmpFlashArray[9] = 20;
	tmpFlashArray[10] = 100;

	tmpFlashArray[11] = 0x1F;
	Save();
}

void Flash::WriteFlash(){
	if (this->driveSettings->isSaveSettings())
	{
		tmpFlashArray[0] = driveSettings->getClampingSpeed();
		tmpFlashArray[1] = driveSettings->getClampingTorque();
		tmpFlashArray[2] = driveSettings->getTeachSpeed();
		tmpFlashArray[3] = driveSettings->getTeachTroque();

		tmpFlashArray[4] = driveSettings->getOverCurrentError();
		tmpFlashArray[5] = driveSettings->getOverCurrentWarning();
		tmpFlashArray[6] = driveSettings->getUnderVoltageError();
		tmpFlashArray[7] = driveSettings->getUnderVoltageWarning();

		tmpFlashArray[8] = driveSettings->getSelfShutdownDelay();
		tmpFlashArray[9] = driveSettings->getInPosDiff();
		tmpFlashArray[10] = driveSettings->getOpeningDistance();

		tmpFlashArray[11] = driveSettings->getDeviceAddress();
		Save();
	}
}


HAL_StatusTypeDef Flash::Save()
{

	FLASH_EraseInitTypeDef EraseinitStruct{};
	uint32_t sectorError = 0;

	if (HAL_FLASH_Unlock() != HAL_OK)
	{
		HAL_FLASH_Lock();
		driveStatus->setError(DriveStatus::E_FLASH_ERROR);
		return HAL_ERROR;
	}

	EraseinitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseinitStruct.Banks = 1;
	EraseinitStruct.Page = UFLASH_PAGE;
	EraseinitStruct.NbPages = UFLASH_NPAGES;

	if (HAL_FLASHEx_Erase(&EraseinitStruct, &sectorError) != HAL_OK)
	{
		HAL_FLASH_Lock();
		driveStatus->setError(DriveStatus::E_FLASH_ERROR);
		return HAL_ERROR;
	}

	for (int i = 0; i < UFLASH_SIZE; i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,
				(FLASH_STAR_PAGE_ADDR + 64 * i), tmpFlashArray[i]);
	}

	if (HAL_FLASH_Lock() != HAL_OK)
	{
		HAL_FLASH_Lock();
		driveStatus->setError(DriveStatus::E_FLASH_ERROR);
		return HAL_ERROR;
	}

	return HAL_OK;
}


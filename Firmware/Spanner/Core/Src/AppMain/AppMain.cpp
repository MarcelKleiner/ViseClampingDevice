/*
 * AppMain.cpp
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#include "AppMain.h"
#include "usbd_conf.h"
#include "usbd_def.h"
#include "usbd_cdc_if.h"

extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

extern ADC_HandleTypeDef hadc1;

AppMain::AppMain()
{

}

void AppMain::Startup()
{
	//Set "self power on" to turn on the external Mosfet.
	HAL_GPIO_WritePin(POWER_SWITCH_GPIO_Port, POWER_SWITCH_Pin, GPIO_PIN_SET);
	//turn ext led on
	ledExt.ON();

	//inti SPI
	HAL_SPI_MspInit(&hspi1);

	//init and start Timer
	HAL_TIM_PWM_MspInit(&htim2);	//PWM timer
	HAL_TIM_Base_MspInit(&htim16);	//task handler timer
	HAL_TIM_Base_MspInit(&htim6);	//ADC trigger timer

	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);	//start PWM CH2
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);	//start PWM CH1
	HAL_TIM_Base_Start_IT(&htim16);				//start task handler in IT mode

	//init and start ADC
	HAL_ADC_MspInit(&hadc1);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) adc1Buffer, BUFFER_SIZE_ADC1);
	HAL_TIM_Base_Start_IT(&htim6);

	//configure Motor throttle
	TIM2->CCR1 = 6400;
	HAL_Delay(7000);
	TIM2->CCR1 = 3200;

	if (!rfm95.InitRFM())
	{
		error.setError(Error::COM_ERROR);
		taskHandler.setDriveTaskEnable(false);
	}
	rfm95.receive(0);
	encoder.init();

	Main();
}

int startupCounter = 50;

void AppMain::Reset()
{
	error.resetError();
	taskHandler.setAdcUpdateTaskEnable(true);
	taskHandler.setComTaskEnable(true);
	taskHandler.setDriveTaskEnable(true);
	taskHandler.setErrorTaskEnable(true);
	taskHandler.setIoUpdateTaskEnable(true);

	driveCommand.setStop(false);
}

void AppMain::Main()
{

	taskHandler.setDriveTaskEnable(false);

	while (1)
	{

		if (init && startupCounter <= 0)
		{
			startupCounter = 1;
			taskHandler.setDriveTaskEnable(true);
			TIM2->CCR1 = 3600;
			init = false;
		}

		if (driveCommand.isReset())
		{
			drive.Reset();
			driveCommand.setReset(false);
		}

		if (taskHandler.isADCUpdateTask())
		{
			//read from ADC DMA register
		}

		if (taskHandler.isComTask())
		{
			if (!rfm95COM->Receive())
			{
				comLoseCounter++;
			}
			else
			{
				comLoseCounter = 0;

			}

			if (comLoseCounter == (driveSettings.getSelfShutdownDelay() * 4))
			{
				//Self-shutdown when the delay time for self-shutdown has elapsed
				HAL_GPIO_WritePin(POWER_SWITCH_GPIO_Port, POWER_SWITCH_Pin,
						GPIO_PIN_RESET);
			}
		}

		if (taskHandler.isDriveTask())
		{
			encoder.update();
			drive.updateDrive();
		}

		if (taskHandler.isErrorTask())
		{
			if(driveStatus.getVoltage() < driveSettings.getUnderVoltageWarning()){
				driveStatus.setError(DriveStatus::E_UNDERVOLTAGE_WARNING);
			}

			if(driveStatus.getVoltage() < driveSettings.getUnderVoltageError()){
				driveStatus.setError(DriveStatus::E_UNDERVOLTAGE_ERROR);
			}



			if (driveStatus.getError() != DriveStatus::E_NO_ERROR)
			{
				drive.Stop();
				taskHandler.setAdcUpdateTaskEnable(false);
				taskHandler.setDriveTaskEnable(false);
			}

			error.error2LED();

			if (startupCounter > 0)
			{
				startupCounter--;
			}
		}

		if (taskHandler.isIoUpdateTask())
		{

		}

		if (taskHandler.isLEDTask())
		{
			led.Toggle();
		}

	}
}

void AppMain::ADCRead(ADC_HandleTypeDef *hadc)
{
	uint16_t current = 0; //1/3
	uint16_t voltage = 0; //0/2

	current = (adc1Buffer[1] + adc1Buffer[3]) / 2;
	voltage = (adc1Buffer[0] + adc1Buffer[2]) / 2;

	if (init && zCurrentCounter < 16)
	{
		if (zCurrentCounter == 15)
		{
			driveStatus.setZCurrent(zCurrent / 15);
			zCurrentCounter = 16;
		}
		else
		{
			zCurrent += current;
			zCurrentCounter++;
		}
	}



	driveStatus.setCurrent(current);
	driveStatus.setVoltage(voltage);

	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) adc1Buffer, BUFFER_SIZE_ADC1);
}


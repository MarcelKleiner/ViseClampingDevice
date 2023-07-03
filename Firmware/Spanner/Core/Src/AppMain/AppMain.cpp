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


	if (!rfm95.InitRFM())
	{
		driveStatus.setError(DriveStatus::E_COM_ERROR);
		taskHandler.setDriveTaskEnable(false);
	}
	rfm95.receive(0);
	encoder.init();

	Main();
}



void AppMain::Reset()
{
	taskHandler.setComTaskEnable(true);
	taskHandler.setDriveTaskEnable(true);
	taskHandler.setErrorTaskEnable(true);

	TIM2->CCR1 = 3600;

	driveCommand.setTeach(false);
	driveCommand.setClose(false);
	driveCommand.setOpen(false);
	driveCommand.setEnable(false);
	driveCommand.setStop(false);
	driveCommand.setReset(false);

	driveStatus.setError(DriveStatus::E_NO_ERROR);
	comLoseCounter = 0;
}


void AppMain::Main()
{

	taskHandler.setDriveTaskEnable(false);

	while (1)
	{
		//Reset task
		if (driveCommand.isReset())
		{
			Reset();
		}

		//RFM Communication task
		if (taskHandler.isComTask())
		{
			if (!rfm95COM->Receive())
			{
				comLoseCounter++;
				drive.Stop();
			}
			else
			{
				comLoseCounter = 0;
			}

			if (comLoseCounter == (driveSettings.getSelfShutdownDelay() * 4))
			{
				//Self-shutdown when the delay time for self-shutdown has elapsed
				HAL_GPIO_WritePin(POWER_SWITCH_GPIO_Port, POWER_SWITCH_Pin, GPIO_PIN_RESET);
			}
		}

		//Drive Task
		if (taskHandler.isDriveTask())
		{
			encoder.update();
			drive.updateDrive();
		}

		//Error Task
		if (taskHandler.isErrorTask())
		{
			if(driveStatus.getVoltage() < driveSettings.getUnderVoltageWarning()){
				driveStatus.setError(DriveStatus::E_UNDERVOLTAGE_WARNING);
			}

			if(driveStatus.getVoltage() < driveSettings.getUnderVoltageError()){
				driveStatus.setError(DriveStatus::E_UNDERVOLTAGE_ERROR);
			}

			if(driveStatus.getCurrent() > driveSettings.getOverCurrentWarning())
			{
				driveStatus.setError(DriveStatus::E_OVERCURRENT_WARNING);
			}

			if(driveStatus.getCurrent() > driveSettings.getOverCurrentError())
			{
				driveStatus.setError(DriveStatus::E_OVERCURRENT_ERROR);
			}

			if (driveStatus.getError() != DriveStatus::E_NO_ERROR)
			{
				drive.Stop();
				taskHandler.setDriveTaskEnable(false);
				taskHandler.setLEDTaskEnable(false);
				error.error2LED();
			}
		}


		if (taskHandler.isLEDTask())
		{
			led.Toggle();
			ledExt.Toggle();
		}

	}
}




void AppMain::ADCRead(ADC_HandleTypeDef *hadc)
{
    currentSum = currentSum - currentArray[staticCounter] + adc1Buffer[0];
    currentArray[staticCounter] = adc1Buffer[0];

    voltageSum = voltageSum - voltageArray[staticCounter] + adc1Buffer[1];
    voltageArray[staticCounter] = adc1Buffer[1];


    if (staticCounter == MEAN_VALUE_SIZE-1)
    {
        staticCounter = 0;
    }
    else
    {
        staticCounter++;
    }


	driveStatus.setCurrent(currentSum/MEAN_VALUE_SIZE);
	driveStatus.setVoltage(voltageSum/MEAN_VALUE_SIZE);

	//restart ADC DMA Conversion
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) adc1Buffer, BUFFER_SIZE_ADC1);
}




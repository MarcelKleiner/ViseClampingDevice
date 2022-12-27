/*
 * AppMain.cpp
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#include "AppMain.h"

extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

AppMain::AppMain()
{

}

void AppMain::Startup()
{
	HAL_SPI_MspInit(&hspi1);

	HAL_TIM_PWM_MspInit(&htim2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);



	//TIM2->CCR1 = 6400;

	TIM2->CCR1 = 6400;
	HAL_Delay(7000);
	TIM2->CCR1 = 3200;



	HAL_Delay(100);

	if (!rfm95.InitRFM())
	{
		error.setError(Error::COM_ERROR);
		taskHandler.setDriveTaskEnable(false);
	}
	rfm95.receive(0);
	encoder.init();

	HAL_TIM_Base_MspInit(&htim16);

	HAL_TIM_Base_Start_IT(&htim16);


	Main();
}

int startupCounter = 100;

void AppMain::Reset()
{

	error.resetError();
	taskHandler.setAdcUpdateTaskEnable(true);
	taskHandler.setComTaskEnable(true);
	taskHandler.setDriveTaskEnable(true);
	taskHandler.setErrorTaskEnable(true);
	taskHandler.setIoUpdateTaskEnable(true);
}

void AppMain::Main()
{

	taskHandler.setDriveTaskEnable(false);
	bool init = true;
	while (1)
	{

		if(init && startupCounter <= 0){
			startupCounter = 1;
			TIM2->CCR1 = 3400;
			taskHandler.setDriveTaskEnable(true);
			init = false;
		}


		if (driveStatus.isReset())
		{
			drive.Reset();
			driveStatus.setReset(false);
		}

		if (taskHandler.isADCUpdateTask())
		{
			//read from ADC DMA register
		}

		if (taskHandler.isComTask())
		{
			rfm95COM->Receive();
		}

		if (taskHandler.isDriveTask())
		{
			encoder.update();
			drive.updateDrive();
		}

		if (taskHandler.isErrorTask())
		{
			if (driveStatus.getError() != Error::NO_ERROR)
			{
				drive.Stop();
				taskHandler.setAdcUpdateTaskEnable(false);
				taskHandler.setDriveTaskEnable(false);
			}

			error.error2LED();

			if(startupCounter > 0){
				startupCounter--;
			}
		}

		if (taskHandler.isIoUpdateTask())
		{

		}

		if (taskHandler.isLEDTask())
		{
			this->led.Toggle();
		}

	}
}


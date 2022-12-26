/*
 * AppMain.cpp
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#include "AppMain.h"

extern TIM_HandleTypeDef htim16;


AppMain::AppMain()
{

}


void AppMain::Startup()
{
	HAL_SPI_MspInit(&hspi1);
	//HAL_TIM_Base_Start_IT(&htim16);

	HAL_Delay(100);

	if(!rfm95.InitRFM()){
			error.setError(Error::COM_ERROR);
			taskHandler.setDriveTaskEnable(false);
	}
	rfm95.receive(0);

	  HAL_TIM_Base_MspInit(&htim16);
	  HAL_TIM_Base_Start_IT(&htim16);
	Main();
}

void AppMain::Reset(){

	error.resetError();
	taskHandler.setAdcUpdateTaskEnable(true);
	taskHandler.setComTaskEnable(true);
	taskHandler.setDriveTaskEnable(true);
	taskHandler.setErrorTaskEnable(true);
	taskHandler.setIoUpdateTaskEnable(true);
}


void AppMain::Main()
{


	while(1)
	{

		if(taskHandler.isADCUpdateTask()){
			//read from ADC DMA register
		}

		if(taskHandler.isComTask()){
			com.ReadData();
		}

		if(taskHandler.isDriveTask()){

		}

		if(taskHandler.isErrorTask()){
			error.error2LED();
			if(error.getError() != Error::NO_ERROR){
				drive.Stop();
			}
		}

		if(taskHandler.isIoUpdateTask()){

		}

		if(taskHandler.isLEDTask()){
			//this->led.Toggle();
		}


	}
}





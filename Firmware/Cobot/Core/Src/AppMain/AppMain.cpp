/*
 * AppMain.cpp
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#include "AppMain.h"
#include "../Tools/Delay.h"

extern TIM_HandleTypeDef htim7;

AppMain::AppMain()
{

}

void AppMain::Startup()
{
	Storage.ReadFlash();


	HAL_TIM_Base_Start_IT(&htim7);

	LED_Green.OFF();
	LED_Red.OFF();

	if (rfm95.InitRFM())
	{

	}

	Delay::DWT_Init();


	Main();
}

void AppMain::Main()
{

	while (1)
	{

		if (taskStatus.isErrorTask())
		{

		}

		if (taskStatus.isLEDUpdateTask())
		{
			LED_Green.Toggle();
		}

		if (taskStatus.isComTask())
		{
			com.UpdateCom();
			com.ReadData();
		}

		if (taskStatus.isIoUpdateTask())
		{
			DigitalInOut.Read();
		}

	}
}


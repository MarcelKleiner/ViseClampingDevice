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

	HAL_TIM_Base_Start_IT(&htim7);

	LED_Green.OFF();
	LED_Red.OFF();

	if (rfm95.InitRFM())
	{

	}

	Delay::DWT_Init();

	closed.Reset();
	open.Reset();
	viseReady.Reset();
	error.Reset();
	batteryLow.Reset();
	signal.Reset();
	res1.Reset();
	res2.Reset();

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

		}

		if (taskStatus.isIoUpdateTask())
		{
			DigitalIn.Read();
			if (DigitalIn.IsDataReady())
			{
				uint8_t data = DigitalIn.GetData();
			}
		}

	}
}


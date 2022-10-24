/*
 * AppMain.cpp
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#include "AppMain.h"



AppMain::AppMain()
{

}


void AppMain::Startup()
{
	if(rfm95.InitRFM()){

	}


}



void AppMain::Main()
{
	initRFM();

	while(1)
	{

		if(taskStatus.isDigitalInTask()){

		}


		if(taskStatus.isDigitalOutTask()){

		}


		if(taskStatus.isLedTask()){

		}


		if(taskStatus.isRfmTask()){

		}

	}
}





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
	if(!rfm95.InitRFM()){
		error.setError(Error::COM_ERROR);
		taskHandler.setDriveTaskEnable(false);
	}


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



	}
}





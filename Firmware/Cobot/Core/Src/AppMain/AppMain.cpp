/*
 * AppMain.cpp
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#include "../Tools/Delay.h"
#include "AppMain.h"

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

     if (!rfm95.InitRFM())
     {
          //ToDo set error
     }

     Delay::DWT_Init();

     Main();
}
bool toggleRFM = false;
void AppMain::Main()
{

     while (1)
     {

          if (taskStatus.isErrorTask())
          {
               error.PrintError();
          }

          if (taskStatus.IsLEDUpdateTask())
          {
               LED_Green.Toggle();
          }

          if (taskStatus.isComTask())
          {
               rfm95COM.Transmitt();
          }

          if (taskStatus.isComTaskRx()) {
               rfm95COM.Receive();
          }

          if (taskStatus.isIoUpdateTask())
          {
               ioCOM->Receive();
               ioCOM->Transmitt();
          }

          if (taskStatus.isSaveTask())
          {
               Storage.WriteFlash();
          }

          if (taskStatus.IsResetUpdateTask()) {
               if (driveStatus.IsSelfReset())
               {
                    error.ResetError();
                    driveStatus.ResetSelfReset();
               }
          }

     }
}


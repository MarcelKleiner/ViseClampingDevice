/*
 * AppMain.h
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#ifndef SRC_APPMAIN_APPMAIN_H_
#define SRC_APPMAIN_APPMAIN_H_

#include "../Taskhandler/Taskhandler.h"
#include "../RFM95W/RFM95.h"
#include "../RFM95W/Communication.h"
#include "../Tools/Delay.h"
#include "../IO/DO.h"
#include "../IO/LED.h"
#include "../IO/DI.h"
#include "tim.h"
#include "main.h"

class AppMain
{

	public:
		AppMain();

		void Startup(void);
		void Main(void);

		RFM95_LoRa rfm95 = RFM95_LoRa();
		TaskHandler taskStatus = TaskHandler();

		LED LED_Green = LED(LED_G_GPIO_Port, LED_G_Pin, true);
		LED LED_Red = LED(LED_R_GPIO_Port, LED_R_Pin, true);

		DriveSettings driveSettings = DriveSettings();
		DriveStatus driveStatus = DriveStatus();

		Digitll_IN_OUT DigitalInOut = Digitll_IN_OUT(&driveSettings, &driveStatus);
		Communication com = Communication(&driveStatus, &driveSettings, &rfm95, &DigitalInOut);

	private:

};

#endif /* SRC_APPMAIN_APPMAIN_H_ */

/*
 * AppMain.h
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#ifndef SRC_APPMAIN_APPMAIN_H_
#define SRC_APPMAIN_APPMAIN_H_

#include "../Flash/Flash.h"
#include "../IO/DO.h"
#include "../IO/LED.h"
#include "../RFM95W/RFM95.h"
#include "../Taskhandler/Taskhandler.h"
#include "../Tools/Delay.h"
#include "main.h"
#include "tim.h"

#include "../COM/ICom.h"
#include "../COM/IOCom.h"
#include "../COM/RFM95Com.h"
#include "../COM/USBCom.h"
#include "../Error/Error.h"

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
		DriveCommand driveCommand = DriveCommand();

		Flash Storage = Flash(&driveSettings, &driveStatus);

		RFM95Com rfm95COM =  RFM95Com(&driveStatus, &driveSettings, &driveCommand, &rfm95, &Storage);
		ICom *usbCOM	= new USBCom(&driveStatus, &driveSettings, &driveCommand, &Storage);
		ICom *ioCOM	= new IOCom(&driveStatus, &driveSettings, &driveCommand, &Storage);


		Error error = Error(&driveStatus);
	private:

};

#endif /* SRC_APPMAIN_APPMAIN_H_ */

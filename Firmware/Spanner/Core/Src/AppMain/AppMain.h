/*
 * AppMain.h
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#ifndef SRC_APPMAIN_APPMAIN_H_
#define SRC_APPMAIN_APPMAIN_H_

#include "../Error/Error.h"
#include "../Taskhandler/TaskHandler.h"
#include "../RFM95/RFM95.h"
#include "../RFM95/Communication.h"

#include "../Drive/Drive.h"

#include "../Settings/DriveSettings.h"
#include "../Status/DriveStatus.h"

#include "../IO/LED.h"


 class AppMain{

 public:
	 AppMain();

	 void Startup(void);
	 void Main(void);
	 void Reset(void);

	 TaskHandler taskHandler = TaskHandler();

 private:

	 Error error = Error();
	 RFM95_LoRa rfm95 = RFM95_LoRa();
	 DriveSettings driveSettings = DriveSettings();
	 DriveStatus driveStatus = DriveStatus();
	 Communication com = Communication(&driveStatus, &driveSettings, &rfm95);

	 Drive drive = Drive(&driveSettings, &driveStatus);

	 LED led = LED(LED_GPIO_Port, LED_Pin, false);


};


#endif /* SRC_APPMAIN_APPMAIN_H_ */

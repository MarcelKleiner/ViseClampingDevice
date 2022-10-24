/*
 * AppMain.h
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#ifndef SRC_APPMAIN_APPMAIN_H_
#define SRC_APPMAIN_APPMAIN_H_

#include "../Error/Error.h"
#include "../Status/TaskHandler.h"
#include "../RFM95/RFM95.h"
#include "../Status/DriveStatus.h"
#include "../Drive/Drive.h"
#include "../Settings/DriveSettings.h"



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


	 Drive drive = Drive(&driveSettings, &driveStatus);

};


#endif /* SRC_APPMAIN_APPMAIN_H_ */

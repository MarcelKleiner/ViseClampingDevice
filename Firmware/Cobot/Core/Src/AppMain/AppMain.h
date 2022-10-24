/*
 * AppMain.h
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#ifndef SRC_APPMAIN_APPMAIN_H_
#define SRC_APPMAIN_APPMAIN_H_

#include "../Status/TaskStatus.h"





 class AppMain{

 public:
	 AppMain();

	 void Startup(void);
	 void Main(void);

	 RFM95_LoRa rfm95 = RFM95_LoRa();

	 TaskHandler taskStatus = TaskHandler();



 private:



};


#endif /* SRC_APPMAIN_APPMAIN_H_ */

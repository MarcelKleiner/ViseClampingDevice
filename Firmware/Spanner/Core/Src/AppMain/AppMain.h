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


#include "../Drive/Drive.h"

#include "../Settings/DriveSettings.h"
#include "../Status/DriveStatus.h"
#include "../Status/DriveCommand.h"

#include "../COM/BaseCOM.h"
#include "../COM/ICom.h"
#include "../COM/RFM95Com.h"


#include "../IO/LED.h"

#define BUFFER_SIZE_ADC1	2

#define MEAN_VALUE_SIZE 	5


 class AppMain{

 public:
	 AppMain();

	 void Startup(void);
	 void Main(void);
	 void Reset(void);
	 void ADCRead(ADC_HandleTypeDef *hadc);
	 TaskHandler taskHandler = TaskHandler();

 private:


	 RFM95_LoRa rfm95 = RFM95_LoRa();


	 DriveSettings driveSettings = DriveSettings();
	 DriveStatus driveStatus = DriveStatus();
	 DriveCommand driveCommand = DriveCommand();

	 Encoder encoder = Encoder(&driveStatus);
	 ICom *rfm95COM 	= 	 new RFM95Com	(&driveStatus, &driveSettings, &driveCommand, &rfm95);
	 LED led = LED(LED_GPIO_Port, LED_Pin, false);
	 LED ledExt = LED(LED_EXT_GPIO_Port, LED_EXT_Pin, false);


	 Drive drive = Drive(&driveSettings, &driveStatus, &driveCommand, &encoder, &led);
	 Error error = Error(&ledExt, &driveStatus);

	bool init = true;
	uint16_t comLoseCounter = 0;




	//ADC Variables
	volatile int16_t adc1Buffer[BUFFER_SIZE_ADC1];
	uint16_t currentArray[MEAN_VALUE_SIZE];
	uint16_t voltageArray[MEAN_VALUE_SIZE];
	uint32_t currentSum = 0;
	uint32_t voltageSum = 0;
	uint8_t staticCounter = 0;

};


#endif /* SRC_APPMAIN_APPMAIN_H_ */

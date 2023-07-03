/*
 * Error.cpp
 *
 *  Created on: 23.10.2022
 *      Author: marce
 */

#include "Error.h"
#include "main.h"
#include "gpio.h"

Error::Error(LED* led, DriveStatus *driveStatus){
	this->led = led;
	this->driveStatus = driveStatus;
}


void Error::error2LED() {
	//function should be call every 100ms

	if (driveStatus->getError() != DriveStatus::E_NO_ERROR) {
		if (this->LEDerrorCounter == 1) {
			this->errorCode = (uint8_t)driveStatus->getError();		//Errorcode vom DriveStatus bei Zyklus 1 einlesen
		}

		if (LEDerrorCounter <= errorCode * 6) {
			//Error Code Ausgeben
			if (LEDerrorCounter % 6 == 0) {
				led->ON();
			} else {
				led->OFF();
			}
			LEDerrorCounter++;
		} else if (LEDerrorCounter <= errorCode * 6 + 15) {
			//Nach Errorcode 4 Zyklen Pause
			led->OFF();
			LEDerrorCounter++;
		} else {
			//Nach 4 Pause Widerholen
			LEDerrorCounter = 1;
		}
	}

}

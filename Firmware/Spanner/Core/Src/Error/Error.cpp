/*
 * Error.cpp
 *
 *  Created on: 23.10.2022
 *      Author: marce
 */

#include "Error.h"
#include "main.h"
#include "gpio.h"


void Error::setError(EERROR_CODE error) {
	this->errorCode = error;
}

Error::EERROR_CODE Error::getError() {
	return this->errorCode;
}

void Error::resetError() {
	this->errorCode = EERROR_CODE::NO_ERROR;
}


void Error::error2LED() {
	//function should be call every 100ms
	static uint8_t errorCounter = 0;
	static bool risingEdge = 0;

	if(errorCode != NO_ERROR ){

		if(risingEdge){

			if((this->errorCode>>errorCounter)& 0x01){
				//set LED Error
			}else{
				//reset LED Error
			}

			//increment error counter by 1
			errorCounter++;


			if(errorCounter > 7){
				errorCounter = 0;
			}

		}
	}
	risingEdge != risingEdge;
}

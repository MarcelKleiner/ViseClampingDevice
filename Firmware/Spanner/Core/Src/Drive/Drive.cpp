
/*
 * Drive.cpp
 *
 *  Created on: 23.10.2022
 *      Author: marce
 */


#include "Drive.h"
#include "../IO/IO.h"

Drive::Drive(DriveSettings *driveSettings, DriveStatus *driveStatus){

	this->driveSettings  = driveSettings;
	this->driveStatus = driveStatus;

}

void Drive::updateDrive() {
	switch (driveMode) {
		case Drive::OP_MODE:
			OpMode();
			break;
		case Drive::TEACH_MODE:
			TeachMode();
		default:
			break;
	}
}



void Drive::OpMode() {

}

void Drive::Stop() {

}



void Drive::TeachMode() {
	static uint8_t counter = 0;
	static bool InOut = 0;
	currentState = nextState;

	switch (currentState) {
		case TEACH_MODE_ENTER:
			if(IS_EXT_SWITCH == GPIO_PIN_RESET){
				nextState = TEACH_RDY;
			}
		case TEACH_RDY:
			if(IS_EXT_SWITCH){
				nextState = CHECK_CLK;
			}
		case CHECK_CLK:
			if(counter > 2 && IS_EXT_SWITCH){
				if(InOut){
					nextState = DRIVE_IN;
				}else{
					nextState = DRIVE_OUT;
				}
				InOut = !InOut;
			}

			if(!IS_EXT_SWITCH){
				nextState = CLK_1;
			}

			if(nextState != currentState){
				counter = 0;
			}else{
				counter++;
			}

			break;
		case CLK_1:
			if(counter > 2 && !IS_EXT_SWITCH){
				nextState = TEACH_RDY;
			}

			if(IS_EXT_SWITCH){
				nextState = CLK_2;
			}

			if(nextState != currentState){
				counter = 0;
			}else{
				counter++;
			}

			break;
		case CLK_2:
			if(IS_EXT_SWITCH){
				nextState = TEACH_END;
			}

			break;
		case DRIVE_IN:
			//move drive in
			MoveDrive(IN, driveSettings->getTeachTroque() , driveSettings->getTeachSpeed());
			break;
		case DRIVE_OUT:
			//move drive out
			MoveDrive(OUT, driveSettings->getTeachTroque() , driveSettings->getTeachSpeed());
			break;
		case TEACH_END:
			//reset TTL counter
			break;
		default:
			break;
	}

}



Drive::EDRIVE_MODE Drive::getDriveMode() const {
	return driveMode;
}

void Drive::setDriveMode(EDRIVE_MODE driveMode) {
	this->driveMode = driveMode;
}

void Drive::MoveDrive(DIRECTION direction, uint16_t torque, uint16_t speed) {
}

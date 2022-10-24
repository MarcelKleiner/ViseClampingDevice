
/*
 * DriveStatus.cpp
 *
 *  Created on: 22.10.2022
 *      Author: marce
 */

#include "DriveStatus.h"



/*******************************************************************
 * Current settings
 ******************************************************************/

uint16_t DriveStatus::getCurrent() const {
	return current;
}

void DriveStatus::setCurrent(uint16_t current) {
	this->current = current;
}



/*******************************************************************
 * Position settings
 ******************************************************************/

uint16_t DriveStatus::getPosition() const {
	return position;
}

void DriveStatus::setPosition(uint16_t position) {
	this->position = position;
}






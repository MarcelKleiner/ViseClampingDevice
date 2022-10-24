
/*
 * IO.cpp
 *
 *  Created on: 23.10.2022
 *      Author: marce
 */
#include "IO.h"

uint16_t IO::getCurrent() const {
	return current;
}

void IO::setCurrent(uint16_t rawCurrent) {

	//ToDo convert rawCurrent in current
	this->current = current;
}

uint16_t IO::getVoltage() const {
	return voltage;
}

void IO::setVoltage(uint16_t rawVoltage) {
	//ToDo convert rawVoltage in voltage
	this->voltage = voltage;
}



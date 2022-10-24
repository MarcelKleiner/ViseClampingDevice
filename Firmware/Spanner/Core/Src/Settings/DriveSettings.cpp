/*
 * DriveSettings.cpp
 *
 *  Created on: 22.10.2022
 *      Author: marce
 */
#include "DriveSettings.h"

uint16_t DriveSettings::getClampingSpeed() const {
	return clampingSpeed;
}

void DriveSettings::setClampingSpeed(uint16_t clampingSpeed) {
	this->clampingSpeed = clampingSpeed;
}

uint16_t DriveSettings::getClampingTorque() const {
	return clampingTorque;
}

void DriveSettings::setClampingTorque(uint16_t clampingTorque) {
	this->clampingTorque = clampingTorque;
}

uint8_t DriveSettings::getDeviceAddress() const {
	return deviceAddress;
}

void DriveSettings::setDeviceAddress(uint8_t deviceAddress) {
	this->deviceAddress = deviceAddress;
}

uint16_t DriveSettings::getInPosDiff() const {
	return inPosDiff;
}

void DriveSettings::setInPosDiff(uint16_t inPosDiff ) {
	this->inPosDiff = inPosDiff;
}

uint16_t DriveSettings::getOpeningDistance() const {
	return openingDistance;
}

void DriveSettings::setOpeningDistance(uint16_t openingDistance ) {
	this->openingDistance = openingDistance;
}

uint16_t DriveSettings::getOverCurrentTimeThreshold() const {
	return overCurrentTimeThreshold;
}

void DriveSettings::setOverCurrentTimeThreshold(
		uint16_t overCurrentTimeThreshold) {
	this->overCurrentTimeThreshold = overCurrentTimeThreshold;
}

uint16_t DriveSettings::getOverCurrentWarning() const {
	return overCurrentWarning;
}

void DriveSettings::setOverCurrentWarning(uint16_t overCurrentWarning) {
	this->overCurrentWarning = overCurrentWarning;
}

uint16_t DriveSettings::getSelfShutdownDelay() const {
	return selfShutdownDelay;
}

void DriveSettings::setSelfShutdownDelay(uint16_t selfShutdownDelay) {
	this->selfShutdownDelay = selfShutdownDelay;
}

uint16_t DriveSettings::getTeachSpeed() const {
	return teachSpeed;
}

void DriveSettings::setTeachSpeed(uint16_t teachSpeed ) {
	this->teachSpeed = teachSpeed;
}

uint16_t DriveSettings::getTeachTroque() const {
	return teachTroque;
}

void DriveSettings::setTeachTroque(uint16_t teachTroque) {
	this->teachTroque = teachTroque;
}

uint16_t DriveSettings::getUnderVoltageError() const {
	return underVoltageError;
}

void DriveSettings::setUnderVoltageError(uint16_t underVoltageError) {
	this->underVoltageError = underVoltageError;
}

uint16_t DriveSettings::getUnderVoltageWarning() const {
	return underVoltageWarning;
}

void DriveSettings::setUnderVoltageWarning(
		uint16_t underVoltageWarning) {
	this->underVoltageWarning = underVoltageWarning;
}






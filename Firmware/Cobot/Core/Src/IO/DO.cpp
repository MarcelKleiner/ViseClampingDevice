/*
 * DO.cpp
 *
 *  Created on: Oct 30, 2022
 *      Author: marce
 */

#include "DO.h"
#include "../Tools/Delay.h"

DigitalOut::DigitalOut(GPIO_TypeDef* GPIOx_N, uint16_t GPIO_Pin_N, GPIO_TypeDef* GPIOx_P, uint16_t GPIO_Pin_P){
	this->GPIO_Pin_N = GPIO_Pin_N;
	this->GPIOx_N = GPIOx_N;
	this->GPIO_Pin_P = GPIO_Pin_P;
	this->GPIOx_P = GPIOx_P;
}

void DigitalOut::Set() {
	//P set, N reset
	HAL_GPIO_WritePin(GPIOx_N, GPIO_Pin_N, GPIO_PIN_RESET);
	Delay::DWT_Delay_us(25);
	HAL_GPIO_WritePin(GPIOx_P, GPIO_Pin_P, GPIO_PIN_SET);
	status = true;
}

void DigitalOut::Reset() {
	HAL_GPIO_WritePin(GPIOx_P, GPIO_Pin_P, GPIO_PIN_RESET);
	Delay::DWT_Delay_us(25);
	HAL_GPIO_WritePin(GPIOx_N, GPIO_Pin_N, GPIO_PIN_SET);
	status = false;
}

bool DigitalOut::Status() const {
	return status;
}




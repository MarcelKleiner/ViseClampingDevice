/*
 * LED.cpp
 *
 *  Created on: Oct 30, 2022
 *      Author: marce
 */


#include "LED.h"


LED::LED(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, bool outputInverted) {

	this->GPIO_Pin = GPIO_Pin;
	this->GPIOx = GPIOx;
	this->outputInverted = outputInverted;
}

/*
 * LED ON method
 */
void LED::ON() {
	//check if output is inverted
	if(outputInverted){
		//clear output
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
	}else{
		//write output
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
	}
}

/*
 * LED OFF method
 */
void LED::OFF() {
	//check if output is inverted
	if(outputInverted){
		//clear output
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
	}else{
		//write output
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
	}
}

/*
 * LED Toggle method
 */
void LED::Toggle() {
	HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
}

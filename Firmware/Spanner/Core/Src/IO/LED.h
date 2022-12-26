/*
 * LED.h
 *
 *  Created on: Oct 30, 2022
 *      Author: marce
 */

#ifndef SRC_IO_LED_H_
#define SRC_IO_LED_H_

#include "stdint.h"
#include "gpio.h"

class LED{

public:

	LED(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, bool outputInverted);

	void ON();
	void OFF();
	void Toggle();

private:
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;

	bool outputInverted;
};




#endif /* SRC_IO_LED_H_ */

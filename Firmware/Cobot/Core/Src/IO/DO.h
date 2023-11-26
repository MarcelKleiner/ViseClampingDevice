/*
 * IO.h
 *
 *  Created on: Oct 30, 2022
 *      Author: marce
 */

#ifndef SRC_IO_DO_H_
#define SRC_IO_DO_H_

#include "stdint.h"
#include "gpio.h"


class DigitalOut{

public:
	DigitalOut(GPIO_TypeDef* GPIOx_N, uint16_t GPIO_Pin_N, GPIO_TypeDef* GPIOx_P, uint16_t GPIO_Pin_P);

	void Set();
	void Reset();


	bool Status() const;

private:

	GPIO_TypeDef* GPIOx_N;
	uint16_t GPIO_Pin_N;
	GPIO_TypeDef* GPIOx_P;
	uint16_t GPIO_Pin_P;

	bool status;
};


#endif /* SRC_IO_DO_H_ */

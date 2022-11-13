/*
 * Delay.h
 *
 *  Created on: 30.10.2022
 *      Author: marce
 */

#ifndef SRC_TOOLS_DELAY_H_
#define SRC_TOOLS_DELAY_H_

#include "stdint.h"


class Delay{

public:
	static void DWT_Init(void);
	static void DWT_Delay_us(volatile uint32_t microseconds);

};





#endif /* SRC_TOOLS_DELAY_H_ */

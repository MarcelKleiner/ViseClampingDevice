/*
 * CRC8.h
 *
 *  Created on: 10.12.2022
 *      Author: marce
 */

#ifndef SRC_TOOLS_CRC8_H_
#define SRC_TOOLS_CRC8_H_

#include "main.h"

class CRC8
{
	public:
		//private function declaration
		static uint8_t CRC_8(uint8_t *data, uint8_t length);
};

#endif /* SRC_TOOLS_CRC8_H_ */

/*
 * CRC8.cpp
 *
 *  Created on: 10.12.2022
 *      Author: marce
 */

#include "CRC8.h"

//private function declaration
uint8_t CRC8::CRC_8(uint8_t *data, uint8_t length)
{
	uint8_t crc = 0xff;
	size_t i, j;
	for (i = 0; i < length; i++)
	{
		crc ^= data[i];
		for (j = 0; j < 8; j++)
		{
			if ((crc & 0x80) != 0)
				crc = (uint8_t) ((crc << 1) ^ 0x31);
			else
				crc <<= 1;
		}
	}
	return crc;
}


/*
 * TypeConverter.h
 *
 *  Created on: 11.12.2022
 *      Author: marce
 */

#ifndef SRC_TOOLS_TYPECONVERTER_H_
#define SRC_TOOLS_TYPECONVERTER_H_


/*Systemdefinierte Includs*/
#include "stm32l4xx_hal.h"
#include <stdint.h>


class TypeConverter {
public:
	static uint16_t floatToUint(float data);
	static float  UintToFloat(uint16_t data);

	static float Uint642Float(uint64_t data);
	static uint64_t Float2Uint64_t(float data);

	static float byteToFloat16(uint8_t* byteArray);
	static void floatToByte(uint8_t *byteArray, float data, uint8_t arraySize);

	static void intToByte(uint8_t *byteArray, int data, uint8_t arraySize, uint8_t offset);

	static void uint16ToByte(uint8_t* byteArray, uint16_t data, uint8_t arraySize);
	static uint16_t byteToUint16(uint8_t *byteArray, uint8_t offset);

	static int16_t byteToInt16(uint8_t* byteArray);
	static int32_t byteToInt32(uint8_t* byteArray);
	static int32_t byteToInt32(uint8_t* byteArray, uint8_t offset);

	static uint64_t byte2Uint32(uint8_t* byteArray);
	static void uint32ToByte(uint8_t *byteArray, uint64_t data);

};



#endif /* SRC_TOOLS_TYPECONVERTER_H_ */

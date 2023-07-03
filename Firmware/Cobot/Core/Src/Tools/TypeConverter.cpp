/*
 * TypCasting.cpp
 *
 *  Created on: 13.02.2020
 *      Author: marcel.kleiner
 */

#include "TypeConverter.h"



/*
 * Konvertiert ein float wert in ein uint16_t
 * Bsp: 34.90 -> 3490
 *
 * @param zu konvertierender float wert
 * @return konvertierter uint16_t wert
 */
uint16_t TypeConverter::floatToUint(float data) {
	return ((int16_t) (data * 100));
}

/*
 * Konvertiert ein uint16_t wert in ein float
 * Bsp: 3490 -> 34.90
 *
 * @param zu konvertierender uint16_t wert
 * @param konvertierter float wert
 */
float TypeConverter::UintToFloat(uint16_t data) {
	return (((float) data) / 100);
}

float TypeConverter::Uint642Float(uint64_t data){
	return (((float) data) / 100);
}

uint64_t TypeConverter::Float2Uint64_t(float data){
	return (uint64_t)(data*100);
}

float TypeConverter::byteToFloat16(uint8_t* byteArray) {
    int16_t byte_1 = byteArray[0];
    int16_t byte_2 = byteArray[1]<<8;
    return (float)(byte_1+byte_2)/100;
}


void TypeConverter::floatToByte(uint8_t *byteArray, float data, uint8_t arraySize){
    int32_t idata = data*100;
    for(int byteCounter = 0; byteCounter<arraySize; byteCounter++){
        byteArray[byteCounter] = idata>>(8*(byteCounter));
    }
}



/*
 * Speicher ein int Wert in ein byte Array
 *
 * @param *byteArray: Array in dem der aufgesplitete int gespeichert werden soll.
 * @param data: das aufzusplitende int
 * @param arraySize: gr�sse des byteArray
 *
 * @return none
 */
void TypeConverter::intToByte(uint8_t *byteArray, int data, uint8_t arraySize, uint8_t offset) {
    for(int byteCounter = offset; byteCounter<arraySize; byteCounter++){
        byteArray[byteCounter] = data>>(8*(byteCounter));
    }
}

/*
 * konvertiert ein byteArray (l�nge 2) in ein int16
 *
 * @param *byteArray: das zu konvertierende byteArray
 *
 * @return int16 zusammengesetzt aus dem byteArray
 */
int16_t TypeConverter::byteToInt16(uint8_t *byteArray) {
	int16_t byte1 = byteArray[0];
	int16_t byte2 = byteArray[1]<<8;
	return(byte1 + byte2);
}




void TypeConverter::uint16ToByte(uint8_t* byteArray, uint16_t data, uint8_t offset){
	byteArray[offset] = data;
	byteArray[offset+1] = data>>8;
}

uint16_t TypeConverter::byteToUint16(uint8_t* byteArray, uint8_t offset){
	uint16_t byte1 = byteArray[offset];
	uint16_t byte2 = byteArray[offset+1]<<8;
	return(byte1 + byte2);
}





uint64_t TypeConverter::byte2Uint32(uint8_t* byteArray){
	uint64_t byte1 = byteArray[0];
	uint64_t byte2 = byteArray[1]<<8;
	uint64_t byte3 = byteArray[1]<<16;
	uint64_t byte4 = byteArray[1]<<24;

	return(byte1 + byte2 + byte3 + byte4);
}

void TypeConverter::uint32ToByte(uint8_t *byteArray, uint64_t data){
	byteArray[0] = data;
	byteArray[1] = data>>8;
	byteArray[2] = data>>16;
	byteArray[3] = data>>24;
}




/*
 * konvertiert ein byteArray (l�nge 4) in ein int32
 *
 * @param *byteArray: das zu konvertierende byteArray
 *
 * @return int32 zusammengesetzt aus dem byteArray
 */
int32_t TypeConverter::byteToInt32(uint8_t *byteArray) {
	int32_t byte1 = byteArray[0];
	int32_t byte2 = byteArray[1] << 8;
	int32_t byte3 = byteArray[2] << 16;
	int32_t byte4 = byteArray[3] << 24;

	return (byte1 + byte2 + byte3 + byte4);
}


int32_t TypeConverter::byteToInt32(uint8_t* byteArray, uint8_t offset){

	int32_t byte1 = byteArray[offset];
	int32_t byte2 = byteArray[offset+1] << 8;
	int32_t byte3 = byteArray[offset+2] << 16;
	int32_t byte4 = byteArray[offset+3] << 24;

	return (byte1 + byte2 + byte3 + byte4);
}



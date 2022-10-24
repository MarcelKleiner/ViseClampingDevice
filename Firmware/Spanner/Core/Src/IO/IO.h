/*
 * IO.h
 *
 *  Created on: 23.10.2022
 *      Author: marce
 */

#include "main.h"

#ifndef SRC_IO_IO_H_
#define SRC_IO_IO_H_



#define EXT_LED_SET 		HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_SET)
#define EXT_LED_RESET 		HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_RESET)

#define LED_SET 			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET)
#define LED_RESET 			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET)

#define POWER_FET_SET 	 	HAL_GPIO_WritePin(POWER_SWITCH_GPIO_Port, POWER_SWITCH_Pin, GPIO_PIN_SET)
#define POWER_FET_RESET 	HAL_GPIO_WritePin(POWER_SWITCH_GPIO_Port, POWER_SWITCH_Pin, GPIO_PIN_RESET)

#define IS_EXT_SWITCH		HAL_GPIO_ReadPin(SW_EXT_GPIO_Port, SW_EXT_Pin)


class IO{

public:
	uint16_t getCurrent() const;
	void setCurrent(uint16_t current);

	uint16_t getVoltage() const;
	void setVoltage(uint16_t voltage);

private:

uint16_t current;
uint16_t voltage;

};



#endif /* SRC_IO_IO_H_ */

#include "gpio.h"

#ifndef SRC_APPMAIN_DEFINES_H_
#define SRC_APPMAIN_DEFINES_H_

constexpr auto  GEAR_RATIO = 1;
constexpr auto  CURRENT_2_TORQUE = 1;

constexpr uint8_t SEND_SETTINGS = 0x11;
constexpr uint8_t SEND_STATUS = 0x13;

constexpr uint8_t RECEIVE_STATUS_REQUEST = 0x03;
constexpr uint8_t RECEIVE_SETTINGS_REQUEST = 0x04;

constexpr uint8_t RECEIVE_SETTINGS = 0x01;
constexpr uint8_t RECEIVE_COMMAND = 0x02;


//Address
constexpr auto  CLOSE_ADDR = 0x01;
constexpr auto  OPEN_ADDR = 0x02;
constexpr auto  TEACH_ADDR = 0x03;
constexpr auto  RESET_ADDR = 0x04;
constexpr auto  ENABLE_ADDR = 0x05;

constexpr auto  STOP_ADDR = 0x07;
constexpr auto  ERROR_ADDR = 0x08;
constexpr auto  STATUS_ADDR = 0x09;

constexpr auto  TEACH_TORQUE_ADDR = 0x10;
constexpr auto  TEACH_SPEED_ADDR = 0x11;

constexpr auto  CLAMPING_TORQUE_ADDR = 0x12;
constexpr auto  CLAMPING_SPEED_ADDR = 0x13;

constexpr auto  SELF_SHUTDOWN_DELAY_ADDR = 0x14;
constexpr auto  IN_POS_DIFF_ADDR = 0x15;
constexpr auto  OPENING_DISTANCE_ADDR = 0x16;

constexpr auto  UNDERVOLTAGE_WARNING_ADDR = 0x17;
constexpr auto  UNDERVOLTAGE_ERROR_ADDR = 0x18;

constexpr auto  OVER_CURRENT_WARNING_ADDR = 0x19;
constexpr auto  OVER_CURRENT_ERROR_ADDR = 0x1A;

constexpr auto  DEVICE_ADDRESS_ADDR = 0x20;


constexpr auto  RCV_STATUS = 0xAA;
#define EXT_LED_SET 		HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_SET)
#define EXT_LED_RESET 		HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_RESET)

#define LED_SET 			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET)
#define LED_RESET 			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET)

#define POWER_FET_SET 	 	HAL_GPIO_WritePin(POWER_SWITCH_GPIO_Port, POWER_SWITCH_Pin, GPIO_PIN_SET)
#define POWER_FET_RESET 	HAL_GPIO_WritePin(POWER_SWITCH_GPIO_Port, POWER_SWITCH_Pin, GPIO_PIN_RESET)

#define IS_EXT_SWITCH		HAL_GPIO_ReadPin(SW_EXT_GPIO_Port, SW_EXT_Pin)

//general settings

constexpr auto DIRECTION_IN = 3200;
constexpr auto DIRECTION_OUT = 6400;



#endif /* SRC_APPMAIN_DEFINES_H_ */

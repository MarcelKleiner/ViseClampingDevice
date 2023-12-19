#include "gpio.h"

#ifndef SRC_APPMAIN_DEFINES_H_
#define SRC_APPMAIN_DEFINES_H_

constexpr auto  GEAR_RATIO = 1;
constexpr auto  CURRENT_2_TORQUE = 1;

constexpr uint8_t SEND_SETTINGS = 0x11;
constexpr uint8_t SEND_COMMAND = 0x12; //should never be used 
constexpr uint8_t SEND_STATUS = 0x13;

constexpr uint8_t RECEIVE_STATUS_REQUEST = 0x05;
constexpr uint8_t RECEIVE_SETTINGS_REQUEST = 0x06;
constexpr uint8_t RECEIVE_COMMAND_REQUEST = 0x07;

constexpr uint8_t RECEIVE_SETTINGS = 0x01;
constexpr uint8_t RECEIVE_COMMAND = 0x02;


//Address
constexpr auto  CLOSE_ADDR = 0x01;
constexpr auto  OPEN_ADDR = 0x02;
constexpr auto  TEACH_ADDR = 0x03;
constexpr auto  RESET_ADDR = 0x04;
constexpr auto  ENABLE_ADDR = 0x05;
constexpr auto  STOP_ADDR = 0x07;
constexpr uint8_t READ_ALL_STATUS = 0x08;
constexpr auto  STATUS_ADDR = 0x09;


constexpr auto  ERROR_ADDR = 0x28;

constexpr auto TEACH_TORQUE_ADDR = 0x29;
constexpr auto TEACH_SPEED_ADDR = 0x2A;
constexpr auto CLAMPING_TORQUE_ADDR = 0x2B;
constexpr auto CLAMPING_SPEED_ADDR = 0x2C;
constexpr auto SELF_SHUTDOWN_DELAY_ADDR = 0x2D;
constexpr auto IN_POS_DIFF_ADDR = 0x2E;
constexpr auto OPENING_DISTANCE_ADDR = 0x2F;
constexpr auto UNDERVOLTAGE_WARNING_ADDR = 0x30;
constexpr auto UNDERVOLTAGE_ERROR_ADDR = 0x31;
constexpr auto OVER_CURRENT_WARNING_ADDR = 0x32;
constexpr auto OVER_CURRENT_ERROR_ADDR = 0x33;
constexpr auto DEVICE_ADDRESS_ADDR = 0x34;
constexpr auto SAVE_SETTINGS_ADDR = 0x55;
constexpr auto RESET_DEFAULT_SETTINGS_ADDR = 0x56;


constexpr auto  RCV_STATUS = 0xAA;
#define EXT_LED_SET 		HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_SET)
#define EXT_LED_RESET 		HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_RESET)

#define LED_SET 			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET)
#define LED_RESET 			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET)

#define POWER_FET_SET 	 	HAL_GPIO_WritePin(POWER_SWITCH_GPIO_Port, POWER_SWITCH_Pin, GPIO_PIN_SET)
#define POWER_FET_RESET 	HAL_GPIO_WritePin(POWER_SWITCH_GPIO_Port, POWER_SWITCH_Pin, GPIO_PIN_RESET)

#define IS_EXT_SWITCH		HAL_GPIO_ReadPin(SW_EXT_GPIO_Port, SW_EXT_Pin)

//general settings

constexpr auto DIRECTION_IN = 85000; //3200
constexpr auto DIRECTION_OUT = 118000; //6400



#endif /* SRC_APPMAIN_DEFINES_H_ */

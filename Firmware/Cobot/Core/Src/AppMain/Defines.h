#include "gpio.h"


#ifndef SRC_APPMAIN_DEFINES_H_
#define SRC_APPMAIN_DEFINES_H_

//constexpr auto SEND_SETTINGS = 0x01;
//constexpr auto SEND_COMMAND = 0x02;
//constexpr auto SEND_STATUS = 0x03;
//
//constexpr auto GET_SETTINGS = 0x11;
//constexpr auto GET_COMMAND = 0x12;
//constexpr auto GET_STATUS = 0x13;


constexpr uint8_t GET_SETTINGS_TO_TRANSMIT = 0x21;
constexpr uint8_t GET_COMMAND_TO_TRANSMIT = 0x22;
constexpr uint8_t GET_STATUS_TO_TRANSMIT = 0x23;

constexpr uint8_t SET_SETTINGS_FROM_RECEIVE = 0x31;
constexpr uint8_t SET_COMMAND_FROM_RECEIVE = 0x32;
constexpr uint8_t SET_STATUS_FROM_RECEIVE = 0x33;



constexpr auto ADC_UPDATE_TIME = 2;
constexpr auto IO_UPDATE_TIME = 15;
constexpr auto ERROR_UPDATE_TIME = 250;
constexpr auto COM_UPDATE_TIME = 200;
constexpr auto LED_UPDATE_TIME = 500;
constexpr auto RESET_UPDATE_TIME = 300;
constexpr auto SAVE_UPDATE_TIME = 1000;

constexpr auto IO_TIMEOUT = 100;

constexpr auto CLOSE_ADDR = 0x01;
constexpr auto OPEN_ADDR = 0x02;
constexpr auto TEACH_ADDR = 0x03;
constexpr auto RESET_ADDR = 0x04;
constexpr auto ENABLE_ADDR = 0x05;
constexpr auto DISABLE_ADDR = 0x06;
constexpr auto STOP_ADDR = 0x07;

constexpr auto SELF_RESET_ADDR = 0x11;

constexpr auto ERROR_ADDR = 0x28;
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

//#define MAX_ADDR					0x7F

constexpr auto TEACH_TORQUE_CHANGE                = 0x0001;
constexpr auto TEACH_SPEED_CHANGE                 = 0x0002;
constexpr auto CLAMPING_TORQUE_CHANGE             = 0x0004;
constexpr auto CLAMPING_SPEED_CHANGE              = 0x0008;
constexpr auto SELF_SHUTDOWN_DELAY_CHANGE         = 0x0010;
constexpr auto IN_POS_DIFF_CHANGE                 = 0x0020;
constexpr auto OPENING_DISTANCE_CHANGE            = 0x0040;
constexpr auto UNDERVOLTAGE_WARNING_CHANGE        = 0x0080;
constexpr auto UNDERVOLTAGE_ERROR_CHANGE          = 0x0100;
constexpr auto OVER_CURRENT_WARNING_CHANGE        = 0x0200;
constexpr auto OVER_CURRENT_ERROR_CHANGE          = 0x0400;
constexpr auto OVER_CURRENT_TIME_TH_CHANGE        = 0x0800;

constexpr auto CLOSE_CHANGE = 0x01;
constexpr auto OPEN_CHANGE = 0x02;
constexpr auto TEACH_CHANGE = 0x04;
constexpr auto RESET_CHANGE = 0x08;
constexpr auto ENABLE_CHANGE = 0x10;
constexpr auto DISABLE_CHANGE = 0x20;
constexpr auto STOP_CHANGE = 0x40;
constexpr auto ERROR_CHANGE = 0x80;


constexpr auto CONNECTION_LOST_TIMEOUT = 10; //NUMBER OF LOST PACKAGES


<<<<<<< HEAD
#define CLOSE_CHANGE					0x01
#define OPEN_CHANGE						0x02
#define TEACH_CHANGE					0x04
#define RESET_CHANGE					0x08
#define ENABLE_CHANGE					0x10
#define DISABLE_CHANGE					0x20
#define STOP_CHANGE						0x40
#define ERROR_CHANGE					0x80


#define ADC_UPDATE_TIME             	2
#define IO_UPDATE_TIME  	        	15
#define ERROR_UPDATE_TIME           	100
#define LED_UPDATE_TIME             	500
#define COM_UPDATE_TIME					600
#define SAVE_UPDATE_TIME            	1000

#define IO_TIMEOUT						100


#define CONFIG_WRITE 	HAL_GPIO_ReadPin(DI_1_GPIO_Port, DI_1_Pin) == GPIO_PIN_SET
#define CONFIG_ADDR_1 	HAL_GPIO_ReadPin(DI_2_GPIO_Port, DI_2_Pin) == GPIO_PIN_SET
#define CONFIG_ADDR_2 	HAL_GPIO_ReadPin(DI_3_GPIO_Port, DI_3_Pin) == GPIO_PIN_SET
#define CONFIG_ADDR_3 	HAL_GPIO_ReadPin(DI_4_GPIO_Port, DI_4_Pin) == GPIO_PIN_SET
#define CONFIG_ADDR_4 	HAL_GPIO_ReadPin(DI_5_GPIO_Port, DI_5_Pin) == GPIO_PIN_SET
#define CONFIG_ADDR_5 	HAL_GPIO_ReadPin(DI_6_GPIO_Port, DI_6_Pin) == GPIO_PIN_SET
#define CONFIG_ADDR_6 	HAL_GPIO_ReadPin(DI_7_GPIO_Port, DI_7_Pin) == GPIO_PIN_SET
#define CONFIG_ADDR_7 	HAL_GPIO_ReadPin(DI_8_GPIO_Port, DI_8_Pin) == GPIO_PIN_SET
=======
#define IS_CONFIG_WRITE_SET 	HAL_GPIO_ReadPin(DI_1_GPIO_Port, DI_1_Pin) == GPIO_PIN_SET
#define IS_IO1_SET 	HAL_GPIO_ReadPin(DI_2_GPIO_Port, DI_2_Pin) == GPIO_PIN_SET
#define IS_IO2_SET 	HAL_GPIO_ReadPin(DI_3_GPIO_Port, DI_3_Pin) == GPIO_PIN_SET
#define IS_IO3_SET 	HAL_GPIO_ReadPin(DI_4_GPIO_Port, DI_4_Pin) == GPIO_PIN_SET
#define IS_IO4_SET 	HAL_GPIO_ReadPin(DI_5_GPIO_Port, DI_5_Pin) == GPIO_PIN_SET
#define IS_IO5_SET 	HAL_GPIO_ReadPin(DI_6_GPIO_Port, DI_6_Pin) == GPIO_PIN_SET
#define IS_IO6_SET 	HAL_GPIO_ReadPin(DI_7_GPIO_Port, DI_7_Pin) == GPIO_PIN_SET
#define IS_IO7_SET 	HAL_GPIO_ReadPin(DI_8_GPIO_Port, DI_8_Pin) == GPIO_PIN_SET
>>>>>>> origin/main

#endif /* SRC_APPMAIN_DEFINES_H_ */

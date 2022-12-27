/*
 * Defines.h
 *
 *  Created on: Oct 23, 2022
 *      Author: marce
 */

#ifndef SRC_APPMAIN_DEFINES_H_
#define SRC_APPMAIN_DEFINES_H_

#define GEAR_RATIO			1
#define TORQUE_2_CURRENT	1



#define SEND_SETTINGS		0x01
#define SEND_COMMAND		0x02
#define SEND_STATUS			0x03

#define GET_SETTINGS		0x11
#define GET_COMMAND			0x12
#define GET_STATUS			0x13

//Address
#define CLOSE_ADDR					0x01
#define OPEN_ADDR					0x02
#define TEACH_ADDR					0x03
#define RESET_ADDR					0x04
#define ENABLE_ADDR					0x05
#define DISABLE_ADDR				0x06
#define STOP_ADDR					0x07
#define ERROR_ADDR					0x08
#define STATUS_ADDR					0x09

#define TEACH_TORQUE_ADDR			0x10
#define TEACH_SPEED_ADDR			0x11

#define CLAMPING_TORQUE_ADDR		0x12
#define CLAMPING_SPEED_ADDR			0x13

#define SELF_SHUTDOWN_DELAY_ADDR	0x14
#define IN_POS_DIFF_ADDR			0x15
#define OPENING_DISTANCE_ADDR		0x16

#define UNDERVOLTAGE_WARNING_ADDR	0x17
#define UNDERVOLTAGE_ERROR_ADDR		0x18

#define OVER_CURRENT_WARNING_ADDR	0x19
#define OVER_CURRENT_ERROR_ADDR		0x1A

#define DEVICE_ADDRESS_ADDR			0x20



#define RCV_STATUS			0xAA

#endif /* SRC_APPMAIN_DEFINES_H_ */

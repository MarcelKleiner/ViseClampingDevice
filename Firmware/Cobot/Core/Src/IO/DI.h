/*
 * DI.h
 *
 *  Created on: Nov 5, 2022
 *      Author: marce
 */

#ifndef SRC_IO_DI_H_
#define SRC_IO_DI_H_

#include "gpio.h"
#include "stdint.h"
#include "../Tools/Queue.h"
#include "../Settings/DriveSettings.h"
#include "../Settings/"

#define BUFFER_SIZE		10

#define CONFIG_WRITE 	HAL_GPIO_ReadPin(DI_1_GPIO_Port, DI_1_Pin) == GPIO_PIN_SET
#define CONFIG_ADDR_1 	HAL_GPIO_ReadPin(DI_2_GPIO_Port, DI_2_Pin) == GPIO_PIN_SET
#define CONFIG_ADDR_2 	HAL_GPIO_ReadPin(DI_3_GPIO_Port, DI_3_Pin) == GPIO_PIN_SET
#define CONFIG_ADDR_3 	HAL_GPIO_ReadPin(DI_4_GPIO_Port, DI_4_Pin) == GPIO_PIN_SET
#define CONFIG_ADDR_4 	HAL_GPIO_ReadPin(DI_5_GPIO_Port, DI_5_Pin) == GPIO_PIN_SET
#define CONFIG_ADDR_5 	HAL_GPIO_ReadPin(DI_6_GPIO_Port, DI_6_Pin) == GPIO_PIN_SET
#define CONFIG_ADDR_6 	HAL_GPIO_ReadPin(DI_7_GPIO_Port, DI_7_Pin) == GPIO_PIN_SET
#define CONFIG_ADDR_7 	HAL_GPIO_ReadPin(DI_8_GPIO_Port, DI_8_Pin) == GPIO_PIN_SET

//define addresses

#define CLOSE					0x01
#define OPEN					0x02
#define TEACH					0x03
#define RESET					0x04
#define ENABLE					0x05
#define DISABLE					0x06
#define STOP					0x07

#define TEACH_TORQUE			0x10
#define TEACH_SPEED				0x11

#define CLAMPING_TORQUE			0x12
#define CLAMPING_SPEED			0x13

#define SELF_SHUTDOWN_DELAY		0x14
#define IN_POS_DIFF				0x15
#define OPENING_DISTANCE		0x16

#define UNDERVOLTAGE_WARNING	0x17
#define UNDERVOLTAGE_ERROR		0x18

#define OVER_CURRENT_WARNING	0x19
#define OVER_CURRENT_ERROR		0x1A




class DigitalIN{

public:



	void DigitalIN(DriveSettings *driveSettings, DriveStatus *driveStatus);

	uint8_t GetData();
	bool IsDataReady();
	bool IsQueueOverflow();
	void CheckAddress();
	void CheckData();

private:

	bool configeWriteStatus = false;
	bool previousConfigeWriteStatus = false;

	bool isAddressReceived = false;

	uint8_t expectedDataSize;
	uint8_t receivedAddress;


	Queue queue = Queue();

	DriveSettings *driveSettings;
	DriveStatus *driveStatus;
};





#endif /* SRC_IO_DI_H_ */

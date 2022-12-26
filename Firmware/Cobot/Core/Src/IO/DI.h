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
#include "../Status/DriveStatus.h"
#include "../Status/DriveCommand.h"
#include "DO.h"


#define READ_TIMEOUT		100		//timeout = READ_TIMEOUT * 15ms
#define TEMP_BUFFER_SIZE 	2

#define BUFFER_SIZE			10

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
#define ERROR					0x08

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

#define DEVICE_ADDRESS			0x20



#define TEACH_TORQUE_CHANGE				0x0001
#define TEACH_SPEED_CHANGE				0x0002

#define CLAMPING_TORQUE_CHANGE			0x0004
#define CLAMPING_SPEED_CHANGE			0x0008

#define SELF_SHUTDOWN_DELAY_CHANGE		0x0010
#define IN_POS_DIFF_CHANGE				0x0020
#define OPENING_DISTANCE_CHANGE			0x0040

#define UNDERVOLTAGE_WARNING_CHANGE		0x0080
#define UNDERVOLTAGE_ERROR_CHANGE		0x0100

#define OVER_CURRENT_WARNING_CHANGE		0x0200
#define OVER_CURRENT_ERROR_CHANGE		0x0400


class Digitll_IN_OUT{

public:

	Digitll_IN_OUT(DriveSettings *driveSettings, DriveStatus *driveStatus, DriveCommand *driveCommand);

	void Read();
	bool CheckAddress(uint8_t data);
	void CheckData();

	uint16_t isSettingsChanged();
	void ResetSettingsChanged(uint16_t bit);
	bool isStatusChanged();



	void WriteOutput(uint8_t data);

private:

	DigitalOut Out1 = DigitalOut(DI_OUT_1_N_GPIO_Port, DI_OUT_1_N_Pin, DI_OUT_1_P_GPIO_Port, DI_OUT_1_P_Pin);
	DigitalOut Out2 = DigitalOut(DI_OUT_2_N_GPIO_Port, DI_OUT_2_N_Pin, DI_OUT_2_P_GPIO_Port, DI_OUT_2_P_Pin);
	DigitalOut Out3 = DigitalOut(DI_OUT_3_N_GPIO_Port, DI_OUT_3_N_Pin, DI_OUT_3_P_GPIO_Port, DI_OUT_3_P_Pin);
	DigitalOut Out4 = DigitalOut(DI_OUT_4_N_GPIO_Port, DI_OUT_4_N_Pin, DI_OUT_4_P_GPIO_Port, DI_OUT_4_P_Pin);
	DigitalOut Out5 = DigitalOut(DI_OUT_5_N_GPIO_Port, DI_OUT_5_N_Pin, DI_OUT_5_P_GPIO_Port, DI_OUT_5_P_Pin);
	DigitalOut Out6 = DigitalOut(DI_OUT_6_N_GPIO_Port, DI_OUT_6_N_Pin, DI_OUT_6_P_GPIO_Port, DI_OUT_6_P_Pin);
	DigitalOut Out7 = DigitalOut(DI_OUT_7_N_GPIO_Port, DI_OUT_7_N_Pin, DI_OUT_7_P_GPIO_Port, DI_OUT_7_P_Pin);
	DigitalOut Out8 = DigitalOut(DI_OUT_8_N_GPIO_Port, DI_OUT_8_N_Pin, DI_OUT_8_P_GPIO_Port, DI_OUT_8_P_Pin);




	bool configeWriteStatus = false;
	bool previousConfigeWriteStatus = false;

	bool isAddressReceived = false;

	uint8_t expectedDataSize;
	uint8_t receivedAddress;

	uint8_t timeoutCounter;
	uint8_t dataTemp[TEMP_BUFFER_SIZE];
	uint16_t value;

	Queue queue = Queue();

	DriveSettings *driveSettings;
	DriveStatus *driveStatus;
	DriveCommand *driveCommand;


	uint16_t settingsChangedReg;
	bool statusChangedReg;

};





#endif /* SRC_IO_DI_H_ */

/*
 * IOCom.h
 *
 *  Created on: 26.12.2022
 *      Author: marce
 */

#ifndef SRC_COM_IOCOM_H_
#define SRC_COM_IOCOM_H_

#include "BaseCOM.h"
#include "ICom.h"
#include "../Status/DriveCommand.h"
#include "../Status/DriveStatus.h"
#include "../Settings/DriveSettings.h"
#include "../IO/DO.h"

class IOCom: public ICom, public BaseCOM
{
	public:
		IOCom(DriveStatus *driveStatus, DriveSettings *driveSettings,
				DriveCommand *driveCommand) :
				BaseCOM(driveStatus, driveSettings, driveCommand)
		{
			this->driveStatus = driveStatus;
		}

		virtual bool Transmitt(uint8_t *data = NULL, uint8_t length = 0) override;
		virtual bool Receive(uint8_t *data = NULL, uint8_t length = 0) override;


	private:

		bool CheckData();


		DigitalOut Out1 = DigitalOut(DI_OUT_1_N_GPIO_Port, DI_OUT_1_N_Pin, DI_OUT_1_P_GPIO_Port, DI_OUT_1_P_Pin);
		DigitalOut Out2 = DigitalOut(DI_OUT_2_N_GPIO_Port, DI_OUT_2_N_Pin, DI_OUT_2_P_GPIO_Port, DI_OUT_2_P_Pin);
		DigitalOut Out3 = DigitalOut(DI_OUT_3_N_GPIO_Port, DI_OUT_3_N_Pin, DI_OUT_3_P_GPIO_Port, DI_OUT_3_P_Pin);
		DigitalOut Out4 = DigitalOut(DI_OUT_4_N_GPIO_Port, DI_OUT_4_N_Pin, DI_OUT_4_P_GPIO_Port, DI_OUT_4_P_Pin);
		DigitalOut Out5 = DigitalOut(DI_OUT_5_N_GPIO_Port, DI_OUT_5_N_Pin, DI_OUT_5_P_GPIO_Port, DI_OUT_5_P_Pin);
		DigitalOut Out6 = DigitalOut(DI_OUT_6_N_GPIO_Port, DI_OUT_6_N_Pin, DI_OUT_6_P_GPIO_Port, DI_OUT_6_P_Pin);
		DigitalOut Out7 = DigitalOut(DI_OUT_7_N_GPIO_Port, DI_OUT_7_N_Pin, DI_OUT_7_P_GPIO_Port, DI_OUT_7_P_Pin);
		DigitalOut Out8 = DigitalOut(DI_OUT_8_N_GPIO_Port, DI_OUT_8_N_Pin, DI_OUT_8_P_GPIO_Port, DI_OUT_8_P_Pin);


		uint8_t counter = 0;
		uint8_t reg;
		uint8_t command;
		uint16_t payload;



		bool configeWriteStatus = false;
		bool previousConfigeWriteStatus = false;



		DriveStatus* driveStatus;
};

#endif /* SRC_COM_IOCOM_H_ */

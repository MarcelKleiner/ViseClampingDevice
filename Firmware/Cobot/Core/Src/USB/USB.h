/*
 * USB.h
 *
 *  Created on: 09.12.2022
 *      Author: marce
 */

#ifndef SRC_USB_USB_H_
#define SRC_USB_USB_H_


#include "../Settings/DriveSettings.h"
#include "../Status/DriveStatus.h"
#include "../IO/DI.h"
#include "stdio.h"


class USBCom
{

	public:

		USBCom(DriveSettings *driveSettings, DriveStatus *driveStatus);
		bool USB_Transmit(uint8_t *data, uint8_t length);
		void USB_Receive(uint8_t *data, uint32_t length);



	private:

		uint8_t data;

		DriveSettings *driveSettings;
		DriveStatus *driveStatus;

};



#endif /* SRC_USB_USB_H_ */

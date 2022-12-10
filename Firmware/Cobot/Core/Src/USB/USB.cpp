/*
 * USB.cpp
 *
 *  Created on: 09.12.2022
 *      Author: marce
 */
#include "USB.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

USBCom::USBCom(DriveSettings *driveSettings, DriveStatus *driveStatus)
{
	this->driveSettings = driveSettings;
	this->driveStatus = driveStatus;
}

bool USBCom::USB_Transmit(uint8_t *data, uint8_t length)
{
	uint16_t counter = 0;
	while (CDC_Transmit_FS((uint8_t*) data, length) != USBD_OK)
	{
		counter++;
		if (counter >= 1000)
		{
			return false;	//Trasmit faild
		}
	}
	return true;	//Transmit successful
}

void USBCom::USB_Receive(uint8_t *data, uint32_t length)
{

	uint8_t response[2];

	if(length == 0){
		return;
	}

	switch (data[0])
	{
		case CLOSE:
		case OPEN:
		case TEACH:
		case RESET:
		case ENABLE:
		case DISABLE:
		case STOP:
		case TEACH_TORQUE:
		case TEACH_SPEED:
		case CLAMPING_TORQUE:
		case CLAMPING_SPEED:
		case SELF_SHUTDOWN_DELAY:
		case IN_POS_DIFF:
		case OPENING_DISTANCE:
		case UNDERVOLTAGE_WARNING:
		case UNDERVOLTAGE_ERROR:
		case OVER_CURRENT_WARNING:
		case OVER_CURRENT_ERROR:
			break;
		default:
			response[0] = 0x1F;
			response[1] = 0xAA;
			USB_Transmit(response, 2);
			break;
	}

}

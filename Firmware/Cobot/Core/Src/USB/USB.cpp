/*
 * USB.cpp
 *
 *  Created on: 09.12.2022
 *      Author: marce
 */
#include "USB.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "../Tools/TypeConverter.h"

USBCom::USBCom(DriveSettings *driveSettings, DriveStatus *driveStatus,
		DriveCommand *driveCommand)
{
	this->driveSettings = driveSettings;
	this->driveStatus = driveStatus;
	this->driveCommand = driveCommand;
}

bool USBCom::USB_Transmit(uint8_t *data, uint8_t length)
{
	uint16_t counter = 0;
	while (CDC_Transmit_FS((uint8_t*) data, length) != USBD_OK)
	{
		counter++;
		if (counter >= 1000)
		{
			//ToDo USB Error
			return false;	//Trasmit faild
		}
	}
	return true;	//Transmit successful
}

void USBCom::USB_Receive(uint8_t *data, uint32_t length)
{



	if (length == 0)
	{
		return;
	}

	uint8_t data2send[5];
	uint16_t convertedData = 0;
	uint8_t readWrite = data[0];
	uint8_t command = data[1];

	if (readWrite)
	{
		//usb read
		data2send[0] = 0x1D;	//random preamble
		data2send[1] = command;
		switch (command)
		{
			case CLOSE:
				data2send[2] = driveStatus->isClose();
				break;
			case OPEN:
				data2send[2] = driveStatus->isOpen();
				break;
			case TEACH:
				data2send[2] = driveStatus->isTeach();
				break;
			case RESET:
				data2send[2] = driveStatus->isReset();
				break;
			case ENABLE:
				data2send[2] = driveStatus->isEnable();
				break;
			case DISABLE:
				data2send[2] = driveStatus->isDisable();
				break;
			case STOP:
				data2send[2] = driveStatus->isStop();
				break;
			case TEACH_TORQUE:
				TypeConverter::uint16ToByte(data2send,
						driveSettings->getTeachTroque(), 2);
				break;
			case TEACH_SPEED:
				TypeConverter::uint16ToByte(data2send,
						driveSettings->getTeachSpeed(), 2);
				break;
			case CLAMPING_TORQUE:
				TypeConverter::uint16ToByte(data2send,
						driveSettings->getClampingTorque(), 2);
				break;
			case CLAMPING_SPEED:
				TypeConverter::uint16ToByte(data2send,
						driveSettings->getClampingSpeed(), 2);
				break;
			case SELF_SHUTDOWN_DELAY:
				TypeConverter::uint16ToByte(data2send,
						driveSettings->getSelfShutdownDelay(), 2);
				break;
			case IN_POS_DIFF:
				TypeConverter::uint16ToByte(data2send,
						driveSettings->getInPosDiff(), 2);
			case OPENING_DISTANCE:
				TypeConverter::uint16ToByte(data2send,
						driveSettings->getOpeningDistance(), 2);
				break;
			case UNDERVOLTAGE_WARNING:
				TypeConverter::uint16ToByte(data2send,
						driveSettings->getUnderVoltageWarning(),2);
				break;
			case UNDERVOLTAGE_ERROR:
				TypeConverter::uint16ToByte(data2send,
						driveSettings->getUnderVoltageError(), 2);
				break;
			case OVER_CURRENT_WARNING:
				TypeConverter::uint16ToByte(data2send,
						driveSettings->getOverCurrentWarning(), 2);
				break;
			case OVER_CURRENT_ERROR:
				TypeConverter::uint16ToByte(data2send,
						driveSettings->getOverCurrentError(), 2);
				break;
			case DEVICE_ADDRESS:
				data2send[2] = driveSettings->getDeviceAddress();
				break;
			default:
				data2send[1] = 0x1F;
				data2send[2] = 0xAA;
				break;
		}
	}
	else
	{
		data2send[0] = command;
		//usb write
		switch (command)
		{
			case CLOSE:
				driveStatus->setClose(data[2]);
				break;
			case OPEN:
				driveStatus->setOpen(data[2]);
				break;
			case TEACH:
				driveStatus->setTeach(data[2]);
				break;
			case RESET:
				driveStatus->setReset(data[2]);
				break;
			case ENABLE:
				driveStatus->setEnable(data[2]);
				break;
			case DISABLE:
				driveStatus->setDisable(data[2]);
				break;
			case STOP:
				driveStatus->setStop(data[2]);
				break;
			case TEACH_TORQUE:
				convertedData = TypeConverter::byteToUint16(data, 2);
				driveSettings->setTeachTroque(convertedData);
				break;
			case TEACH_SPEED:
				convertedData = TypeConverter::byteToUint16(data, 2);
				driveSettings->setTeachSpeed(convertedData);
				break;
			case CLAMPING_TORQUE:
				convertedData = TypeConverter::byteToUint16(data, 2);
				driveSettings->setClampingTorque(convertedData);
				break;
			case CLAMPING_SPEED:
				convertedData = TypeConverter::byteToUint16(data, 2);
				driveSettings->setClampingSpeed(convertedData);
				break;
			case SELF_SHUTDOWN_DELAY:
				convertedData = TypeConverter::byteToUint16(data, 2);
				driveSettings->setSelfShutdownDelay(convertedData);
				break;
			case IN_POS_DIFF:
				convertedData = TypeConverter::byteToUint16(data, 2);
				driveSettings->setInPosDiff(convertedData);
				break;
			case OPENING_DISTANCE:
				convertedData = TypeConverter::byteToUint16(data, 2);
				driveSettings->setOpeningDistance(convertedData);
				break;
			case UNDERVOLTAGE_WARNING:
				convertedData = TypeConverter::byteToUint16(data, 2);
				driveSettings->setUnderVoltageWarning(convertedData);
				break;
			case UNDERVOLTAGE_ERROR:
				convertedData = TypeConverter::byteToUint16(data, 2);
				driveSettings->setUnderVoltageError(convertedData);
				break;
			case OVER_CURRENT_WARNING:
				convertedData = TypeConverter::byteToUint16(data, 2);
				driveSettings->setOverCurrentWarning(convertedData);
				break;
			case OVER_CURRENT_ERROR:
				convertedData = TypeConverter::byteToUint16(data, 2);
				driveSettings->setOverCurrentError(convertedData);
				break;
			case DEVICE_ADDRESS:
				driveSettings->setDeviceAddress(data[2]);
			default:
				data2send[0] = 0x1F;
				data2send[1] = 0xAA;
				break;
		}
	}

	data2send[4] = 0x0A;
	USB_Transmit(data2send, 5);
}

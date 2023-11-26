#include "BaseCOM.h"
#include "USBCom.h"
#include "../AppMain/Defines.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

bool USBCom::Transmitt(uint8_t *data, uint8_t length)
{
	if (data == NULL)
	{
		return false;
	}

	uint16_t counter = 0;
	while (CDC_Transmit_FS((uint8_t*) data, length) != USBD_OK)
	{
		counter++;
		if (counter >= 1000)
		{
			//ToDo USB Error
			return false;	//Transmit failed
		}
	}
	return true;	//Transmit successful
}

bool USBCom::Receive(uint8_t *data, uint8_t length)
{
	uint8_t data2send[] = { 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	uint8_t crc = 0;




	//data[0] = 0x1F
	//data[1] = deviceAddress
	//data[2] = command (readCommand, readSettings, readStatus, writeCommand...)
	//data[3] = reg addr (close, open, setTeach...)
	//data[4+5] = Payload
	//data[6] = crc

	if (length >= 5)
	{
		//calculate CRC from received data

		crc = this->CRC8(data, 6);
		if (crc != data[6])
		{
			data[2] = 0;
			driveStatus->setError(DriveStatus::E_CRC_ERROR);
		}


		switch (data[2])
		{
			case SET_SETTINGS_FROM_RECEIVE:
				this->SetSettings(data);
				break;
			case SET_COMMAND_FROM_RECEIVE:
				this->SetCommand(data);
				break;
			case SET_STATUS_FROM_RECEIVE:
				this->SetStatus(data);
				break;
			case GET_SETTINGS_TO_TRANSMIT:
				return Transmitt(this->GetSettings(data[3]), 7);
			case GET_COMMAND_TO_TRANSMIT:
				return Transmitt(this->GetCommand(data[3]), 7);
			case GET_STATUS_TO_TRANSMIT:
				return Transmitt(this->GetStatus(data[3]), 7);
			default:
				data[2] = 0;
				driveStatus->setError(DriveStatus::E_UNKOWN_COMMAND_OR_ADDR_ERROR);
				break;
		}

		data2send[0] = 0x1F;
		data2send[1] = driveSettings->getDeviceAddress();
		data2send[2] = 0x01;
		data2send[3] = 0x01;
		data2send[6] = CRC8(data2send, 6);
		return Transmitt(data2send, 6);
	}

	return false;
}

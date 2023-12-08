#include "../AppMain/Defines.h"
#include "../Tools/TypeConverter.h"
#include "BaseCOM.h"

BaseCOM::BaseCOM(DriveStatus *driveStatus, DriveSettings *driveSettings, DriveCommand *driveCommand)
{
	this->driveSettings = driveSettings;
	this->driveStatus = driveStatus;
	this->driveCommand = driveCommand;
}

uint8_t* BaseCOM::GetSettings(uint8_t addr)
{

	data2send[0] = 0x1F;
	data2send[1] = driveSettings->getDeviceAddress();
	data2send[2] = 0x00;	//replace with address
	data2send[3] = addr;

	switch (addr)
	{
		case TEACH_TORQUE_ADDR:
			TypeConverter::uint16ToByte(data2send,
					driveSettings->getTeachTroque(), 4);
			break;
		case TEACH_SPEED_ADDR:
			TypeConverter::uint16ToByte(data2send,
					driveSettings->getTeachSpeed(), 4);
			break;
		case CLAMPING_TORQUE_ADDR:
			TypeConverter::uint16ToByte(data2send,
					driveSettings->getClampingTorque(), 4);
			break;
		case CLAMPING_SPEED_ADDR:
			TypeConverter::uint16ToByte(data2send,
					driveSettings->getClampingSpeed(), 4);
			break;
		case SELF_SHUTDOWN_DELAY_ADDR:
			TypeConverter::uint16ToByte(data2send,
					driveSettings->getSelfShutdownDelay(), 4);
			break;
		case IN_POS_DIFF_ADDR:
			TypeConverter::uint16ToByte(data2send,
					driveSettings->getInPosDiff(), 4);
		case OPENING_DISTANCE_ADDR:
			TypeConverter::uint16ToByte(data2send,
					driveSettings->getOpeningDistance(), 4);
			break;
		case UNDERVOLTAGE_WARNING_ADDR:
			TypeConverter::uint16ToByte(data2send,
					driveSettings->getUnderVoltageWarning(),4);
			break;
		case UNDERVOLTAGE_ERROR_ADDR:
			TypeConverter::uint16ToByte(data2send,
					driveSettings->getUnderVoltageError(), 4);
			break;
		case OVER_CURRENT_WARNING_ADDR:
			TypeConverter::uint16ToByte(data2send,
					driveSettings->getOverCurrentWarning(), 4);
			break;
		case OVER_CURRENT_ERROR_ADDR:
			TypeConverter::uint16ToByte(data2send,
					driveSettings->getOverCurrentError(), 4);
			break;
		case DEVICE_ADDRESS_ADDR:
			data2send[4] = driveSettings->getDeviceAddress();
			break;
		default:
			data2send[1] = 0x1D;
			break;
	}
	data2send[6] = CRC8(data2send, 6);
	return data2send;
}

uint8_t* BaseCOM::GetStatus(uint8_t addr)
{
	data2send[0] = 0x1F;
	data2send[1] = driveSettings->getDeviceAddress();
	data2send[2] = 0x00;	////replace with address
	data2send[3] = addr;
	data2send[4] = 0x00;
	data2send[5] = 0x00;
	switch (addr)
	{
		case CLOSE_ADDR:
			data2send[4] = driveStatus->isClose();
			break;
		case OPEN_ADDR:
			data2send[4] = driveStatus->isOpen();
			break;
		case TEACH_ADDR:
			data2send[4] = driveStatus->isTeach();
			break;
		case RESET_ADDR:
			data2send[4] = driveStatus->isReset();
			break;
		case ENABLE_ADDR:
			data2send[4] = driveStatus->isEnable();
			break;
		case STOP_ADDR:
			data2send[4] = driveStatus->isStop();
			break;
		case ERROR_ADDR:
			data2send[4] = driveStatus->getError();
			break;
		case READ_ALL_STATUS:
			data2send[4] |= ((0x01 & driveStatus->isClose()) << 6);	//0100 0000
			data2send[4] |= ((0x01 & driveStatus->isOpen()) << 5);		//0010 0000
			data2send[4] |= ((0x01 & driveStatus->isTeach()) << 4);	//0001 0000
			data2send[4] |= ((0x01 & driveStatus->isReset()) << 3);	//0000 1000
			data2send[4] |= ((0x01 & driveStatus->isEnable()) << 2);	//0000 0100
			data2send[4] |= ((0x01 & !driveStatus->isEnable()) << 1);	//0000 0010
			data2send[4] |= ((0x01 & driveStatus->isStop()) << 0);		//0000 0001

			data2send[5] = driveStatus->getError() << 0;
			break;
		default:
			data2send[0] = 0x1D;
			break;
	}
	data2send[6] = CRC8(data2send, 6);

	return data2send;
}

uint8_t* BaseCOM::GetCommand(uint8_t addr)
{
	data2send[0] = 0x1F;
	data2send[1] = driveSettings->getDeviceAddress();
	data2send[2] = 0x00;	////replace with address
	data2send[3] = addr;

	switch (addr)
	{
		case CLOSE_ADDR:
			data2send[4] = driveCommand->isClose();
			break;
		case OPEN_ADDR:
			data2send[4] = driveCommand->isOpen();
			break;
		case TEACH_ADDR:
			data2send[4] = driveCommand->isTeach();
			break;
		case RESET_ADDR:
			data2send[4] = driveCommand->isReset();
			break;
		case ENABLE_ADDR:
			data2send[4] = driveCommand->isEnable();
			break;
		case STOP_ADDR:
			data2send[4] = driveCommand->isStop();
			break;
		default:
			data2send[0] = 0x1D;
			break;
	}
	data2send[6] = CRC8(data2send, 6);

	return data2send;
}


void BaseCOM::SetSettings(uint8_t *data)
{
	//data[0] = 0x1F
	//data[1] = deviceAddress
	//data[2] = command (readCommand, readSettings, readStatus, writeCommand...)
	//data[3] = reg addr (close, open, setTeach...)
	//data[4..n] = Payload
	//data[6] = crc

	uint16_t value = 0;
	switch (data[3])
	{
		case TEACH_TORQUE_ADDR:
			value = ((uint16_t) data[5]) << 8 | data[4];
			driveSettings->setTeachTroque(value);
			break;
		case TEACH_SPEED_ADDR:
			value = ((uint16_t) data[5]) << 8 | data[4];
			driveSettings->setTeachSpeed(value);
			break;
		case CLAMPING_TORQUE_ADDR:
			value = ((uint16_t) data[5]) << 8 | data[4];
			driveSettings->setClampingTorque(value);
			break;
		case CLAMPING_SPEED_ADDR:
			value = ((uint16_t) data[5]) << 8 | data[4];
			driveSettings->setClampingSpeed(value);
			break;
		case IN_POS_DIFF_ADDR:
			value = ((uint16_t) data[5]) << 8 | data[4];
			driveSettings->setInPosDiff(value);
			break;
		case OPENING_DISTANCE_ADDR:
			value = ((uint16_t) data[5]) << 8 | data[4];
			driveSettings->setOpeningDistance(value);
			break;
		case OVER_CURRENT_WARNING_ADDR:
			value = ((uint16_t) data[5]) << 8 | data[4];
			driveSettings->setOverCurrentWarning(value);
			break;
		case OVER_CURRENT_ERROR_ADDR:
			value = ((uint16_t) data[5]) << 8 | data[4];
			driveSettings->setOverCurrentError(value);
			break;
		case SELF_SHUTDOWN_DELAY_ADDR:
			value = ((uint16_t) data[5]) << 8 | data[4];
			driveSettings->setSelfShutdownDelay(value);
			break;
		case UNDERVOLTAGE_WARNING_ADDR:
			value = ((uint16_t) data[5]) << 8 | data[4];
			driveSettings->setUnderVoltageWarning(value);
			break;
		case UNDERVOLTAGE_ERROR_ADDR:
			value = ((uint16_t) data[5]) << 8 | data[4];
			driveSettings->setUnderVoltageError(value);
			break;
		default:
			break;
	}
}

void BaseCOM::SetCommand(uint8_t *data)
{
	//data[0] = 0x1F
	//data[1] = deviceAddress
	//data[2] = command (readCommand, readSettings, readStatus, writeCommand...)
	//data[3] = reg addr (close, open, setTeach...)
	//data[4..n] = Payload
	//data[6] = crc

	switch (data[3])
	{
		case CLOSE_ADDR:
			driveCommand->setClose(data[4] == 0x01);
			break;
		case OPEN_ADDR:
			driveCommand->setOpen(data[4] == 0x01);
			break;
		case TEACH_ADDR:
			driveCommand->setTeach(data[4] == 0x01);
			break;
		case RESET_ADDR:
			driveCommand->setReset(data[4] == 0x01);
			break;
		case ENABLE_ADDR:
			driveCommand->setEnable(data[4] == 0x01);
			break;
		case STOP_ADDR:
			driveCommand->setStop(data[4] == 0x01);
			break;
		default:
			break;
	}
}

uint8_t BaseCOM::CRC8(uint8_t *data, uint8_t length)
{
	uint8_t crc = 0xff;
	size_t i, j;
	for (i = 0; i < length; i++)
	{
		crc ^= data[i];
		for (j = 0; j < 8; j++)
		{
			if ((crc & 0x80) != 0)
				crc = (uint8_t) ((crc << 1) ^ 0x31);
			else
				crc <<= 1;
		}
	}
	return crc;
}

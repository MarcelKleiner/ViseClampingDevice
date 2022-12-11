/*
 * Communication.h
 *
 *  Created on: 26.11.2022
 *      Author: marce
 */

#ifndef SRC_RFM95W_COMMUNICATION_H_
#define SRC_RFM95W_COMMUNICATION_H_

#include "../Settings/DriveSettings.h"
#include "../Status/DriveStatus.h"
#include "../IO/DI.h"
#include "RFM95.h"
#include "stdio.h"

#define SEND_SETTINGS		0x01
#define SEND_COMMAND		0x02
#define SEND_STATUS_REQ		0x03

#define RCV_STATUS			0x11

//Registers








#define MAX_PACKET_2_SEND		10
#define MAX_PACKET_2_RECEIVE 	10


#if MAX_PACKET_2_RECEIVE > MAX_PKT_LENGTH
#error "PACKE_2_RECEIVE canot be greather than MAX_PKT_LENGTH"
#endif
#if MAX_PACKET_2_SEND > MAX_PKT_LENGTH
#error "MAX_PACKET_2_SEND canot be greather than MAX_PKT_LENGTH"
#endif


class Communication
{

	public:
		Communication(DriveStatus *driveStatus, DriveSettings *driveSettings,
				RFM95_LoRa *rfm95, Digitll_IN_OUT *digitalInOut, DriveCommand *driveCommand);

		bool UpdateCom();
		void ReadData();
	private:

		DriveStatus *driveStatus;
		DriveSettings *driveSettings;
		DriveCommand *driveCommand;
		RFM95_LoRa *rfm95;
		Digitll_IN_OUT *digitalInOut;

		uint8_t CRC8(uint8_t *data, uint8_t length);

		uint8_t rxData[MAX_PACKET_2_SEND] ={ 0 };

};

#endif /* SRC_RFM95W_COMMUNICATION_H_ */

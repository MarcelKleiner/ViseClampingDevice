/*
 * RFM95Com.h
 *
 *  Created on: 26.12.2022
 *      Author: marce
 */

#ifndef SRC_COM_RFM95COM_H_
#define SRC_COM_RFM95COM_H_

#include "../RFM95W/RFM95.h"
#include "../Settings/DriveSettings.h"
#include "../Status/DriveCommand.h"
#include "../Status/DriveStatus.h"
#include "BaseCOM.h"
#include "ICom.h"
#include "USBCom.h"



#define MAX_PACKET_2_SEND		7
#define MAX_PACKET_2_RECEIVE 	7


#if MAX_PACKET_2_RECEIVE > MAX_PKT_LENGTH
#error "PACKE_2_RECEIVE canot be greather than MAX_PKT_LENGTH"
#endif
#if MAX_PACKET_2_SEND > MAX_PKT_LENGTH
#error "MAX_PACKET_2_SEND canot be greather than MAX_PKT_LENGTH"
#endif




class RFM95Com :   public BaseCOM
{
	public:
		RFM95Com(DriveStatus *driveStatus, DriveSettings *driveSettings,
				DriveCommand *driveCommand, RFM95_LoRa *rfm95, Flash *flash) :
				BaseCOM(driveStatus, driveSettings, driveCommand, flash)
		{
			this->rfm95 = rfm95;
			this->driveCommand = driveCommand;
			this->driveStatus = driveStatus;
			this->driveSettings = driveSettings;
			this->usbCom = usbCom;
		}


		 bool Transmitt(uint8_t *data = NULL, uint8_t length = 0) ;
		 bool Receive(uint8_t *data = NULL, uint8_t length = 0) ;


	private:

		RFM95_LoRa *rfm95;
		DriveSettings *driveSettings;
		DriveStatus *driveStatus;
		DriveCommand *driveCommand;
		USBCom* usbCom;

		uint8_t data[7] ={ 0 };

		uint8_t receiveErrorCounter = 0;

};

#endif /* SRC_COM_RFM95COM_H_ */

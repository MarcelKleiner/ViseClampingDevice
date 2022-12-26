/*
 * RFM95Com.h
 *
 *  Created on: 26.12.2022
 *      Author: marce
 */

#ifndef SRC_COM_RFM95COM_H_
#define SRC_COM_RFM95COM_H_

#include "BaseCOM.h"
#include "ICom.h"
#include "../Status/DriveCommand.h"
#include "../Status/DriveStatus.h"
#include "../Settings/DriveSettings.h"
#include "../RFM95W/RFM95.h"



#define MAX_PACKET_2_SEND		10
#define MAX_PACKET_2_RECEIVE 	10


#if MAX_PACKET_2_RECEIVE > MAX_PKT_LENGTH
#error "PACKE_2_RECEIVE canot be greather than MAX_PKT_LENGTH"
#endif
#if MAX_PACKET_2_SEND > MAX_PKT_LENGTH
#error "MAX_PACKET_2_SEND canot be greather than MAX_PKT_LENGTH"
#endif




class RFM95Com :  public ICom, public BaseCOM
{
	public:
		RFM95Com(DriveStatus *driveStatus, DriveSettings *driveSettings,
				DriveCommand *driveCommand, RFM95_LoRa *rfm95) :
				BaseCOM(driveStatus, driveSettings, driveCommand)
		{
			this->rfm95 = rfm95;
			this->driveCommand = driveCommand;
			this->driveStatus = driveStatus;
			this->driveSettings = driveSettings;
		}


		virtual bool Transmitt(uint8_t *data = NULL, uint8_t length = 0) override;
		virtual bool Receive(uint8_t *data = NULL, uint8_t length = 0) override;


	private:

		RFM95_LoRa *rfm95;
		DriveSettings *driveSettings;
		DriveStatus *driveStatus;
		DriveCommand *driveCommand;

		uint8_t data[5] ={ 0 };

};

#endif /* SRC_COM_RFM95COM_H_ */

/*
 * USB.h
 *
 *  Created on: 25.12.2022
 *      Author: marce
 */

#include "BaseCOM.h"
#include "ICom.h"
#include "../Status/DriveCommand.h"
#include "../Status/DriveStatus.h"
#include "../Settings/DriveSettings.h"

#ifndef SRC_COM_USB1_H_
#define SRC_COM_USB1_H_

class USBCom :  public ICom, public BaseCOM
{

	public:

		USBCom(DriveStatus *driveStatus, DriveSettings *driveSettings,
				DriveCommand *driveCommand) :
				BaseCOM(driveStatus, driveSettings, driveCommand)
		{
		}
		virtual bool Transmitt(uint8_t *data = NULL, uint8_t length = 0) override;
		virtual bool Receive(uint8_t *data = NULL, uint8_t length = 0) override;
};

#endif /* SRC_COM_USB_H_ */

/*
 * USB.h
 *
 *  Created on: 25.12.2022
 *      Author: marce
 */

#include "../Flash/Flash.h"
#include "../Settings/DriveSettings.h"
#include "../Status/DriveCommand.h"
#include "../Status/DriveStatus.h"
#include "BaseCOM.h"
#include "ICom.h"

#ifndef SRC_COM_USB1_H_
#define SRC_COM_USB1_H_

class USBCom :  public ICom, public BaseCOM
{

	public:

		USBCom(DriveStatus *driveStatus, DriveSettings *driveSettings,
				DriveCommand *driveCommand, Flash *flash) :
				BaseCOM(driveStatus, driveSettings, driveCommand, flash)
		{
		}
		virtual bool Transmitt(uint8_t *data = NULL, uint8_t length = 0) override;
		virtual bool Receive(uint8_t *data = NULL, uint8_t length = 0) override;
};

#endif /* SRC_COM_USB_H_ */

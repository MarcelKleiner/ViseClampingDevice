#ifndef SRC_ERROR_ERROR_H_
#define SRC_ERROR_ERROR_H_

#include <stm32l433xx.h>
#include "../Status/DriveStatus.h"

class Error{
public:
	Error(DriveStatus* driveStatus);
	void PrintError();
	void ResetError();
private:
	uint8_t errorCode;
	uint8_t erroCounter = 0;
	DriveStatus* driveStatus;
};

#endif /* SRC_ERROR_ERROR_H_ */

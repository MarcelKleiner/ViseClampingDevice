/*
 * DriveStatus.h
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#ifndef SRC_STATUS_DRIVESTATUS_H_
#define SRC_STATUS_DRIVESTATUS_H_

#include "stdint.h"

class DriveStatus{

public:
	uint16_t getCurrent() const;
	void setCurrent(uint16_t current);

	uint16_t getPosition() const;
	void setPosition(uint16_t position);

private:

	uint16_t current;
	uint16_t position;

	uint16_t autoShutdownCounter;

	uint8_t error;
};



#endif /* SRC_STATUS_DRIVESTATUS_H_ */

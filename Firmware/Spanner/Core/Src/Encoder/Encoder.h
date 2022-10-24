/*
 * Encoder.h
 *
 *  Created on: 23.10.2022
 *      Author: marce
 */

#ifndef SRC_ENCODER_ENCODER_H_
#define SRC_ENCODER_ENCODER_H_

#include "stdint.h"
#include "tim.h"
#include "../Status/DriveStatus.h"
#include "../AppMain/Defines.h"

class Encoder{
public:
	Encoder(DriveStatus *driveStatus);

	bool init();
    bool update(void);
    void ResetEncoder();


private:

    DriveStatus *driveStatus;

	int32_t cValue = 0;			//Aktueller Encoderwert
	int32_t lValue = 0;			//Vorgänger Encoderwert
	int32_t deltaValue = 0;			//Encoderwert Differenz
	volatile int32_t encoderValue;	//Aktueller Encoderwert

};



#endif /* SRC_ENCODER_ENCODER_H_ */

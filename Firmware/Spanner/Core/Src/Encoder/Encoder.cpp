/*
 * Encoder.cpp
 *
 *  Created on: 23.10.2022
 *      Author: marce
 */

#include "Encoder.h"

Encoder::Encoder(DriveStatus *driveStatus)
{
	this->driveStatus = driveStatus;
}

bool Encoder::init()
{
	HAL_TIM_Encoder_MspInit(&htim1);
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_2 | TIM_CHANNEL_1);

	cValue = 0;
	lValue = 0;
	deltaValue = 0;
	encoderValue = 0;
	return true;
}

void Encoder::ResetEncoder()
{
	encoderValue = 0;
}

int32_t Encoder::GetValue()
{
	return this->encoderValue;
}

bool Encoder::update()
{

	cValue = TIM1->CNT;				//Read out value from timer register
	deltaValue = cValue - lValue;//Calculate the difference to the previous value

	//forward overflow
	if (deltaValue < -32768)
	{				//Check whether a timer overflow has occurred forwards
		deltaValue = (deltaValue + 65535);	//Overflow correction
	}

	//backwards overflow
	if (deltaValue > 32768)
	{				//Check whether a timer overflow has occurred backwards
		deltaValue = (deltaValue - 65535);	//overflow correction
	}

	encoderValue += deltaValue;	//Increase the encoder value by the difference
	lValue = cValue;						//previous value = current value

	driveStatus->setPosition(encoderValue * GEAR_RATIO);

	return true;
}

/*
 * Drive.cpp
 *
 *  Created on: 23.10.2022
 *      Author: marce
 */

#include "Drive.h"
#include <bits/std_abs.h>

Drive::Drive(DriveSettings *driveSettings, DriveStatus *driveStatus,DriveCommand *driveCommand, Encoder *encoder, LED *led)
{
	this->driveSettings = driveSettings;
	this->driveStatus = driveStatus;
	this->driveCommand = driveCommand;
	this->encoder = encoder;
	this->led = led;
}



void Drive::updateDrive()
{
	if(!driveCommand->isEnable() || driveCommand->isStop()){
		Stop();
		return;
	}

	switch (driveMode)
	{
		case Drive::OP_MODE:
			OpMode();
			break;
		case Drive::TEACH_MODE:
			TeachMode();
			break;
		default:
			Stop();
			break;
	}
}

void Drive::OpMode()
{
	if (driveCommand->isClose())
	{
		Close();
	}
	else if (driveCommand->isOpen())
	{
		Open();
	}
}


void Drive::Close(){
	if(MoveDrive(DIRECTION::IN, driveSettings->getClampingTorque(), driveSettings->getClampingSpeed()))
	{
		driveStatus->setInPos(true);
		driveCommand->setClose(true);
		driveCommand->setOpen(false);
		Stop();
		driveMode = EDRIVE_MODE::STOP_MODE;
	}
}

void Drive::Open(){

	auto posOut = driveSettings->getOpeningDistance() + driveSettings->getInPosDiff();
	auto posIn = driveSettings->getOpeningDistance() - driveSettings->getInPosDiff();
	int32_t currentPosition = driveStatus->getPosition();

	if(currentPosition < posIn)
	{
		MoveDrive(DIRECTION::OUT, driveSettings->getClampingTorque(), driveSettings->getClampingSpeed());
	}

	if(currentPosition > posOut){
		MoveDrive(DIRECTION::IN, driveSettings->getClampingTorque(), driveSettings->getClampingSpeed());
	}

	if(driveStatus->getPosition() < posOut && driveStatus->getPosition() > posIn)
	{
		driveStatus->setInPos(true);
		driveCommand->setOpen(true);
		driveCommand->setClose(false);
		Stop();
		driveMode = EDRIVE_MODE::STOP_MODE;
	}
}



void Drive::Stop()
{
	TIM2->CCR1 = 64000; //3200-6400
}

int32_t initialPosition = 0;
int32_t currentPosition = 0;
int32_t lastPosition = 0;

void Drive::TeachMode()
{
	currentState = nextState;

	switch (currentState)
	{
		case TEACH_MODE_ENTER:
			if (IS_EXT_SWITCH == false)
			{
				nextState = TEACH_RDY;
			}
			break;
		case TEACH_RDY:
			if (IS_EXT_SWITCH == true)
			{
				initialPosition = driveStatus->getPosition();
				currentPosition = initialPosition;
				lastPosition = initialPosition;
				nextState = DRIVE_OUT;
			}
			break;
		case DRIVE_IN:

			currentPosition = driveStatus->getPosition();

			if (!IS_EXT_SWITCH)
			{
				Stop();
				if (abs(currentPosition - lastPosition) > 5);
				{
					lastPosition = currentPosition;
					return;
				}

				nextState = DRIVE_OUT;
				currentPosition = driveStatus->getPosition();
				lastPosition = currentPosition;
			}

			//move drive in
			if(MoveDrive(IN, driveSettings->getTeachTroque(),driveSettings->getTeachSpeed()))
			{
				Stop();
				nextState = TEACH_END;
			}

			lastPosition = currentPosition;
			break;
		case DRIVE_OUT:
			//move drive out
			
			currentPosition = driveStatus->getPosition();

			//the encoder value should increase when driving out!
			if (lastPosition > currentPosition) 
			{
				driveStatus->setError(DriveStatus::E_ENCODER_ERROR);
				Stop();
				driveMode = EDRIVE_MODE::STOP_MODE;
				return;
			}
			else if (currentPosition >= initialPosition)
			{
				positionReached = true;
				Stop();
			} 
			else if (torqueOutReached || positionReached || MoveDrive(OUT, driveSettings->getTeachTroque(), driveSettings->getTeachSpeed()))
			{
				torqueOutReached = true;
			}


			if(IS_EXT_SWITCH)
			{
				Stop();
				//wait until stop
				if (abs(currentPosition - lastPosition) > 5);
				{
					lastPosition = currentPosition;
					return;
				}

				nextState = DRIVE_IN;
				torqueOutReached = false;
				positionReached = false;
			}

			lastPosition = currentPosition;

			break;
		case TEACH_END:
			//reset TTL counter
			encoder->ResetEncoder();
			driveCommand->setTeach(false);
			driveMode = OP_MODE;
			break;
		default:
			break;
	}

}

Drive::EDRIVE_MODE Drive::getDriveMode()
{
	return driveMode;
}

void Drive::setDriveMode(EDRIVE_MODE driveMode)
{
	this->driveMode = driveMode;
}

bool Drive::MoveDrive(DIRECTION direction, uint16_t torque, uint16_t speed)
{
	if(driveStatus->getCurrent() * CURRENT_2_TORQUE > torque){
		Stop();
		return true;
	}

	if (speed > 6400)
		speed = 6400;

	if (speed < 3200)
		speed = 3200;


	switch (direction)
	{
		case DIRECTION::IN:
			TIM2->CCR2 = DIRECTION_IN;	//direction
			TIM2->CCR1 = 65000;	//speed
			break;
		case DIRECTION::OUT:
			TIM2->CCR2 = DIRECTION_OUT;	//direction
			TIM2->CCR1 = 65000; //speed
			break;
		default:
			Stop();
			break;
	}
	return false;
}

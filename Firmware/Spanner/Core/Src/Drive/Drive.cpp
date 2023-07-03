/*
 * Drive.cpp
 *
 *  Created on: 23.10.2022
 *      Author: marce
 */

#include "Drive.h"

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
		driveCommand->setClose(false);
	}
}

void Drive::Open(){

	auto posOut = driveSettings->getOpeningDistance() + driveSettings->getInPosDiff();
	auto posIn = driveSettings->getOpeningDistance() - driveSettings->getInPosDiff();


	if(driveStatus->getPosition() < posIn)
	{
		MoveDrive(DIRECTION::OUT, driveSettings->getClampingTorque(), driveSettings->getClampingSpeed());
	}

	if(driveStatus->getPosition() > posOut){
		MoveDrive(DIRECTION::IN, driveSettings->getClampingTorque(), driveSettings->getClampingSpeed());
	}

	if(driveStatus->getPosition() < posOut && driveStatus->getPosition() > posIn)
	{
		driveStatus->setInPos(true);
		driveCommand->setOpen(false);
	}
}



void Drive::Stop()
{
	TIM2->CCR1 = 3200; //3200-6400
}

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
				nextState = DRIVE_OUT;
			}
			break;
		case DRIVE_IN:
			//move drive in
			if(MoveDrive(IN, driveSettings->getTeachTroque(),driveSettings->getTeachSpeed()))
			{
				nextState = TEACH_END;
			}

			if(IS_EXT_SWITCH)
			{
				nextState = DRIVE_OUT;
			}
			break;
		case DRIVE_OUT:
			//move drive out
			if(MoveDrive(OUT, driveSettings->getTeachTroque(), driveSettings->getTeachSpeed()) || torqueOutReached)
			{
				torqueOutReached = true;
			}

			if(!IS_EXT_SWITCH)
			{
				nextState = DRIVE_IN;
				torqueOutReached = false;
			}
			break;
		case TEACH_END:
			//reset TTL counter
			encoder->ResetEncoder();
			driveCommand->setTeach(false);
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

	switch (direction)
	{
		case DIRECTION::IN:
			TIM2->CCR2 = DIRECTION_IN;	//direction
			TIM2->CCR1 = speed; //4000;	//speed
			led->ON();
			break;
		case DIRECTION::OUT:
			TIM2->CCR2 = DIRECTION_OUT;	//direction
			TIM2->CCR1 = speed; //4000; //speed
			led->ON();
			break;
		default:
			Stop();
			break;
	}
	return false;
}

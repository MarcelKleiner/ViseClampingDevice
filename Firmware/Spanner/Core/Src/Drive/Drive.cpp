/*
 * Drive.cpp
 *
 *  Created on: 23.10.2022
 *      Author: marce
 */

#include "Drive.h"
#include "../IO/IO.h"

Drive::Drive(DriveSettings *driveSettings, DriveStatus *driveStatus,
		DriveCommand *driveCommand, Encoder *encoder)
{
	this->driveSettings = driveSettings;
	this->driveStatus = driveStatus;
	this->driveCommand = driveCommand;
	this->encoder = encoder;
}

void Drive::Reset()
{
	isDriveStoped = false;
}

void Drive::updateDrive()
{
	if (driveCommand->isStop() || isDriveStoped)
	{
		isDriveStoped = true;
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

	if(driveStatus->getCurrent() >= (driveSettings->getClampingTorque() * TORQUE_2_CURRENT))
	{
		driveStatus->setInPos(true);
	}
	else
	{
		MoveDrive(DIRECTION::IN, driveSettings->getClampingTorque(), driveSettings->getClampingSpeed());
	}
}

void Drive::Open(){

	auto posOut = driveSettings->getOpeningDistance() + driveSettings->getInPosDiff();
	auto posIn = driveSettings->getOpeningDistance() - driveSettings->getInPosDiff();


	if(driveStatus->getPosition() >= posOut && driveStatus->getPosition() < posIn)
	{
		driveStatus->setInPos(true);
	}
	else
	{
		MoveDrive(DIRECTION::OUT, driveSettings->getClampingTorque(), driveSettings->getClampingSpeed());
	}
}



void Drive::Stop()
{
	TIM2->CCR1 = 3200; //3200-6400
}

void Drive::TeachMode()
{
	static uint8_t counter = 0;
	static bool InOut = 0;
	currentState = nextState;

	switch (currentState)
	{
		case TEACH_MODE_ENTER:
			if (IS_EXT_SWITCH == GPIO_PIN_RESET)
			{
				nextState = TEACH_RDY;
			}
			break;
		case TEACH_RDY:
			if (IS_EXT_SWITCH)
			{
				nextState = CHECK_CLK;
			}
			break;
		case CHECK_CLK:
			if (counter > 2 && IS_EXT_SWITCH)
			{
				if (InOut)
				{
					nextState = DRIVE_IN;
				}
				else
				{
					nextState = DRIVE_OUT;
				}
				InOut = !InOut;
			}

			if (!IS_EXT_SWITCH)
			{
				nextState = CLK_1;
			}

			if (nextState != currentState)
			{
				counter = 0;
			}
			else
			{
				counter++;
			}

			break;
		case CLK_1:
			if (counter > 2 && !IS_EXT_SWITCH)
			{
				nextState = TEACH_RDY;
			}

			if (IS_EXT_SWITCH)
			{
				nextState = CLK_2;
			}

			if (nextState != currentState)
			{
				counter = 0;
			}
			else
			{
				counter++;
			}

			break;
		case CLK_2:
			if (IS_EXT_SWITCH)
			{
				nextState = TEACH_END;
			}

			break;
		case DRIVE_IN:
			//move drive in
			MoveDrive(IN, driveSettings->getTeachTroque(),
					driveSettings->getTeachSpeed());
			break;
		case DRIVE_OUT:
			//move drive out
			MoveDrive(OUT, driveSettings->getTeachTroque(),
					driveSettings->getTeachSpeed());
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

Drive::EDRIVE_MODE Drive::getDriveMode() const
{
	return driveMode;
}

void Drive::setDriveMode(EDRIVE_MODE driveMode)
{
	this->driveMode = driveMode;
}

void Drive::MoveDrive(DIRECTION direction, uint16_t torque, uint16_t speed)
{

	switch (direction)
	{
		case DIRECTION::IN:
			TIM2->CCR2 = 3200;	//direction

			TIM2->CCR1 = 4000;	//speed
			break;
		case DIRECTION::OUT:
			TIM2->CCR2 = 6400;	//direction

			TIM2->CCR1 = 4000; //speed

			break;
		default:
			Stop();
			break;
	}

}

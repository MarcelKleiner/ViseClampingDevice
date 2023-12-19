/*
 * Drive.cpp
 *
 *  Created on: 23.10.2022
 *      Author: marce
 */

#include "Drive.h"
#include <bits/std_abs.h>

Drive::Drive(DriveSettings* driveSettings, DriveStatus* driveStatus, DriveCommand* driveCommand, Encoder* encoder, LED* led)
{
     this->driveSettings = driveSettings;
     this->driveStatus = driveStatus;
     this->driveCommand = driveCommand;
     this->encoder = encoder;
     this->led = led;
}



void Drive::updateDrive()
{
     if (!driveCommand->isEnable() || driveCommand->isStop()) {
          Stop();
          return;
     }

     if (driveCommand->isTeach()) {
          driveCommand->setTeach(false);
          ResetTeachState();
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


void Drive::ResetTeachState() {
     initialPosition = 0;
     currentPosition = 0;
     lastPosition = 0;
     currentState = TEACH_MODE_ENTER;
     nextState = TEACH_MODE_ENTER;
     isLocalDelayInitialized = false;
     driveMode = Drive::TEACH_MODE;
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
     else {
          Stop();
     }
}


void Drive::Close() {
     if (MoveDrive(DIRECTION::IN, driveSettings->getClampingTorque(), driveSettings->getClampingSpeed(), false))
     {
          driveStatus->setInPos(true);
          driveStatus->setClose(true);
          driveStatus->setOpen(false);
          driveCommand->setClose(false);
          driveCommand->setOpen(false);
          Stop();
     }
}

void Drive::Open() {

     auto posOut = driveSettings->getOpeningDistance() + driveSettings->getInPosDiff();
     auto posIn = driveSettings->getOpeningDistance() - driveSettings->getInPosDiff();
     int32_t currentPosition = driveStatus->getPosition();

     if (currentPosition > posIn)
     {
          MoveDrive(DIRECTION::OUT, driveSettings->getClampingTorque(), driveSettings->getClampingSpeed(), false);
     }

     if (currentPosition > posOut) {
          MoveDrive(DIRECTION::IN, driveSettings->getClampingTorque(), driveSettings->getClampingSpeed(), false);
     }

     if (driveStatus->getPosition() < posOut && driveStatus->getPosition() > posIn)
     {
          driveStatus->setInPos(true);
          driveStatus->setOpen(true);
          driveStatus->setClose(false);
          driveCommand->setClose(false);
          driveCommand->setOpen(false);
          Stop();
     }
}

void Drive::Stop()
{
     TIM2->CCR1 = 64000; //3200-6400
}



void Drive::TeachMode()
{
     currentState = nextState;
     currentPosition = driveStatus->getPosition();

     switch (currentState)
     {
     case TEACH_MODE_ENTER:
          if (!IS_EXT_SWITCH)
          {
               nextState = TEACH_RDY;
          }
          break;
     case TEACH_RDY:
          if (IS_EXT_SWITCH)
          {
               encoder->ResetEncoder();
               initialPosition = 0;
               currentPosition = 0;
               lastPosition = 0;
               nextState = DRIVE_OUT;
          }
          break;
     case DRIVE_IN:
          //move drive in	
          if (IS_EXT_SWITCH)
          {
               if (MoveDrive(IN, driveSettings->getTeachTroque(), driveSettings->getTeachSpeed(),!InternalDelay(50)))
               {
                    Stop();
                    initialPosition =  -currentPosition;
                    isLocalDelayInitialized = false;
                    encoder->ResetEncoder();
                    driveCommand->setTeach(false);
                    nextState = TEACH_END;
               }
          }
          else
          {
               Stop();
               if (abs(currentPosition - lastPosition) == 0 && InternalDelay(50))
               {
                    isLocalDelayInitialized = false;
                    nextState = DRIVE_OUT;
               }
          }
          break;
     case DRIVE_OUT:
          //move drive out	
          if (IS_EXT_SWITCH)
          {
               Stop();
               //wait until stop

               if (abs(currentPosition - lastPosition) == 0 && InternalDelay(50))
               {
                    isLocalDelayInitialized = false;
                    nextState = DRIVE_IN;
               }
          }
          else
          {
               if (DriveOutToInitializePosition())
               {
                    Stop();
               }
          }
          break;
     case TEACH_END:
          if (DriveOutToInitializePosition()) {
               driveMode = OP_MODE;
          }
          break;
     default:
          break;
     }
     lastPosition = currentPosition;
}

bool Drive::InternalDelay(uint16_t delay)
{
     static int16_t localDelay;
     if (!isLocalDelayInitialized) {
          localDelay = delay;
          isLocalDelayInitialized = true;
     }
     
     if (localDelay-- <= 0)
     {
          localDelay = 0;
          return true;
     }
     return false;
}

bool Drive::DriveOutToInitializePosition() {

     if (currentPosition <= initialPosition) 
     {
          Stop();
          isLocalDelayInitialized = false;
          return true;
     }

     bool isTorqueReached = MoveDrive(OUT, 
          driveSettings->getTeachTroque() * 2, 
          driveSettings->getTeachSpeed(), 
          !InternalDelay(50));

     if (isTorqueReached)
     {
          Stop();
          isLocalDelayInitialized = false;
          return true;

     }
     return false;
}

bool Drive::MoveDrive(DIRECTION direction, uint16_t torque, uint16_t speed, bool ignoreTorque)
{

     if (driveStatus->getCurrent() * CURRENT_2_TORQUE > torque && !ignoreTorque) 
     {
          Stop();
          return true;
     }
     speed = speed * 533 + 66670;

     if (speed > 120000)
          speed = 120000;

     if (speed < 72000)
          speed = 72000;


     switch (direction)
     {
     case DIRECTION::IN:
          TIM2->CCR2 = DIRECTION_IN;	//direction
          TIM2->CCR1 = 72000;	//speed
          break;
     case DIRECTION::OUT:
          TIM2->CCR2 = DIRECTION_OUT;	//direction
          TIM2->CCR1 = 72000; //speed
          break;
     default:
          Stop();
          break;
     }
     return false;
}

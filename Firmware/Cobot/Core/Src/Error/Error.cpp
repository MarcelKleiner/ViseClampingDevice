#include "Error.h"

Error::Error(DriveStatus* driveStatus) {
     this->driveStatus = driveStatus;
}

void Error::ResetError() {
     driveStatus->ResetError();
     errorCode = 0;
}


void Error::PrintError() 
{
     if (erroCounter == 16) {
          errorCode = (uint8_t)driveStatus->GetError() * 2;
          HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);
          erroCounter = 0;
     }
     else {
          erroCounter++;
     }

     if (erroCounter < errorCode)
     {
          HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
     }
     else {
          HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);
     }
}
/*
 * AppMain.h
 *
 *  Created on: Oct 20, 2022
 *      Author: marce
 */

#ifndef SRC_APPMAIN_APPMAIN_H_
#define SRC_APPMAIN_APPMAIN_H_

#include "../Taskhandler/Taskhandler.h"
#include "../RFM95W/RFM95.h"
#include "../Tools/Delay.h"
#include "../IO/DO.h"
#include "../IO/LED.h"
#include "../IO/DI.h"
#include "tim.h"
#include "main.h"


 class AppMain{

 public:
	 AppMain();

	 void Startup(void);
	 void Main(void);

	 RFM95_LoRa rfm95 = RFM95_LoRa();
	 TaskHandler taskStatus = TaskHandler();

	 LED LED_Green = LED(LED_G_GPIO_Port, LED_G_Pin, true);
	 LED LED_Red = LED(LED_R_GPIO_Port, LED_R_Pin, true);

	 DigitalIN DigitalIn = DigitalIN();

	 DigitalOut closed = DigitalOut(DI_OUT_1_N_GPIO_Port, DI_OUT_1_N_Pin, DI_OUT_1_P_GPIO_Port, DI_OUT_1_P_Pin);
	 DigitalOut open = DigitalOut(DI_OUT_2_N_GPIO_Port, DI_OUT_2_N_Pin, DI_OUT_2_P_GPIO_Port, DI_OUT_2_P_Pin);
	 DigitalOut viseReady = DigitalOut(DI_OUT_3_N_GPIO_Port, DI_OUT_3_N_Pin, DI_OUT_3_P_GPIO_Port, DI_OUT_3_P_Pin);
	 DigitalOut error = DigitalOut(DI_OUT_4_N_GPIO_Port, DI_OUT_4_N_Pin, DI_OUT_4_P_GPIO_Port, DI_OUT_4_P_Pin);
	 DigitalOut batteryLow = DigitalOut(DI_OUT_5_N_GPIO_Port, DI_OUT_5_N_Pin, DI_OUT_5_P_GPIO_Port, DI_OUT_5_P_Pin);
	 DigitalOut signal = DigitalOut(DI_OUT_6_N_GPIO_Port, DI_OUT_6_N_Pin, DI_OUT_6_P_GPIO_Port, DI_OUT_6_P_Pin);
	 DigitalOut res1 = DigitalOut(DI_OUT_7_N_GPIO_Port, DI_OUT_7_N_Pin, DI_OUT_7_P_GPIO_Port, DI_OUT_7_P_Pin);
	 DigitalOut res2 = DigitalOut(DI_OUT_8_N_GPIO_Port, DI_OUT_8_N_Pin, DI_OUT_8_P_GPIO_Port, DI_OUT_8_P_Pin);

 private:



};


#endif /* SRC_APPMAIN_APPMAIN_H_ */

/*
 * Delay.cpp
 *
 *  Created on: 30.10.2022
 *      Author: marce
 */
#include "Delay.h"
#include "stm32l4xx_hal.h"


/*
 * Mikrosenkunden delay Initialisieren
 */
void Delay::DWT_Init(void) {
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CYCCNT = 0;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

/*
 * Mikrosenkunden delay für Push-Pull ansteuerung
 */
void Delay::DWT_Delay_us(volatile uint32_t microseconds) {
	uint32_t clk_cycle_start = DWT->CYCCNT;
	/* Go to number of cycles for system */
	microseconds *= (HAL_RCC_GetHCLKFreq() / 1000000);
	/* Delay till end */
	while ((DWT->CYCCNT - clk_cycle_start) < microseconds);
}



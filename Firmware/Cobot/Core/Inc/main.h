/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void USB_CDC_RX_Interrupt(uint8_t *data, uint32_t length);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DI_OUT_8_P_Pin GPIO_PIN_14
#define DI_OUT_8_P_GPIO_Port GPIOC
#define DI_OUT_8_N_Pin GPIO_PIN_15
#define DI_OUT_8_N_GPIO_Port GPIOC
#define DI_1_Pin GPIO_PIN_1
#define DI_1_GPIO_Port GPIOH
#define DI_2_Pin GPIO_PIN_0
#define DI_2_GPIO_Port GPIOC
#define DI_3_Pin GPIO_PIN_1
#define DI_3_GPIO_Port GPIOC
#define DI_4_Pin GPIO_PIN_2
#define DI_4_GPIO_Port GPIOC
#define DI_5_Pin GPIO_PIN_3
#define DI_5_GPIO_Port GPIOC
#define DI_6_Pin GPIO_PIN_0
#define DI_6_GPIO_Port GPIOA
#define DI_7_Pin GPIO_PIN_1
#define DI_7_GPIO_Port GPIOA
#define DI_8_Pin GPIO_PIN_2
#define DI_8_GPIO_Port GPIOA
#define DI_OUT_6_N_Pin GPIO_PIN_4
#define DI_OUT_6_N_GPIO_Port GPIOC
#define DI_OUT_4_P_Pin GPIO_PIN_0
#define DI_OUT_4_P_GPIO_Port GPIOB
#define DI_OUT_6_P_Pin GPIO_PIN_1
#define DI_OUT_6_P_GPIO_Port GPIOB
#define DI_OUT_2_N_Pin GPIO_PIN_2
#define DI_OUT_2_N_GPIO_Port GPIOB
#define DI_OUT_4_N_Pin GPIO_PIN_10
#define DI_OUT_4_N_GPIO_Port GPIOB
#define DI_OUT_2_P_Pin GPIO_PIN_11
#define DI_OUT_2_P_GPIO_Port GPIOB
#define DI_OUT_7_N_Pin GPIO_PIN_13
#define DI_OUT_7_N_GPIO_Port GPIOB
#define DI_OUT_7_P_Pin GPIO_PIN_14
#define DI_OUT_7_P_GPIO_Port GPIOB
#define DI_OUT_5_N_Pin GPIO_PIN_15
#define DI_OUT_5_N_GPIO_Port GPIOB
#define DI_OUT_5_P_Pin GPIO_PIN_6
#define DI_OUT_5_P_GPIO_Port GPIOC
#define DI_OUT_3_N_Pin GPIO_PIN_7
#define DI_OUT_3_N_GPIO_Port GPIOC
#define DI_OUT_3_P_Pin GPIO_PIN_8
#define DI_OUT_3_P_GPIO_Port GPIOC
#define DI_OUT_1_N_Pin GPIO_PIN_9
#define DI_OUT_1_N_GPIO_Port GPIOC
#define DI_OUT_1_P_Pin GPIO_PIN_8
#define DI_OUT_1_P_GPIO_Port GPIOA
#define LED_R_Pin GPIO_PIN_9
#define LED_R_GPIO_Port GPIOA
#define LED_G_Pin GPIO_PIN_10
#define LED_G_GPIO_Port GPIOA
#define RFM_NSS_Pin GPIO_PIN_3
#define RFM_NSS_GPIO_Port GPIOB
#define RFM_RST_Pin GPIO_PIN_4
#define RFM_RST_GPIO_Port GPIOB
#define RFM_DI_3_Pin GPIO_PIN_5
#define RFM_DI_3_GPIO_Port GPIOB
#define RFM_DI_0_Pin GPIO_PIN_6
#define RFM_DI_0_GPIO_Port GPIOB
#define RFM_DI_2_Pin GPIO_PIN_7
#define RFM_DI_2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

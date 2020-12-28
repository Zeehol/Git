/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define LED_R_ON        HAL_GPIO_WritePin(GPIOH, LED_R_Pin, GPIO_PIN_RESET)
#define LED_R_OFF       HAL_GPIO_WritePin(GPIOH, LED_R_Pin, GPIO_PIN_SET)
#define LED_R_TOGGLE    HAL_GPIO_TogglePin(LED_R_GPIO_Port,LED_R_Pin)

#define LED_G_ON        HAL_GPIO_WritePin(GPIOH, LED_G_Pin, GPIO_PIN_RESET)
#define LED_G_OFF       HAL_GPIO_WritePin(GPIOH, LED_G_Pin, GPIO_PIN_SET)
#define LED_G_TOGGLE    HAL_GPIO_TogglePin(LED_G_GPIO_Port,LED_G_Pin)

#define LED_B_ON        HAL_GPIO_WritePin(GPIOH, LED_B_Pin, GPIO_PIN_RESET)
#define LED_B_OFF       HAL_GPIO_WritePin(GPIOH, LED_B_Pin, GPIO_PIN_SET)
#define LED_B_TOGGLE    HAL_GPIO_TogglePin(LED_B_GPIO_Port,LED_B_Pin)

#define LED_ALL_ON      HAL_GPIO_WritePin(GPIOH, LED_R_Pin|LED_G_Pin|LED_B_Pin, GPIO_PIN_RESET)
#define LED_ALL_OFF     HAL_GPIO_WritePin(GPIOH, LED_R_Pin|LED_G_Pin|LED_B_Pin, GPIO_PIN_SET)

#define Key_Delay(value)   HAL_Delay(value)
#define KEY1_PUSH       Key_Scan(KEY1_GPIO_Port,KEY1_Pin,1,&pKey1Press)
#define KEY2_PUSH       Key_Scan(KEY2_GPIO_Port,KEY2_Pin,1,&pKey2Press)
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
static uint8_t pKey1Press = 0;
static uint8_t pKey2Press = 0;
extern uint8_t Key_Scan ( GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin, uint8_t ucPushState, uint8_t * pKeyPress);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

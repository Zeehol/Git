/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN Private defines */
#define RXBUFFER_LENGTH  100
#define TXBUFFER_LENGTH  100
extern uint8_t RxBuffer[RXBUFFER_LENGTH];
extern uint8_t TxBuffer[TXBUFFER_LENGTH];

extern UART_HandleTypeDef huart1;

/*信息输出*/
#define PRINTF_INFO_ON          1

#define PRINTF_INFO(fmt,arg...)           do{\
                                          if(PRINTF_INFO_ON)\
                                          printf("<<-PRINTF-INFO->>"fmt"\n\n", ##arg);\
                                          }while(0)

/*错误输出*/																			
#define PRINTF_ERROR_ON         1
																					
#define PRINTF_ERROR(fmt,arg...)          do{\
                                          if(PRINTF_ERROR_ON)\
                                          printf("<<-PRINTF-ERROR->>"fmt"\n\n", ##arg);\
                                          }while(0)

/*DEBUG输出*/
#define PRINTF_DEBUG_ON         1
																					
#define PRINTF_DEBUG(fmt,arg...)          do{\
                                          if(PRINTF_DEBUG_ON)\
                                          printf("<<-PRINTF-DEBUG->>[%s] 第[%d]行：\n "fmt" \n\n ",__FILE__,__LINE__, ##arg);\
                                          }while(0)

																					
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * File Name          : FMC.h
  * Description        : This file provides code for the configuration
  *                      of the FMC peripheral.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#ifndef __FMC_H
#define __FMC_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include <stdio.h>
/* USER CODE END Includes */

extern SDRAM_HandleTypeDef hsdram1;

/* USER CODE BEGIN Private defines */
/*信息输出*/
#define SDRAM_DEBUG_ON         1

#define SDRAM_INFO(fmt,arg...)           printf("<<-SDRAM-INFO->> "fmt"\n",##arg)
#define SDRAM_ERROR(fmt,arg...)          printf("<<-SDRAM-ERROR->> "fmt"\n",##arg)
#define SDRAM_DEBUG(fmt,arg...)          do{\
                                          if(SDRAM_DEBUG_ON)\
                                          printf("<<-SDRAM-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)


#define IS42S16400J_SIZE 0x800000  //400000*16bits = 0x800000  ，8M字节


/*SDRAM 的bank选择*/  
#define FMC_BANK_SDRAM            FMC_Bank2_SDRAM  
#define FMC_COMMAND_TARGET_BANK   FMC_SDRAM_CMD_TARGET_BANK2

/**
  * @brief  FMC SDRAM 数据基地址
  */   
#define SDRAM_BANK_ADDR     ((uint32_t)0xD0000000)
  
/**
  * @brief  FMC SDRAM 数据宽度
  */  
/* #define SDRAM_MEMORY_WIDTH   FMC_SDMemory_Width_8b  */
#define SDRAM_MEMORY_WIDTH    FMC_SDRAM_MEM_BUS_WIDTH_16 

/**
  * @brief  FMC SDRAM CAS Latency
  */  
/* #define SDRAM_CAS_LATENCY   FMC_CAS_Latency_2  */
#define SDRAM_CAS_LATENCY    FMC_SDRAM_CAS_LATENCY_3

/**
  * @brief  FMC SDRAM SDCLK时钟分频因子
  */  
#define SDCLOCK_PERIOD    FMC_SDRAM_CLOCK_PERIOD_2        /* Default configuration used with LCD */
/* #define SDCLOCK_PERIOD    FMC_SDClock_Period_3 */

/**
  * @brief  FMC SDRAM 突发读取特性
  */  
#define SDRAM_READBURST    FMC_SDRAM_RBURST_DISABLE    /* Default configuration used with LCD */
/* #define SDRAM_READBURST    FMC_Read_Burst_Enable  */

/**
  * @brief  FMC SDRAM Bank Remap
  */    
/* #define SDRAM_BANK_REMAP */   

#define SDRAM_TIMEOUT                    ((uint32_t)0xFFFF)



/**
  * @brief  FMC SDRAM 模式配置的寄存器相关定义
  */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000) 
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)      

/* USER CODE END Private defines */

void MX_FMC_Init(void);
void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef* hsdram);
void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef* hsdram);

/* USER CODE BEGIN Prototypes */
void  SDRAM_WriteBuffer(uint32_t* pBuffer, uint32_t uwWriteAddress, uint32_t uwBufferSize);
void  SDRAM_ReadBuffer(uint32_t* pBuffer, uint32_t uwReadAddress, uint32_t uwBufferSize);
uint8_t SDRAM_Test(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__FMC_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* FreeRTOSͷ�ļ� */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
//#include "netconn.h"
#include "MQTTClient.h"
#include "cJSON_Process.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/**************************** ������ ********************************/
/* 
 * ��������һ��ָ�룬����ָ��һ�����񣬵����񴴽���֮�����;�����һ��������
 * �Ժ�����Ҫ��������������Ҫͨ�������������������������������Լ�����ô
 * ����������ΪNULL��
 */
static TaskHandle_t AppTaskCreate_Handle = NULL;/* ���������� */
static TaskHandle_t Test1_Task_Handle = NULL;/* LED������ */
static TaskHandle_t Test2_Task_Handle = NULL;/* KEY������ */

QueueHandle_t MQTT_Data_Queue =NULL;
//��Ϣ����̫��ᵼ�³����ܷ�
#define  MQTT_QUEUE_LEN    4   /* ���еĳ��ȣ����ɰ������ٸ���Ϣ */
#define  MQTT_QUEUE_SIZE   10   /* ������ÿ����Ϣ��С���ֽڣ� */

 uint8_t *Test_Ptr = NULL;
 uint32_t g_memsize;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/*
*************************************************************************
*                             ��������
*************************************************************************
*/
static void AppTaskCreate(void);/* ���ڴ������� */

static void Test1_Task(void* pvParameters);/* Test1_Task����ʵ�� */
static void Test2_Task(void* pvParameters);/* Test2_Task����ʵ�� */

extern void TCPIP_Init(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	printf("���ڳ�ʼ����ɣ�");

/* ����AppTaskCreate���� */
  xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  /* ������ں��� */
                        (const char*    )"AppTaskCreate",/* �������� */
                        (uint16_t       )512,  /* ����ջ��С */
                        (void*          )NULL,/* ������ں������� */
                        (UBaseType_t    )1, /* ��������ȼ� */
                        (TaskHandle_t*  )&AppTaskCreate_Handle);/* ������ƿ�ָ�� */ 
  /* ����������� */           
  if(pdPASS == xReturn)
    vTaskStartScheduler();   /* �������񣬿������� */
  else
    return -1;  
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//		if(KEY1_PUSH)LED_R_TOGGLE;
//		if(KEY2_PUSH)LED_B_TOGGLE;
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* ʹ��HSE������HSEΪPLL��ʱ��Դ������PLL�ĸ��ַ�Ƶ����M N P Q 
	 * PLLCLK = HSE/M*N/P = 25M / 25 *432 / 2 = 216M
	 */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
   while(1) {}
  }

  /* ���� OverDrive ģʽ */
  HAL_PWREx_EnableOverDrive();
 
  /* ѡ��PLLCLK��ΪSYSCLK�������� HCLK, PCLK1 and PCLK2 ��ʱ�ӷ�Ƶ���� 
	 * SYSCLK = PLLCLK     = 180M
	 * HCLK   = SYSCLK / 1 = 180M
	 * PCLK2  = SYSCLK / 2 = 90M
	 * PCLK1  = SYSCLK / 4 = 45M
	 */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    while(1) {}
  }
  
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/configTICK_RATE_HZ);
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
/***********************************************************************
  * @ ������  �� AppTaskCreate
  * @ ����˵���� Ϊ�˷���������е����񴴽����������������������
  * @ ����    �� ��  
  * @ ����ֵ  �� ��
  **********************************************************************/
static void AppTaskCreate(void)
{
  BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */

	/* ����Test_Queue */
  MQTT_Data_Queue = xQueueCreate((UBaseType_t ) MQTT_QUEUE_LEN,/* ��Ϣ���еĳ��� */
                                 (UBaseType_t ) MQTT_QUEUE_SIZE);/* ��Ϣ�Ĵ�С */
  if(NULL != MQTT_Data_Queue)
  printf("����MQTT_Data_Queue��Ϣ���гɹ�!\r\n");

  TCPIP_Init();
	mqtt_thread_init();
	
  printf("����������/IP��ַ : %s \t �˿ں� : %d \n\n",HOST_NAME,HOST_PORT);  
  
  printf("������CLIENT_ID : %s\n\n",CLIENT_ID); 
  
  printf("������USER_NAME : %s\n\n",USER_NAME); 
  
  printf("������PASSWORD : %s\n\n",PASSWORD);  
  
  printf("������TOPIC : %s\n\n",TOPIC);  
  
  printf("������TEST_MESSAGE : %s\n\n",TEST_MESSAGE); 
	
  taskENTER_CRITICAL();           //�����ٽ���

  /* ����Test1_Task���� */
  xReturn = xTaskCreate((TaskFunction_t )Test1_Task, /* ������ں��� */
                        (const char*    )"Test1_Task",/* �������� */
                        (uint16_t       )512,   /* ����ջ��С */
                        (void*          )NULL,	/* ������ں������� */
                        (UBaseType_t    )1,	    /* ��������ȼ� */
                        (TaskHandle_t*  )&Test1_Task_Handle);/* ������ƿ�ָ�� */
  if(pdPASS == xReturn)
    printf("Create Test1_Task sucess...\r\n");
  
  /* ����Test2_Task���� */
  xReturn = xTaskCreate((TaskFunction_t )Test2_Task,  /* ������ں��� */
                        (const char*    )"Test2_Task",/* �������� */
                        (uint16_t       )512,  /* ����ջ��С */
                        (void*          )NULL,/* ������ں������� */
                        (UBaseType_t    )2, /* ��������ȼ� */
                        (TaskHandle_t*  )&Test2_Task_Handle);/* ������ƿ�ָ�� */ 
  if(pdPASS == xReturn)
    printf("Create Test2_Task sucess...\n\n");
  
  vTaskDelete(AppTaskCreate_Handle); //ɾ��AppTaskCreate����
  
  taskEXIT_CRITICAL();            //�˳��ٽ���
}



/**********************************************************************
  * @ ������  �� Test1_Task
  * @ ����˵���� Test1_Task��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
static void Test1_Task(void* parameter)
{	
  while (1)
  {
//		if (NULL == Test_Ptr)
//		{
//			g_memsize = xPortGetFreeHeapSize();
//			printf("ϵͳ��ǰ�ڴ��СΪ %d �ֽڣ� ��ʼ�����ڴ�\n",g_memsize);
//			Test_Ptr = pvPortMalloc(1024);
//			if (NULL != Test_Ptr)
//			{
//				printf("�ڴ�����ɹ��� \n");
//				printf("���뵽���ڴ��ַΪ%#x\n",(int)Test_Ptr);
//				g_memsize = xPortGetFreeHeapSize();
//				printf("ϵͳ��ǰ�ڴ�ʣ����СΪ %d �ֽڣ� \n",g_memsize);
//			}
//		}
    vTaskDelay(1000);/* ��ʱ1000��tick */
  }
}

/**********************************************************************
  * @ ������  �� Test2_Task
  * @ ����˵���� Test2_Task��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
static void Test2_Task(void* parameter)
{	 
//	 BaseType_t xReturn = pdPASS;
//	uint32_t* recv_data;
  while (1)
  {
//		if (NULL != Test_Ptr)
//		{
//			printf("�ͷ��ڴ棡");
//			vPortFree(Test_Ptr); //�ͷ��ڴ�
//			Test_Ptr=NULL;
//			g_memsize = xPortGetFreeHeapSize();
//			printf("ϵͳ��ǰ�ڴ�ʣ����СΪ %d �ֽڣ� \n",g_memsize);
//		}
//		    xReturn = xQueueReceive( MQTT_Data_Queue,    /* ��Ϣ���еľ�� */
//                             &recv_data,      /* ���͵���Ϣ���� */
//                             0); /* �ȴ�ʱ�� 3000ms */

    vTaskDelay(1000);/* ��ʱ2000��tick */
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

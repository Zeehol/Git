#include "cJSON_Process.h"
#include "main.h"

/*******************************************************************
 *                          变量声明                               
 *******************************************************************/

extern QueueHandle_t MQTT_Data_Queue;
cJSON* cJSON_Root = NULL;    //json根节点

cJSON* cJSON_Data_Init(const char * name,const double led_statue)
{


  cJSON_Root = cJSON_CreateObject();   /*创建项目*/
  if(NULL == cJSON_Root)
  {
		PRINT_DEBUG("创建失败");
      return NULL;
  }
  cJSON_AddStringToObject(cJSON_Root, METHOD, DEFAULT_METHOD);  /*添加元素  键值对*/
  cJSON_AddStringToObject(cJSON_Root,  ID, DEFAULT_ID);
	cJSON* params = cJSON_AddObjectToObject(cJSON_Root,  PARAMS);
	cJSON_AddStringToObject(cJSON_Root,  VERSION, DEFAULT_VERSION);
	cJSON* statue = cJSON_AddNumberToObject(params,name,led_statue);
	
//	cJSON_ReplaceItemInObject(params,LEDG,params1);
//	cJSON_Update(params,LEDG,&i);

//	  char* p = cJSON_Print(cJSON_Root);  /*p 指向的字符串是json格式的*/	
//  PRINT_DEBUG("%s\n",p); /*p 指向的字符串是json格式的*/
//  vPortFree(p);
//  p = NULL;
	
  return cJSON_Root;

  
}
uint8_t cJSON_Update(const cJSON * const object,const char * const string,void *d)
{
  cJSON* node = NULL;    //json根节点
  node = cJSON_GetObjectItem(object,string);
  if(node == NULL)
    return NULL;
  if(cJSON_IsBool(node))
  {
    int *b = (int*)d;
//    printf ("d = %d",*b);
    cJSON_GetObjectItem(object,string)->type = *b ? cJSON_True : cJSON_False;
//    char* p = cJSON_Print(object);    /*p 指向的字符串是json格式的*/
    return 1;
  }
  else if(cJSON_IsString(node))
  {
    cJSON_GetObjectItem(object,string)->valuestring = (char*)d;
//    char* p = cJSON_Print(object);    /*p 指向的字符串是json格式的*/
    return 1;
  }
  else if(cJSON_IsNumber(node))
  {
    double *num = (double*)d;
//    printf ("num = %f",*num);
//    cJSON_GetObjectItem(object,string)->valueint = (double)*num;
    cJSON_GetObjectItem(object,string)->valuedouble = (double)*num;
//    char* p = cJSON_Print(object);    /*p 指向的字符串是json格式的*/
    return 1;
  }
  else
    return 1;
}

void Proscess(void* data)
{
	uint32_t* send_data;
	
  PRINT_DEBUG("开始解析JSON数据");
  cJSON *root,*params,*ledr,*ledg,*ledb;
  root = cJSON_Parse((char*)data); //解析成json形式
//	PRINT_DEBUG("%s\n",cJSON_Print(root));
	
	params = cJSON_GetObjectItem(root,"params");
	ledr = cJSON_GetObjectItem(params,"powerstate");
	if(ledr)
	{
		
		if(ledr->valueint)
		{
			LED_R_ON;
			*send_data = 1;
		xQueueSend( MQTT_Data_Queue, /* 消息队列的句柄 */
												&send_data,/* 发送的消息内容 */
												0 );        /* 等待时间 0 */

		}
		else
		{
			LED_R_OFF;
			*send_data = 2;
			xQueueSend( MQTT_Data_Queue, /* 消息队列的句柄 */
												&send_data,/* 发送的消息内容 */
												0 );        /* 等待时间 0 */
		}

	}
	ledg = cJSON_GetObjectItem(params,"PowerSwitch");
	if(ledg)
	{

		if(ledg->valueint)
		{
			LED_G_ON;
			*send_data = 3;
			xQueueSend( MQTT_Data_Queue, /* 消息队列的句柄 */
												&send_data,/* 发送的消息内容 */
												0 );        /* 等待时间 0 */
		}
		else
		{
			LED_G_OFF;
			*send_data = 4;
			xQueueSend( MQTT_Data_Queue, /* 消息队列的句柄 */
												&send_data,/* 发送的消息内容 */
												0 );        /* 等待时间 0 */
		}
	}
	ledb = cJSON_GetObjectItem(params,"LEDSwitch");
	if(ledb)
	{

		if(ledb->valueint)
		{
			LED_B_ON;
			*send_data = 5;
			xQueueSend( MQTT_Data_Queue, /* 消息队列的句柄 */
												&send_data,/* 发送的消息内容 */
												0 );        /* 等待时间 0 */
		}
		else
		{
			LED_B_OFF;
			*send_data = 6;
			xQueueSend( MQTT_Data_Queue, /* 消息队列的句柄 */
												&send_data,/* 发送的消息内容 */
												0 );        /* 等待时间 0 */
		}
	}
  cJSON_Delete(root);  //释放内存 
}









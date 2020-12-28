#include "cJSON_Process.h"
#include "main.h"

/*******************************************************************
 *                          ��������                               
 *******************************************************************/

extern QueueHandle_t MQTT_Data_Queue;
cJSON* cJSON_Root = NULL;    //json���ڵ�

cJSON* cJSON_Data_Init(const char * name,const double led_statue)
{


  cJSON_Root = cJSON_CreateObject();   /*������Ŀ*/
  if(NULL == cJSON_Root)
  {
		PRINT_DEBUG("����ʧ��");
      return NULL;
  }
  cJSON_AddStringToObject(cJSON_Root, METHOD, DEFAULT_METHOD);  /*���Ԫ��  ��ֵ��*/
  cJSON_AddStringToObject(cJSON_Root,  ID, DEFAULT_ID);
	cJSON* params = cJSON_AddObjectToObject(cJSON_Root,  PARAMS);
	cJSON_AddStringToObject(cJSON_Root,  VERSION, DEFAULT_VERSION);
	cJSON* statue = cJSON_AddNumberToObject(params,name,led_statue);
	
//	cJSON_ReplaceItemInObject(params,LEDG,params1);
//	cJSON_Update(params,LEDG,&i);

//	  char* p = cJSON_Print(cJSON_Root);  /*p ָ����ַ�����json��ʽ��*/	
//  PRINT_DEBUG("%s\n",p); /*p ָ����ַ�����json��ʽ��*/
//  vPortFree(p);
//  p = NULL;
	
  return cJSON_Root;

  
}
uint8_t cJSON_Update(const cJSON * const object,const char * const string,void *d)
{
  cJSON* node = NULL;    //json���ڵ�
  node = cJSON_GetObjectItem(object,string);
  if(node == NULL)
    return NULL;
  if(cJSON_IsBool(node))
  {
    int *b = (int*)d;
//    printf ("d = %d",*b);
    cJSON_GetObjectItem(object,string)->type = *b ? cJSON_True : cJSON_False;
//    char* p = cJSON_Print(object);    /*p ָ����ַ�����json��ʽ��*/
    return 1;
  }
  else if(cJSON_IsString(node))
  {
    cJSON_GetObjectItem(object,string)->valuestring = (char*)d;
//    char* p = cJSON_Print(object);    /*p ָ����ַ�����json��ʽ��*/
    return 1;
  }
  else if(cJSON_IsNumber(node))
  {
    double *num = (double*)d;
//    printf ("num = %f",*num);
//    cJSON_GetObjectItem(object,string)->valueint = (double)*num;
    cJSON_GetObjectItem(object,string)->valuedouble = (double)*num;
//    char* p = cJSON_Print(object);    /*p ָ����ַ�����json��ʽ��*/
    return 1;
  }
  else
    return 1;
}

void Proscess(void* data)
{
	uint32_t* send_data;
	
  PRINT_DEBUG("��ʼ����JSON����");
  cJSON *root,*params,*ledr,*ledg,*ledb;
  root = cJSON_Parse((char*)data); //������json��ʽ
//	PRINT_DEBUG("%s\n",cJSON_Print(root));
	
	params = cJSON_GetObjectItem(root,"params");
	ledr = cJSON_GetObjectItem(params,"powerstate");
	if(ledr)
	{
		
		if(ledr->valueint)
		{
			LED_R_ON;
			*send_data = 1;
		xQueueSend( MQTT_Data_Queue, /* ��Ϣ���еľ�� */
												&send_data,/* ���͵���Ϣ���� */
												0 );        /* �ȴ�ʱ�� 0 */

		}
		else
		{
			LED_R_OFF;
			*send_data = 2;
			xQueueSend( MQTT_Data_Queue, /* ��Ϣ���еľ�� */
												&send_data,/* ���͵���Ϣ���� */
												0 );        /* �ȴ�ʱ�� 0 */
		}

	}
	ledg = cJSON_GetObjectItem(params,"PowerSwitch");
	if(ledg)
	{

		if(ledg->valueint)
		{
			LED_G_ON;
			*send_data = 3;
			xQueueSend( MQTT_Data_Queue, /* ��Ϣ���еľ�� */
												&send_data,/* ���͵���Ϣ���� */
												0 );        /* �ȴ�ʱ�� 0 */
		}
		else
		{
			LED_G_OFF;
			*send_data = 4;
			xQueueSend( MQTT_Data_Queue, /* ��Ϣ���еľ�� */
												&send_data,/* ���͵���Ϣ���� */
												0 );        /* �ȴ�ʱ�� 0 */
		}
	}
	ledb = cJSON_GetObjectItem(params,"LEDSwitch");
	if(ledb)
	{

		if(ledb->valueint)
		{
			LED_B_ON;
			*send_data = 5;
			xQueueSend( MQTT_Data_Queue, /* ��Ϣ���еľ�� */
												&send_data,/* ���͵���Ϣ���� */
												0 );        /* �ȴ�ʱ�� 0 */
		}
		else
		{
			LED_B_OFF;
			*send_data = 6;
			xQueueSend( MQTT_Data_Queue, /* ��Ϣ���еľ�� */
												&send_data,/* ���͵���Ϣ���� */
												0 );        /* �ȴ�ʱ�� 0 */
		}
	}
  cJSON_Delete(root);  //�ͷ��ڴ� 
}









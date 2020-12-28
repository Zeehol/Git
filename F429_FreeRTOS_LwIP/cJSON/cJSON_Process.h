#ifndef _CJSON_PROCESS_H_
#define _CJSON_PROCESS_H_
#include "cJSON.h"
#include "stdint.h"


#define   MEN            "name"     
#define   TEMP_NUM        "temp"  
#define   HUM_NUM         "hum" 

#define   DEFAULT_NAME          "fire"     
#define   DEFAULT_TEMP_NUM       25.0 
#define   DEFAULT_HUM_NUM        50.0 

#define   METHOD          "method"
#define   ID              "id"
#define   PARAMS          "params"
#define   LEDR            "redLightOnOff"
#define   LEDG            "StatusLightSwitch"
#define   LEDB            "InfraredSwitch"
#define   VERSION         "version"

#define   DEFAULT_METHOD  "thing.event.property.post"
#define   DEFAULT_ID      "632739348"

#define   DEFAULT_VERSION "1.0.0"
 
#define   UPDATE_SUCCESS       1 
#define   UPDATE_FAIL          0

extern cJSON* cJSON_Data_Init(const char * name,const double led_statue);
uint8_t cJSON_Update(const cJSON * const object,const char * const string,void * d);
void Proscess(void* data);
#endif


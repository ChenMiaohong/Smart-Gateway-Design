#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

#include "smart_getway_parse.h"



#define CASE_FUNC_CONFIG "../config/smart_getway_config.json"
#define PTHREAD_NAME_LENGTH 32
static char *json_file = NULL;
char* json_file_load(const char *filename)
{
    FILE *fp = NULL;
    char *json_info = NULL;
    int size;

    if (filename == NULL) {
        return NULL;
    }
    if (!(fp = fopen(filename, "rb"))) {
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    json_info = (char *)malloc(size + 1);
    if (json_info == NULL) {
        printf("%s: Out of memory!", filename);
        return NULL;
    }
    rewind(fp);
    if (fread(json_info, size, 1, fp) <= 0) {
            printf("fopen json file for read failed!");
            fclose(fp);
            return NULL;
    }
    fclose(fp);
    return json_info;
}
int  get_sys_arch()
{
    cJSON *item;int arch_type = 0;
    if(!json_file) {
        json_file = json_file_load(CASE_FUNC_CONFIG);
        if (!json_file)
            return -1;
    }
   
    cJSON *object=cJSON_Parse(json_file);
    if (!object) {
        printf("get_inst_num Error before: [%s]\n",cJSON_GetErrorPtr());
        return -1;
    }

    item=cJSON_GetObjectItem(object,"arch");

    if(item != NULL) {
        printf("%s\n",item->valuestring);
        if(!strcmp(item->valuestring,"x86_linux")) {
            arch_type = X86;
        } 
        else if(!strcmp(item->valuestring,"arm_linux")) {
            arch_type = ARM;
        }
        else {
            arch_type = ERROR_VAL;
        }
    }
    cJSON_Delete(object);
    return arch_type;
}
int  get_sys_baud_rate()
{
    cJSON *item;int baud_rate = 0;
    if(!json_file) {
        json_file = json_file_load(CASE_FUNC_CONFIG);
        if (!json_file)
            return -1;
    }
   
    cJSON *object=cJSON_Parse(json_file);
    if (!object) {
        printf("get_inst_num Error before: [%s]\n",cJSON_GetErrorPtr());
        return -1;
    }

    item=cJSON_GetObjectItem(object,"baud_rate");

    if(item != NULL) {
        printf("%s\n",item->valuestring);
        baud_rate = item->valueint;
    }
    cJSON_Delete(object);
    return baud_rate;
}

int get_sys_server_ip(char *ip_str)
{
    cJSON *item;
    if(!json_file) {
        json_file = json_file_load(CASE_FUNC_CONFIG);
        if (!json_file)
            return -1;
    }
   
    cJSON *object=cJSON_Parse(json_file);
    if (!object) {
        printf("get_inst_num Error before: [%s]\n",cJSON_GetErrorPtr());
        return -1;
    }

    item=cJSON_GetObjectItem(object,"server_ip");

    if(item != NULL) {
        printf("%s\n",item->valuestring);
        strcpy(ip_str,item->valuestring);
    }
    cJSON_Delete(object);
    return ip_str;
}
int get_sys_serial_num()
{
    cJSON *item;int serial_num;
    if(!json_file) {
        json_file = json_file_load(CASE_FUNC_CONFIG);
        if (!json_file)
            return -1;
    }
   
    cJSON *object=cJSON_Parse(json_file);
    if (!object) {
        printf("get_inst_num Error before: [%s]\n",cJSON_GetErrorPtr());
        return -1;
    }

    item=cJSON_GetObjectItem(object,"serial_num");

    if(item != NULL) {
        printf("%s\n",item->valuestring);
        serial_num = item->valueint;
    }
    cJSON_Delete(object);
    return serial_num;
}

int get_sys_wifi_num()
{
    cJSON *item;int wifi_num = 0;
    if(!json_file) {
        json_file = json_file_load(CASE_FUNC_CONFIG);
        if (!json_file)
            return -1;
    }
   
    cJSON *object=cJSON_Parse(json_file);
    if (!object) {
        printf("get_inst_num Error before: [%s]\n",cJSON_GetErrorPtr());
        return -1;
    }

    item=cJSON_GetObjectItem(object,"wifi_num");

    if(item != NULL) {
        printf("%s\n",item->valuestring);
        wifi_num = item->valueint;
    }
    cJSON_Delete(object);
    return wifi_num;
}

int get_sys_usb_sensor_num()
{
    cJSON *item;int usb_sensor_num = 0;
    if(!json_file) {
        json_file = json_file_load(CASE_FUNC_CONFIG);
        if (!json_file)
            return -1;
    }
   
    cJSON *object=cJSON_Parse(json_file);
    if (!object) {
        printf("get_inst_num Error before: [%s]\n",cJSON_GetErrorPtr());
        return -1;
    }
  
    item=cJSON_GetObjectItem(object,"usb_sensor_num");
    printf("%s\n",item->valuestring);
    printf("----------1------------\n");

    if(item != NULL) {
        printf("%s\n",item->valuestring);
        usb_sensor_num = item->valueint;
    }
    printf("-----------2-----------\n");
    cJSON_Delete(object);
    return usb_sensor_num;
}

int get_sys_network_protocol()
{
    cJSON *item;int network_protocol_type = 0;
    if(!json_file) {
        json_file = json_file_load(CASE_FUNC_CONFIG);
        if (!json_file)
            return -1;
    }
   
    cJSON *object=cJSON_Parse(json_file);
    if (!object) {
        printf("get_inst_num Error before: [%s]\n",cJSON_GetErrorPtr());
        return -1;
    }

    item=cJSON_GetObjectItem(object,"serial_num");

    if(item != NULL) {
        printf("%s\n",item->valuestring);
        if(!strcmp(item->valuestring,"http")) {
            network_protocol_type = HTTP;
        } 
        else if(!strcmp(item->valuestring,"mqtt")) {
            network_protocol_type = MQTT;
        }
        else if(!strcmp(item->valuestring,"tcp")) {
            network_protocol_type = TCP;
        }
        else {
            network_protocol_type = ERROR_VAL;
        }
    }
    cJSON_Delete(object);
    return network_protocol_type;
}


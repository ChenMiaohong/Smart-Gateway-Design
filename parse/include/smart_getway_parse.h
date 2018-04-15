#ifndef __SMART_GETWAY_PARSE_H
#define __SMART_GETWAY_PARSE_H
#include <stdint.h>

/*
 **@brief the define of ERROR VALUE
 */
 #define ERROR_VAL -1001
 
/*
 *@brief the define of cpu arch
 */
 #define X86 1
 #define ARM 2

/*
 *@brief the define of network protocol type
 */
#define HTTP 1
#define MQTT 2
#define TCP  3







 int  get_sys_arch();
 int get_sys_network_protocol();
 int get_sys_usb_sensor_num();
 int get_sys_wifi_num();
 int get_sys_serial_num();
 char* json_file_load(const char *filename);

 #endif
 
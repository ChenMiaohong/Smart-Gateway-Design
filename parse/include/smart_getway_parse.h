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

/*
 *
 */
 #define SERIAL_NAME_LENGTH 16






 int get_sys_arch();
 int get_sys_network_protocol();
 int get_sys_usb_sensor_num();
 int get_sys_wifi_num();
 int get_sys_serial_num();
 char* get_sys_server_ip(char *ip_str);
 int get_sys_serial_dev_num(int serial_id);
 int get_sys_dev_info_sensor_num(int serial_id, int dev_id);
 char* get_sys_sensor_info_sensor_name(int serial_id, int dev_id, int sensor_id, char *sensor_name);
 char* get_sys_sensor_info_sensor_gather_cmd(int serial_id, int dev_id, int sensor_id, char *gather_cmd);
 char* json_file_load(const char *filename);

 #endif
 
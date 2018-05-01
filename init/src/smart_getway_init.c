#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef struct serial_controller {
    dev_controller_t *dev_control;
    char serial_name[NAME_MAX_LENGTH];
    int serial_id;
    int dev_num;
    int pipe[2];
} serial_controller_t;
typedef struct dev_controller {
    sensor_controller_t *sensor_control;
    char dev_name[NAME_MAX_LENGTH];
    int dev_id;
    int sensor_num;
} dev_controller_t;

typedef struct sensor_controller {
    char sensor_name[NAME_MAX_LENGTH];
    int serial_id;
    int sensor_type;
    char gather_cmd[NAME_MAX_LENGTH];
    int gather_freq;
} sensor_controller_t;
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
, serial_controller_t* fill_serial_controller(int serial_id)
{
    if (serial_id >= get_sys_serial_num()){
        return -1;
    }
    serial_controller_t* serial_controller = (serial_controller_t*)malloc(sizeof(serial_controller_t));
    if(!serial_controller) {
        printf("malloc serial_controller fail\n");
    }
    
    serial_controller->dev_num = get_sys_serial_dev_num();
    serial_controller->dev_control = ( dev_controller_t*)malloc(sizeof(dev_controller_t)*dev_num);
    if(!(serial_controller->dev_control) {
        printf("malloc serial_controller->dev_control fail\n");
    }
    snprintf(serial_controller->serial_name,SERIAL_NAME_LENGTH, "serial-%d", serial_id);
    return serial_controller;
}
int fill_dev_controller(int serial_id, int dev_id ,)
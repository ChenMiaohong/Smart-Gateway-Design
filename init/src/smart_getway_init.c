#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "smart_getway_init.h"
#include "smart_getway_parse.h"

case_controller_t* fill_case_controller() 
{
    case_controller_t* case_controller = (case_controller_t*)malloc(sizeof(case_controller_t));
    if(!case_controller) {
        printf("malloc serial_controller fail\n");
        return NULL;
    }
   
    case_controller->serial_control = (serial_controller_t*)malloc(sizeof(serial_controller_t)*get_sys_serial_num());
    if(!(case_controller->serial_control)) {
        printf("malloc case_controller->serial_control fail\n");
    }
    return case_controller;
}
int  fill_serial_controller(int serial_id, serial_controller_t* serial_controller)
{
    printf("_____fill_serial_controller0,%d\n",get_sys_serial_num());
    if (serial_id >= get_sys_serial_num()){
        return -1;
    }
    printf("_____fill_serial_controller1\n");
    int dev_num = get_sys_serial_dev_num(serial_id);
    printf("_____fill_serial_controller2\n");
    //serial_controller->dev_num = get_sys_serial_dev_num(serial_id);
    printf("_____fill_serial_controller2.1\n");
    serial_controller->dev_control = (dev_controller_t*)malloc(sizeof(dev_controller_t)*(dev_num));
    if(!serial_controller->dev_control) {
        printf("malloc serial_controller->dev_control fail\n");
    }
    printf("_____fill_serial_controller3\n");
    snprintf(serial_controller->serial_name,SERIAL_NAME_LENGTH, "serial-%d", serial_id);
    printf("_____fill_serial_controller4\n");
    return 0;
}
int  fill_dev_controller(int serial_id, int dev_id , dev_controller_t* dev_control)
{
    printf("______fill_dev_controller__start_____________\n");
    int sensor_num = get_sys_dev_info_sensor_num(serial_id, dev_id);
    dev_control->sensor_control = (sensor_controller_t*)malloc(sizeof(sensor_controller_t)*sensor_num);
    dev_control->dev_id = dev_id;
    dev_control->sensor_num = get_sys_dev_info_sensor_num(serial_id, dev_id);
    printf("______fill_dev_controller__end_____________\n");
    return 0;
}

int fill_sensor_controller(int serial_id, int dev_id, int sensor_id, 
                                            sensor_controller_t* sensor_control) {
    
  
    sensor_control->sensor_id = sensor_id;
    sensor_control->sensor_type = get_sys_sensor_info_sensor_type(serial_id, dev_id, sensor_id);
    get_sys_sensor_info_sensor_name(serial_id, dev_id, sensor_id,sensor_control->sensor_name);
    get_sys_sensor_info_sensor_gather_cmd(serial_id, dev_id, sensor_id,sensor_control->gather_cmd);
    sensor_control->gather_freq = get_sys_sensor_info_sensor_gather_freq(serial_id, dev_id, sensor_id);      
    return 0;
}
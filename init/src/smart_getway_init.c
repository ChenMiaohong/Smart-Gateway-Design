#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


serial_controller_t* fill_serial_controller(int serial_id)
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
int  fill_dev_controller(int serial_id, int dev_id , dev_controller_t* dev_control)
{
    
    int sensor_num = get_sys_dev_info_sensor_num(serial_id, dev_id);
    dev_control->sensor_control = (sensor_controller_t*)malloc(sizeof(sensor_controller_t)*sensor_num);
    dev_control->dev_id = dev_id;
    return 0;
}

int fill_sensor_controller(int serial_id, int dev_id, int sensor_id, 
                                            sensor_controller_t* sensor_control) {
    
    sensor_control->sensor_num = get_sys_dev_info_sensor_num(serial_id, dev_id);
    sensor_control->sensor_id = sensor_id;
    sensor_control->sensor_type = get_sys_sensor_info_sensor_type(serial_id, dev_id, sensor_id);
    get_sys_sensor_info_sensor_name(serial_id, dev_id, sensor_id,sensor_control->sensor_name);
    get_sys_sensor_info_sensor_gather_cmd(serial_id, dev_id, sensor_id,sensor_control->gather_cmd);
    sensor_control->gather_freq = get_sys_sensor_info_sensor_gather_freq(serial_id, dev_id, sensor_id);      
    return 0;
}
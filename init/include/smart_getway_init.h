#ifndef __SMART_GETWAY_INIT_H
#define __SMART_GETWAY_INIT_H
#include <stdint.h>

#define NAME_MAX_LENGTH 16


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


serial_controller_t* fill_serial_controller(int serial_id);
int  fill_dev_controller(int serial_id, int dev_id , dev_controller_t* dev_control);
int fill_sensor_controller(int serial_id, int dev_id, int sensor_id, 
                                            sensor_controller_t* sensor_control);

#endif

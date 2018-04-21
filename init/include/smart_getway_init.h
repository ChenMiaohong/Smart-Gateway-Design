#ifndef __SMART_GETWAY_INIT_H
#define __SMART_GETWAY_INIT_H
#include <stdint.h>

#define NAME_MAX_LENGTH 16


typedef struct serial_controller {
    char serial_name[NAME_MAX_LENGTH];
    int serial_id;
    int dev_num;
    int pipe[2];
} serial_controller_t;

typedef struct dev_controller {
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

typedef struct 
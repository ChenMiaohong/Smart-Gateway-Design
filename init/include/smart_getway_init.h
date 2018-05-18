#ifndef __SMART_GETWAY_INIT_H
#define __SMART_GETWAY_INIT_H

#include <stdint.h>

#define NAME_MAX_LENGTH 16
#define MAX_TIME_LEN 64

typedef struct msg_head {
    uint8_t length;
    uint8_t serial_id;
    uint8_t dev_id;
    uint8_t sensor_id;
    uint8_t resp;
    uint8_t type;
    uint8_t addr;
} msg_head_t;

typedef struct serial_ms_msg {
    uint16_t start;
    msg_head_t header;
    uint8_t data[0];
    char timestamp[MAX_TIME_LEN];
    uint32_t crc32;
} serial_ms_msg_t;

typedef struct sensor_controller {
    char sensor_name[NAME_MAX_LENGTH];
    int sensor_id;
    int sensor_type;
    char gather_cmd[NAME_MAX_LENGTH];
    int gather_freq;
} sensor_controller_t;

typedef struct dev_controller {
    sensor_controller_t *sensor_control;
    char dev_name[NAME_MAX_LENGTH];
    int dev_id;
    int sensor_num;
} dev_controller_t;

typedef struct serial_controller {
    dev_controller_t* dev_control;
    char serial_name[NAME_MAX_LENGTH];
    int serial_id;
    int dev_num;
    int pipe[2];
} serial_controller_t;

typedef struct case_controller {
    int serial_num;
    serial_controller_t* serial_control;

}case_controller_t;

int fill_serial_controller(int serial_id, serial_controller_t* serial_controller);
int fill_dev_controller(int serial_id, int dev_id , dev_controller_t* dev_control);
int fill_sensor_controller(int serial_id, int dev_id, int sensor_id, 
                                            sensor_controller_t* sensor_control);
case_controller_t* fill_case_controller();
int get_sys_cur_time(char* time_cur);
#endif

#ifndef __SMART_GETWAY_INIT_H
#define __SMART_GETWAY_INIT_H

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

#define NAME_MAX_LENGTH 16
#define MAX_TIME_LEN 64
#define MAX_CONTROL_LENGTH 8
#define CAM_DATA_LEN 16
#define MAX_SENSOR_LENGTH 8
/*
typedef struct serial_ms_msg {
    uint16_t start;
    msg_head_t header;
    uint8_t data[16];
    char timestamp[MAX_TIME_LEN];
    uint16_t crc32;
} serial_ms_msg_t;*/


typedef struct wifi_data_des {
    uint8_t wifi_id;
    char data[MAX_SENSOR_LENGTH];
    pthread_mutex_t wifi_lock;
} wifi_data_des_t;

typedef struct sensor_data_des {
    uint8_t serial_id;
    uint8_t dev_id;
    uint8_t sensor_id;
    char data[MAX_SENSOR_LENGTH];
    pthread_mutex_t sensor_lock;
} sensor_data_des_t;

typedef struct usb_cam_data {
    uint8_t usb_id;
    int length;
    char str_len[CAM_DATA_LEN];
    unsigned char* data;
    pthread_mutex_t cam_lock;
} usb_cam_data_t;

typedef struct merge_smart_getway_data {
    uint8_t sensor_num;
    sensor_data_des_t* sensor_des;
    uint8_t usb_num;
    usb_cam_data_t* cam_des;
    uint8_t wifi_num;
    wifi_data_des_t* wifi_des;
} merge_smart_getway_data_t;

typedef struct msg_head {
    uint8_t start;
    uint8_t type;
    uint8_t length;
    uint8_t serial_id;
    uint8_t dev_id;
    uint8_t sensor_id;
    uint8_t addr;
} msg_head_t;

typedef struct serial_ms_msg {
    msg_head_t header;
    uint8_t data[0];
}serial_ms_msg_t;

typedef struct server_control_cmd {
    uint8_t serial_id;
    uint8_t dev_id;
    uint8_t sensor_id;
    char control_cmd[MAX_CONTROL_LENGTH];
} server_control_cmd_t;


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
#ifdef __cplusplus
}
#endif

#endif

#ifndef SMART_GETWAY_SERIAL_TASK_H
#define SMART_GETWAY_SERIAL_TASK_H
#include "smart_getway_forward.h"

#define MAX_SENSOR_LENGTH 8
typedef struct senial_data_des {
    uint8_t serial_id;
    uint8_t dev_id;
    uint8_t sensor_id;
    char data[MAX_SENSOR_LENGTH];
} sensor_data_des_t;

int uart_send(int fd, uint8_t *data, int datalen);
int uart_recv(int fd, uint8_t* data, int datalen);
void* do_serial_task(void* param);


extern int add_send_queue(server_control_cmd_t server_control_data);
extern int size_send_queue();
extern int del_send_queue(server_control_cmd_t* server_control_data);



#endif
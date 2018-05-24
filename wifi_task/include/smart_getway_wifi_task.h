#ifndef SMART_GETWAY_WIFI_TASK_H
#define SMART_GETWAY_WIFI_TASK_H







typedef struct wifi_data_des {
    uint8_t wifi_id;
    char data[MAX_SENSOR_LENGTH];
} wifi_data_des_t;

void* do_wifi_task(void* param);





#endif

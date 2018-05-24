#ifndef SMART_GETWAY_MERGE_H
#define SMART_GETWAY_MERGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <smart_getway_serial_task.h>
#include <smart_getway_usb_cam.h>
#include <smart_getway_wifi_task.h>





typedef struct merge_smart_getway_data {
    uint8_t sensor_num;
    sensor_data_des_t* sensor_des;
    uint8_t usb_num;
    usb_cam_data_t* cam_des;
    uint8_t wifi_num;
    wifi_data_des_t* wifi_des;
} merge_smart_getway_data_t;




void* read_func(void* param);

void* write_func(void* param);



#ifdef __cplusplus
}
#endif

#endif



#ifndef SMART_GETWAY_USB_CAM_H
#define SMART_GETWAY_USB_CAM_H
#include "smart_getway_init.h"
#define CAM_DATA_LEN 16
#ifdef __cplusplus
extern "C"
{
#endif

typedef struct usb_cam_data {
    uint8_t usb_id;
    int length;
    char str_len[CAM_DATA_LEN];
    unsigned char* data;
    pthread_mutex_t cam_lock;
} usb_cam_data_t;

int get_usb_cam(int usb_id, usb_cam_data_t* cam_data);
void* do_usb_task(void* param);

#ifdef __cplusplus
}

#endif
#endif

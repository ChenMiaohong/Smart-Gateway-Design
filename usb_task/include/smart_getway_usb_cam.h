#ifndef SMART_GETWAY_USB_CAM_H
#define SMART_GETWAY_USB_CAM_H
#include "smart_getway_init.h"

#ifdef __cplusplus
extern "C"
{
#endif



int get_usb_cam(int usb_id, usb_cam_data_t* cam_data);
void* do_usb_task(void* param);
int str_to_mat(unsigned char* str,int length);
#ifdef __cplusplus
}

#endif
#endif

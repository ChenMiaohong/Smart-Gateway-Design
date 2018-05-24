#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "smart_getway_usb_cam.h"
#include "smart_getway_parse.h"
using namespace cv;
using namespace std;


int get_usb_cam(int usb_id, usb_cam_data_t* cam_data) 
{
    Mat image;
    VideoCapture capture(0);
    capture>>image;
    vector<uchar> data_encode;
    imencode(".jpg", image, data_encode);
    int len_encode = data_encode.size();
    string len = to_string(len_encode);
    int length = len.length();
    for (int i = 0; i < 16 - length; i++) {
        len = len + " ";
    }
    //pthread_mutex_lock(&cam_data->cam_lock);
    cam_data->length = data_encode.size();
    printf("%d\n",data_encode.size() );
    memcpy(cam_data->str_len, len.c_str(), length);
    cam_data->data = (unsigned char*)malloc(cam_data->length);
    unsigned char* v_ptr = &data_encode[0];
    memcpy(cam_data->data, v_ptr, cam_data->length);
    //pthread_mutex_unlock(&cam_data->cam_lock);
    return 0;
}


void* do_usb_task(void* param)
{
    int usb_id;
    int usb_num = get_sys_usb_sensor_num();
    while(1){
        for(usb_id = 0; usb_id < usb_num; usb_id++) {
            usb_cam_data_t cam_data;
            get_usb_cam(usb_id, &cam_data);
            free(cam_data.data);

        }
           





        sleep(5);
    }

    return 0;
}
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
#include "base64.h"
#include "smart_getway_usb_cam.h"
#include "smart_getway_parse.h"
using namespace cv;
using namespace std;

extern merge_smart_getway_data_t* smart_getway_data;


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
    int cam_data_length = data_encode.size();
    
    printf("%d\n",data_encode.size() );
   
    unsigned char* v_ptr = &data_encode[0];
    //base64_encode(cam_data_temp, (unsigned char*)v_ptr, cam_data_length, MAX_UPLOAD_DATA_LENGTH);
    
    pthread_mutex_lock(&cam_data->cam_lock);
    free(cam_data->data);
    cam_data->data = (char*)malloc(cam_data_length);
    cam_data->usb_id = usb_id;
    cam_data->length = cam_data_length;
    memcpy(cam_data->str_len, len.c_str(), length);
    memcpy(cam_data->data, v_ptr, cam_data->length);
    pthread_mutex_unlock(&cam_data->cam_lock);
    return 0;
}

int str_to_mat(unsigned char* str, int length)
{
    namedWindow("server",CV_WINDOW_AUTOSIZE);
    vector<uchar> data;
    data.resize(length);
    for (int i = 0; i < length; i++)
    {
        data[i] = str[i];
    }
    Mat img_decode;
    img_decode = imdecode(data, CV_LOAD_IMAGE_COLOR);
    while(1){
        imshow("server", img_decode);
        waitKey(30);
    }

    return 0;

}
void* do_usb_task(void* param)
{
    int usb_id;
    //cam_data_temp = (char*)malloc(MAX_UPLOAD_DATA_LENGTH);
    int usb_num = get_sys_usb_sensor_num();
    for(usb_id = 0; usb_id < usb_num; usb_id++) {
        (smart_getway_data->cam_des + usb_id)->data = NULL;
        

    }
          
    while(1){
        for(usb_id = 0; usb_id < usb_num; usb_id++) {
            get_usb_cam(usb_id, (smart_getway_data->cam_des + usb_id));
         

        }
           





        sleep(5);
    }

    return 0;
}
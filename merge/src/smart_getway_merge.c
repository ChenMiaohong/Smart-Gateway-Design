#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include <cjson/cJSON.h>
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <termios.h> 
#include <smart_getway_init.h>

#define MAXLINE 1024


extern merge_smart_getway_data_t* smart_getway_data;
extern unsigned char* server_json;
unsigned char* temp_data = NULL;
char* cam_data_temp = NULL;
int merge_sys_data()
{   int sensor_id, usb_id, wifi_id;
    memset(server_json, 0, MAX_UPLOAD_DATA_LENGTH);
    printf("------------------------------------==------------------------------------\n");
    printf("sensor_num:%d,usb_num:%d,wifi_num:%d\n",smart_getway_data->sensor_num,smart_getway_data->usb_num,
    smart_getway_data->wifi_num);
    strcpy(server_json,"{");
    
   
    strcat(server_json,"\"sensor_data_des\": [");
    for(sensor_id = 0; sensor_id < (smart_getway_data -> sensor_num); sensor_id++) {
        memset(temp_data, 0, MAX_UPLOAD_DATA_LENGTH);
        pthread_mutex_lock(&((smart_getway_data->sensor_des + sensor_id)->sensor_lock));
        snprintf(temp_data, MAX_UPLOAD_DATA_LENGTH, "{\"serial_id\": %d,\"dev_id\": %d,\"sensor_id\": \"%d\",\"data\": \"%s\"}",
        (smart_getway_data -> sensor_des + sensor_id) -> serial_id, 
        (smart_getway_data -> sensor_des + sensor_id) -> dev_id,  
        (smart_getway_data -> sensor_des + sensor_id) -> sensor_id, (smart_getway_data -> sensor_des + sensor_id) -> data);
        strcat(server_json, temp_data);
        if(sensor_id == (smart_getway_data -> sensor_num - 1 )) {
             strcat(server_json, "]");
        }
        else {
            strcat(server_json, ",");
        }
        pthread_mutex_unlock(&((smart_getway_data->sensor_des + sensor_id)->sensor_lock));
    }
    if(smart_getway_data -> usb_num >= 1) {
        strcat(server_json, ",");
        strcat(server_json,"\"usb_cam_data\": [");
    }
    
    for(usb_id = 0; usb_id < (smart_getway_data -> usb_num); usb_id++) {
        memset(temp_data, 0, MAX_UPLOAD_DATA_LENGTH);
        memset(cam_data_temp, 0, MAX_UPLOAD_DATA_LENGTH);
        base64_encode(cam_data_temp, (unsigned char*)(smart_getway_data->cam_des + usb_id) -> data,
        (smart_getway_data->cam_des + usb_id) -> length, MAX_UPLOAD_DATA_LENGTH);
        pthread_mutex_lock(&((smart_getway_data->cam_des + usb_id) -> cam_lock));
        snprintf(temp_data, 1024*1024*11, "{\"usb_id\": %d,\"length\": %d,\"str_len\": \"%s\",\"data\": \"%s\"}",
        (smart_getway_data->cam_des + usb_id) -> usb_id,
        (smart_getway_data->cam_des + usb_id) -> length,
        (smart_getway_data->cam_des + usb_id) -> str_len,
        cam_data_temp);
       
        strcat(server_json, temp_data);
       
        if(usb_id == (smart_getway_data -> usb_num - 1 )) {
             strcat(server_json, "]");
        }
        else {
            strcat(server_json, ",");
        }
        pthread_mutex_unlock(&((smart_getway_data->cam_des + usb_id) -> cam_lock));
    }
    if(smart_getway_data -> wifi_num >= 1) {
        strcat(server_json, ",");
        strcat(server_json,"\"wifi_data_des\": [");
    }
    for(wifi_id = 0; wifi_id < (smart_getway_data -> wifi_num); wifi_id++) {
        memset(temp_data, 0, MAX_UPLOAD_DATA_LENGTH);
        pthread_mutex_lock(&((smart_getway_data->wifi_des + wifi_id) -> wifi_lock));
        snprintf(temp_data, 1024*1024*11, "{\"wifi_id\": %d,\"data\": \"%s\"}",
        (smart_getway_data->wifi_des + wifi_id) -> wifi_id,
        (smart_getway_data->wifi_des + wifi_id) -> data);
        strcat(server_json, temp_data);
        if(wifi_id == (smart_getway_data -> wifi_num - 1 )) {
             strcat(server_json, "]");
        }
        else {
            strcat(server_json, ",");
        }
        pthread_mutex_unlock(&((smart_getway_data->wifi_des + wifi_id) -> wifi_lock));
    }
    strcat(server_json,"}");
    /*
    int fd = open("./base_test_merge.txt",O_CREAT|O_RDWR,0666);
    if(fd < 0) {
        printf("err\n");
    }
    int n = write(fd, server_json, strlen(server_json));
    close(fd);
    int fd1 = open("./base_test_image.txt",O_CREAT|O_RDWR,0666);
    if(fd1 < 0) {
        printf("err\n");
    }
    int n1 = write(fd1, cam_data_temp, strlen(cam_data_temp));
    close(fd1);*/
    //printf("#server_json %s", server_json);
    return 0;

}


// int get_usb_cam(int usb_id, usb_cam_data_t* cam_data) 
// {
//     Mat image;
//     VideoCapture capture(0);
//     capture>>image;
//     vector<uchar> data_encode;
//     imencode(".jpg", image, data_encode);

//     int len_encode = data_encode.size();
//     string len = to_string(len_encode);
//     int length = len.length();
//     for (int i = 0; i < 16 - length; i++) {
//         len = len + " ";
//     }
//     int cam_data_length = data_encode.size();
    
//     printf("%d\n",data_encode.size() );
   
//     memset(cam_data_temp, 0, MAX_UPLOAD_DATA_LENGTH);
//     unsigned char* v_ptr = &data_encode[0];
    
//     base64_encode(cam_data_temp, (unsigned char*)v_ptr, cam_data_length, MAX_UPLOAD_DATA_LENGTH);
    
    
//     pthread_mutex_lock(&cam_data->cam_lock);
//     free(cam_data->data);
//     cam_data->data = (char*)malloc(strlen(cam_data_temp));
//     cam_data->usb_id = usb_id;
//     cam_data->length = cam_data_length;
//     memcpy(cam_data->str_len, len.c_str(), length);
//     memcpy(cam_data->data, cam_data_temp, strlen(cam_data_temp));
//     int fd = open("./base_test2.txt",O_CREAT|O_RDWR,0666);
//     if(fd < 0) {
//         printf("err\n");
//     }
//     int n = write(fd, cam_data->data, strlen(cam_data->data));
//     close(fd);

//     int fd1 = open("./base_test3.txt",O_CREAT|O_RDWR,0666);
//     if(fd < 0) {
//         printf("err\n");
//     }
//     int n1 = write(fd1, cam_data_temp, strlen(cam_data_temp));
//     close(fd1);
//     //printf("####################################################cam_data:%s#\n",cam_data_temp);
//     pthread_mutex_unlock(&cam_data->cam_lock);
//     return 0;
// }

void* read_func(void* param) {
    int client_sockfd = *((int*)(param));
    char readbuff[MAXLINE];  
    int n;
    while(1)  
    {  
        n = recv(client_sockfd, readbuff, MAXLINE, 0);  /*recv 在这里是阻塞运行*/  
        if(n > 0)  
        {  
            /*server_control_cmd_t cmd_msg;
            memcpy(&cmd_msg, readbuff, sizeof(server_control_cmd_t));
            add_send_queue(cmd_msg);
            printf("before size: %d \n", size_send_queue());*/
            printf("server recv data: %s \n",readbuff);  
        }  
    }
}

void* write_func(void* param)  
{  
    int client_sockfd = *((int*)(param));
    char writebuff[MAXLINE];  
    char* write = "I am client";   
    int num = 0;  
    memset(&writebuff,0,sizeof(writebuff));
    temp_data = (char*)malloc(1024*1024*10);
    if(!temp_data) {
        printf("temp_data alloc fail\n");
        goto out;
    }
    cam_data_temp = (char*)malloc(MAX_UPLOAD_DATA_LENGTH);
    if(!cam_data_temp) {
        printf("cam_data_temp alloc fail\n");
        goto out;
    }
    while(1)  
    {  
        sleep(1); 
        merge_sys_data();
        int ret = send(client_sockfd,server_json,strlen(server_json)+1,MSG_DONTWAIT); 
        if(ret < 0) {
            printf("client send fail\n");
        }  
    } 
out:
    pthread_exit(NULL);
}  

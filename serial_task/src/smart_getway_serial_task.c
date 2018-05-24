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
#include "smart_getway_init.h"
#include "smart_getway_parse.h"

extern case_controller_t* case_controller;
int uart_send(int fd, uint8_t *data, int datalen)  
{  
    int len = 0;  
    int i;
    len = write(fd, data, datalen);//实际写入的长度 ; 
    for(i = 0; i < datalen; i++) {
        printf("i = %d, data = %x\n", i, data[i]);
    }
    printf("len:%d,datalen=%d\n", len, datalen); 
    if(len == datalen) {  
        return len;  
    } else {  
        tcflush(fd, TCOFLUSH);//TCOFLUSH刷新写入的数据但不传送  
        return -1;  
    }  
      
    return 0;  
}  
  
 
int uart_recv(int fd, uint8_t* data, int datalen)  
{  
    int len=0, ret = 0;
    fd_set fs_read;
    struct timeval tv_timeout;
      
    FD_ZERO(&fs_read);
    FD_SET(fd, &fs_read);
    tv_timeout.tv_sec  = (10*20/115200+2);
    tv_timeout.tv_usec = 0;
      
    ret = select(fd+1, &fs_read, NULL, NULL, &tv_timeout);
    printf("ret = %d\n", ret);
    //如果返回0，代表在描述符状态改变前已超过timeout时间,错误返回-1  
    if (FD_ISSET(fd, &fs_read)) {
        len = read(fd, data, datalen);
        printf("len = %d\n", len);
        return len;
    } else {
        perror("select");
        return -1;
    }
    return 0;
}


void* do_serial_task(void* param) 
{
    int serial_id = 0;
    int dev_id = 0;
    int sensor_id = 0;
    printf("get_sensor_data\n");
    while(1) {
        int s_fd = serial_init();
        for(serial_id = 0; serial_id < case_controller->serial_num; serial_id++) {
            for(dev_id = 0; dev_id < (case_controller->serial_control + serial_id)->dev_num; dev_id++) {
                for(sensor_id = 0; sensor_id < ((case_controller->serial_control + serial_id)->dev_control+dev_id)->sensor_num ; sensor_id++) {
                    int datalen = strlen(((((case_controller->serial_control + serial_id)->dev_control+dev_id)->sensor_control+sensor_id)->gather_cmd));
                    printf("sensor_name:%d,%s\n",datalen, ((((case_controller->serial_control + serial_id)->dev_control+dev_id)->sensor_control+sensor_id)->gather_cmd));
                    serial_ms_msg_t *msg = (serial_ms_msg_t *)malloc(sizeof(serial_ms_msg_t)+datalen);
                    serial_ms_msg_t msg1;
                    msg->header.start = 0x55;
                    msg->header.type = 0x55;
                    msg->header.length = datalen + 4;
                    msg->header.serial_id = serial_id;
                    msg->header.dev_id = dev_id;
                    msg->header.sensor_id = sensor_id;
                    msg->header.addr = 0x01;
                    memcpy(msg->data, ((((case_controller->serial_control + serial_id)->dev_control+dev_id)->sensor_control+sensor_id)->gather_cmd), datalen);
                    printf("struct size:%d\n",sizeof(serial_ms_msg_t)+datalen);
                   
                    uart_send(s_fd, (uint8_t*)msg, sizeof(serial_ms_msg_t)+datalen);
                }
            }
        }
        if(size_send_queue() > 0) {
            while(size_send_queue() > 0) {
                printf("after size: %d \n", size_send_queue());
                server_control_cmd_t server_cmd;
                del_send_queue(&server_cmd);
                uart_send(s_fd, (uint8_t*)&server_cmd, sizeof(server_control_cmd_t));
            }
        }
        close(s_fd);
        sleep(1);
    }
    pthread_exit(NULL);
}

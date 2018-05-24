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
void* read_func(void* param) {
    int client_sockfd = *((int*)(param));
    char readbuff[MAXLINE];  
    int n;
    while(1)  
    {  
        n = recv(client_sockfd, readbuff, MAXLINE, 0);  /*recv 在这里是阻塞运行*/  
        if(n > 0)  
        {  
            server_control_cmd_t cmd_msg;
            memcpy(&cmd_msg, readbuff, sizeof(server_control_cmd_t));
            add_send_queue(cmd_msg);
            printf("before size: %d \n", size_send_queue());
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
    while(1)  
    {  
        sleep(1); 
        //get_sensor_data(1);
        int ret = send(client_sockfd,write,strlen(write)+1,MSG_DONTWAIT); 
        if(ret < 0) {
            printf("client send fail\n");
        }  
    }  
}  

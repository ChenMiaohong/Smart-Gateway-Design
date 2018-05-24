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
#include <smart_getway_merge.h>
#include <smart_getway_net.h>

void* data_forward_deal(void* param)
{

    int serial_id = 0;
    int status = -1; 
    int addrlen;
    int client_sockfd;  
    struct sockaddr_in server_addr;  /*服务器地址结构*/  
    pthread_t read_id, write_id;
 
    if((client_sockfd=socket(PF_INET,SOCK_STREAM,0)) < 0) {  
        perror("socket");  
        goto out;
    }  
    /*设置服务端地址*/  
    addrlen = sizeof(struct sockaddr_in);  
    memset(&server_addr, 0, addrlen);  
    server_addr.sin_family = AF_INET;    /*AF_INET表示 IPv4 Intern 协议*/  
    server_addr.sin_addr.s_addr = inet_addr("120.77.46.12");
    //server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8000); /*设置端口*/  
      
    /*绑定地址结构到套接字描述符*/  
    if(connect(client_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) { 
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
    }  
     if(pthread_create(&read_id,NULL,read_func,&client_sockfd)) {
        printf("pthread_create read_func err\n");
    }  
    if(pthread_create(&write_id,NULL,write_func,&client_sockfd)) {  
        printf("pthread_create write_func err\n");
    }
    //signal(SIGINT,stop); /*注册SIGINT 信号*/
    while(1){
        //printf("do_serial_task:pid = %d, parent pid = %d\n", getpid(), getppid());
        sleep(5);
    }
out:
    pthread_exit(NULL);
}
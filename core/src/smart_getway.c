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
#include "zlog.h"
#include "s2j.h"
#include "smart_getway.h"
#include "smart_getway_log.h"
#include "smart_getway_parse.h"
#include "smart_getway_init.h"

case_controller_t* case_controller = NULL;
char *json_file = NULL;
pthread_mutex_t queue_lock = PTHREAD_MUTEX_INITIALIZER;

/*
test_module_list:
name:pubsub_msg_id
name:cbk_msg_id
name:manurcv_msg_id
*/

int sys_init() {
    int serial_id = 0;
    int dev_id = 0;
    int sensor_id = 0;
    case_controller = fill_case_controller();
    printf("----=----\n");
    for(serial_id = 0; serial_id < get_sys_serial_num(); serial_id++) {
        printf("--serial_id:%d,serial_num = %d---\n",serial_id, get_sys_serial_num());
        fill_serial_controller(serial_id, (case_controller->serial_control + serial_id));
        printf("----1----\n");
        for(dev_id = 0; dev_id < get_sys_serial_dev_num(serial_id); dev_id++) {
            fill_dev_controller(serial_id, dev_id, ((case_controller->serial_control + serial_id)->dev_control+dev_id));
          
            for(sensor_id = 0; sensor_id < get_sys_dev_info_sensor_num(serial_id, dev_id) ; sensor_id++) {
                fill_sensor_controller(serial_id, dev_id, sensor_id, 
                 ((case_controller->serial_control + serial_id)->dev_control+dev_id)->sensor_control+sensor_id);
            }
        }
    }
    printf("%d\n",case_controller->serial_num);
    printf("%d\n",(case_controller->serial_control + 0)->dev_num);
    printf("%d\n",(((case_controller->serial_control + 0)->dev_control+0)->sensor_num));
    return 0;
}
/*
void sensor_deal(void* param)
{
   while(1) {


   }



}
static finish_dev_pthread_task()
{
    int status = -1;
    pthread_t  ntid;
    ntid = pthread_create(&ntid, NULL, sensor_deal, NULL);
    return 0;
}*/

int uart_send(int fd, char *data, int datalen)  
{  
    int len = 0;  
    len = write(fd, data, datalen);//实际写入的长度  
    if(len == datalen) {  
        return len;  
    } else {  
        tcflush(fd, TCOFLUSH);//TCOFLUSH刷新写入的数据但不传送  
        return -1;  
    }  
      
    return 0;  
}  
  
 
int uart_recv(int fd, char *data, int datalen)  
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

char * get_sensor_data(int fd) {

    int serial_id = 0;
    int dev_id = 0;
    int sensor_id = 0;
    printf("get_sensor_data\n");
    int fd = serial_init();
    for(serial_id = 0; serial_id < case_controller->serial_num; serial_id++) {
        for(dev_id = 0; dev_id < (case_controller->serial_control + serial_id)->dev_num; dev_id++) {
            for(sensor_id = 0; sensor_id < ((case_controller->serial_control + serial_id)->dev_control+dev_id)->sensor_num ; sensor_id++) {
                printf("sensor_name:%s\n",((((case_controller->serial_control + serial_id)->dev_control+dev_id)->sensor_control+sensor_id)->sensor_name));

            }
        }
    }
    return NULL;
}
static int do_dev_task(int serial_id)
{
    int status = -1;
    int dev_num = get_sys_serial_dev_num(serial_id);
    int dev_id = 0;

    for(dev_id = 0; dev_id < dev_num; dev_id++) {
        status= fork();
        if(status == 0 || status == -1) {
            break;
        } 
    }
    if(status == -1) {
      printf("the process fork fail \n");
    } else if(status == 0) {
        do_dev_task(serial_id);
    } else {
        printf("the parent\n");
    }
    while(1) {
        printf("do_dev_task:pid = %d, parent pid = %d\n", getpid(), getppid());
        sleep(5);
    }
    return 0;
}


void* read_func(void* param) {
    int client_sockfd = *((int*)(param));
    char readbuff[MAXLINE];  
    int n;
     printf("-------------read_func-----------------\n");  
    while(1)  
    {  
        n = recv(client_sockfd, readbuff, MAXLINE, 0);  /*recv 在这里是阻塞运行*/  
        if(n > 0)  
        {  
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
        get_sensor_data(1);
        int ret = send(client_sockfd,write,strlen(write)+1,MSG_DONTWAIT); 
        if(ret < 0) {
            printf("client send fail\n");
        }  
    }  
}  

static int do_serial_task()
{

    int serial_num = get_sys_serial_num();
    int serial_id = 0;
    int status = -1;
    char buff[MAXLINE];   
    int addrlen;
    int client_sockfd;  
    struct sockaddr_in server_addr;  /*服务器地址结构*/  
    pthread_t read_id, write_id;
 
    if((client_sockfd=socket(PF_INET,SOCK_STREAM,0)) < 0) {  
        perror("socket");  
        return -1;  
    }  
    /*设置服务端地址*/  
    addrlen = sizeof(struct sockaddr_in);  
    memset(&server_addr, 0, addrlen);  
    server_addr.sin_family = AF_INET;    /*AF_INET表示 IPv4 Intern 协议*/  
    //server_addr.sin_addr.s_addr = inet_addr("120.77.46.12");
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8080); /*设置端口*/  
      
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
        printf("do_serial_task:pid = %d, parent pid = %d\n", getpid(), getppid());
        sleep(5);
    }

    return 0;
}
static int do_wifi_task()
{
    while(1){
        printf("do_wifi_task:pid = %d, parent pid = %d\n", getpid(), getppid());
        sleep(5);
    }
    return 0;
}
static int do_usb_task()
{
    while(1){
        printf("do_usb_task:pid = %d, parent pid = %d\n", getpid(), getppid());
        sleep(5);
    }

    return 0;
}

int create_child_process()
{
  int i;
  int status = -1;
  for(i = 0; i < 5 ; i++) {
      status= fork();
      if(status == 0 || status == -1) {
          break;
      }
  }
  if(status == -1) {
      printf("the process fork fail \n");
  } else if(status == 0) {
        if(i == 1) {
            //printf("the i = 1\n");
            do_serial_task();
        }
        if(i == 2) {
            //printf("the i = 2\n");
            do_wifi_task();
        }
        if(i == 3) {
            do_usb_task();
            printf("the i = 3\n");
        }
  } else {
      while(1) {
        printf("the parent,%d\n",getpid());
        sleep(3);
    }
     
  }
  return 0;
}





int main()
{
    Init_LogDir();
    int ret = zlog_init(DCOS_PRETEST_LOG_CONFIG);
    if (ret) {
	    printf("dcos init log failed, %d\n", ret);
     }
    char ip_addr[18];
    char sensor_name[32];
    char gather_cmd[8];
    int arch_type = get_sys_arch();
    printf("the sys arch = %d \n",arch_type);
   
    printf("the wifi_num = %d\n",get_sys_wifi_num());
    printf("the sys serial num =%d\n",get_sys_serial_num());
    printf("the usb_sensor_num = %d\n",get_sys_usb_sensor_num());
    printf("the network_protocol = %d\n",get_sys_network_protocol());
    strcpy(ip_addr,get_sys_server_ip(ip_addr));
    printf("%s\n",ip_addr);
    strcpy(sensor_name,get_sys_sensor_info_sensor_name(0,0,0,sensor_name));
    printf("%s \n",sensor_name);
    printf("gather_freq: %d \n",get_sys_sensor_info_sensor_gather_freq(0,0,0));
    strcpy(gather_cmd, get_sys_sensor_info_sensor_gather_cmd(0,0,0,gather_cmd));
    printf("gather_cmd: %s \n",gather_cmd);
    printf("dev_num:%d \n",get_sys_serial_dev_num(0));
    printf("sensor_num:%d \n",get_sys_dev_info_sensor_num(0,0));
  
    sys_init();
   

    /*serialize Student structure object */
    //cJSON *json_student = struct_to_json(&orignal_student_obj);
    //char *rendered=cJSON_Print(json_student);
    printf("------1--------\n");
    printf("%s\n", json_file);
    cJSON *object=cJSON_Parse(json_file);
    if (!object) {
        printf("test Error before: [%s]\n",cJSON_GetErrorPtr());
        return -1;
    }
    printf("the main parent,%d\n",getpid());
    create_child_process();
    
    return 0;
}

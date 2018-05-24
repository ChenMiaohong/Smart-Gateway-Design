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
#include "zlog.h"
#include "s2j.h"
#include "smart_getway.h"
#include "smart_getway_validation.h"
#include "smart_getway_serial_task.h"

#include "smart_getway_wifi_task.h"
#include "smart_getway_log.h"
#include "smart_getway_parse.h"
#include "smart_getway_init.h"


#include "smart_getway_usb_cam.h"
#include "smart_getway_net.h"


char *json_file = NULL;
pthread_mutex_t queue_lock = PTHREAD_MUTEX_INITIALIZER;


/*
test_module_list:
name:pubsub_msg_id
name:cbk_msg_id
name:manurcv_msg_id
*/


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



/*char * get_sensor_data(int fd) {

    int serial_id = 0;
    int dev_id = 0;
    int sensor_id = 0;
    printf("get_sensor_data\n");
    int s_fd = serial_init();
    for(serial_id = 0; serial_id < case_controller->serial_num; serial_id++) {
        for(dev_id = 0; dev_id < (case_controller->serial_control + serial_id)->dev_num; dev_id++) {
            for(sensor_id = 0; sensor_id < ((case_controller->serial_control + serial_id)->dev_control+dev_id)->sensor_num ; sensor_id++) {
                int datalen = strlen(((((case_controller->serial_control + serial_id)->dev_control+dev_id)->sensor_control+sensor_id)->gather_cmd));
                printf("sensor_name:%d,%s\n",datalen, ((((case_controller->serial_control + serial_id)->dev_control+dev_id)->sensor_control+sensor_id)->gather_cmd));
                serial_ms_msg_t msg;
                serial_ms_msg_t msg1;
                msg.header.length = datalen;
                msg.header.serial_id = serial_id;
                msg.header.dev_id = dev_id;
                msg.header.sensor_id = sensor_id;
                memcpy(msg.data, ((((case_controller->serial_control + serial_id)->dev_control+dev_id)->sensor_control+sensor_id)->gather_cmd), msg.header.length);
                msg.crc32 = CRC32_Table(msg.data, strlen((char *)msg.data), msg.crc32);
                get_sys_cur_time(msg.timestamp);
                printf("struct size:%d\n",sizeof(serial_ms_msg_t));
                uart_send(s_fd, (char*)&msg, sizeof(serial_ms_msg_t));
               
                del_send_queue(&msg1);
                printf("%d,%d,%d,%d\n", msg1.header.length, msg1.header.serial_id, msg1.header.dev_id, msg1.header.sensor_id);
                printf("after size: %d \n", size_send_queue());
                //uart_recv(fd, (char*)msg, datalen)
            }
        }
    }
    close(s_fd);
    return NULL;
}*/

// char * get_sensor_data(int fd) {

//     int serial_id = 0;
//     int dev_id = 0;
//     int sensor_id = 0;
//     printf("get_sensor_data\n");
   
//     for(serial_id = 0; serial_id < case_controller->serial_num; serial_id++) {
//         for(dev_id = 0; dev_id < (case_controller->serial_control + serial_id)->dev_num; dev_id++) {
//             for(sensor_id = 0; sensor_id < ((case_controller->serial_control + serial_id)->dev_control+dev_id)->sensor_num ; sensor_id++) {
//                 int datalen = strlen(((((case_controller->serial_control + serial_id)->dev_control+dev_id)->sensor_control+sensor_id)->gather_cmd));
//                 printf("sensor_name:%d,%s\n",datalen, ((((case_controller->serial_control + serial_id)->dev_control+dev_id)->sensor_control+sensor_id)->gather_cmd));
//                 serial_ms_msg_t *msg = (serial_ms_msg_t *)malloc(sizeof(serial_ms_msg_t)+datalen);
//                 serial_ms_msg_t msg1;
//                 msg->start = 0x55;
//                 msg->type = 0x10;
//                 msg->length = datalen;
//                 memcpy(msg->data, ((((case_controller->serial_control + serial_id)->dev_control+dev_id)->sensor_control+sensor_id)->gather_cmd), msg->length);
//                 //msg->end = 0x60;
//                 //msg.crc32 = CRC32_Table(msg.data, strlen((char *)msg.data), msg.crc32);
//                 //get_sys_cur_time(msg.timestamp);
//                 printf("struct size:%d\n",sizeof(serial_ms_msg_t)+datalen);
//                 int s_fd = serial_init();
//                 //uart_send(s_fd, (uint8_t*)msg, sizeof(serial_ms_msg_t)+datalen);
//                 uart_send(s_fd, "12", 2);
//                 close(s_fd);
//                 //del_send_queue(&msg1);
//                 //printf("%d,%d,%d,%d\n", msg1.header.length, msg1.header.serial_id, msg1.header.dev_id, msg1.header.sensor_id);
//                 printf("after size: %d \n", size_send_queue());
//                 //uart_recv(fd, (char*)msg, datalen)
//             }
//         }
//     }
   
//     return NULL;
// }




// static int do_serial_task()
// {

//     int serial_num = get_sys_serial_num();
//     int serial_id = 0;
//     int status = -1;
//     char buff[MAXLINE];   
//     int addrlen;
//     int client_sockfd;  
//     struct sockaddr_in server_addr;  /*服务器地址结构*/  
//     pthread_t read_id, write_id;
 
//     if((client_sockfd=socket(PF_INET,SOCK_STREAM,0)) < 0) {  
//         perror("socket");  
//         return -1;  
//     }  
//     /*设置服务端地址*/  
//     addrlen = sizeof(struct sockaddr_in);  
//     memset(&server_addr, 0, addrlen);  
//     server_addr.sin_family = AF_INET;    /*AF_INET表示 IPv4 Intern 协议*/  
//     server_addr.sin_addr.s_addr = inet_addr("120.77.46.12");
//     //server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//     server_addr.sin_port = htons(8000); /*设置端口*/  
      
//     /*绑定地址结构到套接字描述符*/  
//     if(connect(client_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) { 
//         printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);  
//         exit(0);  
//     }  
//     if(pthread_create(&read_id,NULL,read_func,&client_sockfd)) {
//         printf("pthread_create read_func err\n");
//     }  
//     if(pthread_create(&write_id,NULL,write_func,&client_sockfd)) {  
//         printf("pthread_create write_func err\n");
//     }
//     //signal(SIGINT,stop); /*注册SIGINT 信号*/
//     while(1){
//         //printf("do_serial_task:pid = %d, parent pid = %d\n", getpid(), getppid());
//         sleep(5);
//     }

//     return 0;
// }


int create_child_pthread()
{
    pthread_t serial_id, usb_id, wifi_id, net_id;
    if(pthread_create(&serial_id, NULL, do_serial_task, NULL)) {
        printf("pthread_create read_func err\n");
    }
    if(pthread_create(&usb_id, NULL, do_usb_task, NULL)) {
        printf("pthread_create read_func err\n");
    } 
    if(pthread_create(&wifi_id, NULL, do_wifi_task, NULL)) {
        printf("pthread_create read_func err\n");
    }
    if(pthread_create(&net_id, NULL, data_forward_deal, NULL)) {
        printf("pthread_create read_func err\n");
    } 
    while(1) {
        sleep(5);
    }
    return 0;
}


// int i;
//   int status = -1;
//   for(i = 0; i < 5 ; i++) {
//       status= fork();
//       if(status == 0 || status == -1) {
//           break;
//       }
//   }
//   if(status == -1) {
//       printf("the process fork fail \n");
//   } else if(status == 0) {
//         if(i == 1) {
//             //printf("the i = 1\n");
//             do_serial_task();
//         }
//         if(i == 2) {
//             //printf("the i = 2\n");
//             do_wifi_task();
//         }
//         if(i == 3) {
//             do_usb_task();
//             //printf("the i = 3\n");
//         }
//   } else {
//       while(1) {
//         //printf("the parent,%d\n",getpid());
//         sleep(3);
//     }
     
//   }

int core_init() 
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
    printf("%s\n", json_file);
    cJSON *object=cJSON_Parse(json_file);
    if (!object) {
        printf("test Error before: [%s]\n",cJSON_GetErrorPtr());
        return -1;
    }
    printf("the main parent,%d\n",getpid());
   
    return 0;
}

int main()
{
    core_init();
    create_child_pthread();
    return 0;
}

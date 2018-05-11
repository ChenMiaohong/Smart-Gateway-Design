#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "zlog.h"
#include "smart_getway_log.h"
#include "smart_getway_parse.h"
#include "smart_getway_init.h"

case_controller_t* case_controller = NULL;

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
    return 0;
}
void sensor_deal(void* param)
{
    alloc_msg_t 
    send_to_serial



}
static finish_dev_pthread_task()
{
    int status = -1;
    pthread_t  ntid;
    npip = pthread_create(&ntid, NULL, sensor_deal, NULL);
    return 0;
}
static int do_dev_task(serial_id)
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
static int do_serial_task()
{
    int serial_num = get_sys_serial_num();
    int serial_id = 0;
    int status = -1;
   for(serial_id = 0; serial_id < serial_num; serial_id++) {
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
      printf("the parent\n");
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
    create_child_process();
    while(1) {
        sleep(100);
    }
    return 0;
}

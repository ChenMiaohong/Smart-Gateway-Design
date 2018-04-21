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
/*
test_module_list:
name:pubsub_msg_id
name:cbk_msg_id
name:manurcv_msg_id
*/

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
    
    return 0;
}

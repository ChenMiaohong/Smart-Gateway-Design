#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "zlog.h"
#include "smart_getway_log.h"

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

    int arch_type = get_sys_arch();
    printf("the sys arch = %d \n",arch_type);
   
    printf("the wifi_num = %d\n",get_sys_wifi_num());
    printf("the network_protocol%d\n",get_sys_network_protocol());
    printf("the usb_sensor_num = %d\n",get_sys_usb_sensor_num());
    return 0;
}

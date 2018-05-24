#ifndef SMART_GETWAY_FORWARD_H
#define SMART_GETWAY_FORWARD_H
#include "smart_getway_init.h"



#ifdef __cplusplus
extern "C"
{
#endif
    int add_send_queue(server_control_cmd_t server_control_data);
      
    int size_send_queue();

    int del_send_queue(server_control_cmd_t* server_control_data);
    
#ifdef __cplusplus
}

#endif
#endif

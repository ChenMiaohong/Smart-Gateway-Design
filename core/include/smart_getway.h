#ifndef __SMART_GETWAY_H
#define __SMART_GETWAY_H
#include "smart_getway_init.h"
// #ifdef __cplusplus
// extern "C" {
// #endif

// //#define LOG_INIT  dcos_test_init_log()
// /*typedef struct msg_head {
//     uin8_t length;
//     uin8_t serial_id;
//     uint8_t dev_id;
//     uint8_t sensor_id;
//     uint8_t resp;
//     uint8_t addr;
// } msg_head_t;
// typedef struct serial_ms_msg {
//     uint16_t start;
//     msg_head_t header;
//     uin8_t data[0];
//     uint64_t timestamp;
//     uint32_t crc32;
// } serial_ms_msg_t;
// */


// extern void* data_forward_deal(void* param);
// extern void* do_usb_task(void* param);
// #define MAXLINE 1024

// #ifdef __cplusplus
// }
// #endif

extern void* data_forward_deal(void* param);
extern void* do_usb_task(void* param);
#endif

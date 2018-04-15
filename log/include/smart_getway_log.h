#ifndef __LOG_H
#define __LOG_H
#include "zlog.h"

#define DCOS_PRETEST_LOG_CONFIG "/etc/smart_getway/smart_getway_log.conf"
#define CAT zlog_get_category("my_cat")

int Init_LogDir();

zlog_category_t * smart_getway_init_log();

#endif

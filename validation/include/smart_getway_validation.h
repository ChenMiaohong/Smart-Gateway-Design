#ifndef __CRC32CHECK_H
#define __CRC32CHECK_H
#include <stdint.h>

uint32_t CRC32_Table(const uint8_t* pdata, int len, uint32_t crc);
#endif

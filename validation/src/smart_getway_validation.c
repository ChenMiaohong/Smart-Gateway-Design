#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "smart_getway_validation.h"
uint32_t gsTable[256];
void CRC32_TableInit()
{
    uint32_t i;
    int bits;
    for( i= 0; i < 256; i++) {
        uint32_t crc = i << 24;

        for (bits= 0; bits < 8; bits++) {
            if (crc & 0x80000000) {
                crc = (crc << 1) ^(0xEDB88320);
            }
            else {
                crc <<= 1;
            }
        }

        gsTable[i] = crc;
    }
}

uint32_t CRC32_Table(const uint8_t* pdata, int len, uint32_t crc)
{
    uint8_t index;
    int i;
    CRC32_TableInit();
    for (i = 0; i < len; i++, pdata++) {
        index = *pdata ^ (crc >> 24);
        crc = (crc << 8) ^ gsTable[index];
    }
    return crc;
}

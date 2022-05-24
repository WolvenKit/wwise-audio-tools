#ifndef WW2OGG_CRC_H
#define WW2OGG_CRC_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

uint32_t checksum(unsigned char *data, int bytes);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // WW2OGG_CRC_H

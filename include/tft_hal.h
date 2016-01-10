#ifndef TFT_HAL_H
#define TFT_HAL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void TFT_HAL_DP(uint16_t data);
void TFT_HAL_WR(unsigned char data);
void TFT_HAL_RD(unsigned char data);
void TFT_HAL_CS(unsigned char data);
void TFT_HAL_RS(unsigned char data);
void TFT_HAL_RST(unsigned char data);
void TFT_HAL_init(void);

#ifdef __cplusplus
}
#endif

#endif

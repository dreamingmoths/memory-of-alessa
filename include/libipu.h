#ifndef SCE_LIBIPU_H
#define SCE_LIBIPU_H

#include "common.h"

#define SCE_IPU_BCLR 0x00000000
#define sceIpuIsBusy() ((int)((int)DGET_IPU_CTRL() < 0))
#define sceIpuBCLR(bp) DPUT_IPU_CMD(SCE_IPU_BCLR | (bp))

typedef struct
{
    u_int d4madr;
    u_int d4tadr;
    u_int d4qwc;
    u_int d4chcr;
    u_int d3madr;
    u_int d3qwc;
    u_int d3chcr;
    u_int ipubp;
    u_int ipuctrl;
} sceIpuDmaEnv;

typedef struct {
	u_char y[256];
	u_char cb[64];
	u_char cr[64];
} sceIpuRAW8;

#endif // SCE_LIBIPU_H

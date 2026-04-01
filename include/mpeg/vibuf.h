// https://github.com/Mikompilation/Himuro/blob/828c49053f0d0a67694ae678463dfa3b770b6ef3/include/sce/mpeg/vibuf.h

#ifndef SCE_MPEG_VIBUF_H
#define SCE_MPEG_VIBUF_H

#include "common.h"
#include "libipu.h"

#define DMA_ID_REFE 0
#define DMA_ID_NEXT 2
#define DMA_ID_REF 3

#define VIBUF_ELM_SIZE 2048
#define VIBUF_SIZE 256
#define VIBUF_TS_SIZE (VIBUF_SIZE * 2)

#define TAG_ADDR(i) ((u_int)DmaAddr(f->tag + i))
#define DATA_ADDR(i) ((u_int)f->data + VIBUF_ELM_SIZE * (i))
#define WRAP_ADDR(addr) ((u_int)(f->data) + (((u_int)(addr) - (u_int)(f->data)) % (VIBUF_ELM_SIZE * f->n)))
#define IsInRegion(i, start, len, n) ((0 <= (((i) + (n) - (start)) % (n))) && ((((i) + (n) - (start)) % (n)) < (len)))

extern inline int IsPtsInRegion(int tgt, int pos, int len, int size)
{
    int tgt1 = (tgt + size - pos) % size;
    return tgt1 < len;
}

typedef struct
{ // 0x18
    /* 0x00 */ long int pts;
    /* 0x08 */ long int dts;
    /* 0x10 */ int pos;
    /* 0x14 */ int len;
} TimeStamp;

typedef struct
{ // 0x60
    /* 0x00 */ u_long128 *data;
    /* 0x04 */ u_long128 *tag;
    /* 0x08 */ int n;
    /* 0x0c */ int dmaStart;
    /* 0x10 */ int dmaN;
    /* 0x14 */ int readBytes;
    /* 0x18 */ int buffSize;
    /* 0x1c */ sceIpuDmaEnv env;
    /* 0x40 */ int sema;
    /* 0x44 */ int isActive;
    /* 0x48 */ long int totalBytes;
    /* 0x50 */ TimeStamp *ts;
    /* 0x54 */ int n_ts;
    /* 0x58 */ int count_ts;
    /* 0x5c */ int wt_ts;
} ViBuf;

#endif // SCE_MPEG_VIBUF_H

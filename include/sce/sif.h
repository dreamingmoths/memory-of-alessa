#ifndef SCE_SIF_H
#define SCE_SIF_H

typedef struct
{
    u_int data;
    u_int addr;
    u_int size;
    u_int mode;
} sceSifDmaData;

extern u_int sceSifSetDma(sceSifDmaData* sdd, int len);
extern u_int isceSifSetDma(sceSifDmaData* sdd, int len);
extern int sceSifDmaStat(u_int id);
extern int isceSifDmaStat(u_int id);

#define ExitHandler() __asm__ volatile("sync.l; ei")

#define WRITEBACK_DCACHE 0
#define INVALIDATE_DCACHE 1
#define INVALIDATE_ICACHE 2
#define INVALIDATE_CACHE 3

#endif
#ifndef SCE_SIF_H
#define SCE_SIF_H

typedef struct
{
    unsigned int data;
    unsigned int addr;
    unsigned int size;
    unsigned int mode;
} sceSifDmaData;

extern unsigned int sceSifSetDma(sceSifDmaData *sdd, int len);
extern unsigned int isceSifSetDma(sceSifDmaData *sdd, int len);
extern int sceSifDmaStat(unsigned int id);
extern int isceSifDmaStat(unsigned int id);

#define ExitHandler() __asm__ volatile("sync.l; ei")

#define WRITEBACK_DCACHE 0
#define INVALIDATE_DCACHE 1
#define INVALIDATE_ICACHE 2
#define INVALIDATE_CACHE 3

#endif
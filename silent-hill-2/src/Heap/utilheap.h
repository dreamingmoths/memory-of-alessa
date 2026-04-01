#ifndef UTILHEAP_H
#define UTILHEAP_H

#include "sh2_common.h"

#define CEIL16(x) (((x + 0xF) / 0x10) * 0x10)
#define FLOOR16(x) (x & ~0xF)

typedef struct utilHeapCtrl
{
    // total size: 0x10
    int size;   // offset 0x0, size 0x4
    int free;   // offset 0x4, size 0x4
    void *head; // offset 0x8, size 0x4
    void *tail; // offset 0xC, size 0x4
} utilHeapCtrl;

typedef struct utilHeapMBlock
{
    // total size: 0x10
    u_int size;     // offset 0x0, size 0x4
    void *heapctrl; // offset 0x4, size 0x4
    void *next;     // offset 0x8, size 0x4
    void *prev;     // offset 0xC, size 0x4
} utilHeapMBlock;

utilHeapCtrl *utilHeapInit(void *buf, u_int bytesize);
void *utilHeapMalloc(utilHeapCtrl *heapctrl, u_int n);
void utilHeapFree(void *obj);

#endif

#ifndef LOADBG_CLD_H
#define LOADBG_CLD_H

#include "sh2_common.h"

#define LBM_CLD_SLOTS 16

typedef struct loadBgCLD_Ctrl {
    // total size: 0x104
    int mapid[16];  // offset 0x0, size 0x40
    void* addr[16]; // offset 0x40, size 0x40
    int size[16];   // offset 0x80, size 0x40
    void* list[17]; // offset 0xC0, size 0x44
} loadBgCLD_Ctrl;

int loadBgCLD_Replace(int slot, int mapid, void* addr, int size);
void** loadBgCLD_GetLoadedDataAddrList();

#endif

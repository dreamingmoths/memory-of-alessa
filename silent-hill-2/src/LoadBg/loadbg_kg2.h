#ifndef LOADBG_KG2_H
#define LOADBG_KG2_H

#include "sh2_common.h"

#define LBM_KG2_SLOTS 4

// total size: 0x44
typedef struct loadBgKG2_Ctrl {
    // Members
    int mapid[4]; // offset 0x0, size 0x10
    void* addr[4]; // offset 0x10, size 0x10
    int size[4]; // offset 0x20, size 0x10
    void* list[5]; // offset 0x30, size 0x14
} loadBgKG2_Ctrl;

int loadBgKG2_Replace(int slot, int mapid, void* addr, int size);
void** loadBgKG2_GetLoadedDataAddrList(void);

#endif // LOADBG_KG2_H

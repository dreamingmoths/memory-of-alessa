#ifndef LOADBG_CAM_H
#define LOADBG_CAM_H

#include "sh2_common.h"

#define LBM_CAM_SLOTS 17

// total size: 0x114
typedef struct loadBgCAM_Ctrl {
    // Members
    int mapid[17]; // offset 0x0, size 0x44
    void* addr[17]; // offset 0x44, size 0x44
    int size[17]; // offset 0x88, size 0x44
    void* list[18]; // offset 0xCC, size 0x48
} loadBgCAM_Ctrl;

int loadBgCAM_ReplaceG(int mapid, void* addr, int size);
int loadBgCAM_Replace(int slot, int mapid, void* addr, int size);
void** loadBgCAM_GetLoadedDataAddrList(void);
void loadBgCAM_vcReset(void);

#endif // LOADBG_CAM_H

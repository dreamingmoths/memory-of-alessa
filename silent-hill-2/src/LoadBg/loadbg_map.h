#ifndef LOADBG_MAP_H
#define LOADBG_MAP_H

#include "sh2_common.h"

// not 100% sure about these numbers
#define LBM_TEX_SLOTS 2
#define LBM_MAP_SLOTS 5

// total size: 0x54
typedef struct loadBgTEX_Ctrl {
    // Members
    int mapid[7]; // offset 0x0, size 0x1C
    void* addr[7]; // offset 0x1C, size 0x1C
    int size[7]; // offset 0x38, size 0x1C
} loadBgTEX_Ctrl;

int loadBgTEX_Replace(int slot, int mapid, void* addr, int size);
int loadBgMAP_Replace(int slot, int mapid, void* addr, int size);
void loadBgMAP_AllClear(void);

#endif // LOADBG_MAP_H

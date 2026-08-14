#ifndef LOADBG_COMMON_H
#define LOADBG_COMMON_H

#include "sh2_common.h"
#include "data/fs_structs.h"

// total size: 0xBC
typedef struct _loadBgCommon_Info_T {
    // Members
    int glb_crd; // offset 0x0, size 0x4
    float px; // offset 0x4, size 0x4
    float pz; // offset 0x8, size 0x4
    float fcx; // offset 0xC, size 0x4
    float fcz; // offset 0x10, size 0x4
    int icx; // offset 0x14, size 0x4
    int icz; // offset 0x18, size 0x4
    int minx; // offset 0x1C, size 0x4
    int minz; // offset 0x20, size 0x4
    int outdoor; // offset 0x24, size 0x4
    int RoomID; // offset 0x28, size 0x4
    int BlockID[4]; // offset 0x2C, size 0x10
    int AroundID[5][5]; // offset 0x3C, size 0x64
    int unit; // offset 0xA0, size 0x4
    int load; // offset 0xA4, size 0x4
    int need; // offset 0xA8, size 0x4
    int lock; // offset 0xAC, size 0x4
    int miss; // offset 0xB0, size 0x4
    int hide_map; // offset 0xB4, size 0x4
    int hide_map_request; // offset 0xB8, size 0x4
} loadBgCommon_Info_T;

extern loadBgCommon_Info_T _loadBgCommon_Info[1]; // size: 0xBC, address: 0x36D750

int _loadBgCommon_LoadData(void* loadbuf, fsFileIndex* file, int limit);
int BPOSfromFPOS(float f);
float FPOSfromBPOS(int i);
int loadBgCommon_SetInfo(int glb_crd, float px, float pz);
int loadBgCommon_HideMapBlockOutdoor(int mapid);

#endif // LOADBG_COMMON_H

#ifndef LOADBG_2X2_H
#define LOADBG_2X2_H

#include "sh2_common.h"
#include "LoadBg/loadbg_mem.h"

#define LBM2x2_SECTIONS_O   8
#define LBM2x2_SECTFILES_O  4
#define LBM2x2_SECTIONS_I   2
#define LBM2x2_SECTFILES_I  20

// total size: 0x5AC
typedef struct _loadBg2x2_Ctrl {
    // Members
    loadBgMem_LoadCtrl* load; // offset 0x0, size 0x4
    loadBgMem_CacheCtrl* cache; // offset 0x4, size 0x4
    loadBgMem_Sect SectI[2]; // offset 0x8, size 0x28
    loadBgMem_Sect SectO[8]; // offset 0x30, size 0xA0
    loadBgMem_File FileI[2][20]; // offset 0xD0, size 0x280
    loadBgMem_File FileO[8][4]; // offset 0x350, size 0x200
    loadBgMem_Sect* SectList[8]; // offset 0x550, size 0x20
    int Sections; // offset 0x570, size 0x4
    int cache_in_access_count[1]; // offset 0x574, size 0x4
    int cache_out_access_count[1]; // offset 0x578, size 0x4
    int file_access_count[1]; // offset 0x57C, size 0x4
    int miss_access_count[1]; // offset 0x580, size 0x4
    int load_cleanup; // offset 0x584, size 0x4
    int cache_cleanup; // offset 0x588, size 0x4
    int slot_cleanup[8]; // offset 0x58C, size 0x20
} loadBg2x2_Ctrl;

void loadBg2x2_CheckCacheWork(void);
void loadBg2x2_CheckLoadWork(void);
void loadBg2x2_ClearRequest(void);
void loadBg2x2_SetRequest(void);
void loadBg2x2_CleanupNonRequest(void);
int loadBg2x2_GetOutdoorBlockSection(int bx, int bz);
int loadBg2x2_GetOutdoorBlockPhase(int bx, int bz);
int loadBg2x2_CheckLoadBufferOutdoor(int bx, int bz);
int loadBg2x2_SetRequestOutdoor(int prio, int reduceRate8, int bx, int bz, int mid);
int loadBg2x2_GetIndoorRoomSection(int roomid);
int loadBg2x2_CheckLoadBufferIndoor(int roomid);
int loadBg2x2_SetRequestIndoor(int roomid, int* mid4);
int loadBg2x2_CheckRequest(int* reqUnits);
int loadBg2x2_LoadRequest(void);
int loadBg2x2_ActivateRequestOutdoor(int slot, int mid, int* reqUnits);
int loadBg2x2_ActivateRequestIndoor(int* mid4, int* reqUnits);
int loadBg2x2_GetSlotOutdoor(int bx, int bz);
int loadBg2x2_GetFreeSlotIndoor(int roomid);
int loadBg2x2_GetUseSlotIndoor(int roomid);

#endif // LOADBG_2X2_H

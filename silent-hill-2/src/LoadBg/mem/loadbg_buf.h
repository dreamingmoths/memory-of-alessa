#ifndef LOADBG_BUF_H
#define LOADBG_BUF_H

#include "sh2_common.h"
#include "LoadBg/loadbg_mem.h"

extern loadBgMem_CacheCtrl loadBg4x4_CacheCtrl[1]; // size: 0x18, address: 0x0
extern loadBgMem_LoadCtrl loadBg4x4_LoadCtrl[1]; // size: 0x18, address: 0x0
extern loadBgMem_UnitC loadBg4x4_CacheUnit[76]; // size: 0x4C0, address: 0x0
extern loadBgMem_UnitR loadBg4x4_RequestUnit[304]; // size: 0x1300, address: 0x0
extern loadBgMem_UnitL loadBg4x4_LoadUnit[304]; // size: 0x1300, address: 0x0
extern loadBgMem_CacheCtrl loadBg2x2_CacheCtrl[1]; // size: 0x18, address: 0x122A330
extern loadBgMem_LoadCtrl loadBg2x2_LoadCtrl[1]; // size: 0x18, address: 0x122A350
extern loadBgMem_UnitC loadBg2x2_CacheUnit[8]; // size: 0x80, address: 0x122A370
extern loadBgMem_UnitR loadBg2x2_RequestUnit[120]; // size: 0x780, address: 0x122A3F0
extern loadBgMem_UnitL loadBg2x2_LoadUnit[120]; // size: 0x780, address: 0x122AB70
extern loadBgMem_CacheCtrl loadBg1x1_CacheCtrl[1]; // size: 0x18, address: 0x0
extern loadBgMem_LoadCtrl loadBg1x1_LoadCtrl[1]; // size: 0x18, address: 0x0
extern loadBgMem_UnitC loadBg1x1_CacheUnit[128]; // size: 0x800, address: 0x0
extern loadBgMem_UnitR loadBg1x1_RequestUnit[256]; // size: 0x1000, address: 0x0
extern loadBgMem_UnitL loadBg1x1_LoadUnit[256]; // size: 0x1000, address: 0x0

#endif // LOADBG_BUF_H

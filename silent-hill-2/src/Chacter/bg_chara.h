#ifndef BG_CHARA_H
#define BG_CHARA_H

#include "sh2_common.h"
#include "Chacter/character.h"
#include "data/fs_structs.h"

typedef struct _BgCharaManData {
    // total size: 0x24
    int now[2]; // offset 0x0, size 0x8
    void* nowp[2]; // offset 0x8, size 0x8
    int pre[2]; // offset 0x10, size 0x8
    void* prep[2]; // offset 0x18, size 0x8
    int cnt; // offset 0x20, size 0x4
} BgCharaManData;

int BgCharaGetBlockSize(fsFileIndex* id);
void BgCharaRelocateSet(int glb_crd, float x, float z, int chara_id);
int BgCharaIsId(int chara_id);
void* BgCharaIsLoad(int chara_id);
void BgCharaManInit(void);
void BgCharaMan(int cnt);
void BgCharaDelSlot(int slot);
int BgCharaGetSlotId(int slot);

#endif // BG_CHARA_H

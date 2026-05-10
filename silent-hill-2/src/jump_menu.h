// E:\work\sh2(CVS全取得)\src\jump_menu.c
#ifndef JUMP_MENU_H
#define JUMP_MENU_H

#include "common.h"

typedef struct /* @anon7 */ {
    // total size: 0x14
    signed int x; // offset 0x0, size 0x4
    signed int z; // offset 0x4, size 0x4
    signed int flg; // offset 0x8, size 0x4
    signed int trg; // offset 0xC, size 0x4
    signed int glb_crd; // offset 0x10, size 0x4
} JumpMenuUserData;

void JumpMenuPosNormal(void);

void CheckModeJumpDataSet(void);

#endif

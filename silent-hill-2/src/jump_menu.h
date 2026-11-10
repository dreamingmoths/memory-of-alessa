#ifndef JUMP_MENU_H
#define JUMP_MENU_H

#include "sh2_common.h"

typedef struct /* anonymous in the dwarf info */ {
    // total size: 0x14
    int x;       // offset 0x0, size 0x4
    int z;       // offset 0x4, size 0x4
    int flg;     // offset 0x8, size 0x4
    int trg;     // offset 0xC, size 0x4
    int glb_crd; // offset 0x10, size 0x4
} JumpMenuUserData;

// total size: 0x94
typedef struct JumpMenu_List {
    // Members
    s_char string[128]; // offset 0x0, size 0x80
    float pos_x; // offset 0x80, size 0x4
    float pos_y; // offset 0x84, size 0x4
    float pos_z; // offset 0x88, size 0x4
    float rot; // offset 0x8C, size 0x4
    int stg; // offset 0x90, size 0x4
} JumpMenu_List;

void JumpMenuPosNormal(void);
void CheckModeJumpDataSet(void);

extern int jump_menu_select;

#endif // JUMP_MENU_H

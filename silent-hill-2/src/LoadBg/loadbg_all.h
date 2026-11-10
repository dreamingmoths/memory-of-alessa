#ifndef LOADBG_ALL_H
#define LOADBG_ALL_H

#include "sh2_common.h"

// total size: 0x14
typedef struct loadBgAll_2x2Block {
    // Members
    int mid; // offset 0x0, size 0x4
    int bx; // offset 0x4, size 0x4
    int bz; // offset 0x8, size 0x4
    int slot; // offset 0xC, size 0x4
    float dist2; // offset 0x10, size 0x4
} loadBgAll_2x2Block;

// total size: 0xC0
typedef struct loadBgAll_2x2Info {
    // Members
    loadBgAll_2x2Block block[8]; // offset 0x0, size 0xA0
    loadBgAll_2x2Block* sort[8]; // offset 0xA0, size 0x20
} loadBgAll_2x2Info;

void loadBgAll_Init(void);
int loadBgAll_PrepareAround(int* loading, int* require);

#endif // LOADBG_ALL_H

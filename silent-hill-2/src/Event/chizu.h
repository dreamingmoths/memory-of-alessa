#ifndef CHIZU_H
#define CHIZU_H

#include "sh2_common.h"

// total size: 0xC
typedef struct Chizu_CurrentBlock {    
    int chizu; // offset 0x0, size 0x4
    float cp_x;       // offset 0x4, size 0x4
    float cp_y;       // offset 0x8, size 0x4
} Chizu_CurrentBlock;

// total size: 0x8
typedef struct Chizu_MarkerTex {
    // Members
    short u0; // offset 0x0, size 0x2
    short v0; // offset 0x2, size 0x2
    short u1; // offset 0x4, size 0x2
    short v1; // offset 0x6, size 0x2
} Chizu_MarkerTex;

// total size: 0x10
typedef struct Chizu_MarkerList {
    // Members
    Chizu_MarkerTex* tex; // offset 0x0, size 0x4
    int* data; // offset 0x4, size 0x4
    int head; // offset 0x8, size 0x4
    int tail; // offset 0xC, size 0x4
} Chizu_MarkerLists;

// total size: 0x4
typedef struct Chizu_ConnectInfo {
    // Members
    char up; // offset 0x0, size 0x1
    char down; // offset 0x1, size 0x1
    char right; // offset 0x2, size 0x1
    char left; // offset 0x3, size 0x1
} Chizu_ConnectInfo;

void ChizuMain(void);

#endif // CHIZU_H

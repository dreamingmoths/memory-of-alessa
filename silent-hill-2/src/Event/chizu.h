#ifndef CHIZU_H
#define CHIZU_H

typedef struct Chizu_CurrentBlock {
    // total size: 0xC
    signed int chizu; // offset 0x0, size 0x4
    float cp_x; // offset 0x4, size 0x4
    float cp_y; // offset 0x8, size 0x4
} Chizu_CurrentBlock;

#endif // CHIZU_H

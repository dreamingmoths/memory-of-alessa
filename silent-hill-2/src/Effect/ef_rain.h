#ifndef EF_RAIN_H
#define EF_RAIN_H

#include "common.h"
#include "taskman/shtskman.h"

// total size: 0x180
typedef struct _EF_RAINDROP_DATA {
    // Members
    int life; // offset 0x0, size 0x4
    int pad[2]; // offset 0x4, size 0x8
    float p[15][4]__attribute__((aligned(64))); // offset 0x40, size 0xF0
    float v[4][4]__attribute__((aligned(16))); // offset 0x130, size 0x40
} _EF_RAINDROP_DATA;

// total size: 0x30
typedef struct _EF_RAIN_LINE {
    // Members
    float v[2][4]__attribute__((aligned(16))); // offset 0x0, size 0x20
    u_char rgba[4]; // offset 0x20, size 0x4
} _EF_RAIN_LINE;

// total size: 0x240
typedef struct _EF_EF_RAINDROP_TASK {
    // Members
    _shTskEXECUTE exe; // offset 0x0, size 0x14
    _EF_RAINDROP_DATA data; // offset 0x40, size 0x180
    u_char freemem[108]; // offset 0x1C0, size 0x6C
} _EF_EF_RAINDROP_TASK;

int EFCTSetRainDrop(int lev /* r17 */);
void EFCTDelRainDrop(void);
void EFCTRainDropMain(_shTskTASK * ptr /* r18 */);
void efRainDropDrawLINE(_EF_RAIN_LINE* p);

#endif // EF_RAIN_H

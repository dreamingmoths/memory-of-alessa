#ifndef TITLE_H
#define TITLE_H

typedef struct _OPD_W {
    // total size: 0x34
    float u0;       // offset 0x0, size 0x4
    float u1;       // offset 0x4, size 0x4
    float v0;       // offset 0x8, size 0x4
    float v1;       // offset 0xC, size 0x4
    float x0;       // offset 0x10, size 0x4
    float y0;       // offset 0x14, size 0x4
    float x1;       // offset 0x18, size 0x4
    float y1;       // offset 0x1C, size 0x4
    float offset_x; // offset 0x20, size 0x4
    float offset_y; // offset 0x24, size 0x4
    float scale_x;  // offset 0x28, size 0x4
    float scale_y;  // offset 0x2C, size 0x4
    u_char rgb;     // offset 0x30, size 0x1
    u_char step;    // offset 0x31, size 0x1
    u_char timer;   // offset 0x32, size 0x1
} OPD_W;

typedef struct /* @anon7 */ {
    // total size: 0x20
    short u0;           // offset 0x0, size 0x2
    short v0;           // offset 0x2, size 0x2
    short u1;           // offset 0x4, size 0x2
    short v1;           // offset 0x6, size 0x2
    short w;            // offset 0x8, size 0x2
    short h;            // offset 0xA, size 0x2
    sceVu0IVECTOR rgba; // offset 0x10, size 0x10
} TitleSprWork;

typedef struct /* @anon0 */ {
    // total size: 0x30
    sceVu0IVECTOR start_rgba; // offset 0x0, size 0x10
    sceVu0IVECTOR end_rgba;   // offset 0x10, size 0x10
    float cycle;              // offset 0x20, size 0x4
    float timer;              // offset 0x24, size 0x4
} TitleSprChgColorWork;
STATIC_ASSERT_SIZEOF(TitleSprChgColorWork, 0x30);

int TitleMain(void);

void titleSetDataStartPoint(void);

int GameendMain(void);

int GameoverMain(void);

#endif // TITLE_H

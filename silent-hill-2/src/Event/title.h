#ifndef TITLE_H
#define TITLE_H

#include "Event/picture.h"
#include "sce/libvu0.h"

#define SH2_TITLE_DATA_MODE_0 0
#define SH2_TITLE_DATA_MODE_1 1
#define SH2_TITLE_DATA_MODE_2 2
#define SH2_TITLE_DATA_MODE_3 3
#define SH2_TITLE_DATA_MODE_4 4
#define SH2_TITLE_DATA_MODE_5 5
#define SH2_TITLE_DATA_MODE_6 6

/**
 * The default title test mode.
 */
#define TITLE_TEST_MODE_NONE   0

/**
 * Contains the default menu options and also allows the user to jump to
 * apartment, hospital, prison, or hotel.
 */
#define TITLE_TEST_MODE_JP     1

/**
 * Only allows one to select new game, apartment, or prison.
 */
#define TITLE_TEST_MODE_US     2

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

typedef struct /* @anon3 */ {
    // total size: 0x18
    float pos_x;      // offset 0x0, size 0x4
    float pos_y;      // offset 0x4, size 0x4
    float pos_z;      // offset 0x8, size 0x4
    float rot;        // offset 0xC, size 0x4
    int stg;          // offset 0x10, size 0x4
    int jump_nemu_id; // offset 0x14, size 0x4
} TitlePointList;

typedef struct /* @anon6 */ {
    // total size: 0x94
    int memcard;              // offset 0x0, size 0x4
    int mode;                 // offset 0x4, size 0x4
    int sel;                  // offset 0x8, size 0x4
    float timer;              // offset 0xC, size 0x4
    int alpha;                // offset 0x10, size 0x4
    float alphar;             // offset 0x14, size 0x4
    u_int menu[10];           // offset 0x18, size 0x28
    struct PicDraw_Data pic0; // offset 0x40, size 0x44
    u_char* pload0;           // offset 0x84, size 0x4
    u_char* pload1;           // offset 0x88, size 0x4
    int texadr;               // offset 0x8C, size 0x4
    int clutadr;              // offset 0x90, size 0x4
} TitleDataWork;

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

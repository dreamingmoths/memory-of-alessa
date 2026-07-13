#ifndef FONT_SHARED_H
#define FONT_SHARED_H

#include "sce/eetypes.h"
#include "shared/Font/font.h"

#define MES_V_COUNT 10

// @todo: unsure what this is?
#define FONT_CLUT(x) (((2 * x + 3) << 28) | 0x0FA0A0A0)

typedef struct WFONT_STREAM_DATA {
    // total size: 0x18
    /* 0x00 */ u_short x;   // size 0x2
    /* 0x02 */ u_short y;   // size 0x2
    /* 0x04 */ u_short vw;  // size 0x2
    /* 0x06 */ u_short vh;  // size 0x2
    /* 0x08 */ u_short u;   // size 0x2
    /* 0x0A */ u_short v;   // size 0x2
    /* 0x0C */ u_int rgb_u; // size 0x4
    /* 0x10 */ u_int rgb_d; // size 0x4
    /* 0x14 */ u_short w;   // size 0x2
    /* 0x16 */ u_short h;   // size 0x2
} WFONT_STREAM_DATA;

typedef struct MFONT_STREAM_DATA {
    // total size: 0x8
    /* 0x0 */ u_short x; // size 0x2
    /* 0x2 */ u_short y; // size 0x2
    /* 0x4 */ u_short u; // size 0x2
    /* 0x6 */ u_short v; // size 0x2
} MFONT_STREAM_DATA;

typedef struct FONT_STREAM_DATA {
    u_short x;
    u_short y;
    u_short w;
    u_short h;
    u_short u;
    u_short v;
    u_int rgb_u;
    u_int rgb_d;
} FONT_STREAM_DATA;

#endif // FONT_SHARED_H

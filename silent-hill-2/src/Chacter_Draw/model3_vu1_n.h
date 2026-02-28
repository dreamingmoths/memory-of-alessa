#ifndef MODEL3_VU1_N_H
#define MODEL3_VU1_N_H

#include "common.h"
#include "libvifpk.h"
#include "libdma.h"
#include "model_common.h"
#include "GFW/sh2gfw_Init_ModelDrawData.h"

typedef struct Model3Junk
{
    // total size: 0x1C0
    float xyz_min[4];          // offset 0x0, size 0x10
    float xyz_max[4];          // offset 0x10, size 0x10
    float xyz_min_wide[4];     // offset 0x20, size 0x10
    float xyz_max_wide[4];     // offset 0x30, size 0x10
    float rgba_max[4];         // offset 0x40, size 0x10
    float global_ambient[4];   // offset 0x50, size 0x10
    __int128 giftag_0;         // offset 0x60, size 0x10
    __int128 giftag_1;         // offset 0x70, size 0x10
    __int128 giftag_2;         // offset 0x80, size 0x10
    float camera[4];           // offset 0x90, size 0x10
    float wvm[4][4];           // offset 0xA0, size 0x40
    float vsm[4][4];           // offset 0xE0, size 0x40
    float wsm[4][4];           // offset 0x120, size 0x40
    float vwm[4][4];           // offset 0x160, size 0x40
    void *vi00;                // offset 0x1A0, size 0x4
    void *xtop;                // offset 0x1A4, size 0x4
    float (*cluster_nodes)[4]; // offset 0x1A8, size 0x4
    u_int fogcol;              // offset 0x1AC, size 0x4
    u_char view_clip_and;      // offset 0x1B0, size 0x1
    u_char view_clip_or;       // offset 0x1B1, size 0x1
    u_char gs_clip_and;        // offset 0x1B2, size 0x1
    u_char gs_clip_or;         // offset 0x1B3, size 0x1
} Model3Junk;

typedef struct TextureParam {
    // total size: 0x10
    unsigned long clamp; // offset 0x0, size 0x4
    unsigned long tex1; // offset 0x8, size 0x4
} TextureParam;

typedef struct NDrawData {
    // total size: 0x80
    union Q giftag; // offset 0x0, size 0x10
    union Q waittag; // offset 0x10, size 0x10
    union Q envtag; // offset 0x20, size 0x10
    union Q tex0; // offset 0x30, size 0x10
    union Q tex1; // offset 0x40, size 0x10
    union Q clamp; // offset 0x50, size 0x10
    union Q alpha; // offset 0x60, size 0x10
    union Q fogcol; // offset 0x70, size 0x10
} NDrawData;

typedef struct SprData {
    // total size: 0x200
    struct NDrawData ndraw[2]; // offset 0x0, size 0x100
    struct NDrawData odraw[2]; // offset 0x100, size 0x100
} SprData;

typedef struct Data {
    // total size: 0x10
    union Q rgba; // offset 0x0, size 0x10
} Data;

extern int all_data;
extern SprData* spr_data;
extern u_int xitop_0x0041BF08;

#endif


#ifndef MODEL3_STRUCTS_H
#define MODEL3_STRUCTS_H

#include "sh2_common.h"
#include "sce/libvu0.h"

typedef struct Model3Junk {
    // total size: 0x1C0
    float xyz_min[4];          // offset 0x0, size 0x10
    float xyz_max[4];          // offset 0x10, size 0x10
    float xyz_min_wide[4];     // offset 0x20, size 0x10
    float xyz_max_wide[4];     // offset 0x30, size 0x10
    float rgba_max[4];         // offset 0x40, size 0x10
    float global_ambient[4];   // offset 0x50, size 0x10
    u_long128 giftag_0;        // offset 0x60, size 0x10
    u_long128 giftag_1;        // offset 0x70, size 0x10
    u_long128 giftag_2;        // offset 0x80, size 0x10
    float camera[4];           // offset 0x90, size 0x10
    float wvm[4][4];           // offset 0xA0, size 0x40
    float vsm[4][4];           // offset 0xE0, size 0x40
    float wsm[4][4];           // offset 0x120, size 0x40
    float vwm[4][4];           // offset 0x160, size 0x40
    void* vi00;                // offset 0x1A0, size 0x4
    void* xtop;                // offset 0x1A4, size 0x4
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
    unsigned long tex1;  // offset 0x8, size 0x4
} TextureParam;

typedef struct Init_Gs_Packet {
    // total size: 0x40
    u_long giftag_tag; // offset 0x0, size 0x4
    u_long giftag_reg; // offset 0x8, size 0x4
    u_long test_d; // offset 0x10, size 0x4
    u_long test_a; // offset 0x18, size 0x4
    u_long fba_d; // offset 0x20, size 0x4
    u_long fba_a; // offset 0x28, size 0x4
    u_long texflush_d; // offset 0x30, size 0x4
    u_long texflush_a; // offset 0x38, size 0x4
} Init_Gs_Packet;


typedef struct Packet {
    // total size: 0x30
    u_long giftag_tag; // offset 0x0, size 0x4
    u_long giftag_reg; // offset 0x8, size 0x4
    u_long TexFlush_D; // offset 0x10, size 0x4
    u_long TexFlush_A; // offset 0x18, size 0x4
    u_long Clamp_D; // offset 0x20, size 0x4
    u_long Clamp_A; // offset 0x28, size 0x4
} Packet;


typedef struct PLightData {
    // total size: 0x80
    sceVu0FMATRIX nlm; // offset 0x0, size 0x40
    sceVu0FMATRIX lcm; // offset 0x40, size 0x40
}  PLightData;

typedef struct ELightData {
    // total size: 0x40
    sceVu0FVECTOR pos; // offset 0x0, size 0x10
    sceVu0FVECTOR dir; // offset 0x10, size 0x10
    sceVu0FVECTOR col; // offset 0x20, size 0x10
    sceVu0FVECTOR param; // offset 0x30, size 0x10
} ELightData;

typedef struct EMapData {
    // total size: 0x60
    float vwm[4][4]; // offset 0x0, size 0x40
    float mag[4]; // offset 0x40, size 0x10
    float offset[4]; // offset 0x50, size 0x10
} EMapData;

typedef struct EDrawData {
    // total size: 0x80
    Q giftag; // offset 0x0, size 0x10
    Q waittag; // offset 0x10, size 0x10
    Q envtag; // offset 0x20, size 0x10
    Q tex0; // offset 0x30, size 0x10
    Q tex1; // offset 0x40, size 0x10
    Q clamp; // offset 0x50, size 0x10
    Q alpha; // offset 0x60, size 0x10
    Q fogcol; // offset 0x70, size 0x10
} EDrawData;

typedef struct SMapData {
    // total size: 0x40
    float nhm[4][4]; // offset 0x0, size 0x40
} SMapData;

typedef struct DSetupData {
    // total size: 0x80
    float vsp[2][4]; // offset 0x0, size 0x20
    float vcp[2][4]; // offset 0x20, size 0x20
    Q xyz_mul; // offset 0x40, size 0x10
    Q xyz_add; // offset 0x50, size 0x10
    Q rgba_max; // offset 0x60, size 0x10
    Q waittag; // offset 0x70, size 0x10
} DSetupData;

typedef struct NDrawData {
    // total size: 0x80
    Q giftag;  // offset 0x0, size 0x10
    Q waittag; // offset 0x10, size 0x10
    Q envtag;  // offset 0x20, size 0x10
    Q tex0;    // offset 0x30, size 0x10
    Q tex1;    // offset 0x40, size 0x10
    Q clamp;   // offset 0x50, size 0x10
    Q alpha;   // offset 0x60, size 0x10
    Q fogcol;  // offset 0x70, size 0x10
} NDrawData;

typedef struct SprData {
    // total size: 0x200
    struct NDrawData ndraw[2]; // offset 0x0, size 0x100
    struct NDrawData odraw[2]; // offset 0x100, size 0x100
} SprData;

typedef struct Data {
    // total size: 0x30
    sceVu0FVECTOR diffuse; // offset 0x0, size 0x10
    sceVu0FVECTOR ambient; // offset 0x10, size 0x10
    sceVu0FVECTOR param; // offset 0x20, size 0x10
} Data;


typedef struct LambertData {
    // total size: 0xA0
    sceVu0FMATRIX nlm; // offset 0x0, size 0x40
    sceVu0FMATRIX lcm; // offset 0x40, size 0x40
    sceVu0FVECTOR rgba_max; // offset 0x80, size 0x10
    sceVu0FVECTOR global_ambient; // offset 0x90, size 0x10
} LambertData;


typedef struct SDrawData {
    // total size: 0x90
    Q giftag; // offset 0x0, size 0x10
    Q waittag; // offset 0x10, size 0x10
    Q envtag; // offset 0x20, size 0x10
    Q tex0; // offset 0x30, size 0x10
    Q tex1; // offset 0x40, size 0x10
    Q clamp; // offset 0x50, size 0x10
    Q alpha; // offset 0x60, size 0x10
    Q fogcol; // offset 0x70, size 0x10
    Q reflection_color; // offset 0x80, size 0x10
} SDrawData;

typedef struct AllData {
    // total size: 0x800
    LambertData lambert; // offset 0x0, size 0xA0
    PLightData plight[4] __attribute__((aligned(64))); // offset 0xC0, size 0x200
    ELightData elight[8]; // offset 0x2C0, size 0x200
    EMapData emap __attribute__((aligned(64))); // offset 0x4C0, size 0x60
    SMapData smap __attribute__((aligned(64))); // offset 0x540, size 0x40
    DSetupData dsetup __attribute__((aligned(64))); // offset 0x580, size 0x80
    EDrawData edraw __attribute__((aligned(64))); // offset 0x600, size 0x80
    SDrawData sdraw __attribute__((aligned(64))); // offset 0x680, size 0x90
    SDrawData bdraw __attribute__((aligned(64))); // offset 0x740, size 0x90
} AllData;


#endif // MODEL3_STRUCTS_H

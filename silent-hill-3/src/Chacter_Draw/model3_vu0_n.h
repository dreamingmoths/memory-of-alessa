#ifndef MODEL3_VU0_N_H
#define MODEL3_VU0_N_H

#include "common.h"
#include "eestruct.h"
#include "eeregs.h"
#include "libgraph.h"
#include "model3_vu0_n.h"
#include "model_common.h"
#include "libdma.h"
#include "libdmapk.h"
#include "GFW/sh3gfw_Init_ModelDrawData.h"
#include "vifot/sh_kt_vif0.h"
#include "light_n.h"
#include "model3_sub_n.h"

#define GIF_REG(reg, n) ((u_long)(reg) << ((n) * 4))

#define DMArefe (0<<28)
#define DMAcnt  (1<<28)
#define DMAnext (2<<28)
#define DMAref  (3<<28)
#define DMArefs (4<<28)
#define DMAcall (5<<28)
#define DMAret  (6<<28)
#define DMAend  (7<<28)

typedef union Q
{
    __int128 u128;         // offset 0x0, size 0x10
    unsigned long u64[2];  // offset 0x0, size 0x8
    unsigned int u32[4];   // offset 0x0, size 0x10
    unsigned short u16[8]; // offset 0x0, size 0x10
    unsigned char u8[16];  // offset 0x0, size 0x10
    signed long s64[2];    // offset 0x0, size 0x8
    signed int s32[4];     // offset 0x0, size 0x10
    signed short s16[8];   // offset 0x0, size 0x10
    signed char s8[16];    // offset 0x0, size 0x10
    signed int q[4];       // offset 0x0, size 0x10
    float fv[4];           // offset 0x0, size 0x10
    signed int iv[4];      // offset 0x0, size 0x10
} Q;

typedef struct TriangleNormal
{
    // total size: 0xD0
    union Q dmatag;   // offset 0x0, size 0x10
    union Q n_giftag; // offset 0x10, size 0x10
    union Q n_tex0;   // offset 0x20, size 0x10
    union Q n_clamp;  // offset 0x30, size 0x10
    union Q n_stq2;   // offset 0x40, size 0x10
    union Q n_rgba2;  // offset 0x50, size 0x10
    union Q n_xyzf2;  // offset 0x60, size 0x10
    union Q n_stq1;   // offset 0x70, size 0x10
    union Q n_rgba1;  // offset 0x80, size 0x10
    union Q n_xyzf1;  // offset 0x90, size 0x10
    union Q n_stq0;   // offset 0xA0, size 0x10
    union Q n_rgba0;  // offset 0xB0, size 0x10
    union Q n_xyzf0;  // offset 0xC0, size 0x10
} TriangleNormal;

typedef struct TriangleNormalEnviron {
    // total size: 0x170
    union Q dmatag; // offset 0x0, size 0x10
    union Q n_giftag; // offset 0x10, size 0x10
    union Q n_tex0; // offset 0x20, size 0x10
    union Q n_clamp; // offset 0x30, size 0x10
    union Q n_stq2; // offset 0x40, size 0x10
    union Q n_rgba2; // offset 0x50, size 0x10
    union Q n_xyzf2; // offset 0x60, size 0x10
    union Q n_stq1; // offset 0x70, size 0x10
    union Q n_rgba1; // offset 0x80, size 0x10
    union Q n_xyzf1; // offset 0x90, size 0x10
    union Q n_stq0; // offset 0xA0, size 0x10
    union Q n_rgba0; // offset 0xB0, size 0x10
    union Q n_xyzf0; // offset 0xC0, size 0x10
    union Q e_giftag; // offset 0xD0, size 0x10
    union Q e_tex0; // offset 0xE0, size 0x10
    union Q e_clamp; // offset 0xF0, size 0x10
    union Q e_rgba; // offset 0x100, size 0x10
    union Q e_stq2; // offset 0x110, size 0x10
    union Q e_xyzf2; // offset 0x120, size 0x10
    union Q e_stq1; // offset 0x130, size 0x10
    union Q e_xyzf1; // offset 0x140, size 0x10
    union Q e_stq0; // offset 0x150, size 0x10
    union Q e_xyzf0; // offset 0x160, size 0x10
} TriangleNormalEnviron;

typedef struct TriangleNormalSpecular {
    // total size: 0x1B0
    union Q dmatag; // offset 0x0, size 0x10
    union Q n_giftag; // offset 0x10, size 0x10
    union Q n_tex0; // offset 0x20, size 0x10
    union Q n_clamp; // offset 0x30, size 0x10
    union Q n_stq2; // offset 0x40, size 0x10
    union Q n_rgba2; // offset 0x50, size 0x10
    union Q n_xyzf2; // offset 0x60, size 0x10
    union Q n_stq1; // offset 0x70, size 0x10
    union Q n_rgba1; // offset 0x80, size 0x10
    union Q n_xyzf1; // offset 0x90, size 0x10
    union Q n_stq0; // offset 0xA0, size 0x10
    union Q n_rgba0; // offset 0xB0, size 0x10
    union Q n_xyzf0; // offset 0xC0, size 0x10
    union Q s_giftag; // offset 0xD0, size 0x10
    union Q s_tex0; // offset 0xE0, size 0x10
    union Q s_clamp; // offset 0xF0, size 0x10
    union Q s_alpha; // offset 0x100, size 0x10
    union Q s_fogcol; // offset 0x110, size 0x10
    union Q s_rgba; // offset 0x120, size 0x10
    union Q s_stq2; // offset 0x130, size 0x10
    union Q s_xyzf2; // offset 0x140, size 0x10
    union Q s_stq1; // offset 0x150, size 0x10
    union Q s_xyzf1; // offset 0x160, size 0x10
    union Q s_stq0; // offset 0x170, size 0x10
    union Q s_xyzf0; // offset 0x180, size 0x10
    union Q S_alpha; // offset 0x190, size 0x10
    union Q S_fogcol; // offset 0x1A0, size 0x10
} TriangleNormalSpecular;

typedef struct TriangleSpecularNormal {
    // total size: 0x1B0
    union Q dmatag; // offset 0x0, size 0x10
    union Q s_giftag; // offset 0x10, size 0x10
    union Q s_tex0; // offset 0x20, size 0x10
    union Q s_clamp; // offset 0x30, size 0x10
    union Q s_alpha; // offset 0x40, size 0x10
    union Q s_fogcol; // offset 0x50, size 0x10
    union Q s_rgba; // offset 0x60, size 0x10
    union Q s_stq2; // offset 0x70, size 0x10
    union Q s_xyzf2; // offset 0x80, size 0x10
    union Q s_stq1; // offset 0x90, size 0x10
    union Q s_xyzf1; // offset 0xA0, size 0x10
    union Q s_stq0; // offset 0xB0, size 0x10
    union Q s_xyzf0; // offset 0xC0, size 0x10
    union Q S_alpha; // offset 0xD0, size 0x10
    union Q S_fogcol; // offset 0xE0, size 0x10
    union Q n_giftag; // offset 0xF0, size 0x10
    union Q n_tex0; // offset 0x100, size 0x10
    union Q n_clamp; // offset 0x110, size 0x10
    union Q n_stq2; // offset 0x120, size 0x10
    union Q n_rgba2; // offset 0x130, size 0x10
    union Q n_xyzf2; // offset 0x140, size 0x10
    union Q n_stq1; // offset 0x150, size 0x10
    union Q n_rgba1; // offset 0x160, size 0x10
    union Q n_xyzf1; // offset 0x170, size 0x10
    union Q n_stq0; // offset 0x180, size 0x10
    union Q n_rgba0; // offset 0x190, size 0x10
    union Q n_xyzf0; // offset 0x1A0, size 0x10
} TriangleSpecularNormal;

typedef struct TriangleNormalEnvironSpecular {
    // total size: 0x250
    union Q dmatag; // offset 0x0, size 0x10
    union Q n_giftag; // offset 0x10, size 0x10
    union Q n_tex0; // offset 0x20, size 0x10
    union Q n_clamp; // offset 0x30, size 0x10
    union Q n_stq2; // offset 0x40, size 0x10
    union Q n_rgba2; // offset 0x50, size 0x10
    union Q n_xyzf2; // offset 0x60, size 0x10
    union Q n_stq1; // offset 0x70, size 0x10
    union Q n_rgba1; // offset 0x80, size 0x10
    union Q n_xyzf1; // offset 0x90, size 0x10
    union Q n_stq0; // offset 0xA0, size 0x10
    union Q n_rgba0; // offset 0xB0, size 0x10
    union Q n_xyzf0; // offset 0xC0, size 0x10
    union Q e_giftag; // offset 0xD0, size 0x10
    union Q e_tex0; // offset 0xE0, size 0x10
    union Q e_clamp; // offset 0xF0, size 0x10
    union Q e_rgba; // offset 0x100, size 0x10
    union Q e_stq2; // offset 0x110, size 0x10
    union Q e_xyzf2; // offset 0x120, size 0x10
    union Q e_stq1; // offset 0x130, size 0x10
    union Q e_xyzf1; // offset 0x140, size 0x10
    union Q e_stq0; // offset 0x150, size 0x10
    union Q e_xyzf0; // offset 0x160, size 0x10
    union Q s_giftag; // offset 0x170, size 0x10
    union Q s_tex0; // offset 0x180, size 0x10
    union Q s_clamp; // offset 0x190, size 0x10
    union Q s_alpha; // offset 0x1A0, size 0x10
    union Q s_fogcol; // offset 0x1B0, size 0x10
    union Q s_rgba; // offset 0x1C0, size 0x10
    union Q s_stq2; // offset 0x1D0, size 0x10
    union Q s_xyzf2; // offset 0x1E0, size 0x10
    union Q s_stq1; // offset 0x1F0, size 0x10
    union Q s_xyzf1; // offset 0x200, size 0x10
    union Q s_stq0; // offset 0x210, size 0x10
    union Q s_xyzf0; // offset 0x220, size 0x10
    union Q S_alpha; // offset 0x230, size 0x10
    union Q S_fogcol; // offset 0x240, size 0x10
} TriangleNormalEnvironSpecular;

typedef struct TriangleNormalUnknown {
	union Q dmatag;
	union Q n_giftag;
	union Q unknown_0x20;
	union Q unknown_0x30;
	union Q unknown_0x40;
	union Q unknown_0x50;
	union Q unknown_0x60;
	union Q unknown_0x70;
	union Q unknown_0x80;
	union Q unknown_0x90;
	union Q unknown_0xa0;
	union Q unknown_0xb0;
	union Q unknown_0xc0;
	union Q u_giftag;
	union Q unknown_0xe0;
	union Q unknown_0xf0;
	union Q unknown_0x100;
	union Q unknown_0x110;
	union Q unknown_0x120;
	union Q unknown_0x130;
	union Q unknown_0x140;
	union Q unknown_0x150;
	union Q unknown_0x160;
	union Q unknown_0x170;
	union Q unknown_0x180;
	union Q unknown_0x190;
	union Q unknown_0x1a0;
} TriangleNormalUnknown;

typedef struct AllPacket {
    // total size: 0xFE0
    struct TriangleNormal normal[2]; // offset 0x0, size 0x1A0
    struct TriangleNormalSpecular normal_specular[2]; // offset 0x1A0, size 0x360
    struct TriangleSpecularNormal specular_normal[2]; // offset 0x500, size 0x360
    struct TriangleNormalUnknown unknown[2]; // offset 0x860, size 0x1B0
} AllPacket;

typedef struct PersData {
    // total size: 0x70
    float vsp[2][4]; // offset 0x0, size 0x20
    float vcp[2][4]; // offset 0x20, size 0x20
    float xyz_min[4]; // offset 0x40, size 0x10
    float xyz_max[4]; // offset 0x50, size 0x10
    float rgba_max[4]; // offset 0x60, size 0x10
} PersData;
typedef struct PLightData {
    // total size: 0x80
    float nlm[4][4]; // offset 0x0, size 0x40
    float lcm[4][4]; // offset 0x40, size 0x40
} PLightData;
typedef struct Lambert0Data {
    // total size: 0x80
    float nlm[4][4]; // offset 0x0, size 0x40
    float lcm[4][4]; // offset 0x40, size 0x40
} Lambert0Data;
typedef struct Lambert1Data {
    // total size: 0x10
    float global_ambient[4]; // offset 0x0, size 0x10
} Lambert1Data;
typedef struct ELightData {
    // total size: 0x40
    float pos[4]; // offset 0x0, size 0x10
    float dir[4]; // offset 0x10, size 0x10
    float col[4]; // offset 0x20, size 0x10
    float param[4]; // offset 0x30, size 0x10
} ELightData;
typedef struct EMapData {
    // total size: 0x60
    float vwm[4][4]; // offset 0x0, size 0x40
    float mag[4]; // offset 0x40, size 0x10
    float offset[4]; // offset 0x50, size 0x10
} EMapData;
typedef struct SMapData {
    // total size: 0x40
    float nhm[4][4]; // offset 0x0, size 0x40
} SMapData;
typedef struct AllData_Vu0 {
    // total size: 0x600
    struct PLightData plight[4]; // offset 0x0, size 0x200
    struct ELightData elight[8]; // offset 0x200, size 0x200
    struct Lambert0Data lambert0; // offset 0x400, size 0x80
    struct Lambert1Data lambert1; // offset 0x480, size 0x10
    struct SMapData smap __attribute__((aligned(64)));
    struct PersData pers __attribute__((aligned(64)));
    char unknown_0x580[0x64] __attribute__((aligned(64))); // guessed size
    struct EMapData emap __attribute__((aligned(64)));
} AllData_Vu0;

typedef struct ClusterData {
    // total size: 0x6
    unsigned short src; // offset 0x0, size 0x2
    unsigned short dst; // offset 0x2, size 0x2
    unsigned short n; // offset 0x4, size 0x2
} ClusterData;

typedef struct Data {
    // total size: 0x10
    union Q rgba; // offset 0x0, size 0x10
} Data;


void FlipXMTOP();
static void DrawParts0(ktVif1Ot2 * ot /* r17 */, ModelWork * work /* r2 */, void (*make)(Part*), void (*draw)(ktVif1Ot2*, Part*, ModelWork*));

extern u_int model3_mpg0_skel_load[];
extern signed int initialized; // @ 0x00419FA0

extern __int128* D_01EE30C0; // packet buffer
extern __int128 D_003B63C0;
extern __int128 D_003BA2C0;

extern Model3Junk model3_junk;

extern int D_003B5280;
extern u_int D_003B53B0;
extern int D_003B55C0;
extern u_int D_003B57D0;

extern s32 xitop;
extern AllData_Vu0 * pAllData_Vu0;

extern u32 _vu_0_0x00380640;
extern u32 _vu_0_0x00380F00;
extern u32 _vu_0_0x00381200;

extern u32 D_003B5D00;
extern u32 D_003B5E40;
extern u32 D_003B6200;
extern u32 D_003B6A80;

extern u32 model3_mpg0_lambert_size;
extern u32 model3_mpg0_para_size;
extern u32 model3_mpg0_point_size;
extern u32 model3_mpg0_spot_size;

extern u32 model3_mpg0_specular_size;
// extern u32 model3_mpg0_persfvg_size;
// extern u32 model3_mpg0_venvmap_size;
extern u32 D_003BAEB0;

extern int D_003B61C0;
extern int D_003BAD60;
extern u_int D_003B6940; // vutext
extern u_int D_003B6080; // vutext
extern u_int D_003BAB80; // vutext
extern u_int D_003BAD80; // vutext

extern u_int D_003B9F40;
extern u_int D_003BA080;
extern u_int D_003BA0C0;
extern u_int D_003BA170;
extern u_int D_003BAA00;
extern u_int D_003BAB50;

extern int func_001C91F0();
extern int func_001D0EA0(); // gets model n parts?
extern Part* func_001D0EC0();
extern int func_0025C0A0();

extern void func_0025BF10(Q*, s32 arg1, s32 arg2);
extern void func_0025C000(void*);
extern void func_0025C0D0(Q*);

extern int D_01EE3DE0;
extern int draw_base;

extern u32 xmtop;
extern AllPacket* all_packet;
extern int calc_base;
extern void (* sort_functions[8])(struct ktVif1Ot2 *, struct Part *); // size: 0x20, address: 0x2A9730

extern void func_0011FD28(sceVif0Packet *pPacket, u_long128 *pBase);
extern void func_0011FE80(sceVif0Packet*, __int128*, int);
extern s32 func_001CC680();

#endif

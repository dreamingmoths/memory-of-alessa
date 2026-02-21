#ifndef MODEL3_VU0_N_H
#define MODEL3_VU0_N_H

#include "eetypes.h"
#include "common.h"
#include "model_common.h"
#include "libdmapk.h"

#define GIF_REG(reg, n) ((u_long)(reg) << ((n) * 4))

#define DMArefe (0<<28)
#define DMAcnt  (1<<28)
#define DMAnext (2<<28)
#define DMAref  (3<<28)
#define DMArefs (4<<28)
#define DMAcall (5<<28)
#define DMAret  (6<<28)
#define DMAend  (7<<28)

union Q
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
};

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

typedef struct AllPacket {
    // total size: 0xFE0
    struct TriangleNormal normal[2]; // offset 0x0, size 0x1A0
    struct TriangleNormalEnviron normal_environ[2]; // offset 0x1A0, size 0x2E0
    struct TriangleNormalSpecular normal_specular[2]; // offset 0x480, size 0x360
    struct TriangleNormalEnvironSpecular normal_environ_specular[2]; // offset 0x7E0, size 0x4A0
    struct TriangleSpecularNormal specular_normal[2]; // offset 0xC80, size 0x360
} AllPacket;

typedef struct ClusterData {
    // total size: 0x6
    unsigned short src; // offset 0x0, size 0x2
    unsigned short dst; // offset 0x2, size 0x2
    unsigned short n; // offset 0x4, size 0x2
} ClusterData;

extern u_int model3_mpg0_skel_load[];
extern signed int initialized; // @ 0x00419FA0

extern __int128* D_01EE30C0; // packet buffer
extern __int128 D_003B63C0;
extern __int128 D_003BA2C0;

extern Model3Junk model3_junk;

extern void func_0011FD28(sceVif0Packet *pPacket, u_long128 *pBase); // scePkInit
extern void func_0011FE80(sceVif0Packet*, __int128*, int);

#endif

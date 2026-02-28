#ifndef MODEL3_VU0_N_H
#define MODEL3_VU0_N_H

#include "eetypes.h"
#include "sh2_common.h"
#include "libdma.h"

#define GIF_REG(reg, n) ((u_long)(reg) << ((n) * 4))

#define DMArefe (0<<28)
#define DMAcnt  (1<<28)
#define DMAnext (2<<28)
#define DMAref  (3<<28)
#define DMArefs (4<<28)
#define DMAcall (5<<28)
#define DMAret  (6<<28)
#define DMAend  (7<<28)

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

typedef struct SMapData {
    // total size: 0x40
    float nhm[4][4]; // offset 0x0, size 0x40
} SMapData;
typedef struct ktVif1Ot2 {
    // total size: 0x20
    struct _sceDmaTag * top_1; // offset 0x0, size 0x4
    struct _sceDmaTag * top_2; // offset 0x4, size 0x4
    unsigned int n_bits_1; // offset 0x8, size 0x4
    unsigned int n_bits_2; // offset 0xC, size 0x4
    unsigned int length_1; // offset 0x10, size 0x4
    unsigned int length_2; // offset 0x14, size 0x4
    unsigned int mask_1; // offset 0x18, size 0x4
    unsigned int mask_2; // offset 0x1C, size 0x4
};
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
typedef struct AllData_Vu0 {
    // total size: 0x600
    struct PLightData plight[4]; // offset 0x0, size 0x200
    struct ELightData elight[8]; // offset 0x200, size 0x200
    struct Lambert0Data lambert0; // offset 0x400, size 0x80
    struct Lambert1Data lambert1; // offset 0x480, size 0x10
    struct EMapData emap __attribute__((aligned(64))); // offset 0x4C0, size 0x60
    struct SMapData smap __attribute__((aligned(64))); // offset 0x540, size 0x40
    struct PersData pers __attribute__((aligned(64))); // offset 0x580, size 0x70
} AllData_Vu0;

typedef struct ClusterData {
    // total size: 0x6
    unsigned short src; // offset 0x0, size 0x2
    unsigned short dst; // offset 0x2, size 0x2
    unsigned short n; // offset 0x4, size 0x2
} ClusterData;

static void FlipXMTOP();
void KickCalcPartPacket();
void TransferToSPR();
void PrepareSort();
static void MakeData0();
static void LoadProgram_Vu0();

extern u_int xmtop; // size: 0x4, address: 0x41AC40
extern int model3_mpg0_clipv_size; // size: 0x4, address: 0x37FF20
extern int model3_mpg0_clip1_size; // size: 0x4, address: 0x37FD90
extern int model3_mpg0_clip0v_size; // size: 0x4, address: 0x37FB70

extern u_int _vu_0_0x0037F980;
extern u_int _vu_0_0x0037FB80;
extern u_int _vu_0_0x0037FDC0;

extern u_int model3_mpg0_skel_load[];
extern signed int initialized; // @ 0x00419FA0
extern __int128 * packet_buffer; // r2

extern struct AllData_Vu0 alldata_Vu0_Dblbuffer[2]; // size: 0xC00, address: 0x41A040
extern int alldata_Vu0_page;
extern f32 mag_114;
extern f32 offset_115;
extern struct AllData_Vu0 * pAllData_Vu0;
extern AllPacket* all_packet;
extern int calc_base;

#endif

#ifndef VC_PLAY_H
#define VC_PLAY_H

#include "sh2_common.h"
#include "Chacter/character.h"
#include "SH2_common/sh2dt.h"

// total size: 0xD0
typedef struct _VC_PRE_INFO {
    // Members
    float hero_neck_wm[4][4]; // offset 0x0, size 0x40
    float hero_neck_lm[4][4]; // offset 0x40, size 0x40
    float hero_neck_lwm[4][4]; // offset 0x80, size 0x40
    float hero_head_ang_x; // offset 0xC0, size 0x4
    float hero_head_ang_y; // offset 0xC4, size 0x4
    float hero_eye_y; // offset 0xC8, size 0x4
} VC_PRE_INFO;

// total size: 0x40
typedef struct _KANRI {
    // Members
    float pos[4]; // offset 0x0, size 0x10
    float ang[4]; // offset 0x10, size 0x10
    float rot_spd[4]; // offset 0x20, size 0x10
    float velo_y; // offset 0x30, size 0x4
    float velo_xz; // offset 0x34, size 0x4
    float velo_houi; // offset 0x38, size 0x4
} KANRI;

// total size: 0x50
typedef struct _SYS_W {
    // Members
    float cam_ang_y; // offset 0x0, size 0x4
    float cam_ang_z; // offset 0x4, size 0x4
    float cam_r_xz; // offset 0x8, size 0x4
    float cam_y; // offset 0xC, size 0x4
    struct _KANRI hero; // offset 0x10, size 0x40
} SYS_W;

extern void GetPlayerPartsLocalMatrix(float (* mat)[4] /* r2 */, u_int parts_name /* r17 */);
extern void GetPlayerPartsWorldMatrix(float (* mat)[4] /* r2 */, u_int parts_name /* r2 */);
extern float PlayerGetNeckAngleX(void);
extern float PlayerGetNeckAngleY(void);
extern float shAtan2(float, float);
extern void shMulMatrix(float (* m0)[4] /* r2 */, float (* m1)[4] /* r2 */, float (* m2)[4] /* r2 */);
extern float shGetFPS(void);

extern struct shPlayerWork sh2jms;
extern SYS_W sys;
extern VC_PRE_INFO vcPreInfo;

#endif
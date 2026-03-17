#ifndef MODEL3_SUB_N_H
#define MODEL3_SUB_N_H

#include "common.h"
#include "model_common.h"

typedef struct ModelWork
{
    // total size: 0x30
    u_int id;                                 // offset 0x0, size 0x4
    float (*relatives)[4][4];                 // offset 0x4, size 0x4
    float (*matrices)[4][4];                  // offset 0x8, size 0x4
    float *cluster_weights;                   // offset 0xC, size 0x4
    __int128 equipment_flag;                  // offset 0x10, size 0x10
    int (*draw_hook)(void *, void *, void *); // offset 0x20, size 0x4
    void *draw_hook_data;                     // offset 0x24, size 0x4
} ModelWork;

typedef struct
{
    int texture_id;
    int text_pos_param;
} ModelTextPose;

extern Model3Junk model3_junk;
extern sceVu0FMATRIX D_003669A0;
extern sceVu0FVECTOR D_00366910;
extern sceVu0FVECTOR D_00366920;
extern sceVu0FVECTOR D_01EE15E0;
extern sceVu0FVECTOR D_00366930;
extern sceVu0FVECTOR D_00366940;
extern sceVu0FVECTOR D_00366950;
extern sceVu0FVECTOR D_00366960;
extern sceVu0FVECTOR D_00366970;
extern sceVu0FVECTOR D_00366980;
extern sceVu0FVECTOR D_00366990;
void shMulMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1, sceVu0FMATRIX m2);

extern int D_01EE3080;
extern float D_00366918;
extern float D_00366948;
extern float D_00366938;
extern float D_01EE15E8;
extern float D_00366928;

float func_001B4200(void);
float func_001B4210(void);
s64 func_001CC710(int flag, int text_poses_offset, int texture_blocks_offset);
int func_001D0D80(int tex);
int func_001D0DB0(int tex);
int func_001D0DF0(int tex);
void sh3gfw_Thr_d2TextureSend(int tex0, int arg1, int tex1, int tex2);
__int128 *func_001B5B00(int tex0, int text_pos_param, int arg2);

#endif

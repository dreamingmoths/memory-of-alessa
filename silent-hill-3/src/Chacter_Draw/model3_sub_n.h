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

typedef struct
{
    ModelWork works[16];
    void *current;
} ModelWorkGroup;

// By wrapping, we encourage more quadword ops
typedef struct
{
    sceVu0FMATRIX m;
} ModelMatrix;

extern Model3Junk model3_junk;
void shMulMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1, sceVu0FMATRIX m2);

extern int initialized;

/**
 * @brief Gets cluster weights from `ModelWork`.
 */
float* func_001D3780(void *work_);

float func_001B4200(void);
float func_001B4210(void);
s64 func_001CC710(int flag, int text_poses_offset, int texture_blocks_offset);
int func_001D0D80(int tex);
int func_001D0DB0(int tex);
int func_001D0DF0(int tex);
void sh3gfw_Thr_d2TextureSend(int tex0, int arg1, int tex1, int tex2);
__int128 *func_001B5B00(int tex0, int text_pos_param, int arg2);
void func_001D37C0(void *work, __int128 mask, __int128 value);
#endif

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

extern Model3Junk model3_junk;
void shMulMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1, sceVu0FMATRIX m2);

extern int initialized;

/**
 * @brief Gets cluster weights from `ModelWork`.
 */
float* func_001D3780(void *work_);

extern float func_001B4200(void);
extern float func_001B4210(void);

#endif

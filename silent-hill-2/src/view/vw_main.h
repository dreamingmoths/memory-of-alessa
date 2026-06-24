#ifndef VW_MAIN_H
#define VW_MAIN_H

#include "sh2_common.h"

typedef struct _VbCOORDINATE {
    // total size: 0x140
    u_int flg;                   // offset 0x0, size 0x4
    sceVu0FMATRIX coord;         // offset 0x10, size 0x40
    sceVu0FMATRIX work;          // offset 0x50, size 0x40
    u_int* param;                // offset 0x90, size 0x4
    struct _VbCOORDINATE* super; // offset 0x94, size 0x4
    struct _VbCOORDINATE* sub;   // offset 0x98, size 0x4
    struct /* @anon0 */ {
        // total size: 0x8
        short vx;      // offset 0x0, size 0x2
        short vy;      // offset 0x2, size 0x2
        short vz;      // offset 0x4, size 0x2
        short pad;     // offset 0x6, size 0x2
    } r;               // offset 0x9C, size 0x8
    sceVu0FMATRIX lw;  // offset 0xB0, size 0x40
    sceVu0FMATRIX ls;  // offset 0xF0, size 0x40
    sceVu0FVECTOR rot; // offset 0x130, size 0x10
} VbCOORDINATE;

typedef struct _VbRVIEW {
    /* 0x00 */ sceVu0FVECTOR vp;
    /* 0x10 */ sceVu0FVECTOR vr;
    /* 0x20 */ float rz;
    /* 0x24 */ VbCOORDINATE* super;
} VbRVIEW;

typedef struct _VW_VIEW_WORK {
    /* 0x000 */ VbRVIEW rview;
    /* 0x030 */ VbCOORDINATE vwcoord;
    /* 0x170 */ sceVu0FVECTOR worldpos;
    /* 0x180 */ sceVu0FVECTOR worldang;
} VW_VIEW_WORK;

extern VW_VIEW_WORK vwViewPointInfo;

void vwInitViewInfo(void);

void vwGetViewPosition(sceVu0FVECTOR pos);

void vwGetViewAngle(sceVu0FVECTOR ang);

void vwSetCoordRefAndEntou(VbCOORDINATE* parent_p, sceVu0FVECTOR ref, float cam_ang_y, float cam_ang_z, float cam_y, float cam_xz_r);

void vwSetViewInfo(void);

void vwSetViewInfoDirectMatrix(VbCOORDINATE* pcoord, sceVu0FMATRIX cammat);

#endif // VW_MAIN_H

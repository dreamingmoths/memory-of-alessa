#ifndef VW_MAIN_H
#define VW_MAIN_H

#include "sh2_common.h"
#include "view/vb_main.h"

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

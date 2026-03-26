#ifndef HH_CLASS_WRAPPER_H
#define HH_CLASS_WRAPPER_H

#include "common.h"

void HH_ClassWrapper_WorldScreenMatrix_Get(sceVu0FMATRIX m);
void HH_ClassWrapper_ViewFrustum_Primitive_ClipMatrix_Get(sceVu0FMATRIX m);
float HH_ClassWrapper_Float_Clamp(float, float, float);
float HH_ClassWrapper_FogParameter_A_Get(void);
float HH_ClassWrapper_FogParameter_B_Get(void);
void HH_ClassWrapper_Transform_PerspectiveProjection_Clip_forTriangleStrip(int*, sceVu0FVECTOR, sceVu0FMATRIX, sceVu0FMATRIX, float*);

#endif

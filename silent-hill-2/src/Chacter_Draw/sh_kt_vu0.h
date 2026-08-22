#ifndef SH_KT_VU0_H
#define SH_KT_VU0_H

#include "sh2_common.h"
#include "sce/libvu0.h"

/* apply a 4x4 matrix to a vector */
void ktVu0ApplyMatrixXYZ1(float* v0, sceVu0FMATRIX m0, float* v1);

/* apply a 3x3 matrix to a vector */
void ktVu0ApplyMatrixXYZ0(float* v0, sceVu0FMATRIX m0, float* v1);

/* convert float vector to integer */
void ktVu0FTOI4VectorXYZ(int* v0, float* v1);

#endif // SH_KT_VU0_H

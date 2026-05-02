#ifndef SH_VU0_H
#define SH_VU0_H

float sh_ecossin(float);

float shAtan_asm(float);

float shSway1f(float, float);

float shSway1f_asm(float, float);

void shMulMatrix(float (* m0)[4], float (* m1)[4], float (* m2)[4]);

void shRotMatrixY(float (* m0)[4], float (* m1)[4], float);

void shRotMatrixX(float (* m0)[4], float (* m1)[4], float);

void shMulMatrix(float (* m0)[4], float (* m1)[4], float (* m2)[4]);

float shAngleRegulate(float);

float shSinF(float);

float shRandF(void);

void shQzero(void*, int);

void shCreateNormal(float* out, float* vx, float* vy, float* fz);

#endif // SH_VU0_H

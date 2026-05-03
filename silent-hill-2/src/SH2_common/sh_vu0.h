#ifndef SH_VU0_H
#define SH_VU0_H

#include "common.h"

float shAngleRegulate(void);
float shAtanV(void);
float shAtan2(float y, float x);
float shAtan_asm(float angle);
void sh_ecossin(void);
float shSinF(float);
float shCosF(float);
void shSinCosV(void);
void shSinCosV_Scale(void);
void shRotVectorY(void);
void shRotMatrixX(void);
void shRotMatrixY(void);
void shRotMatrixZ(void);
void sh_mulmatrix(void);
void shSrand(int seed);
void shPushRandSeed(int seed);
int shPopRandSeed(void);
int shRandI(void);
float shRandF(void);
void shRandF_asm(void);
void shRandV_Scale(void);
void shRandV_asm(void);
float shSway1f(float, float);
void shSway1f_asm(void);
void shCreateNormal(float*, float*, float*, float*);
void shSetMiniMaxN(float* min, float* max, float* v, int n);
char shScreenClipI(int* v0);
char shScreenClipF(float* v0);
void shQzero(void*, int);
void shFill(void);
void shMulMatrix(float m0[4], float m1[4], float m2[4]);

#endif // SH_VU0_H

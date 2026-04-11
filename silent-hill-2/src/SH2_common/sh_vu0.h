#ifndef SH_VU0_H
#define SH_VU0_H

#include "common.h"

float shAngleRegulate();
float shAtanV();
float shAtan2();
void shAtan_asm();
void sh_ecossin();
float shSinF();
float shCosF();
void shSinCosV();
void shSinCosV_Scale();
void shRotVectorY();
void shRotMatrixX();
void shRotMatrixY();
void shRotMatrixZ();
void sh_mulmatrix();
void shSrand(int seed);
void shPushRandSeed(int seed);
int shPopRandSeed();
int shRandI();
float shRandF();
void shRandF_asm();
void shRandV_Scale();
void shRandV_asm();
float shSway1f();
void shSway1f_asm();
void shCreateNormal();
void shSetMiniMaxN();
char shScreenClipI(int* v0);
char shScreenClipF(float* v0);
void shQzero();
void shFill();
void shMulMatrix(float m0[4], float m1[4], float m2[4]);

#endif // SH_VU0_H

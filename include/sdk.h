#ifndef ALESSA_SDK_H
#define ALESSA_SDK_H

/**
 * unsorted gcc functions + other common sdk/library helpers
 */

#include "types.h"

extern float asinf(float);
extern float fabsf(float);
extern float cosf(float);
extern float sinf(float);
extern float atan2f(float, float);
extern float fmodf(float, float);
extern float sqrtf(float);

extern double sin(double);
extern double cos(double);

extern int abs(int);

extern u_int fptoui(float);
extern int fptosi(float);

extern double dpdiv(double, double);

extern void qsort(int*, int, int, int (*)(void*, void*));

extern int CreateSema2(int, int, const s_char*);

#endif // ALESSA_SDK_H

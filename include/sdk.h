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

extern u_int fptoui(float);
extern int fptosi(float);

extern double dpdiv(double, double);

extern void qsort(int*, int, int, int (*)(void*, void*));

#endif // ALESSA_SDK_H

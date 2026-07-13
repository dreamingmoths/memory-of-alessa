#ifndef ALESSA_SDK_H
#define ALESSA_SDK_H

/**
 * unsorted gcc functions + other common sdk/library helpers
 */

#include "types.h"

extern void* memcpy(void* __dest, void* __src, u_int __n);
extern float asinf(float);
extern float fabsf(float);
extern float cosf(float);
extern float sinf(float);
extern float atan2f(float, float);
extern float fmodf(float, float);
extern u_int fptoui(float);
extern double dpdiv(double, double);

#endif // ALESSA_SDK_H

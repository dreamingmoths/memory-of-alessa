#ifndef SH2_COMMON_H
#define SH2_COMMON_H

#include "common.h"

#pragma fast_fptosi off

static inline int clamp(int b, int i) {
    asm("slt $t7, %1, %0; movn %0, %1, $t7" : "=r"(b) : "r"(i) :);
    return b;
}

static inline int clamp_max(int b, int i) {
    asm("slt $t7, %0, %1; movn %0, %1, $t7" : "=r"(b) : "r"(i) :);
    return b;
}

static inline int clamp_n_reverse(int value, u_int n) {
    int result = value >> n;
    if (value < 0)
        result = (value + ((1 << n) - 1)) >> n;
    return result;
}
static inline int clamp_n(int value, int n) {
    int result = value & ((1 << n) - 1);
    if (value < 0 && result != 0)
        result -= (1 << n);
    return result;
}

extern float sqrtf(float);

#endif

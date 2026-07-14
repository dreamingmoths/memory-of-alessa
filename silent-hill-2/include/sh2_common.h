#ifndef SH2_COMMON_H
#define SH2_COMMON_H

#include "common.h"

#pragma fast_fptosi off

// @todo: find a proper home for these
#define MATERIAL_TYPE_0  0
#define MATERIAL_TYPE_1  1
#define MATERIAL_TYPE_2  2
#define MATERIAL_TYPE_3  3
#define MATERIAL_TYPE_4  4
#define MATERIAL_TYPE_5  5
#define MATERIAL_TYPE_6  6
#define MATERIAL_TYPE_7  7
#define MATERIAL_TYPE_8  8
#define MATERIAL_TYPE_9  9
#define MATERIAL_TYPE_10 10
#define MATERIAL_TYPE_11 11
#define MATERIAL_TYPE_12 12

#define SH2_SOUND_19031 19031
#define SH2_SOUND_19032 19032
#define SH2_SOUND_19033 19033
#define SH2_SOUND_19034 19034
#define SH2_SOUND_19035 19035
#define SH2_SOUND_19036 19036
#define SH2_SOUND_19037 19037
#define SH2_SOUND_19038 19038
#define SH2_SOUND_19039 19039
#define SH2_SOUND_19040 19040
#define SH2_SOUND_19041 19041

// @todo: move to vec.h if possible, but arg order is different from the one we
// have for sh3 `amusement_01`
static inline float vec3_dist_xz(sceVu0FVECTOR w, sceVu0FVECTOR v) {
    float d;
    asm("lwc1 %2, 0(%0)\n\
         lwc1 f8, 0(%1)\n\
         lwc1 f9, 8(%0)\n\
         lwc1 f10, 8(%1)\n\
         sub.s %2, %2, f8\n\
         sub.s f9, f9, f10\n\
         mula.s %2, %2;\
         madd.s %2, f9, f9\n\
         sqrt.s %2, %2"
        : "+r"(v), "+r"(w), "+f"(d)::"f8", "f9", "f10");
    return d;
}

static inline float vec3_dist_xz_reverse(sceVu0FVECTOR v, sceVu0FVECTOR w) {
    float d;
    asm("lwc1 %2, 0(%0)\n\
         lwc1 f8, 0(%1)\n\
         lwc1 f9, 8(%0)\n\
         lwc1 f10, 8(%1)\n\
         sub.s %2, %2, f8\n\
         sub.s f9, f9, f10\n\
         mula.s %2, %2;\
         madd.s %2, f9, f9\n\
         sqrt.s %2, %2"
        : "+r"(v), "+r"(w), "+f"(d)::"f8", "f9", "f10");
    return d;
}

static inline float reflex_angle(float x) {
    float result;
    if (x > 0.0f) {
        result = fmodf(x, TAU);
        if (result > PI)
            result -= TAU;
    } else {
        result = fmodf(x, -TAU);
        if (result < -PI)
            result += TAU;
    }
    return result;
}

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

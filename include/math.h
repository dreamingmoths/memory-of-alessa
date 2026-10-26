#ifndef ALESSA_MATH_H
#define ALESSA_MATH_H

#include "sdk.h"

/**
 * miscellaneous math + float helpers used in sh2+3.
 */

#define NULL 0
#define PI 3.1415927f
#define TAU 6.2831855f
#define QUARTER_TURN 1.5707964f
#define MAX_FLOAT 3.4028235e38f
#define TIME_STEP_30FPS (1.0f / 30.0f)
#define TIME_STEP_60FPS (1.0f / 60.0f)
#define RADIANS_PER_DEGREE (PI / 180.0f)
#define TO_RAD(x) (RADIANS_PER_DEGREE * (x))
#define SQUARE(_x) ((_x) * (_x))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(x, min, max) \
    (((x) < (min)) ? (min) : (((x) > (max)) ? (max) : (x)))
#define CLAMP_MAX(_val, _max) do { (_val) = (_val) > (_max) ? (_val) : (_max); } while (0)
#define CLAMP_MIN(_val, _min) do { (_val) = (_val) > (_min) ? (_min) : (_val); } while (0)
#define IS_IN_RANGE(x, min, max) (((x) >= (min) && (x) < max) ? 1 : 0)
#define ABS_WITHIN_TOLERANCE(x, range) IS_IN_RANGE(x, -range, range)
#define COLOR_RGBA(r, g, b, a) (((a) << 24) | ((((b) << 16) | ((r) | ((g) << 8)))))
#define COLOR_RGB(r, g, b) ((((b) << 16) | ((r) | ((g) << 8))))
#define Q4(x) (int)((x) * 16)

// Convert a reflex angle (> 180deg, or < -180deg) to the range [-PI, PI].
#define REFLEX_ANGLE(out, value) do { \
    float ret; \
    if (value > PI) ret = value-TAU; \
    else if (value < -PI) ret = value+TAU; \
    else ret = value; \
    out = ret; \
} while (0)
#define GET_REFLEX_ANGLE(x) (((x) > PI) != 0 ? (x) - TAU : ((x) < -PI) ? (x) + TAU : (x))

static inline float shReflexAngle(float x) {
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

static inline int shClamp(int value, int low, int high) {
    asm("slt $t6, %0, %1; slt $t7, %2, %0; movn %0, %1, $t6; movn %0, %2, $t7" : "=r"(value) : "r"(low), "r"(high) :);
    return value;
}

static inline int shClampMin(int b, int i) {
    asm("slt $t7, %1, %0; movn %0, %1, $t7" : "=r"(b) : "r"(i) :);
    return b;
}

static inline int shClampMax(int b, int i) {
    asm("slt $t7, %0, %1; movn %0, %1, $t7" : "=r"(b) : "r"(i) :);
    return b;
}

static inline int shClampNReverse(int value, u_int n) {
    int result = value >> n;
    if (value < 0)
        result = (value + ((1 << n) - 1)) >> n;
    return result;
}
static inline int shClampN(int value, int n) {
    int result = value & ((1 << n) - 1);
    if (value < 0 && result != 0)
        result -= (1 << n);
    return result;
}

static inline int shAbs(int b) {
    asm("slt $t7, %0, $zero; neg $t6, %0; movn %0, $t6, $t7" : "=r"(b) :);
    return b;
}

static inline float shFloatAbs(float x) {
    asm("abs.s %0, %0" : "+f"(x));
    return x;
}

static inline float shFloatClamp(float x, float lower, float upper) {
    asm("max.s %0, %0, %1; min.s %0, %0, %2" : "+f"(x) : "f"(lower), "f"(upper));
    return x;
}

static inline float shFloatMin(float x, float y) {
    asm("min.s %0, %0, %1" : "+f"(x) : "f"(y) :);
    return x;
}

static inline float shFloatMax(float x, float y) {
    asm("max.s %0, %0, %1" : "+f"(x) : "f"(y) :);
    return x;
}

/* sqrt function for when `pragma fastmath` is not available */
static inline float SQRT(float x) {
    float result = x;
    asm("sqrt.s  %0, %0"
        : "+f"(result));
    return result;
}

#endif // ALESSA_MATH_H

#include "sh2_common.h"

float HH_MathWrapper_Sqrtf(float Value) {
    // 2.4 doesn't have `#pragma fastmath`
    asm volatile(
        "sqrt.s %0, %0" 
        : "=f"(Value)
    );

    return Value;
}

static const float fact9 = 1*2*3*4*5*6*7*8*9;
static const float fact8 = 1*2*3*4*5*6*7*8;
static const float fact7 = 1*2*3*4*5*6*7;
static const float fact6 = 1*2*3*4*5*6;
static const float fact5 = 1*2*3*4*5;
static const float fact4 = 1*2*3*4;
static const float fact3 = 1*2*3;
static const float fact2 = 1*2;

float HH_MathWrapper_Sinf(float x) {
    float x2 = x * x;
    float x3 = x2 * x;
    float x5 = x3 * x2;
    float x7 = x5 * x2;
    float x9 = x7 * x2;
    float result = x 
        + (-1.0f / fact3) * x3 + (1.0f / fact5) * x5
        + (-1.0f / fact7) * x7 + (1.0f / fact9) * x9;
    return result;
}

float HH_MathWrapper_Cosf(float x) {
    float x2 = x * x;
    float x4 = x2 * x2;
    float x6 = x4 * x2;
    float x8 = x6 * x2;
    float result = 1 
        + (-1.0f / fact2) * x2 + (1.0f / fact4) * x4
        + (-1.0f / fact6) * x6 + (1.0f / fact8) * x8;
    return result;
}

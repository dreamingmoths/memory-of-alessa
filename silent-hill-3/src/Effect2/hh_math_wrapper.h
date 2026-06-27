#ifndef HH_MATH_WRAPPER_H
#define HH_MATH_WRAPPER_H

static inline float HH_MathWrapper_Sqrtf(float Value) {
    // 2.4 doesn't have `#pragma fastmath`, but 3.0.3 does. however, using the
    // builtin `sqrtf` in `hh_class_wrapper` does not seem to match.
    asm (
        "sqrt.s %0, %0" 
        : "+f"(Value)
    );

    return Value;
}


#endif

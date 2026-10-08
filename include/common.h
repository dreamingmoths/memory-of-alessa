#ifndef COMMON_H
#define COMMON_H

#ifdef __MWERKS__
#pragma divbyzerocheck on
#pragma mpwc_relax     on
#pragma fast_fptosi    on
#endif

#include "types.h"
#include "math.h"
#include "sdk.h"
#include "ee.h"
#include "macros.h"

typedef union Q {
    u_long128 u128;  // offset 0x0, size 0x10
    u_long u64[2];   // offset 0x0, size 0x8
    u_int u32[4];    // offset 0x0, size 0x10
    u_short u16[8];  // offset 0x0, size 0x10
    u_char u8[16];   // offset 0x0, size 0x10
    long s64[2];     // offset 0x0, size 0x8
    int s32[4];      // offset 0x0, size 0x10
    short s16[8];    // offset 0x0, size 0x10
    s_char s8[16];   // offset 0x0, size 0x10
    int q[4];        // offset 0x0, size 0x10
    float fv[4];     // offset 0x0, size 0x10
    int iv[4];       // offset 0x0, size 0x10
} Q;

typedef union Q_WORDDATA {
    u_int ui32[4];   // offset 0x0, size 0x10
    u_short us16[8]; // offset 0x0, size 0x10
    float fl32[4];   // offset 0x0, size 0x10
    u_char uc8[16];  // offset 0x0, size 0x10
    int si32[4];     // offset 0x0, size 0x10
    short ss16[8];   // offset 0x0, size 0x10
    s_char sc8[16];  // offset 0x0, size 0x10
    u_long ul64[2];  // offset 0x0, size 0x8
    u_long128 ul128; // offset 0x0, size 0x10
} Q_WORDDATA __attribute__((aligned(16)));

typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vector4 __attribute__((aligned(16)));

typedef struct {
    int x;
    int y;
    int z;
    int w;
} IVector4 __attribute__((aligned(16)));

typedef struct {
    // total size: 0x40
    float d[4][4]; // offset 0x0, size 0x40
} Matrix4 __attribute__((aligned(16)));

static inline u_int reinterpret_as_u_int(float v) {
    return *(u_int*) &v;
}

static inline int float_floor(float x) {
    int out;
    asm("mfc1 %1, %0;\
          addi t7, zero, 1\n\
          slt %1, %1, zero\n\
          cvt.w.s %0, %0;\
          movz t7, zero, %1;\
          mfc1 %1, %0;\
          sub %1, %1, t7"
        : "+f"(x), "+r"(out)::"t7");
    return out;
}

#endif

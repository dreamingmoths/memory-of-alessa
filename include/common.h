#ifndef COMMON_H
#define COMMON_H

#pragma divbyzerocheck on
#pragma mpwc_relax     on

#include "libvu0.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef unsigned long u64;
typedef long s64;
typedef float f32;

typedef signed char s_char;
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;
typedef unsigned int u_long128;

#define NULL 0
#define PI 3.1415927f
#define QUARTER_TURN 1.5707964f
#define RADIANS_PER_DEGREE (PI / 180.0f)
#define TO_RAD(x) RADIANS_PER_DEGREE * (x)
#define MIN(a,b) ((a) > (b) ? (b) : (a))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

#define READ_UNCACHED(addr)      ((((u_int)(addr)) & 0x0fffffff) | 0x20000000)
#define GIF_REG(reg, n) ((u_long)(reg) << ((n) * 4))

#define GET_BIT(x, i) (((x) >> (i)) & 1)
#define GET_FLAG(x, i) (((x[i >> 5]) >> (i & 0x1F)) & 1)
#define SET_FLAG(x, i) ((x[i >> 5]) |= (1 << (i & 0x1F)))
#define REMOVE_FLAG(x, i) ((x)[(i) >> 5] &= ~(1 << ((i) & 0x1F)))

#define ABORT() asm("breakc 0")

#ifdef DEBUG
#define debugPrintf(...) printf(__VA_ARGS__)
#else
#define fjAssert(_cond, _file, _line)
#define debugPrintf(...)
#endif

#ifdef DEBUG
#include "debug.h"
#else
#define ASSERT(cond)
#define ASSERT_ON_LINE(cond, line)
#endif

#define INCLUDE_ASM(FOLDER, NAME)
#define INCLUDE_RODATA(FOLDER, NAME)

typedef union Q
{
    __int128 u128;         // offset 0x0, size 0x10
    unsigned long u64[2];  // offset 0x0, size 0x8
    unsigned int u32[4];   // offset 0x0, size 0x10
    unsigned short u16[8]; // offset 0x0, size 0x10
    unsigned char u8[16];  // offset 0x0, size 0x10
    signed long s64[2];    // offset 0x0, size 0x8
    signed int s32[4];     // offset 0x0, size 0x10
    signed short s16[8];   // offset 0x0, size 0x10
    signed char s8[16];    // offset 0x0, size 0x10
    signed int q[4];       // offset 0x0, size 0x10
    float fv[4];           // offset 0x0, size 0x10
    signed int iv[4];      // offset 0x0, size 0x10
} Q;

static inline int clamp(int b, int i) {
    asm("slt $t7, %1, %0; movn %0, %1, $t7" : "=r"(b) : "r"(i) : ); return b;
}

inline void vec_copy(void* dst, void* src) {
    asm volatile ("\
         lq t7, 0(%1)\n\
         sq t7, 0(%0)"
    : "=r"(dst): "r"(src): "t7");
}

inline void vec_add(void* x, void* y, void* out) {
    asm ("\
        lqc2 vf4, 0(%0)\n\
        lqc2 vf5, 0(%1)\n\
        vadd.xyzw vf4, vf4, vf5\n\
        sqc2 vf4, 0(%2)"
        : "=r"(x), "=r"(y): "r"(out));
}

extern void * memcpy(void *__dest, void *__src, u_int __n);

#endif

#ifndef COMMON_H
#define COMMON_H

#pragma divbyzerocheck on
#pragma mpwc_relax     on
#pragma fast_fptosi    on

#include "types.h"
#include "math.h"
#include "sdk.h"
#include "sce/libvu0.h"
#include "dma.h"

#define ABORT() asm("breakc 0")
#define BLOCK_WHILE(_cond) do { /* wait */ } while (_cond)

#define UNCACHED(p) ((char*)((u_int)p | 0x20000000))
#define READ_UNCACHED(addr) ((((u_int)(addr)) & 0x0fffffff) | 0x20000000)
#define UNCACHED_POINTER(addr) ((void*) ((((u_int)(addr)) & 0x0fffffff) | 0x20000000))
#define MAIN_RAM_POINTER(addr) ((void*) (((u_int)(addr)) & 0x0fffffff))

#define SCRATCHPAD_START 0x70000000

#define GIF_REG(reg, n) ((u_long)(reg) << ((n) * 4))

/* bit helpers */
#define GET_BIT(x, i) (((x) >> (i)) & 1)
#define SET_BIT(x, i) ((x) |= (1 << (i)))
#define UNSET_BIT(x, i) ((x) &= ~(1 << (i)))

/* bit array helpers */
#define GET_FLAG(x, i) ((((x)[(i) >> 5]) >> ((i) & 0x1F)) & 1)
#define SET_FLAG(x, i) (((x)[(i) >> 5]) |= (1 << ((i) & 0x1F)))
#define UNSET_FLAG(x, i) ((x)[(i) >> 5] &= ~(1 << ((i) & 0x1F)))

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

#define STATIC_ASSERT(cond, msg) \
    typedef char static_assertion_##msg[(cond) ? 1 : -1]
#define STATIC_ASSERT_SIZEOF(type, size) \
    typedef char static_assertion_sizeof_##type[(sizeof(type) == (size)) ? 1 : -1]

#define INCLUDE_ASM(FOLDER, NAME)
#define INCLUDE_RODATA(FOLDER, NAME)

// Convert a reflex angle (> 180deg, or < -180deg) to the range [-PI, PI].
#define REFLEX_ANGLE(out, value) do { \
    float ret; \
    if (value > PI) ret = value-TAU; \
    else if (value < -PI) ret = value+TAU; \
    else ret = value; \
    out = ret; \
} while (0);

typedef union Q {
    u_long128 u128;        // offset 0x0, size 0x10
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

typedef union Q_WORDDATA {
    u_int ui32[4];   // offset 0x0, size 0x10
    u_short us16[8]; // offset 0x0, size 0x10
    float fl32[4];   // offset 0x0, size 0x10
    u_char uc8[16];  // offset 0x0, size 0x10
    int si32[4];     // offset 0x0, size 0x10
    short ss16[8];   // offset 0x0, size 0x10
    char sc8[16];    // offset 0x0, size 0x10
    u_long ul64[2];  // offset 0x0, size 0x8
    __int128 ul128;  // offset 0x0, size 0x10
} Q_WORDDATA;

typedef struct
{
    float x;
    float y;
    float z;
    float w;
} Vector4 __attribute__((aligned(16)));

typedef struct
{
    int x;
    int y;
    int z;
    int w;
} IVector4 __attribute__((aligned(16)));

typedef struct {
    // total size: 0x40
    float d[4][4]; // offset 0x0, size 0x40
}  Matrix4 __attribute__((aligned(16)));

static inline u_int reinterpret_as_u_int(float v) {
    return *(u_int*) &v;
}

extern float asinf(float);
extern float fabsf(float);
extern float cosf(float);
extern float sinf(float);
extern float atan2f(float, float);
extern float fmodf(float, float);
extern float sqrtf(float);
extern u_int fptoui(float);
extern double dpdiv(double, double);
extern int fptosi(float);
extern void qsort(int*, int, int, int (*)(void*, void*));

#endif

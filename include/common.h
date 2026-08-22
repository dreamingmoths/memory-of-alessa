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
#include "sce/libvu0.h"

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

#define BLOCK_WHILE(_cond) do { /* wait */ } while (_cond)

/* bit helpers */
#define GET_BIT(x, i) (((x) >> (i)) & 1)
#define SET_BIT(x, i) ((x) |= (1 << (i)))
#define UNSET_BIT(x, i) ((x) &= ~(1 << (i)))

/* bit array helpers */
#define GET_FLAG(x, i) ((((x)[(i) >> 5]) >> ((i) & 0x1F)) & 1)
#define SET_FLAG(x, i) (((x)[(i) >> 5]) |= (1 << ((i) & 0x1F)))
#define UNSET_FLAG(x, i) ((x)[(i) >> 5] &= ~(1 << ((i) & 0x1F)))

#define STATIC_ASSERT(cond, msg) \
    typedef char static_assertion_##msg[(cond) ? 1 : -1]
#define STATIC_ASSERT_SIZEOF(type, size) \
    typedef char static_assertion_sizeof_##type[(sizeof(type) == (size)) ? 1 : -1]

#define INCLUDE_ASM(FOLDER, NAME)
#define INCLUDE_RODATA(FOLDER, NAME)

#ifndef __COMPATIBILITY__
#define ABORT() asm("breakc 0")
#else
#define ABORT() abort()
#endif

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

#endif

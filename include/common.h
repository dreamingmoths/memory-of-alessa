#ifndef COMMON_H
#define COMMON_H

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

#define READ_UNCACHED(addr)      ((((u_int)(addr)) & 0x0fffffff) | 0x20000000)

#define ABORT() asm("breakc 0")

#ifdef DEBUG
int fjAssert_(const char *file, int line, const char *str) __attribute__((noreturn))
{
    printf("assertion \"%s\" failed: file \"%s\", line %d\n", str, file, line);
    ABORT();
    return 1;
}
#define fjAssert(_cond, _file, _line)    \
    if (_cond)                           \
    {                                    \
        int foo = 0;                     \
    }                                    \
    else                                 \
    {                                    \
        fjAssert_(_file, _line, #_cond); \
    }
#define debugPrintf(...) printf(__VA_ARGS__)
#else
#define fjAssert(_cond, _file, _line)
#define debugPrintf(...)
#endif

#define INCLUDE_ASM(FOLDER, NAME)
#define INCLUDE_RODATA(FOLDER, NAME)

#endif

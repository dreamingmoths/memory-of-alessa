#ifndef ALESSA_MACROS_H
#define ALESSA_MACROS_H

#define CAT(a,b) CAT_(a,b)
#define CAT_(a,b) a##b

#define IS_DIGIT_CHARACTER(character) ((character) >= '0' && (character) <= '9')
#define CHAR_TO_INT(character) ((character) - '0')

#ifdef DEBUG
#define debugPrintf(...) printf(__VA_ARGS__)
#else
#define fjAssert(cond, file, line)
#define debugPrintf(...)
#endif

#ifdef DEBUG
#include "debug.h"
#else
#define ASSERT(cond)
#define ASSERT_ON_LINE(cond, line)
#endif

#define BLOCK_WHILE(cond) do { /* wait */ } while (cond)

/* bit helpers */
#define GET_BIT(x, i) (((x) >> (i)) & 1U)
#define SET_BIT(x, i) ((x) |= (1U << (i)))
#define UNSET_BIT(x, i) ((x) &= ~(1U << (i)))
#define FLIP_BIT(x, i) ((x) ^= (1U << (i)))

/* bit array helpers */
#define GET_FLAG(x, i) ((((x)[(i) >> 5]) >> ((i) & 0x1F)) & 1U)
#define SET_FLAG(x, i) (((x)[(i) >> 5]) |= (1U << ((i) & 0x1F)))
#define UNSET_FLAG(x, i) ((x)[(i) >> 5] &= ~(1U << ((i) & 0x1F)))

#define STATIC_ASSERT(cond, msg) \
    typedef char static_assertion_##msg[(cond) ? 1 : -1]
#define STATIC_ASSERT_SIZEOF(type, size) \
    typedef char static_assertion_sizeof_##type[(sizeof(type) == (size)) ? 1 : -1]

#define INCLUDE_ASM(FOLDER, NAME)
#define INCLUDE_RODATA(FOLDER, NAME)

#define UNMIGRATED(declaration) extern declaration
#define UNLINKED(declaration, ...) UNMIGRATED(declaration)

#endif // ALESSA_MACROS_H

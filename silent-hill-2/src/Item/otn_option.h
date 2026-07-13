#ifndef OTN_OPTION_H
#define OTN_OPTION_H

#include "sce/eetypes.h"

static inline void dword_struct_copy(u_int* dst, u_int* src, u_int size) {
    int i = size / 8;
    do {
        int w0 = src[0];
        int w1 = src[1];
        src += 2, i--;
        dst[0] = w0;
        dst[1] = w1;
        dst += 2;
    } while (i > 0);
}

#endif // OTN_OPTION_H

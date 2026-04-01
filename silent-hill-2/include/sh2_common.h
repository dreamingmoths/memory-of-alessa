#ifndef SH2_COMMON_H
#define SH2_COMMON_H

#define DEBUG

#include "common.h"

inline int clamp(int b, int i) {
    asm("slt $t7, %1, %0; movn %0, %1, $t7" : "=r"(b) : "r"(i) : ); return b;
}

inline int clamp_max(int b, int i) {
    asm("slt $t7, %0, %1; movn %0, %1, $t7" : "=r"(b) : "r"(i) : ); return b;
}

#endif

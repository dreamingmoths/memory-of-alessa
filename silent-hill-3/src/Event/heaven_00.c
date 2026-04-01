#include "heaven_00.h"

void func_01F6D680_heaven_00(void) {
    if (func_00199C70(6) != 0) {
        D_1D31670[3] |= 0x08000000;
    }
}

void func_01F6D6C0_heaven_00(void) {
    if (GET_FLAG(D_1D31670, 0x7B)) {
        func_0016CA40(0xD);
    }
}

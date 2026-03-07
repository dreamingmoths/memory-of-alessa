#include "heaven_00.h"

static inline int get_bit(int bit) {
    return (D_1D31670[bit / 32] >> (bit % 32)) & 1;
}

void func_01F6D680_heaven_00(void) {
    if (func_00199C70(6) != 0) {
        D_1D31670[3] |= 0x08000000;
    }
}

void func_01F6D6C0_heaven_00(void) {
    if (get_bit(0x7B)) { //((D_1D31670[3] >> 0x1B) & 1)
        func_0016CA40(0xD);
    }
}

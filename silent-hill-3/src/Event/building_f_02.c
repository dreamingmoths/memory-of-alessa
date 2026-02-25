#include "building_f_02.h"

void func_01F6D680_building_f_02(void) {
    switch (func_00170810()) {                              
        case 0x7A:
            if (!(((u32)D_1D3166C >> 1) & 1)) {
                func_0016CA40(7);
                D_1D31710 |= 0x200;
            } else {
                D_1D31710 &= ~0x200;
            }
        break;
        case 0x7C:
            if ((func_00199820() & 0xFF) && !(((u32)D_1D31668 >> 0x1E) & 1)) {
                func_0016CA40(4);
                D_1D31710 |= 0x1000;
            } else {
                D_1D31710 &= ~0x1000;
            }
        break;
        case 0x7D:
            if (!(D_1D3166C & 1)) {
                func_0016CA40(3);
                D_1D31710 |= 0x2000;
            } else {
                D_1D31710 &= ~0x2000;
            }
        break;
    }
}

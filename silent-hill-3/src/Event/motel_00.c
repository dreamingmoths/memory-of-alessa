#include "motel_00.h"

int func_01F6D680_motel_00(void) {
    int temp_s0;

    temp_s0 = func_0016C540(&D_01F6DF60_motel_00, &D_01F6DFC0_motel_00);
    func_0016CB30(5);

    switch(D_01F6E100_motel_00) {
        case 0:
        func_00190A20(2);
        func_00316C50(0);
        func_001C2290(2, 0.0f);
        D_01F6E100_motel_00 += 1;
    }

    if (temp_s0 != 0) {
        D_1D316FC |= 0x800;
        func_001C2290(5, 0.8f);
        func_00190A20(0);
        D_01F6E100_motel_00 = 0;
    }
    return temp_s0;
}

int func_01F6D750_motel_00(void) {
    int var_s0;

    var_s0 = 0;
    switch (D_01F6E100_motel_00) {                  
    case 0:
        func_001C2290(2, 0.0f);
        D_1D316AC |= 0x20000000;
        D_01F6E100_motel_00 += 1;

    case 1:
        var_s0 = func_0016C540(&D_01F6DFE0_motel_00, &D_01F6E040_motel_00);
        if (func_001646F0() == 2) {
            func_0019A940();
            D_01F6E100_motel_00 += 1;
        }
        break;
    case 2:
        if (func_0013D080(0, 0, 1, 4) != 0) {
            D_01F6E100_motel_00 = 4;
            func_0015E780(5);
            func_00164210();
        } else {
            func_00164750(7);
            if (func_0019A9B0(31.489f - (7.0f * shGetDT())) != 0) {
                D_01F6E100_motel_00 += 1;
            }
        }
        break;
    case 3:
        var_s0 = func_0016C540(&D_01F6DFE0_motel_00, &D_01F6E040_motel_00);
        if (var_s0 != 0) {
            D_01F6E100_motel_00 = 0;
        }
        break;
    case 4:
        D_01F6E100_motel_00 = 0;
        var_s0 = 1;
        D_1D316AC &= 0xDFFFFFFF;
        break;
    }
    return var_s0;
}

void func_01F6D910_motel_00(void) {
    if (func_0016C540(&D_01F6E060_motel_00, &D_01F6E0C0_motel_00) != 0) {
        D_1D316AC &= 0xDFFFFFFF;
    } else {
        D_1D316AC |= 0x20000000;
    }
}

void func_01F6D980_motel_00(void) {
    D_01F6E108_motel_00 = 0;
    D_01F6E100_motel_00 = 0;
}

void func_01F6D9A0_motel_00(void) {
    float temp_f2;

    if (func_001643D0() == 0) {
        func_0016CA40(1);
    }
    if (!(((u32) D_1D31684 >> 3) & 1)) {
        func_0016CA40(4);
    } else {
        func_0016CA40(5);
    }
    temp_f2 = D_01F6E108_motel_00 + (45.0f * shGetDT());
    D_01F6E108_motel_00 = temp_f2;
    if (!(temp_f2 <= 180.0f)) {
        D_01F6E108_motel_00 = temp_f2 - 360.0f;
    }
    func_001C2A60(1, 0.017453292f * D_01F6E108_motel_00);
    func_0018A260(0x1F);
    func_0018A310(0x1F, 0, 1);
}

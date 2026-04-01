#include "car_00.h"

int func_01F6D680_car_00() {
    int data_0x01F6DBA0[4];
    int data_0x01F6DC80[4];
    float float_end;
    float float_value;
    int end;

    data_0x01F6DBA0 = D_01F6DBA0_car_00;
    data_0x01F6DC80 = D_01F6DC80_car_00;

    switch (state_01F6DCA0_car_00) {
    case CAR_00_INIT:
        D_01F6DC90_car_00 = &D_01F6DB98_car_00;
        func_001603E0(2, 2, 1);
        D_01F6DC98_car_00 = 0;

        state_01F6DCA0_car_00 += 1;
        D_1D316AC |= 0x20000000;
        func_00190A20(2);

    case CAR_00_PLAY:
        end = func_0016C540(&D_01F6DBB0_car_00, &D_01F6DC10_car_00); // plays cutscene?
        if (func_001646F0() == 2) {
            func_001DA020(1, &data_0x01F6DBA0, &data_0x01F6DC80);
        }
        float_end = func_001643C0();
        float_value = D_01F6DC90_car_00->fv[0];
        if (float_value > 0.0f && (float_value <= float_end)) {
            func_0013D250(0, D_01F6DC90_car_00->u32[1], 1.0f);
            D_01F6DC90_car_00++;
        }
        if (end == 0) {
            return 0;
        }
        if (func_001646C0() != 0) {
            func_0013D280(0);
            D_1D316AC &= 0xDFFFFFFF;
            func_00190A20(0);
            return 1;
        }
        state_01F6DCA0_car_00++;
        func_001C2290(2, 0);
        return 0;

    default:
        if (D_01F6DC98_car_00 == 0) {
            if (func_0013D080(0, 0, 1, 4) != 0) {
                func_0015E780(5);
                D_01F6DC98_car_00 = 1;
            }
        }
        if (func_00160520(2) == 0) {
            return 0;
        }
        D_1D316AC &= 0xDFFFFFFF;
        func_00190A20(0);
        func_0013D280(0);
        func_0016DCE0(0);
        return 1;
    }
}

int func_01F6D8E0_car_00() {
    state_01F6DCA0_car_00 = 0;
}

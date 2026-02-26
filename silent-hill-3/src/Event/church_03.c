#include "church_03.h"

int func_01F6D680_church_03(void) {
    int temp_s0;
    int temp_v0;

    switch(D_01F6DF80_church_03) {
        case 0:
        func_001C2290(2, 0);
        func_00316C50(0);
        D_1D316AC |= 0x20000000;
        D_01F6DF80_church_03 += 1;
    }
    
    temp_s0 = func_0012FD80(0x214, 0x1CD);
    temp_v0 = func_0016C540(&D_01F6DDB0_church_03, &D_01F6DE10_church_03);
    if (temp_v0 != 0) {
        D_1D316AC &= 0xDFFFFFFF;
        func_001C2290(5, 0.5f);
        D_01F6DF80_church_03 = 0;
        func_001602D0(0x276B, 3, 1, 1.0f);
        if (temp_s0 != 0) {
            func_001DC9E0(temp_s0, 1);
        }
    } else if (temp_s0 != 0) {
        func_001DC9E0(temp_s0, 0);
    }
    func_0016CAF0(1);
    return temp_v0;
}

int func_01F6D7B0_church_03(void) {
    float temp_f20;
    int temp_s0;
    int temp_s1;

    switch(D_01F6DF80_church_03) {
        case 0:
        D_1D316AC |= 0x20000000;
        func_001C2290(3, 0.5f);
        D_01F6DF88_church_03 = (D_01F6DF88_struct*) &D_01F6DE30_church_03;
        D_01F6DF80_church_03 += 1;
    }
    
    temp_s0 = func_0012FD80(0x214, 0x1CD);
    temp_s1 = func_0016C540(&D_01F6DE90_church_03, &D_01F6DEF0_church_03);
    temp_f20 = func_001643C0();

    if (!(D_01F6DF88_church_03->unk0 <= 0.0f) && (D_01F6DF88_church_03->unk0 <= temp_f20)) {
        func_0013D250(0, D_01F6DF88_church_03->unk4, 1.0f);
        D_01F6DF88_church_03++;
    }

    if (!(D_01F6DF88_church_03->unk0 <= 0.0f) && (D_01F6DF88_church_03->unk0 <= temp_f20)) {
        func_0013D250(0, D_01F6DF88_church_03->unk4, 1.0f);
        D_01F6DF88_church_03++;
    }
    if (temp_s1 != 0) {
        func_0013D280(0);
        D_01F6DF80_church_03 = 0;
        if (temp_s0 != 0) {
            func_001DC9E0(temp_s0, 1);
        }
    } else if (temp_s0 != 0) {
        func_001DC9E0(temp_s0, 0);
    }
    func_0016CAF0(2);
    return temp_s1;
}

void func_01F6D970_church_03(void) {
    D_01F6DF80_church_03 = 0;
}

void func_01F6D980_church_03(void) {
    if ((func_0022F150(5) != 0) && !(((u32) D_1D316AC >> 7) & 1)) {
        if (func_00199C70(8) != 0) {
            D_1D316AC |= 0x02000000;
        }
        D_1D316AC |= 0x80;
        func_001603E0(2, 2);
    }
    if (((u32) D_1D316AC >> 7) & 1) {
        func_0016CAF0(2);
        return;
    }
    func_0016CAF0(1);
}

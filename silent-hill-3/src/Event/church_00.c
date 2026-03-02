#include "church_00.h"

INCLUDE_ASM("asm/nonmatchings/Event/church_00", func_01F6D680_church_00);

INCLUDE_ASM("asm/nonmatchings/Event/church_00", func_01F6D9C0_church_00);

INCLUDE_ASM("asm/nonmatchings/Event/church_00", func_01F6DB00_church_00);

void func_01F6DB10_church_00(void) {
    func_01F6D9C0_church_00(1);
}

void func_01F6DB20_church_00(void) {
    func_01F6D9C0_church_00(2);
}

void func_01F6DB30_church_00(void) {
    func_01F6D9C0_church_00(3);
}

void func_01F6DB40_church_00(void) {
    func_01F6D9C0_church_00(4);
}

void func_01F6DB50_church_00(void) {
    func_01F6D9C0_church_00(5);
}

int func_01F6DB60_church_00(void)
{
    int s0 = 0;
    int var_1 = 1;

    switch (D_01F6E600_church_00) {
    case 0:
        func_00190A20(2);
        func_0019A940();
        func_01F6DCD0_church_00();
        D_01F6E600_church_00 = 1;
        break;

    case 1:
        if (func_0019A9B0(0.5f) != 0) {
            if (((u_int)D_1D316A4 >> 14) & 1) {
                D_01F6E600_church_00 = 3;
            } else {
                D_01F6E600_church_00 = 2;
            }
        }
        break;

    case 2:
        if (func_0016C1C0(0x43) != 0) {
            D_01F6E600_church_00 = 4;
        }
        break;

    case 3:
        if ((func_0013D080(0, 0, var_1, var_1) != 0) ||
            (func_0013D080(0, 0, var_1, 2)   != 0)) {
            D_01F6E600_church_00 = 4;
        }
        break;

    case 4:
        D_1D316A4 |= 0x4000;
        func_001C0EE0(0);
        func_00190A20(0);
        s0 = 1;
        D_01F6E600_church_00 = 0;
        break;
    }

    return s0;
}

void func_01F6DCD0_church_00(void) {
    func_001C0EB0((void*)func_01F6DCF0_church_00, 0x000F423F, 0);
}

INCLUDE_ASM("asm/nonmatchings/Event/church_00", func_01F6DCF0_church_00);

INCLUDE_ASM("asm/nonmatchings/Event/church_00", func_01F6DD40_church_00);

INCLUDE_ASM("asm/nonmatchings/Event/church_00", func_01F6DD90_church_00);

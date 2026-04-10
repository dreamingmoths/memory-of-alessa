#include "mall_f_01.h"

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6D680_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6D820_mall_f_01);

int func_01F6DA20_mall_f_01(void) {
    int temp_v0 = func_0016C540(&D_01F72890_mall_f_01, &D_01F728F0_mall_f_01);
    if (temp_v0 != 0) {
        func_001C2290(5, 0.5f);
    }
    return temp_v0;
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6DA70_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6DBD0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6DCC0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6DDB0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6DF00_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6DF90_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6DFE0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6E3F0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6E630_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6E6E0_mall_f_01);

u_short func_01F6E700_mall_f_01(void) {
    float sp18;
    float sp1C;

    func_0029F330(&sp18, &sp1C);
    return func_002A47C0(sp18, sp1C);
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6E730_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6E9E0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6EE40_mall_f_01);

void func_01F6F1C0_mall_f_01(void) {
    func_01F6EE40_mall_f_01(0);
}

void func_01F6F1D0_mall_f_01(void) {
    func_01F6EE40_mall_f_01(0x27);
}

void func_01F6F1E0_mall_f_01(void) {
    func_01F6EE40_mall_f_01(0x28);
}

void func_01F6F1F0_mall_f_01(void) {
    func_01F6EE40_mall_f_01(0x29);
}

void func_01F6F200_mall_f_01(void) {
    func_01F6EE40_mall_f_01(0x2A);
}

void func_01F6F210_mall_f_01(void) {
    func_01F6EE40_mall_f_01(0x2B);
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F220_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F2B0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F300_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F510_mall_f_01);

u_short func_01F6F5A0_mall_f_01(void) {
    float sp18;
    float sp1C;

    func_0029F330(&sp18, &sp1C);
    return func_002A47C0(sp18, sp1C);
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F5D0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F720_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F810_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6FB30_mall_f_01);

int func_01F6FCB0_mall_f_01(void) {
    Q sp10;

    sp10 = D_01F72AB0_mall_f_01;
    func_002A2E70(&sp10);
    D_1D3164C |= 0x04000000;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6FD00_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6FDA0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6FED0_mall_f_01);

void func_01F70070_mall_f_01(void) {
    if (!GET_BIT(D_1D31650, 0x12)) {
        func_01F70720_mall_f_01();
        D_1D31650 |= 0x40000;
    }

    switch (RoomName()) {
        case 12:
            D_01F72BC8_mall_f_01 = 0;
            D_1D31700 |= 8;
            break;
        case 17:
            D_01F72BB8_mall_f_01 = 0;
            break;
        case 16:
            break;
        case 15:
            D_1D31784 |= 0x2000;
            D_1D31700 |= 0x10;
            break;
        case 18:
            D_1D31700 |= 0x40;
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F70160_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F70720_mall_f_01);

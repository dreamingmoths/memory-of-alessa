#include "building_f_01.h"

INCLUDE_ASM("asm/nonmatchings/Event/building_f_01", func_01F6D680_building_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_f_01", func_01F6D7E0_building_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_f_01", func_01F6D940_building_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_f_01", func_01F6DA80_building_f_01);

void func_01F6DC50_building_f_01(unk_struct01F6DC50* arg0) {
    shQzero(arg0, 0xB4);
    arg0->unkAC = 0x80;
}

INCLUDE_ASM("asm/nonmatchings/Event/building_f_01", func_01F6DC80_building_f_01);

int func_01F6E010_building_f_01(void) {
    if (!GET_BIT(D_1D3166C, 3)) {
        func_0016CD00(&D_01F700B0_building_f_01);
        D_1D3166C |= 8;
        func_00190A20(2);
    }
    if (func_0016BED0(0xC7, 0x1E) == 0) {
        return 0;
    }
    D_1D3166C &= ~8;
    func_00190A20(0);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/building_f_01", func_01F6E0A0_building_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_f_01", func_01F6E130_building_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_f_01", func_01F6E230_building_f_01);

void func_01F6E2C0_building_f_01(unk_struct01F6E2C0* arg0) {
    func_01F6E230_building_f_01();
    if (arg0->unkB0 != 0) {
        func_01F6E130_building_f_01(arg0);
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/building_f_01", func_01F6E300_building_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_f_01", func_01F6E610_building_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_f_01", func_01F6E680_building_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_f_01", func_01F6E730_building_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_f_01", func_01F6E7F0_building_f_01);

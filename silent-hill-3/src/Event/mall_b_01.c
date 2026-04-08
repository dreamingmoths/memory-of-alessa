#include "mall_b_01.h"

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_01", func_01F6D680_mall_b_01);

void func_01F6D740_mall_b_01(void) {
    if (GET_BIT(D_1D31658, 0x19)) {
        func_0016D0E0(0x300F, D_01F72910_mall_b_01);
        REMOVE_FLAG(&D_1D31658, 25);
    }
}

int func_01F6D7A0_mall_b_01(void) {
    switch (D_01F72918_mall_b_01) {
        case 0:
            func_00190A20(2);
            func_001C2290(3, 0.5f);
            D_01F72918_mall_b_01++;
            /* fallthrough */
        case 1:
            if (!func_001C2580(2)) {
                return 0;
            }
            func_0016D500(2, 34, &D_01F72640_mall_b_01);
            D_01F72918_mall_b_01++; 
            break;
        default:
            func_00190A20(0);
            return 1;
    }
    return 0; 
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_01", func_01F6D860_mall_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_01", func_01F6DA50_mall_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_01", func_01F6DC10_mall_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_01", func_01F6DE60_mall_b_01);

int func_01F6DEE0_mall_b_01(void) {
    func_0012CFA0();
    if (func_0012D080() == 0) {
        func_00190A20(2);
    }
    func_0012CFC0();
    if (func_0016BED0(!GET_BIT(D_1D31654, 0x1E) ? 0x47 : 0x45, 0x28) == 0) {
        return 0;
    }
    func_00190A20(0);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_01", func_01F6DF60_mall_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_01", func_01F6E0F0_mall_b_01);

void func_01F6E180_mall_b_01(unk_struct01F6E180* arg0) {
    func_01F6E0F0_mall_b_01();
    if (arg0->unkB0 != 0) {
        func_01F6DF60_mall_b_01(arg0);
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_01", func_01F6E1C0_mall_b_01);

int func_01F6E500_mall_b_01(void) {
    D_1D31658 |= 0x10;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_01", func_01F6E520_mall_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_01", func_01F6E580_mall_b_01);

int func_01F6E8A0_mall_b_01(void) {
    unk_struct* temp_v0;

    if (func_00190A20(8) != 0) {
        temp_v0 = func_00190AC0();
        temp_v0->unk0 = 0x30;
        temp_v0->unk10 = -20000.0f;
        temp_v0->unk14 = 1600.0;
        temp_v0->unk18 = -20000.0f;
        temp_v0->unk4 = -(PI/2);
    }
    return 1;
}

int func_01F6E900_mall_b_01(void) {
    unk_struct* temp_v0;

    if (func_00190A20(8) != 0) {
        temp_v0 = func_00190AC0();
        temp_v0->unk0 = 3;
        temp_v0->unk10 = 63603.97f;
        temp_v0->unk14 = 505.2f;
        temp_v0->unk18 = 24132.64f;
        temp_v0->unk4 = 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_01", func_01F6E960_mall_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_01", func_01F6EB90_mall_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_01", func_01F6EEC0_mall_b_01);

#include "amusement_02.h"

INCLUDE_ASM("asm/nonmatchings/Event/amusement_02", func_01F6D680_amusement_02);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_02", func_01F6D7A0_amusement_02);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_02", func_01F6D8D0_amusement_02);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_02", func_01F6D9E0_amusement_02);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_02", func_01F6DAF0_amusement_02);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_02", func_01F6DC30_amusement_02);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_02", func_01F6DD80_amusement_02);

#ifdef NON_MATCHING
void func_01F6E050_amusement_02() {
    D_01F7AB58_amusement_02 = 1;

    switch (func_00170810()) {
        case 0xEA:
            SeCall(1.0f, 0.0f, 0x4A48);
            return;
        default:
            return;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/amusement_02", func_01F6E050_amusement_02);
#endif

INCLUDE_ASM("asm/nonmatchings/Event/amusement_02", func_01F6E0B0_amusement_02);



void func_01F6F500_amusement_02(s32 arg0) {
    D_01F7AB78_amusement_02 = arg0;
}

int func_01F6F510_amusement_02() {
    return D_01F7AB78_amusement_02;
}


void func_01F6F520_amusement_02(s32 arg0) {
    D_01F7AB50_amusement_02 = arg0;
}


s32 func_01F6F530_amusement_02(void) {
    return D_01F7AB50_amusement_02;
}


f32 func_01F6F540_amusement_02(void) {
    return D_01F76698_amusement_02;
}


s32 func_01F6F550_amusement_02(void) {
    return D_01F76690_amusement_02;
}

INCLUDE_ASM("asm/nonmatchings/Event/amusement_02", func_01F6F560_amusement_02);

void func_01F6F760_amusement_02(void) {
    func_01F6F560_amusement_02(0);
}

void func_01F6F770_amusement_02(void) {
    func_01F6F560_amusement_02(1);
}

void func_01F6F780_amusement_02(void) {
    func_01F6F560_amusement_02(2);
}

void func_01F6F790_amusement_02(void) {
    func_01F6F560_amusement_02(3);
}

void func_01F6F7A0_amusement_02(void) {
    func_01F6F560_amusement_02(4);
}

void func_01F6F7B0_amusement_02(void) {
    func_01F6F560_amusement_02(5);
}

void func_01F6F7C0_amusement_02(void) {
    func_01F6F560_amusement_02(6);
}

void func_01F6F7D0_amusement_02(void) {
    func_01F6F560_amusement_02(7);
}

void func_01F6F7E0_amusement_02(void) {
    func_01F6F560_amusement_02(8);
}

void func_01F6F7F0_amusement_02(void) {
    func_01F6F560_amusement_02(9);
}

void func_01F6F800_amusement_02(void) {
    func_01F6F560_amusement_02(10);
}

void func_01F6F810_amusement_02(void) {
    func_01F6F560_amusement_02(11);
}

INCLUDE_ASM("asm/nonmatchings/Event/amusement_02", func_01F6F820_amusement_02);

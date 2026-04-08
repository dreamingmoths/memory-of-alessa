#include "mall_b_00.h"

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_00", func_01F6D680_mall_b_00);

void func_01F6D900_mall_b_00(float arg0)
{
    double t = func_00124120(arg0);
    t = func_0012B398(t);
    t = func_001248A0(1.0f, t * 1.667f);
    func_00124CD8(t);
}

void func_01F6D960_mall_b_00(float arg0)
{
    func_00124CD8(
        func_0012AB58(
            func_00124120(1.0f / arg0)
        )
    );
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_00", func_01F6D9A0_mall_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_00", func_01F6DAE0_mall_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_00", func_01F6DBB0_mall_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_00", func_01F6E0E0_mall_b_00);

void func_01F6E3A0_mall_b_00(void) {
    shQzero(&D_01F71700_mall_b_00, 0x3C);
    shQzero(&D_01F716D0_mall_b_00, 0x30);
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_00", func_01F6E3E0_mall_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_00", func_01F6E8B0_mall_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_00", func_01F6EC30_mall_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_00", func_01F6ED90_mall_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_00", func_01F6EF00_mall_b_00);

int func_01F6F030_mall_b_00(void) {
    func_00190A20(2);
    if (func_0016C1C0(0x37) == 0) {
        return 0;
    }
    D_01F716A8_mall_b_00 = 1;
    func_00190A20(0);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_00", func_01F6F080_mall_b_00);

int func_01F6F230_mall_b_00(void) {
    D_01F71688_mall_b_00 = D_01F71688_mall_b_00 + ((PI * 0.4f) * shGetDT());
    if (D_01F71688_mall_b_00 < PI) {
        return 0;
    }
    D_01F71688_mall_b_00 = PI;
    return 1;
}

int func_01F6F2A0_mall_b_00(void) {
    unk_struct* temp_v0;

    if (func_00190A20(8) != 0) {
        temp_v0 = func_00190AC0();
        temp_v0->unk0 = 0x1E;
        temp_v0->unk10 = -100975.0;
        temp_v0->unk14 = -40.0f;
        temp_v0->unk18 = -20390.0;
        temp_v0->unk4 = 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_00", func_01F6F300_mall_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_00", func_01F6F3E0_mall_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_00", func_01F6F570_mall_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/mall_b_00", func_01F6F740_mall_b_00);

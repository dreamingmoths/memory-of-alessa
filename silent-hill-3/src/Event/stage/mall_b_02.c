#include "Event/stage/mall_b_02.h"

// bss?
extern /* static */ unk_01F6E890_mall_b_02_struct D_01F6E890_mall_b_02; 

INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_02", func_01F6D680_mall_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_02", func_01F6D820_mall_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_02", func_01F6D970_mall_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_02", func_01F6DA80_mall_b_02);

int func_01F6DBC0_mall_b_02(void) {
    unk_01F6E890_mall_b_02_struct* p = &D_01F6E890_mall_b_02;   
    switch (p->unk8) {
        case 0:
            func_001603E0(2, 1);
            func_001EC5C0(1);
            func_001EC610(0);
            func_001EC630(0);
            func_0012EA40();
            p->unk10[1] = 0.0f;
            p->unk10[2] = 9.0f;
            p->unk8++;
            /* fallthrough */
        
        case 1:
            p->unk10[1] += shGetDT();
            p->unk10[0] = (30.0f * p->unk10[1]) / 2.0f;
            if (p->unk10[0] > 30.0f) {
                p->unkC = 30;
            } else {                
                p->unkC = p->unk10[0];
            }                        
            func_001EC5E0(p->unkC);
            if (func_00190240()) {
                func_001EC5C0(0);
                D_1D316AC &= 0xDFFFFFFF;
                return 1;
            }
            if (p->unk10[1] < p->unk10[2]) {
                return 0;
            }
            func_001C2290(8, 3.0f);
            D_1D316AC |= 0x20000000;
            p->unk8++;
        
        default:
            func_001EC5E0(p->unkC);
            if (!func_001C2580(2)) {
                return 0;
            }
            D_1D31658 |= 0x20;
            func_001EC5C0(0);
            D_1D316AC &= 0xDFFFFFFF;
            func_0013D280(0);
            return 1;
    }
}

int func_01F6DDA0_mall_b_02(void) {
    return D_01F6E890_mall_b_02.unk4;
}

void func_01F6DDB0_mall_b_02(int arg0) {
    D_01F6E890_mall_b_02.unk4 = arg0;
}

void func_01F6DDC0_mall_b_02(void) {
    shQzero(&D_01F6E890_mall_b_02, sizeof(unk_01F6E890_mall_b_02_struct)); // 0x1C
    func_01F6DDB0_mall_b_02(1);
}

void func_01F6DDF0_mall_b_02(void) {
    if ((func_01F6DDA0_mall_b_02() == 2) && !(((D_1D31658 >> 0xE) & 1))) {
        D_1D31658 |= 0x4000;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_02", func_01F6DE40_mall_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_02", func_01F6DEE0_mall_b_02);

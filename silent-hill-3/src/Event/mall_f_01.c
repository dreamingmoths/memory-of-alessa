#include "common.h"
#include "mall_b_00.h"

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6D680_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6D820_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6DA20_mall_f_01);

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

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6E700_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6E730_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6E9E0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6EE40_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F1C0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F1D0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F1E0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F1F0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F200_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F210_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F220_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F2B0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F300_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F510_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F5A0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F5D0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F720_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F810_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6FB30_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6FCB0_mall_f_01);

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

#include "church_02.h"

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6D680_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6D7B0_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6DB40_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6DC10_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6DCE0_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6DE30_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6DF20_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6E400_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6E590_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6EA20_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6EFA0_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6F1F0_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6F810_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6F820_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6F8E0_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6F8F0_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6F900_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6F910_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6F920_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6F930_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6F940_church_02);

u_short func_01F6FDD0_church_02(void) {
    float sp18;
    float sp1C;

    func_0029F330(&sp18, &sp1C);
    return func_002A47C0(sp18, sp1C);
}

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6FE00_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6FE40_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6FE80_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6FED0_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F70000_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F70020_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F70050_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F700D0_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F708C0_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F70930_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F70950_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F709E0_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F70C50_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F70D60_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F711F0_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F71370_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F715C0_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F71710_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F71A20_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F71B40_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F71CB0_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F725C0_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F725E0_church_02);

void func_01F72720_church_02(void) {
    D_01F775C0_church_02 = 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F72730_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F72790_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F72890_church_02);

void func_01F729F0_church_02(void) {
    D_01F77590_church_02 = 0;
    D_01F77610_church_02 = 0;
    D_01F77598_church_02 = 0;
    D_01F77608_church_02 = -1;
    D_01F77600_church_02 = -1;
    func_01F72720_church_02();
    if (func_0016D5B0() != 0) {
        func_001C2290(2, 0.0f);
        return;
    }
    D_01F77580_church_02 = 0;
    switch (RoomName()) { //I will debug the rest another time
        case CHURCH_LIBRARY:
            if (GetExtraNewGame() == 1 && (GetRiddleLevel() & 0xFF) == 2) { //Royal Flush Riddle
                D_1D316A8 |= 0x800000;
            }
            break;
        case 0xFE:
            break;
        case 0xFF:
            break;
        case 0x100:
            break;
        case 0x101:
            break;
        case 0x102:
            break;
        case 0x103:
            D_1D316A8 |= 0x4000;
            break;
        case 0x104:
            D_1D316A8 &= ~0x20000;
            D_1D316A8 &= ~0x40000;
            break;
        case 0x108:
            D_01F775C8_church_02 = 0;
            break;
        case 0x109:
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F72B30_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F72F90_church_02);

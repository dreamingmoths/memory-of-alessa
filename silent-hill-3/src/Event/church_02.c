#include "church_02.h"

int func_01F6D680_church_02(void) {
    int ret;

    ret = 0;
    if (GET_FLAG(D_1D316A8, 0x11) && !GET_FLAG(D_1D316A8, 0x12)) {
        return 1;
    }
    switch (D_01F77580_church_02) {
        case 0:
            func_00190A20(2);
            func_001C2290(3, 0.5f);
            D_01F77580_church_02++;
        case 1:
            if (func_0016C540(&D_01F769C0_church_02, &D_01F76A20_church_02) != 0) {
                D_01F77580_church_02++;
            case 2:
                func_00190A20(0);
                func_001C2290(5, 0.5f);
                D_01F77580_church_02 = 0;
                ret = 1;
                D_1D31644[0] |= 0x10;
                D_1D317D0[0] |= 0x400000;
            }
            break;
    }
    return ret;
}

#ifdef NON_MATCHING
int func_01F6D7B0_church_02(void) {
    switch (D_01F77580_church_02) {
        case 0:
            D_1D316AC[0] |= 0x20000000;
            func_00190A20(2);
            SeCall(1.0f, 0.0f, 0x2B21);
            D_1D316A4[0] |= 0x02000000;
            ItemGet(0x4B);
            func_00317490(0x4B, 0.2f);
            D_01F77580_church_02++;
            /* fallthrough */
        case 1:
            if (func_0016C1C0(0xDE) == 0) {
                return 0;
            }
            func_0016C3C0();
            func_003174B0(0.2f);
            func_001C2290(4, 1.2f);
            D_01F77580_church_02++;
        case 2:
            if (func_001C2580(2) == 0) {
                return 0;
            }
            SeCall(0.5f, 0.0f, 0x4A38);
            func_0019A940();
            D_01F77580_church_02++;
        case 3:
            if (func_0019A9B0(1.2f) == 0) {
                return 0;
            }
            SeCall(0.5f, 0.0f, 0x4A39);
            D_01F77580_church_02++;
        case 4:
            if (func_0016C540(&D_01F76A40_church_02, &D_01F76AA0_church_02) == 0) {
                return 0;
            }
            func_0016C9C0();
            if (func_001646C0() != 0) {
                D_01F77580_church_02 += 2;
            } else {
                SeCall(0.5f, 0.0f, 0x4A38);
            }
            func_0019A940();
            D_01F77580_church_02++;
        case 5:
            if (func_0019A9B0(1.2f) == 0) {
                return 0;
            }
            SeCall(0.5f, 0.0f, 0x4A39);
            D_01F77580_church_02++;
            func_0019A940();
        case 6:
            if (func_0019A9B0(1.2f) == 0) {
                return 0;
            }
            D_01F77580_church_02++;
        case 7:
            SeCall(1.0f, 0.0f, 0x2B21);
            func_001C2290(5, 1.2f);
            D_1D316A4[0] |= 0x04000000;
            ItemGet(0x4C);
            func_00317490(0x4C, 0.2f);
            D_01F77580_church_02++;
        case 8:
            if (func_0016C1C0(0xDF) == 0) {
                return 0;
            }
            func_0016C3C0();
            func_003174B0(0.2f);
            D_1D316AC[0] &= ~0x20000000;
            func_00190A20(0);
        default:
            D_01F77580_church_02 = 0;
            return 1;
    }
}

#else
INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6D7B0_church_02); //SeCall memes
#endif

int func_01F6DB40_church_02(void) {
    switch (D_01F77580_church_02) {
        case 0:
            func_00190A20(2);
            func_0016CD00(&D_01F76AC0_church_02);
            D_01F77580_church_02++;
        case 1:
            if (func_0016C1C0(0x99) == 0) {
                return 0;
            }
            func_0016C3C0();
            D_01F77580_church_02++;
        case 2:
            if (func_0016BED0(0x12, 0x9A) == 0) {
                return 0;
            }
            func_00190A20(0);
        default:
            D_01F77580_church_02 = 0;
            return 1;
        }
}

int func_01F6DC10_church_02(void) {
    switch (D_01F77580_church_02) {
        case 0:
            func_00190A20(2);
            func_0016CD00(&D_01F76AC0_church_02);
            D_01F77580_church_02++;
        case 1:
            if (func_0016C1C0(0x9B) == 0) {
                return 0;
            }
            func_0016C3C0();
            D_01F77580_church_02++;
        case 2:
            if (func_0016BED0(0x13, 0x9C) == 0) {
                return 0;
            }
            func_00190A20(0);
        default:
            D_01F77580_church_02 = 0;
            return 1;
    }
}

int func_01F6DCE0_church_02(void) {
    switch (D_01F77580_church_02) {
        case 0:
            func_00190A20(2);
            func_0016CD00(&D_01F76AD0_church_02);
            D_01F77580_church_02++;
    
        case 1:
            if (!GET_FLAG(D_1D316F8, 0xA)) {
                if (func_0016C1C0(0x9D) == 0) {
                    return 0;
                }
                func_0016C3C0();
            }
            D_01F77580_church_02++;
        case 2:
            if (func_0016BED0(0x14, 0x9E) == 0) {
                return 0;
            }
            func_0012CFA0();
            func_0012CFE0(0);
            func_0012CFC0();
            D_01F77580_church_02++;
        case 3:
            if (!GET_FLAG(D_1D316F8, 0xA)) {
                if (func_0016C1C0(0xA0) == 0) {
                    return 0;
                }
            }
            func_00190A20(0);
        default:
            D_01F77580_church_02 = 0;
            return 1;
    }
}

int func_01F6DE30_church_02(void) {

    switch (D_01F77580_church_02) {
        case 0:
            func_00190A20(2);
            D_01F77580_church_02++;
    
        case 1:    
            if (!GET_FLAG(D_1D316F8, 0xA)) {
                D_01F77908_church_02 = 0xCB;
            } else {
                D_01F77908_church_02 = 0xCC;
            }                    
            D_01F77580_church_02++;
    
        case 2:
            if (func_0016BED0(0xD8, D_01F77908_church_02) == 0) {
                return 0;
            }
            D_1D316F8[0] |= 0x01000000;
            func_00190A20(0);
        
        default:
            D_01F77580_church_02 = 0;
            return 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6DF20_church_02); // matched but I need to remove the gotos

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6E400_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6E590_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6EA20_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6EFA0_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F6F1F0_church_02);

int func_01F6F810_church_02(void) {
    return 1;
}

int func_01F6F820_church_02(void) {
    int ret = 0;

    switch (D_01F77580_church_02) {
    case 0:
        func_001C2290(3, 0.5f);
        func_00190A20(2);
        D_01F77580_church_02++;
        /* fallthrough */
    case 1:
        ret = func_0016C540(&D_01F76E10_church_02, &D_01F76E70_church_02);
        break;
    }
    if (ret != 0) {
        D_01F77580_church_02 = 0;
        D_1D316AC[0] |= 0x20000000;
        func_00190A20(0);
        func_001C2290(2, 0.0f);
    }
    return ret;
}

void func_01F6F8E0_church_02(void) {
    D_01F77890_church_02 = 0x4A;
    func_01F6F940_church_02();
}

void func_01F6F8F0_church_02(void) {
    D_01F77890_church_02 = 0x4B;
    func_01F6F940_church_02();
}

void func_01F6F900_church_02(void) {
    D_01F77890_church_02 = 0x4D;
    func_01F6F940_church_02();
}

void func_01F6F910_church_02(void) {
    D_01F77890_church_02 = 0x50;
    func_01F6F940_church_02();
}

void func_01F6F920_church_02(void) {
    D_01F77890_church_02 = 0x51;
    func_01F6F940_church_02();
}

void func_01F6F930_church_02(void) {
    D_01F77890_church_02 = 0;
    func_01F6F940_church_02();
}

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

int func_01F70000_church_02(int arg0) {
    return D_01F77858_church_02[arg0][0];
}

int func_01F70020_church_02(void) {
    func_0016BD90(0, 0, 1.0f);
    return 1;
}

void func_01F70050_church_02(void) {
    if ((func_01F6FE40_church_02(0xE) != -1) || (func_01F6FE40_church_02(0xD) != -1)
        || (func_01F6FE40_church_02(0xC) != -1) || (func_01F6FE40_church_02(0xB) != -1)) {
        func_001DE5B0(&func_01F715C0_church_02, 0, 1);
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F700D0_church_02);

INCLUDE_ASM("asm/nonmatchings/Event/church_02", func_01F708C0_church_02);

int func_01F70930_church_02(int arg0) {
    return D_01D31938[arg0];
}

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
                D_1D316A8[0] |= 0x800000;
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
            D_1D316A8[0] |= 0x4000;
            break;
        case 0x104:
            D_1D316A8[0] &= ~0x20000;
            D_1D316A8[0] &= ~0x40000;
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

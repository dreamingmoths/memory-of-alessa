#include "hospital_f_02.h"

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_02", func_01F6D680_hospital_f_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_02", func_01F6D720_hospital_f_02);

int func_01F6D780_hospital_f_02(void) {
    switch (D_01F6FFA0_hospital_f_02) {
        case 0:
            func_001C2290(3, 0.5f);
            D_01F6FFA0_hospital_f_02 += 1;
        case 1:
            if (func_001C2580(2) == 0) {
                return 0;
            }
            D_1D31680 &= 0xFFBFFFFF;
            func_0016D0E0(0x3908, D_01F6FFC0_hospital_f_02);
            D_01F6FFA0_hospital_f_02 += 1;
        case 2:
            if (func_0016C540(&D_01F6FCD0_hospital_f_02, &D_01F6FD30_hospital_f_02) == 0) {
                D_1D31644 |= 0x40;
                return 0;
            }
            D_1D31644 &= ~0x40;
            D_01F6FFA0_hospital_f_02 += 1;
        default:
            func_001C2290(5, 0.5f);
            return 1;
    }
}

int func_01F6D8B0_hospital_f_02(void) {
    int ret;

    ret = 0;
    if (!((D_1D31684 >> 0x16) & 1)) {
        D_01F6FF98_hospital_f_02 = 1;
        func_0016C3C0();
        D_1D31684 |= 0x400000;
        func_00190A20(5);
    }
    switch (D_01F6FF98_hospital_f_02) { 
        case 1:
            if (func_00190C00() == 0) {
                return 0;
            }
            D_01F6FF98_hospital_f_02 = 2;
        case 2:
            if (func_0016BED0(0x32, 0x47) == 0) {
                return 0;
            }
            D_01F6FF98_hospital_f_02 = 3;
            break;
        case 3:
            func_00190A20(6);
            D_01F6FF98_hospital_f_02 = 4;
        case 4:
            if (func_00190C00() == 0) {
                return 0;
            }
            D_01F6FF98_hospital_f_02 = 5;
        default:
            D_1D31684 &= 0xFFBFFFFF;
            D_1D316F4 |= 0x200000;
            func_00190A20(0);
            ret = 1;
        }
    return ret;        
}

int func_01F6DA20_hospital_f_02(void) {
    func_0012CFA0();
    if (func_0012D080() == 0) {
        func_00190A20(2);
    }
    func_0012CFC0();
    if (func_0016BED0(0x33, 0x48) == 0) {
        return 0;
    }
    D_1D316F4 |= 0x400000;
    func_00190A20(0);
    return 1;
}

int func_01F6DAA0_hospital_f_02(void) {
    func_0012CFA0();
    if (func_0012D080() == 0) {
        func_00190A20(2);
    }
    func_0012CFC0();
    if (func_0016BED0(0x35, 0x49) == 0) {
        return 0;
    }
    D_1D316F4 |= 0x01000000;
    func_00190A20(0);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_02", func_01F6DB20_hospital_f_02);

void func_01F6DBB0_hospital_f_02(void) {
    return;
}

void func_01F6DBC0_hospital_f_02(void) {
    return;
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_02", func_01F6DBD0_hospital_f_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_02", func_01F6DC40_hospital_f_02);

int func_01F6DC60_hospital_f_02(void) {
    float sp18;
    float sp1C;

    func_0029F330(&sp18, &sp1C);
    return func_002A47C0(sp18, sp1C) & 0xFFFF;
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_02", func_01F6DC90_hospital_f_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_02", func_01F6DDE0_hospital_f_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_02", func_01F6DEC0_hospital_f_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_02", func_01F6E200_hospital_f_02);

int func_01F6E3A0_hospital_f_02(void) {
    int ret;

    ret = 0;
    if (!((D_1D31688 >> 4) & 1)) {
        D_01F6FF80_hospital_f_02 = 0;
        D_1D31688 |= 0x10;
        D_01F6FF88_hospital_f_02 = 0.0f;
        func_001C2290(3, 1.5f);
        func_0016C1A0();
        SeCall(1.0f, 0.0f, 0x4A59);
    }
    D_01F6FF88_hospital_f_02 += shGetDT();
    switch (D_01F6FF80_hospital_f_02) { 
        case 0:
            if (D_01F6FF88_hospital_f_02 < 0.5f) {
                return 0;
            }
            SeCall(1.0f, 0.0f, 0x4A58);
            D_01F6FF80_hospital_f_02 += 1;
        case 1:
            if (D_01F6FF88_hospital_f_02 < 1.5f) {
                return 0;
            }
            func_0016C1B0();
            D_01F6FF80_hospital_f_02 += 1;
            break;       
        default:
            ret = 1;
            D_1D31688 &= ~0x10;
            D_1D31724 |= 1;
            D_1D31684 |= 0x400;
            D_1D317BC |= 0x8000;
        }
    return ret;
}

int func_01F6E550_hospital_f_02(void) {
    if (!((D_1D31688 >> 0x13) & 1)) {
        func_00190A20(2);
        D_1D31688 |= 0x80000;
    }
    if (func_0016C1C0(!((D_1D31688 >> 0x10) & 1) ? 0x51 : 0x52) == 0) {
        return 0;
    }
    if (!((D_1D31688 >> 0x10) & 1)) {
        D_1D31688 |= 0x10000;
        D_1D316F8 |= 0x200000;
    }
    D_1D31688 &= 0xFFF7FFFF;
    func_00190A20(0);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_02", func_01F6E630_hospital_f_02); // need jumptable

void func_01F6E950_hospital_f_02(void) {
    D_01F6FF90_hospital_f_02 = 1;

    switch(RoomName()) {
        case 0xB4:
            if ((D_1D31680 >> 0x16) & 1) {
                func_01F6D680_hospital_f_02();
            }
        default:
            break;
    }
        
}

void func_01F6E9B0_hospital_f_02(void) {
    Q sp10;
    Q sp20;
    Q sp30;

    sp10 = D_01F6FE80_hospital_f_02;
    sp20 = D_01F6FE90_hospital_f_02;
    sp30 = D_01F6FEA0_hospital_f_02;
    if (func_0019B580(2) == 0) {
        func_001C7BC0(&sp20, &sp10, &sp30, 0x200);
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_02", func_01F6EA20_hospital_f_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_02", func_01F6ECC0_hospital_f_02); // need jumptable

void func_01F6EE10_hospital_f_02(void) {
    if (!((D_1D31684 >> 2) & 1)) {
        func_01F6ECC0_hospital_f_02();
        D_1D31684 |= 4;
    }
}

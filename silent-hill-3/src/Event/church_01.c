#include "church_01.h"

int func_01F6D680_church_01(void) {
    switch (D_01F70600_church_01) {
        case 0:
            func_00190A20(2);
            func_0016CD00(&D_01F70280_church_01);
            func_001C2290(3, 0.8f);
            D_01F70600_church_01 = 1;
            /* fallthrough */
        case 1:
            if (func_001C2580(2) == 0) {
                return 0;
            }
            D_01F70600_church_01 = 2;
            func_001C2290(5, 0.8f);
        case 2:
            if (func_0016BED0(0xCD, 0x49) == 0) {
                return 0;
            }
            D_01F70600_church_01 = 3;
            func_001C2290(5, 0.8f);
        case 3:
            func_00190A20(0);
        default:
            D_01F70600_church_01 = 0;
            return 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/church_01", func_01F6D790_church_01);

int func_01F6DA80_church_01(void) {
    switch (D_01F70600_church_01) {
        case 0:
            func_00190A20(2);
            func_001C2290(3, 0.8f);
            D_01F70600_church_01 = 1;
            /* fallthrough */
        case 1:
            if (func_001C2580(2) == 0) {
                return 0;
            }
            D_01F70600_church_01 = 2;
            func_001C2290(5, 0.8f);
        case 2:
            if (func_0016BED0(0x59, 0x44) == 0) {
                return 0;
            }
            D_01F70600_church_01 = 3;
            func_001C2290(5, 0.8f);
        case 3:
            if (func_001C2580(4) == 0) {
                return 0;
            }
            func_00190A20(0);
        default:
            D_01F70600_church_01 = 0;
            return 1;
    }
}

int func_01F6DBA0_church_01(void) {
    switch (D_01F70600_church_01) {
        case 0:
            func_00190A20(2);
            func_001C2290(3, 0.8f);
            D_01F70600_church_01 = 1;
            /* fallthrough */
        case 1:
            if (func_001C2580(2) == 0) {
                return 0;
            }
            D_01F70600_church_01 = 2;
            func_001C2290(5, 0.8f);
        case 2:
            if (func_0016BED0(0x5B, 0x46) == 0) {
                return 0;
            }
            D_01F70600_church_01 = 3;
            func_001C2290(5, 0.8f);
        case 3:
            if (func_001C2580(4) == 0) {
                return 0;
            }
            func_00190A20(0);
        default:
            D_01F70600_church_01 = 0;
            return 1;
    }
}

int func_01F6DCC0_church_01(void) {
    switch (D_01F70600_church_01) {
        case 0:
            func_00190A20(2);
            func_001C2290(3, 0.8f);
            D_01F70600_church_01 = 1;
            /* fallthrough */
        case 1:
            if (func_001C2580(2) == 0) {
                return 0;
            }
            D_01F70600_church_01 = 2;
            func_001C2290(5, 0.8f);
        case 2:
            if (func_0016BED0(0x5A, 0x47) == 0) {
                return 0;
            }
            D_01F70600_church_01 = 3;
            func_001C2290(5, 0.8f);
        case 3:
            if (func_001C2580(4) == 0) {
                return 0;
            }
            func_00190A20(0);
        default:
            D_01F70600_church_01 = 0;
            return 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/church_01", func_01F6DDE0_church_01);

int func_01F6DF40_church_01(void) {
    switch (D_01F70600_church_01) {
        case 0:
            func_00190A20(2);
            func_0016CD00(&D_01F703F0_church_01);
            D_01F70600_church_01++;
            /* fallthrough */
        case 1:
            if (!GET_FLAG(D_1D316A8, 0x15)) {
                if (func_0016C1C0(0x5F) == 0) {
                    return 0;
                }
                func_0016C3C0();
            }
            D_01F70600_church_01++;
        case 2:
            if (func_0016BED0(0x1C, 0x5E) == 0) {
                return 0;
            }
            func_00190A20(0);
            D_1D316A8[0] |= 0x200000;
        default:
            D_01F70600_church_01 = 0;
            return 1;
    }
}

int func_01F6E040_church_01(void) {
    switch (D_01F70600_church_01) {
        case 0:
            func_00190A20(2);
            func_0016CD00(&D_01F70400_church_01);
            D_01F70600_church_01++;
            /* fallthrough */
        case 1:
            if (!GET_FLAG(D_1D316A8, 0x16)) {
                if (func_0016C1C0(0x61) == 0) {
                    return 0;
                }
                func_0016C3C0();
            }
            D_01F70600_church_01++;          
        case 2:
            if (func_0016BED0(0x1B, 0x60) == 0) {
                return 0;
            }
            func_00190A20(0);
            D_1D316A8[0] |= 0x400000;
        default:
            D_01F70600_church_01 = 0;
            return 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/church_01", func_01F6E140_church_01);

INCLUDE_ASM("asm/nonmatchings/Event/church_01", func_01F6E1A0_church_01);

int func_01F6E3D0_church_01(void) {
    switch (D_01F70600_church_01) {
        case 0:
            func_00190A20(2);
            D_01F70600_church_01++;
            /* fallthrough */
        case 1:
            if (func_0016BED0(0x15, 0x53) == 0) {
                return 0;
            }
            func_00190A20(0);
        default:
            D_01F70600_church_01 = 0;
            return 1;
        }
}

int func_01F6E460_church_01(void) {
    switch (D_01F70600_church_01) {
        case 0:
            func_00190A20(2);
            func_0016CD00(&D_01F70430_church_01);
            D_01F70600_church_01++;
            if (GET_FLAG(D_1D316A8, 5)) {
                D_01F70600_church_01++;
                return 0;
            }
        case 1:
            if (func_0016C1C0(0x5C) == 0) {
                return 0;
            }
            func_0016C3C0();
            D_01F70600_church_01++;
        case 2:
            if (func_0016BED0(1, 0x5D) == 0) {
                return 0;
            }
            func_0016C3C0();
            func_00190A20(0);
        default:
            D_01F70600_church_01 = 0;
            return 1;
    }
}

int func_01F6E570_church_01(void) {
    switch (D_01F70600_church_01) {
        case 0:
            func_00190A20(2);
            D_01F70600_church_01++;
            /* fallthrough */
        case 1:
            if (func_0016BED0(0x16, 0x4E) == 0) {
                return 0;
            }
            func_00190A20(0);
        default:
            D_01F70600_church_01 = 0;
            return 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/church_01", func_01F6E600_church_01);

INCLUDE_ASM("asm/nonmatchings/Event/church_01", func_01F6E910_church_01);

INCLUDE_ASM("asm/nonmatchings/Event/church_01", func_01F6E920_church_01);

INCLUDE_ASM("asm/nonmatchings/Event/church_01", func_01F6E980_church_01);

INCLUDE_ASM("asm/nonmatchings/Event/church_01", func_01F6EA80_church_01);

INCLUDE_ASM("asm/nonmatchings/Event/church_01", func_01F6EBF0_church_01);

INCLUDE_ASM("asm/nonmatchings/Event/church_01", func_01F6ECD0_church_01);

INCLUDE_ASM("asm/nonmatchings/Event/church_01", func_01F6EEB0_church_01);

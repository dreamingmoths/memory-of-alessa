#include "hospital_turning_00.h"

INCLUDE_ASM("asm/nonmatchings/Event/hospital_turning_00", func_01F6D680_hospital_turning_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_turning_00", func_01F6D9F0_hospital_turning_00);

int func_01F6DB90_hospital_turning_00(void) {

    switch (D_01F715C0_hospital_turning_00) {
        
        case 0:
            func_00190A20(2);
            D_01F715C0_hospital_turning_00 = 1;
        
        case 1:
            if (func_0016C1C0(0x3D) == 0) return 0;
            func_001C2290(0xB, 0.5f);
            func_0013D280(0);
            D_01F715C0_hospital_turning_00 = 2;
            break;
        
        case 2:
            if (!func_001C2580(2)) return 0;
            D_01F715C0_hospital_turning_00 = 3;
            
        case 3:
            func_0016D500(3, 0x39, &D_01F70850_hospital_turning_00);
            D_1D3168C |= 0x40;
            D_01F715C0_hospital_turning_00 = 4;
            break;
        
        case 4:
            func_001C2290(5, 0.5f);
            D_01F715C0_hospital_turning_00 = 5;

        case 5:
            if (func_001C2580(4) == 0) return 0;
            D_01F715C0_hospital_turning_00 = 6;

        case 6:
            if (func_0016C1C0(0x3E) == 0) return 0;
            D_01F715C0_hospital_turning_00 = 7;

        default:
            func_00190A20(0);
            return 1;
        
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_turning_00", func_01F6DD00_hospital_turning_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_turning_00", func_01F6DE50_hospital_turning_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_turning_00", func_01F6E230_hospital_turning_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_turning_00", func_01F6E270_hospital_turning_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_turning_00", func_01F6E300_hospital_turning_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_turning_00", func_01F6E470_hospital_turning_00);

void func_01F6E540_hospital_turning_00(void) {
    float temp_f0;

    if (((D_1D3168C >> 8) & 1) && (func_001E2050() == 0)) {
        switch (func_001E2070()) {
            case 0:
                break;
            default:
                return;
        }
        temp_f0 = D_01F713B0_hospital_turning_00 - shGetDT();
        D_01F713B0_hospital_turning_00 = temp_f0;
        if (temp_f0 <= 0.0f) {
            D_1D3168C &= ~0x100;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_turning_00", func_01F6E5E0_hospital_turning_00);

void func_01F6E720_hospital_turning_00(void) {

    int room;
    room = RoomName();
    D_01F70F80_hospital_turning_00 = 1;
    switch (room) {
        case 0xBD:
            func_00332D10(1);
            func_003027E0();
            break;
    }

}

void func_01F6E770_hospital_turning_00(void) {

    if (D_01F70F80_hospital_turning_00 == 0) {
        func_01F6E720_hospital_turning_00();
    }

    switch (RoomName()) {
        
        case 0xBD:
            if ((func_001646F0() == 0) && !(D_01F713A8_hospital_turning_00 <= 0.0f)) {
                D_01F713A8_hospital_turning_00 -= shGetDT();
            }
            func_01F6E300_hospital_turning_00();
            func_01F6E540_hospital_turning_00();
            if (func_001643D0() == 0x2E) {
                func_0016CA40(1);
            } else {
                func_00189F00(0xFF);
                func_00189FA0(0xFF, 1);
                func_00189FA0(0xFF, 2);
                func_00189FA0(0xFF, 3);
                func_00189FA0(0xFF, 4);
                func_00189FA0(0xFF, 5);
                func_00189FA0(0xFF, 6);
                func_00189FA0(0xFF, 7);
                func_00189FA0(0xFF, 8);
                func_00189FA0(0xFF, 9);
                func_00189FA0(0xFF, 0xA);
                func_00189FA0(0xFF, 0xB);
                func_00189FA0(0xFF, 0xC);
                func_00189FA0(0xFF, 0xE);
                func_00189FA0(0xFF, 0xD);
                func_00189FA0(0xFF, 0xF);
                func_00189FA0(0xFF, 0x10);
                func_00189FA0(0xFF, 0x11);
            }
            if (((D_1D31648 >> 0x10) & 1) && !((D_1D31648 >> 0x11) & 1)) {
                func_01F6EB90_hospital_turning_00(150.0f);
                func_01F6EBB0_hospital_turning_00(1.0f);
                func_003027E0();
                D_1D31648 |= 0x20000;
            }
            func_01F6EC60_hospital_turning_00();
            func_00332D20();
            func_00302870(0, 0);
            if (func_00190240() == 0) {
                if (((D_1D31690 >> 0x11) & 1) && !((D_1D3168C >> 9) & 1)) {
                    D_01F713A0_hospital_turning_00 += shGetDT();
                    if (!(D_01F713A0_hospital_turning_00 < 0.3f)) {
                        func_0013D280(0);
                        func_001603E0(2, 2);
                        D_1D3168C |= 0x200;
                        break;
                    }
                } else if ((func_0022F150(3) != 0) && !((D_1D31690 >> 0x11) & 1)) {
                    D_01F713A0_hospital_turning_00 = 0.0f;
                    D_1D31690 |= 0x20000;
                    break;
                }
            } else {
                break;
            }
            break;
        
        case 0xBC:
            if (!((D_1D3168C >> 6) & 1)) {
                func_0016CA40(1);
                func_0016CA40(6);
                clAddDynamicWall(&D_01F70420_hospital_turning_00);
                D_1D31728 |= 0x200;
            } else {
                func_0016CA40(2);
                D_1D31728 &= ~0x200;
            }
        
        default:
            func_01F6DE50_hospital_turning_00();
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_turning_00", func_01F6EAF0_hospital_turning_00);

void func_01F6EB70_hospital_turning_00(__int128* arg0) {
    vec_copy(arg0, &D_01F715F0_hospital_turning_00);
}

int func_01F6EB90_hospital_turning_00(float fparg0) {
    D_01F71608_hospital_turning_00 = fparg0;
}

float func_01F6EBA0_hospital_turning_00(void) {
    return D_01F71608_hospital_turning_00;
}

int func_01F6EBB0_hospital_turning_00(float fparg0) {
    D_01F7160C_hospital_turning_00 = fparg0;
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_turning_00", func_01F6EBC0_hospital_turning_00);

int func_01F6EC60_hospital_turning_00(void) {
    func_01F6EBC0_hospital_turning_00();
    func_0029AC80(func_01F6EBA0_hospital_turning_00());
}

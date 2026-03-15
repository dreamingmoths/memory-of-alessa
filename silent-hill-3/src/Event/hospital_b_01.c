#include "hospital_b_01.h"

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_01", func_01F6D680_hospital_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_01", func_01F6D740_hospital_b_01);

int func_01F6D7A0_hospital_b_01(void) {
    switch (D_01F6EBA8_hospital_b_01) {
        case 0:
            func_001C2290(3, 0.5f);
            D_01F6EBA0_hospital_b_01 = 1.0f;
            D_01F6EBA8_hospital_b_01 += 1;
    
        case 1:
            if (func_001C2580(2) == 0) {
                return 0;
            }
            D_1D31698 &= ~0x40;
            func_0016D0E0(0x3A98, D_01F6EBC0_hospital_b_01);
            D_01F6EBA8_hospital_b_01 += 1;
        
        case 2:
            if (func_0016C540(&D_01F6EAF0_hospital_b_01, &D_01F6EB50_hospital_b_01) == 0) {
                D_1D31648 |= 2;
                if (!(func_001643C0() <= 245.0f)) {
                    if (!(D_01F6EBA0_hospital_b_01 < 1.0f)) {
                        D_01F6EBA0_hospital_b_01 = 1.0f;
                    } else {
                        D_01F6EBA0_hospital_b_01 += shGetDT();
                    }
                    func_002395A0(D_01F6EBA0_hospital_b_01);
                } else {
                    func_002395A0(0.0f);
                }
                return 0;
            }
            D_1D31648 &= ~2;
            func_0016E400(0x22, 1);
            D_01F6EBA8_hospital_b_01 += 1;
        
        default:
            func_001C2290(5, 0.5f);
            return 1;
    }
}

void func_01F6D970_hospital_b_01(void) {
    func_001433A0(shCharacterGetSubCharacter(0x101C, 0x146), 0x2728, 0);
    D_1D31698 |= 0x200;
    SeCall(1.0f, 0.0f, 0x3A99);
}

int func_01F6D9D0_hospital_b_01(void) {
    int ret;

    ret = 0;
    if (!((D_1D31698 >> 4) & 1)) {
        D_01F6EB80_hospital_b_01 = 0;
        D_1D31698 |= 0x10;
        D_01F6EB88_hospital_b_01 = 0.0f;
        func_001C2290(3, 1.5f);
        func_0016C1A0();
        SeCall(1.0f, 0.0f, 0x4A59);
    }
    D_01F6EB88_hospital_b_01 += shGetDT();
    switch (D_01F6EB80_hospital_b_01) {
        case 0:
            if (D_01F6EB88_hospital_b_01 < 0.5f) {
                return 0;
            }
            SeCall(1.0f, 0.0f, 0x4A58);
            D_01F6EB80_hospital_b_01 += 1;
        case 1:
            if (D_01F6EB88_hospital_b_01 < 1.5f) {
                return 0;
            }
            func_0016C1B0();
            D_01F6EB80_hospital_b_01 += 1;  
            break;
        default:
            ret = 1;
            D_1D31698 &= ~0x10;                        
            D_1D3172C |= 0x800;
            D_1D31694 |= 0x40000000;
            D_1D317C8 |= 0x10;
    }
    return ret;
}

void func_01F6DB80_hospital_b_01(void) {

    D_01F6EB90_hospital_b_01 = 0;
    switch (RoomName()) { 
        case 0xC5:
            if ((D_1D31698 & 1) && !((D_1D31698 >> 1) & 1)) {
                D_1D31698 |= 2;
                break;
            }
            break;
        case 0xC6:
            D_01F6EBA8_hospital_b_01 = 0;
            if (!((D_1D31694 >> 0x13) & 1)) {
                D_1D31694 |= 0x80000;
            }
            break;
        case 0xC7:
            D_1D3172C |= 0x2000;
            if (!((D_1D31694 >> 0x13) & 1)) {
                D_1D31694 |= 0x80000;
            }
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_01", func_01F6DC60_hospital_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_01", func_01F6DDC0_hospital_b_01);

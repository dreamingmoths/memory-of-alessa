#include "hospital_b_01.h"

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_01", func_01F6D680_hospital_b_01);

void func_01F6D740_hospital_b_01(void) {
    if (GET_BIT(D_1D31698, 6)) {                
        func_0016D170(0x3A98, &D_01F6EBB0_hospital_b_01, 0, 0, 1.0f, 5000.0f, D_01F6EBC0_hospital_b_01);
    }
}

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
    if (!GET_BIT(D_1D31698, 4)) {
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
            D_1D317C0[2] |= 0x10;
    }
    return ret;
}

void func_01F6DB80_hospital_b_01(void) {

    D_01F6EB90_hospital_b_01 = 0;
    switch (RoomName()) { 
        case 0xC5:
            if (GET_BIT(D_1D31698, 0) && !GET_BIT(D_1D31698, 1)) {
                D_1D31698 |= 2;
                break;
            }
            break;
        case 0xC6:
            D_01F6EBA8_hospital_b_01 = 0;
            if (!GET_BIT(D_1D31694, 0x13)) {
                D_1D31694 |= 0x80000;
            }
            break;
        case 0xC7:
            D_1D3172C |= 0x2000;
            if (!GET_BIT(D_1D31694, 0x13)) {
                D_1D31694 |= 0x80000;
            }
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_01", func_01F6DC60_hospital_b_01);

void func_01F6DDC0_hospital_b_01(void) {
    Q *sp20[4];
    Q sp30;
    sceVu0FMATRIX sp40;
    Q *sp80[4];
    Q sp90;
    sceVu0FMATRIX spA0;
    SubCharacter *temp_s0;

    if (!D_01F6EB90_hospital_b_01) {
        func_01F6DC60_hospital_b_01();
    }

    switch (RoomName()) {
    case 0xC6:
        func_01F6D740_hospital_b_01();
        if (GET_BIT(D_1D31648, 1)) {
            break;
        }
        if (!GET_BIT(D_1D31648, 0)) {
            func_0016CBD0(sp20, &sp30, 0x10);
            mat_copy(sp40, sp20[0]);
            func_001C2A80(1, sp40);
            D_1D3172C |= 0x1000;
        } else {
            func_0016CBD0(sp80, &sp90, 0x11);
            mat_copy(spA0, sp80[0]);
            func_001C2A80(1, spA0);
            clAddDynamicWall(&D_01F6E890_hospital_b_01);
            D_1D3172C &= ~0x1000;
        }
        func_0016CA40(3);
        func_0016CA40(4);
        func_0016CA40(5);
        func_0016CA40(6);
        func_0016CA40(7);
        func_0016CA40(8);
        func_0016CA40(9);
        func_0016CA40(0xA);
        func_0016CA40(2);
        func_0018A260(0xF2);
        func_0018A310(0xF2, 8, 1);
        break;
    case 0xC7:
        if (GET_BIT(D_1D31698, 8)) {
            if (!GET_BIT(D_1D31698, 9)) {
                func_01F6D970_hospital_b_01();
            }
        }
        temp_s0 = shCharacterGetSubCharacter(0x101C, 0x146);
        if (!GET_BIT(D_1D31698, 9) || (func_001DD9F0(temp_s0) == 0)) {
            clAddDynamicWall(&D_01F6E6B0_hospital_b_01);
        } else if (!GET_BIT(D_1D31698, 17)) {
            D_1D31698 |= 0x20000;
        }
        if (GET_BIT(D_1D31698, 9)) {
            // @hack?
            if (D_01F6EB98_hospital_b_01) {}
            func_0016D170(0x3A9A, &temp_s0->pos, 0, 0, 1.0f, 1500.0f, D_01F6EB98_hospital_b_01);
        }
        if (!GET_BIT(D_1D31694, 7)) {
            func_0016CA40(0xA);
            D_1D3172C |= 0x4000;
        } else {
            D_1D3172C &= ~0x4000;
        }
        break;
    }
}

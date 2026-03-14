#include "amusement_02.h"

int func_01F6D680_amusement_02(void) {
    int ret = 0;

    switch (D_01F76688_amusement_02) {
        case 0:
            func_00190A20(2);
            D_01F76688_amusement_02 = 1;
        case 1:
            if (func_0016C540(&D_01F761A0_amusement_02, &D_01F76200_amusement_02) == 0) {
                break;
            }
            D_01F76688_amusement_02 = 2;
        case 2:
            func_0019B4B0(7);
            if (func_00160520(2) != 0) {
                func_0019B540(7);
                func_001C2290(2, 0.0f);
                func_0016D500(6, 0, 0);
                D_1D316AC |= 0x04000000;
                func_00199830(1);
                D_1D316AC &= 0xDFFFFFFF;
                func_00190A20(0);
                D_01F76688_amusement_02 = 0;
                ret = 1;
            }
            break;
    }
    return ret;
}

int func_01F6D7A0_amusement_02(void) {
    int var_s0  = 0;

    switch (D_01F76688_amusement_02) {
        case 0:
            func_00190A20(2);
            D_01F76688_amusement_02 = 1;
        case 1:
            if (func_0016C540(&D_01F76220_amusement_02, &D_01F76280_amusement_02) == 0) {
                func_002FE570();
            } else {
                D_01F76688_amusement_02 = 2;
            case 2:
                func_0019B4B0(5);
                func_0019B4B0(7);

                if (func_00160520(2) != 0) {
                    func_0019B540(7);
                    func_001C2290(2, 0.0f);
                    func_0016D500(8, 0, 0);
                    D_1D316AC &= 0xDFFFFFFF;
                    D_1D316AC |= 0x04000000;
                    func_00199830(2);
                    func_00190A20(0);
                    var_s0 = 1;
                    D_01F76688_amusement_02 = 0;
                }
            }
            break;
    }

    return var_s0;
}

int func_01F6D8D0_amusement_02(void) {
    switch (D_01F76688_amusement_02) {
        case 0:
            func_00190A20(2);
            func_001C2290(3, 0.8f);
            func_0016C1A0();
            D_01F76688_amusement_02 = 1;
            /* fallthrough */
        case 1:
            if (func_001C2580(2) == 0) {
                return 0;
            }
            D_01F76688_amusement_02 = 2;
            func_001C2290(5, 0.8f);
        case 2:
            if (func_0016BED0(0x4C, 0x27) == 0) {
                return 0;
            }
            D_01F76688_amusement_02 = 3;
            func_001C2290(5, 0.8f);
        case 3:
            func_00190A20(0);
        default:
            D_01F76688_amusement_02 = 0;
            return 1;
    }
}

int func_01F6D9E0_amusement_02(void) {

    switch (D_01F76688_amusement_02) {              
        case 0:    
            if (!(((u_int) D_1D316A0 >> 0x19) & 1)) {
                D_01F7AB70_amusement_02 = 0x29;
            } else {
                D_01F7AB70_amusement_02 = 0x2A;
            }
            func_00190A20(5);
            D_01F76688_amusement_02 = 1;
                
        case 1:
            if (func_00190C00() == 0) {
                return 0;
            }
            D_01F76688_amusement_02 = 2;
            
        case 2:
            if (func_0016C1C0(D_01F7AB70_amusement_02) == 0) {
                return 0;
            }
            func_00190A20(6);
            D_01F76688_amusement_02 = 3;
            
        case 3:
            if (func_00190C00() == 0) {
                return 0;
            }
            func_00190A20(0);
            D_01F76688_amusement_02 = 0;
            
        default:
            return 1;
    }
}

int func_01F6DAF0_amusement_02(void) {
    float temp_f0;
    float temp_f2;

    switch (D_01F7AB68_amusement_02) {
    case 0:
        func_001C2290(3, 0.5f);
        D_01F7AB68_amusement_02 += 1;
        func_00190A20(2);
        D_01F7AB60_amusement_02 = (D_01F7AB60_struct*) &D_01F762A0_amusement_02;

    case 1:
        if (func_001C2580(2) == 0) {
            return 0;
        }
        func_001603E0(2, 1);
        D_01F7AB68_amusement_02 += 1;
    default:
        if (func_0016C540(&D_01F762C0_amusement_02, &D_01F76320_amusement_02) == 0) {
            temp_f0 = func_001643C0();
            temp_f2 = D_01F7AB60_amusement_02->unk0;
            if (!(temp_f2 <= 0.0f) && (temp_f2 <= temp_f0)) {
                func_0013D250(0, D_01F7AB60_amusement_02->unk4, 1.0f);
                D_01F7AB60_amusement_02++;
            }
            return 0;
        }
        func_0013D280(0);
        func_00190A20(0);
        return 1;
    }
}

int func_01F6DC30_amusement_02(void) {
    SubCharacter* temp_v0_2;
    int ret;

    switch (D_01F76688_amusement_02) {
        case 0:
            func_00316C50(0);
            func_001C2290(2, 0.0f);
            func_00190A20(2);
            D_01F76688_amusement_02 += 1;
        } 
    
    ret = func_0016C540(&D_01F76340_amusement_02, &D_01F763A0_amusement_02);
    if (ret == 0) {
        SubCharacter* temp_s1;
        temp_v0_2 = shCharacterGetSubCharacter(MEMORY_OF_ALESSA_CHARA_ID, 0);
        if (temp_v0_2 != 0) {
            func_001D37E0(temp_v0_2, 3, 0, 0, 0);
        }
        temp_s1 = shCharacterGetSubCharacter(MEMORY_OF_ALESSA_CHARA_ID, 0x18D);
        func_001E22F0(MEMORY_OF_ALESSA_CHARA_ID, 0x18D, 0);
        func_001DC9E0(temp_s1, 0);
    } else {
        SubCharacter* temp_s1_2;
        temp_s1_2 = shCharacterGetSubCharacter(MEMORY_OF_ALESSA_CHARA_ID, 0x18D);
        func_001E22F0(MEMORY_OF_ALESSA_CHARA_ID, 0x18D, 1);
        func_001DC9E0(temp_s1_2, 1);
        D_01F76688_amusement_02 = 0;
        func_00190A20(0);
        func_001C2290(5, 0.5f);
        func_001602D0(0x276A, 3, 1, 1.0f);
    }
    return ret;
}


INCLUDE_ASM("asm/nonmatchings/Event/amusement_02", func_01F6DD80_amusement_02);

#ifdef NON_MATCHING
void func_01F6E050_amusement_02() {
    D_01F7AB58_amusement_02 = 1;

    switch (RoomName()) {
        case 0xEA:
            SeCall(1.0f, 0.0f, 0x4A48);
            return;
        default:
            return;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/amusement_02", func_01F6E050_amusement_02);
#endif

INCLUDE_ASM("asm/nonmatchings/Event/amusement_02", func_01F6E0B0_amusement_02);

void func_01F6F500_amusement_02(int arg0) {
    D_01F7AB78_amusement_02 = arg0;
}

int func_01F6F510_amusement_02() {
    return D_01F7AB78_amusement_02;
}


void func_01F6F520_amusement_02(int arg0) {
    D_01F7AB50_amusement_02 = arg0;
}


int func_01F6F530_amusement_02(void) {
    return D_01F7AB50_amusement_02;
}


float func_01F6F540_amusement_02(void) {
    return D_01F76698_amusement_02;
}


int func_01F6F550_amusement_02(void) {
    return D_01F76690_amusement_02;
}

int func_01F6F560_amusement_02(int arg0) {
    int temp_v0;
    int var_s0;
    int var_s1;
    int var_s2;
    int var_v0;

    var_s0 = 0;

    if (!D_01F7AB30_amusement_02[0]) return 1;
    if (!D_01F76710_amusement_02) return 1;

    switch (D_01F76688_amusement_02) {
        case 0:
            func_00190A20(2);
            D_01F76688_amusement_02++;
            return 0;
    }

    switch (arg0) {
        case 4: {            
            var_s1 = 0;
            var_s2 = 0;
            for (; var_s1 < 12; var_s1++, var_s2 += 0x14) {
                SubCharacter *scp;
                if (var_s1 == 4) continue;
                scp = shCharacterGetSubCharacter(0x20C, D_01F763C0_amusement_02[var_s1].id);
                if (func_001E2110(scp))
                    var_s0++;
            }
            if (var_s0) {
                var_v0 = func_0016C1C0(0x2C);
            } else {
                var_v0 = func_0016C1C0(0x2B);
            }
            break;
        }
        default: {
            shCharacterGetSubCharacter(0x20C, D_01F763C0_amusement_02[arg0].id);
            temp_v0 = arg0 >> 5;
            if (!((D_01F7AB30_amusement_02[temp_v0] >> (arg0 & 0x1F)) & 1)) {
                var_v0 = func_0016C1C0(0x2F);
            } else if (!((D_1D316A0 >> 24) & 1) && (D_01F7AB38_amusement_02[temp_v0] >> (arg0 & 0x1F)) & 1) {
                D_1D316A0 |= 0x1000000;
                var_v0 = func_0016C1C0(0x2D);
            } else {
                var_v0 = func_0016C1C0(0x2E);
            }
            break;
        }
    }

    if (var_v0) {
        func_00190A20(0);
        D_01F76688_amusement_02 = 0;
    }
    return var_v0;
}

void func_01F6F760_amusement_02(void) {
    func_01F6F560_amusement_02(0);
}

void func_01F6F770_amusement_02(void) {
    func_01F6F560_amusement_02(1);
}

void func_01F6F780_amusement_02(void) {
    func_01F6F560_amusement_02(2);
}

void func_01F6F790_amusement_02(void) {
    func_01F6F560_amusement_02(3);
}

void func_01F6F7A0_amusement_02(void) {
    func_01F6F560_amusement_02(4);
}

void func_01F6F7B0_amusement_02(void) {
    func_01F6F560_amusement_02(5);
}

void func_01F6F7C0_amusement_02(void) {
    func_01F6F560_amusement_02(6);
}

void func_01F6F7D0_amusement_02(void) {
    func_01F6F560_amusement_02(7);
}

void func_01F6F7E0_amusement_02(void) {
    func_01F6F560_amusement_02(8);
}

void func_01F6F7F0_amusement_02(void) {
    func_01F6F560_amusement_02(9);
}

void func_01F6F800_amusement_02(void) {
    func_01F6F560_amusement_02(10);
}

void func_01F6F810_amusement_02(void) {
    func_01F6F560_amusement_02(11);
}

INCLUDE_ASM("asm/nonmatchings/Event/amusement_02", func_01F6F820_amusement_02);

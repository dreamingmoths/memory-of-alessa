#include "hospital_b_02.h"

int func_01F6D680_hospital_b_02(void) {
    unk_01F6D680_hospital_b_02_struct* temp_v0;

    if (func_00190A20(8) != 0) {
        temp_v0 = func_00190AC0();
        temp_v0->unk0 = 0x21;
        temp_v0->unk10 = 20000.0f;
        temp_v0->unk14 = 0;
        temp_v0->unk18 = -100131.25f;
        temp_v0->unk4 = 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6D6E0_hospital_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6D830_hospital_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6D980_hospital_b_02); // picture shit

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6DA10_hospital_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6DC40_hospital_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6DC80_hospital_b_02);

int func_01F6DCA0_hospital_b_02(void) {
    return func_0013D080(0, 0, 1, 0x80000) != 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6DCD0_hospital_b_02);

int func_01F6DD20_hospital_b_02(void) {
    if (func_0016BED0(0xD9, 0x23) == 0) {
        return 0;
    }
    D_1D316FC[0] |= 0x20;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6DD70_hospital_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6DFF0_hospital_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6E1C0_hospital_b_02); // picture shit

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6E250_hospital_b_02); // more picture shit

void func_01F6E490_hospital_b_02(int arg0) {
    func_01F6E1C0_hospital_b_02();
    func_01F6E250_hospital_b_02(arg0);
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6E4C0_hospital_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6E4E0_hospital_b_02);

int func_01F6E5E0_hospital_b_02(unk_01F6E700_hospital_b_02_struct* arg0) {
    int temp_s1;
    int temp_t0;
    u_int temp_a3;
    int temp_a3_2;
    int a1;

    func_001916F0();
    func_0029FA30();
    if (arg0->unk8AC == arg0->unk8A8) {
        SeCall(1.0f, 0.0f, 0x3AFF);
        return 2;
    }
    temp_s1 = func_01F6E4E0_hospital_b_02();
    if (func_0013D080(0, 0, 1, 2) != 0) {
        return 1;
    }
    if (func_0013D080(0, 0, 1, 1) != 0) {
        if (temp_s1 != 0) {
            temp_t0 = (4 - temp_s1) * 4;
            temp_a3_2 = arg0->unk8AC >> temp_t0;
            a1 = (temp_a3_2 & 0xF);
            a1++;
            a1 %= 10;
            a1 <<= temp_t0;
            arg0->unk8AC &= ~(0xF << temp_t0);
            arg0->unk8AC |= a1;
            arg0->unk8A4 = 0.2f;
            SeCall(1.0f, 0.0f, 0x3AFC);
        }
    }
    return 0;
}

void func_01F6E700_hospital_b_02(unk_01F6E700_hospital_b_02_struct *arg0) {
    u_int *temp;
    func_0029F9B0();
    shQzero(arg0, 0x8B0);
    temp = D_01D31640;
    arg0->unk8AC = D_1D318EC;
   
    if ((GetRiddleLevel() & 0xFF) >= 2) {
        arg0->unk8A8 = 0x9271;  // oven code if riddle is hard
        
    } else {
        arg0->unk8A8 = temp[0x2A8 / 4];
    }
    arg0->unk8A0 = 0;
}

int func_01F6E780_hospital_b_02(void) {
    float var_f12;
    float var_f12_2;
    int temp_v0_2;
    u_int var_v0;
    unk_01F6E700_hospital_b_02_struct* temp_s0;

    temp_s0 = func_00156410(9);
    if (!GET_FLAG(D_1D31694, 0xF)) {
        D_1D31694[0] |= 0x8000;
        func_01F6E700_hospital_b_02(temp_s0);
        D_1D31680[0] |= 0x20000;
        func_00190A20(2);
    }

    switch (temp_s0->unk8A0) {
        case 0:
            func_0016BBF0();
            func_0016C1A0();
            func_0016F550(0x37, 1);
            func_0016F550(0x36, 0);
            if (func_00151150(0, 1) != 0) {
                var_f12 = 0.8f;
            } else {
                var_f12 = 1.2f;
            }
            func_001C2290(3, var_f12);
            temp_s0->unk8A0 = 1U;
            /* fallthrough */
        case 1:
            if ((func_00151150(0, 1) != 0) && (func_001C2580(2) != 0)) {
                func_001C2290(5, 0.8f);
                temp_s0->unk8A0 = 2U;
            }
            break;
            
        case 2:
            func_01F6E4C0_hospital_b_02(temp_s0);
            if (func_001C2580(4) != 0) {
                temp_s0->unk8A0 = 3U;
            }
            break;
        case 3:
            temp_v0_2 = func_01F6E5E0_hospital_b_02(temp_s0);
            if (temp_v0_2  == 2) {
                temp_s0->unk8A0 = 6;
            } else if (temp_v0_2  == 1) {
                temp_s0->unk8A0 = 4;
            }
            func_01F6E4C0_hospital_b_02(temp_s0);
            break;
    
        case 4:
            func_0016BC00(1);
            func_01F6E4C0_hospital_b_02(temp_s0);
            if (func_00151150(0, 1) != 0) {
                var_f12_2 = 0.8f;
            } else {
                var_f12_2 = 1.2f;
            }
            func_001C2290(3, var_f12_2);
            if (func_001C2580(2) != 0) {
                temp_s0->unk8A0 = 5U;
            }
            break;
    
        case 6:
            func_01F6E4C0_hospital_b_02(temp_s0);
            func_0016BC00(1);
            if (func_0016C1C0(1) != 0) {
                temp_s0->unk8A0 = 4U;
                D_1D31694[0] |= 0x10000;
            }
            break;
    
        default:
            func_0016C1B0();
            func_001C2290(5, 0.8f);
            D_1D31694[0] &= 0xFFFF7FFF;
            D_1D318EC = temp_s0->unk8AC;
            D_1D31680[0] &= 0xFFFDFFFF;
            func_00190A20(0);
            return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6EA60_hospital_b_02); // picture shit

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6EAF0_hospital_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6EB40_hospital_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6ED00_hospital_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6ED50_hospital_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6ED70_hospital_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6EEB0_hospital_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6EFD0_hospital_b_02);

int func_01F6F780_hospital_b_02(void) {
    int ret;

    ret = 0;

    if (!GET_FLAG(D_1D31698, 0x4)) {
        D_01F74100_hospital_b_02 = 0;
        D_1D31698[0] |= 0x10;
        D_01F74108_hospital_b_02 = 0.0f;
        func_001C2290(3, 1.5f);
        func_0016C1A0();
        SeCall(1.0f, 0.0f, 0x4A59);
    }
    D_01F74108_hospital_b_02 += shGetDT();
    switch (D_01F74100_hospital_b_02) {
        case 0:
            if (D_01F74108_hospital_b_02 < 0.5f) {
                return 0;
            }
            SeCall(1.0f, 0.0f, 0x4A58);
            D_01F74100_hospital_b_02 += 1;
        case 1:
            if (D_01F74108_hospital_b_02 < 1.5f) {
                return 0;
            }
            func_0016C1B0();
            D_01F74100_hospital_b_02 += 1;
            break;        
        default:
            ret = 1;
            D_1D31698[0] &= ~0x10;
            D_1D31694[0] |= 0x80000000;
            D_1D3172C[0] |= 0x02000000;
            D_1D317C0[3] |= 4;

    }
    return ret;
}

int func_01F6F930_hospital_b_02(void) {
    int ret;

    ret = 0;
    if (!GET_FLAG(D_1D31698, 0x4)) {
        D_01F74110_hospital_b_02 = 0;
        D_1D31698[0] |= 0x10;
        D_01F74118_hospital_b_02 = 0.0f;
        func_001C2290(3, 1.5f);
        func_0016C1A0();
        SeCall(1.0f, 0.0f, 0x4A59);
    }
    D_01F74118_hospital_b_02 += shGetDT();
    switch (D_01F74110_hospital_b_02) {
        case 0:
            if (D_01F74118_hospital_b_02 < 0.5f) {
                return 0;
            }
            SeCall(1.0f, 0.0f, 0x4A58);
            D_01F74110_hospital_b_02 += 1;
        case 1:
            if (D_01F74118_hospital_b_02 < 1.5f) {
                return 0;
            }
            func_0016C1B0();
            D_01F74110_hospital_b_02 += 1;
            break;
            
        default:
            ret = 1;
            D_1D31698[0] &= ~0x10;
            D_1D31694[0] |= 0x10000000;
            D_1D3172C[0] |= 0x08000000;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6FAD0_hospital_b_02);

void func_01F6FBA0_hospital_b_02(void) {
    sceVu0FVECTOR sp20;
    float var_f0;
    SubCharacter* scp;

    scp = shCharacterGetSubCharacter(0x101F, 0x14E);
    func_0016D170(0x3B00, &scp->pos, 0, 0, 1.0f, 1000.0f, D_01F74140_hospital_b_02);
    if ((func_001DDAE0(scp) & 0xFFFF) < 0xF) {
        D_01F74148_hospital_b_02 = 0;
        return;
    }
    
    if (D_01F74148_hospital_b_02 == 0) {
        func_0018FE60((u_long128 *)&sp20);

        if((sp20[1] > -2514.0f)){
            var_f0 = sp20[1] - -2514.0f;
        }
        else{
            var_f0 = -2514.0f - sp20[1];
        }

        if (var_f0 <= 1000.0f) {
            SeCall((1000.0f - var_f0) / 1000.0f, -0.7853982f, 0x3B01);
            D_01F74148_hospital_b_02 = 1;
        }    
    }    
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6FCB0_hospital_b_02);

void func_01F6FEA0_hospital_b_02(void) {
    Q sp10;
    Q sp20;
    Q sp30;

    sp10 = D_01F73FC0_hospital_b_02;
    sp20 = D_01F73FD0_hospital_b_02;
    sp30 = D_01F73FE0_hospital_b_02;
    if (func_0019B580(2) == 0) {
        func_001C7BC0(&sp20, &sp10, &sp30, 0x200);
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F6FF10_hospital_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F700C0_hospital_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_02", func_01F705C0_hospital_b_02);

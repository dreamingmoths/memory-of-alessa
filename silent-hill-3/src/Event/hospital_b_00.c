#include "hospital_b_00.h"

#define GET_FLAG(x, i) (((x[i >> 5]) >> (i & 0x1F)) & 1)

int func_01F6D680_hospital_b_00(void) {
    int ret;

    ret = 0;
    if (!(GET_FLAG(D_1D31694, 3))){
        D_01F706F8_hospital_b_00 = 1;
        D_1D31694[0] |= 8;
        func_00190A20(5);
    }
    if (func_00168440() != 0) {
        fontClear();
        D_01F706F8_hospital_b_00 = 5;
    }
    switch (D_01F706F8_hospital_b_00) {
        case 1:
            if (func_00190C00() == 0) {
                return 0;
            }
            D_01F706F8_hospital_b_00 = 2;
        case 2:
            if (func_0016C1C0(!(GET_FLAG(D_1D31694, 4)) ? 0x21 : 0x22) == 0) {
                return 0;
            }
            if (!(GET_FLAG(D_1D31694, 4))) {
                D_1D31694[0] |= 0x10;
            }
            D_01F706F8_hospital_b_00 = 3;
            break;        
        case 3:
            func_00190A20(6);
            D_01F706F8_hospital_b_00 = 4;
        case 4:
            if (func_00190C00() == 0) {
                return 0;
            }
            D_01F706F8_hospital_b_00 = 5;
        default:
            D_1D31694[0] &= ~8;
            func_00190A20(0);
            ret = 1;
    
        }
        return ret;
}

void func_01F6D820_hospital_b_00(void) {
    int birthday_room_ammo_score;
    int birthday_room_drug_score;
    int action;

    if (GET_FLAG(D_1D31694, 5)) {
        return;
    }
 
    birthday_room_ammo_total = GetItemCount(0xF); // handgun ammo
    birthday_room_ammo_total += GetItemCount(0x10) * 2; // shotgun ammo 
    birthday_room_ammo_total += GetItemCount(0x11); // smg ammo 
    birthday_room_ammo_score = birthday_room_ammo_total;

    birthday_room_drug_total = GetItemCount(0x12) * 4; // health drink
    birthday_room_drug_total += GetItemCount(0x13) * 8; // first aid kit
    birthday_room_drug_total += GetItemCount(0x14) * 12; // ampoule
    birthday_room_drug_score = birthday_room_drug_total;

    action = GetActionLevel();

    if (!(birthday_room_ammo_score > birthday_room_drug_score)) {
        if (action >= 3) {
            birthday_room_ammo_score += 30;  // Add 30 points if playing on Hard
        }
        if (birthday_room_ammo_score <= 30) {
            birthday_shotgun_shells++; // Add flag to spawn 6 Shotgun Shells
        }
        if (birthday_room_ammo_score <= 60) {
            birthday_shotgun_shells++; // Add flag to spawn 6 Shotgun Shells
        }
        if (birthday_room_ammo_score <= 90) {
            birthday_submachine_gun_bullets++; // Add flag to spawn 32 Submachine Gun Bullets
        }
        if (birthday_room_ammo_score <= 120) {
            birthday_handgun_bullets++;  // Add flag to spawn 10 Handgun Bullets
        }
        birthday_handgun_bullets += 2; // Add flag to spawn 20 Handgun Bullets
    } else {
        if (action >= 3) {
            birthday_room_drug_score += 30;  // Add 30 points if playing on Hard
        }
        if (birthday_room_drug_score <= 30) {
            birthday_ampoules++; // Add flag to spawn 1 Ampoules
        }
        if (birthday_room_drug_score <= 60) {
            birthday_first_aid_kits++; // Add flag to spawn 1 First Aid Kit
        }
        if (birthday_room_drug_score <= 90) {
            birthday_health_drinks++; // Add flag to spawn 2 Health Drinks
        }
        if (birthday_room_drug_score <= 120) {
            birthday_first_aid_kits++; // Add flag to spawn 1 First Aid Kit
        }
        birthday_health_drinks += 2;  // Add flag to spawn 2 Health Drinks
    }

    D_1D31694[0] |= 0x20;
}

int func_01F6DA90_hospital_b_00(u_short* arg0) {
    int ret;

    ret = 0;
    switch (*arg0) {
        case 15:
            if ((birthday_handgun_bullets > D_01F706F0_hospital_b_00)) {
                D_01F706F0_hospital_b_00 += 1;
                ret = 1;
            }
            break;
        case 16:
            if (birthday_shotgun_shells > D_01F706E8_hospital_b_00) {
                D_01F706E8_hospital_b_00 += 1;
                ret = 1;
            }
            break;
    
        case 17:
            if (birthday_submachine_gun_bullets > D_01F706E0_hospital_b_00) {
                D_01F706E0_hospital_b_00 += 1;
                ret = 1;
            }
            break;
   
        case 18:
            if (birthday_health_drinks > D_01F706D8_hospital_b_00) {
                D_01F706D8_hospital_b_00 += 1;
                ret = 1;
            }
            break;
        case 19:
            if (birthday_first_aid_kits > D_01F706D0_hospital_b_00) {
                D_01F706D0_hospital_b_00 += 1;
                ret = 1;
            }

            break;
        case 20:
            if (birthday_ampoules > D_01F706C8_hospital_b_00) {
                D_01F706C8_hospital_b_00 += 1;
                ret = 1;
            }
            break;

    }
    return ret;
    
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6DBF0_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6DD80_hospital_b_00);

int func_01F6DE10_hospital_b_00(void) {
    int ret;

    ret = 0;
    if (!(GET_FLAG(D_1D31694, 2)))  {
        func_0016C3C0();
        D_1D31694[0] |= 4;
        func_00190A20(5);
        D_01F70628_hospital_b_00 = 0;
        D_01F70630_hospital_b_00 = 1;
    }
    if (func_00168440() != 0) {
        if (func_0016C190() != 0) {
            func_0016C1B0();
        }
        fontClear();
        D_01F70630_hospital_b_00 = 6;
    }
    switch (D_01F70630_hospital_b_00) { 

        case 1:
            if (func_00190C00() == 0) {
                return 0;
            }
            D_01F70630_hospital_b_00 = 2;
            
        case 2:
            if (func_0016BED0(0x3C, 0x26) == 0) {
                return 0;
            }
            if (!(GET_FLAG(D_1D31698, 22)))  {
                D_1D31698[0] |= 0x400000;
                D_01F70628_hospital_b_00 = 1;            
            }
            if (!(GET_FLAG(D_1D316F4, 26)))  {
                D_1D316F4[0] |= 0x04000000;
            }
            D_01F70630_hospital_b_00 = 3;
            break;
            
        case 3:
            func_00190A20(6);
            D_01F70630_hospital_b_00 = 4;
            
        case 4:
            if (func_00190C00() == 0) {
                return 0;
            }
            func_00190A20(2);
            if (D_01F70628_hospital_b_00 != 0) {
                func_0016C3C0();
                D_01F70630_hospital_b_00 = 5;
            } else {
                D_01F70630_hospital_b_00 = 6;
            }
            break;
            
        case 5:
            if (func_0016C1C0(0x27) == 0) {
                return 0;
            }
            D_01F70630_hospital_b_00 = 6;
            
        default:
            D_1D31694[0] &= ~4;
            func_00190A20(0);
            ret = 1;
    }

    return ret;
}

int func_01F6E060_hospital_b_00(void) {
    if (!GET_FLAG(D_1D31698, 7)) {
        func_00190A20(2);
        D_01F70620_hospital_b_00 = 0;
        D_1D31698[0] |= 0x80;
    }
    if (func_0016C1C0(0x19) == 0) {
        return 0;
    }
    if (!GET_FLAG(D_1D316F4, 27)) {
        D_1D316F4[0] |= 0x08000000;
    }
    D_1D31698[0] &= ~0x80;
    func_00190A20(0);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E110_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E230_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E290_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E360_hospital_b_00);

void func_01F6E4E0_hospital_b_00(void) {

    SubCharacter* scp;
    int var_s0;
    int* cur; 
    
    cur = &D_01F70528_hospital_b_00;
    var_s0 = 0;
    for (cur = &D_01F70528_hospital_b_00; *cur != 0; cur++) {
        scp = shCharacterGetSubCharacter(SLURPER_E_CHARA_ID, *cur);
        if (scp != NULL) {
            
            if(!func_001E2110(scp)) var_s0++;            
            if ((*cur != 0x140) && (GET_FLAG(D_1D31694, 11)) && (GetActionLevel() < 3) && (1 < var_s0)) {
            shCharacter_Manage_Delete(SLURPER_E_CHARA_ID, *cur);                
            }
        }
    }
}

void func_01F6E5B0_hospital_b_00(void) {
    SubCharacter* scp;
    int score;
    int action;
    int* cur;

    action = GetActionLevel();
    score = birthday_room_ammo_total + birthday_room_drug_total;

    for (cur = &D_01F70540_hospital_b_00; *cur != 0; cur++) {
        scp = shCharacterGetSubCharacter(NURSE_CHARA_ID, *cur);

        if (scp != NULL && !func_001E2110(scp)) {
            switch (*cur) {
                case 317:
                    if (score < 120) {
                        shCharacter_Manage_Delete(NURSE_CHARA_ID, *cur);
                    }
                    break;
                case 318:
                    if (score < 190) {
                        shCharacter_Manage_Delete(NURSE_CHARA_ID, *cur);
                    }
                    break;
                case 319:
                    if (score < 260) {
                        shCharacter_Manage_Delete(NURSE_CHARA_ID, *cur);
                    }
                    break;
            }
        }
    }
}

int func_01F6E6C0_hospital_b_00(void) {
    int ret;
    
    ret = 0;
    if (!GET_FLAG(D_1D31698, 4)) {
        D_01F70600_hospital_b_00 = 0;
        D_1D31698[0] |= 0x10;
        D_01F70608_hospital_b_00 = 0.0f;
        func_001C2290(3, 1.5f);
        func_0016C1A0();
        SeCall(1.0f, 0.0f, 0x4A59);
    }
    D_01F70608_hospital_b_00 += shGetDT();
    switch (D_01F70600_hospital_b_00) {    
        case 0:
            if (D_01F70608_hospital_b_00 < 0.5f) {
                return 0;
            }
            SeCall(1.0f, 0.0f, 0x4A58);
            D_01F70600_hospital_b_00 += 1;
        case 1:
            if (D_01F70608_hospital_b_00 < 1.5f) {
                return 0;
            }
            func_0016C1B0();
            D_01F70600_hospital_b_00 += 1;
            break;        
        default:
            ret = 1;
            D_1D31698[0] &= ~0x10;
            D_1D31728[0] |= 0x04000000;
            D_1D31694[0] |= 0x20000000;
            D_1D317C0[0] |= 0x01000000;
        }
    return ret;
}

void func_01F6E880_hospital_b_00(void) {

    D_01F70610_hospital_b_00 = 0;

    switch (RoomName()) {                             
        case 0xC0:
            D_1D31728[0] |= 0x40000000;
            D_1D31728[0] |= 0x80000000;
            break;
        
        case 0xC2:
            break;
            
        case 0xC1:
            D_1D31698[0] |= 0x400;
            D_1D3172C[0] |= 2;
            break;        
    
        case 0xC3:
            D_1D3172C[0] |= 0x20;
            func_01F6DBF0_hospital_b_00();
            break;
        
        case 0xC4:
            D_01F70618_hospital_b_00 = 0;
            D_1D3172C[0] |= 0x40;
            D_1D3172C[0] |= 0x80;
            break;
    }
}

void func_01F6E980_hospital_b_00(void) {

    D_01F70610_hospital_b_00 = 1;
    switch (RoomName()) {        
        case 0xC2:
            func_01F6E4E0_hospital_b_00();
            break;
        
        case 0xC3:
            if ((GET_FLAG(D_1D31694, 6))){
                D_1D31694[0] &= ~0x40;
            }
            func_01F6E5B0_hospital_b_00();
            break;
        }
}

void func_01F6EA00_hospital_b_00(void) {

    if (D_01F70610_hospital_b_00 == 0) {
        func_01F6E980_hospital_b_00();
    }
    switch (RoomName()) {                             
        case 0xBE:
            if ((GET_FLAG(D_1D31694, 20)) && !(GET_FLAG(D_1D31694, 21))) {
                func_01F6E360_hospital_b_00();
            }
            if (func_00190950() != 0) {
                clAddDynamicWall(&D_01F70350_hospital_b_00);
                break;
            }
            break;
        case 0xC2:
            if (GET_FLAG(D_1D31648, 0)) {
                func_0016CA40(5);
                D_1D3172C[0] |= 0x10;
                break;
            }
            D_1D3172C[0] &= ~0x10;
            break;
        case 0xC3:
            func_01F6DD80_hospital_b_00();
            break;
        case 0xC4:
            if (GET_FLAG(D_1D31644, 29)) {
                func_002FE380();
                break;
            }
            if (func_00190050() != 0) {
                D_1D31698[0] |= 0x100000;
            } else {
                D_1D31698[0] &= 0xFFEFFFFF;
            }
            if (!GET_FLAG(D_1D31644, 28)) {
                D_1D3172C[0] |= 0x100;
                if (func_0019B580(0x12) != 0) {
                    clAddDynamicFloor(&D_01F6FC20_hospital_b_00);
                    clAddDynamicFloor(&D_01F6FCC0_hospital_b_00);
                    func_0019F820();
                }
                func_0016CA40(1);
                clAddDynamicFloor(&D_01F6FC20_hospital_b_00);
                clAddDynamicFloor(&D_01F6FCC0_hospital_b_00);
                func_00189F00(0xDD);
                func_00189FA0(0xDD, 0x3B);
                func_00189FA0(0xDD, 0x41);
                func_00189FA0(0xDD, 0x40);
                func_00189FA0(0xDD, 0x3F);
                func_00189FA0(0xDD, 0x3E);
                func_00189FA0(0xDD, 0x3D);
                func_00189FA0(0xDD, 0x3C);
                func_00189FA0(0xDD, 0x3A);
                func_00189FA0(0xDD, 0x39);
                func_00189FA0(0xDD, 0x38);
                func_00189FA0(0xDD, 0x37);
                func_00189FA0(0xDD, 0x36);
                func_00189FA0(0xDD, 0x35);
                func_00189FA0(0xDD, 0x34);
                func_00189FA0(0xDD, 0x33);
            } else {
                if (func_00190950() != 0) {
                    clAddDynamicWall(&D_01F702B0_hospital_b_00);
                }
                D_1D3172C[0] &= ~0x100;
                func_0016CA40(2);
                clAddDynamicWall(&D_01F70030_hospital_b_00);
                clAddDynamicFloor(&D_01F6FEA0_hospital_b_00);
                func_00189F00(0xDD);
                func_00189FA0(0xDD, 0x2B);
                func_00189FA0(0xDD, 0x2C);
                func_00189FA0(0xDD, 0x2D);
                func_00189FA0(0xDD, 0x2E);
                func_00189FA0(0xDD, 0x2F);
                func_00189FA0(0xDD, 0x30);
                func_00189FA0(0xDD, 0x31);
                func_00189FA0(0xDD, 0x2A);
                func_00189FA0(0xDD, 0x22);
                func_00189FA0(0xDD, 0x23);
                func_00189FA0(0xDD, 0x24);
                func_00189FA0(0xDD, 0x25);
                func_00189FA0(0xDD, 0x26);
                func_00189FA0(0xDD, 0x27);
                func_00189FA0(0xDD, 0x28);
                func_00189FA0(0xDD, 0x29);
                func_002FE380();
            }
            func_0016CA40(3);
            func_0016CA40(4);
            break;
    }
}

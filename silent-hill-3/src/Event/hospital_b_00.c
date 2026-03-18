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

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6DE10_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E060_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E110_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E230_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E290_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E360_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E4E0_hospital_b_00);

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

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E6C0_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E880_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6E980_hospital_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_b_00", func_01F6EA00_hospital_b_00);

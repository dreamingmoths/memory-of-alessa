#include "Event/stage/mall_b_01.h"

#include "vec.h"

#include "Collision/cl_main.h"

#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"

#include "Font/font.h"

INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_01", func_01F6D680_mall_b_01);

void func_01F6D740_mall_b_01(void) {
    if (GET_BIT(D_1D31658, 0x19)) {
        func_0016D0E0(0x300F, D_01F72910_mall_b_01);
        UNSET_FLAG(&D_1D31658, 25);
    }
}

int func_01F6D7A0_mall_b_01(void) {
    switch (D_01F72918_mall_b_01) {
        case 0:
            func_00190A20(2);
            func_001C2290(3, 0.5f);
            D_01F72918_mall_b_01++;
            /* fallthrough */
        case 1:
            if (!func_001C2580(2)) {
                return 0;
            }
            func_0016D500(2, 34, &D_01F72640_mall_b_01);
            D_01F72918_mall_b_01++; 
            break;
        default:
            func_00190A20(0);
            return 1;
    }
    return 0; 
}

#ifdef HOLY_CANDLE
int func_01F6D860_mall_b_01(void) {
    if (!GET_BIT(D_1D31654, 0x19)) {
        func_00190A20(2);
        SET_BIT(D_1D31654, 0x19);
    }

    if (!GET_BIT(D_1D31654, 0x1A)) {
        if (!func_0016C1C0(36)) {
            return 0;
        }
        if (!func_0016CB70()) {
            SET_BIT(D_1D31654, 0x1A);
            SET_BIT(D_1D31654, 0x1B);
            SeCall(12302, 0.0f, 1.0f);
        }
    } 
    else if (GET_BIT(D_1D31654, 0x1B)) {
        if (!func_0016C1C0(38)) {
            return 0;
        }
        if (!func_0016CB70()) {
            UNSET_BIT(D_1D31654, 0x1B);
            SeCall(12302, 0.0f, 1.0f);
            if (GET_BIT(D_01D31640, 0x1F) && !GET_BIT(D_1D31654, 0x1C)) {
                SET_BIT(D_1D31654, 0x1C);
            }
        }
    } 
    else {
        if (!func_0016C1C0(37)) {
            return 0;
        }
        if (!func_0016CB70()) {
            SET_BIT(D_1D31654, 0x1B);
            SeCall(12302, 0.0f, 1.0f);
        }
    }

    func_00190A20(0);
    UNSET_BIT(D_1D31654, 0x19);
    
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_01", func_01F6D860_mall_b_01);
#endif

INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_01", func_01F6DA50_mall_b_01);

int func_01F6DC10_mall_b_01(void) {
    sceVu0FVECTOR vec1;
    sceVu0FVECTOR vec2; 
    SubCharacter* scp;
    
    if (!GET_BIT(D_1D31658, 0x14)) {
        D_01F728C8_mall_b_01 = 0;
        if ((GET_BIT(D_1D31658, 0x15))) {
            D_01F728C0_mall_b_01 = 27;
        } else {
            D_01F728C0_mall_b_01 = 26;
        }
        SET_BIT(D_1D31658, 0x14);
    }
    
    if (func_00190240() != 0) {
        fontClear();
        D_01F728C8_mall_b_01 = 3;
    }
    
    if (D_01F728C8_mall_b_01 != 0) {
        clAddDynamicWall(&D_01F719C0_mall_b_01);
    }
    
    switch (D_01F728C8_mall_b_01) {                  
        case 0:
            scp = (SubCharacter*)shCharacterGetPlayer();
            scp->pos.x += -50.0f;
            volatile_vec_copy(&vec1, &scp->pos);
            volatile_vec_copy(&vec2, &scp->pos);
            vec1[0] += 1000.0f;
            vec2[0] -= 1000.0f;
            func_001E0130(NULL, vec1, vec2, 217);
            D_01F728C8_mall_b_01++;
            break;
    
        case 1:
            scp = (SubCharacter*)shCharacterGetPlayer();
            if (scp->pos.x > 52900.0f) {
                scp->pos.x += -50.0f;
            }
    
            if (func_00190D90() == 0) {
                break; 
            }
            
            func_00168430();
            func_00190A20(2);
            D_01F728C8_mall_b_01++;
        
        case 2:
            if (func_0016C1C0(D_01F728C0_mall_b_01) == 0) {
                break; 
            }
            
            D_01F728C8_mall_b_01++;
    
        default:
            if (!GET_BIT(D_1D31658, 0x15)) {
                SET_BIT(D_1D31658, 0x15);
            }
            UNSET_BIT(D_1D31658, 0x14);
            func_00190A20(0);
            return 1; 
    }
    
    return 0;
}

int func_01F6DE60_mall_b_01(void) {
    SubCharacter* scp;
    sceVu0FVECTOR vec1;
    sceVu0FVECTOR vec2; 
    
    scp = (SubCharacter*)shCharacterGetPlayer();
    scp->pos.x += -50.0f; 
    volatile_vec_copy(&vec1, &scp->pos);
    volatile_vec_copy(&vec2, &scp->pos);
    vec1[0] += 500.0f;
    vec2[0] -= 500.0f;
    func_001E0130(NULL, vec1, vec2, 218);
    return 1;
}

int func_01F6DEE0_mall_b_01(void) {
    func_0012CFA0();
    if (func_0012D080() == 0) {
        func_00190A20(2);
    }
    func_0012CFC0();
    if (func_0016BED0(!GET_BIT(D_1D31654, 0x1E) ? 0x47 : 0x45, 0x28) == 0) {
        return 0;
    }
    func_00190A20(0);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_01", func_01F6DF60_mall_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_01", func_01F6E0F0_mall_b_01);

void func_01F6E180_mall_b_01(unk_struct01F6E180* arg0) {
    func_01F6E0F0_mall_b_01();
    if (arg0->unkB0 != 0) {
        func_01F6DF60_mall_b_01(arg0);
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_01", func_01F6E1C0_mall_b_01);

int func_01F6E500_mall_b_01(void) {
    D_1D31658 |= 0x10;
    return 1;
}

void func_01F6E520_mall_b_01(void) {
    int* id;

    if ((u_char)(GetActionLevel()) <= 1) {
        return;
    }
    
    id = &D_01F727B0_mall_b_01;       

    while (*id != NULL) {
        shCharacter_Manage_Delete(NUMB_BODY_CHARA_KIND, *id);
        ++id;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_01", func_01F6E580_mall_b_01);

int func_01F6E8A0_mall_b_01(void) {
    unk_struct* temp_v0;

    if (func_00190A20(8) != 0) {
        temp_v0 = func_00190AC0();
        temp_v0->unk0 = 0x30;
        temp_v0->unk10 = -20000.0f;
        temp_v0->unk14 = 1600.0;
        temp_v0->unk18 = -20000.0f;
        temp_v0->unk4 = -(PI/2);
    }
    return 1;
}

int func_01F6E900_mall_b_01(void) {
    unk_struct* temp_v0;

    if (func_00190A20(8) != 0) {
        temp_v0 = func_00190AC0();
        temp_v0->unk0 = 3;
        temp_v0->unk10 = 63603.97f;
        temp_v0->unk14 = 505.2f;
        temp_v0->unk18 = 24132.64f;
        temp_v0->unk4 = 0;
    }
    return 1;
}

void func_01F6E960_mall_b_01(void) {
    int room;

    room = RoomName();
    D_01F72890_mall_b_01 = 0;
    switch (room) {
        case 34:
            SET_BIT(D_1D31704, 0x1D);
            break;
            
        case 29:
            if (func_0016D5B0() == 0) {
                D_01F72918_mall_b_01 = 0;
                SET_BIT(D_1D31704, 0x11);
                UNSET_BIT(D_1D31658, 0x19); 
                UNSET_BIT(D_1D31658, 0x1B);
                if (GET_BIT(D_1D31658, 0x11)) {
                    func_00190A20(0);
                    UNSET_BIT(D_1D31658, 0x11); 
                }
            }
            break;
            
        case 36:
            D_01F728E0_mall_b_01[0] = 19200.0f;
            D_01F728E0_mall_b_01[1] = -1200.0f;
            D_01F728E0_mall_b_01[2] = 56140.0f;
            D_01F728E0_mall_b_01[3] = 1.0f;
            if (!GET_BIT(D_1D31654, 0x1A)) {
                D_01F728A8_mall_b_01 = 0;
            }
            if (!GET_BIT(D_1D31654, 0x1B)) {
                D_01F728B8_mall_b_01 = 0;
                break;
            }
            D_01F728B8_mall_b_01 = 1;
            break;
            
        case 37:
            D_01F728D8_mall_b_01 = 0;
            D_01F72880_mall_b_01 = 0.0f;
            D_01F728E0_mall_b_01[0] = 51600.0f;
            D_01F728E0_mall_b_01[1] = -1199.75f;
            D_01F728E0_mall_b_01[2] = 57339.0f;
            D_01F728E0_mall_b_01[3] = 1.0f;
            D_01F72888_mall_b_01 = 0.4f;
            if (!GET_BIT(D_1D31654, 0x1B)) {
                D_01F728B8_mall_b_01 = 0;
                break;
            }
            D_01F728B8_mall_b_01 = 1;
            break;
            
        case 41:
            SET_BIT(D_1D31704, 0x12);
    }
}

void func_01F6EB90_mall_b_01(void) {
    sceVu0FMATRIX* sp20[4];
    sceVu0FMATRIX* sp30[4];
    sceVu0FVECTOR sp40;
    sceVu0FMATRIX* sp50[4];
    sceVu0FMATRIX* sp60[4];
    sceVu0FVECTOR sp70;
    sceVu0FMATRIX* sp80[4];
    sceVu0FMATRIX* sp90[4];
    sceVu0FVECTOR spA0;
    
    SubCharacter* scp;
    
    D_01F72890_mall_b_01 = 1;
    switch (RoomName()) {
        case 29:
            func_01F6D680_mall_b_01();
            scp = shCharacterGetSubCharacter(BG_TKA_CHARA_KIND, 0x3D);
            if (scp != NULL) {
                func_0016CBD0(sp20, sp30, 6);
                func_0016CC50(BG_TKA_CHARA_KIND, 0, *sp20, &sp40[0]);
                volatile_vec_copy(&scp->pos, (sceVu0FVECTOR *) *sp20 + 3);
                volatile_vec_copy(&scp->rot, &sp40);
            }
            
            scp = shCharacterGetSubCharacter(BG_TKA_CHARA_KIND, 0x3E);
            if (scp != NULL) {
                func_0016CBD0(sp20, sp30, 7);
                func_0016CC50(BG_TKA_CHARA_KIND, 0, *sp20, &sp40[0]);
                volatile_vec_copy(&scp->pos, (sceVu0FVECTOR *) *sp20 + 3);
                volatile_vec_copy(&scp->rot, &sp40);
            }
            
            scp = shCharacterGetSubCharacter(BG_TKA_CHARA_KIND, 0x3F);
            if (scp != NULL) {
                func_0016CBD0(sp20, sp30, 8);
                func_0016CC50(BG_TKA_CHARA_KIND, 0, *sp20, &sp40[0]);
                volatile_vec_copy(&scp->pos, (sceVu0FVECTOR *) *sp20 + 3);
                volatile_vec_copy(&scp->rot, &sp40);
            }
            break;
        
        case 40:
            scp = shCharacterGetSubCharacter(BG_TKA_CHARA_KIND, 0x41);
            if (scp != NULL) {
                func_0016CBD0(sp50, sp60, 4);
                func_0016CC50(BG_TKA_CHARA_KIND, 0, *sp50, &sp70[0]);
                volatile_vec_copy(&scp->pos, (sceVu0FVECTOR *) *sp50 + 3);
                volatile_vec_copy(&scp->rot, &sp70);
            }
            break;
        
        case 36:
            if (!GET_BIT(D_1D31654, 0x1B)) {
                D_01F728F0_mall_b_01 = func_0016D240(1.0f, 5000.0f, 0x300D, D_01F728E0_mall_b_01, 0, 0);
                break;
            }
            break;
        
        case 37:
            if (!GET_BIT(D_1D31654, 0x1B)) {
                D_01F728F0_mall_b_01 = func_0016D240(1.0f, 5000.0f, 0x300D, D_01F728E0_mall_b_01, 0, 0);
            }
            
            if ((u_char)GetRiddleLevel()) {
                if (!GET_BIT(D_01D31640, 0x1F)) {
                    func_00196770();
                    func_003010F0();
                } else {
                    func_00300E70();
                }
            }
            
            if (GET_BIT(D_01D31640, 0x1F)) {
                if (!GET_BIT(D_1D31654, 0x1C)) {
                    func_00196770();
                    func_00311410();
                }
            }
            
            scp = shCharacterGetSubCharacter(BG_TKA_CHARA_KIND, 0x40);
            if (scp != NULL) {
                func_0016CBD0(sp80, sp90, 5);
                func_0016CC50(BG_TKA_CHARA_KIND, 0, *sp80, &spA0[0]);
                volatile_vec_copy(&scp->pos, (sceVu0FVECTOR *) *sp80 + 3);
                volatile_vec_copy(&scp->rot, &spA0);
            }
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_01", func_01F6EEC0_mall_b_01);

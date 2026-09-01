#include "mall_b_01.h"

#include "Chacter/m3_sc.h"

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
            SeCall(1.0f, 0.0f, 0x300E);
        }
    } 
    else if (GET_BIT(D_1D31654, 0x1B)) {
        if (!func_0016C1C0(38)) {
            return 0;
        }
        if (!func_0016CB70()) {
            UNSET_BIT(D_1D31654, 0x1B);
            SeCall(1.0f, 0.0f, 0x300E);
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
            SeCall(1.0f, 0.0f, 0x300E);
        }
    }

    func_00190A20(0);
    UNSET_BIT(D_1D31654, 0x19);
    
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_01", func_01F6DA50_mall_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_01", func_01F6DC10_mall_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_01", func_01F6DE60_mall_b_01);

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

INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_01", func_01F6E960_mall_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_01", func_01F6EB90_mall_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/stage/mall_b_01", func_01F6EEC0_mall_b_01);

#include "building_b_02.h"

INCLUDE_ASM("asm/nonmatchings/Event/building_b_02", func_01F6D680_building_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_02", func_01F6D7B0_building_b_02);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_02", func_01F6D980_building_b_02);

void func_01F6DB60_building_b_02(void) { //I will debug it later
    int temp_a0;
    int var_s0;
    int* var_s1;

    var_s0 = 0;

    for (var_s1 = D_01F6EE80_building_b_02; *var_s1 != 0; var_s1++) {
        temp_a0 = func_0012FD80(0x20A, *var_s1);
        if (temp_a0 == 0) {
            continue;
        }
        
        if (func_001E2110(temp_a0) == 0) {
            var_s0++;
        }
        if ((*var_s1 == 0xDB || *var_s1 == 0xDC)) {
            continue;
        }
        if (!((D_1D31670 >> 0x11) & 1)) {
            shCharacter_Manage_Delete(0x20A, *var_s1);
            continue;
        }
        if (func_00199770() < 3) {
            if (var_s0 > 1) {
                shCharacter_Manage_Delete(0x20A, *var_s1);
            }
        } else {
            if (var_s0 > 2) {
                shCharacter_Manage_Delete(0x20A, *var_s1);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/building_b_02", func_01F6DC70_building_b_02);

int func_01F6DE10_building_b_02(void) { //this is similar to func_01F6E700_building_b_03
    int var_s0;

    var_s0 = 0;

    if (!((D_1D31670 >> 0x16) & 1)) {
        D_01F6EF00_building_b_02 = 0;
        D_01F6EF08_building_b_02 = 0.0f;
        D_1D31670 |= 0x400000;
        func_001C2290(3, 1.5f);
        func_0016C1A0();
        SeCall(1.0f, 0.0f, 0x4A59);
    }
    D_01F6EF08_building_b_02 += shGetDT();

    switch (D_01F6EF00_building_b_02) {
        
        case 0:
            if (D_01F6EF08_building_b_02 < 0.5f) {
                return 0;
            }
            SeCall(1.0f, 0.0f, 0x4A58);
            D_01F6EF00_building_b_02 += 1;
        
        case 1:
            if (D_01F6EF08_building_b_02 < 1.5f) {
                return 0;
            }
            func_0016C1B0();
            D_01F6EF00_building_b_02 += 1;
            break;
        
        default:
            var_s0 = 1;
            D_1D31670 &= 0xFFBFFFFF;
            D_1D31714 |= 0x40000;
            D_1D31670 |= 0x100;
            D_1D317AC |= 0x08000000;
    
    }
    return var_s0;
}

void func_01F6DFD0_building_b_02(void) {
    
    D_01F6EF10_building_b_02 = 0;
 
    switch (RoomName()) {

        case BUILDING_OTHERWORLD_STAIRS_BEHIND_PAINTING:
            D_1D31714 |= 0x200000; //first time entering the stairs
            break;

        case BUILDING_OTHERWORLD_4F_SILVER_COIN_ROOM:
            D_01F6EF28_building_b_02 = 0;
            break;

        case BUILDING_OTHERWORLD_4F_BED_ROOM:
            D_1D317B0 |= 0x400; //first time entering this room
            break;

        }
}

void func_01F6E050_building_b_02(void) {
    
    D_01F6EF10_building_b_02 = 1; //it probably has something to do with spawning the extra dog

    switch (RoomName()) {
        
        case BUILDING_OTHERWORLD_4F_SILVER_COIN_CORRIDOR:
            func_01F6DB60_building_b_02(); //I need to verify this with higher action level difficulties
        
        default:
            break;
        
    }
    
}

void func_01F6E090_building_b_02(void) {
    
    if (D_01F6EF10_building_b_02 == 0) {
        func_01F6E050_building_b_02(); //I need to verify this with higher action level difficulties
    }

    switch (RoomName()) {
        
        case BUILDING_OTHERWORLD_4F_HALL:
            if (func_00190950() != 0) {
                func_001A06F0(&D_01F6EB80_building_b_02); 
                break;
            }
            break;
            
        case BUILDING_OTHERWORLD_4F_SILVER_COIN_ROOM:
            if (!((D_1D31670 >> 0xF) & 1)) { //check if you have the silver coin
                func_0016CA40(1);
                D_1D31714 |= 0x02000000; //if you dont
            } else {
                D_1D31714 &= 0xFDFFFFFF; //when you grab it
            }
            
            if (!((D_1D31644 >> 0x14) & 1)) { //if you havent solved the vending machine puzzle yet
                D_1D31714 |= 0x04000000;
                D_1D31714 |= 0x08000000;
                break;
            }
            D_1D31714 &= 0xFBFFFFFF; //after you solved it
            D_1D31714 &= 0xF7FFFFFF;
            break;
            
        case BUILDING_OTHERWORLD_4F_SILVER_COIN_CORRIDOR:
            if (((D_1D31670 >> 0x12) & 1) && !((D_1D31670 >> 0x13) & 1)) {
                func_01F6DC70_building_b_02(D_1D31670); //it probably has something to do with spawning the extra dog, but I need to match it first
            }
            break;
    }
}

#include "building_b_00.h"

INCLUDE_ASM("asm/nonmatchings/Event/building_b_00", func_01F6D680_building_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_00", func_01F6D7C0_building_b_00);

int func_01F6D9B0_building_b_00(void) {
    if (!GET_FLAG(D_1D31670, 0xB)) {
        func_00317420(0x3A);
        D_01F6FB00_building_b_00 = 0;
        func_0016C3C0();
        D_1D31670[0] |= 0x800;
        func_00190A20(2);
    }
    switch (D_01F6FB00_building_b_00) {
        
        case 0:
            if (func_0016C1C0(0x29) == 0) {
                return 0;
            }
            if (func_00168440() != 0) {
                break;
            }
            func_00317490(0x3A, 0.2f);
            func_0016C3C0();
            SeCall(1.0f, 0.0f, 0x2B21);
            ItemGet(0x3A);
            D_1D31670[0] |= 0x1000;
            D_01F6FB00_building_b_00 += 1;
        default:
            
            if (func_0016C1C0(0x33) == 0) {
                return 0;
            }
        func_003174B0(0.2f);
    }    
    D_1D31670[0] &= ~0x800;
    func_00190A20(0);
    return 1;
}


INCLUDE_ASM("asm/nonmatchings/Event/building_b_00", func_01F6DB00_building_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_00", func_01F6DC40_building_b_00);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_00", func_01F6DD70_building_b_00);

int func_01F6E0B0_building_b_00(void) { // same elevator bullshit as the others similar functions
    int var_s0;

    var_s0 = 0;
    if (!GET_FLAG(D_1D31670, 0x16)) {
        D_01F6FB08_building_b_00 = 0;
        D_01F6FB10_building_b_00 = 0.0f;
        D_1D31670[0] |= 0x400000;
        func_001C2290(3, 1.5f);
        func_0016C1A0();
        SeCall(1.0f, 0.0f, 0x4A59);
    }
    D_01F6FB10_building_b_00 += shGetDT();
    switch (D_01F6FB08_building_b_00) {

        case 0:
            if (D_01F6FB10_building_b_00 < 0.5f) {
                return 0;
            }
            SeCall(1.0f, 0.0f, 0x4A58);
            D_01F6FB08_building_b_00 += 1;
        
        case 1:
            if (D_01F6FB10_building_b_00 < 1.5f) {
                return 0;
            }
            func_0016C1B0();
            D_01F6FB08_building_b_00 += 1;
            break;
           
        default:
            var_s0 = 1;
            D_1D31670[0] &= 0xFFBFFFFF;
            D_1D31710[0] |= 0x40000000;
            D_1D31670[0] |= 0x40;
            D_1D317A8 |= 0x100000;
            
    }
    return var_s0;
}


void func_01F6E270_building_b_00(void) {

    switch (RoomName()) {

        case BUILDING_OTHERWORLD_1F_HALL:
            D_1D31714 |= 0x2;    
            break;
        
        case BUILDING_OTHERWORLD_1F_LAST_FAIRY_TAIL_PIECE_ROOM:
            D_1D31714 |= 0x10;
            break;
        
    }
}

void func_01F6E2D0_building_b_00(void) {
    switch (RoomName()) {                              
        case 0x81:
            if (!((D_1D31644 >> 0x16) & 1)) {
                func_0016CA40(1);
                func_0016CA40(2);
                break;
            }
            break;
            
        case 0x7F:
            if (!GET_FLAG(D_1D31670, 0xC)) {
                func_0016CA40(7);
                D_1D31714 |= 4;
            } else {
                D_1D31714 &= ~4;
            }
            break;
        
        case 0x7E:
            if (!GET_FLAG(D_1D31670, 0x15) && (GET_FLAG(D_1D31670, 0x18) || GET_FLAG(D_1D31670, 0x19))) {
                D_1D31670[1] |= 0x10;
            } else {
                D_1D31670[1] &= ~0x10;
            }

            if (!GET_FLAG(D_1D31670, 0x15)) {
                clAddDynamicFloor(&D_01F6EC70_building_b_00);
                clAddDynamicFloor(&D_01F6F260_building_b_00);
                clAddDynamicFloor(&D_01F6F530_building_b_00);
                clAddDynamicWall(&D_01F6F760_building_b_00);
                D_1D31714 |= 0x1;
            } else {
                func_00189F00(0xEF);
                func_00189FA0(0xEF, 9);
                D_1D31714 &= ~0x1;
            }
            break;
    }
}
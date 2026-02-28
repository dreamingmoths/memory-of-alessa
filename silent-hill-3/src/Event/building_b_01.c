#include "building_b_01.h"

INCLUDE_ASM("asm/nonmatchings/Event/building_b_01", func_01F6D680_building_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_01", func_01F6D6E0_building_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_01", func_01F6D7E0_building_b_01);

void func_01F6D970_building_b_01(void) {

    if (func_0016C540(&D_01F6EFF0_building_b_01, &D_01F6F050_building_b_01) == 0) {
        D_1D316AC |= 0x20000000; //cutscene start
    } else {
        D_1D316AC &= 0xDFFFFFFF; //cutscene end
    }

}

INCLUDE_ASM("asm/nonmatchings/Event/building_b_01", func_01F6D9E0_building_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_01", func_01F6DA90_building_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_01", func_01F6DEA0_building_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_01", func_01F6DFF0_building_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_01", func_01F6E0F0_building_b_01);

void func_01F6E2A0_building_b_01(void) {

    switch (RoomName()) {                              
        case BUILDING_OTHERWORLD_BATHTUB_ROOM:
            if (((D_01D31640 >> 0x12) & 1) && !((D_01D31640 >> 0x13) & 1)) { //after the bathtub room awakening cutscene ???
                func_001C2290(2, 0.0f); 
            }
            D_01F6F138_building_b_01 = 0;
            D_01F6F130_building_b_01 = 0;
            break;
        case BUILDING_OTHERWORLD_HANGING_MOTHER_ROOM:
            D_01F6F118_building_b_01 = 0;
            D_1D317AC |= 0x20000; //first time entering hanging mother room
            break;
        case BUILDING_OTHERWORLD_VINCENT_CORRIDOR:
            D_1D31714 |= 0x1000; //first time entering vincent corridor
            break;
    }
}

void func_01F6E360_building_b_01(void) {

    switch (RoomName()) {                              

        case BUILDING_OTHERWORLD_BATHTUB_ROOM:
            break;
            
        case BUILDING_OTHERWORLD_OXYDOL_ROOM:
            if ((func_00199820() & 0xFF) != 2) { //different hint based on riddle????
                func_0016CA40(0x13);
                D_1D31714 |= 0x8000;
            } else {
                D_1D31714 &= 0xFFFF7FFF;
            }
    
            if (!((D_1D31670 >> 0xE) & 1)) { //oxydol check
                func_0016CA40(0x12);
                D_1D31714 |= 0x4000;
                break;
            }
            func_00189F00(0xF1);
            func_00189FA0(0xF1, 0xF);
            D_1D31714 &= ~0x4000; //oxydol grab
            break;
            
        case BUILDING_OTHERWORLD_VINCENT_CORRIDOR:
            if (!((D_1D3166C >> 0x1C) & 1)) { //check if player hasnt read heather's photo letter yet
                func_0016CA40(6);
                D_1D31714 |= 0x2000;
                break;
            }
            D_1D31714 &= ~0x2000; //after picking up the note
            break;
    
        case BUILDING_OTHERWORLD_HANGING_MOTHER_ROOM: 
            func_01F6DFF0_building_b_01(); //no idea what it does
    
    }
   
}

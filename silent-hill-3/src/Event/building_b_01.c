#include "building_b_01.h"

INCLUDE_ASM("asm/nonmatchings/Event/building_b_01", func_01F6D680_building_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_01", func_01F6D6E0_building_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_01", func_01F6D7E0_building_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_01", func_01F6D970_building_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_01", func_01F6D9E0_building_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_01", func_01F6DA90_building_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_01", func_01F6DEA0_building_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_01", func_01F6DFF0_building_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_01", func_01F6E0F0_building_b_01);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_01", func_01F6E2A0_building_b_01);

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

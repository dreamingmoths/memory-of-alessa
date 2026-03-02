#include "building_b_03.h"

INCLUDE_ASM("asm/nonmatchings/Event/building_b_03", func_01F6D680_building_b_03);

int func_01F6D8F0_building_b_03(void) { //All of this handle the interaction with the "Flame Purifies All" painting in the otherworld gallery room

    if (!((D_1D31674 >> 6) & 1)) {
        func_00190A20(2);
        D_1D31674 |= 0x40;
        if (!((D_1D31674 >> 3) & 1)) {
            D_01F6FC30_building_b_03 = 0x19; //this gets set the FIRST TIME you interact with with the "Flame Purifies All" painting, where Heather mentions that she has already seen the painting
        } else {
            D_01F6FC30_building_b_03 = 0x1A; //this gets set the SECOND TIME you interact with with the "Flame Purifies All" painting, heather doesnt mention that she saw the painting anymore
        }
    }
   
    if (func_0016C1C0(D_01F6FC30_building_b_03) == 0) { //no idea what this does for now Sadge
        return 0;
    }
    if (!((D_1D31674 >> 3) & 1)) {
        D_1D31674 |= 8; //this gets set when you FINISH to interact with the "Flame Purifies All" painting for the FIRST time
    }

    D_1D316F4 |= 0x20; //These get set when you FINISH to interact with the "Flame Purifies All" painting
    D_1D317B0 |= 0x40000000; 
    D_1D31674 &= ~0x40;
    
    func_00190A20(0);
    return 1;
}


INCLUDE_ASM("asm/nonmatchings/Event/building_b_03", func_01F6D9F0_building_b_03);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_03", func_01F6DA80_building_b_03);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_03", func_01F6DAD0_building_b_03);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_03", func_01F6DC90_building_b_03);

void func_01F6DCE0_building_b_03(int arg0) {
    func_001DE5B0(func_01F6DC90_building_b_03, arg0, 1); 
}

INCLUDE_ASM("asm/nonmatchings/Event/building_b_03", func_01F6DD00_building_b_03);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_03", func_01F6DE40_building_b_03);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_03", func_01F6DF60_building_b_03);

#ifdef NON_MATCHING
int func_01F6E700_building_b_03(void) { 
    int var_s0;

    var_s0 = 0;
    if (!((D_1D31670 >> 0x16) & 1)) {  //interacting with the elevator from the 5th floor (when you want to enter inside of it)
        D_01F6FC00_building_b_03 = 0;
        D_01F6FC08_building_b_03 = 0.0f;
        D_1D31670 |= 0x400000; 
        func_001C2290(3, 1.5f);
        func_0016C1A0();
        SeCall(1.0f, 0.0f, 0x4A59);
    }
    D_01F6FC08_building_b_03 += shGetDT();
    switch (D_01F6FC00_building_b_03) {
        case 0:
            if (D_01F6FC08_building_b_03 < 0.5f) {
                return 0;
            }
            SeCall(1.0f, 0.0f, 0x4A58);
            D_01F6FC00_building_b_03 += 1;
        case 1:
            if (D_01F6FC08_building_b_03 < 1.5f) {
                return 0;
            }
            func_0016C1B0();
            D_01F6FC00_building_b_03 += 1;
            break;
        default:  //this gets executed everytime you reach the 5th floor with the elevator
            var_s0 = 1;
            D_1D31670 &= 0xFFBFFFFF;
            D_1D31714 |= 0x80000000;            
            D_1D31670 |= 0x200;
            D_1D317B0 |= 0x2000;
    }

    return var_s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/building_b_03", func_01F6E700_building_b_03);
#endif

void func_01F6E8C0_building_b_03(void) {
    int room;    
    room = RoomName();
    D_01F6FC28_building_b_03 = 0;
    switch (room) { //I would like to put RoomName() here directly

        case BUILDING_OTHERWORLD_MATCHBOOK_ROOM: //Matchbook room
            break;

        case BUILDING_OTHERWORLD_GALLERY_ROOM: //otherworld gallery
            D_01F6FC40_building_b_03 = 0;
            D_1D31718 |= 0x10; //first time entering gallery 
            break;

        case BUILDING_OTHERWORLD_ELEVATOR: //elevator
            D_01F6FC10_building_b_03 = 0;
            D_01F6FC18_building_b_03 = 1.0f;
            D_1D31718 |= 0x20; //this gets set the FIRST TIME you enter the elevator
            D_01F6FC20_building_b_03 = 1500.0f;

            if (!((D_1D31670 >> 6) & 1) && !((D_1D31670 >> 7) & 1) && !((D_1D31670 >> 8) & 1) && !((D_1D31670 >> 9) & 1)) {
                D_1D31670 |= 0x80; //this gets set ONLY WHEN YOU ENTER THE ELEVATOR FROM THE SECOND FLOOR, then it get reset everytime you exit the elevator
            }            

    }
}

INCLUDE_ASM("asm/nonmatchings/Event/building_b_03", func_01F6E9B0_building_b_03);

INCLUDE_ASM("asm/nonmatchings/Event/building_b_03", func_01F6EAC0_building_b_03);

#include "building_f_00.h"

int func_01F6D680_building_f_00(void) {
    return 1;
}

int func_01F6D690_building_f_00(void) {
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/building_f_00", func_01F6D6A0_building_f_00);

void func_01F6D960_building_f_00(void* arg) {
    shQzero(arg, 0xE8);
}

INCLUDE_ASM("asm/nonmatchings/Event/building_f_00", func_01F6D970_building_f_00);

void func_01F6E0D0_building_f_00(void) {
    
    switch (RoomName()) {   

        case BUILDING_BATHTUB_ROOM:
            D_1D3170C |= 0x100000;
            break;
            
        case BUILDING_2F_HALL:
            D_1D3170C |= 0x200000;
            break;

    }
}

int func_01F6E140_building_f_00(void) {

    switch (RoomName()) {

         case BUILDING_BATHTUB_ROOM:
            break;

    }
}

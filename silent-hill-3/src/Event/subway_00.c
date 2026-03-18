#include "common.h"
#include "subway_00.h"

int func_01F6D680_subway_00(void) {
    int temp_v0;
    int var_s0;

    var_s0 = 0;
    
    func_0012CFA0();
    temp_v0 = func_0012D080();
    switch (temp_v0) {                              
    case 0:
        if (func_00190A20(2) != 0) {
            func_0012D0A0();
        }
        break;
    case 1:
        if (func_0016C1C0(0x19) != 0) {
            func_0012D0A0();
        case 2:
            PlayerEventMove(&D_01F6F4C0_subway_00);
            if (func_00190690() != 0) {
                func_00190AD0();
                var_s0 = 1;
            }
        }
        break;
    }
    func_0012CFC0();
    return var_s0;
}

int func_01F6D740_subway_00(void) {
    switch (D_01F6F600_subway_00) {                
    case 0:
        func_00190A20(2);
        D_01F6F600_subway_00 += 1;
        /* fallthrough */
    case 1:
        if (func_0016BED0(0x50, 0x1A) == 0) {
            return 0;
        }
        func_00190A20(0);
    default:
        D_01F6F600_subway_00 = 0;
        return 1;
    }
}

int func_01F6D7D0_subway_00(void) {
    switch (D_01F6F600_subway_00) {                 
    case 0:
        func_00190A20(2);
        func_0016CD00(&D_01F6F4D0_subway_00);
        func_001C2290(3, 0.8f);
        D_01F6F600_subway_00 = 1;
        /* fallthrough */
    case 1:
        if (func_001C2580(2) == 0) {
            return 0;
        }
        D_01F6F600_subway_00 = 2;
        func_001C2290(5, 0.8f);
    case 2:
        if (func_0016BED0(0xBD, 0x1B) == 0) {
            return 0;
        }
        D_01F6F600_subway_00 = 3;
        func_001C2290(5, 0.8f);
    case 3:
        func_00190A20(0);
    default:
        D_01F6F600_subway_00 = 0;
        return 1;
    }
}

int func_01F6D8E0_subway_00(void) {
    switch (D_01F6F600_subway_00) {                
    case 0:
        func_00190A20(2);
        D_01F6F600_subway_00 += 1;
        /* fallthrough */
    case 1:
        if (func_0016BED0(0x4E, 0x1C) == 0) {
            return 0;
        }
        func_00190A20(0);
    default:
        D_01F6F600_subway_00 = 0;
        return 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/subway_00", func_01F6D970_subway_00);

INCLUDE_ASM("asm/nonmatchings/Event/subway_00", func_01F6DA10_subway_00);

INCLUDE_ASM("asm/nonmatchings/Event/subway_00", func_01F6DE90_subway_00);

INCLUDE_ASM("asm/nonmatchings/Event/subway_00", func_01F6DFB0_subway_00);

INCLUDE_ASM("asm/nonmatchings/Event/subway_00", func_01F6E0E0_subway_00);

void func_01F6E250_subway_00(void) 
{
    D_01F6F620_subway_00 = 0.0f;
    RoomName();
}


INCLUDE_ASM("asm/nonmatchings/Event/subway_00", func_01F6E260_subway_00);

INCLUDE_ASM("asm/nonmatchings/Event/subway_00", func_01F6E2E0_subway_00);

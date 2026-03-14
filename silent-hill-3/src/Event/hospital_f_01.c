#include "hospital_f_01.h"

int func_01F6D680_hospital_f_01(void) {
    func_0012CFA0();
    if (func_0012D080() == 0) {
        func_00190A20(2);
    }
    func_0012CFC0();
    if (func_0016BED0(0x30, 0x27) == 0) {
        return 0;
    }
    D_1D316F4 |= 0x80000;
    func_00190A20(0);
    return 1;
}

int func_01F6D700_hospital_f_01(void) {

    func_0012CFA0();
    if (func_0012D080() == 0) {
        func_00190A20(2);
    }
    func_0012CFC0();
    D_1D31680 |= 0x20000;
    if (func_0016BED0(0x31, 0x28) == 0) {
        return 0;
    }
    D_1D31680 &= 0xFFFDFFFF;
    D_1D316F4 |= 0x100000;
    func_00190A20(0);
    return 1;
}

int func_01F6D7B0_hospital_f_01(void) {
    func_0012CFA0();
    if (func_0012D080() == 0) {
        func_00190A20(2);
    }
    func_0012CFC0();
    if (func_0016BED0(0x2D, 0x1D) == 0) {
        return 0;
    }
    if (!((D_1D316F4 >> 0xE) & 1)) {
        D_1D316F4 |= 0x4000;
    }
    if (!((D_1D31680 >> 0xE) & 1)) {
        D_1D31680 |= 0x4000;
    }
    if (!((D_1D31688 >> 7) & 1)) {
        D_1D31688 |= 0x80;
    }
    func_00190A20(0);
    return 1;
}

int func_01F6D880_hospital_f_01(void) {
    int var_s1;
    int riddle_level;
    int index;

    if (!((D_1D31688 >> 0xB) & 1)) {
        if (!((D_1D31688 >> 0xA) & 1)) {
            D_01F71680_hospital_f_01 = 0;
        } else {
            D_01F71680_hospital_f_01 = 1;
        }
        D_1D31688 |= 0x800;
        func_00190A20(2);
    }
    riddle_level = GetRiddleLevel() & 0xFF;
    var_s1 = 0x19;
    if (riddle_level <= 0) {
        index = 0x5AB;
    } else {
        var_s1 = 0x1A;
        if (riddle_level >= 2) {
            var_s1 = 0x1B;
            index = 0x5AD;
        } else {
            index = 0x5AC;
        }
    }
   
    switch (D_01F71680_hospital_f_01) {
        case 0:
            if (!func_0016C1C0(0x1C)) return 0;
            if (func_00168440()) break;
            D_01F71680_hospital_f_01++;
            func_0016C3C0();
        default:
            if (!func_0016C1C0(var_s1)) return 0;
            break;
    }

    func_00190A20(0);
    D_1D31688 &= ~0x800;
    if (!((D_1D31688 >> 10) & 1)) {
        D_1D31688 |= 0x400;
    }
    
    if (!(((D_01D31640[index >> 5] >> (index & 0x1F)) & 1))) {
        D_01D31640[index >> 5] |= (1 << (index & 0x1F));
    }
    return 1;

}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6DA30_hospital_f_01);

void func_01F6DAC0_hospital_f_01(void) {

}

void func_01F6DAD0_hospital_f_01(void) {

}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6DAE0_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6DB50_hospital_f_01);

int func_01F6DB70_hospital_f_01(void) {
    float sp18;
    float sp1C;

    func_0029F330(&sp18, &sp1C);
    return func_002A47C0(sp18, sp1C) & 0xFFFF;
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6DBA0_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6DCF0_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6DE00_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6E140_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6E1C0_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6E570_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6E600_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6E650_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6E850_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6EE60_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6EED0_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6EEF0_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6EFB0_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6F060_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6F380_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6F410_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6F640_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6F670_hospital_f_01);

int func_01F6F690_hospital_f_01(void) {
    float sp18;
    float sp1C;

    func_0029F330(&sp18, &sp1C);
    return func_002A47C0(sp18, sp1C) & 0xFFFF;
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6F6C0_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6F7D0_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6F880_hospital_f_01);

#ifdef NON_MATCHING
int func_01F6FBA0_hospital_f_01(void) { //when you enter the elevator from the second floor
    int ret;

    ret = 0;
    if (!(( D_1D31688 >> 4) & 1)) {
        D_01F71688_hospital_f_01 = 0;
        D_1D31688 |= 0x10;
        D_01F71690_hospital_f_01 = 0.0f;
        func_001C2290(3, 1.5f);
        func_0016C1A0();
        SeCall(1.0f, 0.0f, 0x4A59);
    }
    D_01F71690_hospital_f_01 += shGetDT();
    switch (D_01F71688_hospital_f_01) {
        case 0:
            if (D_01F71690_hospital_f_01 < 0.5f) {
                return ret;
            }
            SeCall(1.0f, 0.0f, 0x4A58);
            D_01F71688_hospital_f_01 += 1;
        case 1:
            if (D_01F71690_hospital_f_01 < 1.5f) {
                return ret;
            }
            func_0016C1B0();
            D_01F71688_hospital_f_01 += 1;
            break;        
        default:
            ret = 1;
            D_1D31688 &= ~0x10;
            D_1D31720 |= 0x2000;
            D_1D31684 |= 0x200;
            D_1D317B8 |= 0x100000;

    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6FBA0_hospital_f_01);
#endif

void func_01F6FD50_hospital_f_01(void) {

    if (!(D_1D31684 & 1)) {
        func_01F70370_hospital_f_01();
        D_1D31684 |= 1;
    }
    if ((D_1D31680 >> 0x10) & 1) {
        D_1D31680 &= 0xFFFDFFFF;
        D_1D31680 &= 0xFFFEFFFF;
    }

    switch (RoomName()) {
        case HOSPITAL_2F_ELEVATOR_HALLWAY:
            if (((D_1D31684 >> 0xC) & 1) && !((D_1D31684 >> 0x12) & 1) && !((D_1D31688 >> 2) & 1) && !((D_1D31644 >> 5) & 1) && !((D_1D31684 >> 0x11) & 1)) {
                D_1D31684 |= 0x10000;
                break;
            }
            D_1D31684 &= 0xFFFEFFFF;
            break;
        case HOSPITAL_2F_M4_ROOM:
            if (((D_1D31684 >> 0xC) & 1) && !((D_1D31684 >> 0x15) & 1) && !((D_1D31688 >> 2) & 1) && !((D_1D31644 >> 5) & 1) && ((D_1D31680 >> 0xE) & 1) && !((D_1D31684 >> 0x14) & 1)) {
                D_1D31684 |= 0x80000;
                D_1D31684 |= 0x100000;
                break;
            }
            D_1D31684 &= 0xFFF7FFFF;
            break;
        case HOSPITAL_2F_EXAMINING_ROOM_3:
            D_1D31720 |= 0x800000;
            D_1D31720 |= 0x01000000;
            D_1D31720 |= 0x02000000;
            break;
        case HOSPITAL_2F_WOMENS_LOCKER_ROOM:
            if (GetExtraNewGame() == 1) {
                D_1D31688 |= 0x8000;
            } else {
                D_1D31688 &= 0xFFFF7FFF;
            }
            break;
        }
}

void func_01F70000_hospital_f_01(void) {

    int riddle_level;

    switch (RoomName()) { 
        
        case HOSPITAL_2F_ELEVATOR_HALLWAY:
            if ((D_1D31684 >> 0x10) & 1) {
                func_0016CA40(1);
                D_1D31720 |= 0x8000;
            } else {
                D_1D31720 &= 0xFFFF7FFF;
            }
    
            riddle_level = GetRiddleLevel() & 0xFF;
            if (riddle_level <= 0) {
                func_0016CA40(9);
            } else if (riddle_level == 1) {
                func_0016CA40(0xB);
            } else {
                func_0016CA40(0xA);
            }
            if (!((D_1D31680 >> 0xB) & 1)) {
                D_1D31720 |= 0x4000;
                D_1D31720 |= 0x10000;
            } else {
                D_1D31720 &= ~0x4000;
                D_1D31720 &= 0xFFFEFFFF;
            }
            break;
        
        case HOSPITAL_2F_WOMENS_LOCKER_ROOM:
            if (!((D_1D31680 >> 4) & 1)) {
                func_0016CA40(0xB);
                D_1D31720 |= 0x40000;
            } else {
                D_1D31720 &= 0xFFFBFFFF;
            }
    
            if (!(( D_1D31680 >> 5) & 1)) {
                func_0016CA40(0xA);
                D_1D31720 |= 0x20000;
            } else {
                D_1D31720 &= 0xFFFDFFFF;
            }
            break;
        
        case HOSPITAL_2F_M_CORRIDOR:
            if ((D_1D31644 >> 5) & 1) {
                func_0016CA40(2);
                func_0016CA40(3);
                break;
            }
            func_0016CA40(1);
            clAddDynamicWall(&D_01F71000_hospital_f_01);
            clAddDynamicWall(&D_01F71140_hospital_f_01);
            clAddDynamicWall(&D_01F711E0_hospital_f_01);
            break;
        
        case HOSPITAL_2F_M4_ROOM:
            if ((D_1D31684 >> 0x13) & 1) {
                func_0016CA40(4);
                D_1D31720 |= 0x10000000;
            } else {
                D_1D31720 &= 0xEFFFFFFF;
            }
    
            func_01F6E1C0_hospital_f_01();
            if ((D_1D31680 >> 0x14) & 1) {
                func_0016CA40(3);
                if (!((D_1D31680 >> 6) & 1)) {
                    func_0016CA40(1);
                    D_1D31720 |= 0x04000000;
                } else {
                    D_1D31720 &= 0xFBFFFFFF;
                }
            } else {
                func_0016CA40(2);
                D_1D31720 |= 0x04000000;
            }
            break;
        }
}

int func_01F70370_hospital_f_01(void) {
    
    int hours;
    int minutes;
    u_int *temp = D_01D31640;

    D_1D318DC = 0;
    D_1D318E0 = 0;
    if ((GetRiddleLevel () & 0xFF) == 2) { //check if riddle level is hard
        hours = (shRandI() % 12) + 12;
    } else {
        hours = (shRandI() % 12) + 1;
    }
    
    temp[0xA7] = ((((hours / 10) * 16)  << 8) + ((hours) % 10 * 128 << 1));
    minutes = shRandI() % 60;
    temp[0xA7] += minutes % 10 + 16 * (minutes / 10);
    
    /* I will leave a clearer version as a comment
    D_1D318DC = (hours % 10 + 16 * (hours / 10)) << 8;   
    minutes = shRandI() % 60;
    D_1D318DC->unk29C += minutes % 10 + 16 * (minutes / 10);
    */

}

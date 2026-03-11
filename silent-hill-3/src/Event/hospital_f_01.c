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


INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6D880_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6DA30_hospital_f_01);

void func_01F6DAC0_hospital_f_01(void) {

}

void func_01F6DAD0_hospital_f_01(void) {

}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6DAE0_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6DB50_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6DB70_hospital_f_01);

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

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6F690_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6F6C0_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6F7D0_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6F880_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F6FBA0_hospital_f_01);

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
            if (func_00199BB0() == 1) {
                D_1D31688 |= 0x8000;
            } else {
                D_1D31688 &= 0xFFFF7FFF;
            }
            break;
        }
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F70000_hospital_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_01", func_01F70370_hospital_f_01);

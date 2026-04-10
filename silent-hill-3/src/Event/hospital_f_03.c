#include "hospital_f_03.h"

UNCURSE_HOSPITAL_MOON();

int func_01F6D680_hospital_f_03(void) {
    int ret;

    ret = 0;
    if (!GET_BIT(D_1D31688, 3)) {
        func_00317420(0xC);
        D_01F70910_hospital_f_03 = 0;
        D_1D31688 |= 8;
    }
    switch (D_01F70910_hospital_f_03) {
        
        case 0:
            func_00190A20(5);
            D_01F70910_hospital_f_03 = 1;
    
        case 1:
            if (func_00190C00() == 0) {
                return 0;
            }
            
            func_00317490(0xC, 0.2f);        
            SeCall(1.0f, 0.0f, 0x2B21);
            D_1D31680 |= 0x80;
            D_01F70910_hospital_f_03 = 2;  
        
        case 2:
            if (func_0016C1C0(0x26) == 0) {
                return 0;
            }
            func_0016C3C0();
            func_003174B0(0.2f);
            D_01F70910_hospital_f_03 = 3;
            break;
        
        case 3:
            func_00190A20(6);
            D_01F70910_hospital_f_03 = 4;
    
        case 4:
            if (func_00190C00() == 0) {
                return 0;
            }
            D_01F70910_hospital_f_03 = 5;
        
        default:
            D_1D31688 &= ~8;
            func_00190A20(0);
            ret = 1;        
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_03", func_01F6D840_hospital_f_03);

void func_01F6D940_hospital_f_03(void) {
    func_0016C540(&D_01F70580_hospital_f_03, &D_01F705E0_hospital_f_03);
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_03", func_01F6D960_hospital_f_03);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_03", func_01F6D9F0_hospital_f_03);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_03", func_01F6DC20_hospital_f_03);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_03", func_01F6DC50_hospital_f_03);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_03", func_01F6DC70_hospital_f_03);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_03", func_01F6DCB0_hospital_f_03);

int func_01F6DFA0_hospital_f_03(void) {
    int ret;

    ret = 0;
    if (!GET_BIT(D_1D31684, 0x1D)) {
        D_01F70908_hospital_f_03 = 1;
        func_0016C3C0();
        D_1D31684 |= 0x20000000;
        func_00190A20(5);
    }
    switch (D_01F70908_hospital_f_03) {
        case 1:
            if (func_00190C00() == 0) {
                return 0;
            }
            D_01F70908_hospital_f_03 = 2;
        case 2:
            if (func_0016BED0(0x34, 0x23) == 0) {
                return 0;
            }
            D_01F70908_hospital_f_03 = 3;
            break;
        case 3:
            func_00190A20(6);
            D_01F70908_hospital_f_03 = 4;
        case 4:
            if (func_00190C00() == 0) {
                return 0;
            }
            D_01F70908_hospital_f_03 = 5;
        default:
            D_1D31684 &= 0xDFFFFFFF;
            D_1D316F4 |= 0x800000;
            func_00190A20(0);
            ret = 1;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_03", func_01F6E110_hospital_f_03);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_03", func_01F6E3B0_hospital_f_03);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_03", func_01F6E440_hospital_f_03);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_03", func_01F6E490_hospital_f_03);

void func_01F6E650_hospital_f_03(unk_struct* arg0) {
    int temp_a1;

    func_01F6E3B0_hospital_f_03();
    func_01F6E440_hospital_f_03(arg0);
    temp_a1 = arg0->unk934;
    if (temp_a1 != 0xF) {
        func_01F6E490_hospital_f_03(arg0, temp_a1);
    }
}

void func_01F6E6A0_hospital_f_03(int arg0) {
    func_001DE5B0(&func_01F6E650_hospital_f_03, arg0, 1);
}
INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_03", func_01F6E6C0_hospital_f_03);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_03", func_01F6E7E0_hospital_f_03);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_03", func_01F6E900_hospital_f_03);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_03", func_01F6EF30_hospital_f_03);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_03", func_01F6EF40_hospital_f_03);

void func_01F6F5D0_hospital_f_03(void) {
    int count;
    D_01F70890_hospital_f_03 = 0;
    if (!GET_BIT(D_1D31680, 0x1E)) {
        func_01F6FC10_hospital_f_03();
        D_1D31680 |= 0x40000000;
    }
    switch (RoomName()) {
        case 0xB8:
            count = 0;
            if (GET_BIT(D_1D31684, 0xF)) {
                count += 1;
            }
            if (GET_BIT(D_1D31684, 0x12)) {
                count += 1;
            }
            if (GET_BIT(D_1D31684, 0x15)) {
                count += 1;
            }
            if ( GET_BIT(D_1D31684, 0x19)) {
                count += 1;
            }
            if (GET_BIT(D_1D31684, 0x1C)) {
                count += 1;
            }
            if ((count >= 2) && !GET_BIT(D_1D31688, 2) && !GET_BIT(D_1D31644, 5) && !GET_BIT(D_1D31684, 0x1F)) {
                D_1D31684 |= 0x40000000;
                break;
            }
            D_1D31684 &= 0xBFFFFFFF;
            break;
        case 0xB9:
            D_1D31724 |= 0x200000;
            if (!GET_BIT(D_1D31684, 8) && !GET_BIT(D_1D31684, 9) && !GET_BIT(D_1D31684, 0xA)) {
                D_1D31684 |= 0x100;
                break;
            }
            break;
        case 0xB6:
            func_01F6EF30_hospital_f_03();
            break;
        case 0xB5:
            D_01F708D0_hospital_f_03 = 0;
            D_1D31724 |= 0x8000;
            D_1D31724 |= 0x20000;
            D_01F708E0_hospital_f_03 = 0xBFA0D97C;        
            D_01F708D8_hospital_f_03 = 0x3DD67750;
    
            if (GET_BIT(D_1D31680, 0x1A)) {
                D_1D31680 |= 0x08000000;
                break;
            }
            break;
        case 0xB7:
            if ((func_00199C70(6) != 0) && !GET_BIT(D_1D31688, 0x12)) {
                D_1D31688 |= 0x40000;
            } else {
                D_1D31688 &= 0xFFFBFFFF;
            }
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_03", func_01F6F890_hospital_f_03);

void func_01F6F930_hospital_f_03(void) {

    if (D_01F70890_hospital_f_03 == 0) {
        func_01F6F890_hospital_f_03();
    }

    switch (RoomName()) {
        case 0xB5:
            func_01F6E110_hospital_f_03();
            if (!GET_BIT(D_1D31680, 7)) {
                func_0016CA40(1);
                D_1D31724 |= 0x10000;
            } else {
                D_1D31724 &= 0xFFFEFFFF;
            }
            break;
        case 0xB6:
            if (!GET_BIT(D_1D31680, 0x19)) {
                func_01F6EF40_hospital_f_03();
                func_0016CA40(1);
            }
            if (!GET_BIT(D_1D31644, 0xC)) {
                D_1D31724 |= 0x40000;
            } else {
                D_1D31724 &= 0xFFFBFFFF;
            }
            break;
        case 0xB8:
            if (GET_BIT(D_1D31684, 0x1E)) {
                func_0016CA40(1);
                D_1D31724 |= 0x100000;
            } else {
                D_1D31724 &= 0xFFEFFFFF;
            }
            break;
    }
}

void func_01F6FAC0_hospital_f_03(void) {
    int numbers[9];
    int i, j;
    int index;
    u_int *temp = D_01D31640;

    D_1D318E4 = 0;

    for (i = 0; i < 9; i++) {
        numbers[i] = i + 1;
    }

    // takes whatever is in temp[0xA9] and sets 4 numbers in it
    // each number is placed in a 4-bit big segment
    // i.e. if the numbers 1, 5, 8 and 3 were set it'd basically be
    // 0b0001 0b0101 0b1000 0b0011
    // the whole value being 0b0001010110000011
    for (i = 0; i < 4; i++) {
        int rand = shRandI();
        index = rand % (9-i);
        temp[0xA9] <<= 4;
        temp[0xA9] += numbers[index];
        for (j = index; j < 8 - i; j++) {
            numbers[j] = numbers[j + 1];
        }
    }
}

int func_01F6FC10_hospital_f_03(void) {
    if (!GET_BIT(D_1D31684, 2)) {
        func_01F6FAC0_hospital_f_03();
        D_1D31684 |= 4;
    }
}

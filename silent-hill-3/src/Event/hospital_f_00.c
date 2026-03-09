#include "hospital_f_00.h"

int func_01F6D680_hospital_f_00(void) {
    if (!((D_1D31680 >> 2) & 1)) {
        func_0016CD00(&D_01F6F920_hospital_f_00);
        D_1D31680 |= 4;
        func_00190A20(2);
    }
    if (func_0016BED0(0xBA, 0x1D) == 0) {
        return 0;
    }
    D_1D31680 &= ~4;
    func_00190A20(0);
    return 1;
}

int func_01F6D710_hospital_f_00(void) {
    func_0012CFA0();
    if (func_0012D080() == 0) {
        func_00190A20(2);
    }
    func_0012CFC0();
    if (func_0016BED0(0x2E, 0x25) == 0) {
        return 0;
    }
    D_1D316F4 |= 0x20000;
    func_00190A20(0);
    return 1;
}

int func_01F6D790_hospital_f_00(void) {
    func_0012CFA0();
    if (func_0012D080() == 0) {
        func_00190A20(2);
    }
    func_0012CFC0();
    if (func_0016BED0(0x2F, 0x28) == 0) {
        return 0;
    }
    D_1D316F4 |= 0x40000;
    func_00190A20(0);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_00", func_01F6D810_hospital_f_00); //

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_00", func_01F6D920_hospital_f_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_00", func_01F6DA80_hospital_f_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_00", func_01F6DC00_hospital_f_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_00", func_01F6DDC0_hospital_f_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_00", func_01F6DF60_hospital_f_00);

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_00", func_01F6DFF0_hospital_f_00);

void func_01F6E030_hospital_f_00(int arg0) {
    func_001DE5B0(&func_01F6DFF0_hospital_f_00, arg0, 1);
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_00", func_01F6E050_hospital_f_00);

void func_01F6E3C0_hospital_f_00(void) {
    SubCharacter *scp;
    int var_s0;
    int *var_s1;
    var_s0 = 0;
    for (var_s1 = &D_01F6F9C0_hospital_f_00; *var_s1 != 0; var_s1++) {
        scp = shCharacterGetSubCharacter(NURSE_CHARA_ID , *var_s1);
        if (scp == 0) {
            continue;
        }
        if (func_001E2110(scp) == 0) {
            var_s0 += 1;
        }
        if ((*var_s1 == 0x11B) || (*var_s1 == 0x11C)) {
            continue;
        }
        if (!((D_1D31680 >> 9) & 1)) {
            shCharacter_Manage_Delete(NURSE_CHARA_ID , *var_s1);
        } else if (1 < var_s0) {
            shCharacter_Manage_Delete(NURSE_CHARA_ID , *var_s1);
        }
    }
}

int func_01F6E490_hospital_f_00(void) {
    int ret;

    ret = 0;
    
    if (!((D_1D31688 >> 4) & 1)) {
        D_01F6FA88_hospital_f_00 = 0;
        D_1D31688 |= 0x10;
        D_01F6FA90_hospital_f_00 = 0.0f;
        func_001C2290(3, 1.5f);
        func_0016C1A0();
        SeCall(1.0f, 0.0f, 0x4A59);
    }
    
    D_01F6FA90_hospital_f_00 += shGetDT();
    
    switch (D_01F6FA88_hospital_f_00) {
        
        case 0:
            if (D_01F6FA90_hospital_f_00 < 0.5f) {
                return 0;
            }
            SeCall(1.0f, 0.0f, 0x4A58);
            D_01F6FA88_hospital_f_00 += 1;
        
        case 1:
            if (D_01F6FA90_hospital_f_00 < 1.5f) {
                return 0;
            }
            func_0016C1B0();
            D_01F6FA88_hospital_f_00 += 1;
            break;    
        
        default:
            ret = 1;
            D_1D31688 &= ~0x10;
            D_1D3171C |= 0x80000000;
            D_1D31684 |= 0x100;
            D_1D317B4 |= 0x8000;
    }
    return ret;
}

void func_01F6E640_hospital_f_00(void) {

    if (!((D_1D31680 >> 0x1F) & 1)) {
        func_01F6EB00_hospital_f_00();
        D_1D31680 |= 0x80000000;
    }
    if (!((D_1D31688 >> 0x19) & 1)) {
        func_00316C50(0);
        func_0016ECE0(4);
        D_1D31688 |= 0x02000000;
    }
    D_01F6FA98_hospital_f_00 = 0;

    switch (RoomName()) { 

        case HOSPITAL_1F_RECEPTION:
            D_1D31720 |= 2;
            break;
        
        case HOSPITAL_1F_VISITING_ROOM:
            if (!((D_1D31684 >> 0xC) & 1) && !((D_1D31644 >> 5) & 1)) {
                D_1D31684 |= 0x800;
                break;
            }
            D_1D31684 &= ~0x800;
            break;
        
        case HOSPITAL_1F_C4_ROOM:
            if (((D_1D31684 >> 0xC) & 1) && !((D_1D31684 >> 0xF) & 1) && !((D_1D31688 >> 2) & 1) && !((D_1D31644 >> 5) & 1) && !((D_1D31684 >> 0xE) & 1)) {
                D_1D31684 |= 0x2000;
                D_1D31684 |= 0x4000;
            } else {
                D_1D31684 &= ~0x2000;
            }
    
            if ((D_1D3168C >> 9) & 1) {
                D_01F6FAC0_hospital_f_00 = 0;
                return;
            }
            break;
        
        case HOSPITAL_1F_DOCTORS_LOUNGE:
            D_1D31720 |= 8;
            break;
    }
}

void func_01F6E850_hospital_f_00(void) {
    D_01F6FA98_hospital_f_00 = 1;

    switch (RoomName()) {
        case HOSPITAL_1F:
            func_01F6E3C0_hospital_f_00();
            break;
    }
    
}

INCLUDE_ASM("asm/nonmatchings/Event/hospital_f_00", func_01F6E890_hospital_f_00);

void func_01F6E900_hospital_f_00(void) {

    if (D_01F6FA98_hospital_f_00 == 0) {
        func_01F6E850_hospital_f_00();
    }

    switch (RoomName()) {

        case HOSPITAL_1F_RECEPTION:
            if (!((D_1D31680 >> 3) & 1)) {
                func_0016CA40(1);
                D_1D31720 |= 4;
            } else {
                D_1D31720 &= ~4;
            }
    
            func_01F6E890_hospital_f_00();
            break;
        
        case HOSPITAL_1F_VISITING_ROOM:
            if ((D_1D31684 >> 0xB) & 1) {
                func_0016CA40(1);
                D_1D31720 |= 0x10;
                D_1D31720 |= 0x20;
                break;
            }
            D_1D31720 &= ~0x10;
            D_1D31720 &= ~0x20;
            break;
        
        case HOSPITAL_1F_C4_ROOM:
            if ((D_1D31684 >> 0xD) & 1) {
                func_0016CA40(1);
                D_1D31720 |= 0x100;
            } else {
                D_1D31720 &= ~0x100;
            }
            if (!((D_1D31680 >> 9) & 1)) {
                func_0016CA40(2);
                D_1D31720 |= 0x200;
            } else {
                D_1D31720 &= ~0x200;
            }
    
            if (!((D_1D3168C >> 9) & 1)) {
                func_0016CA40(7);
                break;
            }
            func_0016CA40(8);
            break;
    }
}

void func_01F6EB00_hospital_f_00(void) {
    return;
}

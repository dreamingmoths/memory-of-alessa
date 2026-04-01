#include "hospital_f_00.h"

int func_01F6D680_hospital_f_00(void) {
    if (!GET_BIT(D_1D31680, 2)) {
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

int func_01F6D810_hospital_f_00(void) {

    int var_a0;
    int temp_v1;

    if (!GET_BIT(D_1D31688, 0xE)) {
        D_1D31688 |= 0x4000;
        func_00190A20(2);
    }
    
    if (GET_BIT(D_1D31644, 5)) {
        var_a0 = 0x20;
        temp_v1 = 0x5AA;
    } else {
        var_a0 = 0x1E;
        if (GET_BIT(D_1D31684, 0xC)) {
            var_a0 = 0x1F;
            temp_v1 = 0x5AA;
        } else {
            temp_v1 = 0x5AA;
        }
    }
    
    if (func_0016C1C0(var_a0) == 0) {
        return 0;
    }
    
    if (!GET_FLAG(D_01D31640, temp_v1)) {
        D_01D31640[temp_v1 >> 5] |= (1 << (temp_v1 & 0x1F));
    }
    func_00190A20(0);
    D_1D31688 &= ~0x4000;
    return 1;
}

int func_01F6D920_hospital_f_00(void) {
    sceVu0FVECTOR sp10;
    int t;

    if (!GET_BIT(D_1D31688, 0xD)) {
        D_01F6FA80_hospital_f_00 = 0;
        D_1D31688 |= 0x2000;
        func_00190A20(2);
    }
    t = GET_BIT(D_1D31688, 0xC) ? 0x31 : 0x30;
    switch (D_01F6FA80_hospital_f_00) {
        case 0:
        if (func_0016C1C0(t) == 0) {
            return 0;
        }
        if ((func_00168440() != 0) || ((GET_BIT(D_1D31688, 0xC)))) {
            break;
        }
            
        D_01F6FA80_hospital_f_00 += 1;
        func_0016C3C0();
        func_0018FE60((u_long128*)&sp10);
        func_0015DCD0(1.0f, 10000.0f, 0x2B21, (float*)&sp10, 0, 0);
        
        default:
        if (func_0016C1C0(0xF) == 0) {
            return 0;
        }
        ItemGet(0x12);
        D_1D31688 |= 0x1000;
    }

    D_1D31688 &= ~0x2000;
    func_00190A20(0);
    return 1;
}

int func_01F6DA80_hospital_f_00(void) {
    float temp_f20;
    int ret;

    switch(D_01F6FAC0_hospital_f_00) {
        case 0:
            func_001C2290(6, 0.0f);            
            D_1D316AC |= 0x20000000;
            D_01F6FAB8_hospital_f_00 = &D_01F6F930_hospital_f_00;
            D_01F6FAC0_hospital_f_00 += 1;
            break;
    }
    
    ret = func_0016C540(&D_01F6F940_hospital_f_00, &D_01F6F9A0_hospital_f_00);
    if (ret != 0) {
        D_1D3171C &= 0x7FFFFFFF;
        D_1D3171C &= ~0x08000000;
        func_0013D280(0);
        D_1D316AC &= 0xDFFFFFFF;
        func_001C2290(5, 0.5f);
    } else {
        temp_f20 = func_001643C0();
        while (D_01F6FAB8_hospital_f_00->unk0 > 0.0f) {
            if (D_01F6FAB8_hospital_f_00->unk0 > temp_f20) {
                break;
            }
            func_0013D250(0, D_01F6FAB8_hospital_f_00->unk4, 1.0f);
            D_01F6FAB8_hospital_f_00++;
        }
    }
    return ret;
}

int func_01F6DC00_hospital_f_00(void) {
    if (!GET_BIT(D_1D31688, 0x15)) {
        if (!GET_BIT(D_1D31680, 9) && !GET_BIT(D_1D31688, 0x14)) {
            D_01F6FAB0_hospital_f_00 = 0;
        } else {
            D_01F6FAB0_hospital_f_00 = 1;
        }
        func_0016C3C0();
        func_00190A20(2);
        if (!GET_BIT(D_1D31680, 9)) {
            D_01F6FAA8_hospital_f_00 = 0x27;
            if (!GET_BIT(D_1D31688, 0x14)) {
                D_01F6FAA0_hospital_f_00 = 0x21;
            } else {
                D_01F6FAA0_hospital_f_00 = 0x22;
            }
        } else {
            D_01F6FAA8_hospital_f_00 = 0x28;
            D_01F6FAA0_hospital_f_00 = 0x24;
        }
        D_1D31688 |= 0x200000;
    }

    switch (D_01F6FAB0_hospital_f_00) {
        case 0:
            if (func_0016C1C0(0x23) == 0) {
                return 0;
            }
            func_0016C3C0();
            D_1D31688 |= 0x100000;
            D_01F6FAB0_hospital_f_00 += 1;
    }

    if (func_0016BED0(D_01F6FAA8_hospital_f_00, D_01F6FAA0_hospital_f_00) == 0) {
        return 0;
    }
    D_1D317B8 |= 0x2000;
    D_1D31688 &= ~0x200000;
    func_00190A20(0);
    return 1;
}

void func_01F6DDC0_hospital_f_00(PictureGroup *arg0) {
    PictureLoad *temp_s2 = &arg0->unk10;
    Picture *temp_s0 = &arg0->unk64;

    temp_s2->unk00 = func_00170410(0);
    temp_s2->unk04 = -1;
    temp_s2->unk08 = -1;
    temp_s2->unk0C = 2;
    PictureLoadImage(temp_s2);

    shQzero(temp_s0, 0x44);
    temp_s0->unk00 = func_00170410(0);
    temp_s0->unk04 = -1;
    temp_s0->unk08 = -1;
    temp_s0->unk42 |= 1;
    temp_s0->unk1C = 0;
    temp_s0->unk20 = 0;
    temp_s0->unk24 = 0x800;
    temp_s0->unk28 = 0xC00;
    temp_s0->unk42 &= ~8;
    temp_s0->unk42 |= 4;
    temp_s0->unk0C = -0x3C0;
    temp_s0->unk0E = -0x5E0;
    temp_s0->unk10 = 0x440;
    temp_s0->unk12 = -0x5E0;
    temp_s0->unk42 |= 2;
    temp_s0->unk14 = -0x3C0;
    temp_s0->unk16 = 0x620;
    temp_s0->unk18 = 0x440;
    temp_s0->unk1A = 0x620;
    temp_s0->unk42 |= 0x80;
    temp_s0->unk2C = 0x80;
    temp_s0->unk2D = 0x80;
    temp_s0->unk2E = 0x80;
    temp_s0->unk42 |= 0x10;
    temp_s0->unk2F = arg0->unkB0;
    temp_s0->unk30 = 0;
    temp_s0->unk31 = 1;
    temp_s0->unk32 = 0;
    temp_s0->unk33 = 1;
    temp_s0->unk34 = 0;
    temp_s0->unk42 |= 0x20;
    temp_s0->unk35 = 1;
    temp_s0->unk36 = 6;
    temp_s0->unk37 = 0;
    temp_s0->unk38 = 0;
    temp_s0->unk39 = 0;
    temp_s0->unk3A = 0;
    temp_s0->unk3B = 1;
    temp_s0->unk3C = 1;
    temp_s0->unk42 |= 0x40;
    temp_s0->unk40 = 3;
    PictureDraw(temp_s0);
}

void func_01F6DF60_hospital_f_00(PictureGroup *arg0) {
    Picture *temp_s0 = &arg0->unk20;

    arg0->unk00.unk00 = func_00170410(1);
    arg0->unk00.unk04 = -1;
    arg0->unk00.unk08 = -1;
    arg0->unk00.unk0C = 0;
    PictureLoadImage(&arg0->unk00);

    shQzero(temp_s0, 0x44);
    temp_s0->unk00 = func_00170410(1);
    temp_s0->unk04 = -1;
    temp_s0->unk08 = -1;
    temp_s0->unk42 |= 1;
    temp_s0->unk40 = 1;
    PictureDraw(temp_s0);
}

void func_01F6DFF0_hospital_f_00(PictureGroup *arg0) {
    func_01F6DF60_hospital_f_00(arg0);
    if (arg0->unkB0 != 0) {
        func_01F6DDC0_hospital_f_00(arg0);
    }
}

void func_01F6E030_hospital_f_00(PictureGroup *arg0) {
    func_001DE5B0(func_01F6DFF0_hospital_f_00, arg0, 1);
}

int func_01F6E050_hospital_f_00(void) {
    float var_f12;
    float var_f12_2;
    PictureGroup *temp_s0;

    temp_s0 = (PictureGroup*) func_00156410(9);

    if (!GET_BIT(D_1D31680, 8)) {
        shQzero(temp_s0, 0xB4);
        temp_s0->unkB0 = 0x80;
        func_0016C3C0();
        D_1D31680 |= 0x100;
    }

    switch (temp_s0->unkA8) {
        case 0:
            func_0016BBF0();
            func_0016C1A0();
            func_0016F550(0x28, 1);
            func_0016F550(0x29, 0);
            if (func_00151150(0, 1) != 0) {
                var_f12 = 0.8f;
            } else {
                var_f12 = 1.2f;
            }
            func_001C2290(3, var_f12);
            temp_s0->unkA8 = 1U;
        case 1:
            if ((func_00151150(0, 1) != 0) && (func_001C2580(2) != 0)) {
                func_001C2290(5, 0.8f);
                temp_s0->unkA8 = 2U;
            }
            break;
        case 2:
            func_01F6E030_hospital_f_00(temp_s0);
            if (func_001C2580(4) != 0) {
                temp_s0->unkA8 = 3U;
            }
            break;
        case 3:
            func_01F6E030_hospital_f_00(temp_s0);
            if (func_0013D080(0, 0, 1, 0x80000) != 0) {
                temp_s0->unkA8 = 4U;
            }
            break;
        case 4:
            func_01F6E030_hospital_f_00(temp_s0);
            func_0016BC00(1);
            if (func_0016C1C0(0x37) != 0) {
                func_0016C3C0();
                temp_s0->unkA8 = 5U;
                SeCall(1.0f, 0.0f, 0x3840);
            }
            break;
        case 5:
            if (temp_s0->unkAC < 8) {
                temp_s0->unkAC += 1;
                temp_s0->unkB0 = (8 - temp_s0->unkAC) * 128 / 8;
            } else {
                temp_s0->unkB0 = 0;
                temp_s0->unkA8 = 6U;
                SeCall(1.0f, 0.0f, 0x2B21);
            }
            func_01F6E030_hospital_f_00(temp_s0);
            func_0016BC00(1);
            break;
        case 6:
            func_01F6E030_hospital_f_00(temp_s0);
            func_0016BC00(1);
            if (func_0016C1C0(0x38) != 0) {
                func_0016C3C0();
                temp_s0->unkA8 = 7U;
            }
            break;
        case 7:
            func_01F6E030_hospital_f_00(temp_s0);
            func_0016BC00(1);
            if (func_00151150(0, 1) != 0) {
                var_f12_2 = 0.8f;
            } else {
                var_f12_2 = 1.2f;
            }
            func_001C2290(3, var_f12_2);
            if (func_001C2580(2) != 0) {
                temp_s0->unkA8 = 8U;
            }
            break;
        default:
            func_0016C1B0();
            func_001C2290(5, 0.8f);
            if (GET_BIT(D_1D317B8, 0xD)) {
                D_1D317B8 |= 0x4000;
            }
            D_1D317B8 |= 0x2000;
            D_1D31680 &= ~0x100; //???
            return 1;
    }
    return 0;
}


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
        if (!GET_BIT(D_1D31680, 9)) {
            shCharacter_Manage_Delete(NURSE_CHARA_ID , *var_s1);
        } else if (1 < var_s0) {
            shCharacter_Manage_Delete(NURSE_CHARA_ID , *var_s1);
        }
    }
}

int func_01F6E490_hospital_f_00(void) {
    int ret;

    ret = 0;
    
    if (!GET_BIT(D_1D31688, 4)) {
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

    if (!GET_BIT(D_1D31680, 0x1F)) {
        func_01F6EB00_hospital_f_00();
        D_1D31680 |= 0x80000000;
    }
    if (!GET_BIT(D_1D31688, 0x19)) {
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
            if (!GET_BIT(D_1D31684, 0xC) && !GET_BIT(D_1D31644, 5)) {
                D_1D31684 |= 0x800;
                break;
            }
            D_1D31684 &= ~0x800;
            break;
        
        case HOSPITAL_1F_C4_ROOM:
            if (GET_BIT(D_1D31684, 0xC) && !GET_BIT(D_1D31684, 0xF) && !GET_BIT(D_1D31688, 2) && !GET_BIT(D_1D31644, 5) && !GET_BIT(D_1D31684, 0xE)) {
                D_1D31684 |= 0x2000;
                D_1D31684 |= 0x4000;
            } else {
                D_1D31684 &= ~0x2000;
            }
    
            if (GET_BIT(D_1D3168C, 9)) {
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

void func_01F6E890_hospital_f_00(void) {
    Q sp10;
    Q sp20;
    Q sp30;

    sp10 = D_01F6F9D0_hospital_f_00;
    sp20 = D_01F6F9E0_hospital_f_00;
    sp30 = D_01F6F9F0_hospital_f_00;
    
    if (func_0019B580(2) == 0) {
        func_001C7BC0(&sp20, &sp10, &sp30, 0x200);
    }
}

void func_01F6E900_hospital_f_00(void) {

    if (D_01F6FA98_hospital_f_00 == 0) {
        func_01F6E850_hospital_f_00();
    }

    switch (RoomName()) {

        case HOSPITAL_1F_RECEPTION:
            if (!GET_BIT(D_1D31680, 3)) {
                func_0016CA40(1);
                D_1D31720 |= 4;
            } else {
                D_1D31720 &= ~4;
            }
    
            func_01F6E890_hospital_f_00();
            break;
        
        case HOSPITAL_1F_VISITING_ROOM:
            if (GET_BIT(D_1D31684, 0xB)) {
                func_0016CA40(1);
                D_1D31720 |= 0x10;
                D_1D31720 |= 0x20;
                break;
            }
            D_1D31720 &= ~0x10;
            D_1D31720 &= ~0x20;
            break;
        
        case HOSPITAL_1F_C4_ROOM:
            if (GET_BIT(D_1D31684, 0xD)) {
                func_0016CA40(1);
                D_1D31720 |= 0x100;
            } else {
                D_1D31720 &= ~0x100;
            }
            if (!GET_BIT(D_1D31680, 9)) {
                func_0016CA40(2);
                D_1D31720 |= 0x200;
            } else {
                D_1D31720 &= ~0x200;
            }
    
            if (!GET_BIT(D_1D3168C, 9)) {
                func_0016CA40(7);
                break;
            }
            func_0016CA40(8);
            break;
    }
}

int func_01F6EB00_hospital_f_00(void) {

}

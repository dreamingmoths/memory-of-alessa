#include "Event/stage/mall_b_02.h"

#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"

#include "SH3_common/sh3dt.h"
#include "SH3_common/sh_vu0.h"

extern void func_001603E0(int, int);
extern int func_001C2580(int);
extern void func_0012EA40(void);
extern void func_0013D280(int);
extern int func_00190240(void); // @note: this comes from m3_play_event, might be worth it to check what this is
extern void func_001C2290(int, float);
extern void func_001EC5C0(int);
extern void func_001EC5E0(int); 
extern void func_001EC610(int);
extern void func_001EC630(int);
extern int func_00190A20(int);
extern void ItemGet(u_int); // (int kind) in sh2
extern void func_003174B0(float);
extern int func_00168440(void);
extern int func_0016C1C0(int);
extern void func_00317490(int, float);
extern int SeCall(float, float, int);
extern void func_00317420(int);
extern void func_0016C3C0(void);
extern void func_0018FE60(u_long128*);
extern void func_0016C1B0(void);
extern void func_0016C1A0(void);
extern int func_0015DCD0(float, float, int, float*, int, int);
extern int RoomName(void);
extern void func_0016CA40(int);
extern void func_0016CBD0(sceVu0FMATRIX*[], sceVu0FMATRIX*[], int);
extern void func_001C2A80(int, sceVu0FMATRIX*);
extern int func_0016C540(float*, float*);
extern void func_001DC9E0(SubCharacter*, int);
extern void func_001E22F0(int, int, int);
extern void func_0013D250(int, int*, float);
extern void func_001602D0(int, int, int, float);
extern float func_001643C0(void);
extern int func_001646C0(void);

// data

extern unk_01F6E770_mall_b_02_struct D_01F6E770_mall_b_02;

extern float D_01F6E7A0_mall_b_02;

extern float D_01F6E800_mall_b_02;

// bss
extern int D_01F6E880_mall_b_02;

extern int D_01F6E888_mall_b_02;

extern unk_01F6E890_mall_b_02_struct D_01F6E890_mall_b_02; 

extern int D_01F6E8B0_mall_b_02;

extern unk_01F6E770_mall_b_02_struct* D_01F6E8B8_mall_b_02;

extern int D_01F6E8C0_mall_b_02;

int func_01F6D680_mall_b_02(void) {
    SubCharacter* split_worm;
    float temp_f0;
    float temp_f2;
    int ret;

    switch (D_01F6E8C0_mall_b_02) {
        case 0:
            func_001C2290(2, 0.0f);
            split_worm = shCharacterGetSubCharacter(SPLIT_WORM_CHARA_KIND, 0x5B);
            func_001E22F0(SPLIT_WORM_CHARA_KIND, 0x5B, 0);
            func_001DC9E0(split_worm, 0);
            D_01F6E8B8_mall_b_02 = &D_01F6E770_mall_b_02;
            func_00190A20(2);
            D_01F6E8C0_mall_b_02++;            
    }

    ret = func_0016C540(&D_01F6E7A0_mall_b_02, &D_01F6E800_mall_b_02);
    temp_f0 = func_001643C0();
    temp_f2 = D_01F6E8B8_mall_b_02->unk0;
    if ((temp_f2 > 0.0f) && (temp_f2 <= temp_f0)) {
        func_0013D250(0, D_01F6E8B8_mall_b_02->unk4, 1.0f);
        D_01F6E8B8_mall_b_02++;
    }
    if (ret != 0) {
        split_worm = shCharacterGetSubCharacter(SPLIT_WORM_CHARA_KIND, 0x5B);
        func_001E22F0(SPLIT_WORM_CHARA_KIND, 0x5B, 1);
        func_001DC9E0(split_worm, 1);
        func_00190A20(0);
        func_001C2290(5, 0.5f);
        func_0013D280(0);
        if (func_001646C0()) {
            func_001602D0(0x2738, 3, 1, 1.0f);
        }
    }
    return ret;
}

int func_01F6D820_mall_b_02(void) {
    if (!(D_1D31658 & 1)) {
        func_00317420(0x2F);
        D_01F6E880_mall_b_02 = 0;
        D_1D31658 |= 1;
        func_00190A20(2);
    }

    switch (D_01F6E880_mall_b_02) {
        case 0:
            if (!func_0016C1C0(0x1A)) {
                return 0;
            }
            if (func_00168440()) {
                break;
            }
            D_01F6E880_mall_b_02++;
            func_00317490(0x2F, 0.2f);
            D_1D31658 |= 2;
            func_0016C3C0();
            SeCall(1.0f, 0.0f, 0x2B21);

        default:
            if (!func_0016C1C0(0x21)) {
                return 0;
            }
            func_003174B0(0.2f);
            ItemGet(0x2FU);
    }
    func_00190A20(0);
    D_1D31658 &= ~1;
    return 1;
}

int func_01F6D970_mall_b_02(void) {
    if (!((D_1D31658 >> 2) & 1)) {
        D_01F6E888_mall_b_02 = 0;
        D_1D31658 |= 4;
        func_00190A20(2);
    }
    switch (D_01F6E888_mall_b_02) {
        case 0:
            if (!func_0016C1C0(0)) {
                return 0;
            }
            if (func_00168440()) {
                break;
            }
            D_01F6E888_mall_b_02++;
            func_0016C3C0();

        default:
            if (!func_0016C1C0(0x19)) {
                return 0;
            }
    }
    func_00190A20(0);
    if (!((D_1D31794 >> 8) & 1)) {
        D_1D31794 |= 0x100;
    }
    D_1D31658 &= ~4;
    return 1;
}

int func_01F6DA80_mall_b_02(void) {
    sceVu0FVECTOR  sp10;

    switch (D_01F6E8B0_mall_b_02) {
        case 0:
            func_0018FE60((u_long128*)&sp10);
            SeCall(1.0f, 0.0f, 0x3070);
            func_001C2290(3, 0.5f);
            func_0016C1A0();
            D_1D31658 |= 8;
            func_00190A20(2);
            D_01F6E8B0_mall_b_02++;
            /* fallthrough */
        case 1:
            if (!func_001C2580(2)) {
                return 0;
            }
            func_001C2290(5, 0.5f);
            func_0016C1B0();
            D_01F6E8B0_mall_b_02++;
        default:
            if (!func_0016C1C0(0x22)) {
                return 0;
            }
            func_0018FE60((u_long128*)&sp10);
            func_0015DCD0(1.0f, 10000.0f, 0x4A51, sp10, 0, 0);
            func_00190A20(0);
            return 1;
    }
}

int func_01F6DBC0_mall_b_02(void) {
    unk_01F6E890_mall_b_02_struct* p = &D_01F6E890_mall_b_02;   
    switch (p->unk8) {
        case 0:
            func_001603E0(2, 1);
            func_001EC5C0(1);
            func_001EC610(0);
            func_001EC630(0);
            func_0012EA40();
            p->unk10[1] = 0.0f;
            p->unk10[2] = 9.0f;
            p->unk8++;
            /* fallthrough */
        
        case 1:
            p->unk10[1] += shGetDT();
            p->unk10[0] = (30.0f * p->unk10[1]) / 2.0f;
            if (p->unk10[0] > 30.0f) {
                p->unkC = 30;
            } else {                
                p->unkC = p->unk10[0];
            }                        
            func_001EC5E0(p->unkC);
            if (func_00190240()) {
                func_001EC5C0(0);
                D_1D316AC &= ~0x20000000;
                return 1;
            }
            if (p->unk10[1] < p->unk10[2]) {
                return 0;
            }
            func_001C2290(8, 3.0f);
            D_1D316AC |= 0x20000000;
            p->unk8++;
        
        default:
            func_001EC5E0(p->unkC);
            if (!func_001C2580(2)) {
                return 0;
            }
            D_1D31658 |= 0x20;
            func_001EC5C0(0);
            D_1D316AC &= ~0x20000000;
            func_0013D280(0);
            return 1;
    }
}

int func_01F6DDA0_mall_b_02(void) {
    return D_01F6E890_mall_b_02.unk4;
}

void func_01F6DDB0_mall_b_02(int arg0) {
    D_01F6E890_mall_b_02.unk4 = arg0;
}

void func_01F6DDC0_mall_b_02(void) {
    shQzero(&D_01F6E890_mall_b_02, sizeof(unk_01F6E890_mall_b_02_struct)); // 0x1C
    func_01F6DDB0_mall_b_02(1);
}

void func_01F6DDF0_mall_b_02(void) {
    if ((func_01F6DDA0_mall_b_02() == 2) && !(((D_1D31658 >> 0xE) & 1))) {
        D_1D31658 |= 0x4000;
    }
}

void func_01F6DE40_mall_b_02(void) {
    switch (RoomName()) { // @todo: add room id                            
        case 42:
            D_01F6E8B0_mall_b_02 = 0;
            break;
        
        case 45:
            func_01F6DDC0_mall_b_02();
            if (!((D_01D31640 >> 0xA) & 1)) {
                func_00316C50(0);
                if ((D_1D31658 >> 4) & 1) {
                    func_001C2290(2, 0.0f);
                    D_01F6E8C0_mall_b_02 = 0;
                }
            }
        
    }
}

void func_01F6DEE0_mall_b_02(void) { // I have no idea how I matched this
    sceVu0FMATRIX* sp10[4];
    sceVu0FMATRIX* sp20[4];
    sceVu0FMATRIX sp30;
    
    switch (RoomName()) { // @todo: add room id 
        case 42:
            if ((D_1D31658 >> 3) & 1) {
                func_0016CA40(1);
            }
            break;
        case 45:
            if ((D_01D31640 >> 0xA) & 1) {
                func_0016CBD0(sp10, sp20, 4);
                mat_copy(sp30, sp10[0]);    
                func_001C2A80(1, sp30);
                
                func_0016CBD0(sp10, sp20, 5);
                mat_copy(sp30, sp10[0]);    
                func_001C2A80(2, sp30);
                
                func_0016CA40(1);
            }
            func_01F6DDF0_mall_b_02();
            break;
        
        case 43:
            if (!(((D_1D31658 >> 1) & 1))) {
                func_0016CA40(1);
                D_1D31708 |= 2;
            } else {
                D_1D31708 &= ~2;
            }
    }
}

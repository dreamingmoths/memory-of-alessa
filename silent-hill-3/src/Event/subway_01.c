#include "subway_01.h"

int func_01F6D680_subway_01(void)
{
    return 0x1;
}

int func_01F6D690_subway_01(void)
{
    int var_s0 = 0;
    
    switch (D_01F70700_subway_01)
    {
        case 0:
            func_00190A20(2);
            D_01F70700_subway_01 += 1;
        case 1:
            if (func_0016CED0(0x4F, 0x1D, &D_01F70370_subway_01) != 0)
            {
                func_00190A20(0);
                var_s0 = 1;
                D_01F70700_subway_01 = 0;
            }
            
            break;
    }
    
    return var_s0;
}

INCLUDE_ASM("asm/nonmatchings/Event/subway_01", func_01F6D720_subway_01);

INCLUDE_ASM("asm/nonmatchings/Event/subway_01", func_01F6DAA0_subway_01);

INCLUDE_ASM("asm/nonmatchings/Event/subway_01", func_01F6DBE0_subway_01);

INCLUDE_ASM("asm/nonmatchings/Event/subway_01", func_01F6DD70_subway_01);

INCLUDE_ASM("asm/nonmatchings/Event/subway_01", func_01F6DF90_subway_01);

INCLUDE_ASM("asm/nonmatchings/Event/subway_01", func_01F6E100_subway_01);

void func_01F6E270_subway_01(void)
{
    int id;
    int* var_s0 = &D_01F70650_subway_01;

    D_1D3165C |= 0x8000;
    
    while (id = *var_s0)
    {
        shCharacter_Manage_Delete(DOUBLE_HEAD_CHARA_ID, id);
        var_s0++;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/subway_01", func_01F6E2D0_subway_01);

void func_01F6E320_subway_01(void)
{
    D_01F70700_subway_01 = 0;
    D_01F70708_subway_01 = 0;
    
    switch (RoomName())
    {
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x3A:
        case 0x3B:
        case 0x3C:
        case 0x3D:
            break;
        case 0x39:
            func_01F6E7C0_subway_01();
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/subway_01", func_01F6E380_subway_01);

void func_01F6E7C0_subway_01(void)
{
    D_01F70718_subway_01 = 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/subway_01", func_01F6E7D0_subway_01);

void func_01F6E900_subway_01(Q* arg0, int* arg1, Q* arg2, int* arg3, int* arg4)
{
    Q sp0;
    Q sp10;
    
    sp0.s32 = D_01F70660_subway_01.s32;
    sp10.s32 = D_01F70670_subway_01.s32;
    
    vec_copy(&arg0->u128, &sp0.u128);
    *arg1 = 1;
    vec_copy(&arg2->u128, &sp10.u128);
    *arg3 = 1;
    *arg4 = 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/subway_01", func_01F6E960_subway_01);

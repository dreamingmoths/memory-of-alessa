#include "subway_01.h"
#include "Chacter/m3_sc.h"

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

INCLUDE_ASM("asm/nonmatchings/Event/subway_01", func_01F6E320_subway_01);

INCLUDE_ASM("asm/nonmatchings/Event/subway_01", func_01F6E380_subway_01);

INCLUDE_ASM("asm/nonmatchings/Event/subway_01", func_01F6E7C0_subway_01);

INCLUDE_ASM("asm/nonmatchings/Event/subway_01", func_01F6E7D0_subway_01);

INCLUDE_ASM("asm/nonmatchings/Event/subway_01", func_01F6E900_subway_01);

INCLUDE_ASM("asm/nonmatchings/Event/subway_01", func_01F6E960_subway_01);

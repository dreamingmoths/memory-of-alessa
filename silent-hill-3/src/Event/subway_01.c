#include "subway_01.h"

int func_01F6D680_subway_01(void)
{
    return 1;
}

int func_01F6D690_subway_01(void)
{
    int var_s0 = 0;
    
    switch (D_01F70700_subway_01)
    {
        case 0:
            func_00190A20(2);
            ++D_01F70700_subway_01;
            /* fallthrough */
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

int func_01F6D720_subway_01(void)
{
    int var_s0 = 0;
    short temp_v1 = RoomName();
    float sp38;
    float sp3C;
    SubCharacter* var_v0;
    float temp_f0;
    float var_f12;
    SubCharacter* temp_v0;
    
    func_001908A0(&sp38, &sp3C);
    
    switch (temp_v1)
    {
        case 0x39:
            if (sp3C > 60000.0f)
            {
                D_01F70380_subway_01 = 6;
                D_01F70384_subway_01 = 7;
            }
            else
            {
                D_01F70380_subway_01 = 0xB;
                D_01F70384_subway_01 = 0xA;
            }
            
            var_v0 = shCharacterGetSubCharacter(0x1009, 0x6C);
            break;
        case 0x3A:
            D_01F70380_subway_01 = 8;
            D_01F70384_subway_01 = 7;
            var_v0 = shCharacterGetSubCharacter(0x1009, 0x6E);
            break;
        case 0x3B:
            if (sp3C > 20000.0f)
            {
                D_01F70380_subway_01 = 9;
                D_01F70384_subway_01 = 0xA;
            }
            else
            {
                D_01F70380_subway_01 = 0xC;
                D_01F70384_subway_01 = 0xD;
            }
            
            var_v0 = shCharacterGetSubCharacter(0x1009, 0x70);
            break;
        default:
            return 1;
    }

    if (var_v0 != 0)
    {
        func_001DC9E0(var_v0, 0);
    }
    
    switch (D_01F70700_subway_01)
    {
        case 0:
            func_00190A20(2);
            func_001C2290(3, 0.5f);
            SeCall(1.0f, 0.0f, 0x3139);
            func_01F6E2D0_subway_01();
            func_0013D250(0, &D_01F70180_subway_01, 1.0f);
            D_01F70700_subway_01 = 1;
            break;
        case 1:
            /* fallthrough */
        case 2:
            if (func_0016C540(&D_01F70380_subway_01, &D_01F703E0_subway_01) == 0)
            {
                temp_f0 = func_001643C0();
                
                if (D_01F70700_subway_01 == 1 && temp_f0 > 145.0f)
                {
                    func_0013D250(0, &D_01F70140_subway_01, 1.0f);
                    D_01F70700_subway_01 = 2;
                }
                
                if (func_001646C0() != 0)
                {
                    if (func_00151150(0, 1) != 0)
                    {
                        var_f12 = 0.8f;
                    }
                    else
                    {
                        var_f12 = 1.2f;
                    }
                    
                    func_001C2290(3, var_f12);
                }
            }
            else
            {
                func_0019A940();
                D_01F70700_subway_01 = 3;
            }
            
            break;
        case 3:
            if (func_0019A9B0(2.0f) != 0 || func_001646C0() != 0)
            {
                var_s0 = 1;
            }
            
            break;
    }
    
    temp_v0 = shCharacterGetSubCharacter(HEATHER_CHARA_ID, -1);
    
    if (var_s0 != 0)
    {
        func_001DC9E0(temp_v0, 1);
        func_00190C40();
        func_00190A20(0);
        func_0013D280(0);
        D_01F70700_subway_01 = 0;
    }
    else
    {
        func_001DC9E0(temp_v0, 0);
    }
    
    return var_s0;
}

int func_01F6DAA0_subway_01(void)
{
    int var_s0 = 0;
    float temp_f0;
    
    switch (D_01F70700_subway_01)
    {
        case 0:
            func_00190A20(2);
            func_001C2290(3, 0.5f);
            D_01F70740_subway_01 = &D_01F70400_subway_01;
            ++D_01F70700_subway_01;
            break;
        case 1:
            var_s0 = func_0016C540(&D_01F70420_subway_01, &D_01F70480_subway_01);
            temp_f0 = func_001643C0();
            
            if (D_01F70740_subway_01->unk0 > 0.0f && D_01F70740_subway_01->unk0 <= temp_f0)
            {
                func_0013D250(0, D_01F70740_subway_01->unk4, 1.0f);
                ++D_01F70740_subway_01;
            }
            
            break;
    }
    
    if (var_s0 != 0)
    {
        func_00190A20(0);
        func_001C2290(5, 1.2f);
        D_01F70708_subway_01 = 4;
        func_0013D280(0);
        D_01F70700_subway_01 = 0;
    }
    
    return var_s0;
}

int func_01F6DBE0_subway_01(void)
{
    int var_s0 = 0;
    SubCharacter* temp_v0;
    
    switch (D_01F70700_subway_01)
    {
        case 0:
            if (func_00190880() > 200.0f)
            {
                return 1;
            }
            
            D_1D31648 |= 0x40000;
            SeCall(1.0f, 0.0f, 0x3139);
            ++D_01F70700_subway_01;
            /* fallthrough */
        case 1:
            func_00190A20(2);
            func_001C2290(3, 0.3f);
            func_01F6E270_subway_01();
            ++D_01F70700_subway_01;
            /* fallthrough */
        case 2:
            var_s0 = func_0016C540(&D_01F704A0_subway_01, &D_01F70500_subway_01);
            
            if (var_s0 != 0)
            {
                temp_v0 = shCharacterGetSubCharacter(HEATHER_CHARA_ID, -1);
                
                temp_v0->pos.x = -12500.0f;
                temp_v0->pos.y = 0.0f;
                temp_v0->pos.z = 62000.0f;
                
                temp_v0->rot.y = -PI / 2.0f;
                
                D_01F70700_subway_01 = 0;
                D_1D3165C |= 0x4000;
                func_00190A20(0);
                func_001C2290(5, 1.2f);
                func_001BF720(0);
            }
            /* fallthrough */
        default:
            return var_s0;
    }
}

int func_01F6DD70_subway_01(void)
{
    int var_s0 = 0;
    SubCharacter* temp_s1 = shCharacterGetSubCharacter(0x1009, 0x70);
    SubCharacter* temp_s2 = shCharacterGetSubCharacter(0x1019, 0x71);
    float temp_f0;
    
    func_001DC9E0(temp_s1, 0);
    func_001DC9E0(temp_s2, 0);
    
    switch (D_01F70700_subway_01)
    {
        case 0:
            func_001C2290(3, 0.8f);
            func_00190A20(2);
            D_01F70738_subway_01 = &D_01F70520_subway_01;
            D_01F70710_subway_01 = func_0016E0F0();
            ++D_01F70700_subway_01;
            /* fallthrough */
        case 1:
            var_s0 = func_0016C540(&D_01F705C0_subway_01, &D_01F70620_subway_01);
            temp_f0 = func_001643C0();
            
            if (temp_f0 >= 396.0f)
            {
                func_0013D250(0, &D_01F70220_subway_01, 1.0f);
            }
            
            if (D_01F70738_subway_01->unk0 > 0.0f && D_01F70738_subway_01->unk0 <= temp_f0)
            {
                func_0013D250(0, D_01F70738_subway_01->unk4, 1.0f);
                ++D_01F70738_subway_01;
            }
            
            if (D_01F70738_subway_01->unk0 > 0.0f && D_01F70738_subway_01->unk0 <= temp_f0)
            {
                func_0013D250(0, D_01F70738_subway_01->unk4, 1.0f);
                ++D_01F70738_subway_01;
            }
            
            if (var_s0 != 0)
            {
                func_00190A20(0);
                func_0013D280(0);
                func_0016E400(0x22, D_01F70710_subway_01);
                D_01F70700_subway_01 = 0;
            }
            
            break;
    }
    
    return var_s0;
}

void func_01F6DF90_subway_01(void)
{
    int* id; 
    D_01F6F7D0_struct* var_s1;
    func_0016A080_struct sp30;

    D_1D3165C |= 0x1000;

    if (GET_BIT(D_1D3177C, 0x14))
    {
        return;
    }

    for (id = &D_01F70640_subway_01; *id != 0; id++)
    {
        if (shCharacterGetSubCharacter(DOUBLE_HEAD_CHARA_ID, *id) == NULL)
        {
            for (var_s1 = &D_01F6F7D0_subway_01; var_s1 != NULL && var_s1->unk0 != 0; var_s1++)
            {
                if (var_s1->unk0 == DOUBLE_HEAD_CHARA_ID && var_s1->unk2 == *id)
                {
                    break;
                }
            }

            if (var_s1 != NULL && func_0016B4E0(var_s1) != 0)
            {
                shQzero(&sp30, 0x40);

                sp30.unk4 = var_s1->unk0;
                sp30.unk6 = var_s1->unk2;
                
                sp30.unk10 = var_s1->unk4;
                sp30.unk14 = var_s1->unkC;
                sp30.unk18 = var_s1->unk8;
                
                sp30.unk24 = (PI * 2 * var_s1->unkE) / 4096.0f;
                
                sp30.unk30 = var_s1->unk10;
                sp30.unk34 = var_s1->unk16;

                func_0016A080(&sp30);
            }
        }
    }
}

void func_01F6E100_subway_01(void)
{
    int* id; 
    D_01F6F7D0_struct* var_s1;
    func_0016A080_struct sp30;

    D_1D3165C |= 0x40000;

    if (GET_BIT(D_1D3177C, 0x14))
    {
        return;
    }

    for (id = &D_01F70650_subway_01; *id != 0; id++)
    {
        if (shCharacterGetSubCharacter(DOUBLE_HEAD_CHARA_ID, *id) == NULL)
        {
            for (var_s1 = &D_01F6F7D0_subway_01; var_s1 != NULL && var_s1->unk0 != 0; var_s1++)
            {
                if (var_s1->unk0 == DOUBLE_HEAD_CHARA_ID && var_s1->unk2 == *id)
                {
                    break;
                }
            }

            if (var_s1 != NULL && func_0016B4E0(var_s1) != 0)
            {
                shQzero(&sp30, 0x40);

                sp30.unk4 = var_s1->unk0;
                sp30.unk6 = var_s1->unk2;
                
                sp30.unk10 = var_s1->unk4;
                sp30.unk14 = var_s1->unkC;
                sp30.unk18 = var_s1->unk8;
                
                sp30.unk24 = (PI * 2 * var_s1->unkE) / 4096.0f;
                
                sp30.unk30 = var_s1->unk10;
                sp30.unk34 = var_s1->unk16;

                func_0016A080(&sp30);
            }
        }
    }
}

void func_01F6E270_subway_01(void)
{
    int* var_s0 = &D_01F70650_subway_01;
    int id;
    
    D_1D3165C |= 0x8000;
    
    while (id = *var_s0)
    {
        shCharacter_Manage_Delete(DOUBLE_HEAD_CHARA_ID, id);
        ++var_s0;
    }
}

void func_01F6E2D0_subway_01(void)
{
    SubCharacter* var_v0 = shCharacterGetSubCharacter(DOUBLE_HEAD_CHARA_ID, -1);

    while (var_v0 != NULL)
    {
        shCharacter_Manage_Delete(DOUBLE_HEAD_CHARA_ID, var_v0->id);
        var_v0 = shCharacterGetSubCharacter(DOUBLE_HEAD_CHARA_ID, -1);
    }
}

void func_01F6E320_subway_01(void)
{
    D_01F70700_subway_01 = 0;
    D_01F70708_subway_01 = 0;
    
    switch (RoomName())
    {
        case 0x35:
            /* fallthrough */
        case 0x36:
            /* fallthrough */
        case 0x37:
            /* fallthrough */
        case 0x38:
            /* fallthrough */
        case 0x3A:
            /* fallthrough */
        case 0x3B:
            /* fallthrough */
        case 0x3C:
            /* fallthrough */
        case 0x3D:
            break;
        case 0x39:
            func_01F6E7C0_subway_01();
            break;
    }
}

void func_01F6E380_subway_01(void)
{
    SubCharacter* temp_v0;
    SubCharacter* temp_s0;
    SubCharacter* temp_s1;
    float sp30[4];
    float sp40[4];

    switch (RoomName())
    {
        case 0x35:
            /* fallthrough */
        case 0x36:
            /* fallthrough */
        case 0x37:
            /* fallthrough */
        case 0x38:
            /* fallthrough */
        case 0x3C:
            /* fallthrough */
        case 0x3D:
            break;
        case 0x39:
            func_01F6E7D0_subway_01();
            func_01F6E960_subway_01();
            
            if (GET_BIT(D_1D3165C, 0xE))
            {
                clAddDynamicWall(&D_01F70000_subway_01);
            }
            else if (func_001909B0() != 0)
            {
                clAddDynamicWall(&D_01F6FEC0_subway_01);
            }
            
            if (func_001909B0() != 0)
            {
                clAddDynamicWall(&D_01F6FF60_subway_01);
            }
            
            temp_v0 = shCharacterGetSubCharacter(0x1009, 0x6C);
            
            if (temp_v0 != NULL)
            {
                if (!GET_BIT(D_1D3165C, 0xE))
                {
                    func_001DC9E0(temp_v0, 0);
                }
                else
                {
                    func_001DC9E0(temp_v0, 1);
                    
                    temp_v0->pos.x = -34500.0f;
                    temp_v0->pos.y = -500.0f;
                    temp_v0->pos.z = 61025.0f;
                    
                    temp_v0->rot.x = 0;
                    temp_v0->rot.y = -PI / 2.0f;
                    temp_v0->rot.z = 0;
                }
                
                if (GET_BIT(D_1D3165C, 0xB) && !GET_BIT(D_1D3165C, 0xC))
                {
                    func_01F6DF90_subway_01();
                }
                
                if (GET_BIT(D_1D3165C, 0x11) && !GET_BIT(D_1D3165C, 0x12))
                {
                    func_01F6E100_subway_01();
                }
            }
            
            break;
        case 0x3A:
            func_01F6E960_subway_01();
            
            if (GET_BIT(D_1D3165C, 0xE))
            {
                clAddDynamicWall(&D_01F6FE20_subway_01);
            }
            else if (func_001909B0() != 0)
            {
                clAddDynamicWall(&D_01F6FD80_subway_01);
            }
            
            temp_v0 = shCharacterGetSubCharacter(0x1009, 0x6E);
            
            if (temp_v0 != NULL)
            {
                if (!GET_BIT(D_1D3165C, 0xE))
                {
                    func_001DC9E0(temp_v0, 0);
                    return;
                }
                
                func_001DC9E0(temp_v0, 1);
                
                temp_v0->pos.x = -64250.0f;
                temp_v0->pos.y = -500.0f;
                temp_v0->pos.z = 61025.0f;
                
                temp_v0->rot.x = 0;
                temp_v0->rot.y = -PI / 2.0f;
                temp_v0->rot.z = 0;
            }
            
            break;
        case 0x3B:
            func_01F6E960_subway_01();
            
            if (GET_BIT(D_1D3165C, 0xE))
            {
                clAddDynamicWall(&D_01F6FB00_subway_01);
                clAddDynamicFloor(&D_01F6FCE0_subway_01);
            }
            else if (func_001909B0() != 0)
            {
                clAddDynamicWall(&D_01F6F9C0_subway_01);
            }
            
            if (func_001909B0() != 0)
            {
                clAddDynamicWall(&D_01F6FA60_subway_01);
            }
            
            temp_s1 = shCharacterGetSubCharacter(0x1009, 0x70);
            temp_s0 = shCharacterGetSubCharacter(0x1019, 0x71);
            
            if (temp_s1 != NULL && temp_s0 != NULL)
            {
                if (!GET_BIT(D_1D3165C, 0xE))
                {
                    func_001DC9E0(temp_s1, 0);
                    func_001DC9E0(temp_s0, 0);
                    return;
                }
                
                func_001DC9E0(temp_s1, 1);
                func_001DC9E0(temp_s0, 1);
                
                temp_s1->pos.x = -44250.0f;
                temp_s1->pos.y = -500.0f;
                
                temp_s1->rot.x = 0;
                
                temp_s1->pos.x = -46050.0f;
                temp_s1->pos.y = -550.0f;
                temp_s1->pos.z = 21025.0f;
                
                temp_s1->rot.x = 0;
                temp_s1->rot.y = -PI / 2.0f;
                temp_s1->rot.z = 0;
                
                temp_s0->pos.x = -67775.0f;
                temp_s0->pos.y = -550.0f;
                temp_s0->pos.z = 21687.5f;
                
                temp_s0->rot.y = -PI / 2.0f;
                
                func_001DD650(temp_s0, 0, sp30, sp40);
                sp30[2] -= 600.0f;
                func_001DD6F0(temp_s0, 0, sp30, sp40);
                
                func_001DD650(temp_s0, 1, sp30, sp40);
                sp30[2] += 600.0f;
                func_001DD6F0(temp_s0, 1, sp30, sp40);
            }
            
            break;
    }
}

void func_01F6E7C0_subway_01(void)
{
    D_01F70718_subway_01 = 0;
}

void func_01F6E7D0_subway_01(void)
{
    float sp10[3]; 

    func_001E1F20(sp10);
    
    if (!GET_BIT(D_1D31648, 0x12))
    {
        if (-11747.0f < sp10[0] && -10012.0f >= sp10[0] && 63234.0f >= sp10[2] && 61648.0f < sp10[2])
        {
            if (D_01F70718_subway_01 == 0) 
            {
                func_001C0EB0(func_01F6E900_subway_01, 0xF423F, 0);
                D_01F70718_subway_01 = 1;
            }
        } 
        else if (D_01F70718_subway_01 != 0) 
        {
            func_001C0EE0(1);
            D_01F70718_subway_01 = 0;
        }
    } 
    else if (D_01F70718_subway_01 != 0) 
    {
        func_001C0EE0(1);
        D_01F70718_subway_01 = 0;
    }
}

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

void func_01F6E960_subway_01(void)
{
    short temp_s0;
    float sp20[3];

    if (!GET_BIT(D_1D31648, 0x12))
    {
        temp_s0 = RoomName();
        func_001E1F20(sp20);
        
        if (GET_BIT(D_1D3165C, 0x11) && temp_s0 == 0x39)
        {
            D_01F70708_subway_01 = 0;
            
            switch (D_01F70720_subway_01)
            {
                case 0:
                    SeCall(0.2f, 0.0f, 0x3139);
                    D_01F70730_subway_01 = 0.0f;
                    ++D_01F70720_subway_01;
                    break;
                case 1:
                    D_01F70730_subway_01 += shGetDT();
                    
                    if (D_01F70730_subway_01 > 20.0f)
                    {
                        SeCall(0.6f, 0.0f, 0x3139);
                        ++D_01F70720_subway_01;
                    }
                    
                    break;
                case 2:
                    D_01F70730_subway_01 += shGetDT();
                    
                    if (D_01F70730_subway_01 > 30.0f)
                    {
                        ++D_01F70720_subway_01;
                    }
                    
                    break;
                case 3:
                    if (sp20[1] > 450.0f)
                    {
                        D_1D31644 |= 0x80000000;
                    }
                    else
                    {
                        D_1D3165C |= 0x4000;
                    }
                    
                    ++D_01F70720_subway_01;
                    break;
            }
        }
        else if (sp20[1] > 450.0f)
        {
            D_01F70720_subway_01 = 0;
            
            switch (D_01F70708_subway_01)
            {
                case 0:
                    D_01F70728_subway_01 = 0.0f;
                    ++D_01F70708_subway_01;
                    break;
                case 1:
                    D_01F70728_subway_01 += shGetDT();
                    
                    if (D_01F70728_subway_01 > 50.0f)
                    {
                        SeCall(0.6f, 0.0f, 0x3139);
                        ++D_01F70708_subway_01;
                    }
                    
                    break;
                case 2:
                    D_01F70728_subway_01 += shGetDT();
                    
                    if (D_01F70728_subway_01 > 60.0f)
                    {
                        ++D_01F70708_subway_01;
                    }
                    
                    break;
                case 3:
                    D_1D31644 |= 0x80000000;
                    D_01F70708_subway_01 = 6;
                    break;
                case 4:
                    D_01F70708_subway_01 = 5;
                    D_01F70728_subway_01 = 0.0f;
                    SeCall(0.6f, 0.0f, 0x3139);
                    break;
                case 5:
                    D_01F70728_subway_01 += shGetDT();
                    
                    if (D_01F70728_subway_01 > 6.0f)
                    {
                        D_01F70708_subway_01 = 3;
                    }
                    
                    break;
            }
        }
        else
        {
            D_01F70720_subway_01 = 0;
            D_01F70708_subway_01 = 0;
        }
    }
}
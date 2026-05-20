#include "mall_f_00.h"

void func_01F6D680_mall_f_00(void)
{
    if (D_01F6FBF8_mall_f_00 == 0)
    {
        func_001C2290(2, 0.0f);
        ++D_01F6FBF8_mall_f_00;
    }

    func_0016C540(&D_01F6F810_mall_f_00, &D_01F6F870_mall_f_00);
}

int func_01F6D6E0_mall_f_00(void)
{
    int ret = func_0016C9B0(&D_01F6F8A0_mall_f_00, 1, 1);
    float var_f20 = func_001643C0();
    int var_s1 = func_0015E880();
    int var_s2 = func_0015E850();

    if (D_01F6FB80_mall_f_00 > 0)
    {
        while (D_01F6FBF0_mall_f_00->unk0 > 0.0f)
        {
            if (D_01F6FBF0_mall_f_00->unk0 <= var_f20)
            {
                func_0013D250(0, D_01F6FBF0_mall_f_00->unk4, 1.0f);
                ++D_01F6FBF0_mall_f_00;
                continue;
            }

            break;
        }
    }

    switch (D_01F6FB80_mall_f_00)
    {
        case 0:
            D_01F6FBF0_mall_f_00 = &D_01F6F890_mall_f_00;
            ++D_01F6FB80_mall_f_00;
            /* fallthrough */
        case 1:
            if (var_s1 < 0x48001)
            {
                ++D_01F6FB80_mall_f_00;
            }

            break;
        case 2:
            if (var_s1 >= 0x48000)
            {
                func_001603E0(!var_s2, 3);
                ++D_01F6FB80_mall_f_00;
                break;
            }

            if (ret != 0)
            {
                func_001603E0(!var_s2, 3);
                ++D_01F6FB80_mall_f_00;
            }

            break;
    }

    if (ret != 0)
    {
        func_0013D280(0);

        if (func_001646C0())
        {
            func_001602D0(0x2714, !var_s2, 1, 1.0f);
        }
    }

    return ret;
}

int func_01F6D8D0_mall_f_00(void)
{
    sceVu0FVECTOR sp50;
    sceVu0FVECTOR sp60;
    Q sp70;
    sceVu0FVECTOR sp80;
    sceVu0FMATRIX sp90;
    sceVu0FVECTOR spD0;
    sceVu0FVECTOR spE0;
    sceVu0FVECTOR spF0;
    sceVu0FVECTOR sp100;
    sceVu0FMATRIX sp110;
    sceVu0FMATRIX* sp150[4];
    sceVu0FMATRIX* sp160[4];
    sceVu0FVECTOR sp170;
    float var_f20 = func_001643C0();
    int ret = func_0016C540(&D_01F6F9F0_mall_f_00, &D_01F6FA50_mall_f_00);
    SubCharacter* closer;
    SubCharacter* var_s2;

    switch (D_01F6FB80_mall_f_00)
    {
        case 0:
            D_01F6FB88_mall_f_00 = 0;
            D_01F6FB90_mall_f_00 = 0;
            D_01F6FB98_mall_f_00 = 0;
            D_01F6FBA0_mall_f_00 = 0;
            func_001646B0(-0.3f);
            ++D_01F6FB80_mall_f_00;
            /* fallthrough */
        case 1:
            if (func_0019B580(5) != 0)
            {
                int temp_D_01F6FB90_mall_f_00; // Anchors global value to prevent redundant RAM access
                int temp_D_01F6FB88_mall_f_00; // Same as above
                float temp_f0 = D_01F6F930_mall_f_00[temp_D_01F6FB90_mall_f_00 = D_01F6FB90_mall_f_00];
                float temp_zero = 0.0f;        // Forces zero into $f1 instead of the default $f0
                float temp_f1;

                if (temp_f0 != 0.0f && var_f20 >= temp_f0)
                {
                    D_01F6F950_struct* temp_s1;

                    sp70 = D_01F6FA70_mall_f_00;
                    temp_s1 = &D_01F6F950_mall_f_00[temp_D_01F6FB90_mall_f_00];
                    func_001300F0(&sp90, 0x1004, -1, 2);
                    sp80[0] = sp90[3][0];
                    sp80[1] = -75.0f + sp90[3][1];
                    sp80[2] = sp90[3][2];
                    sp80[3] = 1.0f;
                    func_00213810(&sp80, temp_s1, temp_s1->unk10, 0, temp_s1->unk14, temp_s1->unk18, &sp70);
                    ++D_01F6FB90_mall_f_00;
                }

                spD0 = D_01F6FA80_mall_f_00;

                if (var_f20 >= 672.0f && D_01F6FBA0_mall_f_00 == 0)
                {
                    spE0[0] = 0.6f;
                    spE0[1] = 0.0f;
                    spE0[2] = -0.8f;
                    func_002804E0(&spD0, &spE0, 0, 0);
                    ++D_01F6FBA0_mall_f_00;
                }
                else if (var_f20 >= 708.0f && D_01F6FBA0_mall_f_00 == 1)
                {
                    spE0[0] = 0.267f;
                    spE0[1] = 0.0f;
                    spE0[2] = -0.965f;
                    func_002804E0(&spD0, &spE0, 0, 0);
                    ++D_01F6FBA0_mall_f_00;
                }

                temp_f1 = D_01F6F900_mall_f_00[temp_D_01F6FB88_mall_f_00 = D_01F6FB88_mall_f_00];

                if (temp_f1 != 0.0f && var_f20 >= temp_f1)
                {
                    sp100 = D_01F6FA90_mall_f_00;

                    if (temp_D_01F6FB88_mall_f_00 >= 7)
                    {
                        if (temp_D_01F6FB88_mall_f_00 >= 9)
                        {
                            func_0013D250(0, &D_01F6F730_mall_f_00, 1.0f);
                        }
                        else
                        {
                            func_0013D250(0, &D_01F6F6F0_mall_f_00, 1.0f);
                        }
                    }
                    else
                    {
                        float* p_spF4;

                        func_0013D250(0, &D_01F6F6B0_mall_f_00, 1.0f);
                        func_00143610(&sp50, &sp60);
                        func_00281120(&sp50, &sp60, 1);
                        func_0023D820(&sp50, &sp60, 1);
                        func_001300F0(&sp110, 0x202, -1, 0xB);
                        spF0[0] = sp110[3][0] - -60.000004f;
                        p_spF4 = &spF0[1];
                        *p_spF4 = sp110[3][1];
                        spF0[2] = -240.00002f + sp110[3][2];
                        spF0[3] = 1.0f;
                        *p_spF4 += 200.0f;
                        func_00280430(&spF0, &sp100, 0, 0, 0, D_01F6FA04_mall_f_00, var_f20);
                    }

                    ++D_01F6FB88_mall_f_00;
                }
            }

            break;
    }

    closer = shCharacterGetSubCharacter(CLOSER_CHARA_ID, 0x11);
    var_s2 = shCharacterGetSubCharacter(0x1004, 0x12);

    if (ret == 0)
    {
        func_001DC9E0(closer, 0);
        func_001DC9E0(var_s2, 0);
    }
    else
    {
        sp170 = D_01F6FBB0_mall_f_00;

        func_001DC9E0(closer, 1);
        func_001DC9E0(var_s2, 1);
        func_0016CBD0(sp150, sp160, 7);
        func_0016CC50(0x202, 0, *sp150, &sp170);

        volatile_vec_copy(&closer->pos, (sceVu0FVECTOR *) *sp150 + 3);
        volatile_vec_copy(&closer->rot, sp170);

        func_002F2AF0(&closer->pos, closer, 0);
        func_0016CBD0(sp150, sp160, 8);
        func_0016CC50(0x1004, 0, *sp150, &sp170);

        volatile_vec_copy(&var_s2->pos, (sceVu0FVECTOR *) *sp150 + 3);
        volatile_vec_copy(&var_s2->rot, sp170);

        SET_BIT(D_1D316FC, 23);
        SET_BIT(D_1D316FC, 24);

        func_001C2290(5, 0.5f);
        func_0013D280(0);
    }

    return ret;
}

void func_01F6DE40_mall_f_00(void)
{
    if (D_01F6FB80_mall_f_00 == 0)
    {
        func_00316C50(0);
        func_0016ECE0(1);
        func_001C2290(2, 0.0f);
        ++D_01F6FB80_mall_f_00;
    }

    if (func_0016C9B0(&D_01F6FAA0_mall_f_00, 1, 1) != 0)
    {
        D_01F6FB80_mall_f_00 = 0;
        UNSET_BIT(D_1D316AC, 29);
    }
    else
    {
        SET_BIT(D_1D316AC, 29);
    }
}

int func_01F6DEF0_mall_f_00(void)
{
    if (!GET_BIT(D_1D3164C, 18))
    {
        D_01F6FBE8_mall_f_00 = 0;
        D_01F6FBE0_mall_f_00 = 0.0f;
        D_01F6FBD8_mall_f_00 = shRandF();
        SET_BIT(D_1D3164C, 18);
        func_00190A20(2);
        SeCall(1.0f, 0.0f, 0x2EE0);
    }

    switch (D_01F6FBE8_mall_f_00)
    {
        case 0:
            if ((D_01F6FBE0_mall_f_00 += shGetDT()) < 0.8f + D_01F6FBD8_mall_f_00)
            {
                return 0;
            }

            SeCall(1.0f, 0.0f, 0x2EE1);
            D_01F6FBE0_mall_f_00 = 0.0f;
            ++D_01F6FBE8_mall_f_00;
            /* fallthrough */
        case 1:
            if ((D_01F6FBE0_mall_f_00 += shGetDT()) < 0.8f)
            {
                return 0;
            }

            ++D_01F6FBE8_mall_f_00;
            /* fallthrough */
        case 2:
            if (func_0016C1C0(0x59) == 0)
            {
                return 0;
            }

            func_0016C3C0();
            UNSET_BIT(D_1D3164C, 18);
            func_00190A20(0);
            /* fallthrough */
        default:
            return 1;
    }
}

int func_01F6E0C0_mall_f_00(void)
{
    if (!GET_BIT(D_1D3164C, 22))
    {
        func_0016CD00(&D_01F6FB00_mall_f_00);
        SET_BIT(D_1D3164C, 22);
        func_00190A20(2);
    }

    if (func_0016BED0(0xB6, 0x57) == 0)
    {
        return 0;
    }

    UNSET_BIT(D_1D3164C, 22);
    func_00190A20(0);

    return 1;
}

void func_01F6E160_mall_f_00(void)
{
    int room_name;

    if (func_00199C70(5) != 0 && !GET_BIT(D_1D31650, 16))
    {
        SET_BIT(D_1D31650, 16);
    }

    room_name = RoomName();
    D_01F6FB80_mall_f_00 = 0;
    D_01F6FBD0_mall_f_00 = 0;

    switch (room_name)
    {
        case MALL_HAPPY_BURGER:
            if (!GET_BIT(D_01D31640, 2))
            {
                func_001C2290(2, 0.0f);
                func_0016D810(0xF);
                func_0016D810(0x11);
                func_0016D810(0x12);
                func_0016D810(0x13);
                func_0016D810(0xC);
                func_0016D810(0xA);
                func_0016D810(2);
                func_0016D810(0x14);
                func_0016E400(0x1F, 0);
                func_0016D810(0x1F);
                func_0016DCE0(0);
                func_0016E400(0x22, 0);
                func_0016D810(0x22);
                ItemGet(1);
                ItemGet(0x23);
                ItemGet(0x24);
                func_001999B0();
                SET_BIT(D_1D3169C, 8);
                SET_BIT(D_01D31640, 1);
                SET_BIT(D_1D31644, 30);
                SET_BIT(D_1D31648, 30);
                func_00316C50(0);
                D_01F6FBF8_mall_f_00 = 0;
            }

            break;
        case MALL_BOUTIQUE_MARGUERITE:
            if (!GET_BIT(D_01D31640, 5))
            {
                ItemGet(0xA);
                func_0016DCE0(0xA);
            }

            SET_BIT(D_1D316FC, 23);
            SET_BIT(D_1D316FC, 24);
            break;
        case MALL_BATHROOM:
            SET_BIT(D_1D316FC, 16);
            SET_BIT(D_1D316FC, 15);
            break;
    }
}

void func_01F6E380_mall_f_00(void)
{
    sceVu0FMATRIX* sp30[4];
    sceVu0FMATRIX* sp40[4];
    sceVu0FVECTOR sp50;
    SubCharacter* closer;
    SubCharacter* var_s1;

    D_01F6FBD0_mall_f_00 = 1;

    switch (RoomName())
    {
        case MALL_BOUTIQUE_MARGUERITE:
            if (GET_BIT(D_01D31640, 5))
            {
                sp50 = D_01F6FBC0_mall_f_00;

                closer = shCharacterGetSubCharacter(CLOSER_CHARA_ID, 0x11);
                var_s1 = shCharacterGetSubCharacter(0x1004, 0x12);

                func_001DC9E0(closer, 1);
                func_001DC9E0(var_s1, 1);
                func_0016CBD0(sp30, sp40, 7);
                func_0016CC50(0x202, 0, *sp30, &sp50);

                volatile_vec_copy(&closer->pos, (sceVu0FVECTOR *) *sp30 + 3);
                volatile_vec_copy(&closer->rot, sp50);

                func_002F2AF0(&closer->pos, closer, 1);
                func_0016CBD0(sp30, sp40, 8);
                func_0016CC50(0x1004, 0, *sp30, &sp50);

                volatile_vec_copy(&var_s1->pos, (sceVu0FVECTOR *) *sp30 + 3);
                volatile_vec_copy(&var_s1->rot, sp50);
            }

            break;
    }
}

void func_01F6E4B0_mall_f_00(void)
{
    if (D_01F6FBD0_mall_f_00 == 0)
    {
        func_01F6E380_mall_f_00();
    }

    switch (RoomName())
    {
        case MALL_ALLEYWAY:
            if (GET_BIT(D_1D31650, 16) && !GET_BIT(D_1D31650, 17))
            {
                func_0016CA40(4);
                SET_BIT(D_1D316FC, 18);
            }
            else
            {
                UNSET_BIT(D_1D316FC, 18);
            }
            /* fallthrough */
        case MALL_BOUTIQUE_MARGUERITE:
            if (GET_BIT(D_01D31640, 5))
            {
                func_0016CA40(1);
            }

            break;
        case MALL_STAIRCASE:
            if (!GET_BIT(D_1D3164C, 21))
            {
                func_0016CA40(1);
            }

            break;
    }
}

int func_01F6E5C0_mall_f_00(void)
{
    return 1;
}
#include "subway_02.h"

int func_01F6D680_subway_02(void)
{
    int var_s0;
    SubCharacter* heather = shCharacterGetSubCharacter(HEATHER_CHARA_ID, -1);
    Q sp40;
    Q sp50;
    float temp_f0;

    switch (D_01F6F080_subway_02)
    {
        case 0:
            func_001C2290(3, 0.8f);
            D_01F6F088_subway_02 = 0;
            ++D_01F6F080_subway_02;
            /* fallthrough */
        case 1:
            var_s0 = func_0016C540(&D_01F6EF10_subway_02, &D_01F6EF70_subway_02);

            if (func_001646F0() == 2)
            {
                sp40 = D_01F6EF90_subway_02;
                sp50 = D_01F6F090_subway_02;
                func_001DA020(1, &sp40, &sp50);
                func_001DA020(2, &sp40, &sp50);
                func_001DA020(3, &sp40, &sp50);
            }

            break;
    }

    temp_f0 = func_001643C0();

    if (temp_f0 < 110.0f)
    {
        func_0013D250(0, &D_01F6ED90_subway_02, 1.0f);
    }

    if (D_01F6F088_subway_02 == 0 && temp_f0 > 120.0f)
    {
        D_01F6F088_subway_02 = 1;
        func_0013D250(0, &D_01F6EDD0_subway_02, 1.0f);
        func_0013D250(0, &D_01F6EE30_subway_02, 1.0f);
    }

    if (temp_f0)
    {
        func_001DC9E0(heather, 0);
    }
    else
    {
        func_001DC9E0(heather, 1);
    }

    if (var_s0 != 0)
    {
        func_001BE4B0(0);
        func_00190A20(0);
        func_001DC9E0(heather, 1);
        func_00190C40();
        func_0013D280(0);
        D_01F6F088_subway_02 = 0;
        D_01F6F080_subway_02 = 0;
    }

    return var_s0;
}

void func_01F6D8B0_subway_02(void)
{
    short temp_a0;

    D_01F6F080_subway_02 = 0;
    temp_a0 = RoomName();

    switch (temp_a0)
    {
        case 0x3E:
            func_01F6DBE0_subway_02(temp_a0);
            break;
        case 0x3F:
            func_01F6DBE0_subway_02(temp_a0);
            break;
        case 0x40:
            func_01F6DBE0_subway_02(temp_a0);
            break;
        case 0x41:
            func_01F6DBE0_subway_02(temp_a0);
            break;
        case 0x42:
            func_01F6DBE0_subway_02(temp_a0);
            break;
        case 0x43:
            func_01F6DBE0_subway_02(temp_a0);
            break;
        case 0x44:
            func_01F6DBE0_subway_02(temp_a0);
            break;
        case 0x45:
            func_01F6DBE0_subway_02(temp_a0);
            break;
        case 0x46:
            func_01F6DBE0_subway_02(temp_a0);
            break;
    }

    func_001BE4B0(1);
}

void func_01F6D9A0_subway_02(void)
{
    switch ((short) RoomName())
    {
        case 0x3E:
            func_01F6DCF0_subway_02(1, 2, 3);
            func_0013D250(0, &D_01F6ED90_subway_02, 1.0f);
            break;
        case 0x3F:
            func_01F6DCF0_subway_02(1, 2, 3);
            func_0013D250(0, &D_01F6ED90_subway_02, 1.0f);
            break;
        case 0x40:
            func_01F6DCF0_subway_02(1, 2, 3);
            func_0013D250(0, &D_01F6ED90_subway_02, 1.0f);
            break;
        case 0x41:
            func_01F6DCF0_subway_02(1, 2, 3);
            func_0013D250(0, &D_01F6ED90_subway_02, 1.0f);
            break;
        case 0x42:
            func_01F6DCF0_subway_02(1, 2, 3);
            func_0013D250(0, &D_01F6ED90_subway_02, 1.0f);
            break;
        case 0x43:
            func_01F6DCF0_subway_02(1, 2, 3);
            func_0013D250(0, &D_01F6ED90_subway_02, 1.0f);
            break;
        case 0x44:
            func_01F6DCF0_subway_02(1, 2, 3);
            func_0013D250(0, &D_01F6ED90_subway_02, 1.0f);
            break;
        case 0x45:
            func_01F6DCF0_subway_02(1, 2, 3);
            func_0013D250(0, &D_01F6ED90_subway_02, 1.0f);
            break;
        case 0x46:
            func_01F6DCF0_subway_02(1, 2, 3);

            if (func_001C2580(4) == 0 || func_00190940() == 1)
            {
                clAddDynamicWall(&D_01F6EC50_subway_02);
            }

            if (func_001643D0() != 0x13)
            {
                func_0013D250(0, &D_01F6ED90_subway_02, 1.0f);
            }

            break;
    }
}

void func_01F6DBE0_subway_02(int arg0)
{
    float temp_f4;
    float temp_f3 = 0.0f;
    float temp_f2 = 4000.0f;
    float temp_f1 = 8000.0f;

    func_00170620(&D_01F6F0A0_subway_02, arg0);
    temp_f4 = -4000.0f + D_01F6F0A0_subway_02;
    D_01F6F0C8_subway_02 = temp_f4 + temp_f3;
    D_01F6F0CC_subway_02 = temp_f4 + temp_f2;
    D_01F6F0D0_subway_02 = temp_f4 + temp_f1;
    D_01F6F0C0_subway_02 = D_01F6F0A8_subway_02;

    if (arg0 == 0x46)
    {
        D_01F6F0B8_subway_02 = 6000.0f + D_01F6F0A0_subway_02 + 2400.0f;
        D_01F6F0B0_subway_02 = -6000.0f + D_01F6F0A0_subway_02 + 2400.0f;
    }
    else
    {
        D_01F6F0B8_subway_02 = 6000.0f + D_01F6F0A0_subway_02;
        D_01F6F0B0_subway_02 = -6000.0f + D_01F6F0A0_subway_02;
    }
}

void func_01F6DCF0_subway_02(int arg0, int arg1, int arg2)
{
    int var_s0 = 0;
    int var_s1;
    int var_s2 = 0;
    int var_s3 = 0;
    float temp_f0;
    float* temp_s4;
    sceVu0FMATRIX spA0;
    sceVu0FVECTOR spE0[3];

    while (var_s0 < 3)
    {
        switch (var_s0)
        {
            case 0:
                var_s1 = arg0;
                break;
            case 1:
                var_s1 = arg1;
                break;
            case 2:
                var_s1 = arg2;
                break;
        }

        temp_f0 = 9000.0f * shGetDT();
        temp_s4 = (float *) ((char *) &D_01F6F0C8_subway_02 + var_s2);
        *temp_s4 -= temp_f0;
        func_001C2AE0(var_s1, &spA0);
        spA0[3][0] = *temp_s4;
        func_001C2A80(var_s1, &spA0);
        sceVu0CopyVector(*(sceVu0FVECTOR *) ((char *) spE0 + var_s3), spA0[3]);

        if (*temp_s4 >= D_01F6F0B8_subway_02)
        {
            *temp_s4 -= D_01F6F0B8_subway_02 - D_01F6F0B0_subway_02;
        }
        else if (*temp_s4 <= D_01F6F0B0_subway_02)
        {
            *temp_s4 -= D_01F6F0B0_subway_02 - D_01F6F0B8_subway_02;
        }

        ++var_s0;
        var_s2 += 4;
        var_s3 += 0x10;
    }

    func_01F6E140_subway_02(spE0);
}

void func_01F6DE80_subway_02(sceVu0FVECTOR* arg0)
{
    sceVu0FVECTOR sp40;
    sceVu0FVECTOR sp50;
    sceVu0FVECTOR sp60;
    sceVu0FMATRIX sp70;
    sceVu0FVECTOR spB0;
    sceVu0FVECTOR spC0;
    func_001C7C80_struct spD0[2];
    func_001C7C80_struct spE8;
    int var_v1;
    sceVu0FVECTOR* pC0;
    sceVu0FVECTOR* pB0;
    sceVu0FVECTOR* p60;
    int temp_a3;
    int temp_t0;
    int var_a0;
    int var_a1;
    int var_a2;
    sceVu0FVECTOR* p_arg0 = arg0;
    int var_s1;
    int var_s2;

    sp40 = D_01F6EFA0_subway_02;
    sp50 = D_01F6EFB0_subway_02;
    sp60 = D_01F6EFC0_subway_02;

    func_001C18C0(&spC0);
    sh3gde_getCameraDir(&sp70);

    asm
    ("\
        lq $t0, 0(%0)\n\
        lq $t1, 0x10(%0)\n\
        lq $t2, 0x20(%0)\n\
        lqc2 $vf4, 0x30(%0)\n\
        pextlw $t3, $t1, $t0\n\
        pextuw $t4, $t1, $t0\n\
        pextlw $t5, $zero, $t2\n\
        pextuw $t6, $zero, $t2\n\
        pcpyld $t0, $t5, $t3\n\
        pcpyud $t1, $t3, $t5\n\
        pcpyld $t2, $t6, $t4\n\
        qmtc2 $t0, $vf5\n\
        qmtc2 $t1, $vf6\n\
        qmtc2 $t2, $vf7\n\
        vmulax.xyz $ACC, $vf5, $vf4x\n\
        vmadday.xyz $ACC, $vf6, $vf4y\n\
        vmaddz.xyz $vf4, $vf7, $vf4z\n\
        sq $t0, 0(%1)\n\
        sq $t1, 0x10(%1)\n\
        vsub.xyz $vf4, $vf0xyz, $vf4xyz\n\
        sq $t2, 0x20(%1)\n\
        sqc2 $vf4, 0x30(%1)"
    : : "r"(sp70), "r"(sp70)
    );

    sceVu0ApplyMatrix(sp60, sp70, sp60);

    var_v1 = 0;
    temp_a3 = 0;
    temp_t0 = 0;

    do
    {
        float temp_f0;
        func_001C7C80_struct* temp_v0;

        pB0 = &spB0;
        pC0 = &spC0;
        p60 = &sp60;

        vec_sub(spC0, (sceVu0FVECTOR *) ((char *) p_arg0 + temp_a3), spB0);

        temp_f0 = vec3_length(spB0);
        temp_v0 = (func_001C7C80_struct *) ((char *) spD0 + temp_t0);
        temp_v0->unk0 = temp_f0;

        if (vec3_dot_product(spB0, sp60) < 0.0f)
        {
            temp_v0->unk0 += 800.0f;
        }

        temp_v0->unk4 = var_v1++;
        temp_a3 += 16;
        temp_t0 += 8;
    } while (var_v1 < 3);

    temp_t0 = 0;
    var_a2 = 0;

    do
    {
        var_a0 = temp_t0 + 1;
        var_a1 = var_a0 * 8;

        if (var_a0 < 3)
        {
            func_001C7C80_struct* pA = (func_001C7C80_struct *) ((char *) spD0 + var_a2);

            do
            {
                func_001C7C80_struct* pB = (func_001C7C80_struct *) ((char *) spD0 + var_a1);

                if (pA->unk0 > pB->unk0)
                {
                    spE8 = *pB;
                    *pB = *pA;
                    *pA = spE8;
                }

                ++var_a0;
                var_a1 += 8;
            } while (var_a0 < 3);
        }

        ++temp_t0;
        var_a2 += 8;
    } while (temp_t0 < 2);

    if (func_0019B580(2) == 0)
    {
        var_s2 = 0;
        var_s1 = 0;

        do
        {
            u_char* p_unk4 = (u_char *) spD0 + var_s1 + 4;

            ((sceVu0FVECTOR *) p_arg0)[*p_unk4][1] = -800.0f;
            ((sceVu0FVECTOR *) p_arg0)[*p_unk4][2] += 50.0f;

            func_001C7C80(&sp40, &sp50, &p_arg0[*p_unk4], (u_char) var_s2 | 0x200);

            ++var_s2;
            var_s1 += 8;
        } while (var_s2 < 2);
    }
}

void func_01F6E140_subway_02(sceVu0FVECTOR* arg0)
{
    switch (RoomName())
    {
        case 0x3E:
            /* fallthrough */
        case 0x3F:
            /* fallthrough */
        case 0x42:
            /* fallthrough */
        case 0x44:
            break;
        default:
            func_01F6DE80_subway_02(arg0);
            break;
    }
}
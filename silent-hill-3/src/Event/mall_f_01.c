#include "mall_f_01.h"

int func_01F6D680_mall_f_01(void)
{
    switch (D_01F72BC8_mall_f_01)
    {
        case 0:
            func_001C2290(3, 0.3f);
            func_0019B4B0(7);
            ++D_01F72BC8_mall_f_01;
            /* fallthrough */
        case 1:
            if (func_001C2580(2) == 0)
            {
                return 0;
            }

            D_01F72BC0_mall_f_01 = &D_01F72758_mall_f_01;
            SET_BIT(D_1D31644, 9);
            ++D_01F72BC8_mall_f_01;
            /* fallthrough */
        default:
            if (func_0016C540(&D_01F72760_mall_f_01, &D_01F727C0_mall_f_01) == 0)
            {
                float var_f20 = func_001643C0();

                while (D_01F72BC0_mall_f_01->unk0 > 0.0f)
                {
                    if (D_01F72BC0_mall_f_01->unk0 <= var_f20)
                    {
                        func_0013D250(0, D_01F72BC0_mall_f_01->unk4, 1.0f);
                        ++D_01F72BC0_mall_f_01;
                        continue;
                    }

                    break;
                }

                return 0;
            }

            UNSET_BIT(D_1D31644, 9);
            func_001C2290(5, 0.5f);
            func_0013D280(0);

            if (GET_BIT(D_1D31784, 1))
            {
                SET_BIT(D_1D31784, 2);
            }

            return 1;
    }
}

int func_01F6D820_mall_f_01(void)
{
    int ret = func_0016C540(&D_01F72810_mall_f_01, &D_01F72870_mall_f_01);

    if (D_01F72BB8_mall_f_01 == 0)
    {
        func_003272C0();
        D_01F72BB8_mall_f_01 = 1;
        D_01F72BB0_mall_f_01 = shRandI() % 30 + 0x794;
    }
    else if (func_001643C0() > 0.0f)
    {
        float var_f20 = func_001643C0();

        if (var_f20 >= 1940.0f && var_f20 <= 2600.0f && D_01F72BB0_mall_f_01 <= var_f20)
        {
            D_01F727E0_struct* var_s1 = &D_01F727E0_mall_f_01;
            int temp_v1 = shRandI() % 4;

            while (temp_v1 != 0)
            {
                --temp_v1;
                ++var_s1;
            }

            func_0013D250(0, var_s1->unk4, 1.0f);
            D_01F72BB0_mall_f_01 = 15.0f + var_f20 + 30.0f * shRandF();
        }

        func_003272E0();
    }

    if (ret != 0)
    {
        if (func_001646C0() != 0)
        {
            func_001602D0(0x272C, 3, 1, 1.0f);
        }

        func_001C2290(5, 0.5f);
        func_003272D0();
        func_0013D280(0);
    }

    return ret;
}

int func_01F6DA20_mall_f_01(void)
{
    int ret = func_0016C540(&D_01F72890_mall_f_01, &D_01F728F0_mall_f_01);

    if (ret != 0)
    {
        func_001C2290(5, 0.5f);
    }

    return ret;
}

int func_01F6DA70_mall_f_01(void)
{
    if (!GET_BIT(D_1D3164C, 24))
    {
        D_01F72B80_mall_f_01 = 0;
        func_0016C3C0();
        SET_BIT(D_1D3164C, 24);
        func_00317420(5);
        func_00190A20(2);
    }

    switch (D_01F72B80_mall_f_01)
    {
        case 0:
            if (func_0016C1C0(0x32) == 0)
            {
                return 0;
            }
            else if (func_00168440() != 0)
            {
                break;
            }

            func_0016C3C0();
            SeCall(1.0f, 0.0f, 0x2B21);
            ItemGet(5);
            SET_BIT(D_1D3164C, 25);
            func_00317490(5, 0.2f);
            ++D_01F72B80_mall_f_01;
            /* fallthrough */
        default:
            if (func_0016C1C0(0x48) == 0)
            {
                return 0;
            }

            func_003174B0(0.2f);
            break;
    }

    UNSET_BIT(D_1D3164C, 24);
    func_00190A20(0);

    return 1;
}

int func_01F6DBD0_mall_f_01(void)
{
    int var_s0;
    int temp_a1;

    func_0012CFA0();

    if (func_0012D080() == 0)
    {
        func_00190A20(2);
    }

    func_0012CFC0();

    if (GET_BIT(D_1D3164C, 27))
    {
        var_s0 = 0x3D;
        temp_a1 = 0x30;
    }
    else
    {
        var_s0 = 0x3E;

        if (GET_BIT(D_1D31BF4, 5) && GetRiddleLevel() == 0)
        {
            temp_a1 = 0x2F;
        }
        else
        {
            temp_a1 = 0x2E;
        }

        if (!GET_BIT(D_1D31784, 1))
        {
            SET_BIT(D_1D31784, 1);
        }
    }

    if (func_0016BED0(var_s0, temp_a1) == 0)
    {
        return 0;
    }

    func_00190A20(0);

    return 1;
}

int func_01F6DCC0_mall_f_01(void)
{
    int temp_a0;
    int temp_a1;

    func_0012CFA0();

    if (func_0012D080() == 0)
    {
        func_00190A20(2);
    }

    func_0012CFC0();

    if (GetRiddleLevel() == 1)
    {
        temp_a0 = 0x42;
        temp_a1 = 0x33;

        if (!GET_BIT(D_1D316F0, 27) && !GET_BIT(D_1D316F0, 28))
        {
            SET_BIT(D_1D316F0, 27);
        }
    }
    else
    {
        temp_a0 = 0x41;
        temp_a1 = 0x34;

        if (!GET_BIT(D_1D316F0, 29) && !GET_BIT(D_1D316F0, 30))
        {
            SET_BIT(D_1D316F0, 29);
        }
    }

    if (func_0016BED0(temp_a0, temp_a1) == 0)
    {
        return 0;
    }

    func_00190A20(0);

    return 1;
}

void func_01F6DDB0_mall_f_01(void)
{
    PicDraw_Data pic;

    shQzero(&pic, sizeof(PicDraw_Data));

    SET_BIT(pic.status, 9);
    pic.b = 0xFF;
    pic.r = 0;
    pic.g = 0;
    SET_BIT(pic.status, 4);
    pic.otp = 6;
    pic.x0 = 0x700;
    pic.y0 = 0x100;
    pic.x1 = 0xF80;
    pic.y1 = 0x100;
    SET_BIT(pic.status, 1);
    PictureDraw(&pic);

    pic.x0 = 0xF80;
    pic.y0 = 0x100;
    pic.x1 = 0xF80;
    pic.y1 = 0x980;
    SET_BIT(pic.status, 1);
    PictureDraw(&pic);

    pic.x0 = 0xF80;
    pic.y0 = 0x980;
    pic.x1 = 0x700;
    pic.y1 = 0x980;
    SET_BIT(pic.status, 1);
    PictureDraw(&pic);

    pic.x0 = 0x700;
    pic.y0 = 0x980;
    pic.x1 = 0x700;
    pic.y1 = 0x100;
    SET_BIT(pic.status, 1);
    PictureDraw(&pic);
}

void func_01F6DF00_mall_f_01(PicLoadImage_Data* pic_load)
{
    PicDraw_Data* pic = (PicDraw_Data *) (pic_load + 2);

    pic_load->ap = func_00170410(1);
    pic_load->tex_adr = -1;
    pic_load->clut_adr = -1;
    pic_load->otp = 0;
    PictureLoadImage(pic_load);

    shQzero(pic, sizeof(PicDraw_Data));
    pic->ap = func_00170410(1);
    pic->tex = -1;
    pic->clut = -1;
    SET_BIT(pic->status, 0);
    pic->otp = 1;
    PictureDraw(pic);
}

void func_01F6DF90_mall_f_01(PicLoadImage_Data* pic_load)
{
    PicLoadImage_Data* next_pic_load = pic_load + 1;

    next_pic_load->ap = func_00170410(0);
    next_pic_load->tex_adr = -1;
    next_pic_load->clut_adr = -1;
    next_pic_load->otp = 2;
    PictureLoadImage(next_pic_load);
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6DFE0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6E3F0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6E630_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6E6E0_mall_f_01);

u_short func_01F6E700_mall_f_01(void) {
    float sp18;
    float sp1C;

    func_0029F330(&sp18, &sp1C);
    return func_002A47C0(sp18, sp1C);
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6E730_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6E9E0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6EE40_mall_f_01);

void func_01F6F1C0_mall_f_01(void) {
    func_01F6EE40_mall_f_01(0);
}

void func_01F6F1D0_mall_f_01(void) {
    func_01F6EE40_mall_f_01(0x27);
}

void func_01F6F1E0_mall_f_01(void) {
    func_01F6EE40_mall_f_01(0x28);
}

void func_01F6F1F0_mall_f_01(void) {
    func_01F6EE40_mall_f_01(0x29);
}

void func_01F6F200_mall_f_01(void) {
    func_01F6EE40_mall_f_01(0x2A);
}

void func_01F6F210_mall_f_01(void) {
    func_01F6EE40_mall_f_01(0x2B);
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F220_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F2B0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F300_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F510_mall_f_01);

u_short func_01F6F5A0_mall_f_01(void) {
    float sp18;
    float sp1C;

    func_0029F330(&sp18, &sp1C);
    return func_002A47C0(sp18, sp1C);
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F5D0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F720_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6F810_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6FB30_mall_f_01);

int func_01F6FCB0_mall_f_01(void) {
    Q sp10;

    sp10 = D_01F72AB0_mall_f_01;
    func_002A2E70(&sp10);
    D_1D3164C |= 0x04000000;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6FD00_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6FDA0_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F6FED0_mall_f_01);

void func_01F70070_mall_f_01(void) {
    if (!GET_BIT(D_1D31650, 0x12)) {
        func_01F70720_mall_f_01();
        D_1D31650 |= 0x40000;
    }

    switch (RoomName()) {
        case 12:
            D_01F72BC8_mall_f_01 = 0;
            D_1D31700 |= 8;
            break;
        case 17:
            D_01F72BB8_mall_f_01 = 0;
            break;
        case 16:
            break;
        case 15:
            D_1D31784 |= 0x2000;
            D_1D31700 |= 0x10;
            break;
        case 18:
            D_1D31700 |= 0x40;
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F70160_mall_f_01);

INCLUDE_ASM("asm/nonmatchings/Event/mall_f_01", func_01F70720_mall_f_01);

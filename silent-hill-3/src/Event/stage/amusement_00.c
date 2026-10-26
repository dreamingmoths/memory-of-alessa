#include "amusement_00.h"
#include "SH3_common/sh3dt.h"

int func_01F6D680_amusement_00(void) {
    int ret;

    switch (D_01F72D80_amusement_00) {
        case 0:
            func_001C2290(0.8, 2);
            D_01F72D80_amusement_00++;
    }

    ret = func_0016C540(&D_01F72830_amusement_00, &D_01F72890_amusement_00);
    if (ret) {
        func_001C2290(0.8, 5);
        if (func_001646C0() != 0) {
            func_001602D0(10026, 1, 1, 1.0f);
        }
        D_01F72D80_amusement_00 = 0;
    }

    return ret;
}

int func_01F6D740_amusement_00(void) {
    float float1;
    float float2;
    int ret;

    func_001643C0();
    ret = func_0016C540(&D_01F728E0_amusement_00, &D_01F72940_amusement_00);

    switch (D_01F72D80_amusement_00) {
        case 0:
            func_001C2290(0.5f, 3);
            D_01F72DD8_amusement_00 = &D_01F728B0_amusement_00;
            D_01F72D80_amusement_00++;
        case 1:
            if (func_001646D0() != 0 && func_001C2580(2) != 0) {
                D_01F72D80_amusement_00++;
            }
            break;
    }

    float1 = func_001643C0();
    float2 = D_01F72DD8_amusement_00->unk0;

    if (float2 > 0.0f && float2 <= float1) {
        func_0013D250(0, D_01F72DD8_amusement_00->unk4, 1.0f);
        D_01F72DD8_amusement_00++;
    }

    if (ret) {
        func_0013D280(0);
        func_00190C40();
        D_01F72D80_amusement_00 = 0;
    }

    return ret;
}

int func_01F6D880_amusement_00(void) {
    float float1;
    float float2;
    float float3;
    int ret = 0;

    switch (D_01F72D80_amusement_00) {
        case 0:
            func_00316C50(0);
            func_0016ECE0(5);
            func_001C2290(0.0f, 2);
            func_0016E400(34, 0);
            D_01F72DD0_amusement_00 = &D_01F72960_amusement_00;
            D_01F72D80_amusement_00++;
        case 1:
            ret    = func_0016C540(&D_01F72AF0_amusement_00, &D_01F72B50_amusement_00);
            float2 = func_001643C0();
            float1 = func_001643C0();
            float3 = D_01F72DD0_amusement_00->unk0;
            if (float3 > 0.0f && float3 <= float1) {
                func_0013D250(0, D_01F72DD0_amusement_00->unk4, 1.0f);
                D_01F72DD0_amusement_00++;
            }
            if (float2 >= 1032.0f) {
                func_0016E400(34, 1);
                D_01F72D80_amusement_00++;
            }
            break;
        case 2:
            ret = func_0016C540(&D_01F72AF0_amusement_00, &D_01F72B50_amusement_00);
            break;
    }
    if (ret != 0) {
        D_01F72D80_amusement_00 = 0;
        func_0013D280(0);
        func_001C2290(0.8f, 5);
        func_0016E400(34, 1);
    }
    return ret;
}

int func_01F6DA30_amusement_00(void) {
    float float1;
    float float2;
    int ret = 0;

    switch (D_01F72D80_amusement_00) {
        case 0:
            func_00190A20(2);
            D_1D316AC |= 0x20000000;

            D_01F72DB0_amusement_00 = 0.0f;
            D_01F72DA8_amusement_00 = &D_01F72B70_amusement_00;

            D_01F72DC8_amusement_00 = 1;

            D_01F72DC0_amusement_00 = func_00163920(1, 3);
            D_01F72DB8_amusement_00 = func_00163920(1, 4);
            func_001C2290(0.5f, 3);
            D_01F72D80_amusement_00 = 1;
        case 1:
            if (func_00151150(0, 1) == 0 || func_001C2580(2) == 0) {
                break;
            }
            D_01F72D80_amusement_00 = 2;
            func_001603E0(func_0015E850() != 0 ? 0 : 1, 1);
        case 2:
            func_0016C540(&D_01F72B90_amusement_00, &D_01F72BF0_amusement_00);
            if (func_001646F0() == 2) {
                func_001C2290(0.0f, 2);
                func_001C2290(0.5f, 5);
                func_0019A940();
                D_01F72D80_amusement_00 = 4;
            }
            break;
        case 4:
            func_0019B4B0(5);
            func_0015E650();
            func_01F6DEA0_amusement_00(0.0f);
            func_00258910();
            func_001EC590(0);
            if (func_0013D080(0, 0, 1, 4) != 0) {
                ret = 1;
                func_001C2290(0.5f, 3);
                func_0015E780(5);
                func_00164210();
            } else if (func_0019A9B0(2.5) != 0) {
                D_01F72D80_amusement_00 = 5;
                func_0019A940();
            }
            break;
        case 5:
            func_0019B4B0(5);
            func_0015E650();
            D_01F72DB0_amusement_00 += 4.0f * shGetDT();
            if (D_01F72DB0_amusement_00 >= 1.0f) {
                D_01F72DB0_amusement_00 = 1.0f;
                D_01F72D80_amusement_00 = 6;
            }
            func_01F6DEA0_amusement_00(D_01F72DB0_amusement_00);
            func_00258910();
            func_001EC590(0);
            if (func_0013D080(0, 0, 1, 4) != 0) {
                ret = 1;
                func_001C2290(0.5f, 3);
                func_0015E780(5);
                func_00164210();
            }
            break;
        case 6:
            func_0019B4B0(5);
            func_0015E650();
            func_01F6DEA0_amusement_00(1.0f);
            func_00258910();
            func_001EC590(0);
            if (func_0013D080(0, 0, 1, 4) != 0) {
                ret = 1;
                func_001C2290(0.5f, 3);
                func_0015E780(5);
                func_00164210();
            } else if (func_0019A9B0(1.0f) != 0) {
                func_001C2290(0.0f, 14);
                D_01F72D80_amusement_00 = 7;
            }
            break;
        case 7:
            ret                     = func_0016C540(&D_01F72B90_amusement_00, &D_01F72BF0_amusement_00);
            D_01F72D80_amusement_00 = 8;
            func_00258910();
            func_001EC590(0);
            func_001C2290(0.0f, 1);
            break;
        case 8:
            ret    = func_0016C540(&D_01F72B90_amusement_00, &D_01F72BF0_amusement_00);
            float1 = func_001643C0();
            float2 = D_01F72DA8_amusement_00->unk0;
            if (float2 > 0.0f && float2 <= float1) {
                func_0013D250(0, D_01F72DA8_amusement_00->unk4, 1.0f);
                D_01F72DA8_amusement_00++;
            }
            break;
    }
    if (ret != 0) {
        D_01F72DC8_amusement_00 = 0;
        func_0016F630();
        func_00190A20(0);
        func_0013D280(0);
        D_01F72D80_amusement_00 = 0;
    }
    return ret;
}

void func_01F6DEA0_amusement_00(float fparg0) {
    PicDraw_Data* picDraw1;
    PicDraw_Data* picDraw2;
    PicLoadImage_Data* picLoad1;
    PicLoadImage_Data* picLoad2;
    sh3gfw_AREA_HEAD* areaHead1;
    sh3gfw_AREA_HEAD* areaHead2;

    picLoad1           = func_00170430(0);
    picDraw1           = func_00170450(0);
    areaHead1          = (sh3gfw_AREA_HEAD*) (D_01F72DB8_amusement_00 + 64);
    picLoad1->ap       = areaHead1;
    picLoad1->tex_adr  = -1;
    picLoad1->clut_adr = -1;
    picLoad1->otp      = 0;
    sh3_PictureLoadImageWrapped(picLoad1);

    shQzero(picDraw1, 68);
    picDraw1->ap     = areaHead1;
    picDraw1->tex    = -1;
    picDraw1->clut   = -1;
    picDraw1->status = (short) (picDraw1->status | 1);
    picDraw1->otp    = 1;
    sh3_PictureDrawWrapped(picDraw1);

    picLoad2           = func_00170430(1);
    picDraw2           = func_00170450(1);
    areaHead2          = (sh3gfw_AREA_HEAD*) (D_01F72DC0_amusement_00 + 64);
    picLoad2->ap       = areaHead2;
    picLoad2->tex_adr  = -1;
    picLoad2->clut_adr = -1;
    picLoad2->otp      = 2;
    sh3_PictureLoadImageWrapped(picLoad2);
    shQzero(picDraw2, 68);

    picDraw2->ap     = areaHead2;
    picDraw2->tex    = -1;
    picDraw2->clut   = -1;
    picDraw2->status = (short) (picDraw2->status | 1);
    if (fparg0 < 1.0f) {
        picDraw2->a         = (char) (128.0f * fparg0);
        picDraw2->alpha_a   = 0;
        picDraw2->alpha_b   = 1;
        picDraw2->alpha_c   = 0;
        picDraw2->alpha_d   = 1;
        picDraw2->alpha_fix = 0;
        picDraw2->status    = (short) (picDraw2->status | 32);
    }

    picDraw2->otp = 3;
    sh3_PictureDrawWrapped(picDraw2);
}

int func_01F6E020_amusement_00(void) {
    Vector4 vector;

    vector = D_01F72C10_amusement_00;

    switch (D_01F72D80_amusement_00) {
        case 0:
            func_00190A20(2);
            D_01F72D80_amusement_00++;
    }

    if (func_0016C1C0(26) == 0) {
        return 0;
    }

    if (func_0016CB70() == 0) {
        D_1D3169C |= 0x40;
        func_0015DCD0(1.0f, 10000.0f, 15201, &vector, 0, 0);
        func_0016D0E0(15200, D_01F72DA0_amusement_00);
        D_01F72DA0_amusement_00 = -1;
    }

    func_00190A20(0);
    D_01F72D80_amusement_00 = 0;
    return 1;
}

int func_01F6E120_amusement_00(void) {
    float float1;
    float sound_fa0;
    float sound_fa1;

    switch (D_01F72D80_amusement_00) {
        case 0:
            func_00190A20(0);
            func_00190A20(5);
            D_01F72D98_amusement_00 = 1.0f;
            D_01F72D80_amusement_00 = 1;
        case 1:
            if (func_00190C00() == 0) {
                return 0;
            }
            func_001C2290(0.8f, 3);
            D_01F72D80_amusement_00 = 2;
        case 2:
            func_0016F550(73, 0);
            func_0016F550(72, 4);
            D_01F72D80_amusement_00 = 3;
        case 3:
            if (func_00151150(0, 1) == 0 || func_001C2580(2) == 0) {
                return 0;
            }
            D_01F72D80_amusement_00 = 4;
        case 4:
            if (func_001C2580(4) != 0) {
                func_0016BC00(1);
                D_01F72D80_amusement_00 = 5;
            } else if (func_001C2580(3) == 0) {
                func_0016BC00(0);
                func_001C2290(0.8f, 5);
                func_0016C1A0();
                return 0;
            }
            func_01F6E420_amusement_00(1.0f);
            return 0;
        case 5:
            D_01F72D80_amusement_00 = 6;
            D_1D3169C |= 0x800;
            ItemGet(69);
            sound_fa0 = 1.0f;
            sound_fa1 = 0.0f;
            SeCall(11041, sound_fa0, sound_fa1);
        case 6:
            func_0016BC00(1);
            func_01F6E420_amusement_00(1.0f);
            if (func_0016C1C0(62) == 0) {
                return 0;
            }
            D_01F72D80_amusement_00 = 7;
            return 0;
        case 7:
            func_0016BC00(0);
            float1                  = D_01F72D98_amusement_00 - (0.8f * shGetDT());
            D_01F72D98_amusement_00 = float1;
            if (float1 < 0.0f) {
                D_01F72D98_amusement_00 = 0.0f;
                D_01F72D80_amusement_00 = 8;
                func_001C2290(0.8f, 3);
            }
            func_01F6E420_amusement_00(D_01F72D98_amusement_00);
            return 0;
        case 8:
            func_0016BC00(0);
            func_01F6E420_amusement_00(0.0f);
            if (func_001C2580(2) != 0) {
                D_01F72D80_amusement_00 = 9;
            }
            return 0;
        case 9:
            func_0016C1B0();
            func_001C2290(0.8f, 5);
            func_00190A20(6);
            D_01F72D80_amusement_00 = 10;
        case 10:
            if (func_00190C00() == 0) {
                return 0;
            }
            func_00190A20(0);
            D_01F72D80_amusement_00 = 0;
        default:
            return 1;
    }
}

void func_01F6E420_amusement_00(float fparg0) {
    PicDraw_Data* temp_s0;
    PicLoadImage_Data* temp_s1;

    temp_s1           = func_00170430(4);
    temp_s0           = func_00170450(4);
    temp_s1->ap       = func_00170410(4);
    temp_s1->tex_adr  = -1;
    temp_s1->clut_adr = -1;
    temp_s1->otp      = 2;
    sh3_PictureLoadImageWrapped(temp_s1);
    shQzero(temp_s0, 68);
    temp_s0->ap   = func_00170410(4);
    temp_s0->tex  = -1;
    temp_s0->clut = -1;
    temp_s0->status |= 1;
    temp_s0->a         = (char) (128.0f * fparg0);
    temp_s0->alpha_a   = 0;
    temp_s0->alpha_b   = 1;
    temp_s0->alpha_c   = 0;
    temp_s0->alpha_d   = 1;
    temp_s0->alpha_fix = 0;
    temp_s0->status |= 32;
    temp_s0->x0 = -1872;
    temp_s0->y0 = -1536;
    temp_s0->x1 = -608;
    temp_s0->y1 = 1264;
    temp_s0->status |= 2;
    temp_s0->us0 = 16;
    temp_s0->vt0 = 16;
    temp_s0->us1 = 1280;
    temp_s0->vt1 = 2816;
    temp_s0->status &= ~8;
    temp_s0->status |= 4;
    temp_s0->otp = 3;
    sh3_PictureDrawWrapped(temp_s0);
    func_0016BD90(0, 0, 1.0f);
}

int func_01F6E590_amusement_00(void) {
    switch (D_01F72D80_amusement_00) {
        case 0:
            func_00190A20(2);
            SeCall(19025, 1.0f, 0.0f);
            D_01F72D80_amusement_00++;
        case 1:
            if (func_0016C1C0(63) == 0) {
                return 0;
            }
            func_001C2290(0.5f, 3);
            SeCall(19023, 1.0f, 0.0f);
            D_01F72D80_amusement_00++;
        case 2:
            if (func_001C2580(2) == 0) {
                return 0;
            }
            D_1D3169C |= 0x80;
            func_001C2290(0.5f, 5);
            func_00190A20(0);
            D_01F72D80_amusement_00 = 0;
        default:
            return 1;
    }
}

u_int func_01F6E6A0_amusement_00(int arg0) {
    int x;
    switch (arg0) {
        case 1:
            x = GET_BIT(D_1D3169C, 9) ? 0 : 1;
    }
    return x;
}

void func_01F6E6D0_amusement_00(void) {
    D_01F72D90_amusement_00 = 0;
    D_01F72D80_amusement_00 = 0;

    switch ((short) RoomName()) {
        case 210:
            if (!GET_BIT(D_1D31644, 30)) {
                ItemGet(15);
                ItemGet(15);
                ItemGet(15);
                ItemGet(15);
                ItemGet(17);
                ItemGet(18);
                ItemGet(19);
                ItemGet(12);
                ItemGet(10);
                ItemGet(1);
                ItemGet(2);
                ItemGet(34);
                func_0016E400(34, 1);
                func_0016E400(31, 1);
                func_0016DCE0(1);
                func_001C2290(0.0f, 2);
                func_0016DB80(15);
                func_0016DB80(17);
                return;
            }
        case 209:
        case 211:
        case 213:
        case 214:
            break;
        case 212:
            D_1D3169C &= ~1024;
            break;
        case 215:
            D_01F72DC8_amusement_00 = 0;
    }
}

void func_01F6E810_amusement_00(void) {
    Vector4 vector1;
    Vector4 vector2;
    D_01F72D90_amusement_00 = 1;
    switch ((short) RoomName()) {
        case 214:
            if (!GET_BIT(D_1D3169C, 6)) {
                vector1                 = D_01F72C20_amusement_00;
                D_01F72DA0_amusement_00 = func_0016D240(1.0f, 5000.0f, 15200, &vector1, 0, 0);
                break;
            } else {
                D_01F72DA0_amusement_00 = -1;
                break;
            }
        case 215:
            if (!GET_BIT(D_1D3169C, 6)) {
                vector2                 = D_01F72C30_amusement_00;
                D_01F72DA0_amusement_00 = func_0016D240(1.0f, 5000.0f, 15200, &vector2, 0, 0);
                break;
            } else {
                D_01F72DA0_amusement_00 = -1;
                break;
            }
    }
}

#ifdef HOLY_CANDLE
void func_01F6E920_amusement_00(void) {
    Vector4 vector1;
    Vector4 vector2;

    if (D_01F72D90_amusement_00 == 0) {
        func_01F6E810_amusement_00();
    }

    switch ((short) RoomName()) {
        case 210:
            if (!GET_BIT(D_01D31640, 1) || GET_BIT(D_1D31648, 15)) {
                func_0016CA40(1);
            }
            if (func_00190950() == 1) {
                clAddDynamicWall(&D_01F70290_amusement_00);
                clAddDynamicWall(&D_01F70420_amusement_00);
                clAddDynamicWall(&D_01F70510_amusement_00);
                clAddDynamicWall(&D_01F70740_amusement_00);
            }
            clAddDynamicWall(&D_01F706A0_amusement_00);
            if (GET_BIT(D_1D31644, 30)) {
                func_0016CA40(3);
                return;
            }
            break;

        case 211:
            if (func_00190950() == 1) {
                clAddDynamicWall(&D_01F71D20_amusement_00);
                return;
            }
            break;

        case 212:
            if (GET_BIT(D_1D3169C, 10) && (func_01F6ED00_amusement_00() != 0)) {
                D_1D3169C |= 512;
                D_1D3169C &= ~1024;
            }
            if (GET_BIT(D_1D3169C, 9)) {
                func_0016CA40(1);
                clAddDynamicWall(&D_01F72360_amusement_00);
                if (!GET_BIT(D_1D3169C, 11)) {
                    func_0016CA40(22);
                    return;
                }
            } else {
                func_0016CA40(2);
                return;
            }
            break;

        case 213:
            if (func_00190950() == 1) {
                clAddDynamicWall(&D_01F708D0_amusement_00);
                clAddDynamicWall(&D_01F70970_amusement_00);
                return;
            }
            break;
        case 214:
            if (GET_BIT(D_1D3169C, 7)) {
                func_0016CA40(2);
            } else {
                func_0016CA40(1);
                clAddDynamicWall(&D_01F71C80_amusement_00);
            }
            if (GET_BIT(D_1D3169C, 6)) {
                func_0016CA40(3);
            }
            if (func_00190950() == 1) {
                clAddDynamicWall(&D_01F71960_amusement_00);
                clAddDynamicWall(&D_01F71A00_amusement_00);
                clAddDynamicWall(&D_01F71B40_amusement_00);
                clAddDynamicWall(&D_01F71BE0_amusement_00);
            }
            if (D_01F72DA0_amusement_00 != -1) {
                vector1 = D_01F72C40_amusement_00;
                func_0016D170(15200, &vector1, 0, 0, 1.0f, 5000.0f, D_01F72DA0_amusement_00);
                return;
            }
            break;

        case 215:
            if (GET_BIT(D_1D3169C, 7)) {
                func_0016CA40(2);
            } else {
                func_0016CA40(1);
            }
            if ((D_01F72DC8_amusement_00 == 0) && (func_00190950() == 1)) {
                clAddDynamicWall(&D_01F70A10_amusement_00);
                clAddDynamicWall(&D_01F71140_amusement_00);
                clAddDynamicWall(&D_01F718C0_amusement_00);
            }
            if (D_01F72DA0_amusement_00 != -1) {
                vector2 = D_01F72C50_amusement_00;
                func_0016D170(15200, &vector2, 0, 0, 1.0f, 5000.0f, D_01F72DA0_amusement_00);
            }
            break;

        case 209:
        default:
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/stage/amusement_00", func_01F6E920_amusement_00);
#endif

#ifdef HOLY_CANDLE
int func_01F6ED00_amusement_00(void) {
    Vector4 vector;
    Vector4 rotation;
    double x, z;
    float f;

    switch (D_01F72D80_amusement_00) {
        case 0:
            if (!GET_BIT(D_1D3169C, 8))
                return false;

            f = 1500.0f + 3000.0f * shRandF();
            D_01F72D80_amusement_00++;
            D_01F72D88_amusement_00 = f;

        case 1:
            func_001908A0(&vector.x, &vector.z);

            x = func_0012BB10(vector.x - 23000.0f, 2.0);
            z = x + func_0012BB10(vector.z - -18200.0f, 2.0);

            if (z < func_0012BB10(D_01F72D88_amusement_00, 2.0))
                return false;

            func_001C18E0(&rotation);
            if (rotation.y >= -QUARTER_TURN || rotation.y <= -PI)
                return false;

            vector.y = 0.0f;
            vector.x = 23000.0f;
            vector.z = -18200.0f;

            func_0015DCD0(1.0f, 10000.0f, 15202, &vector, 0, 0); // candle moment
            D_01F72D80_amusement_00 = 0;

        default:
            return true;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/stage/amusement_00", func_01F6ED00_amusement_00);
#endif

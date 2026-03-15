#include "church_00.h"

UNCURSE_CHURCH();

int func_01F6D680_church_00(void)
{
    int s0 = 0;
    int t = 0;
    float cue = 0.0f;
    
    switch (D_01F6E600_church_00) {
    case 0:
        func_00190A20(2);
        func_00316C50(0);
        func_0016ECE0(6);

        D_01F6E608_church_00 = 0;
        D_01F6E620_church_00 = D_01F6E3B0_church_00;
        D_01F6E618_church_00 = D_01F6E480_church_00;
        D_01F6E610_church_00 = 0.0f;

        func_001C2290(2, 0.0f);
        D_01F6E600_church_00++;
    case 1:
        if (func_0016C540(&D_01F6E4D0_church_00, &D_01F6E530_church_00) == 0) {

            D_01F6E608_church_00 = (int)func_001643C0();
                
            
            t = D_01F6E608_church_00;

            if (t < 0x891 && t > 0x48A) {
                func_00300390();
            }
            
            cue = D_01F6E620_church_00->t;

            if (!(cue <= 0.0f)) {
                float cur = (float)D_01F6E608_church_00;
                if (cue <= cur) {
                    func_0013D250(0, D_01F6E620_church_00->id, 1.0f);
                    D_01F6E620_church_00 =
                        (struct ChurchStruct00*)((char*)D_01F6E620_church_00 + 8);
                }
            }
            

            if (!((float)D_01F6E608_church_00 < 4780.0f)) {

                if (D_01F6E618_church_00->t == 0.0f) {
                    D_01F6E610_church_00 = 0.0f;
                    D_01F6E618_church_00 = D_01F6E480_church_00;
                }

                D_01F6E610_church_00 = D_01F6E610_church_00 + (30.0f * shGetDT());

                if (D_01F6E618_church_00->t <= D_01F6E610_church_00) {
                    func_0013D250(0, D_01F6E618_church_00->id, 1.0f);
                    D_01F6E618_church_00 =
                        (struct ChurchStruct00*)((char*)D_01F6E618_church_00 + 8);
                }
            }

        } else {
            if (func_001646C0() != 0) {
                s0 = 1;
            } else {
                SeCall(1.0f, 0.0f, 0x4A38);
            }
            D_01F6E600_church_00++;
            func_0019A940();
        }
        break;

    case 2:
        if (func_0019A9B0(1.2f) == 0) {
            break;
        }
        D_01F6E600_church_00++;
        func_0019A940();
        SeCall(1.0f, 0.0f, 0x4A39);

    case 3:
        if (func_0019A9B0(3.0f) != 0) {
            s0 = 1;
        }
        break;
    }

    if (s0 != 0) {
        func_00190A20(0);
        func_0013D280(0);
        D_01F6E600_church_00 = 0;
        func_001C2290(5, 0.8f);
    }

    return s0;
}

int func_01F6D9C0_church_00(int arg0) {

    switch (D_01F6E600_church_00) {
        case 0:
            func_00190A20(2);
            func_001C2290(3, 0.8f);
            D_01F6E600_church_00 = 1;
        case 1:
            if (func_001C2580(2) == 0) {
                return 0;
            }
            D_01F6E600_church_00 = 2;
            func_001C2290(5, 0.8f);
        case 2:
            if (func_0016BED0(D_01F6E550_church_00[arg0], D_01F6E560_church_00[arg0]) == 0) {
                return 0;
            }
            D_01F6E600_church_00 = 3;
            func_001C2290(5, 0.8f);
        case 3:
            if (func_001C2580(4) == 0) {
                return 0;
            }
            func_00190A20(0);
        default:
            D_01F6E600_church_00 = 0;
            return 1;
    }
}

void func_01F6DB00_church_00(void) {
    func_01F6D9C0_church_00(0);
}

void func_01F6DB10_church_00(void) {
    func_01F6D9C0_church_00(1);
}

void func_01F6DB20_church_00(void) {
    func_01F6D9C0_church_00(2);
}

void func_01F6DB30_church_00(void) {
    func_01F6D9C0_church_00(3);
}

void func_01F6DB40_church_00(void) {
    func_01F6D9C0_church_00(4);
}

void func_01F6DB50_church_00(void) {
    func_01F6D9C0_church_00(5);
}

int func_01F6DB60_church_00(void)
{
    int s0 = 0;
    int var_1 = 1;

    switch (D_01F6E600_church_00) {
    case 0:
        func_00190A20(2);
        func_0019A940();
        func_01F6DCD0_church_00();
        D_01F6E600_church_00 = 1;
        break;

    case 1:
        if (func_0019A9B0(0.5f) != 0) {
            if (((u_int)D_1D316A4 >> 14) & 1) {
                D_01F6E600_church_00 = 3;
            } else {
                D_01F6E600_church_00 = 2;
            }
        }
        break;

    case 2:
        if (func_0016C1C0(0x43) != 0) {
            D_01F6E600_church_00 = 4;
        }
        break;

    case 3:
        if ((func_0013D080(0, 0, var_1, var_1) != 0) ||
            (func_0013D080(0, 0, var_1, 2)   != 0)) {
            D_01F6E600_church_00 = 4;
        }
        break;

    case 4:
        D_1D316A4 |= 0x4000;
        func_001C0EE0(0);
        func_00190A20(0);
        s0 = 1;
        D_01F6E600_church_00 = 0;
        break;
    }

    return s0;
}

int func_01F6DCD0_church_00(void) {
    func_001C0EB0((void*)func_01F6DCF0_church_00, 0x000F423F, 0);
}


void func_01F6DCF0_church_00(Q* arg0, int* arg1, Q* arg2, int*  arg3, int*  arg4)
{
    Q sp0;
    Q sp10;

    sp0.s32  = D_01F6E570_church_00.s32;
    sp10.s32 = D_01F6E580_church_00.s32;

    vec_copy(&arg0->u128, &sp0.u128);
    *arg1 = 0;
    vec_copy(&arg2->u128, &sp10.u128);
    *arg3 = 0;
    *arg4 = 0;
}

void func_01F6DD40_church_00(void) {
    D_01F6E600_church_00 = 0;
    if (!((D_1D31644 >> 0x18) & 1)) {
        func_0016DCE0(0xA);
        func_0016E400(0x18, 0);
    }
}

void func_01F6DD90_church_00(void) {
    if ((D_1D31644 >> 0x18) & 1) {
        func_0016CA40(1);
        func_0016CA40(0xC);
        func_0016CA40(2);
    }
    if (!((D_1D316A4 >> 0xD) & 1)) {
        func_0016CA40(0xD);
    }
}

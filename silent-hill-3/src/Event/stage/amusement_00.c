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
            func_001602D0(0x272A, 1, 1, 1.0f);
        }
        D_01F72D80_amusement_00 = 0;
    }
    return ret;
}

int func_01F6D740_amusement_00(void) {
    float temp_f0;
    float temp_f2;
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
    temp_f0 = func_001643C0();
    temp_f2 = D_01F72DD8_amusement_00->unk0;
    if (temp_f2 > 0.0f && temp_f2 <= temp_f0) {
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
    float temp_f0;
    float temp_f20;
    float temp_f2;
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
                ret = func_0016C540(&D_01F72AF0_amusement_00, &D_01F72B50_amusement_00);
                temp_f20 = func_001643C0();
                temp_f0 = func_001643C0();
                temp_f2 = D_01F72DD0_amusement_00->unk0;
                if (temp_f2 > 0.0f && temp_f2 <= temp_f0) {
                    func_0013D250(0, D_01F72DD0_amusement_00->unk4, 1.0f);
                    D_01F72DD0_amusement_00++;
                }
                if (temp_f20 >= 1032.0f) {
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
    float temp_f0_2;
    float temp_f2;
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
            ret = func_0016C540(&D_01F72B90_amusement_00, &D_01F72BF0_amusement_00);
            D_01F72D80_amusement_00 = 8;
            func_00258910();
            func_001EC590(0);
            func_001C2290(0.0f, 1);
            break;
        case 8:
            ret = func_0016C540(&D_01F72B90_amusement_00, &D_01F72BF0_amusement_00);
            temp_f0_2 = func_001643C0();
            temp_f2 = D_01F72DA8_amusement_00->unk0;
            if (temp_f2 > 0.0f && temp_f2 <= temp_f0_2) {
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

INCLUDE_ASM("asm/nonmatchings/Event/stage/amusement_00", func_01F6DEA0_amusement_00);

int func_01F6E020_amusement_00(void) {
    int sp10[4];

    sp10 = D_01F72C10_amusement_00;
    
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
        func_0015DCD0(1.0f, 10000.0f, 0x3B61, &sp10, 0, 0);
        func_0016D0E0(0x3B60, D_01F72DA0_amusement_00);
        D_01F72DA0_amusement_00 = -1;
    }
    func_00190A20(0);
    D_01F72D80_amusement_00 = 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/amusement_00", func_01F6E120_amusement_00);

INCLUDE_ASM("asm/nonmatchings/Event/stage/amusement_00", func_01F6E420_amusement_00);

#ifdef BROKEN
int func_01F6E590_amusement_00(void) {
    switch (D_01F72D80_amusement_00) {
    case 0:
        func_00190A20(2);
        SeCall(19025, 0.0f, 1.0f);
        D_01F72D80_amusement_00++;
    case 1:
        if (func_0016C1C0(0x3F) == 0) {
            return 0;
        }
        func_001C2290(0.5f, 3);
        SeCall(19023, 0.0f, 1.0f);
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
#else
INCLUDE_ASM("asm/nonmatchings/Event/stage/amusement_00", func_01F6E590_amusement_00);
#endif

u_int func_01F6E6A0_amusement_00(int arg0) {
    int x;
    switch (arg0) {
        case 1:
            x = GET_BIT(D_1D3169C, 9) ? 0 : 1;
            break;
    }
    return x;
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/amusement_00", func_01F6E6D0_amusement_00);

#ifdef BROKEN
void func_01F6E810_amusement_00(void) {
    int sp10[4];
    int sp20[4];
    D_01F72D90_amusement_00 = 1;
    switch ((short)func_00170810()) {
    case 0xD6:
        if (!GET_BIT(D_1D3169C, 6)) {
            sp10 = D_01F72C20_amusement_00;
            D_01F72DA0_amusement_00 = func_0016D240(0x3B60, &sp10, 0, 0, 1.0f, 5000.0f);
            return;
        }
        D_01F72DA0_amusement_00 = -1;
        return;
    case 0xD7:
        if (!GET_BIT(D_1D3169C, 6)) {
            sp20 = D_01F72C30_amusement_00;
            D_01F72DA0_amusement_00 = func_0016D240(0x3B60, &sp20, 0, 0, 1.0f, 5000.0f);
        } else {
            D_01F72DA0_amusement_00 = -1;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/stage/amusement_00", func_01F6E810_amusement_00);
#endif

INCLUDE_ASM("asm/nonmatchings/Event/stage/amusement_00", func_01F6E920_amusement_00);

INCLUDE_ASM("asm/nonmatchings/Event/stage/amusement_00", func_01F6ED00_amusement_00);

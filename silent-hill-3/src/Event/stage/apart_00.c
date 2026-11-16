#include "apart_00.h"

INCLUDE_ASM("asm/nonmatchings/Event/stage/apart_00", func_01F6D680_apart_00);

void func_01F6D680_apart_00(void);

int func_001DE5B0(void (*cb)(void), int arg, int flag);

int func_01F6D7B0_apart_00(int arg0) {
    return func_001DE5B0(func_01F6D680_apart_00, arg0, 1);
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/apart_00", func_01F6D7D0_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/stage/apart_00", func_01F6D840_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/stage/apart_00", func_01F6D920_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/stage/apart_00", func_01F6DB90_apart_00);

int func_01F6DDA0_apart_00(void) {
    int temp_s0;
    SubCharacter* missy;

    switch (D_01F70060_apart_00) {
        case 0:
            func_001C2290(2, 0.0f);
            D_01F70060_apart_00++;
            break;
    }
    temp_s0 = func_0016C540(&D_01F6FCC0_apart_00, &D_01F6FD20_apart_00);
    missy   = shCharacterGetSubCharacter(MISSIONARY_CHARA_KIND, MISSIONARY_ID);
    if (temp_s0 == 0) {
        func_001E22F0(MISSIONARY_CHARA_KIND, MISSIONARY_ID, 0);
        func_001DC9E0(missy, 0);
    } else {
        func_001E22F0(MISSIONARY_CHARA_KIND, MISSIONARY_ID, 1);
        func_001DC9E0(missy, 1);
        func_001C2290(5, 0.5f);
        if (func_001646C0() != 0) {
            func_001602D0(0x2732, 3, 1, 1.0f);
        }
    }
    return temp_s0;
}

int func_01F6DEB0_apart_00(void) {
    int temp_v0;
    int var_v0;

    temp_v0 = func_0016C540(&D_01F6FD40_apart_00, &D_01F6FDA0_apart_00);
    if (temp_v0 != 0) {
        func_0016DCE0(0);
        var_v0    = D_1D316AC & 0xDFFFFFFF;
        D_1D316AC = var_v0;
    } else {
        var_v0    = D_1D316AC | 0x20000000;
        D_1D316AC = var_v0;
    }

    return temp_v0;
}

int func_01F6DF30_apart_00(void) {
    int temp_v0;

    temp_v0 = func_0016C540(&D_01F6FDC0_apart_00, &D_01F6FE20_apart_00);

    if (temp_v0 != 0) {
        if (func_001646C0() != 0) {
            func_001602D0(0x271E, 3, 1, 1.0f);
        }

        func_001C2290(5, 0.5f);
    }

    return temp_v0;
}

void func_01F6DFB0_apart_00(void) {

    switch (D_01F70058_apart_00) {
        case 0:
            func_001603E0(2, 1);
            D_1D316AC |= 0x20000000;
            D_01F70058_apart_00 += 1;
            break;
    }

    if (func_0016C9B0(&D_01F6FE40_apart_00, 1, 1) != 0) {
        D_1D316AC &= 0xDFFFFFFF;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/apart_00", func_01F6E050_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/stage/apart_00", func_01F6E060_apart_00);

int func_01F6E770_apart_00(int arg0) {
    int condition = D_01F70020_apart_00[arg0].value == 3;
    return !condition;
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/apart_00", func_01F6E7A0_apart_00);

void func_01F6E800_apart_00(void) {

    if (!GET_FLAG(D_1D31670, 0x51)) {
        func_01F6EB70_apart_00();
        D_1D31670[2] |= 0x20000;
    }

    switch (RoomName()) {

        case APARTMENTS_ROOFTOP:
            func_01F6E050_apart_00();
            D_01F70060_apart_00 = 0;
            if (!GET_BIT(D_01D31640, 0x16)) {
                func_00316C50(0);
                if (GET_BIT(D_01D31640, 0x15)) {
                    func_001C2290(2, 0.0f);
                }
            }
            break;

        case APARTMENTS_LIVING_ROOM:
            if (func_0016D5B0() != 0) {
                func_001C2290(2, 0.0f);
                break;
            }
            if (!GET_FLAG(D_1D31670, 0x4E) && !(GET_FLAG(D_1D31670, 0x45))) {
                D_1D31670[2] |= 0x20;
            }
            D_1D3171C |= 0x200;
            break;

        case APARTMENTS_HARRYS_BEDROOM:
            D_1D3171C |= 0x40;
            break;

        case APARTMENTS_HALLWAY:
            D_1D3171C |= 0x100;
            D_1D3171C |= 0x400;
            break;

        case APARTMENTS_OUTSIDE:
            D_01F70058_apart_00 = 0;
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/apart_00", func_01F6E9A0_apart_00);

void func_01F6EB70_apart_00(void) {
    if (func_00199C70(7) == 1) {
        if (!GET_FLAG(D_1D31670, 0x47)) {
            D_1D31670[2] |= 0x80;
        }
    }
    if ((func_00199C70(9) == 1) && !GET_FLAG(D_1D31670, 0x4E)) {
        D_1D31670[2] |= 0x4000;
    }
}

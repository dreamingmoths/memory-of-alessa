#include "apart_00.h"

typedef struct Apart00Entry {
    int   unknown_0x0;
    float unknown_0x4;
    float unknown_0x8;
} Apart00Entry;

typedef struct Apart00Struct {
    char  unknown_0x0[0x1B8];
    float unknown_0x1B8;
    Apart00Entry entries[];
} Apart00Struct;

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6D680_apart_00);

void func_01F6D680_apart_00(void);

int func_001DE5B0(void (*cb)(void), int arg, int flag);

int func_01F6D7B0_apart_00(int arg0) {
    return func_001DE5B0(func_01F6D680_apart_00, arg0, 1);
}


void func_01F6D7D0_apart_00(void* arg0) {
    char* base;
    char* temp_v1;
    int temp_a0;
    int temp_a1;
    int addr;

    base = (char*)arg0;

    temp_a1 = *(int*)(base + 0x1A8);

    addr = temp_a1 * 0xC;
    addr += (int)base;
    temp_v1 = (char*)addr;

    temp_a0 = *(int*)(temp_v1 + 0x1BC);

    if ((temp_a0 != 0) &&
        !(*(float*)(base + 0x1B4) < *(float*)(temp_v1 + 0x1C0))) {

        func_001C2290(
            temp_a0,
            temp_a1,
            *(float*)(temp_v1 + 0x1C4)
        );

        *(int*)(base + 0x1A8) =
            *(int*)(base + 0x1A8) + 1;
    }
}

void func_01F6D840_apart_00(void* arg0)
{
    int s0;
    int s1;
    char* s2;
    Apart00Struct* s3;

    int a0;
    float f0;
    float f1;
    float t;

    s3 = (Apart00Struct*)arg0;

    func_0019B240(arg0, 0x240);

    s2 = D_01F6FB80_apart_00;
    s0 = 0;
    s1 = 0;

    do {
        func_0016F550(*(int*)(s2 + 0x4), s0);

        a0 = *(int*)(s2 + 0x10);
        if (a0 != 0) {
            s3->entries[s1].unknown_0x0 = a0;

            f0 = *(float*)(s2 + 0x8);
            s3->entries[s1].unknown_0x4 = f0;

            f0 = *(float*)(s2 + 0x14);
            s3->entries[s1].unknown_0x8 = f0;

            s1 = s1 + 1;
        }

        a0 = *(int*)(s2 + 0x18);
        if (a0 != 0) {
            s3->entries[s1].unknown_0x0 = a0;

            t  = *(float*)(s2 + 0x1C);
            f1 = *(float*)(s2 + 0x0C);
            s3->entries[s1].unknown_0x4 = f1 - t;

            f0 = *(float*)(s2 + 0x1C);
            s3->entries[s1].unknown_0x8 = f0;

            s1 = s1 + 1;
        }

        s0 = s0 + 1;
        s2 = s2 + 0x20;
    } while (s0 < 5);

    f0 = *(float*)(s2 + 0x8);
    s3->unknown_0x1B8 = f0;
}

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6D920_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6DB90_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6DDA0_apart_00);

int func_01F6DEB0_apart_00(void)
{
    int temp_v0;
    int var_v0;

    temp_v0 = func_0016C540(&D_01F6FD40_apart_00, &D_01F6FDA0_apart_00);
    if (temp_v0 != 0) {
        func_0016DCE0(0);
        var_v0 = D_1D316AC & 0xDFFFFFFF;
        D_1D316AC = var_v0;
    } else {
        var_v0 = D_1D316AC | 0x20000000;
        D_1D316AC = var_v0;
    }

    return temp_v0;
}

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6DF30_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6DFB0_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6E050_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6E060_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6E770_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6E7A0_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6E800_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6E9A0_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6EB70_apart_00);

#include "amusement_01.h"

#ifdef NON_MATCHING
int func_01F6D680_amusement_01() {
    int ret;

    // @todo is there a cleaner match?
    switch (D_01F74C88_amusement_01)
        case 0: {
            func_001C2290(2, 0.8f);
            D_01F74C98_amusement_01 = 45.0f;
            D_01F74CA0_amusement_01 = 150.0f;
            D_01F74C88_amusement_01++;
        }

    ret = func_0016C540(&D_01F74510_amusement_01, &D_01F74570_amusement_01);
    func_01F703B0_amusement_01(D_01F74C98_amusement_01, D_01F74CA0_amusement_01);

    switch (D_01F74C88_amusement_01)
        case 1:
            if (func_001643C0() > 438.0f) {
                D_01F74C98_amusement_01 = 50.0f;
                D_01F74CA0_amusement_01 = 100.0f;
                D_01F74C88_amusement_01++;
            }

    if (ret != 0) {
        D_01F74C88_amusement_01 = 0;
    }

    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6D680_amusement_01);
#endif

void func_01F6D7A0_amusement_01() {
    func_0016C540(&D_01F74590_amusement_01, &D_01F745F0_amusement_01);
}

int func_01F6D7C0_amusement_01() {
    int audioIsPlaying;

    D_1D3169C |= 0x1000;

    // noping this function prevents the audio from playing
    audioIsPlaying = func_0016CF80(12, 50, &D_01F713D0_amusement_01);


    if (audioIsPlaying != 0) {
        func_0016CF70();
        D_1D3169C &= ~0x1000;
    }

    return audioIsPlaying;
}

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6D840_amusement_01);
    
void func_01F6DC40_amusement_01() {
    func_001C0EB0(func_01F6DC70_amusement_01, 90, 1);
    D_01F74CB0_amusement_01 = 0;
}

static void func_01F6DC70_amusement_01(__int128* arg0, int* arg1, __int128* arg2, int* arg3, int* arg4) {
    qcopy(arg0, &D_01F74680_amusement_01);
    *arg1 = 1;
    qcopy(arg2, &D_01F74670_amusement_01);
    *arg3 = 0;
    *arg4 = 0;
}

void func_01F6DCB0_amusement_01() {
    func_001C0EB0(func_01F6DCF0_amusement_01, 999999, 1);
    D_01F74CB0_amusement_01 = 0;
}

void func_01F6DCF0_amusement_01(__int128* arg0, s32* arg1, __int128* arg2, s32* arg3, s32* arg4) {
    sceVu0FVECTOR sp60;

    func_0018FE60((__int128*) &sp60);
    sp60[1] += -700.0f;
    qcopy(arg0, &D_01F74690_amusement_01[D_01F74CB0_amusement_01]);
    *arg1 = 1;
    if (D_01F74CB0_amusement_01 != 2) {    
        qcopy(arg2, sp60);
    } else {
        qcopy(arg2, D_01F74670_amusement_01);
    }
    *arg3 = 1;
    *arg4 = 0;
}

void func_01F6DDC0_amusement_01(void) {
    D_01F74CB0_amusement_01++;
}

int func_01F6DDE0_amusement_01() {
    float limit;
    int ret = 0;
    int i;
    float* cur;
    int state = D_01F74C88_amusement_01;

    switch (state) {
        case 0:
            func_01F6DC40_amusement_01();
            D_01F74D98_amusement_01 = 0;
            D_01F74C88_amusement_01++;
            /* fallthrough */
        case 1:
            for (i = 0; cur = D_01F74610_amusement_01[i], cur[0] != 0.0f; i++) {
                limit = D_01F74D98_amusement_01;
                if (cur[0] <= limit && cur[1] > limit) {
                    func_0016CA40(1);
                }
            }
            D_01F74D98_amusement_01++;
            if (D_01F74D98_amusement_01 < 90) {
                break;
            }
        case 2:
            ret = 1;
            D_01F74C88_amusement_01 = 0;
    }

    return ret;
}

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6DF10_amusement_01);

int func_01F6E1A0_amusement_01() {
    // entering the room with the metal spikes trap
    int audioIsPlaying;

    D_1D3169C |= 0x1000;
    audioIsPlaying = func_0016CF80(15, 82, &D_01F714A0_amusement_01);

    if (audioIsPlaying != 0) {
        func_0016CF70();
        D_1D3169C &= ~0x1000;
    }

    return audioIsPlaying;
}

int func_01F6E220_amusement_01() {
    // going under the spikes
    int audioIsPlaying;

    D_1D3169C |= 0x1000;
    audioIsPlaying = func_0016CF80(16, 86, &D_01F714D0_amusement_01);

    if (audioIsPlaying != 0) {
        func_0016CF70();
        D_1D3169C &= ~0x1000;
    }

    return audioIsPlaying;
}

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6E2A0_amusement_01);

int func_01F6E710_amusement_01(void) {
    int audioIsPlaying;

    D_1D3169C |= 0x1000;
    audioIsPlaying = func_0016CF80(17, 90, &D_01F71500_amusement_01);
    if (audioIsPlaying != 0) {
        func_0016CF70();
        D_1D3169C &= ~0x1000;
    }
    return audioIsPlaying;
}

int func_01F6E790_amusement_01(void) {
    int audioIsPlaying;

    D_1D3169C |= 0x1000;
    audioIsPlaying = func_0016CF80(18, 95, &D_01F71530_amusement_01);
    if (audioIsPlaying != 0) {
        func_0016CF70();
        D_1D3169C &= ~0x1000;
    }
    return audioIsPlaying;
}

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6E810_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6E9A0_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6F3C0_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6F430_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6F4E0_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6F5C0_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6F6C0_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6F7A0_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6FA20_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6FB50_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6FC80_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6FDC0_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6FED0_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F70000_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F701B0_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F702A0_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F70390_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F703B0_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F70750_amusement_01);

void func_01F70780_amusement_01(void) {
    long id;
    int count;
    int* cur;
    int temp_v0;

    count = 0;
    for (cur = D_01F74B10_amusement_01; *cur != 0; cur++) {
        temp_v0 = func_0012FD80(PENDULUM_CHARA_ID, *cur);
        if (temp_v0 != 0) {
            if (func_001E2110(temp_v0) == 0) {
                count++;
            }
            if ((*cur != 0x182) && (*cur != 0x183)) {
                if (!((D_1D3169C >> 0xF) & 1)) {
                    shCharacter_Manage_Delete(PENDULUM_CHARA_ID, *cur);
                } else if ((1 < (func_00199770())) && (2 < count)) {
                    shCharacter_Manage_Delete(PENDULUM_CHARA_ID, *cur);
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F70870_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F709D0_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F70A90_amusement_01);

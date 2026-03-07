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

int func_01F6F4E0_amusement_01(void) {
    SubCharacter* scp;
    int ret = func_0016C540(&D_01F748F0_amusement_01, &D_01F74950_amusement_01);
    scp = shCharacterGetSubCharacter(0x104, 0x178);
    if (ret != 0) {
        if (func_0019A9B0(2.0f) != 0) {
            scp->pos.x = -59676.0f;
            scp->pos.y = -8.4108f;
            scp->pos.z = 58407.0f;
            scp->rot.y = 3.1415927f;
            func_001DC9E0(scp, 1);
            func_001C2290(5, 0.5f);
            func_00160AF0(10);
            return 1;
        }
    } else {
        func_0019A940();
        func_001DC9E0(scp, 0);
    }
    return 0;
}

int func_01F6F5C0_amusement_01(void) {
    int ret = func_0016C540(&D_01F74970_amusement_01, &D_01F749D0_amusement_01);
    SubCharacter* scp;
    switch (D_01F74C88_amusement_01) {              /* irregular */
    case 0:
        func_001C2290(3, 0.5f);
        D_01F74C88_amusement_01 += 1;
        /* fallthrough */
    case 1:
        scp = shCharacterGetSubCharacter(0x104, 0x178);
        break;
    }
    if (ret != 0) {
        scp->pos.x = -59676.0f;
        scp->pos.y = -8.4108f;
        scp->pos.z = 58407.0f;
        scp->rot.y = 3.1415927f;
        func_001DC9E0(scp, 1);
        func_001C2290(5, 0.5f);
        D_01F74C88_amusement_01 = 0;
    } else {
        func_001DC9E0(scp, 0);
    }
    return ret;
}

int func_01F6F6C0_amusement_01(void) {
    int ret = 0;
    switch (D_01F74C88_amusement_01) {
    case 0:
        if (func_0016C540(&D_01F749F0_amusement_01, &D_01F74A50_amusement_01) != 0) {
            D_01F74C88_amusement_01++;
        case 1:
            if (func_00160520(2) != 0) {
                ret = 1;
            }
        }
        break;
    }
    if (ret != 0) {
        func_001602D0(0x273A, 3, 1, 1.0f);
        func_001C2290(5, 0.5f);
        D_01F74C88_amusement_01 = 0;
        D_1D316AC &= 0xDFFFFFFF;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6F7A0_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6FA20_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6FB50_amusement_01);

int func_01F6FC80_amusement_01() {
    switch (D_01F74C88_amusement_01) {              /* irregular */
        case 0:
            func_00190A20(5);
            D_01F74C88_amusement_01 = 1;
            func_00317420(0x46U);
            /* fallthrough */
        case 1:
            if (func_00190C00() == 0) {
                return 0;
            }
            D_01F74C88_amusement_01 = 2;
            D_1D3169C |= 0x8000;
            func_0016D6B0(0x46U);
            SeCall(1.0f, 0.0f, 0x2B21);
            func_00317490(0x46, 0.2f);
        case 2:
            if (func_0016C1C0(0xBF) == 0) {
                return 0;
            }
            func_00190A20(6);
            func_003174B0(0.2f);
            D_01F74C88_amusement_01 = 3;
        case 3:
            if (func_00190C00() == 0) {
                return 0;
            }
            func_00190A20(0);
            D_01F74C88_amusement_01 = 0;
        default:
            return 1;
    }
}

int func_01F6FDC0_amusement_01() {
    switch (D_01F74C88_amusement_01) {
        case 0:
            D_01F74C88_amusement_01 = 1;
            func_00317420(0x47U);
            /* fallthrough */
        case 1:
            D_01F74C88_amusement_01 = 2;
            D_1D3169C |= 0x10000;
            func_0016D6B0(0x47U);
            SeCall(1.0f, 0.0f, 0x2B21);
            func_00317490(0x47, 0.2f);
            /* fallthrough */
        case 2:
            if (func_0016C1C0(0xC1) == 0) {
                return 0;
            }
            func_003174B0(0.2f);
            D_01F74C88_amusement_01 = 3;
        case 3:
            func_00190A20(0);
            D_01F74C88_amusement_01 = 0;
        default:
            return 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F6FED0_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F70000_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F701B0_amusement_01);

s32 func_01F702A0_amusement_01(void) {
    switch (D_01F74C88_amusement_01) {
        case 0:
            func_00190A20(2);
            D_1D3169C |= 0x200000;
            SeCall(1.0f, 0.0f, 0x3BC5);
            if (((u32) D_1D3169C >> 0x14) & 1) {
                SeCall(1.0f, 0.0f, 0x4A3B);
            }
            D_01F74C88_amusement_01++;
            /* fallthrough */
        case 1:
            if (func_0016C1C0(0xC0) == 0) {
                return 0;
            }
            func_0016C3C0();
            func_00190A20(0);
            D_01F74C88_amusement_01 = 0;
        default:
            return 1;
    }
}

void func_01F70390_amusement_01() {
    func_01F703B0_amusement_01(20.0f, 40.0f);
}

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F703B0_amusement_01);

INCLUDE_ASM("asm/nonmatchings/Event/amusement_01", func_01F70750_amusement_01);

void func_01F70780_amusement_01(void) {
    long id;
    int count;
    int* cur;
    SubCharacter* scp;

    count = 0;
    for (cur = D_01F74B10_amusement_01; *cur != 0; cur++) {
        scp = shCharacterGetSubCharacter(PENDULUM_CHARA_ID, *cur);
        if (scp != 0) {
            if (func_001E2110(scp) == 0) {
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

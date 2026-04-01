#include "en_common.h"

void func_0022EB70(SubCharacter* scp) {
    int i;
    EnemyWork* dp = &D_01F27760;
    for (i = 0; i < 0x20; i++) {
        if (dp->unk_0x160 == 0) {
            dp->scp = scp;
            dp->unk_0x160 = i + 1;
            func_0022FAC0(dp);
            return;
        }
        dp++;
    }
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022EBD0);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022EC70);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022ECC0);

void func_0022ED30(void) {
    int i;
    EnemyWork* var_s0;

    var_s0 = &D_01F27760;
    i = 0;
    do {
        if (var_s0->unk_0x160 != 0) {
            func_0022FC20(var_s0);
        }
        i++;
        var_s0++;
    } while (i < 0x20);
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022ED90);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022EE20);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022EEB0);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022EF10);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022EF30);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022EF40);

u_int func_0022EFD0(u_int mask) {
    return D_01F2A564 & mask;
}

void func_0022EFE0(void) {
    D_01F2A564 |= 0x40;
}

void func_0022F000(void) {
    D_01F2A564 &= ~0x40;
}

void func_0022F020(void) {
    D_01F2A564 |= 0x80;
}

void func_0022F040(void) {
    D_01F2A564 &= ~0x80;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F060);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F070);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F0E0);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F130);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F150);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F170);

void func_0022F1D0(void) {
    D_01F2A581 = 0;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F1E0);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F220);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F270);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F390);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F4C0);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F630);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F870);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F9A0);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022FA20);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022FA60);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022FA90);

void func_0022FAC0(EnemyWork* work) {
    switch (work->scp->kind) {
        case CLOSER_CHARA_ID:
            func_00230010(work);
            return;
        case DOUBLE_HEAD_CHARA_ID:
            func_00215FA0(work);
            return;
        case NUMB_BODY_CHARA_ID:
            func_002434C0(work);
            return;
        case NURSE_CHARA_ID:
            func_0025D750(work);
            return;
        case INSANE_CANCER_CHARA_ID:
            func_00266550(work);
            return;
        case PENDULUM_CHARA_ID:
            func_00290F00(work);
            return;
        case SPLIT_WORM_CHARA_ID:
            func_00225C20(work);
            return;
        case LEONARD_WOLF_CHARA_ID:
            func_002C3B50(work);
            return;
        case EN_DED1_CHARA_ID:
            func_002EE4F0(work);
            return;
        case MISSIONARY_CHARA_ID:
            func_00286DC0(work);
            return;
        case SCRAPER_CHARA_ID:
            func_002BA120(work);
            return;
        case GOD_CHARA_ID:
            func_002D20B0(work);
            return;
        case SEWER_MONSTER_CHARA_ID:
            func_002D7020(work);
            return;
        case CAROUSEL_HORSE_CHARA_ID:
            func_002DFC40(work);
            return;
        case MEMORY_OF_ALESSA_CHARA_ID:
            func_002E0700(work);
            return;
        case SLURPER_E_CHARA_ID:
            func_00304360(work);
            return;
        case 0x20C: /* unknown */
            func_00312DB0(work);
            return;
        case SLURPER_X_CHARA_ID:
            func_0030DB50(work);
    }
}

void func_0022FC20(EnemyWork* work) {
    switch (work->scp->kind) {
        case CLOSER_CHARA_ID:
            func_002308F0(work);
            return;
        case DOUBLE_HEAD_CHARA_ID:
            func_00216940(work);
            return;
        case SCRAPER_CHARA_ID:
            func_002BA370(work);
            return;
        case SLURPER_E_CHARA_ID:
            func_00304B40(work);
            return;
        case NUMB_BODY_CHARA_ID:
            func_00243EF0(work);
            return;
        case PENDULUM_CHARA_ID:
            func_0029ABF0(work);
            return;
        case NURSE_CHARA_ID:
            func_0025E040(work);
            return;
        case INSANE_CANCER_CHARA_ID:
            func_00266E50(work);
            return;
        case SLURPER_X_CHARA_ID:
            func_0030DE10(work);
    }
}

void func_0022FCF0(EnemyWork* work) {
    switch (work->scp->kind) {
        case CLOSER_CHARA_ID:
            func_00230A00(work);
            break;
        case DOUBLE_HEAD_CHARA_ID:
            func_00216AA0(work);
            break;
        case NUMB_BODY_CHARA_ID:
            func_00244000(work);
            break;
        case NURSE_CHARA_ID:
            func_0025E140(work);
            break;
        case INSANE_CANCER_CHARA_ID:
            func_00266F50(work);
            break;
        case MISSIONARY_CHARA_ID:
            func_002870B0(work);
            break;
        case SCRAPER_CHARA_ID:
            func_002BA510(work);
            break;
        case GOD_CHARA_ID:
            func_002D2420(work);
            break;
        case SLURPER_E_CHARA_ID:
            func_00304C50(work);
            break;
        case SLURPER_X_CHARA_ID:
            func_0030DED0(work);
            break;
        case PENDULUM_CHARA_ID:
            func_00293650(work);
            break;
        case SPLIT_WORM_CHARA_ID:
            func_0022E940(work);
            break;
        case LEONARD_WOLF_CHARA_ID:
            func_002CD8B0(work);
            break;
        case MEMORY_OF_ALESSA_CHARA_ID:
            func_002E0EB0(work);
            break;
    }
}

void func_0022FE80(EnemyWork* work) {
    switch (work->scp->kind) {
        case CLOSER_CHARA_ID:
            func_00230A40(work);
            break;
        case DOUBLE_HEAD_CHARA_ID:
            func_00216B30(work);
            break;
        case NUMB_BODY_CHARA_ID:
            func_00244010(work);
            break;
        case NURSE_CHARA_ID:
            func_0025E150(work);
            break;
        case INSANE_CANCER_CHARA_ID:
            func_00266F60(work);
            break;
        case MISSIONARY_CHARA_ID:
            func_002870F0(work);
            break;
        case SCRAPER_CHARA_ID:
            func_002BA550(work);
            break;
        case GOD_CHARA_ID:
            func_002D2460(work);
            break;
        case SLURPER_E_CHARA_ID:
            func_00304CB0(work);
            break;
        case SLURPER_X_CHARA_ID:
            func_0030DF30(work);
            // @bug maybe accidental fallthrough?
        case PENDULUM_CHARA_ID:
            func_002936A0(work);
            break;
        case SPLIT_WORM_CHARA_ID:
            func_0022E970(work);
            break;
        case LEONARD_WOLF_CHARA_ID:
            func_002CD8F0(work);
            break;
        case MEMORY_OF_ALESSA_CHARA_ID:
            func_002E0EC0(work);
            break;
    }
}

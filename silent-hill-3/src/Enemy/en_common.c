#include "en_common.h"


/* not from here */
void func_001E22F0(u_short kind, u_short id, int arg2);

void func_0022E9B0(void) {
    memset(&enemyWork, 0, sizeof(EnemyWork));
}

void func_0022E9D0(void) {
    enemyWork.unk2E02 = 0;
    enemyWork.Status = 0;
    enemyWork.unk2E08[24] = 0;
    enemyWork.unk2E08[25] = 0;
}


void func_0022EA00(void) {
    enemyWork.Status = 0;
    enemyWork.unk2E08[24] = 0;
    enemyWork.unk2E08[25] = 0;
    enemyWork.unk2E40 = 0;
}

void func_0022EA30(void) {
    int i;
    EnemyWork* work = &enemyWork;
    EnemyData* dp = work->Data;

    switch (work->unk2E00) {
        case 0:
            work->unk2E00++;

        case 1:
            switch (work->unk2E02) {
                case 0:
                    work->Status = 0;
                    work->unk2E02++;
                    /* fallthrough */
                case 1:
                    work->Status &= 0xC0;
                    work->Status |= func_001E2050() << 2;
                    work->Status |= func_001E20C0() << 3;
                    work->Status |= func_001E20E0() << 4;
                    work->Status |= func_001E2070() << 5;
                    for (i = 0; i < ENEMY_DATA_COUNT; i++, dp++) {
                        if (dp->unk_0x160 == 0) continue;
                        if (!(dp->scp->battle.status & 0x2000)) continue;
                        dp->function(dp);
                        func_0022EF40(dp);
                    }
                    func_0022F1D0();
                    break;
            }
    }
}

void func_0022EB70(SubCharacter* scp) {
    int i;
    EnemyData* dp = &enemyWork;
    for (i = 0; i < ENEMY_DATA_COUNT; i++) {
        if (dp->unk_0x160 == 0) {
            dp->scp = scp;
            dp->unk_0x160 = i + 1;
            func_0022FAC0(dp);
            return;
        }
        dp++;
    }
}

#ifdef NON_MATCHING
void func_0022EBD0(EnemyWork* dp) {
    int i;
    SubCharacter* scp;
    EnemyWork* free = &D_01F27760;
    int kind;
    int dp_id;

    for (i = 0; i < 32; i++, free++) {
        if (!free->unk_0x160) continue;
        scp = free->scp;
        kind = dp->kind;
        if (scp->kind != kind) continue;
        
        dp_id = dp->id;
        if (scp->id != dp_id) continue;
        
        func_0022EE20(kind, dp_id);
        memset(free, 0, sizeof(EnemyWork));
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022EBD0);
#endif

int func_0022EC70(int kind) {
    int i;
    EnemyData* dp;
    int count = 0;

    for (dp = enemyWork.Data, i = 0; i < ENEMY_DATA_COUNT; i++, dp++) {
        if ((dp->unk_0x160 != 0) && (dp->scp->kind == kind)) {
            count++;
        }
    }

    return count;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022ECC0);

void func_0022ED30(void) {
    int i;
    EnemyData* var_s0 = &enemyWork;
    i = 0;
    do {
        if (var_s0->unk_0x160 != 0) {
            func_0022FC20(var_s0);
        }
        i++;
        var_s0++;
    } while (i < ENEMY_DATA_COUNT);
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022ED90);

void func_0022EE20(int kind, int id) {
    EnemyData* dp;
    int i;

    for (i = 0, dp = enemyWork.Data; i < ENEMY_DATA_COUNT; i++, dp++) {
        SubCharacter* scp;
        if (dp->unk_0x160 != 0 && (scp = dp->scp, (scp->kind == kind)) && (scp->id == id)) {
            if (scp->battle.status & 0x2000) {
                func_001E22F0(kind, id, 0);
                func_0022FE80(dp);
            }
            return;
        }
    }
}


INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022EEB0);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetFunction);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022EF30);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022EF40);

u_int func_0022EFD0(u_int mask) {
    return enemyWork.Status & mask;
}

void func_0022EFE0(void) {
    enemyWork.Status |= 0x40;
}

void func_0022F000(void) {
    enemyWork.Status &= ~0x40;
}

void func_0022F020(void) {
    enemyWork.Status |= 0x80;
}

void func_0022F040(void) {
    enemyWork.Status &= ~0x80;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F060);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F070);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F0E0);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F130);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F150);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", func_0022F170);

void func_0022F1D0(void) {
    enemyWork.unk2E08[0x19] = 0;
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

void func_0022FAC0(EnemyData* work) {
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

void func_0022FC20(EnemyData* work) {
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

void func_0022FCF0(EnemyData* work) {
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

void func_0022FE80(EnemyData* work) {
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

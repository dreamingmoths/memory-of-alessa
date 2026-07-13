#include "Enemy/en_red.h"
#include "Font/fj_man.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2dt.h"

// @todo: migrate data

extern /* static */ EnANIME_DATA EnREDAnime[11]; 

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDInitData);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCtrlMain);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCtrlAutomatic);

/* static */ void enREDCtrlSleep(EnLOCAL_DATA* dp /* r16 */) {
    if (enCheckSleepOut(dp)) {
        enSleepOut(dp);
        SET_DP_STATE_LV(dp, 0, 0);
        dp->type = 0;
    }
}

/* static */ void enREDCtrlGoPlayable(EnLOCAL_DATA* dp /* r2 */) {
    dp->mlv = 1;
    SET_DP_STATE_LV(dp, 1, 0);
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCtrlEvent);

/* static */ void enREDCtrlHand(void) {
    return;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCtrlWander);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCtrlChase);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCtrlBerserk);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCtrlStair);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCtrlAttack);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCtrlSeize);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCtrlConfuse);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCtrlBattleEnd);

/* static */ void enREDCtrlOnlyWalk(EnLOCAL_DATA* dp /* r16 */) {
    if (dp->sslv == 0) {
        enREDAnimeSet(dp, true);
        enREDGetWalkSpeed(dp);
    }
}

/* static */ void enREDCheckPlayerWeapon(EnLOCAL_DATA* dp) {
    if (dp->type != 2) {
        switch (enGetPlayerWeapon()) {
            case 0:
            case 1:
            case 5:
            case 4:
                enFlagSetNoDamage(dp);
                break;            
            default:
                enFlagResetNoDamage(dp);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDSetDamage);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCanSeePlayer);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCanSeeCharacter);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDAnimeSet); // https://decomp.me/scratch/EJU91 I guess I need to add enREDAnimeReset too to make it work

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDAnimeReset);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDAnimeExec);

/* static */ float enREDGetSpeed(EnLOCAL_DATA* dp /* r2 */) {
    return 0.25f + (0.75f * (dp->endurance / dp->endurance_max));
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDGetWalkSpeed);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDGetAttackSpeed);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDGetFeelRange);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDGetRotSpeed);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDSetSlowTime); // https://decomp.me/scratch/x7D12 migrate data first?

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDSetMoveCount);

#pragma fast_fptosi on

/* static */ void enREDSoundLife(EnLOCAL_DATA* dp /* r16 */) {
    if (dp->sound_wait < 0x12C) {
        dp->sound_wait++;
        return;
    }
    if ((dp->anim == 2) || (shRandF() < (0.2f * shGetDT()))) {
        enSoundCall((int)(2.0f * shRandF()) + 0x3EF6, 1.0f, &dp->scp->pos.x);
        dp->sound_wait = 0;
    }
}

#pragma fast_fptosi off

INCLUDE_RODATA("asm/nonmatchings/Enemy/en_red", @1620);

INCLUDE_RODATA("asm/nonmatchings/Enemy/en_red", @1621);

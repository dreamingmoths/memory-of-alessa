#include "Enemy/en_red.h"
#include "Font/fj_man.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2dt.h"

// @todo: migrate data

extern /* static */ EnANIME_DATA EnREDAnime[11]; 

extern /* static */ float hp_roof_pos[4];

/* static */ void enREDCtrlSleep(EnLOCAL_DATA* dp /* r16 */);
/* static */ void enREDCtrlGoPlayable(EnLOCAL_DATA* dp /* r2 */);

/* static */ void enREDCtrlHand(void);

/* static */ void enREDCtrlAttack(EnLOCAL_DATA* dp);

/* static */ void enREDCtrlOnlyWalk(EnLOCAL_DATA* dp /* r16 */);
/* static */ void enREDCheckPlayerWeapon(EnLOCAL_DATA* dp);
/* static */ int enREDSetDamage(EnLOCAL_DATA* dp);

/* static */ void enREDAnimeSet(EnLOCAL_DATA* dp /* r17 */, int anim /* r16 */);
/* static */ void enREDAnimeReset(EnLOCAL_DATA* dp, int anim);

/* static */ float enREDGetSpeed(EnLOCAL_DATA* dp /* r2 */);

/* static */ float enREDGetRotSpeed(void);
/* static */ void enREDSetSlowTime(EnLOCAL_DATA * dp /* r16 */);
/* static */ void enREDSetMoveCount(EnLOCAL_DATA* dp);
/* static */ void enREDSoundLife(EnLOCAL_DATA* dp /* r16 */);

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

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCtrlEvent); // https://decomp.me/scratch/FXm6U help needed

/* static */ void enREDCtrlHand(void) {
    return;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCtrlWander);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCtrlChase);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCtrlBerserk);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCtrlStair);

/* static */ void enREDCtrlAttack(EnLOCAL_DATA* dp) { // not line matched
    int t; // r2
    if (enCheckDamage(dp)) {
        enREDSetDamage(dp);
    }
    switch (dp->sslv) {
        case 0:
            t = enREDCanSeePlayer(dp);
            if (t == 3) {
                enREDAnimeReset(dp, 4);
            } else if (t == 4) {
                enREDAnimeReset(dp, 5);
            } else {
                enREDAnimeReset(dp, 3);
            }
            enFlagSetCritical(dp);
            enAttackStart(dp);
            dp->red.attack_count++;
            dp->sslv++;
            break;
        
        case 1:
            if (dp->anim != 4) {
                enMoveAngleToPlayer(dp, enREDGetRotSpeed());
            }

            enAttackCheck(dp, dp->anim + 0x29);
            if (dp->anim_n == -1) {
                enFlagResetCritical(dp);
                if ((dp->type == 2) && enCheckDeath(dp)) {
                    SET_DP_STATE_LV(dp, 7, 0);
                } else if (enREDCanSeePlayer(dp) >= 2) {
                    dp->sslv = 0;
                } else {
                    if (dp->type == 2) {
                        SET_DP_STATE_LV(dp, 1, 0);
                    } else if (dp->type == 1) {
                        if ((dp->anim == 4) && (enREDCanSeePlayer(dp) < 2)) {
                            dp->type = 0;
                            SET_DP_STATE_LV(dp, 0, 0);
                        } else {
                            SET_DP_STATE_LV(dp, 2, 0);
                        }
                    } else {
                        SET_DP_STATE_LV(dp, 0, 0);
                    }
                }
            }
            break;
    }
    enREDGetAttackSpeed(dp);
}

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

/* static */ int enREDSetDamage(EnLOCAL_DATA* dp) {
    enREDSetSlowTime(dp);
    if (dp->type != 2) {
        if ((dp->endurance -= dp->scp->battle.damage, dp->endurance < 0.0f)) dp->endurance = 0.0f;
        dp->scp->battle.damage = 0.0f;        
    } else {
        enReduceHP(dp);
        if (enCheckDeath(dp))
            return 1;
        
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCanSeePlayer);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCanSeeCharacter);

/* static */ void enREDAnimeSet(EnLOCAL_DATA* dp /* r17 */, int anim /* r16 */) {
    if (anim == dp->anim) {
        enAnimeRestart(dp);
        if (anim == 2) {
            enREDSetMoveCount(dp);
        }
        return;
    } 
    
    (anim >= 0 && anim < 11U) ? 0 : fjAssert_("en_red.c", 0x3EB, "anim >= 0 && anim < sizeof(EnREDAnime) / sizeof(EnANIME_DATA)");              
    enAnimeSet(dp, anim, EnREDAnime[anim].Anime);
    if (anim == 2) {
        enREDSetMoveCount(dp);
    }
}

/* static */ void enREDAnimeReset(EnLOCAL_DATA* dp, int anim) {

    (anim >= 0 && anim < 11U) ? 0 : fjAssert_("en_red.c", 0x3F6, "anim >= 0 && anim < sizeof(EnREDAnime) / sizeof(EnANIME_DATA)");
    enAnimeSet(dp, anim, EnREDAnime[anim].Anime);
    if (anim == 2) {
        enREDSetMoveCount(dp);
    }
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDAnimeExec);

/* static */ float enREDGetSpeed(EnLOCAL_DATA* dp /* r2 */) {
    return 0.25f + (0.75f * (dp->endurance / dp->endurance_max));
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDGetWalkSpeed);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDGetAttackSpeed);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDGetFeelRange);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDGetRotSpeed);

#ifdef NON_MATCHING
/* static */ void enREDSetSlowTime(EnLOCAL_DATA* dp /* r16 */) {
    int timer[5] = { 180, 90, 60, 30, 1 }; // r29+0x20





    
    enSetTimer(dp, timer[enGetMode()] * 2);
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDSetSlowTime)  // @note: data migration needed I guess
#endif

#pragma fast_fptosi on

/* static */ void enREDSetMoveCount(EnLOCAL_DATA* dp) {
    int n;
    n = 6.0f - (enGetMode() * 0.2f) + shSway1f(-2.0f, 0.5f);    
    enSetAnimeCount(dp, n << 11);
}

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

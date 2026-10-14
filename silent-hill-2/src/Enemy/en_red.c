#include "Enemy/en_red.h"
#include "Font/fj_man.h"
#include "SH2_common/sh_vu0.h"
#include "sce/libvu0.h"
#include "SH2_common/sh2dt.h"
#include "Event/event.h"

#include "vec.h"

// @todo: migrate data

extern /* static */ EnANIME_DATA EnREDAnime[11]; 

extern /* static */ float hp_roof_pos[4];

/* static */ void enREDCtrlSleep(EnLOCAL_DATA* dp /* r16 */);
/* static */ void enREDCtrlGoPlayable(EnLOCAL_DATA* dp /* r2 */);
/* static */ void enREDCtrlEvent(EnLOCAL_DATA* dp);
/* static */ void enREDCtrlWander(EnLOCAL_DATA* dp);
/* static */ void enREDCtrlChase(EnLOCAL_DATA* dp);
/* static */ void enREDCtrlHand(void);

/* static */ void enREDCtrlAttack(EnLOCAL_DATA* dp);

/* static */ void enREDCtrlOnlyWalk(EnLOCAL_DATA* dp /* r16 */);
/* static */ void enREDCheckPlayerWeapon(EnLOCAL_DATA* dp);
/* static */ int enREDSetDamage(EnLOCAL_DATA* dp);
/* static */ int enREDCanSeePlayer(EnLOCAL_DATA* dp);

/* static */ void enREDAnimeSet(EnLOCAL_DATA* dp /* r17 */, int anim /* r16 */);
/* static */ void enREDAnimeReset(EnLOCAL_DATA* dp, int anim);
/* static */ void enREDAnimeExec(EnLOCAL_DATA* dp);
/* static */ float enREDGetSpeed(EnLOCAL_DATA* dp);
/* static */ float enREDGetWalkSpeed(EnLOCAL_DATA* dp);

/* static */ float enREDGetRotSpeed(void);
/* static */ void enREDSetSlowTime(EnLOCAL_DATA * dp /* r16 */);
/* static */ void enREDSetMoveCount(EnLOCAL_DATA* dp);
/* static */ void enREDSoundLife(EnLOCAL_DATA* dp /* r16 */);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDInitData); // matched https://decomp.me/scratch/N1mXg

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCtrlMain); // matched https://decomp.me/scratch/IGw2E

INCLUDE_ASM("asm/nonmatchings/Enemy/en_red", enREDCtrlAutomatic); // matched https://decomp.me/scratch/jZmHW

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

/* static */ void enREDCtrlEvent(EnLOCAL_DATA* dp) {
        
    
    
    
    
    
    
    switch (dp->type) {
        case 0:
            if (dp->sslv == 0) {
                enREDAnimeSet(dp, 10);
                dp->sslv++;
            }
            break;
        case 1:
            if (dp->sslv == 0) {
                enREDAnimeSet(dp, 1);
                enInitPath(&dp->path, -QUARTER_TURN);
                dp->sslv++;
            }
            dp->path.markangle = enCalcDirection(&hp_roof_pos, &dp->scp->pos);
            enMoveAngle(&dp->path, enREDGetRotSpeed());
            dp->scp->rot.y = dp->path.angle;            
            if (vec3_dist_xz_reverse(&hp_roof_pos, &dp->scp->pos) < 50.0f) {
                SET_GAME_FLAG(202); // @todo: add define
            }
    }
    
    
    enREDAnimeExec(dp);
    
    enMoveExec(dp);
}

/* static */ void enREDCtrlHand(void) {
    return;
}

/* static */ void enREDCtrlWander(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec; // r29+0x20
    int t; // r2
    if (enCheckDamage(dp)) {
        if (enREDSetDamage(dp)) {
            ENEMY_STEP(7);
            return;
        }
        if (enCheckSpray(dp)) {
            ENEMY_STEP(6);
            return;
        }
    }
    if (dp->sslv == 0) {
        enREDAnimeSet(dp, 1);
        enInitPath(&dp->path, dp->scp->rot.y);
        ENEMY_NEXT_SUB_STEP();
    }
    enREDGetWalkSpeed(dp);
    
    shSinCosV_Scale(&vec, dp->scp->rot.y, 1500.0f);
    vu0_add_vector(&vec, &dp->scp->pos, &vec);
    enSetPath(dp, &vec, &dp->scp->pos);
    enMoveAngle(&dp->path, enREDGetRotSpeed());
    dp->scp->rot.y = dp->path.angle;
    
    t = enREDCanSeePlayer(dp);
    if (t >= 2) {
        ENEMY_STEP(4);
    } else if (t == 1) {
        ENEMY_STEP(1);
    }
    enREDSoundLife(dp);
}

/* static */ void enREDCtrlChase(EnLOCAL_DATA* dp) {
    int t;
    if (enCheckDamage(dp)) {
        if (enREDSetDamage(dp)) {
            ENEMY_STEP(7);
            return;
        }
        if (enCheckSpray(dp)) {
            ENEMY_STEP(6);
            return;
        }
    }
    if (dp->sslv == 0) {
        enREDAnimeSet(dp, 1);
        enInitPath(&dp->path, dp->scp->rot.y);
        ENEMY_NEXT_SUB_STEP();
    }
    enSetPath(dp, enGetPlayerPos(dp), &dp->scp->pos);
    enMoveAngle(&dp->path, enREDGetRotSpeed());
    dp->scp->rot.y = dp->path.angle;
    dp->anim_s = ftoi(4096.0f * enREDGetWalkSpeed(dp) * enCalcSpeedRate(dp->scp->rot.y, &dp->scp->pos, enGetPlayerPos(dp)));    

    
    t = enREDCanSeePlayer(dp);
    if (t == 5) {
        ENEMY_STEP(5);
    } else if (t >= 2) {
        ENEMY_STEP(4);
    } else if ((t == 0) && (dp->type != 2)) {
        ENEMY_STEP(0);
    } else if ((dp->type == 2) && (enGetPlayerPos(dp)[2] > -99300.0f)) {
    
        ENEMY_STEP(3);
    } else if ((dp->type == 2) &&
               (dp->scp->pos.z > -99300.0f) &&
               (enGetPlayerPos(dp)[2] < -99300.0f)) {        
        ENEMY_STEP(3);
        if (dp->scp->pos.x > 99200.0f) {
            dp->sslv = 5;
        } else {
            dp->sslv = 6;
        }
    }
    enREDSoundLife(dp);
}

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
    
    FJ_ASSERT_ON_LINE(anim >= 0 && anim < sizeof(EnREDAnime) / sizeof(EnANIME_DATA), 1003);
    enAnimeSet(dp, anim, EnREDAnime[anim].Anime);
    if (anim == 2) {
        enREDSetMoveCount(dp);
    }
}

/* static */ void enREDAnimeReset(EnLOCAL_DATA* dp, int anim) {

    FJ_ASSERT_ON_LINE(anim >= 0 && anim < sizeof(EnREDAnime) / sizeof(EnANIME_DATA), 1014);
    enAnimeSet(dp, anim, EnREDAnime[anim].Anime);
    if (anim == 2) {
        enREDSetMoveCount(dp);
    }
}

/* static */ void enREDAnimeExec(EnLOCAL_DATA* dp) {
    int of = dp->anim_n; // r16    
    enAnimeExec(dp, EnREDAnime, 0x14B5);
    if ((dp->anim_n == -1) || (dp->flag & 1)) return;
    if (dp->anim == 1) {         
            enSetTransWalk(dp);
            
        if (((dp->anim_s > 0) && (of < 0x12C0) && (dp->anim_n >= 0x12C0)) ||
            ((dp->anim_s < 0) && (of >= 0x12C0) && (dp->anim_n < 0x12C0))) {
            
            
            
                        
            if ((dp->type == 2) && (dp->scp->pos.z > -1600.0f)) {
                enSoundCall(0x3E94, 1.0f, &dp->scp->pos);
            } else
            
                if (enCheckWater(dp))
                    enSoundCall(0x4978, 1.0f, &dp->scp->pos);
            
            
            
            if (dp->p_dist > 5000.0f) {
                enSoundCall3D((ftoi(3.0f * shRandF()) * 2) + 0x3EE4, 1.0f, &dp->scp->pos.x);
            
            } else 
                enSoundCall(ftoi(6.0f * shRandF()) + 0x3EE4, 1.0f, &dp->scp->pos.x);
        }
    
    
    
    } else if (dp->anim == 3 || dp->anim == 4) {
            if ((dp->scp->battle.atk_result == 2) && (dp->anim_step == 0)){
                dp->anim_step++;
                
                enSoundCall(0x3EEB, 1.0f, &dp->scp->pos);                
            }
    }

}

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

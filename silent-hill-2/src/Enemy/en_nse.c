#include "Enemy/en_nse.h"
#include "Chacter/chara_list.h"
#include "Chacter/m3_nse.h"
#include "Chacter/sh2_battle_list.h"
#include "Font/fj_man.h"
#include "SH2_common/sh_vu0.h"
#include "vec.h"

static void enNSECtrlAutomatic(EnLOCAL_DATA* dp);
static void enNSECtrlSleep(EnLOCAL_DATA* dp);
static void enNSECtrlGoPlayable(EnLOCAL_DATA* dp);
static void enNSECtrlEvent(EnLOCAL_DATA* dp);
static void enNSECtrlHand(EnLOCAL_DATA* dp);
static void enNSECtrlWander(EnLOCAL_DATA* dp);
static void enNSECtrlPrecaution(EnLOCAL_DATA* dp);
static void enNSECtrlChase(EnLOCAL_DATA* dp);
static void enNSECtrlAttack(EnLOCAL_DATA* dp);
static void enNSECtrlDamage(EnLOCAL_DATA* dp);
static void enNSECtrlConfuse(EnLOCAL_DATA* dp);
static void enNSECtrlDown(EnLOCAL_DATA* dp);
static int enNSECanSeePlayer(EnLOCAL_DATA* dp);
static void enNSEAnimeSet(EnLOCAL_DATA* dp, int anim);
static void enNSEAnimeReset(EnLOCAL_DATA* dp, int anim);
static void enNSEAnimeExec(EnLOCAL_DATA* dp);
static void enNSEAutoRecovery(EnLOCAL_DATA* dp);
static float enNSEGetWalkSpeed(EnLOCAL_DATA* dp);
static float enNSEGetFeelRange(void);
static float enNSEGetAttackProbability(void);
static float enNSEGetAttackSpeed(EnLOCAL_DATA* dp);
static float enNSEGetRotSpeed(void);
static void enNSESetDownTime(EnLOCAL_DATA* dp);
static void enNSESetMoveCount(EnLOCAL_DATA* dp);
static void enNSESetDc(EnLOCAL_DATA* dp);
static void enNSESoundSigns(EnLOCAL_DATA* dp);
static void enNSESoundVoice(EnLOCAL_DATA* dp);
static void enNSESoundAttackVoice(EnLOCAL_DATA* dp);

static EnANIME_DATA EnNSEAnime[28] = {
    {
        /* .anime = */ NSE_PLAY_ANIM(1),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(2),
        /* .loop = */ true,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(1),
        /* .loop = */ true,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(3),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(4),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(5),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(6),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(7),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(8),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(9),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(10),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(11),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(12),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(5),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(13),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(14),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(15),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(16),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(17),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(18),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(19),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(20),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(22),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(21),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(24),
        /* .loop = */ true,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(23),
        /* .loop = */ true,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(26),
        /* .loop = */ false,
    },
    {
        /* .anime = */ NSE_PLAY_ANIM(25),
        /* .loop = */ false,
    }
};

#ifdef NON_MATCHING
void enNSEInitData(EnLOCAL_DATA* dp) {
    short vitarity[5] = { 400, 500, 800, 1500, 9999 };
    
    
    
    
    
    
    float endurance[5] = { 10.0f, 190.0f, 285.0f, 380.0f, 450.0f };  
    float rate;
    int mode;


    
    
    mode = enGetMode();
    
    
    ENEMY_MLV(ENEMY_NSE_MODE_AUTOMATIC);
    ENEMY_STEP(0);
    enSetBattleTarget(dp, 0);
    
    enSetSize(dp, 150.0f, 800.0f, 750.0f, 750.0f);
    dp->weight = 2;
    switch (dp->scp->en_first_status) {
        case 1:
            rate = 1.2f;
            break;
        case 2:
            rate = 0.5f;
            break;
        case 4:
            dp->type = 1;
        case 3:
            rate = 0.3f;
            ENEMY_STEP(ENEMY_NSE_STATE_DOWN);
            enNSEAnimeSet(dp, 26);
            enSetSize(dp, 200.0f, 200.0f, 100.0f, 200.0f);
            break;
        case 5:
            ENEMY_STEP(ENEMY_NSE_STATE_DYING);
            enNSEAnimeSet(dp, dp->lie + 26);
            return;
        default:
            rate = 1.0f;
    }
    if (dp->scp->kind == EN_XOO_CHARA_KIND) {
        rate *= 1.2f;
    }
    enSetHP(dp, rate * vitarity[mode], rate * endurance[mode]);
    enSetSeeLightStatus(dp, 1000.0f, 1500.0f);
    enNSEAnimeSet(dp, 1);
    enFlagSetMoved(dp);
    if (enCheckSleepIn(dp)) {
        enSleepIn(dp);
    }
}
#else
short vitarity_0x002AA680[5] = { 400, 500, 800, 1500, 9999 };
float endurance_0x002AA690[5] = { 10.0f, 190.0f, 285.0f, 380.0f, 450.0f };
INCLUDE_ASM("asm/nonmatchings/Enemy/en_nse", enNSEInitData);
#endif

void enNSECtrlMain(EnLOCAL_DATA* dp) {
    void (*enCtrlNSEFunc[7])(EnLOCAL_DATA*) = {
        enDummyCtrl,
        enNSECtrlAutomatic,
        enNSECtrlSleep,
        enNSECtrlGoPlayable,
        enNSECtrlEvent,
        enNSECtrlHand,
        enWaitRegenerate,
    };

    enCtrlNSEFunc[dp->mlv](dp);
}

static void enNSECtrlAutomatic(EnLOCAL_DATA* dp) {
    void (*enCtrlNSESubFunc[8])(EnLOCAL_DATA*) = {
        enNSECtrlWander,
        enNSECtrlPrecaution,
        enNSECtrlChase,
        enNSECtrlAttack,
        enNSECtrlDamage,
        enNSECtrlConfuse,
        enNSECtrlDown,
        enDyingExec,
    };

    enSetBattleTarget(dp, 0);
    
    enCtrlNSESubFunc[dp->slv](dp);
    
    
    enNSEAnimeExec(dp);
    
    enMoveExec(dp);
    
    if (dp->slv < ENEMY_NSE_STATE_DYING) {
        if (enCheckSleepIn(dp)) {
            enSleepIn(dp); 
        } else         
            enNSESoundSigns(dp);
    }

}

static void enNSECtrlSleep(EnLOCAL_DATA* dp) {
    if (enCheckSleepOut(dp)) {
        enSleepOut(dp);
    }
}

static void enNSECtrlGoPlayable(EnLOCAL_DATA* dp) {
    ENEMY_MLV(ENEMY_NSE_MODE_AUTOMATIC);
    ENEMY_STEP(ENEMY_NSE_STATE_WANDER);
}

static void enNSECtrlEvent(EnLOCAL_DATA* dp) {
    void* tmp; // unused
}

static void enNSECtrlHand(EnLOCAL_DATA* dp) {

}

static void enNSECtrlWander(EnLOCAL_DATA* dp) {
    float d; float a;
    int t; 
    sceVu0FVECTOR vec;
    if (enCheckDamage(dp)) {
        ENEMY_STEP(ENEMY_NSE_STATE_DAMAGE);
        return;
    }
    
    t = enNSECanSeePlayer(dp);
    if (t >= 2) {
        ENEMY_STEP(ENEMY_NSE_STATE_ATTACK);
        return;
    } else if (t == 1) {
        ENEMY_STEP(ENEMY_NSE_STATE_CHASE);
        return;
    }
   
    if ((dp->p_dist < enNSEGetFeelRange()) || (enCheckPlayerSound(dp))) {
        ENEMY_STEP(ENEMY_NSE_STATE_PRECAUTION);
        return;
    }
    a = dp->scp->rot.y;
    switch (dp->sslv) {
        case 0:
            enNSEAnimeSet(dp, 1);
            enInitPath(&dp->path, a);
            dp->bos.target[0] = dp->bos.target[1] = 1.0f + (0.5f * shRandF());
            ENEMY_NEXT_SUB_STEP();
            break;
        case 1:
            d = shRandF();
            if (d < 0.002f) {
                enNSEAnimeSet(dp, 2);
                enNSESoundVoice(dp);
                ENEMY_SUB_STEP(2);
            } else if ((dp->path.step == 0) && (d < 0.02f)) {
                dp->bos.target[1] = 1.0f + (0.5f * shRandF());
                a += TO_RAD(3) * (4.0f * (shRandF() - 0.5f));
            }
            break;
        case 2:
            if (dp->anim_n == -1) {
                enNSEAnimeSet(dp, 1);
                dp->bos.target[1] = 1.0f + (0.5f * shRandF());
                ENEMY_SUB_STEP(1);
            }
            break;
    }
    
    if (dp->anim == 1) {
        d = dp->bos.target[1] - dp->bos.target[0];
        if (d < -0.01f) d = -0.01f;        
        if (d > 0.01f) d = 0.01f;
        dp->bos.target[0] += d;
        dp->anim_s = ftoi(4096.0f * dp->bos.target[0] * enNSEGetWalkSpeed(dp));
    }
    
    shSinCosV_Scale(vec, a, 1000.0f);
    shAddVector(vec, &dp->scp->pos, vec);
    if (enSetPath(dp, vec, &dp->scp->pos)) {
        dp->path.timer = 0;
    }
    enMoveAngle(&dp->path, enNSEGetRotSpeed());
    dp->scp->rot.y = dp->path.angle;
    enNSEAutoRecovery(dp);
}

static void enNSECtrlPrecaution(EnLOCAL_DATA* dp) {
    int t;
    if (enCheckDamage(dp)) {
        enSetSize(dp, 150.0f, 800.0f, 750.0f, 750.0f);
        ENEMY_STEP(ENEMY_NSE_STATE_DAMAGE);
        return;
    }
    
    t = enNSECanSeePlayer(dp);
    if (t >= 2) {
        ENEMY_STEP(ENEMY_NSE_STATE_ATTACK);
        return;
    } else if (t == 1) {
        ENEMY_STEP(ENEMY_NSE_STATE_CHASE);
        return;
    }
    
    if (dp->p_dist > enNSEGetFeelRange()) {
    
        ENEMY_STEP(ENEMY_NSE_STATE_WANDER);
        return;
    }

    switch (dp->sslv) {
        case 0:
            enNSEAnimeSet(dp, 2);
            ENEMY_NEXT_SUB_STEP();
        case 1:
            if (dp->anim_n == -1) {
                enNSEAnimeReset(dp, 2);
            }
            break;
    }
    
    enMoveAngleToPlayer(dp, enNSEGetRotSpeed());
    enNSEAutoRecovery(dp);
}

static void enNSECtrlChase(EnLOCAL_DATA* dp) {
    float d;
    int t;
    if (enCheckDamage(dp)) {
        enSetSize(dp, 150.0f, 800.0f, 750.0f, 750.0f);
        ENEMY_STEP(ENEMY_NSE_STATE_DAMAGE);
        return;
    }
    t = enNSECanSeePlayer(dp);
    if (t >= 2) {
        ENEMY_STEP(ENEMY_NSE_STATE_ATTACK);
        return;
    } else if ((t == 0) &&
                (dp->p_dist > enNSEGetFeelRange() ||
                (enLocalWork.Status & 1))) {
        
        ENEMY_STEP(ENEMY_NSE_STATE_WANDER);
        return;
    }
    switch (dp->sslv) {
        case 0:
            enNSEAnimeSet(dp, 1);
            enSetTimer(dp, 300);            
            dp->bos.target[0] = dp->bos.target[1] = 1.0f;
            ENEMY_NEXT_SUB_STEP();

        case 1:
            enSetPath(dp, enGetPlayerPos(dp), &dp->scp->pos);
            
            dp->bos.target[1] = enCalcSpeedRate(dp->path.angle, &dp->scp->pos, enGetPlayerPos(dp));
            break;
    }
    
    
    if (dp->anim == 1) {
        d = dp->bos.target[1] - dp->bos.target[0];
        if (d < -0.01f) d = -0.01f;        
        if (d > 0.01f) d = 0.01f;    
        dp->bos.target[0] += d;
        dp->anim_s = ftoi(4096.0f * dp->bos.target[0] * enNSEGetWalkSpeed(dp));
    }
    
    enMoveAngle(&dp->path, enNSEGetRotSpeed());
    dp->scp->rot.y = dp->path.angle;
    enNSEAutoRecovery(dp);
}

#ifdef NON_MATCHING
static void enNSECtrlAttack(EnLOCAL_DATA* dp) {
    if (enCheckDamage(dp)) {
        ENEMY_STEP(ENEMY_NSE_STATE_DAMAGE);
        enSetNewSize(dp, 150.0f, 800.0f, 750.0f, 750.0f);
        dp->flag &= ~(1 << 10);
        return;
    }
    switch (dp->sslv) {
        case 0:    
            if (shRandF() < enNSEGetAttackProbability()) {
                if ((enNSECanSeePlayer(dp) == 3) && (dp->p_dist > 900.0f || shRandF() < 0.5f)) {
                    
                    enNSEAnimeReset(dp, 4);
                } else {
                    enNSEAnimeReset(dp, 3);
                }
            } else {
                enNSEAnimeSet(dp, 2);
                ENEMY_SUB_STEP(2);
                break;
            }
            enNSEGetAttackSpeed(dp);
            enSetNewSize(dp, 300.0f, 800.0f, 750.0f, 750.0f);
            dp->flag |= (1 << 10);
            enAttackStart(dp);
            enInitPath(&dp->path, dp->scp->rot.y);
            enNSESoundAttackVoice(dp);
            ENEMY_NEXT_SUB_STEP();
            break;
       
        case 1:
            if (dp->scp->kind == EN_NSE_CHARA_KIND) {
                enAttackCheck(dp, (u_char)(dp->anim == 3 ? 40 : 41));
            
            } else {
                enAttackCheck(dp, (u_char)(dp->anim == 3 ? 42 : 43));
            }
            
            if ((enGetMode() >= SH2_BATTLE_LEVEL_HARD) ||
                (dp->anim == 3)) {
                enMoveAngleToPlayer(dp, enNSEGetRotSpeed());
            }
            if (dp->anim_n == -1) 
                if (enNSECanSeePlayer(dp) >= 2) {
                    ENEMY_SUB_STEP(0);
                
                } else {
                    ENEMY_STEP(ENEMY_NSE_STATE_CHASE);
                    enSetNewSize(dp, 150.0f, 800.0f, 750.0f, 750.0f);
                    dp->flag &= ~(1 << 10);
                }            
            break;
        case 2:
            if (dp->anim_n == -1) {
                if (enNSECanSeePlayer(dp) >= 2) {
                    ENEMY_SUB_STEP(0);
                } else {
                    ENEMY_STEP(ENEMY_NSE_STATE_CHASE);
                }
            }
            break;
    }
    enNSEAutoRecovery(dp);
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_nse", enNSECtrlAttack);
#endif

#ifdef NON_MATCHING
static void enNSECtrlDamage(EnLOCAL_DATA* dp) {
    float d;
    switch (dp->sslv) {
        case 0:
            d = enReduceHP(dp);
            if (enCheckSpray(dp)) {
                ENEMY_STEP(ENEMY_NSE_STATE_CONFUSE);
                break;
            }
            if ((d <= 0.0f) ||
                ((d < 100.0f) && (shRandF() > (0.8f + (0.002f * d))))) {
                enNSEAnimeSet(dp, enGetDownMotion(dp));
            } else {
                enNSEAnimeReset(dp, enGetDamageMotion(dp));
            }
            if ((dp->anim >= 14) && (dp->anim < 22)) {
                dp->lie = enGetLieDirection(dp->anim);
                enFlagSetNoDamage(dp);
                enSetNewSize(dp, 400.0f, 200.0f, 100.0f, 200.0f);
                
                ENEMY_SUB_STEP(2);
            } else {
                dp->sslv = 1; // ENEMY_SUB_STEP(1); // @note: I am leaving it like this because ENEMY_SUB_STEP generates an extra nop here
            }
            enSetHitBack(dp);
            break;
        case 1:
            if ((dp->anim_n == -1) && (dp->hb_s == 0.0f)) {
                ENEMY_STEP(ENEMY_NSE_STATE_PRECAUTION);
            } else if (enCheckDamage(dp)) {
                ENEMY_SUB_STEP(0);
            }
            break;
        case 2:
            if (dp->anim_n == -1) {
                ENEMY_STEP(ENEMY_NSE_STATE_DOWN);
                enFlagResetNoDamage(dp);
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_nse", enNSECtrlDamage);
#endif

static void enNSECtrlConfuse(EnLOCAL_DATA* dp) {
    if (enCheckDamage(dp)) {
        if (enCheckSpray(dp)) {
            ENEMY_SUB_STEP(0);
        } else {
            ENEMY_STEP(ENEMY_NSE_STATE_DAMAGE);
            return;
        }
    }
    if (dp->sslv == 0) {
        enReduceHP(dp);
        enNSEAnimeSet(dp, 2);
        ENEMY_NEXT_SUB_STEP();
    }
    if ((dp->sslv == 1) && (dp->anim_n == -1)) {
        ENEMY_NEXT_SUB_STEP();
        enSetTimer(dp, 600 - (enGetMode() * 90));
    } else if ((dp->sslv == 2) && (enReduceTimer(dp) <= 0)) {
        ENEMY_STEP(ENEMY_NSE_STATE_PRECAUTION);
    }
}

#ifdef NON_MATCHING
static void enNSECtrlDown(EnLOCAL_DATA* dp) {
    switch (dp->sslv) {
        case 0:
            enFlagSetRotFloor(dp);
            enResetDamage(dp);
            enFlagSetLieDown(dp);
            enSetNewSize(dp, 200.0f, 200.0f, 100.0f, 200.0f);
            if (enCheckDeath(dp)) {
                enFlagResetMoved(dp);
                if (!enCheckAimedByHuman(dp) || enCheckInstantDeath(dp)) {
                    enKillCountUp(dp);
                    ENEMY_STEP(ENEMY_NSE_STATE_DYING);
                } else {
                    enNSESetDc(dp);
                    ENEMY_SUB_STEP(4);
                }
                break;
            }
            enNSESetDownTime(dp);
            if ((dp->scp->en_first_status == 3) ||
                (dp->scp->en_first_status == 4)) {
                
                dp->timer += enCalcTimer(600);
            }
            ENEMY_NEXT_SUB_STEP();
            break;
        case 1:
            if (enCheckDamage(dp)) {
                enAnimePause(dp);
                enReduceHP(dp);
                enSetHitBack(dp);
                if (enCheckDeath(dp)) {
                    enFlagResetMoved(dp);
                    if (!enCheckAimedByHuman(dp) || enCheckInstantDeath(dp)) {
                        enKillCountUp(dp);
                        ENEMY_STEP(ENEMY_NSE_STATE_DYING);                        
                    } else {
                        enNSESetDc(dp);
                        ENEMY_SUB_STEP(4);                        
                    }
                    break;
                }
                ENEMY_SUB_STEP(3);
                enSetTimer(dp, 90);
            } else if ((enReduceTimer(dp) <= 0) && !enCheckFinishedByHuman(dp)) {
                if (enGetMode() == SH2_BATTLE_LEVEL_BEGINNER) {                   
                    
                    dp->scp->battle.hp = dp->scp->battle.hp_rate = 0.0f;
                    enKillCountUp(dp);
                    ENEMY_STEP(ENEMY_NSE_STATE_DYING);
                    break;
                }
                if (dp->type == 1) {
                    dp->timer += enCalcTimer(600);
                    break;
                }
                
                enNSEAnimeSet(dp, dp->lie + 22);
                enAddHP(dp, 50.0f);
                enFlagResetRotFloor(dp);
                enFlagResetLieDown(dp);
                enFlagSetNoDamage(dp);
                enSetNewSize(dp, 150.0f, 800.0f, 750.0f, 750.0f);
                ENEMY_SUB_STEP(2);
            } else if (dp->flag & 0x2000) {
                if ((dp->anim >= 24) && (dp->anim < 26)) {
                    if ((200.0f * shRandF()) < (100.0f - dp->scp->battle.hp_rate)) {
                        
                        enAnimePause(dp);
                        enAddHP(dp, 10.0f);
                    }
                } else {
                    if ((300.0f * shRandF()) < (200.0f + dp->scp->battle.hp_rate)) {
                       
                        enNSEAnimeSet(dp, dp->lie + 24);                        
                    } else {
                        enAddHP(dp, 10.0f);
                    }                    
                }
            } 
            break;
        case 2:
            if (dp->anim_n == -1) {
                enResetDamage(dp);
                enFlagResetNoDamage(dp);
                ENEMY_STEP(ENEMY_NSE_STATE_PRECAUTION);
            }
            break;
        case 3:
            if (enCheckDamage(dp)) {
                enReduceHP(dp);
                enSetHitBack(dp);
                if (enCheckDeath(dp)) {
                    enFlagResetMoved(dp);
                    if (!enCheckAimedByHuman(dp) || enCheckInstantDeath(dp)) {
                        enKillCountUp(dp);
                        ENEMY_STEP(ENEMY_NSE_STATE_DYING);
                    } else {
                        enNSESetDc(dp);
                        ENEMY_SUB_STEP(4);
                    }
                    break;
                }
                enSetTimer(dp, 90);
            } else if ((dp->hb_s == 0.0f) && (enReduceTimer(dp) <= 0)) {
                if (enGetMode() == SH2_BATTLE_LEVEL_BEGINNER) {                    
                   
                    dp->scp->battle.hp = dp->scp->battle.hp_rate = 0.0f;
                    enKillCountUp(dp);
                    ENEMY_STEP(ENEMY_NSE_STATE_DYING);
                    break;
                }
                if (dp->type == 1) {
                    enSetTimer(dp, 600);
                    ENEMY_SUB_STEP(1);
                    break;
                }
                
                if (enCheckFinishedByHuman(dp)) {
                    ENEMY_SUB_STEP(5);
                    break;
                }
                enNSEAnimeSet(dp, dp->lie + 22);
                enAddHP(dp, 50.0f);
                enFlagResetRotFloor(dp);
                enFlagResetLieDown(dp);
                enFlagSetNoDamage(dp);
                enSetNewSize(dp, 150.0f, 800.0f, 750.0f, 750.0f);
                ENEMY_SUB_STEP(2);
            }
            break;
        case 4:
            if (enCheckDamage(dp)) {
                enReduceHP(dp);
                enSetHitBack(dp);
                dp->hb_s *= (itof(dp->nse.dcm - dp->nse.dc) / (dp->nse.dcm + 1));
                if ((++dp->nse.dc >= dp->nse.dcm) || enCheckInstantDeath(dp)) {
                    enKillCountUp(dp);
                    ENEMY_STEP(ENEMY_NSE_STATE_DYING);
                    break;
                }
                enSetTimer(dp, 200);
            } else if (enReduceTimer(dp) <= 0) {
                enKillCountUp(dp);
                ENEMY_STEP(ENEMY_NSE_STATE_DYING);
            }
            break;
        case 5:
            if (enCheckDamage(dp)) {
                enReduceHP(dp);
                enSetHitBack(dp);
                if (enCheckDeath(dp)) {
                    enFlagResetMoved(dp);
                    if (!enCheckAimedByHuman(dp) || enCheckInstantDeath(dp)) {
                        enKillCountUp(dp);
                        ENEMY_STEP(ENEMY_NSE_STATE_DYING);
                    } else {
                        enNSESetDc(dp);
                        ENEMY_SUB_STEP(4);
                    }
                } else {
                    
                    enSetTimer(dp, 90);
                    ENEMY_SUB_STEP(3);                    
                }                
            } else if (!enCheckFinishedByHuman(dp)) {
                enNSEAnimeSet(dp, dp->lie + 22);
                enAddHP(dp, 50.0f);
                enFlagResetRotFloor(dp);
                enFlagResetLieDown(dp);
                enFlagSetNoDamage(dp);
                enSetNewSize(dp, 150.0f, 800.0f, 750.0f, 750.0f);
                ENEMY_SUB_STEP(2);
            }
            break;       
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_nse", enNSECtrlDown);
#endif

static int enNSECanSeePlayer(EnLOCAL_DATA* dp) {
    float* ppos = enGetPlayerPos(dp);
    float dist; float a;
    int wcd = enGetWorldCondition();    
    dist = enCheckPath2(dp, ppos, &dp->scp->pos);
    if (dist >= 0.0f) {
        if ((wcd >= 2) && (enCheckSeeLight(dp)) && !(enLocalWork.Status & 1)) {
            
            return 1;
        }
        return 0;
    }
    dist = dp->p_dist;
    switch (wcd) {
        case 4:
            if (dist > 1000.0f) return 0;            
            break;
        default:
            if (dist > 4000.0f) return 0;            
            break;
    }
    a = enCalcDirection(ppos, &dp->scp->pos);
    a = enCalcAngleDifference(a, dp->scp->rot.y);
    if ((dist < 1500.0f) && (a < TO_RAD(5)) &&
        (wcd != 4) && !enCheckNoDamageHuman(dp)) {
        return 3;
    }
    if ((dist < 900.0f) && (a < TO_RAD(30)) &&
        !enCheckNoDamageHuman(dp)) {
        return 2;
    }
    if (enLocalWork.Status & 1) return 0;    
    if ((wcd >= 2) && enCheckSeeLight(dp)) return 1;
    
    if (a > TO_RAD(80)) return 0;    
    return 1;
}

static void enNSEAnimeSet(EnLOCAL_DATA* dp, int anim) {
    if (anim == dp->anim) {
        enAnimeRestart(dp);
        if (anim == 2) {
            enNSESetMoveCount(dp);
        }
        return;
    }
  
    FJ_ASSERT_ON_LINE(anim >= 0 && anim < sizeof(EnNSEAnime) / sizeof(EnANIME_DATA), 914);
    enAnimeSet(dp, anim, EnNSEAnime[anim].Anime);
    if (anim == 2) {
        enNSESetMoveCount(dp);
    }
}

static void enNSEAnimeReset(EnLOCAL_DATA* dp, int anim) {
    
    FJ_ASSERT_ON_LINE(anim >= 0 && anim < sizeof(EnNSEAnime) / sizeof(EnANIME_DATA), 925);
    enAnimeSet(dp, anim, EnNSEAnime[anim].Anime);
    if (anim == 2) {
        enNSESetMoveCount(dp);
    }
}

static void enNSEAnimeExec(EnLOCAL_DATA* dp) {
    int of = dp->anim_n;   
    enAnimeExec(dp, EnNSEAnime, NSE_PLAY_ANIM(1));
    if ((dp->anim_n == -1) || (dp->flag & 1)) return;    
    if ((dp->anim >= 14) &&
        (dp->anim <= 21)) {
        enSetTrans(dp);
    } else if ((dp->anim >= 11) &&
               (dp->anim <= 12)) {
        enSetTransWalk(dp);
    } else if ((dp->anim >= 3) &&
               (dp->anim <= 4)) {
        enSetTransWalk(dp);
    } else if (dp->anim == 1) {
        
        enSetTransWalk(dp);
        
    if ((dp->anim_s > 0 &&
        ((of < 2400 && dp->anim_n >= 2400) || (of < 43200 && dp->anim_n >= 43200))) ||            
        (dp->anim_s < 0 && ((of > 36000 && dp->anim_n <= 36000) || (of > 76800 && dp->anim_n <= 76800)))) {
            
            
            
            
            
            
            
            
            if (enCheckWater(dp)) {
                enSoundCall(18808, 1.0f, &dp->scp->pos);
                return;
            }            
            if (dp->flag & (1 << 12)) {
                enSoundCall3D(12100, 1.0f, &dp->scp->pos);
            } else {
                enSoundCall(12100, 1.0f, &dp->scp->pos);
            }            
        }
    }
}

static void enNSEAutoRecovery(EnLOCAL_DATA* dp) {
    short recover_rate[5] = { 0, 10, 30, 60, 100 };

    
    
    
    
    
    enAddEnduranceDT(dp, itof(recover_rate[enGetMode()]));
}

static float enNSEGetWalkSpeed(EnLOCAL_DATA* dp) {
    float speed_rate[5] = { 0.7f, 0.8f, 1.0f, 1.2f, 1.5f };
    float r;

    
    
    
    
    r = speed_rate[enGetMode()];
    r *= (0.5f + (dp->scp->battle.hp_rate / 200.0f));
    dp->anim_s = ftoi(4096.0f * r);
    return r;
}

static float enNSEGetFeelRange(void) {
    float feel_range[5] = { 1000.0f, 1250.0f, 1500.0f, 1500.0f, 1500.0f };

    
    
    
    
    
    if (enGetWorldCondition() == 4) {
        return 750.0f;
    }
    return feel_range[enGetMode()];
}

static float enNSEGetAttackProbability(void) {
    float attack_rate[5] = { 0.1f, 0.5f, 0.7f, 0.9f, 1.0f };


    
    
    
    
    return attack_rate[enGetMode()];
}

static float enNSEGetAttackSpeed(EnLOCAL_DATA* dp) {
    float speed_rate[5] = { 0.5f, 0.8f, 1.0f, 1.1f, 1.2f };
    float r;

    
    
    
    
    r = speed_rate[enGetMode()];
    r *= (0.5f + (dp->scp->battle.hp_rate / 200.0f));
    dp->anim_s = ftoi(4096.0f * r);
    return r;
}

static float enNSEGetRotSpeed(void) {
    float rot_rate[5] = { 0.5f, 0.8f, 1.0f, 1.2f, 1.5f };


    
    
    
    
    return TO_RAD(3) * rot_rate[enGetMode()];
}

static void enNSESetDownTime(EnLOCAL_DATA* dp) {
    short down_time[5] = { 600, 480, 360, 300, 240 };

    
    
    
    
        
    enSetTimer(dp, down_time[enGetMode()]);
}

static void enNSESetMoveCount(EnLOCAL_DATA* dp) {
    int n;
    n = ftoi(8.0f - 0.4f * enGetMode() + shSway1f(-2.0f, 0.5f));
    enSetAnimeCount(dp, n * 2048);
}

#pragma divbyzerocheck off

static void enNSESetDc(EnLOCAL_DATA* dp) {
    enSetTimer(dp, 200);
    dp->nse.dc = 0;
    dp->nse.dcm = ((shRandI() >> 10) % (enGetMode() + 3)) + 4;
}

static void enNSESoundSigns(EnLOCAL_DATA* dp) {
    int signs;
    if ((dp->nse.count -= shGetDF()) <= 0) {
        dp->nse.count = enCalcTimer(60);
        do {
            signs = (shRandI() >> 20) & 3;
        } while (signs == dp->nse.signs);
        dp->nse.signs = signs;
        enSoundCall(signs + 12103, 0.6f, &dp->scp->pos);
    }
}

#pragma divbyzerocheck on

#ifdef NON_MATCHING
static void enNSESoundVoice(EnLOCAL_DATA* dp) {
    enSoundCall(ftoi(4.0f * shRandF()) + 12109, 0.7f, &dp->scp->pos);
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_nse", enNSESoundVoice);
#endif

#ifdef NON_MATCHING
static void enNSESoundAttackVoice(EnLOCAL_DATA* dp) {
    enSoundCall(ftoi(6.0f * shRandF()) + 12107, 1.0f, &dp->scp->pos);
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_nse", enNSESoundAttackVoice);
#endif

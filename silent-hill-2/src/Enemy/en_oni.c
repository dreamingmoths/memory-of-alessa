#include "Enemy/en_oni.h"
#include "Chacter/chara_list.h"
#include "Chacter/m3_oni.h"
#include "Chacter/sh2_battle_list.h"
#include "Event/event.h"
#include "Font/fj_man.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2dt.h"
#include "vec.h"

#include "shared/Fog/fog.h" // @note: float_sign needs to be moved

static void enONICtrlAutomatic(EnLOCAL_DATA* dp);
static void enONICtrlSleep(EnLOCAL_DATA* dp);
static void enONICtrlGoPlayable(EnLOCAL_DATA* dp);
static void enONICtrlEvent(EnLOCAL_DATA* dp);
static void enONICtrlEventChase(EnLOCAL_DATA* dp);
static void enONICtrlHand(void);
static void enONICtrlWander(EnLOCAL_DATA* dp);
static void enONICtrlChase(EnLOCAL_DATA* dp);
static void enONICtrlBothAttack(EnLOCAL_DATA* dp);
static void enONICtrlWait(EnLOCAL_DATA* dp);
static void enONICtrlBerserk(EnLOCAL_DATA* dp);
static void enONICtrlAttack(EnLOCAL_DATA* dp);
static void enONICtrlAttack3(EnLOCAL_DATA* dp);
static void enONICtrlDamage(EnLOCAL_DATA* dp);
static void enONICtrlConfuse(EnLOCAL_DATA* dp);
static void enONICtrlSuicide(EnLOCAL_DATA* dp);
static void enONICtrlDead(EnLOCAL_DATA* dp);
static void enONICheckPlayerWeapon(EnLOCAL_DATA* dp);
static int enONIGetDamageMotion(EnLOCAL_DATA* dp);
static int enONISetDamage(EnLOCAL_DATA* dp);
static int enONICanSeePlayer(EnLOCAL_DATA* dp);
static int enONICanSeeCharacter(EnLOCAL_DATA* dp, SubCharacter* scp);
static void enONIAnimeSet(EnLOCAL_DATA* dp, int anim);
static void enONIAnimeReset(EnLOCAL_DATA* dp, int anim);
static void enONIAnimeExec(EnLOCAL_DATA* dp);
static float enONIGetSpeed(EnLOCAL_DATA* dp);
static float enONIGetWalkSpeed(EnLOCAL_DATA* dp);
static float enONIGetAttackSpeed(EnLOCAL_DATA* dp);
static float enONIGetFeelRange(void);
static float enONIGetRotSpeed(void);
static void enONISetSlowTime(EnLOCAL_DATA* dp);
static void enONISoundLife(EnLOCAL_DATA* dp);

static EnANIME_DATA EnONIAnime[16] = {
    {
        /* .anime = */ ONI_PLAY_ANIM(1),
        /* .loop = */ false,
    },
    {
        /* .anime = */ ONI_PLAY_ANIM(2),
        /* .loop = */ true,
    },
    {
        /* .anime = */ ONI_PLAY_ANIM(1),
        /* .loop = */ true,
    },
    {
        /* .anime = */ ONI_PLAY_ANIM(3),
        /* .loop = */ false,
    },
    {
        /* .anime = */ ONI_PLAY_ANIM(10),
        /* .loop = */ true,
    },
    {
        /* .anime = */ ONI_PLAY_ANIM(9),
        /* .loop = */ false,
    },
    {
        /* .anime = */ ONI_PLAY_ANIM(11),
        /* .loop = */ false,
    },
    {
        /* .anime = */ ONI_PLAY_ANIM(4),
        /* .loop = */ false,
    },
    {
        /* .anime = */ ONI_PLAY_ANIM(5),
        /* .loop = */ false,
    },
    {
        /* .anime = */ ONI_PLAY_ANIM(6),
        /* .loop = */ false,
    },
    {
        /* .anime = */ ONI_PLAY_ANIM(7),
        /* .loop = */ false,
    },
    {
        /* .anime = */ ONI_PLAY_ANIM(8),
        /* .loop = */ false,
    },
    {
        /* .anime = */ ONI_PLAY_ANIM(12),
        /* .loop = */ false,
    },
    {
        /* .anime = */ ONI_PLAY_ANIM(13),
        /* .loop = */ false,
    },
    {
        /* .anime = */ ONI_PLAY_ANIM(14),
        /* .loop = */ false,
    },
    {
        /* .anime = */ ONI_PLAY_ANIM(15),
        /* .loop = */ false,
    }
};

static sceVu0FVECTOR check_point[13] = {
    { 16100.0f, 0.0f, -260300.0f, 0.0f },
    { 16000.0f, 0.0f, -258800.0f, 0.0f },
    { 16100.0f, 0.0f, -258100.0f, 0.0f },
    { 19200.0f, 0.0f, -258000.0f, QUARTER_TURN },
    { 19900.0f, 0.0f, -257900.0f, 0.0f },
    { 19900.0f, 0.0f, -255700.0f, 0.0f },
    { 19200.0f, 0.0f, -255600.0f, -QUARTER_TURN },
    { 16100.0f, 0.0f, -255500.0f, 0.0f },
    { 16100.0f, 0.0f, -254500.0f, 0.0f },
    { 18300.0f, 0.0f, -254300.0f, 0.0f },
    { 18400.0f, 0.0f, -252400.0f, 0.0f },
    { 18500.0f, 0.0f, -251700.0f, 0.0f },
    { 34000.0f, 0.0f, -251600.0f, 0.0f },
};

static char warp_check[4] = { 1, 3, 6, 10 };

static sceVu0FVECTOR suicide_point[2] = {
    { -19344.449f, 0.0f, 21723.15f, -0.52359879f },
    { -19622.8f, 0.0f, 22746.349f, 0.78539818f },
};

#ifdef NON_MATCHING
void enONIInitData(EnLOCAL_DATA* dp) {
    float vitarity[5] = { 3000.0f,
                          7500.0f,
                          10000.0f,
                          20000.0f,
                          40000.0f }; 
    
    
    float endurance[5] = { 500.0f,
                           700.0f,
                           1000.0f,
                           2000.0f,
                           5000.0f };
    
    
    int mode = enGetMode();
    float hp;
    int i; int n; EnLOCAL_DATA* tp;
    dp->oni.other = NULL;
    ENEMY_MLV(ENEMY_ONI_MODE_AUTOMATIC);
    dp->weight = 3;
    enSetSize(dp, 250.0f, 900.0f, 800.0f, 850.0f);

    switch (dp->scp->en_first_status) { 
        case 15:
            enSetSize(dp, 350.0f, 900.0f, 800.0f, 850.0f);
            ENEMY_MLV(ENEMY_ONI_MODE_EVENT);
            dp->slv = ENEMY_ONI_STATE_WANDER;
            dp->weight = 4;
            hp = 1000000.0f;
            enFlagSetMoved(dp);
            
            enSoundCall(16119, 1.0f, &dp->scp->pos);
            
            break;
        case 6:
            ENEMY_STEP(ENEMY_ONI_STATE_CHASE);
            dp->type = 2;
            hp = vitarity[mode];
            
            
            n = 0;
            tp = enLocalWork.Data;
            for (i = 0; i < 32; i++, tp++) {
                if ((tp->kind == EnKIND_ONI) && (tp != dp)) {
                    tp->oni.other = dp;
                    dp->oni.other = tp;
                    n++;
                }
            }
            dp->oni.id = n;
            
            enSetBattleTarget(dp, 1);
            break;
        case 13:
            ENEMY_STEP(ENEMY_ONI_STATE_DEAD);
            hp = 0.0f;
            break;
        default:
            ENEMY_STEP(ENEMY_ONI_STATE_WANDER);
            dp->type = 0;
            hp = 1000000.0f;
            enFlagSetMoved(dp);
            break;
    }
    enSetHP(dp, hp, endurance[mode]);
    if (enCheckSleepIn(dp)) {
        enSleepIn(dp);
    }
}
#else
float vitarity_0x0034C7D0[5] = { 3000.0f,
                                 7500.0f,
                                 10000.0f,
                                 20000.0f,
                                 40000.0f }; 

float endurance_0x0034C7F0[5] = { 500.0f,
                                  700.0f,
                                  1000.0f,
                                  2000.0f,
                                  5000.0f };

INCLUDE_ASM("asm/nonmatchings/Enemy/en_oni", enONIInitData);
#endif

void enONICtrlMain(EnLOCAL_DATA* dp) {
    void (*enCtrlONIFunc[6])(EnLOCAL_DATA*) = {
        enDummyCtrl,
        enONICtrlAutomatic,
        enONICtrlSleep,
        enONICtrlGoPlayable,
        enONICtrlEvent,
        enONICtrlHand,
    };

    enCtrlONIFunc[dp->mlv](dp);
}

static void enONICtrlAutomatic(EnLOCAL_DATA* dp) {
    void (*enCtrlONISubFunc[11])(EnLOCAL_DATA*) = {
        enONICtrlWander,
        enONICtrlChase,
        enONICtrlBothAttack,
        enONICtrlWait,
        enONICtrlBerserk,
        enONICtrlAttack,
        enONICtrlAttack3,
        enONICtrlDamage,
        enONICtrlConfuse,
        enONICtrlSuicide,
        enONICtrlDead,
    };

    enSetBattleTarget(dp, 0);
    
    enONICheckPlayerWeapon(dp);
    
    enCtrlONISubFunc[dp->slv](dp);
    
    if (enReduceTimer(dp) <= 0) {
        dp->endurance += (200.0f * shGetDT()); // @note: not line matched
        if (dp->endurance > dp->endurance_max) {
            dp->endurance = dp->endurance_max;
        }
    }
    enONIAnimeExec(dp);
    
    enMoveExec(dp);
    if ((dp->type != 2) && (enCheckSleepIn(dp))) {
    
        enSleepIn(dp);
    }
}

static void enONICtrlSleep(EnLOCAL_DATA* dp) {
    if (enCheckSleepOut(dp)) {
        enSleepOut(dp);       
        ENEMY_STEP(ENEMY_ONI_STATE_WANDER);
        dp->type = 0;
    }
}

static void enONICtrlGoPlayable(EnLOCAL_DATA* dp) {
    ENEMY_MLV(ENEMY_ONI_MODE_AUTOMATIC);  
    ENEMY_STEP(ENEMY_ONI_STATE_CHASE);
}

static void enONICtrlEvent(EnLOCAL_DATA* dp) {
    int n;
    enSetBattleTarget(dp, 0);
    switch (dp->slv) {
        case ENEMY_ONI_STATE_WANDER:
            enONICtrlEventChase(dp);
            break;
        case ENEMY_ONI_STATE_BERSERK:
            n = dp->sslv;
            if (dp->oni.check <= warp_check[n]) {
                dp->oni.warp = n;
            }
            ENEMY_STEP(ENEMY_ONI_STATE_WANDER); // @note: not line matched (wtf?)
            break;
    }
    
    
    enONIAnimeExec(dp);
    
    enMoveExec(dp);
}

#ifdef NON_MATCHING
static void enONICtrlEventChase(EnLOCAL_DATA* dp) {
    float* tpos;
    float d1; float d2;
    if (enCheckDamage(dp)) {
        switch (dp->last_atk) {
            case 2:
            case 1:
            case 12:
            case 13:
            case 14:
                break;
            default:
                enSetHitBack(dp);
                break;
        }
        enResetDamage(dp);
    }
    switch (dp->sslv) {
        case 0:
            enONIAnimeSet(dp, 1);
            enInitPath(&dp->path, dp->scp->rot.y);
            dp->oni.warp = -1;
            dp->anim_s = 6144;
            ENEMY_NEXT_SUB_STEP();
            break;
        case 1:
            tpos = check_point[dp->oni.check];
            dp->path.markangle = enCalcDirection(tpos, &dp->scp->pos);
            enMoveAngle(&dp->path, enONIGetRotSpeed());
            dp->scp->rot.y = dp->path.angle;            
            d1 = enGetPlayerDistance(dp);
            d2 = shVectorDistXz_reverse(tpos, &dp->scp->pos);
            if (d2 < 150.0f) {
                dp->oni.check++;
                if ((dp->oni.warp != -1) && (dp->oni.check > warp_check[dp->oni.warp])) {
                    dp->oni.warp = -1;
                }
            }
            if ((enCheckIntoScreen(dp) == 0) &&
                ((d1 > 2500.0f) || (dp->oni.warp != -1))) {
                shSinCosV_Scale(dp->vec, dp->scp->rot.y, 1500.0f);
            }
            if ((d1 < 625.0f) && (enCheckPath(dp, enGetPlayerPos(dp), &dp->scp->pos) < 0.0f)) {
                
                
                enONIAnimeSet(dp, 3);
                enONIGetAttackSpeed(dp);
                dp->anim_s /= 2;
                enAttackStart(dp);
                ENEMY_NEXT_SUB_STEP();
            }
            break;
        
        case 2:
            enAttackCheck(dp, 49);
            enMoveAngleToPlayer(dp, enONIGetRotSpeed());
            if (dp->anim_n == -1) {
                dp->sslv = 0;
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_oni", enONICtrlEventChase);
#endif

static void enONICtrlHand(void) {

}

#ifdef NON_MATCHING
static void enONICtrlWander(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec;
    int t;
    if (enCheckDamage(dp)) {
        if (enONISetDamage(dp)) {            
            ENEMY_STEP(ENEMY_ONI_STATE_DAMAGE);
            return;
        }
        if (enCheckSpray(dp)) {
            ENEMY_STEP(ENEMY_ONI_STATE_CONFUSE);
            return;
        }
    }
    if (dp->sslv == 0) {
        enONIAnimeSet(dp, 1);
        enInitPath(&dp->path, dp->scp->rot.y);
        ENEMY_NEXT_SUB_STEP();
    }
    enONIGetWalkSpeed(dp);

    shSinCosV_Scale((float*) vec, dp->scp->rot.y, 1500.0f);
    shAddVector(vec, &dp->scp->pos, vec);
    enSetPath(dp, &vec, &dp->scp->pos);
    enMoveAngle(&dp->path, enONIGetRotSpeed());
    dp->scp->rot.y = dp->path.angle;
    
    t = enONICanSeePlayer(dp);
    if (t >= 2) {
        ENEMY_STEP(ENEMY_ONI_STATE_ATTACK);
    } else if (t == 1) {
        ENEMY_STEP(ENEMY_ONI_STATE_CHASE);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_oni", enONICtrlWander);
#endif

static void enONICtrlChase(EnLOCAL_DATA* dp) {
    int t;
    if (enCheckDamage(dp)) {
        if (enONISetDamage(dp)) {
            ENEMY_STEP(ENEMY_ONI_STATE_DAMAGE);
            return;
        }
        if (enCheckSpray(dp)) {
            ENEMY_STEP(ENEMY_ONI_STATE_CONFUSE);
            return;
        }
    }
    if (dp->sslv == 0) {
        enONIAnimeSet(dp, 1);
        enInitPath(&dp->path, dp->scp->rot.y);
        ENEMY_NEXT_SUB_STEP();
    }
    enSetPath(dp, enGetPlayerPos(dp), &dp->scp->pos);
    enMoveAngle(&dp->path, enONIGetRotSpeed());
    dp->scp->rot.y = dp->path.angle;
    dp->anim_s = ftoi(4096.0f * enONIGetWalkSpeed(dp) * enCalcSpeedRate(dp->scp->rot.y, &dp->scp->pos, enGetPlayerPos(dp)));
    
    if ((dp->type == 2) && (enGetMode() >= SH2_BATTLE_LEVEL_NORMAL) && (enCalcAngleDifference(dp->scp->rot.y, enGetPlayerDirection(dp)) < TO_RAD(5))) {
        
        dp->anim_s = dp->anim_s * 3 / 2;
    }
    
    t = enONICanSeePlayer(dp);
    if (t == 2) {
        ENEMY_STEP(ENEMY_ONI_STATE_ATTACK);
    } else if (t == 4) {
        ENEMY_STEP(ENEMY_ONI_STATE_ATTACK3);
    } else if ((t == 0) && (dp->type != 2)) {
        ENEMY_STEP(ENEMY_ONI_STATE_WANDER);
    } else if ((t != 0) && (dp->oni.other != 0) &&
               (((EnLOCAL_DATA*) dp->oni.other)->slv == ENEMY_ONI_STATE_CHASE) && (dp->p_dist > ((EnLOCAL_DATA *)dp->oni.other)->p_dist)) {
        ENEMY_STEP(ENEMY_ONI_STATE_BOTH_ATTACK);       
    }
}

static void enONICtrlBothAttack(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec;
    float a; float a1; float a2;
    int t;
    if (enCheckDamage(dp)) {
        if (enONISetDamage(dp)) {
            ENEMY_STEP(ENEMY_ONI_STATE_DAMAGE);
            return;
        }
        if (enCheckSpray(dp)) {
            ENEMY_STEP(ENEMY_ONI_STATE_CONFUSE);
            return;
        }
    }
    if (dp->anim == 1) {
        enONIGetWalkSpeed(dp);
        dp->anim_s = dp->anim_s * 6 / 5;
    }
    
    t = enONICanSeePlayer(dp);
    if (t == 2) {
        if (shVectorDistXz_reverse(&dp->scp->pos, &((EnLOCAL_DATA*) dp->oni.other)->scp->pos) > 750.0f) {
            ENEMY_STEP(ENEMY_ONI_STATE_ATTACK3);
        } else {
            ENEMY_STEP(ENEMY_ONI_STATE_ATTACK);
        }
        return;
    } else if (t == 4) {
        ENEMY_STEP(ENEMY_ONI_STATE_ATTACK3);
        return;
    } else if (dp->p_dist > 4000.0f) {
        ENEMY_STEP(ENEMY_ONI_STATE_CHASE);
        return;
    }
    if (dp->p_dist < ((EnLOCAL_DATA*) dp->oni.other)->p_dist) {
        ENEMY_STEP(ENEMY_ONI_STATE_CHASE);
        return;
    }
    a = enGetPlayerDirection(dp);
    a1 = enGetPlayerDirection(dp->oni.other);
    a2 = shAngleRegulate(a - a1);
    switch (dp->sslv) {
        case 0:
            if (dp->p_dist < 500.0f) {
                enONIAnimeSet(dp, 2);
                ENEMY_SUB_STEP(4);
                return;
            }
            enONIAnimeSet(dp, 1);
            enONIGetWalkSpeed(dp);
            ENEMY_NEXT_SUB_STEP();
        case 1:
            shSinCosV_Scale(vec, a1 - (TO_RAD(60) * float_sign(a2)), 2500.0f);
            
            shAddVector(vec, enGetPlayerPos(dp), vec);
            enSetPath(dp, vec, &dp->scp->pos);
            enMoveAngle(&dp->path, enONIGetRotSpeed());
            dp->scp->rot.y = dp->path.angle;
            if ((shFloatAbs(a2) > TO_RAD(100))) {
                ENEMY_SUB_STEP(2);
            }
            break;
        case 2:
            shSinCosV_Scale(vec, a1, 500.0f);
            shAddVector(vec, enGetPlayerPos(dp), vec);
            if (enSetPath(dp, vec, &dp->scp->pos)) {
                
                ENEMY_SUB_STEP(3);
            }
            if (dp->p_dist < 500.0f) {
                
                ENEMY_SUB_STEP(3);
            }
            enMoveAngle(&dp->path, enONIGetRotSpeed());
            dp->scp->rot.y = dp->path.angle;
            break;
        case 3:
            enMoveAngleToPlayer(dp, enONIGetRotSpeed());
            if (dp->p_dist > 2500.0f) {
                ENEMY_SUB_STEP(1);
            } else if (dp->p_dist < 500.0f) {
                
                enONIAnimeSet(dp, 2);
                ENEMY_SUB_STEP(4);
            }
            break;
        case 4:
            enMoveAngleToPlayer(dp, enONIGetRotSpeed());
            if ((dp->p_dist > 500.0f) && (dp->anim_loop > 1)) {
                
                enONIAnimeSet(dp, 1);
                ENEMY_SUB_STEP(1);
            }
            break;
    }
}

static void enONICtrlWait(EnLOCAL_DATA* dp) {
    int t;
    if (enCheckDamage(dp)) {
        if (enONISetDamage(dp)) {
            ENEMY_STEP(ENEMY_ONI_STATE_DAMAGE);
            return;
        }
        if (enCheckSpray(dp)) {
            ENEMY_STEP(ENEMY_ONI_STATE_CONFUSE);
            return;
        }
    }
    enONIGetWalkSpeed(dp);
    
    t = enONICanSeePlayer(dp);
    if (t == 2) {  
        if ((shVectorDistXz_reverse(&dp->scp->pos, &((EnLOCAL_DATA*) dp->oni.other)->scp->pos) > 750.0f)) {
            ENEMY_STEP(ENEMY_ONI_STATE_ATTACK3);
        } else {
            ENEMY_STEP(ENEMY_ONI_STATE_ATTACK);
        }
        return;
    }
    else if (t == 4) {
        ENEMY_STEP(ENEMY_ONI_STATE_ATTACK3);
        return;
    }
    if (dp->p_dist > 2500.0f) {
        ENEMY_STEP(ENEMY_ONI_STATE_CHASE);
        return;
    }
    if (enCalcAngleDifference(enGetPlayerDirection(dp), enGetPlayerDirection(dp->oni.other)) < TO_RAD(100)) {
        ENEMY_STEP(ENEMY_ONI_STATE_BOTH_ATTACK);
        return;
    }
    if (dp->sslv == 0) {
        enONIAnimeSet(dp, 2);
        enInitPath(&dp->path, dp->scp->rot.y);
        ENEMY_NEXT_SUB_STEP();
    }
    enMoveAngleToPlayer(dp, enONIGetRotSpeed());
}

static void enONICtrlBerserk(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec;
    float d;
    int t;
    SubCharacter* scp;
    float* pos;
    if (enCheckDamage(dp)) {
        if (enONISetDamage(dp)) {
            ENEMY_STEP(ENEMY_ONI_STATE_DAMAGE);
            return;
        }
        if (enCheckSpray(dp)) {
            ENEMY_STEP(ENEMY_ONI_STATE_CONFUSE);
            return;
        }
    }
    if (dp->sslv == 0) {
        enONIAnimeSet(dp, 1);
        enInitPath(&dp->path, dp->scp->rot.y);
        ENEMY_NEXT_SUB_STEP();
    }
    enONIGetWalkSpeed(dp);
    scp = enGetNearCharacter(dp);
    
    t = enONICanSeeCharacter(dp, scp);
    if (t == 2) {
        ENEMY_STEP(ENEMY_ONI_STATE_ATTACK);
    }
    
    pos = &scp->pos;
    shSubVector(vec, &dp->scp->pos, pos);
    d = vec3_length(vec);
    if (d < 250.0f) {
        shVectorCopy(vec, pos);
    } else {
        shScaleVector(vec, vec, 250.0f / d);
        shAddVector(vec, pos, vec);
    }
    enSetPath(dp, vec, &dp->scp->pos);
    enMoveAngle(&dp->path, enONIGetRotSpeed());
    dp->scp->rot.y = dp->path.angle;
}

static void enONICtrlAttack(EnLOCAL_DATA* dp) {
    if (enCheckDamage(dp)) {
        if (enONISetDamage(dp)){
            ENEMY_STEP(ENEMY_ONI_STATE_DAMAGE);
            return;
        }
    }
    switch (dp->sslv) {
        case 0:
            enONIAnimeSet(dp, 3);
            enInitPath(&dp->path, dp->scp->rot.y);
            enFlagSetCritical(dp);
            enAttackStart(dp);
            ENEMY_NEXT_SUB_STEP();
            break;
        
        case 1:
            enAttackCheck(dp, 49);
            if (enGetMode() >= SH2_BATTLE_LEVEL_HARD) {
                enMoveAngleToPlayer(dp, enONIGetRotSpeed());
            }
            if (dp->anim_n == -1) {
                if (!(dp->flag & (1 << 2)) && (dp->type == 1)) {
                    
                    dp->type = 0;
                }
                enFlagResetCritical(dp);
                if (dp->type == 1) {
                    ENEMY_STEP(ENEMY_ONI_STATE_BERSERK);
                } else if (dp->type == 0) {
                    ENEMY_STEP(ENEMY_ONI_STATE_WANDER);
                } else {
                    ENEMY_STEP(ENEMY_ONI_STATE_CHASE);
                    if (dp->oni.other && enONICanSeePlayer(dp->oni.other) >= 2) {
                        ENEMY_STEP(ENEMY_ONI_STATE_WAIT);
                    }
                }
            }
            break;
    }
    enONIGetAttackSpeed(dp);
}

static void enONICtrlAttack3(EnLOCAL_DATA* dp) {
    if (enCheckDamage(dp)) {
        enONISetDamage(dp);
        enSetTimer(dp, 0);
        if (enCheckSpray(dp)) {
            ENEMY_STEP(ENEMY_ONI_STATE_CONFUSE);
            return;
        }
    }
    switch (dp->sslv) {
        case 0:
            enONIAnimeSet(dp, 5);
            enFlagSetCritical(dp);
            enAttackStart(dp);
            ENEMY_NEXT_SUB_STEP();
            break;
        case 1:
            if (dp->anim_n == -1) {
                enONIAnimeSet(dp, 4);
                dp->oni.timer2 = ((shRandI() >> 12) & 3) + 2;
                ENEMY_NEXT_SUB_STEP();
            }
            break;
        case 2:
            enAttackCheck(dp, 50);
            if ((dp->anim_loop >= dp->oni.timer2) || !(dp->flag & (1 << 2)) || ((dp->p_dist > 2500.0f) && (dp->anim_loop > 0) && (dp->anim_n < 48000)) || (dp->anim_step > 0)) {
                
                
                enONIAnimeSet(dp, 6);
                ENEMY_NEXT_SUB_STEP();
            }
            break;
        case 3:
            if (dp->anim_n == -1) {
                enFlagResetCritical(dp);
                ENEMY_STEP(ENEMY_ONI_STATE_CHASE);
            }
            break;
    }
    enONIGetAttackSpeed(dp);
}

static void enONICtrlDamage(EnLOCAL_DATA* dp) {
    int m; float d0; float d1; float d2; float d3; float d4; int id;  int n1; int n2;
    switch (dp->sslv) {
        case 0:
            if (dp->type == 2) {
                dp->endurance = dp->endurance_max;
            } else {
                enSetHP(dp, 1000000.0f, 1000000.0f);
            }
            m = enONIGetDamageMotion(dp);
            FJ_ASSERT_ON_LINE(m != 0, 826);
            enONIAnimeSet(dp, m);
            enFlagResetCritical(dp);
            ENEMY_NEXT_SUB_STEP();
            return;
        case 1:
            if (enCheckDamage(dp)) {
                if (enONISetDamage(dp)) {
                    dp->sslv = 0;
                    return;
                }
            }
            if (dp->anim_n == -1) {
                if ((dp->type == 2) && enCheckDeath(dp) && enCheckDeath(dp->oni.other)) {
                    
                    
                    ENEMY_STEP(ENEMY_ONI_STATE_SUICIDE);
                    ((EnLOCAL_DATA*) dp->oni.other)->slv = ENEMY_ONI_STATE_SUICIDE;
                    ((EnLOCAL_DATA*) dp->oni.other)->sslv = 0;
    
                    
                    
                    d0 = enCalcDirection(&((EnLOCAL_DATA*) dp->oni.other)->scp->pos, &dp->scp->pos);
                    d1 = enCalcDirection(suicide_point[0], &dp->scp->pos);
                    d2 = enCalcDirection(suicide_point[1], &dp->scp->pos);
                    d3 = shAngleRegulate(d1 - d0);
                    d4 = shAngleRegulate(d2 - d0);
                    if ((d3 * d4) < 0.0f) {
                        d0 = shVectorDistXz_reverse(&((EnLOCAL_DATA*) dp->oni.other)->scp->pos, &dp->scp->pos);
                        d1 = shVectorDistXz_reverse(suicide_point[0], &dp->scp->pos);
                        d2 = shVectorDistXz_reverse(suicide_point[1], &dp->scp->pos);
                        d3 = shVectorDistXz_reverse(suicide_point[0], &((EnLOCAL_DATA*) dp->oni.other)->scp->pos);
                        d4 = shVectorDistXz_reverse(suicide_point[1], &((EnLOCAL_DATA*) dp->oni.other)->scp->pos);
                        if ((d2 > d0) && (d1 < d0)) {
                            id = 0;
                        } else if ((d1 > d0) && (d2 < d0)) {
                            id = 1;
                        } else {
                            
                            n1 = 0;
                            if (d2 > d1) {
                                d1 = d2;
                                n1 = 1;
                            }
                            n2 = 0;
                            if (d4 > d3) {
                                d3 = d4;
                                n2 = 1;
                            }
                            if ((n1 != n2) || (d1 < d3)) {
                                id = n1;
                            } else {
                                id = n1 ^ 1;
                            }
                        }                   
                    } else
                        if ((shFloatAbs(d3) > shFloatAbs(d4))) {
                        id = 0;
                    } else {
                        id = 1;
                    }
                    
                    dp->oni.id = id;
                    ((EnLOCAL_DATA*) dp->oni.other)->oni.id = id ^ 1;
                
                } else {
                    ENEMY_STEP(ENEMY_ONI_STATE_CHASE);
                }
            } 

    }
}

#ifdef NON_MATCHING
static void enONICtrlConfuse(EnLOCAL_DATA* dp) {
    EnLOCAL_DATA* tp;
    if (enCheckDamage(dp)) {
        if (enCheckSpray(dp)) {
            if (dp->sslv != 4) {
                ENEMY_SUB_STEP(0);
            }
        } else {
            if (enONISetDamage(dp)) {
                ENEMY_STEP(ENEMY_ONI_STATE_DAMAGE);
            } else {
                ENEMY_STEP(ENEMY_ONI_STATE_WANDER);
            }
            return;
        }
    }
    if (dp->sslv == 0) {
        enReduceHP(dp);
        enONIAnimeSet(dp, 2);
        ENEMY_NEXT_SUB_STEP();
    }
    if (dp->sslv >= 4) {
        tp = dp->oni.tp;
        dp->path.markangle = enCalcDirection(&tp->scp->pos, &dp->scp->pos);
        enMoveAngle(&dp->path, enONIGetRotSpeed());
        dp->scp->rot.y = dp->path.angle;
        enAttackCheck(dp, 49);
        if (dp->anim_n == -1) {
            if ((++dp->sslv < 6) &&
                (shVectorDistXz_reverse(&tp->scp->pos, &dp->scp->pos) < 1250.0f)) {
                enAttackStart(dp);
                enONIAnimeReset(dp, 3);
            } else {
                ENEMY_STEP(ENEMY_ONI_STATE_WANDER);
            }
        }
        return;
    }
    if ((dp->sslv == 1) && (dp->anim_n == -1)) {
        tp = enGetNearOtherEnemy(dp);
        if ((tp != NULL) && enGetSprayPower() && (shFloatAbs(tp->scp->pos.y - dp->scp->pos.y) < 250.0f) && (shVectorDistXz(&tp->scp->pos, &dp->scp->pos) < 1250.0f)) {            
            
                        
            dp->oni.tp = tp;
            enAttackStart(dp);
            enONIAnimeSet(dp, 3);
            enInitPath(&dp->path, dp->scp->rot.y);
            ENEMY_SUB_STEP(4);
        } else {
            ENEMY_NEXT_SUB_STEP();
            enSetTimer(dp, 600 - (enGetMode() * 90));
        }
    } else if ((dp->sslv == 2) && (enReduceTimer(dp) <= 0)) {
        ENEMY_STEP(ENEMY_ONI_STATE_WANDER);
    }
    enONISoundLife(dp);
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_oni", enONICtrlConfuse);
#endif

static void enONICtrlSuicide(EnLOCAL_DATA* dp) {
    float d; float a;
    int t; int td; int ts;
    if (enCheckDamage(dp)) {
        enResetDamage(dp);
    }
    switch (dp->sslv) {
        case 0:
            enONIAnimeSet(dp, 1);
            dp->weight = 4;
            enInitPath(&dp->path, dp->scp->rot.y);
            ENEMY_NEXT_SUB_STEP();
            break;
        
        case 2:
            enAttackCheck(dp, 49);
            enMoveAngleToPlayer(dp, enONIGetRotSpeed());
            if (dp->anim_n == -1) {
                ENEMY_SUB_STEP(0);
            }
            return;
        case 3:
        case 4:
            dp->path.markangle = suicide_point[dp->oni.id][3];
            enMoveAngle(&dp->path, enONIGetRotSpeed());
            dp->scp->rot.y = dp->path.angle;
            shSubVector(dp->vec, suicide_point[dp->oni.id], &dp->scp->pos);
            dp->vec[1] = dp->vec[3] = 0.0f;
            if (dp->scp->rot.y == dp->path.markangle) {
                ENEMY_SUB_STEP(4);
                if (((EnLOCAL_DATA*) dp->oni.other)->sslv == 4) {
                    SET_GAME_FLAG(GAME_FLAG_483);    
                }
            }
            return;
        }
        if ((d = shVectorDistXz_reverse(suicide_point[dp->oni.id], &dp->scp->pos)) < 50.0f) {
            enONIAnimeSet(dp, 2);
            dp->sslv = 3;
            return;
        }
        if (d > shVectorDistXz_reverse(suicide_point[((EnLOCAL_DATA*) dp->oni.other)->oni.id], &((EnLOCAL_DATA*) dp->oni.other)->scp->pos) + 100.0f) {
            
            t = 5000;
        } else {
            t = 4096;
        }
        ts = ftoi(4096.0f * shGetDT());
        td = t - dp->anim_s;
        if (td < -ts) dp->anim_s -= ts;
        else if (td > ts) dp->anim_s += ts;
        else dp->anim_s = t;
        dp->path.markangle = a = enCalcDirection(suicide_point[dp->oni.id], &dp->scp->pos);
        enMoveAngle(&dp->path, enONIGetRotSpeed());
        dp->scp->rot.y = dp->path.angle;            
        if ((enCalcAngleDifference(a, enGetPlayerDirection(dp)) < TO_RAD(10)) && (dp->p_dist < 1250.0f)) {
            
            enONIAnimeReset(dp, 3);
            enAttackStart(dp);
            ENEMY_SUB_STEP(2);
        }   
}

static void enONICtrlDead(EnLOCAL_DATA* dp) {
    if (dp->sslv == 0) {
        dp->weight = 4;
        enONIAnimeSet(dp, 15);
        enFlagSetNoDamage(dp);
        enFlagSetDead(dp);
        ENEMY_NEXT_SUB_STEP();
    }
}

static void enONICheckPlayerWeapon(EnLOCAL_DATA* dp) {
    switch (enGetPlayerWeapon()) {
        case WEAPON_ID(WEAPON_ID_NONE):
        case WEAPON_ID(WEAPON_HANDGUN_CHARA_KIND):
        case WEAPON_ID(WEAPON_KAKUZAI_CHARA_KIND):
        case WEAPON_ID(WEAPON_SP_CHARA_KIND):
            enFlagSetNoDamage(dp);
            break;
        default:
            enFlagResetNoDamage(dp);
            break;
    }
}

static int enONIGetDamageMotion(EnLOCAL_DATA* dp) {
    int m; int id; int dd;
    float a;

    a = shAngleRegulate(shAtanV(&dp->scp->battle.vec) - dp->scp->rot.y);
    if (shFloatAbs(a) > QUARTER_TURN) dd = 0;
    else dd = 1;    
    id = dp->last_atk;
    switch (id) {
        case 2:
        case 1:
        case 12:
        case 13:
        case 15:
        case 16:
        case 23:
        case 24:
        case 36:
        case 38:
        case 39:
            m = 0;
            break;
        case 4:
        case 6:
            m = dd + 7;
            break;
        case 14:
        case 17:
            m = 9;
            break;
        case 18:
            m = dd + 10;
            break;
        case 19:
        case 20:
            if (a < 0.0f) {
                m = 12;
            } else {
                m = 13;
            }
            break;
        case 21:
        case 22:
            m = 14;
            break;
        default:
            m = 0;
            printf("Illegal damage type!(%d)\n", id);
    }
    return m;
}

static int enONISetDamage(EnLOCAL_DATA* dp) { // @note: not line matched
    enONISetSlowTime(dp);
    if (dp->type != 2) {
        dp->endurance -= dp->scp->battle.damage;
        if (dp->endurance < 0.0f) {
            dp->endurance = 0.0f;
        }
        dp->scp->battle.damage = 0.0f;
    } else {
        if ((dp->scp->battle.hp -= dp->scp->battle.damage) < 0.0f) {
            dp->endurance = 0.0f;
            if ((((EnLOCAL_DATA*) dp->oni.other)->scp->battle.hp += (0.5f * dp->scp->battle.hp)) < 0.0f) {
                ((EnLOCAL_DATA*) dp->oni.other)->scp->battle.hp = 0.0f;
            }
            ((EnLOCAL_DATA*) dp->oni.other)->scp->battle.hp_rate = 100.0f * (((EnLOCAL_DATA*) dp->oni.other)->scp->battle.hp / ((EnLOCAL_DATA*) dp->oni.other)->scp->battle.hp_max);
            dp->scp->battle.hp = 0.0f;
        }
        dp->endurance -= dp->scp->battle.damage;
        if (dp->endurance < 0.0f) {
            dp->endurance = 0.0f;
        }
        dp->scp->battle.damage = 0.0f;
        dp->scp->battle.hp_rate = 100.0f * (dp->scp->battle.hp / dp->scp->battle.hp_max);
        if (dp->endurance <= 0.0f) {
            return 1;
        }
    }
    return 0;
}

static int enONICanSeePlayer(EnLOCAL_DATA* dp) {
    float* ppos = enGetPlayerPos(dp);
    float dist; float a;    
    int wcd = enGetWorldCondition();
    dist = enCheckPath2(dp, ppos, &dp->scp->pos);
    if (dist >= 0.0f) {
        if ((wcd >= 2) && (enCheckSeeLight(dp))) {
            return 1;
        }
        return 0;
    }
    dist = dp->p_dist;
    if (dist > enONIGetFeelRange()) return 0;    
    if (enCheckNoDamageHuman(dp)) return 1;
    if (dp->oni.other && (((EnLOCAL_DATA*) dp->oni.other)->slv == ENEMY_ONI_STATE_ATTACK || ((EnLOCAL_DATA*) dp->oni.other)->slv == ENEMY_ONI_STATE_ATTACK3)) {
        return 1;
    }
    a = enCalcDirection(ppos, &dp->scp->pos);
    a = enCalcAngleDifference(a, dp->scp->rot.y);
    if ((dp->type == 2) && (dist < 1100.0f) && ((dp->oni.other == 0) || shVectorDistXz_reverse(&dp->scp->pos, &((EnLOCAL_DATA *)dp->oni.other)->scp->pos) > 750.0f)) {
        
        
        if ((dp->scp->pos.x > -22100.0f) && (dp->scp->pos.x < -17900.0f) &&
            (dp->scp->pos.z > 19500.0f) && (dp->scp->pos.z < 24500.0f)) 
            
            return 4;                   
    }
    if ((dist < 1250.0f) && (a < TO_RAD(10))) return 2;    
    return 1;
}

static int enONICanSeeCharacter(EnLOCAL_DATA* dp, SubCharacter* scp) {
    float* ppos = &scp->pos;
    float dist; float a;
    int wcd = enGetWorldCondition();
    dist = enCheckPath2(dp, ppos, &dp->scp->pos);
    if (dist >= 0.0f) return 0;
    dist = shVectorDistXz_reverse(ppos, &dp->scp->pos);
    if (dist > enONIGetFeelRange()) return 0;
    
    a = enCalcDirection(ppos, &dp->scp->pos);
    a = enCalcAngleDifference(a, dp->scp->rot.y);
    if ((dist < 1250.0f) && (a < TO_RAD(10))) return 2;    
    if (enLocalWork.Status & 1) return 0;
    return 1;
}

static void enONIAnimeSet(EnLOCAL_DATA* dp, int anim) {
    if (anim == dp->anim) {
        enAnimeRestart(dp);
        return;
    }
    
    FJ_ASSERT_ON_LINE(anim >= 0 && anim < sizeof(EnONIAnime) / sizeof(EnANIME_DATA), 1199);
    enAnimeSet(dp, anim, EnONIAnime[anim].Anime);
}

static void enONIAnimeReset(EnLOCAL_DATA* dp, int anim) {
    
    FJ_ASSERT_ON_LINE(anim >= 0 && anim < sizeof(EnONIAnime) / sizeof(EnANIME_DATA), 1207);
    enAnimeSet(dp, anim, EnONIAnime[anim].Anime);
}

static void enONIAnimeExec(EnLOCAL_DATA* dp) {
    int of = dp->anim_n;
    enAnimeExec(dp, EnONIAnime, ONI_PLAY_ANIM(1));
    if ((dp->anim_n == -1) || (dp->flag & 1)) return;
    if (dp->anim == 1) {
        
        enSetTransWalk(dp);
        
        if (((dp->anim_s > 0) &&
             (((of < 52800) && (dp->anim_n >= 52800)) || ((of < 105600) && (dp->anim_n >= 105600)))) ||
                ((dp->anim_s < 0) &&
                 (((of > 43200) && (dp->anim_n <= 43200)) || ((of > 96000) && (dp->anim_n <= 96000))))) {
            
            
            
            
            
            
            
            if (enCheckWater(dp)) {
                enSoundCall(18808, 1.0f, &dp->scp->pos);
                return;
            }
           
            if (dp->flag & (1 << 12)) {
                enSoundCall3D(16113, 1.0f, &dp->scp->pos);
            } else
                enSoundCall(16113, 1.0f, &dp->scp->pos);
        }
    }


}

static float enONIGetSpeed(EnLOCAL_DATA* dp) {
    return 0.25f + (0.75f * (dp->endurance / dp->endurance_max));
}

static float enONIGetWalkSpeed(EnLOCAL_DATA* dp) {
    float speed_rate[5] = { 0.5f, 0.8f, 1.0f, 1.1f, 1.2f };
    float r;

   
    
    
    
    r = enONIGetSpeed(dp) * speed_rate[enGetMode()];
    if (dp->type == 1) {
        r *= 1.5f;
    }
    dp->anim_s = ftoi(4096.0f * r);
    return r;
}

static float enONIGetAttackSpeed(EnLOCAL_DATA* dp) {
    float speed_rate[5] = { 0.75f, 0.8f, 1.0f, 1.1f, 1.2f };
    float r;

    
    
    
    
    r = enONIGetSpeed(dp) * speed_rate[enGetMode()];
    dp->anim_s = ftoi(4096.0f * r);
    return r;
}

static float enONIGetFeelRange(void) {
    float feel_range[5] = { 1000.0f, 1500.0f, 2000.0f, 2500.0f, 4000.0f };
    float r;


    
    
    
    r = feel_range[enGetMode()];
    if (enGetWorldCondition() == 4) {
        r *= 0.75f;
    }
    return r;
}

static float enONIGetRotSpeed(void) {
    float rot_rate[5] = { 0.5f, 0.7f, 1.0f, 1.5f, 2.0f };
    
    
    
    
    
    
    return TO_RAD(3) * rot_rate[enGetMode()];
}

static void enONISetSlowTime(EnLOCAL_DATA* dp) {
    int timer[5] = { 180, 90, 60, 30, 1 };

    
    
    
    
    
    enSetTimer(dp, timer[enGetMode()]);
}

static void enONISoundLife(EnLOCAL_DATA* dp) {
    if (dp->sound_wait < 300) {
        dp->sound_wait++;
    } else if ((dp->anim == 2) || (shRandF() < (0.2f * shGetDT()))) {
        
        enSoundCall(ftoi(2.0f * shRandF()) + 16118, 1.0f, &dp->scp->pos);
        
        dp->sound_wait = 0;
    }
}

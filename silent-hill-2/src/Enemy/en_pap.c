#include "sh2_common.h"
#include "SH2_common/sh2dt.h"
#include "SH2_common/sh_vu0.h"

#include "gs.h"
#include "math.h"
#include "vec.h"

#include "sce/libgraph.h"

#include "Fog/spack.h"
#include "Font/fj_man.h"
#include "view/camera_dat.h"

#include "Event/event.h"
#include "Enemy/en_common.h"
#include "Enemy/en_pap.h"

//* abstract daddy *//

static void enPAPCtrlAutomatic(EnLOCAL_DATA* dp);
static void enPAPCtrlSleep(EnLOCAL_DATA* dp);
static void enPAPCtrlGoPlayable(EnLOCAL_DATA* dp);
static void enPAPCtrlEvent(EnLOCAL_DATA* dp);
static void enPAPCtrlHand(EnLOCAL_DATA* dp);
static void enPAPCtrlWander(EnLOCAL_DATA* dp);
static void enPAPCtrlStraight(EnLOCAL_DATA* dp);
static void enPAPCtrlChase(EnLOCAL_DATA* dp);
static void enPAPCtrlRush(EnLOCAL_DATA* dp);
static void enPAPCtrlAttack(EnLOCAL_DATA* dp);
static void enPAPCtrlDamage(EnLOCAL_DATA* dp);
static void enPAPCtrlConfuse(EnLOCAL_DATA* dp);
static void enPAPCtrlDown(EnLOCAL_DATA* dp);
static void enPAPCtrlLastMove(EnLOCAL_DATA* dp);
static void enPAPMoveAngle(EnLOCAL_DATA* dp);
static int enPAPCanSeePlayer(EnLOCAL_DATA* dp);
static void enPAPAnimeSet(EnLOCAL_DATA* dp, int anim);
static void enPAPAnimeExec(EnLOCAL_DATA* dp);
static void enPAPAutoRecovery(EnLOCAL_DATA* dp);
static float enPAPGetWalkSpeed(EnLOCAL_DATA* dp);
static float enPAPGetRotSpeed(void);
static float enPAPGetTurnSpeed(EnLOCAL_DATA* dp);
static void enPAPSetDownTime(EnLOCAL_DATA* dp);
static void enPAPSetMoveCount(EnLOCAL_DATA* dp);
static void enPAPSetDc(EnLOCAL_DATA* dp);
static void enPAPDrawBoad(EnLOCAL_DATA* dp);
static void enPAPSoundSigns(EnLOCAL_DATA* dp);

EnANIME_DATA EnPAPAnime[33] = {
    { /* .anime = */ 5701, /* .loop  = */ false },
    { /* .anime = */ 5702, /* .loop  = */ true  },
    { /* .anime = */ 5701, /* .loop  = */ true  },
    { /* .anime = */ 5704, /* .loop  = */ true  },
    { /* .anime = */ 5727, /* .loop  = */ true  },
    { /* .anime = */ 5706, /* .loop  = */ false },
    { /* .anime = */ 5707, /* .loop  = */ false },
    { /* .anime = */ 5708, /* .loop  = */ false },
    { /* .anime = */ 5709, /* .loop  = */ false },
    { /* .anime = */ 5710, /* .loop  = */ false },
    { /* .anime = */ 5711, /* .loop  = */ false },
    { /* .anime = */ 5712, /* .loop  = */ false },
    { /* .anime = */ 5713, /* .loop  = */ false },
    { /* .anime = */ 5709, /* .loop  = */ false },
    { /* .anime = */ 5714, /* .loop  = */ false },
    { /* .anime = */ 5715, /* .loop  = */ false },
    { /* .anime = */ 5716, /* .loop  = */ false },
    { /* .anime = */ 5717, /* .loop  = */ false },
    { /* .anime = */ 5718, /* .loop  = */ false },
    { /* .anime = */ 5719, /* .loop  = */ false },
    { /* .anime = */ 5720, /* .loop  = */ false },
    { /* .anime = */ 5721, /* .loop  = */ false },
    { /* .anime = */ 5701, /* .loop  = */ false },
    { /* .anime = */ 5722, /* .loop  = */ false },
    { /* .anime = */ 5701, /* .loop  = */ true  },
    { /* .anime = */ 5723, /* .loop  = */ true  },
    { /* .anime = */ 5701, /* .loop  = */ false },
    { /* .anime = */ 5725, /* .loop  = */ false },
    { /* .anime = */ 5703, /* .loop  = */ false },
    { /* .anime = */ 5705, /* .loop  = */ false },
    { /* .anime = */ 5724, /* .loop  = */ false },
    { /* .anime = */ 5726, /* .loop  = */ false },
    { /* .anime = */ 5728, /* .loop  = */ false }
};

#define ENEMY_PAP_MODE_DUMMY         0
#define ENEMY_PAP_MODE_AUTOMATIC     1
#define ENEMY_PAP_MODE_SLEEP         2
#define ENEMY_PAP_MODE_GO_PLAYABLE   3
#define ENEMY_PAP_MODE_EVENT         4
#define ENEMY_PAP_MODE_HAND          5

#define ENEMY_PAP_STATE_WANDER       0
#define ENEMY_PAP_STATE_STRAIGHT     1
#define ENEMY_PAP_STATE_CHASE        2
#define ENEMY_PAP_STATE_RUSH         3
#define ENEMY_PAP_STATE_ATTACK       4
#define ENEMY_PAP_STATE_DAMAGE       5
#define ENEMY_PAP_STATE_CONFUSE      6
#define ENEMY_PAP_STATE_DOWN         7
#define ENEMY_PAP_STATE_LAST_MOVE    8
#define ENEMY_PAP_STATE_DYING        9

typedef enum _EnPAPAnimKind {
    PAPAnime_01 = 1,
    PAPAnime_02 = 2,
    PAPAnime_03 = 3,
    PAPAnime_04 = 4,
    PAPAnime_23 = 23,
    PAPAnime_25 = 25,
    PAPAnime_27 = 27,
    PAPAnime_28 = 28,
    PAPAnime_29 = 29,
    PAPAnime_30 = 30,
    PAPAnime_31 = 31,
    PAPAnime_32 = 32,
} EnPAPAnimKind;

#pragma fast_fptosi on
#pragma divbyzerocheck off

#ifdef HOLY_CANDLE
#line 130
void enPAPInitData(EnLOCAL_DATA* dp) {
    float vitarity[5] = { 
        500.0f,
        750.0f,
        1000.0f,
        2000.0f,
        4000.0f
    }; // r29+0x20
    float endurance[5] = { 
        150.0f,
        285.0f,
        380.0f,
        500.0f,
        600.0f
    }; // r29+0x40
    
    float vitarity2[5] = { 
        1000.0f,
        4000.0f,
        5000.0f,
        7000.0f,
        10000.0f
    }; // r29+0x60
    float endurance2[5] = { 
        300.0f,
        400.0f,
        600.0f,
        800.0f,
        1000.0f 
    }; // r29+0x80
    int mode = enGetMode(); // r2
    
    ENEMY_MLV(ENEMY_PAP_MODE_AUTOMATIC);
    switch (dp->scp->en_first_status) {
        case 6:
            ENEMY_STEP(ENEMY_PAP_STATE_CHASE);
            enSetHP(dp, vitarity2[mode], endurance2[mode]);
            dp->type = 1;
            break;
        case 13:
            dp->type = 1;
            dp->flag = 1 << 15;
            enPAPAnimeSet(dp, PAPAnime_25);
            enSetSize(dp, 300.0f, 250.0f, 125.0f, 125.0f);
            dp->weight = 4;
            enFlagSetNoDamage(dp);
            ENEMY_MLV(ENEMY_PAP_MODE_EVENT);
            return;
        case 5:
            enPAPAnimeSet(dp, PAPAnime_27);
            ENEMY_STEP(ENEMY_PAP_STATE_DYING);
            return;
        default:
            ENEMY_STEP(ENEMY_PAP_STATE_STRAIGHT);
            enSetHP(dp, vitarity[mode], endurance[mode]);
            dp->type = 0;
            break;
    }
    
    enSetSize(dp, 400.0f, 650.0f, 600.0f, 650.0f);
    dp->weight = 3;
    enPAPAnimeSet(dp, PAPAnime_02);
    enSetBattleTarget(dp, true);
    if (enCheckSleepIn(dp)) {
        enSleepIn(dp);
    }
}
#else
float vitarity_0x002AA840[5] = { 
    500.0f,
    750.0f,
    1000.0f,
    2000.0f,
    4000.0f
}; // r29+0x20
float endurance_0x002AA860[5] = { 
    150.0f,
    285.0f,
    380.0f,
    500.0f,
    600.0f
}; // r29+0x40

float vitarity2_0x002AA880[5] = { 
    1000.0f,
    4000.0f,
    5000.0f,
    7000.0f,
    10000.0f
}; // r29+0x60
float endurance2_0x002AA8A0[5] = { 
    300.0f,
    400.0f,
    600.0f,
    800.0f,
    1000.0f 
}; // r29+0x80
INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPInitData);
#endif

#line 202
void enPAPCtrlMain(EnLOCAL_DATA* dp) {
    void (*enCtrlPAPFunc[6])(EnLOCAL_DATA*) = {
        enDummyCtrl,
        enPAPCtrlAutomatic,
        enPAPCtrlSleep,
        enPAPCtrlGoPlayable,
        enPAPCtrlEvent,
        enPAPCtrlHand
    }; // r29+0x10

    enCtrlPAPFunc[dp->mlv](dp);
}


#line 217
static void enPAPCtrlAutomatic(EnLOCAL_DATA* dp) {
    void (*enCtrlPAPSubFunc[10])(EnLOCAL_DATA*) = {
        enPAPCtrlWander,
        enPAPCtrlStraight,
        enPAPCtrlChase,
        enPAPCtrlRush,
        enPAPCtrlAttack,
        enPAPCtrlDamage,
        enPAPCtrlConfuse,
        enPAPCtrlDown,
        enPAPCtrlLastMove,
        enDyingExec 
    }; // r29+0x20
    
    enSetBattleTarget(dp, true);
    
    enCtrlPAPSubFunc[dp->slv](dp);
    
    
    enPAPAnimeExec(dp);
    
    enMoveExec(dp);
    if (dp->type != 1 && dp->slv != ENEMY_PAP_STATE_DYING && 
        enCheckSleepIn(dp)) {
        enSleepIn(dp);
    }
}


#line 247
static void enPAPCtrlSleep(EnLOCAL_DATA* dp) {
    if (enCheckSleepOut(dp)) {
        enSleepOut(dp);
        ENEMY_STEP(ENEMY_PAP_STATE_STRAIGHT);
        enFlagResetLieDown(dp);
    }
}


#line 257
static void enPAPCtrlGoPlayable(EnLOCAL_DATA* dp) {
    ENEMY_MLV(ENEMY_PAP_MODE_AUTOMATIC);
    ENEMY_STEP(ENEMY_PAP_MODE_DUMMY);
}


#line 264
static void enPAPCtrlEvent(EnLOCAL_DATA* dp) {
    if (++dp->sslv >= 10) {
        enAnimePause(dp);
        ENEMY_MLV(ENEMY_PAP_MODE_AUTOMATIC);
        ENEMY_STEP(ENEMY_PAP_STATE_DYING);
    }
}

#line 399
static void enPAPCtrlHand(EnLOCAL_DATA* dp) {
    /* empty */
}


#ifdef HOLY_CANDLE
#line 405
static void enPAPCtrlWander(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec; // r29+0x20
    float a; // r29+0x30
    int t; // r2
    if (enCheckDamage()) {
        if (enCheckSpray(dp)) {
            enReduceHP(dp);
            if (enGetSprayPower()) {
                ENEMY_STEP(ENEMY_PAP_STATE_CONFUSE);
                return;
            }
        } else {
            ENEMY_STEP(ENEMY_PAP_STATE_DAMAGE);
            return;
        }
    }
    t = enPAPCanSeePlayer(dp);
    if (t == 2) {
        ENEMY_STEP(ENEMY_PAP_STATE_ATTACK);
        return;
    } else if (t == 1 || dp->p_dist < 1000.0f) {
        ENEMY_STEP(ENEMY_PAP_MODE_SLEEP); // gn
        return;
    }
    switch (dp->sslv) {
        case 0:
            enPAPAnimeSet(dp, PAPAnime_01);
            enPAPGetWalkSpeed(dp);
            enInitPath(&dp->path, dp->scp->rot.y);
            shSinCosV_Scale(vec, dp->scp->rot.y, 1500.0f);
            shAddVector(dp->pap.target, &dp->scp->pos, vec);
            ENEMY_NEXT_SUB_STEP();
            break;
        case 1:
            if (shRandF() < 0.01f) {
                enPAPAnimeSet(dp, PAPAnime_02);
                ENEMY_SUB_STEP(2);
                break;
            }
            if (shVectorDistXz(&dp->scp->pos, dp->pap.target) < 750.0f || 
                shRandF() < 0.01f) {
                a = dp->scp->rot.y + ((PI * (shRandF() - 0.5f)) / 2.0f);
                shSinCosV_Scale(&vec, a, 1500.0f);
                shAddVector(dp->pap.target, &dp->scp->pos, vec);
            }
            if (enSetPath(dp, dp->ins.view_rot, &dp->scp->pos)) {
                shSinCosV_Scale(&vec, dp->path.markangle, 1500.0f);
                shAddVector(dp->pap.target, &dp->scp->pos, vec);
                dp->path.timer = 0;
            }
            break;
        case 2:
            if (dp->anim_n == -1) {
                enPAPAnimeSet(dp, PAPAnime_01);
                ENEMY_SUB_STEP(1);
            }
            break;
        case 3:
            if (dp->anim_n == -1) {
                enPAPAnimeSet(dp, PAPAnime_01);
                ENEMY_SUB_STEP(1);
            }
            break;
    }
    enPAPMoveAngle(dp);
    if (enCalcAngleDifference(dp->path.markangle, dp->path.angle) > QUARTER_TURN) {
        enPAPAnimeSet(dp, PAPAnime_30);
        ENEMY_SUB_STEP(3);
    }
    enPAPAutoRecovery(dp);
    enPAPSoundSigns(dp);
}


#line 480
static void enPAPCtrlStraight(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec; // r29+0x20
    if (enCheckDamage()) {
        enFlagSetMoved(dp);
        if (enCheckSpray(dp)) {
            enReduceHP(dp);
            if (enGetSprayPower()) {
                ENEMY_STEP(ENEMY_PAP_STATE_CONFUSE);
                return;
            }
        } else {
            ENEMY_STEP(ENEMY_PAP_STATE_DAMAGE);
            return;
        }
    }
    switch (dp->sslv) {
        case 0:
            enPAPAnimeSet(dp, PAPAnime_01);
            enPAPGetWalkSpeed(dp);
            enInitPath(&dp->path, dp->scp->rot.y);
            shSinCosV_Scale(vec, dp->scp->rot.y, 1500.0f);
            shAddVector(dp->pap.target, &dp->scp->pos, vec);
            ENEMY_NEXT_SUB_STEP();
            break;
        case 1:
            if (shRandF() < 0.001f) {
                enPAPAnimeSet(dp, PAPAnime_02);
                ENEMY_SUB_STEP(2);
                return;
            }
            if (enPAPCanSeePlayer(dp) == 2) {
                enFlagSetMoved(dp);
                ENEMY_STEP(ENEMY_PAP_STATE_ATTACK);
                return;
            }
            if (!enSetPath(dp, dp->ins.view_rot, &dp->scp->pos)) break;
            if (shRandF() < 0.01f) {
                enPAPAnimeSet(dp, PAPAnime_02);
                ENEMY_SUB_STEP(2);
                return;
            }
            dp->path.timer = 0;
            
            break;
        case 2:
            if (dp->anim_n == -1) {
                enPAPAnimeSet(dp, PAPAnime_01);
                ENEMY_SUB_STEP(1);
            } else
                return;
        /* fallthrough (this seems to be a @bug? since `dp->anim_n == -1` is checked above) */
        case 3:
            if (dp->anim_n == -1) {
                enPAPAnimeSet(dp, PAPAnime_01);
                ENEMY_SUB_STEP(1);
            }
            break;
    }
    enPAPMoveAngle(dp);
    if (!(enCalcAngleDifference(dp->path.markangle, dp->path.angle) <= QUARTER_TURN)) {
        enPAPAnimeSet(dp, PAPAnime_30);
        ENEMY_SUB_STEP(3);
    }
    shSinCosV_Scale(&vec, dp->path.markangle, 1500.0f);
    shAddVector(dp->pap.target, &dp->scp->pos, vec);
    enPAPAutoRecovery(dp);
    enPAPSoundSigns(dp);
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlWander);
INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlStraight);
#endif

#line 551
static void enPAPCtrlChase(EnLOCAL_DATA* dp) {
    int t; // r2
    if (enCheckDamage()) {
        if (enCheckSpray(dp)) {
            enReduceHP(dp);
            if (enGetSprayPower()) {
                ENEMY_STEP(ENEMY_PAP_STATE_CONFUSE);
                return;
            }
        } else {
            ENEMY_STEP(ENEMY_PAP_STATE_DAMAGE);
            return;
        }
    }
    if (dp->sslv == 0) {
        enPAPAnimeSet(dp, PAPAnime_01);
        ENEMY_NEXT_SUB_STEP();
    } else if (dp->sslv == 2) {
        if (dp->anim_n == -1) {
            enPAPAnimeSet(dp, PAPAnime_01);
            ENEMY_SUB_STEP(1);
        }
    }
    dp->path.markangle = enGetPlayerDirection(dp);
    dp->path.angle = dp->scp->rot.y;
    enPAPMoveAngle(dp);
    if (dp->sslv != 2) {
        float* ppos = enGetPlayerPos(dp);
        dp->anim_s = (short) (4096.0f * enPAPGetWalkSpeed(dp) *  enCalcSpeedRate(dp->scp->rot.y, &dp->scp->pos, ppos));
        
        t = enPAPCanSeePlayer(dp);
        if (t == 2) {
            ENEMY_STEP(ENEMY_PAP_STATE_ATTACK);
        } else if (t == 0 && dp->type == 0 && (dp->p_dist > 2500.0f || enLocalWork.Status & (1 << 0))) {
        
            
            ENEMY_STEP(ENEMY_PAP_STATE_WANDER);
        } else if (!(enCalcAngleDifference(dp->path.markangle, dp->path.angle) <= QUARTER_TURN)) {
            
            enPAPAnimeSet(dp, PAPAnime_30);
            ENEMY_SUB_STEP(2);
        }
    }
    enPAPAutoRecovery(dp);
    enPAPSoundSigns(dp);
}


#ifdef HOLY_CANDLE
#line 599
static void enPAPCtrlRush(EnLOCAL_DATA* dp) {
    if (enCheckDamage()) {
        if (enCheckSpray(dp)) {
            enReduceHP(dp);
            if (enGetSprayPower()) {
                ENEMY_STEP(ENEMY_PAP_STATE_CONFUSE);
                return;
            }
        } else {
            if (dp->last_atk == 2 || 
                dp->last_atk == 1) {
                dp->scp->battle.damage *= 0.4f;
                enReduceHP(dp);
                if (dp->scp->battle.hp <= 0.0f) {
                    ENEMY_STEP(ENEMY_PAP_STATE_DAMAGE);
                    return;
                }
            } else {
                ENEMY_STEP(ENEMY_PAP_STATE_DAMAGE);
                return;
            }
        }
    }
    if (dp->sslv == 0) {
        enPAPAnimeSet(dp, PAPAnime_01);
        enSetNewSize(dp, 200.0f, 650.0f, 600.0f, 650.0f);
        
        enSetTimer(dp, 300);
        ENEMY_NEXT_SUB_STEP();
    } else if (dp->sslv == 2) {
        if (dp->anim_n == -1) {
            enPAPAnimeSet(dp, PAPAnime_01);
            ENEMY_STEP(ENEMY_PAP_STATE_CHASE);
        }
    }
    dp->path.markangle = enGetPlayerDirection(dp);
    dp->path.angle = dp->scp->rot.y;
    enPAPMoveAngle(dp);
    if (enReduceTimer(dp) <= 0) {
        ENEMY_STEP(ENEMY_PAP_STATE_CHASE);
        enSetNewSize(dp, 400.0f, 650.0f, 600.0f, 650.0f);
        return;
    }
    if (dp->sslv != 2) {
        dp->anim_s = (short) (5120.0f * enPAPGetWalkSpeed(dp) * enCalcSpeedRate(dp->scp->rot.y, &dp->scp->pos, enGetPlayerPos(dp)));
        
        if (enPAPCanSeePlayer(dp) == 2) {
            enFlagSetNoDamage(dp);
            ENEMY_STEP(ENEMY_PAP_STATE_ATTACK);
        }
    }
    enPAPAutoRecovery(dp);
    enPAPSoundSigns(dp);
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlRush);
#endif


#ifdef HOLY_CANDLE
#line 656
static void enPAPCtrlAttack(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec; // r29+0x30
    if (enCheckDamage()) {
        if (enCheckHuggedPlayer()) {
         
            enResetDamage(dp);
        } else {
            if (enCheckSpray(dp)) {
                enReduceHP(dp);
                if (enGetSprayPower()) {
                    ENEMY_STEP(ENEMY_PAP_STATE_CONFUSE);
                    return;
                }
            } else {
                ENEMY_STEP(ENEMY_PAP_STATE_DAMAGE);
                return;
            }
        }
    }
    switch (dp->sslv) {
        case 0:
            if (enCalcAngleDifference(enGetPlayerDirection(dp), enGetPlayerAngle(dp)) > QUARTER_TURN) {
     
                enPAPAnimeSet(dp, PAPAnime_28);
            } else {
                enPAPAnimeSet(dp, PAPAnime_31);
            }
            enSetNewSize(dp, 150.0f, 650.0f, 600.0f, 650.0f);
            enFlagSetCritical(dp);
            enAttackStart(dp);
            ENEMY_NEXT_SUB_STEP();
            break;
        case 1:
            enAttackCheck(dp, 0x39);
            dp->path.markangle = enGetPlayerDirection(dp);
            dp->path.angle = dp->scp->rot.y;
            enMoveAngle(&dp->path, 0.05235988f);
            dp->scp->rot.y = dp->path.angle;
            if (enCheckHuggedPlayer()) {
                dp->flag |= (1 << 3);

                shSinCosV_Scale(vec, enGetPlayerDirection(dp), 150.0f);
                shSubVector(vec, enGetPlayerPos(dp), vec);
                shSubVector(vec, vec, &dp->scp->pos);
                vec[1] = vec[3] = 0;
                shScaleVector(dp->vec, vec, 4.0f);
                enSetNewSize(dp, 0.0f, 650.0f, 600.0f, 650.0f);
            }
            if (dp->anim_n == -1) {
                dp->flag |= 1 << 15;
                if (!enCheckHuggedPlayer()) {
                    enPAPAnimeSet(dp, dp->anim == PAPAnime_28 ? PAPAnime_29 : PAPAnime_32);
                    
                    ENEMY_SUB_STEP(4);
                } else {
                    enPAPAnimeSet(dp, (u_char) (dp->anim == PAPAnime_28 ? PAPAnime_03 : PAPAnime_04));
                    
                    enAttackStart(dp);
                    ENEMY_SUB_STEP(2);
                }
                dp->flag &= ~(1 << 15);
            }
            break;
        case 2:
            enAttackCheckHug(dp, 0x3A);
            if (enCheckHuggedPlayer() == 0) {
                enPAPAnimeSet(dp,(u_char) (dp->anim == PAPAnime_03 ? PAPAnime_29 : PAPAnime_32));
                
                ENEMY_NEXT_SUB_STEP();
            }
            break;
        
        case 3:
            shSinCosV_Scale(dp->vec, dp->scp->rot.y, -500.0f); /* fallthrough */
        case 4:
            if (dp->anim_n == -1) {
                enSetNewSize(dp, 400.0f, 650.0f, 600.0f, 650.0f);
                dp->flag &= ~8;
                enFlagResetCritical(dp);
                enFlagResetNoDamage(dp);
                if (dp->type == 0) {
                    ENEMY_STEP(ENEMY_PAP_STATE_WANDER);
                } else {
                    ENEMY_STEP(ENEMY_PAP_STATE_CHASE);
                }
            }
            break;
    }
    enPAPAutoRecovery(dp);
    enPAPSoundSigns(dp);
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlAttack);
#endif



#ifdef HOLY_CANDLE
static void enPAPCtrlDamage(EnLOCAL_DATA* dp) {
    float d; // r20
    switch (dp->sslv) {
        case 0:
            if (dp->endurance == dp->endurance_max && 
                !enCheckCritical(dp)) {
                enReduceHP(dp);
                enAnimePause(dp);
                enSetHitBack(dp);
                enSetTimer(dp, 10);
                ENEMY_SUB_STEP(3);
                return;
            }
            enFlagResetCritical(dp);
            d = enReduceHP(dp);
            if ((d <= 0.0f) || 
                (d < 100.0f && shRandF() > (0.8f + (0.002f * d)))) {
                enPAPAnimeSet(dp, PAPAnime_enGetDownMotion(dp));
                if (dp->type == 1 && dp->scp->battle.hp <= 0.0f) {
                    
                    enSetBlur();
                    dp->flag |= (1 << 3);
                    dp->anim_s = 512;
                }
            } else {
                enPAPAnimeSet(dp, PAPAnime_enGetDamageMotion(dp));
            }
            if ((dp->anim >= 0xE) && (dp->anim < 0x16)) {
                enFlagSetNoDamage(dp);
                enSetNewSize(dp, 300.0f, 250.0f, 200.0f, 250.0f);
                ENEMY_SUB_STEP(2);
            } else {
                ENEMY_SUB_STEP(1);
            }
            enSetHitBack(dp);
            return;
        case 1:
            if ((dp->anim_n == -1) && (dp->hb_s == 0.0f)) {
                if ((dp->type == 1 || enGetMode() >= 3)     && 
                    (dp->last_atk == 2 || dp->last_atk == 1)) {
                    
                    ENEMY_STEP(ENEMY_PAP_STATE_RUSH);
                    return;
                } else ENEMY_STEP(ENEMY_PAP_STATE_CHASE);
                return;
            } else if (!enCheckDamage(dp)) break; // @todo incorrect line numbers >_>
            ENEMY_SUB_STEP(0);
            
            return;
        case 2:
            if (dp->anim_n != -1) break;
            ENEMY_STEP(ENEMY_PAP_STATE_DOWN);
            enFlagResetNoDamage(dp);
            
            return;
        case 3:
            if (enReduceTimer(dp) <= 0) {
                ENEMY_STEP(ENEMY_PAP_STATE_CHASE);
            } else if (enCheckDamage(dp)) {
                ENEMY_SUB_STEP(0);
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlDamage);
#endif


#line 817
static void enPAPCtrlConfuse(EnLOCAL_DATA* dp) {
    if (enCheckDamage()) {
        if (enCheckSpray(dp)) {
            ENEMY_SUB_STEP(0);
        } else {
            ENEMY_STEP(ENEMY_PAP_STATE_DAMAGE);
            return;
        }
    }
    if (dp->sslv == 0) {
        enReduceHP(dp);
        enPAPAnimeSet(dp, PAPAnime_02);
        ENEMY_NEXT_SUB_STEP();
    }
    if (dp->sslv == 1 && dp->anim_n == -1) {
        ENEMY_NEXT_SUB_STEP();
        enSetTimer(dp, 600 - enGetMode() * 90);
    } else if (dp->sslv == 2 && enReduceTimer(dp) <= 0) {
        ENEMY_STEP(0);
    }
}

#ifdef HOLY_CANDLE
static void enPAPCtrlDown(EnLOCAL_DATA* dp) {
    switch (dp->sslv) {
        case 0:
            enFlagSetRotFloor(dp);
            enResetDamage(dp);
            if (dp->type == 0) {
                enFlagSetLieDown(dp);
            }
            enSetNewSize(dp, 300.0f, 250.0f, 200.0f, 250.0f);
            if (enCheckDeath(dp)) {
                if (dp->type == 1) {
                    enSetBlur();
                    dp->flag |= (1 << 3);
                    ENEMY_STEP(8);
                    return;
                } else {   
                    enFlagResetMoved(dp);
                    if (enCheckAimedByHuman(dp) == 0 || enCheckInstantDeath(dp)) {
                        enKillCountUp(dp);
                        enPAPAnimeSet(dp, PAPAnime_27);
                        ENEMY_STEP(ENEMY_PAP_STATE_DYING);
                        return;
                    } else enPAPSetDc(dp);
                    ENEMY_SUB_STEP(4);
                }
                
                return;
            }
            if (dp->type != 1) {
                enPAPSetDownTime(dp);
            } else {
                enSetTimer(dp, 0);
            }
            ENEMY_NEXT_SUB_STEP();
            return;
        case 1:
            if (enCheckDamage(dp)) {
                enAnimePause(dp);
                enReduceHP(dp);
                enSetHitBack(dp);
                if (enCheckInstantDeath(dp)) {
                    enKillCountUp(dp);
                    enPAPAnimeSet(dp, PAPAnime_27);
                    ENEMY_STEP(ENEMY_PAP_STATE_DYING);
                    return;
                }
                ENEMY_SUB_STEP(3);
                enSetTimer(dp, 0x3C);
            return; } else if ((enReduceTimer(dp) <= 0) && (enCheckFinishedByHuman(dp) == 0)) { // @todo!
                if (enGetMode() == 0 &&
                    dp->type != 1) {
                    dp->scp->battle.hp = dp->scp->battle.hp_rate = 0.0f;
                    enKillCountUp(dp);
                    ENEMY_STEP(ENEMY_PAP_STATE_DYING);
                    return;
                }
                
                enPAPAnimeSet(dp, PAPAnime_23);
                enFlagResetRotFloor(dp);
                enFlagResetLieDown(dp);
                enFlagSetNoDamage(dp);
                enSetNewSize(dp, 400.0f, 650.0f, 600.0f, 650.0f);
                enAddHP(dp, 100.0f);
                ENEMY_SUB_STEP(2);
                return; } else if (dp->flag & 0x2000) {
                if (dp->anim == 0x19) {
                    if (200.0f * shRandF() < 100.0f - dp->scp->battle.hp_rate) {
                        enAnimePause(dp);
                        enAddHP(dp, 10.0f);
                        return;
                    }
                } else {
                    if (300.0f * shRandF() < 200.0f + dp->scp->battle.hp_rate) {
                        enPAPAnimeSet(dp, PAPAnime_25);
                        return;
                    }
                    enAddHP(dp, 10.0f);
                    return;
                }
            } 
            break;
        case 2:
            if (dp->anim_n == -1) {
                enResetDamage(dp);
                enFlagResetNoDamage(dp);
                ENEMY_STEP(2);
                return;
            }
            break;
        case 3:
            if (enCheckDamage(dp)) {
                enReduceHP(dp);
                enSetHitBack(dp);
                if (enCheckDeath(dp)) {
                    enFlagResetMoved(dp);
                    if (dp->type == 1) {
                        enSetBlur();
                        dp->flag |= (1 << 3);
                        ENEMY_STEP(ENEMY_PAP_STATE_LAST_MOVE);
                        return;
                    }
                    if (enCheckAimedByHuman(dp) == 0 || enCheckInstantDeath(dp)) {
                        enKillCountUp(dp);
                        enPAPAnimeSet(dp, PAPAnime_27);
                        ENEMY_STEP(ENEMY_PAP_STATE_DYING);
                        return;
                    }
                    enPAPSetDc(dp);
                    ENEMY_SUB_STEP(ENEMY_PAP_STATE_ATTACK);
                    return;
                }
                if (enCheckInstantDeath(dp)) {
                    enKillCountUp(dp);
                    enPAPAnimeSet(dp, PAPAnime_27);
                    ENEMY_STEP(ENEMY_PAP_STATE_DYING);
                    return;
                }
                enSetTimer(dp, 0x3C);
                return;
            }
            if (dp->hb_s == 0.0f && enReduceTimer(dp) <= 0) {
                if ((enGetMode() == 0) && (dp->type != 1)) {
                    dp->scp->battle.hp = dp->scp->battle.hp_rate = 0.0f;
                    enKillCountUp(dp);
                    ENEMY_STEP(11); // ??? is this a de@bug leftover? see enPAPCtrlAutomatic?
                    return;
                }
                if (enCheckFinishedByHuman(dp)) {
                    ENEMY_SUB_STEP(5);
                    return;
                }
                enPAPAnimeSet(dp, PAPAnime_23);
                enAddHP(dp, 50.0f);
                enFlagResetRotFloor(dp);
                enFlagResetLieDown(dp);
                enFlagSetNoDamage(dp);
                enSetNewSize(dp, 400.0f, 650.0f, 600.0f, 650.0f);
                ENEMY_SUB_STEP(2);
            }
            break;
    case 4:
        if (enCheckDamage(dp)) {
            enReduceHP(dp);
            enSetHitBack(dp);
            dp->hb_s *= (float) (dp->pap.dcm - dp->pap.dc) / (float) (dp->pap.dcm + 1);
            if (++dp->pap.dc >= dp->pap.dcm || enCheckInstantDeath(dp)) {
                enKillCountUp(dp);
                enPAPAnimeSet(dp, PAPAnime_27);
                ENEMY_STEP(ENEMY_PAP_STATE_DYING);
                return;
            }
            enSetTimer(dp, 0xC8);
            return;
        }
        if (enReduceTimer(dp) <= 0) {
            enKillCountUp(dp);
            enPAPAnimeSet(dp, PAPAnime_27);
            ENEMY_STEP(ENEMY_PAP_STATE_DYING);
            return;
        }
        break;
    case 5:
        if (enCheckDamage(dp)) {
            enReduceHP(dp);
            enSetHitBack(dp);
            if (enCheckInstantDeath(dp)) {
                enKillCountUp(dp);
                enPAPAnimeSet(dp, PAPAnime_27);
                ENEMY_STEP(ENEMY_PAP_STATE_DYING);
                return;
            }
            enSetTimer(dp, 0x3C);
            dp->sslv = 3;
            return;
        }
        if (enCheckFinishedByHuman(dp) == 0) {
            enPAPAnimeSet(dp, PAPAnime_23);
            enAddHP(dp, 50.0f);
            enFlagResetRotFloor(dp);
            enFlagResetLieDown(dp);
            enFlagSetNoDamage(dp);
            enSetNewSize(dp, 400.0f, 650.0f, 600.0f, 650.0f);
            dp->sslv = 2;
        }
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlDown);
#endif

static void enPAPCtrlLastMove(EnLOCAL_DATA* dp) {
    if (dp->anim_n != -1) return;
    enResetFilter();
    SET_GAME_FLAG(334);
    enPAPAnimeSet(dp, PAPAnime_27);
    ENEMY_STEP(ENEMY_PAP_STATE_DYING);
}

#line 1035
static void enPAPMoveAngle(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec, vec2, tpos; // r29+0x30, r29+0x40, r29+0x50
    float a, d; // r20, r21
    if (dp->anim != 0x1E) {
        d = enPAPGetRotSpeed();
        a = dp->path.markangle;
        shSinCosV_Scale(&vec, a, 300.0f + dp->size);
        shAddVector(vec, &dp->scp->pos, vec);
        shSinCosV_Scale(vec2, QUARTER_TURN + a, dp->size);
        shAddVector(tpos, vec, vec2);
        if (enCheckPath(dp, tpos, &dp->scp->pos) >= 0.0f) {
            a -= d;
        }
        shSubVector(tpos, vec, vec2);
        if (enCheckPath(dp, tpos, &dp->scp->pos) >= 0.0f) {
            a += d;
        }
        dp->path.markangle = shAngleRegulate(a);
    } else {
        d = enPAPGetTurnSpeed(dp) * shSinF(((PI * dp->anim_n) / 2400.0f) / 30.0f);
    }
    
    enMoveAngle(&dp->path, d);
    dp->scp->rot.y = dp->path.angle;
}



#line 1064
static int enPAPCanSeePlayer(EnLOCAL_DATA* dp) {
    float* ppos = enGetPlayerPos(dp); // r2
    float dist, a; // r20, r21
    dist = enCheckPath2(dp, ppos, &dp->scp->pos);
    dp->p_dist = shVectorDistXz(&dp->scp->pos, ppos);
    if (dist >= 0.0f) {
        return 0;
    }
    dist = dp->p_dist;
    if (dist > 2500.0f) return 0;
    a = enCalcDirection(ppos, &dp->scp->pos);
    a = enCalcAngleDifference(a, dp->scp->rot.y);
    if (!enCheckNoDamageHuman(dp) && 
        a < TO_RAD(10)            &&
        dist < ((405.0f + enGetPlayerSize()) - (dp->slv == 3 ? 100.0f : 0.0f))) {
        return 2;
    }
    if (enLocalWork.Status & (1 << 0)) return 0;
    if (a > TO_RAD(10)) return 0;
    return 1;
}


#line 1088
static void enPAPAnimeSet(EnLOCAL_DATA* dp, int anim) {
    if (anim == dp->anim) {
        enAnimeRestart(dp);
        if (anim == 2) {
            enPAPSetMoveCount(dp);
        }
        return;
    }

    FJ_ASSERT_ON_LINE(anim >= 0 && anim < sizeof(EnPAPAnime) / sizeof(EnANIME_DATA), 1097);
    enAnimeSet(dp, anim, EnPAPAnime[anim].Anime);
    if (anim == 2) {
        enPAPSetMoveCount(dp);
    }
    if (anim >= 0xE && anim < 0x1C) {
        dp->flag &= ~(1 << 10);
        return;
    }
    dp->flag |= (1 << 10);
}


















#line 1127
static void enPAPAnimeExec(EnLOCAL_DATA* dp) {
    int of = dp->anim_n; // r16
    enAnimeExec(dp, EnPAPAnime, 5701);
    if (dp->anim == 0x1B) {
        
        enPAPDrawBoad(dp);
    }
    if (dp->anim_n == -1 || dp->flag & (1 << 0)) return;
    if (dp->anim == 11 || dp->anim == 12 || dp->anim == 20 || dp->anim == 21) {

        
        enSetTransWalk(dp);
    } else if (dp->anim == 1) {
        
        enSetTransWalk(dp);
        
        if (
            ((dp->anim_s > 0) && 
                (((of < 4800 ) && (dp->anim_n >= 4800 ))   || 
                 ((of < 38400) && (dp->anim_n >= 38400)))) || 
            ((dp->anim_s < 0) && 
                (((of > 21600) && (dp->anim_n <= 21600))   || 
                 ((of > 55200) && (dp->anim_n <= 55200))))
        ) {
            if (enCheckWater(dp))
                enSoundCall(18808, 1.0f, &dp->scp->pos);
            else if (dp->flag & 0x1000)
                enSoundCall3D(18300, 1.0f, &dp->scp->pos);
            else
                enSoundCall(18300, 1.0f, &dp->scp->pos);
        }

    } else if (dp->anim == 30) {
        if (dp->anim_n < 0xCE41) {
            enFlagSetNoDamage(dp);
            return;
        }
        enFlagResetNoDamage(dp);
    }
}

#ifdef NON_MATCHING
/* @note possible haunting?? */
static void enPAPAutoRecovery(EnLOCAL_DATA* dp) {
    short recover_rate[5] = {
        0,
        10,
        30,
        60,
        100 
    }; // r29+0x20
    enAddEnduranceDT(dp, recover_rate[enGetMode()]);
}
#else
short recover_rate_0x002AA908[5] = {
    0,
    10,
    30,
    60,
    100 
};
INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPAutoRecovery);
#endif


#line 1191
static float enPAPGetWalkSpeed(EnLOCAL_DATA* dp) {
    float speed_rate[5] = {
        0.69999998f,
        0.8f,
        1.0f,
        1.2f,
        1.5f
    }; // r29+0x20
    float r = speed_rate[enGetMode()]; // r29+0x40
    r *= 0.5f + (dp->scp->battle.hp_rate / 200.0f);
    if (dp->type == 1) r *= 0.5f;
    dp->anim_s = (short) (4096.0f * r);
    return r;
}

static float enPAPGetRotSpeed(void) {
    float rot_rate[5] = {
        0.5f,
        0.8f,
        1.0f,
        1.2f,
        1.5f
    }; // r29+0x10
    return TO_RAD(3) * rot_rate[enGetMode()];
}



static float enPAPGetTurnSpeed(EnLOCAL_DATA* dp) {
    float rot_rate[5] = {
        1.0f,
        1.0f,
        1.0f,
        1.5f,
        2.0f
    }; // r29+0x20
    float r = rot_rate[enGetMode()]; // r1
    dp->anim_s = (short) (4096.0f * r);
    return TO_RAD(6) * r;
}



static void enPAPSetDownTime(EnLOCAL_DATA* dp) {
    short down_time[5] = {
        900,
        480,
        360,
        300,
        240
    }; // r29+0x20
    short down_time2[5] = {
        180,
        180,
        120,
        60,
        60
    }; // r29+0x30
    if (dp->type == 0) {
        enSetTimer(dp, down_time[enGetMode()]);
        return;
    }
    enSetTimer(dp, down_time2[enGetMode()]);
}



static void enPAPSetMoveCount(EnLOCAL_DATA* dp) {
    int n; // r2
    n = (int) ((10.0f - (0.4f * (float) enGetMode())) + shSway1f(-4.0f, 0.5f)) << 11;
    enSetAnimeCount(dp, n);
}



static void enPAPSetDc(EnLOCAL_DATA* dp) {
    enSetTimer(dp, 200);
    dp->pap.dc = 0;
    dp->pap.dcm = ((shRandI() >> 10) % (enGetMode() + 5)) + 4;
}


static inline u_long shTransformVectorPackXyz(sceVu0IVECTOR vec, sceVu0FMATRIX mat, sceVu0FVECTOR invec) {
    u_long128 result;
    asm volatile("\
         lqc2         vf4, 0x0(%3)\n\
         lqc2         vf5, 0x0(%2)\n\
         lqc2         vf6, 0x10(%2)\n\
         vmulax.xyzw  ACC, vf5, vf4x\n\
         vmadday.xyzw ACC, vf6, vf4y\n\
         lqc2         vf5, 0x20(%2)\n\
         lqc2         vf6, 0x30(%2)\n\
         vmaddaz.xyzw ACC, vf5, vf4z\n\
         vmaddw.xyzw  vf4, vf6, vf4w\n\
         vdiv         Q, vf0w, vf4w\n\
         vwaitq\n\
         vmulq.xyz    vf4, vf4, Q\n\
         vftoi4.xyw   vf4, vf4\n\
         vftoi0.z     vf4, vf4\n\
         sqc2         vf4, 0x0(%0)\n\
         qmfc2        %1,  vf4\n\
         pexch        t7,  %1\n\
         pextuw       %1,  zero, %1\n\
         pextlw       %1,  %1, t7"
        : "+r"(vec), "=r"(result) : "r"(mat), "r"(invec) : "t7", "f0");
    return result;
}

#ifdef HOLY_CANDLE
static void enPAPDrawBoad(EnLOCAL_DATA* dp) {
    sceVu0FMATRIX pos; // r29+0x40
    sceVu0FVECTOR vec1; // r29+0x80
    sceVu0FVECTOR vec2; // r29+0x90
    sceVu0FMATRIX wsm; // r29+0xA0
    sceVu0IVECTOR iv; // r29+0xE0
    u_long xyz[4]; // r29+0xF0
    int i; // r16
    int cn; // r17
    u_int w; // r18

    sceVu0CopyMatrix(wsm, cam0.world_screen);
    shSinCosV_Scale(vec1, dp->scp->rot.y, 495.0f);
    shSinCosV_Scale(vec2, QUARTER_TURN + dp->scp->rot.y, 195.0f);
    shAddVector(pos[0], &dp->scp->pos, vec1);
    shAddVector(pos[0], pos[0], vec2);
    shAddVector(pos[1], &dp->scp->pos, vec1);
    shSubVector(pos[1], pos[1], vec2);
    shSinCosV_Scale(vec1, dp->scp->rot.y, 315.0f);
    shSubVector(pos[2], &dp->scp->pos, vec1);
    shAddVector(pos[2], pos[2], vec2);
    shSubVector(pos[3], &dp->scp->pos, vec1);
    shSubVector(pos[3], pos[3], vec2);

    for (w = 0, cn = 0, i = 0; i < 4; i++) {
        pos[i][1] -= 10.0f;
        pos[i][3] = 1.0f;
        xyz[i] = shTransformVectorPackXyz(iv, wsm, pos[i]);
        if (iv[3] < 0 || iv[2] < 0 || iv[0] < 0 || iv[1] < 0 || iv[0] > 0xffff || 0xffff < iv[1]) {
            return;
        }
        cn += shScreenClipI(iv);
        if (w < iv[3]) {
            w = iv[3];
        }
    }

    if (cn < 4) {
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 6),
                       GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZ3, SCE_GS_XYZ3, SCE_GS_XYZ2, SCE_GS_XYZ2), 
                       w, 1);
        *spack.pos++ = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 0, 0, 0, 0, 0, 0, 0, 0);
        *spack.pos++ = SCE_GS_SET_RGBAQ(0, 0, 0, 128, 0);
        *spack.pos++ = xyz[0];
        *spack.pos++ = xyz[1];
        *spack.pos++ = xyz[2];
        *spack.pos++ = xyz[3];
        spkCloseGiftag();
    }
}

#line 1321
static void enPAPSoundSigns(EnLOCAL_DATA* dp) {
    int signs; // r3
    if ((dp->pap.count -= shGetDF()) <= 0) {
        dp->pap.count = enCalcTimer(120);
        do {
            signs = (shRandI() >> 20) & 7;
        } while (signs == dp->pap.signs);
        dp->pap.signs = signs;
        enSoundCall(signs + 18305, 0.4f, &dp->scp->pos);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPDrawBoad);
INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPSoundSigns);
#endif

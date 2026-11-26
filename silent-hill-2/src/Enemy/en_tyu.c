#include "sh2_common.h"
#include "SH2_common/sh_vu0.h"

#include "vec.h"

#include "Enemy/en_common.h"
#include "Enemy/en_tyu.h"

#include "Chacter/m3_tyu.h"
#include "Chacter/chara_list.h"

#include "Fog/fog.h"
#include "Font/fj_man.h"
#include "Event/chara_admin.h"

static EnANIME_DATA EnTYUAnime[2] = {
    { TYU_PLAY_ANIM(1), false },
    { TYU_PLAY_ANIM(2), true  },
};

static void enTYUAnimeSet(EnLOCAL_DATA* dp, int anim);
static void enTYUAnimeExec(EnLOCAL_DATA* dp);
static void enTYUCheckWall(EnLOCAL_DATA* dp);
static int enTYUCanSeePlayer(EnLOCAL_DATA* dp);
static void enTYUCheckNearPlayer(EnLOCAL_DATA* dp);
static float enTYUGetSpeed(void);
static void enTYUSoundMove(EnLOCAL_DATA* dp);
static void enTYUCheckUnderWall(EnLOCAL_DATA* dp);
static int enTYUCheckNearWall(EnLOCAL_DATA* dp);
static int enTYUCheckNormal(sceVu0FVECTOR normal);
static int enTYUSetPathV(EnLOCAL_DATA* dp);
static void enTYUSetAttackTime(EnLOCAL_DATA* dp);
static void enTYUSetDownTime(EnLOCAL_DATA* dp);
static void enTYUSetStopTime(EnLOCAL_DATA* dp);
static void enTY2CheckCreateCharacter(EnLOCAL_DATA* dp);
static void enTY3CheckCreateCharacter(EnLOCAL_DATA* dp);
static void enTYUCtrlAutomatic(EnLOCAL_DATA* dp);
static void enTYUCtrlSleep(EnLOCAL_DATA* dp);
static void enTYUCtrlGoPlayable(EnLOCAL_DATA* dp);
static void enTYUCtrlEvent(EnLOCAL_DATA* dp);
static void enTYUCtrlHand(void);
static void enTYUCtrlStraight(EnLOCAL_DATA* dp);
static void enTYUCtrlChase(EnLOCAL_DATA* dp);
static void enTYUCtrlGathering(EnLOCAL_DATA* dp);
static void enTYUCtrlEscape(EnLOCAL_DATA* dp);
static void enTYUCtrlOnWall(EnLOCAL_DATA* dp);
static void enTYUCtrlOnCeiling(EnLOCAL_DATA* dp);
static void enTYUCtrlAttack(EnLOCAL_DATA* dp);
static void enTYUCtrlDown(EnLOCAL_DATA* dp);
static void enTYUCtrlDead(EnLOCAL_DATA* dp);


static void enTY2CtrlFloor(EnLOCAL_DATA* dp);
static void enTY2CtrlWall(EnLOCAL_DATA* dp);
static void enTY2CtrlCeiling(EnLOCAL_DATA* dp);
static void enTY2CtrlDead(EnLOCAL_DATA* dp);
static void enTY2CheckCreateCharacter(EnLOCAL_DATA* dp);

static void enTY3CtrlFloor(EnLOCAL_DATA* dp);
static void enTY3CtrlWall(EnLOCAL_DATA* dp);
static void enTY3CtrlCeiling(EnLOCAL_DATA* dp);
static void enTY3CheckCreateCharacter(EnLOCAL_DATA* dp);

#define ENEMY_TYU_MODE_DUMMY       0
#define ENEMY_TYU_MODE_AUTOMATIC   1
#define ENEMY_TYU_MODE_SLEEP       2
#define ENEMY_TYU_MODE_GO_PLAYABLE 3
#define ENEMY_TYU_MODE_EVENT       4
#define ENEMY_TYU_MODE_HAND        5
#define ENEMY_TYU_MODE_REGENERATE  6

#define ENEMY_TYU_STATE_STRAIGHT   0
#define ENEMY_TYU_STATE_CHASE      1
#define ENEMY_TYU_STATE_GATHERING  2
#define ENEMY_TYU_STATE_ESCAPE     3
#define ENEMY_TYU_STATE_ON_WALL    4
#define ENEMY_TYU_STATE_ON_CEILING 5
#define ENEMY_TYU_STATE_ATTACK     6
#define ENEMY_TYU_STATE_DOWN       7
#define ENEMY_TYU_STATE_DEAD       8

#define ENEMY_TYU_BASE_SPEED       1250.0f
#define ENEMY_TYU_SOUND_START      12200

/* == tyu 2 states == */

#define ENEMY_TYU2_STATE_FLOOR     0
#define ENEMY_TYU2_STATE_WALL      1
#define ENEMY_TYU2_STATE_CEILING   2
#define ENEMY_TYU2_STATE_DEAD      3

/* == tyu 3 states == */

#define ENEMY_TYU3_STATE_FLOOR     0
#define ENEMY_TYU3_STATE_WALL      1
#define ENEMY_TYU3_STATE_CEILING   2

#line 118
void enTYUInitData(EnLOCAL_DATA* dp) {
    float vitarity[5] = {
        1.0f,
        250.0f,
        400.0f,
        600.0f,
        1000.0f
    };
    float endurance[5] = {
        1.0f,
        100.0f,
        150.0f,
        240.0f,
        300.0f
    };
    int mode = enGetMode();

    ENEMY_MLV(ENEMY_TYU_MODE_AUTOMATIC);

    switch (dp->type = dp->scp->en_first_status) {
        case 1:
        case 3:
            ENEMY_STEP(ENEMY_TYU_STATE_ON_WALL);
            break;
        case 4:
            ENEMY_STEP(ENEMY_TYU_STATE_ON_CEILING);
            break;
        case 5:
            ENEMY_STEP(ENEMY_TYU_STATE_DEAD);
            return;
        default:
            ENEMY_STEP(ENEMY_TYU_STATE_STRAIGHT);
            break;
    }

    dp->ins.rot_add[0] = 0.0f;
    enSetSize(dp, 100.0f, 150.0f, 75.0f, 100.0f);
    dp->weight = 1;
    enSetHP(dp, vitarity[mode], endurance[mode]);
    enTYUAnimeSet(dp, 1);
    enFlagSetRotFloor(dp);
    enFlagSetLieDown(dp);
    enFlagSetMoved(dp);
    dp->edb.mark[1] = -1;
    enLocalWork.ActiveEnemy++;
    if (enCheckSleepIn(dp)) {
        enSleepIn(dp);
    }
    dp->flag = 1 << 4;
}

#line 173
void enTYUCtrlMain(EnLOCAL_DATA* dp) {
    void (* enCtrlTYUFunc[7])(EnLOCAL_DATA *) = { 
        enDummyCtrl,
        enTYUCtrlAutomatic,
        enTYUCtrlSleep,
        enTYUCtrlGoPlayable,
        enTYUCtrlEvent,
        enTYUCtrlHand,
        enWaitRegenerate 
    };

    enCtrlTYUFunc[dp->mlv](dp);
}

#line 189
void enTYUCtrlAutomatic(EnLOCAL_DATA* dp) {
    void (* enCtrlTYUSubFunc[9])(EnLOCAL_DATA *) = { 
        enTYUCtrlStraight,
        enTYUCtrlChase,
        enTYUCtrlGathering,
        enTYUCtrlEscape,
        enTYUCtrlOnWall,
        enTYUCtrlOnCeiling,
        enTYUCtrlAttack,
        enTYUCtrlDown,
        enTYUCtrlDead 
    };
    
    enSetBattleTarget(dp, 0);
    
    enCtrlTYUSubFunc[dp->slv](dp);
    
    
    enTYUAnimeExec(dp);
    
    enMoveExec(dp);
    
    if (dp->slv < ENEMY_TYU_STATE_DEAD && enCheckSleepIn(dp)) {
        enSleepIn(dp);
    }
}

#line 218
static void enTYUCtrlSleep(EnLOCAL_DATA* dp) {
    if (enCheckSleepOut(dp)) {
        enSleepOut(dp);
        enFlagSetLieDown(dp);
        enLocalWork.ActiveEnemy++;
        switch (dp->type) {
            case 1:
            case 3:
                ENEMY_STEP(ENEMY_TYU_STATE_ON_WALL);
                return;
            case 4:
                ENEMY_STEP(ENEMY_TYU_STATE_ON_CEILING);
                return;
            default:
                ENEMY_STEP(ENEMY_TYU_STATE_STRAIGHT);
                enFlagSetRotFloor(dp);
                break;
        }
    }
}

#line 241
void enTYUCtrlGoPlayable(EnLOCAL_DATA* dp) {
    ENEMY_MLV(ENEMY_TYU_MODE_AUTOMATIC);
    ENEMY_RESET();
}

#line 248
void enTYUCtrlEvent(EnLOCAL_DATA* dp) {
    /* empty */
}

#line 304
void enTYUCtrlHand(void) {
    /* empty */
}

#line 310
static void enTYUCtrlStraight(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec;
    int t;
    EnCOMMUNICATION* comm;
    if (enCheckDamage()) {
        ENEMY_STEP(ENEMY_TYU_STATE_DOWN);
        return;
    }
    if (dp->sslv == 0) {
        enTYUAnimeSet(dp, 1);
        dp->flag = 1 << 4;
        enFlagSetRotFloor(dp);
        enInitPath(&dp->path, dp->scp->rot.y);
        ENEMY_NEXT_SUB_STEP();
    }
    if (dp->sslv == 2) {
        dp->scp->rot.y = enCalcDirection(dp->tyu.point, ENEMY_POS());
        shSinCosV_Scale(dp->vec, dp->scp->rot.y, enTYUGetSpeed());
        if (shVectorDistXz(dp->tyu.point, ENEMY_POS()) <= 100.0f) {
            dp->scp->pos.y -= 100.0f;
            dp->flag |= 1 << 1;
            dp->type = 3;
            ENEMY_STEP(ENEMY_TYU_STATE_ON_WALL);
        }
        return;
    }
    comm = enCommunicateTribe(3, ENEMY_POS());
    if (comm) {
        dp->tyu.tcomm = comm;
        ENEMY_STEP(ENEMY_TYU_STATE_GATHERING);
        return;
    }
    if (shRandF() < 0.003f) {
        dp->path.angle = shAngleRegulate(dp->path.angle + ((PI * shRandF()) / 3.0f));
    }
    
    shSinCosV_Scale(vec, dp->scp->rot.y, 500.0f);
    shAddVector(vec, ENEMY_POS(), vec);
    if (enSetPath(dp, vec, ENEMY_POS()) && dp->type == 2) {
        CL_VHIT_RESULT* res;
        res = &enLocalWork.HitResult;
        if (res->kind == 1) {
            shVectorCopy(dp->tyu.point, res->hobj.wall.cp);
            ENEMY_SUB_STEP(2);
            return;
        }
    }
    enMoveAngle(&dp->path, TO_RAD(5));
    shSinCosV_Scale(dp->vec, dp->scp->rot.y = dp->path.angle, enTYUGetSpeed());
    t = enTYUCanSeePlayer(dp);
    if (t == 2) {
        ENEMY_STEP(ENEMY_TYU_STATE_ATTACK);
    } else if (t == 1) {
        ENEMY_STEP(ENEMY_TYU_STATE_CHASE);
    }
    
    if (enCheckFinishedByHuman(dp) && dp->p_dist < 200.0f) {
        shVectorZero(dp->vec);
    }
    enTYUCheckNearPlayer(dp);
    enTYUSoundMove(dp);
    enTYUCheckWall(dp);
}

#line 376
void enTYUCtrlChase(EnLOCAL_DATA* dp) {
    int t;
    if (enCheckDamage()) {
        ENEMY_STEP(ENEMY_TYU_STATE_DOWN);
        return;
    }
    if (dp->sslv == 0) {
        enTYUAnimeSet(dp, 1);
        dp->flag = (1 << 4) | (1 << 10);
        enInitPath(&dp->path, enGetPlayerDirection(dp));
        enFlagSetRotFloor(dp);
        ENEMY_NEXT_SUB_STEP();
    }
    
    enSetPath(dp, enGetPlayerPos(dp), ENEMY_POS());
    enMoveAngle(&dp->path, TO_RAD(5));
    
    shSinCosV_Scale(dp->vec, dp->scp->rot.y = dp->path.angle, 
                    enTYUGetSpeed() * enCalcSpeedRate(dp->path.angle, ENEMY_POS(), enGetPlayerPos(dp)));
    t = enTYUCanSeePlayer(dp);
    if (t == 2) {
        ENEMY_STEP(ENEMY_TYU_STATE_ATTACK);
    } else if (t == 0) {
        ENEMY_STEP(ENEMY_TYU_STATE_STRAIGHT);
    }
    if (enCheckFinishedByHuman(dp) && dp->p_dist < 200.0f) {
        shVectorZero(dp->vec);
    }
    enTYUCheckNearPlayer(dp);
    enTYUSoundMove(dp);
    enTYUCheckWall(dp);
}

#line 411
static void enTYUCtrlGathering(EnLOCAL_DATA* dp) {
    int t;
    EnCOMMUNICATION* comm;
    if (enCheckDamage()) {
        ENEMY_STEP(ENEMY_TYU_STATE_DOWN);
        return;
    }
    if ((comm = enCommunicateTribe(3, ENEMY_POS())) != dp->tyu.tcomm) {
        dp->tyu.tcomm = comm;
        if (comm == NULL) {
            ENEMY_STEP(ENEMY_TYU_STATE_STRAIGHT);
            return;
        }
    }
    if (dp->sslv == 0) {
        enTYUAnimeSet(dp, 1);
        enFlagSetRotFloor(dp);
        ENEMY_NEXT_SUB_STEP();
    }
    enSetPath(dp, comm->pos, ENEMY_POS());
    enMoveAngle(&dp->path, TO_RAD(5));
  
    shSinCosV_Scale(dp->vec, dp->scp->rot.y = dp->path.angle, 
                    enTYUGetSpeed() * enCalcSpeedRate(dp->path.angle, ENEMY_POS(), comm->pos));
    t = enTYUCanSeePlayer(dp);
    if (t == 2) {
        ENEMY_STEP(ENEMY_TYU_STATE_ATTACK);
    } else if (t == 1) {
        ENEMY_STEP(ENEMY_TYU_STATE_CHASE);
    }
     if (enCheckFinishedByHuman(dp) && dp->p_dist < 200.0f) {
        shVectorZero(dp->vec);
    }
    enTYUCheckNearPlayer(dp);
    enTYUSoundMove(dp);
    enTYUCheckWall(dp);
}

#line 451
static void enTYUCtrlEscape(EnLOCAL_DATA* dp) {
    int t;
    sceVu0FVECTOR vec;
    CL_VHIT_RESULT* res;
    if (enCheckDamage()) {
        ENEMY_STEP(ENEMY_TYU_STATE_DOWN);
        return;
    }
    if (dp->sslv == 0) {
        enTYUAnimeSet(dp, 1);
        enInitPath(&dp->path, dp->scp->rot.y);
        enFlagSetRotFloor(dp);
        ENEMY_NEXT_SUB_STEP();
    }
    if (dp->p_dist > 500.0f) {
        dp->flag &= ~(1 << 4);
    }
    shSinCosV_Scale(vec, QUARTER_TURN + enGetPlayerDirection(dp), 500.0f);
    shAddVector(vec, ENEMY_POS(), vec);
    if (enSetPath(dp, vec, ENEMY_POS()) && dp->type == 2) {
        CL_VHIT_RESULT* res;
        res = &enLocalWork.HitResult;
        if (res->kind == 1) {
            shVectorCopy(dp->tyu.point, res->hobj.wall.cp);
            ENEMY_STEP(ENEMY_TYU_STATE_STRAIGHT);
            ENEMY_SUB_STEP(2);
            return;
        }
    }
    enMoveAngle(&dp->path, TO_RAD(5));
   
    shSinCosV_Scale(dp->vec, dp->scp->rot.y = dp->path.angle, enTYUGetSpeed());

    if (dp->path.dist < 250.0f && enLocalWork.HitResult.kind == 1) {
        ENEMY_STEP(ENEMY_TYU_STATE_STRAIGHT);
        return;
    }
    if ((t = enTYUCanSeePlayer(dp)) == 0) {
        ENEMY_STEP(ENEMY_TYU_STATE_STRAIGHT);
    }
    
    if (enCheckFinishedByHuman(dp) && dp->p_dist < 200.0f) {
        shVectorZero(dp->vec);
        ENEMY_STEP(ENEMY_TYU_STATE_STRAIGHT);
    }
    enTYUCheckNearPlayer(dp);
    enTYUSoundMove(dp);
    enTYUCheckWall(dp);
}

#line 503
static void enTYUCtrlOnWall(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec;

    if (enCheckDamage()) {
        ENEMY_STEP(ENEMY_TYU_STATE_DOWN);
        ENEMY_SUB_STEP(-1);
        return;
    }
    if (dp->sslv == 0) {
        enTYUAnimeSet(dp, 1);
        if (enTYUCheckNearWall(dp) == 0) {
            if (dp->type == 3) {
                dp->type = 2;
                ENEMY_STEP(ENEMY_TYU_STATE_STRAIGHT);
            }
            return;
        }
        ENEMY_NEXT_SUB_STEP();
    }
    enTYUSetPathV(dp);
    if (dp->path.dist < 250.0f) {
        if (dp->type == 3 && enTYUCheckNormal(enLocalWork.HitResult.hobj.wall.nl)) {
            if (dp->path.dist < 100.0f) {
                dp->scp->rot.y = shAngleRegulate(PI - dp->scp->rot.z);
                dp->trx = 0.0f;
                dp->scp->rot.x = 0.0f;
                dp->trz = 0.0f;
                dp->scp->rot.z = 0.0f;
                dp->flag = (1 << 4) | (1 << 10);
                enFlagSetRotFloor(dp);
                dp->type = 2;
                ENEMY_STEP(ENEMY_TYU_STATE_STRAIGHT);
                shSinCosV_Scale(vec, dp->scp->rot.y, 100.0f);
                shAddVector(ENEMY_POS(), enLocalWork.HitResult.hobj.wall.cp, vec);
                dp->scp->pos.w = 1.0f;
                return;
            }
        } else {
            dp->path.angle = dp->path.markangle;
            if (dp->path.dist < 100.0f) {
                dp->scp->rot.y = dp->path.angle = dp->path.markangle = PI;
            }
        }
    } else {
        enMoveAngle(&dp->path, TO_RAD(5));
    }

    if (dp->scp->pos.y < enGetPlayerPos(dp)[1] - 2000.0f) {
        dp->path.angle = dp->path.markangle = PI;
    }
    dp->scp->rot.y = dp->path.angle;
    enMakeRotVector(dp->vec, (float*) &dp->scp->rot, enTYUGetSpeed());
    enTYUSoundMove(dp);
    enTYUCheckUnderWall(dp);
}


#line 561
void enTYUCtrlOnCeiling(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec;
    if (enCheckDamage()) {
        ENEMY_STEP(ENEMY_TYU_STATE_DOWN);
        ENEMY_SUB_STEP(-1);
        return;
    }
    if (dp->sslv == 0) {
        dp->flag = (1 << 1) | (1 << 4) | (1 << 6) | (1 << 10); // 0b10001010010
        dp->trx = 0.0f;
        dp->scp->rot.x = 0.0f;
        dp->scp->rot.z = dp->trz = PI;
        enInitPath(&dp->path, dp->scp->rot.y);
        ENEMY_NEXT_SUB_STEP();
    }
    if (shRandF() < 0.01f) {
        dp->path.angle = shAngleRegulate(dp->path.angle + ((PI * shRandF()) / 3.0f));
    }
    
    shSinCosV_Scale(vec, dp->path.angle, 500.0f);
    shAddVector(vec, ENEMY_POS(), vec);
    enSetPath(dp, vec, ENEMY_POS());
    
    enMoveAngle(&dp->path, TO_RAD(5));
    shSinCosV_Scale(dp->vec, dp->scp->rot.y = dp->path.angle, enTYUGetSpeed());
    enTYUSoundMove(dp);
    enTYUCheckWall(dp);
}


#line 592
void enTYUCtrlAttack(EnLOCAL_DATA* dp) {
    int t;
    if (enCheckDamage()) {
        ENEMY_STEP(ENEMY_TYU_STATE_DOWN);
        return;
    }
    if (dp->sslv == 0) {
        enTYUSetAttackTime(dp);
        enAttackStart(dp);
        ENEMY_NEXT_SUB_STEP();
    }
    enAttackCheck(dp, 51);
    if (enReduceTimer(dp) <= 0) {
        t = enTYUCanSeePlayer(dp);
        if (t == 2) {
            if (shRandF() < 0.1f) {
                ENEMY_SUB_STEP(0);
            } else {
                ENEMY_STEP(ENEMY_TYU_STATE_ESCAPE);
            }
        } else if (t == 1) {
            ENEMY_STEP(ENEMY_TYU_STATE_CHASE);
        } else {
            ENEMY_STEP(ENEMY_TYU_STATE_STRAIGHT);
        }
    }
    enTYUCheckNearPlayer(dp);
}


#line 623
void enTYUCtrlDown(EnLOCAL_DATA* dp) {
    switch (dp->sslv) {
        case 0:
            if (enCheckSpray(dp)) {
                dp->scp->battle.hp = dp->scp->battle.hp_rate = 0.0f;
            }
            if (enReduceHP(dp) <= 0.0f) {
                enTYUSetDownTime(dp);
            } else {
                enTYUSetStopTime(dp);
            }
            enSetHitBack(dp);
            if (enGetMode() > 0 && !(enLocalWork.Status & (1 << 1))) {
                enSetCommunication(3, 1, ENEMY_POS(), 5000.0f, 180);
            }
            enAnimePause(dp);
            if (enCheckDeath(dp)) {
                if (enGetMode() > 0) {
                    enSetCommunication(3, 1, ENEMY_POS(), 5000.0f, 300);
                }
                if (enCheckInstantDeath(dp)) {
                    enKillCountUp(dp);
                    ENEMY_STEP(ENEMY_TYU_STATE_DEAD);
                } else {
                    enSetTimer(dp, 300);
                    ENEMY_SUB_STEP(2);
                }
            } else {
                ENEMY_NEXT_SUB_STEP();
            }
            break;
        case 1:
            if (enCheckDamage()) {
                enReduceHP(dp);
                if (enCheckDeath(dp)) {
                    if (enGetMode() > 0) {
                        enSetCommunication(3, 1, ENEMY_POS(), 5000.0f, 300);
                    }
                    if (enCheckInstantDeath(dp)) {
                        enKillCountUp(dp);
                        ENEMY_STEP(ENEMY_TYU_STATE_DEAD);
                    } else {
                        enSetTimer(dp, 300);
                        ENEMY_SUB_STEP(2);
                    }
                    break;
                } else {
                    if (dp->endurance <= 0.0f) {
                        enTYUSetDownTime(dp);
                    } else {
                        enTYUSetStopTime(dp);
                    }
                    enSetHitBack(dp);
                }
            }
            if ((enReduceTimer(dp) <= 0) && !enCheckFinishedByHuman(dp)) {
                enAnimeRestart(dp);
                if (dp->endurance <= 0.0f) {
                    enAddHP(dp, 100.0f);
                    ENEMY_STEP(ENEMY_TYU_STATE_ESCAPE);
                } else {
                    ENEMY_STEP(ENEMY_TYU_STATE_CHASE);
                }
            }
            break;
        case 2:
            if (enCheckDamage()) {
                enReduceHP(dp);
                enSetHitBack(dp);
                if (enCheckInstantDeath(dp)) {
                    enKillCountUp(dp);
                    ENEMY_STEP(ENEMY_TYU_STATE_DEAD);
                } else {
                    enSetTimer(dp, 300);
                }
            } else if (enReduceTimer(dp) <= 0) {
                enKillCountUp(dp);
                ENEMY_STEP(ENEMY_TYU_STATE_DEAD);
            }
            break;
        case -1:
            enReduceHP(dp);
            dp->flag = (1 << 1) | (1 << 4) | (1 << 5) | (1 << 10);// 0b10000110010
            dp->trx = QUARTER_TURN;
            dp->trz = PI;
            dp->sslv--;
            /* fallthrough */
        case -2:
            if (enCheckFloor(ENEMY_POS())) {
                CL_VHIT_RESULT* res = &enLocalWork.HitResult;
                
                if (res->hobj.wall.cp[1] > (dp->scp->pos.y - 150.0f)) {
                    dp->flag = (1 << 4) | (1 << 10);
                    enFlagSetRotFloor(dp);
                    dp->trx = 0.0f;
                    dp->scp->rot.x = 0.0f;
                    dp->trz = 0.0f;
                    dp->scp->rot.z = 0.0f;
                    dp->scp->pos.y = res->hobj.wall.cp[1];
                    if (dp->type == 3 || enLocalWork.Status & (1 << 1)) {
                        dp->type = 2;
                    } else {
                        dp->type = 0;
                    }
                    ENEMY_SUB_STEP(0);
                    break;
                }
            }
            dp->vec[1] = 1500.0f;
            break;
    }
    enTYUCheckNearPlayer(dp);
}

extern void fogEraseObj(u_long ID /* r16 */);


#line 741
static void enTYUCtrlDead(EnLOCAL_DATA* dp) {
    if (dp->sslv == 0) {
        enAnimePause(dp);
        enFlagSetDead(dp);
        enFlagResetLieDown(dp);
        enFlagResetMoved(dp);
        fogEraseObj(((int) dp - (int) &enLocalWork) / (int) sizeof(EnLOCAL_DATA) + 10);
        ENEMY_NEXT_SUB_STEP();
        
        if (enLocalWork.Status & (1 << 1)) {
            short id = 0;
            sceVu0FVECTOR pos, rot;
            SubCharacter* t;
            enLocalWork.ActiveEnemy--;
            shVectorCopy(pos, &dp->scp->pos);
            shVectorCopy(rot, &dp->scp->rot);
            t = dp->scp;
            enEfctSetTYU2D((float*) &t->pos, (float*) &t->rot);
        
            enDeleteCharacter(dp);
        }
    }
}

#line 773
static int enTYUSetPathV(EnLOCAL_DATA* dp) {
    EnPATH_DATA* p = &dp->path;
    float dist, ma, a, a1, a2, d1, d2;
    sceVu0FMATRIX rmat;
    sceVu0FVECTOR pos, rot;
    int k;
    shUnitMatrix(rmat);
    shRotMatrixZyx(rmat, rmat, (float*) &dp->scp->rot);
    shVectorZero(rot);
    rot[1] = 60.0f;
    shVectorTransformTo(rot, rmat, rot);
    shSubVector(pos, ENEMY_POS(), rot);
    shVectorCopy(rot, (float*) &dp->scp->rot);
    dist = enCheckForward(dp, pos, rot, 500.0f);
    ma = p->markangle;
    if (dist < 0.0f) {
        p->dist = -dist;
        p->step = 0;
        p->deadend = 0;
        return FALSE;
    }
    p->dist = dist;
    dist += 50.0f;
    switch ((k = p->step)) {
        case 0:
            p->step = 1;
            rot[1] = a1 = TO_RAD(15) + ma;
            d1 = enCheckForward(dp, pos, rot, dist);
            rot[1] = a2 = ma - TO_RAD(15);
            d2 = enCheckForward(dp, pos, rot, dist);
            if (d1 < 0.0f && d2 >= 0.0f) {
                ma = a1;
            } else if ((d1 >= 0.0f) && (d2 < 0.0f)) {
                ma = a2;
            } else {
                if ((d1 >= 0.0f) && (d2 >= 0.0f) && ++p->deadend >= 3) {
                    ma = PI + ma;
                    p->step = -1;
                } else {
                    ma -= TO_RAD(0.1);
                    p->step = 2;
                }
            }
            break;
        case 1:
            a2 = shAngleRegulate(ma - p->angle);
            if (a2 == 0.0f) a2 = TO_RAD(1);
            if (shFloatAbs(a2) < TO_RAD(15)) a1 = ma;
            else a1 = p->angle + (TO_RAD(15) * shFloatSign(a2));
            rot[1] = a1;
            d1 = enCheckForward(dp, pos, rot, dist);
            if (d1 < 0.0f) {
                ma = a1;
                break;
            }
            rot[1] = ma;
            d2 = enCheckForward(dp, pos, rot, dist);
            if (d2 < 0.0f) break;

            #line 833
            if (d1 < d2) {
                a1 = ma;
                d1 = d2;
            }
            a2 = p->angle - (TO_RAD(15) * shFloatSign(a2));
            rot[1] = a2;
            d2 = enCheckForward(dp, pos, rot, dist);
            if (d2 < 0.0f) {
                ma = a2;
            } else if (d1 < 0.0f) {
                ma = a1;
                break;
            } else {       
                ma = a1;
                p->step = 2;
            }
            break;
        case -1:
            ma = p->markangle;
            if (enCalcAngleDifference(ma, p->angle) < TO_RAD(15)) {
                p->deadend = 0;
                p->step = 1;
            }
            break;
        
        default:
            a1 = ma + TO_RAD(15) * k;
            rot[1] = a1;
            d1 = enCheckForward(dp, pos, rot, dist);
            a2 = ma - TO_RAD(15) * k;
            rot[1] = a2;
            d2 = enCheckForward(dp, pos, rot, dist);
            if (d1 < 0.0f) {
                if (d2 < 0.0f) {
                    if (++k >= 6) {
                        ma = a1;
                        k = 1;
                    }
                } else {
                    ma = a1;
                    k = 1;
                }
            } else if (d2 < 0.0f) {
                ma = a2;
                k = 1;
            } else {
                if (d1 > d2) {
                    ma = a1;
                } else {
                    ma = a2;
                }
                if (++k >= 6) {
                    #line 886
                    ma = PI + ma;
                    k = -1;
                }
            }
            p->step = k;
    }
    p->markangle = shAngleRegulate(ma);
    return TRUE;
}

/**
 * returns true if the given vector's upward length is 
 * greater than its horizontal length.
 * if the vector points downward (positive), returns false.
 */
#line 899
static int enTYUCheckNormal(sceVu0FVECTOR normal) {
    float dx, dy = normal[1], dz;
    if (dy >= 0.0f) return FALSE;
    dx = normal[0];
    dz = normal[2];
    return dy * dy > dx * dx + dz * dz;
}

#line 912
static int enTYUCheckNearWall(EnLOCAL_DATA* dp) {
    CL_VHIT_RESULT* res = &enLocalWork.HitResult;
    sceVu0FVECTOR sp, ep, vec, cp;
    float d;
    float r;
    float dm = MAX_FLOAT;
    shSinCosV_Scale(vec, dp->path.angle, 500.0f);
    shSubVector(sp, ENEMY_POS(), vec);
    shAddVector(ep, ENEMY_POS(), vec);
    clCheckHitEyesOnlyWall(res, sp, ep);
    if (res->kind == 1) {
        dm = shVectorDistXz(res->hobj.wall.cp, ENEMY_POS());
        shNormalizeVector(res->hobj.wall.nl, vec);
        shScaleVector(vec, vec, 50.0f);
        shSubVector(cp, res->hobj.wall.cp, vec);
        r = shAtanV(res->hobj.wall.nl);
    }
    sp[0] = dp->scp->pos.x + vec[2];
    sp[2] = dp->scp->pos.z - vec[0];
    ep[0] = dp->scp->pos.x - vec[2];
    ep[2] = dp->scp->pos.z + vec[0];
    clCheckHitEyesOnlyWall(res, sp, ep);
    if (res->kind == 1) {
        d = shVectorDistXz(res->hobj.wall.cp, ENEMY_POS());
        if (d < dm) {
            dm = d;
            shNormalizeVector(res->hobj.wall.nl, vec);
            shScaleVector(vec, vec, 50.0f);
            shSubVector(cp, res->hobj.wall.cp, vec);
            r = shAtanV(res->hobj.wall.nl);
        }
    }
    sp[0] = dp->scp->pos.x - vec[2];
    sp[2] = dp->scp->pos.z + vec[0];
    ep[0] = dp->scp->pos.x + vec[2];
    ep[2] = dp->scp->pos.z - vec[0];
    clCheckHitEyesOnlyWall(res, sp, ep);
    if (res->kind == 1) {
        d = shVectorDistXz(res->hobj.wall.cp, ENEMY_POS());
        if (d < dm) {
            dm = d;
            shNormalizeVector(res->hobj.wall.nl, vec);
            shScaleVector(vec, vec, 50.0f);
            shSubVector(cp, res->hobj.wall.cp, vec);
            r = shAtanV(res->hobj.wall.nl);
        }
    }
    sp[0] = dp->scp->pos.x + vec[0];
    sp[2] = dp->scp->pos.z + vec[2];
    ep[0] = dp->scp->pos.x - vec[0];
    ep[2] = dp->scp->pos.z - vec[2];
    clCheckHitEyesOnlyWall(res, sp, ep);
    if (res->kind == 1) {
        d = shVectorDistXz(res->hobj.wall.cp, ENEMY_POS());
        if (d < dm) {
            dm = d;
            shNormalizeVector(res->hobj.wall.nl, vec);
            shScaleVector(vec, vec, 50.0f);
            shSubVector(cp, res->hobj.wall.cp, vec);
            r = shAtanV(res->hobj.wall.nl);
        }
    }
    if (dm == MAX_FLOAT) return FALSE;
    enFlagResetRotFloorJust(dp);
    dp->flag = (1 << 1) | (1 << 4) | (1 << 5) | (1 << 10);
    shVectorCopyVu0(ENEMY_POS(), cp);
    dp->scp->rot.x = dp->trx = QUARTER_TURN;
    dp->scp->rot.y = 0.0f;
    dp->scp->rot.z = dp->trz = shAngleRegulate(PI - r);
    enInitPath(&dp->path, 0.0f);
    return TRUE;
}


#line 987
static void enTYUCheckWall(EnLOCAL_DATA* dp) {
    CL_VHIT_RESULT* res = &enLocalWork.HitResult;
    sceVu0FVECTOR sp, ep, vec; // 40, 50, 60
    float d;
    shSinCosV_Scale(vec, dp->scp->rot.y, 500.0f);
    shSubVector(sp, ENEMY_POS(), vec);
    shAddVector(ep, ENEMY_POS(), vec);
    if (dp->flag & (1 << 6)) {
        sp[1] += 50.0f;
        ep[1] += 50.0f;
    } else {
        sp[1] -= 50.0f;
        ep[1] -= 50.0f;
    }
    clCheckHitEyesOnlyWall(res, sp, ep);
    if (res->kind == 1) {
        d = shVectorDistXz(res->hobj.wall.cp, sp) - 100.0f;
        if (d < 500.0f) {
            sceVu0FVECTOR tpos;
            float r;
            shNormalizeVector(res->hobj.wall.nl, vec);
            shScaleVector(vec, vec, 100.0f);
            shAddVector(tpos, res->hobj.wall.cp, vec);
            r = shAtanV(res->hobj.wall.nl);
            shVectorCopy(sp, ENEMY_POS());
            if (dp->flag & (1 << 6)) {
                sp[1] += 50.0f;
            } else {
                sp[1] -= 50.0f;
            }
            clCheckHitEyesOnlyWall(res, sp, tpos);
            if (res->kind != 1) {
                shVectorCopyXyz(ENEMY_POS(), tpos);
                shVectorCopy((float*) &dp->scp->b_pos, ENEMY_POS());
                shVectorZero(dp->vec);
                enInitPath(&dp->path, dp->scp->rot.y = r);
            }
        }
    }
}

#line 1031
static void enTYUCheckUnderWall(EnLOCAL_DATA* dp) {
    CL_VHIT_RESULT* res = &enLocalWork.HitResult;
    sceVu0FVECTOR sp, ep, vec;
    
    shSinCosV_Scale(vec, -dp->scp->rot.z, 500.0f);
    shSubVector(sp, ENEMY_POS(), vec);
    shAddVector(ep, ENEMY_POS(), vec);
    clCheckHitEyesOnlyWall(res, sp, ep);
    if (res->kind == 1) {
        shNormalizeVector(res->hobj.wall.nl, vec);
        shScaleVector(vec, vec, 50.0f);
        shSubVector(vec, res->hobj.wall.cp, vec);
        dp->scp->pos.x = vec[0];
        dp->scp->pos.z = vec[2];
        return;
    }
    ENEMY_STEP(ENEMY_TYU_STATE_DOWN);
    ENEMY_SUB_STEP(-1);
}

#line 1054
static int enTYUCanSeePlayer(EnLOCAL_DATA* dp) {
    float dist, a;
    float feel_range[5] = {
        0.0f,
        500.0f,
        600.0f,
        750.0f,
        1000.0f
    };
    if (enGetMode() <= 0) {
        // no bug vision on beginner mode
        return FALSE;
    }
    dist = dp->p_dist;
    a = enCalcAngleDifference(enGetPlayerDirection(dp), dp->scp->rot.y);
    if (dist < 150.0f && a < TO_RAD(60)) {
        return 2;
    }
    if (enLocalWork.Status & (1 << 0)) {
        return FALSE;
    }
    return !(dist > feel_range[enGetMode()]); // @note negation required for match
}

#line 1077
static void enTYUCheckNearPlayer(EnLOCAL_DATA* dp) {
    enCheckNearPlayer(dp, &dp->tyu.near_count, &dp->tyu.dist, 200.0f);
}

#line 1083
static void enTYUAnimeSet(EnLOCAL_DATA* dp, int anim) {
    if (anim == dp->anim) {
        enAnimeRestart(dp);
        return;
    }
    
    FJ_ASSERT_ON_LINE(anim >= 0 && anim < sizeof(EnTYUAnime) / sizeof(EnANIME_DATA), 1089);
    enAnimeSet(dp, anim, EnTYUAnime[anim].Anime);
}

#line 1103
static void enTYUAnimeExec(EnLOCAL_DATA* dp) {
    enAnimeExec(dp, EnTYUAnime, TYU_PLAY_ANIM(1));
}

#line 1109
static float enTYUGetSpeed(void) {
    float speed_rate[5] = { 0.8f, 0.9f, 1.0f, 1.1f, 1.2f };
    return ENEMY_TYU_BASE_SPEED * speed_rate[enGetMode()];
}

#line 1122
static void enTYUSetAttackTime(EnLOCAL_DATA* dp) {
    short attack_time[5] = { 60, 40, 30, 20, 10 };
    enSetTimer(dp, attack_time[enGetMode()]);
}

#line 1135
static void enTYUSetStopTime(EnLOCAL_DATA* dp) {
    short stop_time[5] = { 60, 40, 30, 20, 10 };
    enSetTimer(dp, stop_time[enGetMode()]);
}

#line 1148
static void enTYUSetDownTime(EnLOCAL_DATA* dp) {
    short down_time[5] = { 600, 500, 400, 300, 240 };
    enSetTimer(dp, down_time[enGetMode()]);
}

#line 1161
void enTYUSoundMove(EnLOCAL_DATA* dp) {
    s_char r;
    
    if ((dp->tyu.count -= shGetDF()) <= 0) {
        dp->tyu.count = enCalcTimer(20);
        if (dp->flag & (1 << 12)) {
            do {
                r = shFloatToInt(3.0f * shRandF());
            } while (r == dp->edb.mark[1]);
            enSoundCall(r + ENEMY_TYU_SOUND_START, 0.2f, ENEMY_POS());
            enSoundCall3D(r + ENEMY_TYU_SOUND_START, 0.5f, ENEMY_POS());
        } else {
            do {
                r = shFloatToInt(8.0f * shRandF());
            } while (r == dp->edb.mark[1]);
            enSoundCall(r + ENEMY_TYU_SOUND_START, 0.2f, ENEMY_POS());
        }
        dp->edb.mark[1] = r;
    }
    
}

#line 1189
void enTY2InitData(EnLOCAL_DATA* dp) {
    ENEMY_MLV(1);
    enSetSize(dp, 250.0f, 150.0f, 75.0f, 100.0f);
    dp->weight = 1;
    enSetHP(dp, 1.0f, 1.0f);
    dp->flag = (1 << 4) | (1 << 10);
    switch (dp->scp->en_first_status) {
        case 5:
            ENEMY_STEP(ENEMY_TYU2_STATE_DEAD);
            dp->flag = (1 << 3) | (1 << 10);
            dp->scp->battle.hp = dp->scp->battle.hp_rate = dp->endurance = 0.0f;
            break;
        case 1:
        case 3:
            ENEMY_STEP(ENEMY_TYU2_STATE_WALL);
            break;
        case 4:
            ENEMY_STEP(ENEMY_TYU2_STATE_CEILING);
            break;
        default:
            ENEMY_STEP(ENEMY_TYU2_STATE_FLOOR);
            break;
    }
    enFlagSetRotFloor(dp);
}




#line 1219
void enTY2CtrlMain(EnLOCAL_DATA* dp) {
    void (* enCtrlTY2SubFunc[4])(EnLOCAL_DATA *) = {
        enTY2CtrlFloor,
        enTY2CtrlWall,
        enTY2CtrlCeiling,
        enTY2CtrlDead
    };
    
    enSetBattleTarget(dp, 0);
    
    enCtrlTY2SubFunc[dp->slv](dp);
    
    
    enMoveExec(dp);
}


#line 1237
static void enTY2CtrlFloor(EnLOCAL_DATA* dp) {
    if (enCheckDamage(dp)) {
        enTY2CheckCreateCharacter(dp);
        enResetDamage(dp);
    }
}


#line 1246
static void enTY2CtrlWall(EnLOCAL_DATA* dp) {
    if (dp->sslv == 0) {
        #line 1249
        if (!enTYUCheckNearWall(dp)) return;
        
        
        ENEMY_NEXT_SUB_STEP();
    }
    if (enCheckDamage(dp)) {
        enTY2CheckCreateCharacter(dp);
        enResetDamage(dp);
    }
}


#line 1262
static void enTY2CtrlCeiling(EnLOCAL_DATA* dp) {
    if (dp->sslv == 0) {
        dp->flag = (1 << 1) | (1 << 4) | (1 << 6) | (1 << 10); // 0b10001010010
        dp->scp->rot.x = dp->trx = 0.0f;
        dp->scp->rot.z = dp->trz = PI;
        enInitPath(&dp->path, dp->scp->rot.y);
        ENEMY_NEXT_SUB_STEP();
    }
    if (enCheckDamage(dp)) {
        enTY2CheckCreateCharacter(dp);
        enResetDamage(dp);
    }
}

extern void fogEraseObj(u_long ID);

#line 1279
static void enTY2CtrlDead(EnLOCAL_DATA* dp) {
    if (dp->sslv == 0) {
        enFlagSetDead(dp);
        enFlagResetLieDown(dp);
        enFlagResetMoved(dp);
        fogEraseObj(((int) dp - (int) &enLocalWork) / (int) sizeof(EnLOCAL_DATA) + 10);
        ENEMY_NEXT_SUB_STEP();
    }
}

#define EnKIND_TYU  3
#line 1291
static void enTY2CheckCreateCharacter(EnLOCAL_DATA* dp) {
    SubCharacter* scp;
    EnLOCAL_DATA* tp;
    if (enLocalWork.ActiveEnemy >= 12) {
        int i;
        tp = enLocalWork.Data;
        for (i = 0; i < ENEMY_MAX; i++) { // @bug in the bug code, tp is not incremented! this was not fixed in greatest hits!
            if (tp->kind == EnKIND_TYU) {
                tp->scp->battle.damage = dp->scp->battle.damage;
                tp->scp->battle.id = dp->scp->battle.id;
                tp->scp->battle.shock = dp->scp->battle.shock;
                shVectorCopy(tp->scp->battle.vec, dp->scp->battle.vec);
                return;
            }
        }
        return;
    }
    scp = CharaWorkCreate(EN_TYU_CHARA_KIND, -1, (float*) &dp->scp->pos, (float*) &dp->scp->rot, dp->scp->en_first_status);
    if (scp == NULL) return;
    tp = (EnLOCAL_DATA*) scp->enemy_p;
    tp->slv = ENEMY_TYU_STATE_DOWN;
    switch (tp->type) {
        case 1:
        case 3:
        case 4:
            tp->sslv = -1;
    }
    
    enDeleteCharacter(dp);
}

/* 
pretty much same as ty2? some differences though:
- no dead state
- more HP
- no bugged loop in enTY3CheckCreateCharacter
*/

#line 1328
void enTY3InitData(EnLOCAL_DATA* dp) {
    ENEMY_MLV(1);
    enSetSize(dp, 250.0f, 150.0f, 75.0f, 100.0f);
    dp->weight = 1;
    enSetHP(dp, 8.0f, 8.0f);
    switch (dp->scp->en_first_status) {
        case 1:
        case 3:
            ENEMY_STEP(ENEMY_TYU3_STATE_WALL);
            break;
        case 4:
            ENEMY_STEP(ENEMY_TYU3_STATE_CEILING);
            break;
        default:
            ENEMY_STEP(ENEMY_TYU3_STATE_FLOOR);
            break;
    }
    dp->flag = (1 << 4) | (1 << 10);
    enFlagSetRotFloor(dp);
}

#line 1353
void enTY3CtrlMain(EnLOCAL_DATA* dp) {
    void (* enCtrlTY3SubFunc[3])(EnLOCAL_DATA *) = {
        enTY2CtrlFloor,
        enTY2CtrlWall,
        enTY2CtrlCeiling
    };
    
    enSetBattleTarget(dp, 0);
    
    enCtrlTY3SubFunc[dp->slv](dp);
    
    
    enMoveExec(dp);
}

#line 1370
static void enTY3CtrlFloor(EnLOCAL_DATA* dp) {
    if (enCheckDamage(dp)) {
        enTY3CheckCreateCharacter(dp);
        enResetDamage(dp);
    }
}

#line 1379
static void enTY3CtrlWall(EnLOCAL_DATA* dp) {
    if (dp->sslv == 0) {
        // #line 1249
        if (!enTYUCheckNearWall(dp)) return;
        
        
        ENEMY_NEXT_SUB_STEP();
    }
    if (enCheckDamage(dp)) {
        enTY3CheckCreateCharacter(dp);
        enResetDamage(dp);
    }
}

#line 1395
static void enTY3CtrlCeiling(EnLOCAL_DATA* dp) {

    if (dp->sslv == 0) {
        dp->flag = (1 << 1) | (1 << 4) | (1 << 6) | (1 << 10); // 0b10001010010
        dp->scp->rot.x = dp->trx = 0.0f;
        dp->scp->rot.z = dp->trz = PI;
        enInitPath(&dp->path, dp->scp->rot.y);
        ENEMY_NEXT_SUB_STEP();
    }
    if (enCheckDamage(dp)) {
        enTY3CheckCreateCharacter(dp);
        enResetDamage(dp);
    }
}


#line 1412
static void enTY3CheckCreateCharacter(EnLOCAL_DATA* dp) {
    SubCharacter* scp;
    EnLOCAL_DATA* tp;

    while (dp->endurance) {
        if (enLocalWork.ActiveEnemy >= 12) return;
        scp = CharaWorkCreate(EN_TYU_CHARA_KIND, -1, (float*) &dp->scp->pos, (float*) &dp->scp->rot, dp->scp->en_first_status);
        if (scp == NULL) return;
        tp = (EnLOCAL_DATA*) scp->enemy_p;
        tp->slv = ENEMY_TYU_STATE_DOWN;
        switch (tp->type) {
            case 1:
            case 3:
            case 4:
                tp->sslv = -1;
        }
        
        if ((dp->endurance -= 1.0f) == 0.0f) {
            enDeleteCharacter(dp);
        }
    }
}

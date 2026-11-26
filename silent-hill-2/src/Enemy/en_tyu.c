#include "sh2_common.h"
#include "SH2_common/sh_vu0.h"
#include "vec.h"
#include "Enemy/en_tyu.h"

static void enTYUAnimeSet(EnLOCAL_DATA* dp, int anim);
static void enTYUAnimeExec(EnLOCAL_DATA* dp);
static void enTYUCheckWall(EnLOCAL_DATA* dp);
static int enTYUCanSeePlayer(EnLOCAL_DATA* dp);
static void enTYUCheckNearPlayer(EnLOCAL_DATA* dp);
static float enTYUGetSpeed(void);
static void enTYUSoundMove(EnLOCAL_DATA* dp);
static void enTYUCheckUnderWall(EnLOCAL_DATA* dp);
static int enTYUCheckNearWall(EnLOCAL_DATA* dp);
static int enTYUCheckNormal(float* normal);
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
    }; // r29+0x10

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
    }; // r29+0x10
    
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
    sceVu0FVECTOR vec; // r29+0x20
    int t; // r2
    EnCOMMUNICATION* comm; // r2
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
        dp->scp->rot.y = enCalcDirection(dp->tyu.point, (float*) &dp->scp->pos);
        shSinCosV_Scale(dp->vec, dp->scp->rot.y, enTYUGetSpeed());
        if (shVectorDistXz(dp->tyu.point, (float*) &dp->scp->pos) <= 100.0f) {
            dp->scp->pos.y -= 100.0f;
            dp->flag |= 1 << 1;
            dp->type = 3;
            ENEMY_STEP(ENEMY_TYU_STATE_ON_WALL);
        }
        return;
    }
    comm = enCommunicateTribe(3, (float*) &dp->scp->pos);
    if (comm) {
        dp->tyu.tcomm = comm;
        ENEMY_STEP(ENEMY_TYU_STATE_GATHERING);
        return;
    }
    if (shRandF() < 0.003f) {
        dp->path.angle = shAngleRegulate(dp->path.angle + ((PI * shRandF()) / 3.0f));
    }
    
    shSinCosV_Scale(vec, dp->scp->rot.y, 500.0f);
    shAddVector(vec, (float*) &dp->scp->pos, vec);
    if (enSetPath(dp, vec, (float*) &dp->scp->pos) && dp->type == 2) {
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
    
    enSetPath(dp, enGetPlayerPos(dp), (float*) &dp->scp->pos);
    enMoveAngle(&dp->path, TO_RAD(5));
    
    shSinCosV_Scale(dp->vec, dp->scp->rot.y = dp->path.angle, 
                    enTYUGetSpeed() * enCalcSpeedRate(dp->path.angle, (float*) &dp->scp->pos, enGetPlayerPos(dp)));
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
    int t; // r2
    EnCOMMUNICATION* comm; // r16
    if (enCheckDamage()) {
        ENEMY_STEP(ENEMY_TYU_STATE_DOWN);
        return;
    }
    if ((comm = enCommunicateTribe(3, (float*) &dp->scp->pos)) != dp->tyu.tcomm) {
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
    enSetPath(dp, comm->pos, (float*) &dp->scp->pos.x);
    enMoveAngle(&dp->path, TO_RAD(5));
  
    shSinCosV_Scale(dp->vec, dp->scp->rot.y = dp->path.angle, 
                    enTYUGetSpeed() * enCalcSpeedRate(dp->path.angle, (float*) &dp->scp->pos, comm->pos));
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
    int t; // r2
    sceVu0FVECTOR vec; // r29+0x20
    CL_VHIT_RESULT* res; // r6
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
    shAddVector(vec, (float*) &dp->scp->pos, vec);
    if (enSetPath(dp, vec, (float*) &dp->scp->pos) && dp->type == 2) {
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

/*
    Compile unit: E:\work\sh2(CVS全取得)\src\Enemy\en_tyu.c
    Producer: MW MIPS C Compiler
    Language: C
    Code range: 0x00165D80 -> 0x00166050
*/
// Range: 0x165D80 -> 0x166050
#line 503
static void enTYUCtrlOnWall(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec; // r29+0x20

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
                shAddVector((float*) &dp->scp->pos, enLocalWork.HitResult.hobj.wall.cp, vec);
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
    sceVu0FVECTOR vec; // r29+0x20
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
    shAddVector(vec, (float*) &dp->scp->pos, vec);
    enSetPath(dp, vec, (float*) &dp->scp->pos);
    
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
                enSetCommunication(3, 1, (float*) &dp->scp->pos, 5000.0f, 180);
            }
            enAnimePause(dp);
            if (enCheckDeath(dp)) {
                if (enGetMode() > 0) {
                    enSetCommunication(3, 1, (float*) &dp->scp->pos, 5000.0f, 300);
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
                        enSetCommunication(3, 1, (float*) &dp->scp->pos, 5000.0f, 300);
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
            if (enCheckFloor((float*) &dp->scp->pos)) {
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
            short id = 0; // r2
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



INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTYUSetPathV);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTYUCheckNormal);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTYUCheckNearWall);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTYUCheckWall);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTYUCheckUnderWall);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTYUCanSeePlayer);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTYUCheckNearPlayer);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTYUAnimeSet);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTYUAnimeExec);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTYUGetSpeed);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTYUSetAttackTime);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTYUSetStopTime);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTYUSetDownTime);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTYUSoundMove);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTY2InitData);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTY2CtrlMain);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTY2CtrlFloor);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTY2CtrlWall);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTY2CtrlCeiling);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTY2CtrlDead);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTY2CheckCreateCharacter);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTY3InitData);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTY3CtrlMain);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTY3CtrlFloor);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTY3CtrlWall);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTY3CtrlCeiling);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_tyu", enTY3CheckCreateCharacter);

INCLUDE_RODATA("asm/nonmatchings/Enemy/en_tyu", @1713);

INCLUDE_RODATA("asm/nonmatchings/Enemy/en_tyu", @1714);

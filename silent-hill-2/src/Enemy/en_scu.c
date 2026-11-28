#include "sh2_common.h"
#include "SH2_common/sh_vu0.h"

#include "Chacter/sh2_battle_list.h"

#include "Enemy/en_common.h"

#include "vec.h"

#pragma fast_fptosi on

static void enSCUCtrlAutomatic(EnLOCAL_DATA* dp);
static void enSCUCtrlSleep(EnLOCAL_DATA* dp);
static void enSCUCtrlGoPlayable(EnLOCAL_DATA* dp);
static void enSCUCtrlEvent(EnLOCAL_DATA* dp);
static void enSCUCtrlHand(void);
static void enSCUCtrlWander(EnLOCAL_DATA* dp);
static void enSCUCtrlPrecaution(EnLOCAL_DATA* dp);
static void enSCUCtrlChase(EnLOCAL_DATA* dp);
static void enSCUCtrlBackward(EnLOCAL_DATA* dp);
static void enSCUCtrlAmbush(EnLOCAL_DATA* dp);
static void enSCUCtrlWaitCar(EnLOCAL_DATA* dp);
static void enSCUCtrlCrawl(EnLOCAL_DATA* dp);
static void enSCUCtrlAttack(EnLOCAL_DATA* dp);
static void enSCUCtrlDamage(EnLOCAL_DATA* dp);
static void enSCUCtrlConfuse(EnLOCAL_DATA* dp);
static void enSCUCtrlDown(EnLOCAL_DATA* dp);
static int enSCUCanSeePlayer(EnLOCAL_DATA* dp);
static int enSCUCheckAmbush(EnLOCAL_DATA* dp);
static int enSCUCheckUpper(EnLOCAL_DATA* dp);
static void enSCUAnimeSet(EnLOCAL_DATA* dp, int anim);
static void enSCUAnimeReset(EnLOCAL_DATA* dp, int anim);
static void enSCUAnimeExec(EnLOCAL_DATA* dp);
static void enSCUAutoRecovery(EnLOCAL_DATA* dp);
static float enSCUGetWalkSpeed(EnLOCAL_DATA* dp);
static float enSCUGetCrawlSpeed(EnLOCAL_DATA* dp);
static float enSCUGetFeelRange(void);
static float enSCUGetAttackRange(void);
static float enSCUGetAttackAngle(void);
static float enSCUGetAttackProbability(EnLOCAL_DATA* dp);
static float enSCUGetRepertAttackProbability(void);
static float enSCUGetAttackSpeed(EnLOCAL_DATA* dp);
static float enSCUGetRotSpeed(void);
static float enSCUGetAimingSpeed(void);
static void enSCUSetDownTime(EnLOCAL_DATA* dp);
static float enSCUGetCrawlProbability(void);
static void enSCUSetMoveCount(EnLOCAL_DATA* dp);
static void enSCUSetDc(EnLOCAL_DATA* dp);
static void enSCUSoundLife(EnLOCAL_DATA* dp);
static void enSCUSoundCrawlInit(EnLOCAL_DATA* dp);
static void enSCUSoundCrawl(EnLOCAL_DATA* dp);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUInitData);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUCtrlMain);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUCtrlAutomatic);

static void enSCUCtrlSleep(EnLOCAL_DATA* dp) {
    if (enCheckSleepOut(dp)) {
        enSleepOut(dp);
        enFlagResetLieDown(dp);
        ENEMY_MLV(3);
        if (dp->type & (1 << 3)) {
            enFlagResetMoved(dp);
        }
    }
}

static void enSCUCtrlGoPlayable(EnLOCAL_DATA* dp) {
    ENEMY_MLV(1);
    if (dp->type != -1) {
        if (dp->type & (1 << 4)) {
            ENEMY_STEP(6); 
        } else if (dp->type & (1 << 3)) {
            ENEMY_STEP(5);
        } else {
            ENEMY_STEP(0);
        }
    } else {
        ENEMY_STEP(11);
    } 
}

static void enSCUCtrlEvent(EnLOCAL_DATA* dp) {
    enSCUAnimeExec(dp);
    enMoveExec(dp);
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUCtrlHand);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUCtrlWander);

static void enSCUCtrlPrecaution(EnLOCAL_DATA* dp) {
    int t;
    if (enCheckDamage(dp)) {
        ENEMY_STEP(8);
        return;
    }
    if (dp->sslv == 0) {
        enSCUAnimeReset(dp, 2);
        enInitPath(&dp->path, dp->scp->rot.y);
        ENEMY_NEXT_SUB_STEP();
    }
    if (enSCUCheckAmbush(dp)) {
        ENEMY_STEP(4);
        return;
    }
    if (dp->anim_n == -1) {
        
        t = enSCUCanSeePlayer(dp);
        if (t == 2) {
            ENEMY_STEP(7);
        } else if ((t == 1) && (dp->p_dist > 500.0f)) {
            
            ENEMY_STEP(2);
        } else if (enCommunicateTribe(1, &dp->scp->pos) == NULL) {
            
            if (dp->p_dist > enSCUGetAttackRange()) {
                ENEMY_STEP(0);
            }
        } else {
            enSCUAnimeReset(dp, 2);
        }
    }
    
    enMoveAngleToPlayer(dp, enSCUGetRotSpeed());
    enSCUAutoRecovery(dp);
    enSCUSoundLife(dp);
}


INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUCtrlChase);

static void enSCUCtrlBackward(EnLOCAL_DATA* dp) {
    int t;
    if (enCheckDamage(dp)) {
        ENEMY_STEP(8);
        return;
    }
    if (dp->sslv == 0) {
        enSCUAnimeSet(dp, 1);
        enSCUGetWalkSpeed(dp);
        enAnimeReverse(dp);
        enInitPath(&dp->path, dp->scp->rot.y);
        ENEMY_NEXT_SUB_STEP();
    }
    
    enMoveAngleToPlayer(dp, enSCUGetRotSpeed());
    enSCUAutoRecovery(dp);
    
    t = enSCUCanSeePlayer(dp);
    if ((t == 2) && ((dp->anim_loop >= 2) || (enGetMode() >= 4))) {
       
        ENEMY_STEP(7);
    } else if ((t == 0) && (dp->anim_loop >= 2) && (dp->p_dist > enSCUGetFeelRange())) {
        
        if (enCommunicateTribe(1, &dp->scp->pos) == NULL) {
        
            ENEMY_STEP(0);
        } else {
            ENEMY_STEP(1);
        }
    } else if ((dp->anim_loop >= 3) && (dp->p_dist > 750.0f)) {
        
        ENEMY_STEP(1);
    }
    enSCUSoundLife(dp);
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUCtrlAmbush);

static void enSCUCtrlWaitCar(EnLOCAL_DATA* dp) {
    if (dp->sslv == 0) {
        enSetSize(dp, 250.0f, 200.0f, 100.0f, 200.0f);
        enSCUAnimeSet(dp, 24);
        enFlagSetRotFloor(dp);
        enFlagResetMoved(dp);
        dp->flag |= (1 << 3);
        dp->lie = 0;
        ENEMY_NEXT_SUB_STEP();
    }
    if (dp->p_dist < 2000.0f) {
        dp->scp->rot.y = enGetPlayerDirection(dp);
        enFlagSetMoved(dp);
        dp->flag &= ~(1 << 3);
        dp->type &= ~(1 << 3);
        ENEMY_STEP(6);
    }
}

#line 898
static void enSCUCtrlCrawl(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec; // r29+48
    int t; // r17
    if (enCheckDamage(dp)) {
        if (dp->sslv == 2 || dp->sslv <= 0) {
            enResetDamage(dp);
        } else if (enCheckSpray(dp)) {
            enReduceHP(dp);
            enSCUAnimeSet(dp, 24);
            enSetTimer(dp, 180);
            dp->sslv = 6;
        } else {
            enReduceHP(dp);
            enSCUAnimeSet(dp, 26);
            enSetHitBack(dp);
            if (enCheckInstantDeath(dp)) {
                enKillCountUp(dp);
                ENEMY_STEP(11);
                return;
            }
            dp->sslv = 5;
            enSetTimer(dp, 10);
        }
    }
    switch (dp->sslv) {
        case -1:
            enFlagSetNoDamage(dp);
            enSCUAnimeSet(dp, 29);
            enSetNewSize(dp, 250.0f, 200.0f, 100.0f, 200.0f);
            dp->sslv--;
            break;
        case -2:
            if (dp->anim_n == -1) {
                dp->sslv = 0;
            }
            break;
        case 0:
            enSCUAnimeSet(dp, 28);
            if (!(dp->type & (1 << 4)) && (dp->endurance < dp->endurance_max)) {
                
                enFlagSetLieDown(dp);
            } else {
                enFlagResetLieDown(dp);
            }
            enFlagResetNoDamage(dp);
            enFlagSetRotFloor(dp);
            enInitPath(&dp->path, dp->scp->rot.y);
            shSinCosV_Scale(vec, dp->scp->rot.y + shSway1f(-QUARTER_TURN, 0.5f), 1000.0f);
            
            shAddVector(dp->scu.target, (float*) &dp->scp->pos, vec);
            dp->lie = 0;
            enSCUSoundCrawlInit(dp);
            enSetTimer(dp, (int) (180.0f * (1.0f + shSway1f(-0.5f, 0.5f))));
            dp->flag |= (1 << 9);
            dp->sslv++;
        case 1: /* fallthrough */
            enSCUSoundCrawl(dp);
            if (shVectorDistXz((float*) &dp->scp->pos, dp->scu.target) < 400.0f || shRandF() < 0.002f) {
            
                shSinCosV_Scale(vec, dp->scp->rot.y + shSway1f(-QUARTER_TURN, 0.5f), 1000.0f);
                
                shAddVector(dp->scu.target, (float*) &dp->scp->pos, vec);
            }
            t = enSCUCanSeePlayer(dp);
            if ((enCheckFinishedByHuman(dp)) &&
                (dp->p_dist < 1000.0f)) {
                dp->anim_loop = 0;
                enAnimePause(dp);
                enSetTimer(dp, (int) (180.0f * (1.0f + shSway1f(-0.5f, 0.5f))));
                dp->sslv = 3;
            } else {
                if (enReduceTimer(dp) <= 0) {
                    if (((t == 2 || shRandF() < 0.02f || enSCUCheckAmbush(dp))) && (((dp->type & (1 << 4)) == 0)) && (dp->type != -1) && (enSCUCheckUpper(dp) == 0)) {
                        
                        

                        if (enGetMode() == SH2_BATTLE_LEVEL_BEGINNER) {
                        
                            dp->scp->battle.hp = dp->scp->battle.hp_rate = 0.0f;
                            enKillCountUp(dp);
                            ENEMY_STEP(11);
                            break;
                        }
                        enSCUAnimeSet(dp, 22);
                        enFlagResetRotFloor(dp);
                        enFlagResetLieDown(dp);
                        enFlagSetNoDamage(dp);
                        enSetNewSize(dp, 150.0f, 800.0f, 750.0f, 750.0f);
                        enAddHP(dp, 10.0f);
                        dp->sslv = 2;
                    } else if (shRandF() < 0.1f) {
                        enSCUAnimeSet(dp, 24);
                        enSetTimer(dp, (int) (180.0f * (1.0f + shSway1f(-0.5f, 0.5f))));
                        dp->sslv = 4;
                    } else {
                        dp->anim_loop = 0;
                        enAnimePause(dp);
                        enSetTimer(dp, (int) (180.0f * (1.0f + shSway1f(-0.5f, 0.5f))));
                        dp->sslv = 3;
                        enAddHP(dp, 10.0f);
                    }
                    break;
                }
                if ((dp->type & (1 << 4)) && (dp->p_dist < 2000.0f) &&
                    !enSCUCheckUpper(dp)) {
                    enSCUAnimeSet(dp, 22);
                    dp->type &= ~(1 << 4);
                    enFlagResetRotFloor(dp);
                    enFlagResetLieDown(dp);
                    enFlagSetNoDamage(dp);
                    enSetNewSize(dp, 150.0f, 800.0f, 750.0f, 750.0f);
                    dp->sslv = 2;
                    break;
                }
                    
                if (enSetPath(dp, dp->ins.rot_add, &dp->scp->pos)) {
                    shSinCosV_Scale(vec, dp->path.markangle, 1000.0f);
                    shAddVector(dp->scu.target, (float*) &dp->scp->pos, vec);
                    dp->path.timer = 0;
                }
                
                enMoveAngle(&dp->path, enSCUGetRotSpeed());
                shSinCosV_Scale(dp->vec, dp->scp->rot.y = dp->path.angle, enSCUGetCrawlSpeed(dp));
            }
            break;
        case 2:
            if (dp->anim_n == -1) {
                enResetDamage(dp);
                enFlagResetNoDamage(dp);
                if (enSCUCanSeePlayer(dp) <= 0) {
                    ENEMY_STEP(1);
                } else {
                    ENEMY_STEP(2);
                }
                dp->flag &= ~(1 << 9);
            }
            break;
        case 3:
            if ((enReduceTimer(dp) <= 0) && (enCheckFinishedByHuman(dp) == 0)) {
                t = enSCUCanSeePlayer(dp);
                if (((t == 2 || dp->p_dist < 1000.0f || dp->scp->battle.hp == dp->scp->battle.hp_max)) && 
                    ((dp->type != -1))                               && 
                    !(dp->type & (1 << 4))                           && 
                    (enSCUCheckUpper(dp) == 0)) {
                    #line 1042
                    if (enCheckFinishedByHuman(dp)) break;


                    #line 1046
                    if (enGetMode() == SH2_BATTLE_LEVEL_BEGINNER) {
                    
                        enSCUAnimeSet(dp, 26);
                        dp->scp->battle.hp = dp->scp->battle.hp_rate = 0.0f;
                        enKillCountUp(dp);
                        ENEMY_STEP(11);
                        break;
                    }
                        
                    enSCUAnimeSet(dp, 22);
                    enFlagResetRotFloor(dp);
                    enFlagSetNoDamage(dp);
                    enFlagResetLieDown(dp);
                    enSetNewSize(dp, 150.0f, 800.0f, 750.0f, 750.0f);
                    enAddHP(dp, 10.0f);
                    dp->sslv = 2;
                } else if (shRandF() < 0.1f) {
                    enSCUAnimeSet(dp, 24);
                    enSetTimer(dp, (int) (120.0f * (1.0f + shSway1f(-0.5f, 0.5f))));
                    dp->sslv = 4;
                } else {
                    dp->sslv = 0;
                }
            }
            break;
        case 4:
            if (enReduceTimer(dp) <= 0) {
                enAddHP(dp, 10.0f);
                if (((100.0f * shRandF()) < dp->scp->battle.hp_rate) && 
                    (enCheckFinishedByHuman(dp) == 0)) {
                    dp->sslv = 0;
                } else {
                    enSCUAnimeSet(dp, 26);
                    enSetTimer(dp, (int) (180.0f * (1.0f + shSway1f(-0.5f, 0.5f))));
                    dp->sslv = 3;
                }
            }
            break;
        case 5:
            if (dp->hb_s == 0.0f && enReduceTimer(dp) <= 0) {
                ENEMY_STEP(10);
                dp->flag &= ~(1 << 9);
            }
            break;
        case 6:
            if (enReduceTimer(dp) <= 0) {
                enSCUAnimeSet(dp, 26);
                enSetTimer(dp, (int) (180.0f * (1.0f + shSway1f(-0.5f, 0.5f))));
                dp->sslv = 3;
            }
            break;
    }
    enSCUAutoRecovery(dp);
}

static void enSCUCtrlAttack(EnLOCAL_DATA* dp) {
    if (enCheckDamage(dp)) {
        ENEMY_STEP(8);
        return;
    }
    switch (dp->sslv) {
        case 0:
            if (shRandF() < enSCUGetAttackProbability(dp)) {
                enSCUAnimeReset(dp, 3);
                enSCUGetAttackSpeed(dp);
                enFlagSetCritical(dp);
                enAttackStart(dp);
                ENEMY_NEXT_SUB_STEP();
            } else {
                if (dp->anim == 2) {
                    enSCUSetMoveCount(dp);
                    dp->anim_n = 0;
                } else {
                    enSCUAnimeReset(dp, 2);
                }
                ENEMY_SUB_STEP(2);
            }
            break;
        case 1:
            enMoveAngleToPlayer(dp, enSCUGetAimingSpeed());
            
            enAttackCheck(dp, 36);
            if (dp->anim_n == -1) {
                enFlagResetCritical(dp);
                if ((shRandF() < enSCUGetRepertAttackProbability()) && (enSCUCanSeePlayer(dp) == 2)) {
                    
                   
                    ENEMY_SUB_STEP(0);
                } else
                    if (dp->type & 2) {
                        if ((enGetPlayerDistance(dp) < 750.0f) && (enGetMode() >= SH2_BATTLE_LEVEL_EASY)) {
                            
                            ENEMY_STEP(3);
                        } else {
                            ENEMY_STEP(2);
                        }
                } else {
                    ENEMY_STEP(2);
                }
            }
            
            break;
        case 2:
            enSCUSoundLife(dp);
            if (dp->anim_n == -1) {
                if (dp->type & 2) {
                    if (enGetPlayerDistance(dp) < 750.0f) {
                        ENEMY_SUB_STEP(0);
                    } else {
                        ENEMY_STEP(2);
                    }
                } else {
                    ENEMY_STEP(2);
                }
            }
            break;
    }
    enSCUAutoRecovery(dp);
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUCtrlDamage);

static void enSCUCtrlConfuse(EnLOCAL_DATA* dp) {
    if (enCheckDamage(dp)) {
        if (enCheckSpray(dp)) {
            ENEMY_SUB_STEP(0);
        } else {
            ENEMY_STEP(8);
            return;
        }
    }
    if (dp->sslv == 0) {
        enReduceHP(dp);
        enSCUAnimeSet(dp, 2);
        ENEMY_NEXT_SUB_STEP();
    }
    if ((dp->sslv == 1) && (dp->anim_n == -1)) {
        ENEMY_NEXT_SUB_STEP();
        enSetTimer(dp, 600 - (enGetMode() * 90));
    } else if ((dp->sslv == 2) && (enReduceTimer(dp) <= 0)) {
        ENEMY_STEP(1);
    } 
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUCtrlDown);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUCanSeePlayer);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUCheckAmbush);

static int enSCUCheckUpper(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR pos1; sceVu0FVECTOR pos2;
    shVectorCopy(pos1, &dp->scp->pos);
    shVectorCopy(pos2, &dp->scp->pos);
    pos1[1] -= 1300.0f;
    pos2[1] -= 50.0f;
    if (enCheckHitEyes(dp, pos1, pos2) >= 0.0f) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUAnimeSet);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUAnimeReset);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUAnimeExec);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUAutoRecovery);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUGetWalkSpeed);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUGetCrawlSpeed);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUGetFeelRange);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUGetAttackRange);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUGetAttackAngle);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUGetAttackProbability);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUGetRepertAttackProbability);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUGetAttackSpeed);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUGetRotSpeed);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUGetAimingSpeed);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUSetDownTime);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUGetCrawlProbability);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUSetMoveCount);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUSetDc);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUSoundLife);

static void enSCUSoundCrawlInit(EnLOCAL_DATA* dp) {
    dp->scu.count = 0;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_scu", enSCUSoundCrawl);

INCLUDE_RODATA("asm/nonmatchings/Enemy/en_scu", @2006);

INCLUDE_RODATA("asm/nonmatchings/Enemy/en_scu", @2007);

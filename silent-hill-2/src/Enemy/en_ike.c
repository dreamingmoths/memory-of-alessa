#include "sh2_common.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2dt.h"
#include "Chacter/m3_ike.h"

#include "vec.h"

#include "Enemy/en_common.h"

/* static */ void enIKEAnimeSet(EnLOCAL_DATA* dp, int anim);
/* static */ void enIKEAnimeExec(EnLOCAL_DATA* dp);
/* static */ int enIKECountActive(EnLOCAL_DATA* dp);
/* static */ float enIKEGetMoveSpeed(EnLOCAL_DATA* dp);
/* static */ void enIKESoundSigns(EnLOCAL_DATA* dp);
/* static */ int enIKECanSeePlayer(EnLOCAL_DATA* dp);
/* static */ int enIKECheckOther(EnLOCAL_DATA* dp);
/* static */ void enIKECheckNearPlayer(EnLOCAL_DATA* dp);
/* static */ float* enIKECheckNearOther(EnLOCAL_DATA* dp);
/* static */ int enIKECanSeePlayer2(EnLOCAL_DATA* dp);
/* static */ void enIKESoundSwing(EnLOCAL_DATA* dp);
/* static */ int enIKEGetDamageMotion(EnLOCAL_DATA* dp);
/* static */ void enIKECtrlAutomatic(EnLOCAL_DATA* dp);
/* static */ void enIKECtrlGoPlayable(EnLOCAL_DATA* dp);
/* static */ void enIKECtrlHand(EnLOCAL_DATA* dp);
/* static */ void enIKECtrlWait(EnLOCAL_DATA* dp);
/* static */ void enIKECtrlAppearance(EnLOCAL_DATA* dp);
/* static */ void enIKECtrlMove(EnLOCAL_DATA* dp);
/* static */ void enIKECtrlChase(EnLOCAL_DATA* dp);
/* static */ void enIKECtrlKick(EnLOCAL_DATA* dp);
/* static */ void enIKECtrlSwing(EnLOCAL_DATA* dp);
/* static */ void enIKECtrlAttack(EnLOCAL_DATA* dp);
/* static */ void enIKECtrlAttack2(EnLOCAL_DATA* dp);
/* static */ void enIKECtrlTakePlayer(EnLOCAL_DATA* dp);
/* static */ void enIKECtrlDamage(EnLOCAL_DATA* dp);
/* static */ void enIKECtrlDead(EnLOCAL_DATA* dp);
/* static */ int enIKECheckOther2(EnLOCAL_DATA* dp);

UNLINKED(/* static */ EnANIME_DATA EnIKEAnime[21], {
    { /* .anime = */ IKE_PLAY_ANIM(1), /* .loop = */ false, },
    { /* .anime = */ IKE_PLAY_ANIM(1), /* .loop = */ true,  },
    { /* .anime = */ IKE_PLAY_ANIM(2), /* .loop = */ false, },
    { /* .anime = */ IKE_PLAY_ANIM(3), /* .loop = */ false, },
    { /* .anime = */ IKE_PLAY_ANIM(5), /* .loop = */ true,  },
    { /* .anime = */ IKE_PLAY_ANIM(6), /* .loop = */ false, },
    { /* .anime = */ IKE_PLAY_ANIM(4), /* .loop = */ false, },
    { /* .anime = */ IKE_PLAY_ANIM(19), /* .loop = */ false, },
    { /* .anime = */ IKE_PLAY_ANIM(7), /* .loop = */ false, },
    { /* .anime = */ IKE_PLAY_ANIM(8), /* .loop = */ false, },
    { /* .anime = */ IKE_PLAY_ANIM(9), /* .loop = */ false, },
    { /* .anime = */ IKE_PLAY_ANIM(10), /* .loop = */ false, },
    { /* .anime = */ IKE_PLAY_ANIM(11), /* .loop = */ false, },
    { /* .anime = */ IKE_PLAY_ANIM(12), /* .loop = */ false, },
    { /* .anime = */ IKE_PLAY_ANIM(13), /* .loop = */ false, },
    { /* .anime = */ IKE_PLAY_ANIM(14), /* .loop = */ false, },
    { /* .anime = */ IKE_PLAY_ANIM(15), /* .loop = */ false, },
    { /* .anime = */ IKE_PLAY_ANIM(16), /* .loop = */ false, },
    { /* .anime = */ IKE_PLAY_ANIM(17), /* .loop = */ false, },
    { /* .anime = */ IKE_PLAY_ANIM(18), /* .loop = */ false, },
    { /* .anime = */ IKE_PLAY_ANIM(20), /* .loop = */ false, }
});

UNLINKED(/* static */ sceVu0FVECTOR appearance_point[7], {
    { -141100.0f, -3000.0f, -20400.0f, QUARTER_TURN  },
    { -141100.0f, -3000.0f, -19800.0f, QUARTER_TURN  },
    { -140200.0f, -3000.0f, -18500.0f, PI            },
    { -139600.0f, -3000.0f, -18500.0f, PI            },
    { -138900.0f, -3000.0f, -19600.0f, -QUARTER_TURN },
    { -138900.0f, -3000.0f, -20400.0f, -QUARTER_TURN },
    { -140000.0f, -3000.0f, -21500.0f, 0.0f          },
});

#define ENEMY_IKE_MODE_DUMMY         0
#define ENEMY_IKE_MODE_AUTOMATIC     1
#define ENEMY_IKE_MODE_DUMMY2        2
#define ENEMY_IKE_MODE_GO_PLAYABLE   3
#define ENEMY_IKE_MODE_HAND          5

#define ENEMY_IKE_STATE_WAIT         0
#define ENEMY_IKE_STATE_APPEARANCE   1
#define ENEMY_IKE_STATE_MOVE         2
#define ENEMY_IKE_STATE_CHASE        3
#define ENEMY_IKE_STATE_KICK         4
#define ENEMY_IKE_STATE_SWING        5
#define ENEMY_IKE_STATE_ATTACK       6
#define ENEMY_IKE_STATE_ATTACK2      7
#define ENEMY_IKE_STATE_TAKEPLAYER   8
#define ENEMY_IKE_STATE_DAMAGE       9
#define ENEMY_IKE_STATE_DEAD         10

#ifdef HOLY_CANDLE
#line 152
void enIKEInitData(EnLOCAL_DATA* dp) {
    float vitarity[5] = {
        1000.0f,
        1500.0f,
        2000.0f,
        4000.0f,
        5000.0f
    }; // r29+0x30
    int mode = enGetMode(); // r16
    
    ENEMY_MLV(ENEMY_IKE_MODE_AUTOMATIC);
    ENEMY_STEP(ENEMY_IKE_STATE_APPEARANCE);
    enSetBattleTarget(dp, true);
    if (dp->scp->pos.y < -2140.0f)
        ENEMY_STEP(ENEMY_IKE_STATE_WAIT);


    enSetSize(dp, 150.0f, 650.0f, 500.0f, 600.0f);
    dp->weight = 3;
    enSetHP(dp, vitarity[mode], vitarity[mode]);
    
    
    
    dp->flag |= (1 << 6) | (1 << 1);
    enIKEAnimeSet(dp, 1);
    enLocalWork.ActiveEnemy++;
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_ike", enIKEInitData);
#endif


#ifdef NON_MATCHING
#line 184
void enIKECtrlMain(EnLOCAL_DATA* dp) {
    void (*enCtrlIKEFunc[6])(EnLOCAL_DATA*) = { 
        enDummyCtrl,
        enIKECtrlAutomatic,
        enDummyCtrl,
        enIKECtrlGoPlayable,
        enDummyCtrl,
        enIKECtrlHand
    }; // r29+0x10

    enCtrlIKEFunc[dp->mlv](dp);
}


#line 199
/* static */ void enIKECtrlAutomatic(EnLOCAL_DATA* dp) {
    void (*enCtrlIKESubFunc[11])(EnLOCAL_DATA*) = {
        enIKECtrlWait,
        enIKECtrlAppearance,
        enIKECtrlMove,
        enIKECtrlChase,
        enIKECtrlKick,
        enIKECtrlSwing,
        enIKECtrlAttack,
        enIKECtrlAttack2,
        enIKECtrlTakePlayer,
        enIKECtrlDamage,
        enIKECtrlDead
    }; // r29+0x20

    enSetBattleTarget(dp, true);
    
    enCtrlIKESubFunc[dp->slv](dp);
    
    
    enIKEAnimeExec(dp);
    
    enMoveExec(dp);
}
#else

INCLUDE_ASM("asm/nonmatchings/Enemy/en_ike", enIKECtrlMain);
INCLUDE_ASM("asm/nonmatchings/Enemy/en_ike", enIKECtrlAutomatic);
#endif


#line 226
/* static */ void enIKECtrlGoPlayable(EnLOCAL_DATA* dp) {
    ENEMY_MLV(ENEMY_IKE_MODE_AUTOMATIC);
    ENEMY_STEP(ENEMY_IKE_MODE_DUMMY2);
}

#line 364
/* static */ void enIKECtrlHand(EnLOCAL_DATA* dp) {
    /* empty */
}

#ifdef HOLY_CANDLE
#line 370
/* static */ void enIKECtrlWait(EnLOCAL_DATA* dp) {
    int i; // r6    
    switch (dp->sslv) {
        case 0:
            enIKEAnimeSet(dp, 1);
            enSetTimer(dp, 10800);
            dp->flag |= (1 << 3);
            enFlagResetDisplay(dp);
            ENEMY_NEXT_SUB_STEP();
            return;

        case 1: {
            int n = enIKECountActive(dp); // r16
            if (n == 0 || enReduceTimer(dp) <= 0) {
                float dm, d; // r1, r29+0x30
                int j; // r7
                float* ppos = enGetPlayerPos(dp); // r2
                
                
                dm = 0.0f;
                for (i = 0; i < sizeof(appearance_point) / sizeof(sceVu0FVECTOR); i++) {
                    EnLOCAL_DATA* tp = enLocalWork.Data; // r8
                    for (j = 0; j < 32; j++, tp++) {
                        if (tp != dp               && 
                            tp->kind == EnKIND_IKE && 
                            shVectorDistXz(&tp->scp->pos, appearance_point[i]) < 1000.0f) {
                            j = -1;
                            break;
                        }
                    }
                    if (j == -1) continue;
                    d = shVectorDistXz(appearance_point[i], ppos);
                    if (d > dm) {
                        dm = d;
                        n = i;
                    }
                }
                shVectorCopyXyz(&dp->scp->pos, appearance_point[n]);
                shVectorCopy(&dp->scp->b_pos, &dp->scp->pos);
                dp->scp->rot.y = appearance_point[n][3];
                ENEMY_STEP(ENEMY_IKE_STATE_APPEARANCE);
                enFlagSetDisplay(dp);
            }
        }
    }
}



#line 419
/* static */ void enIKECtrlAppearance(EnLOCAL_DATA* dp) {
    switch (dp->sslv) {
        case 0:
            if (dp->scp->pos.y >= -1640.0f) {
                ENEMY_STEP(ENEMY_IKE_STATE_MOVE);
                return;
            }
            enIKEAnimeSet(dp, 1);
            dp->flag |= (1 << 3);
            ENEMY_NEXT_SUB_STEP();
        case 1:
            if (dp->scp->pos.y >= -1640.0f) { // wtf??????
                dp->scp->pos.y = -1640.0f;
                enSetTimer(dp, 60);
                enInitPath(&dp->path, dp->scp->rot.y);
                ENEMY_NEXT_SUB_STEP();
            } else {
                dp->vec[1] = 250.0f;
            }
            break;            
        case 2:
            shSinCosV_Scale(dp->vec, dp->scp->rot.y, enIKEGetMoveSpeed(dp));
            if (enReduceTimer(dp) <= 0) {
                dp->flag &= ~(1 << 3);
                ENEMY_STEP(ENEMY_IKE_STATE_MOVE);
            }
    }   
    enIKESoundSigns(dp);
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_ike", enIKECtrlWait);
INCLUDE_ASM("asm/nonmatchings/Enemy/en_ike", enIKECtrlAppearance);
#endif

INCLUDE_ASM("asm/nonmatchings/Enemy/en_ike", enIKECtrlMove);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_ike", enIKECtrlChase);

#line 573
/* static */ void enIKECtrlKick(EnLOCAL_DATA* dp) {
    int t;
    float d;
    float d2;
    if (enCheckDamage()) {
        ENEMY_STEP(ENEMY_IKE_STATE_DAMAGE);
        return;
    }
    if (dp->sslv == 0) {
        enIKEAnimeSet(dp, 1);
        enInitPath(&dp->path, dp->scp->rot.y);
        dp->ike.direc = 0;
        ENEMY_NEXT_SUB_STEP();
    }
    dp->path.markangle = enGetPlayerDirection(dp);
    enMoveAngle(&dp->path, TO_RAD(1));
    d = enGetPlayerDistance(dp);
    d2 = 750.0f - d;
    shSinCosV_Scale(dp->vec, dp->scp->rot.y = dp->path.angle, d2);
    t = enIKECanSeePlayer2(dp);
    if (t == 3) {
        ENEMY_STEP(ENEMY_IKE_STATE_ATTACK2);
    } else if (t == 2) {
        ENEMY_STEP(ENEMY_IKE_STATE_ATTACK);
    } else if (d > 1000.0f) {
        ENEMY_STEP(ENEMY_IKE_STATE_MOVE);
    }
    enIKECheckNearPlayer(dp);
    enIKESoundSigns(dp);    
}

/* static */ void enIKECtrlSwing(EnLOCAL_DATA* dp) {
    int d; // r16
    float a; // r20
    if (enCheckDamage()) {
        ENEMY_STEP(ENEMY_IKE_STATE_DAMAGE);
        return;
    }
    if (dp->sslv == 0) {
        enIKEAnimeSet(dp, 1);
        enInitPath(&dp->path, dp->scp->rot.y);
        dp->ike.direc = (shRandI() >> 10) & 1;
        dp->ike.swing = 0.0f;
        ENEMY_NEXT_SUB_STEP();
    }
    d = dp->ike.direc;
    if (!(dp->sslv & 1)) d ^= 1;
    a = dp->ike.swing = dp->ike.swing + (PI * shGetDT());

    switch (dp->sslv) {
        case 1:
        case 4:
            if (a > QUARTER_TURN) {
                dp->ike.swing -= QUARTER_TURN;
                ENEMY_NEXT_SUB_STEP();
                if (dp->sslv == 2) {
                    enIKESoundSwing(dp);
                } else {
                    a = 0.0f;
                    ENEMY_STEP(ENEMY_IKE_STATE_MOVE);
                }
            }
            a = TO_RAD(10) * shSinF(2.0f * a);
            break;
        case 2:
        case 3:
            if (a > PI) {
                dp->ike.swing -= PI;
                ENEMY_NEXT_SUB_STEP();
                if (dp->sslv == 3) {
                    enIKESoundSwing(dp);
                }
            }
            a = TO_RAD(40) * shSinF(a);
            break;
    }
    if (d != 0) a = -a;
    dp->trx = dp->scp->rot.x = a;
    enIKECheckNearPlayer(dp);
}

/* static */ void enIKECtrlAttack(EnLOCAL_DATA* dp) {
 
    s_char temp_v1; // removing this adds a new float meme ?=????"??"?!?!?!?!??!
    
    if (enCheckDamage()) {
        if (enCheckHuggedPlayer()) {
            enResetDamage(dp);
        } else {
            ENEMY_STEP(ENEMY_IKE_STATE_DAMAGE);
            enSetNewSize(dp, 150.0f, 650.0f, 500.0f, 600.0f); // lmao leaving the goto fixes the memes
            dp->flag &= ~(1 << 15);
            return;
        }
    }
    
    switch (dp->sslv) {
        case 0:
            enIKECheckNearPlayer(dp);
            enIKEAnimeSet(dp, 2);
            enSetNewSize(dp, 150.0f, 600.0f, 400.0f, 600.0f);
            enAttackStart(dp);
            dp->flag |= (1 << 15);
            enFlagSetCritical(dp);
            ENEMY_NEXT_SUB_STEP(); 
            break;
        case 1:
            enIKECheckNearPlayer(dp);
            enAttackCheck(dp, 54);
            if (dp->anim_n == -1) {
                dp->ike.pipe_count = 0;
                if (dp->flag & (1 << 2)) {
                    enIKEAnimeSet(dp, 6);
                    ENEMY_SUB_STEP(4);
                } else {
                    enIKEAnimeSet(dp, 3);
                    ENEMY_NEXT_SUB_STEP();
                }
            }
            break;
        case 2:
            if (dp->anim_n == -1) {
                enIKEAnimeSet(dp, 4);
                enAttackStart(dp);
                enSetTimer(dp, 120);
                dp->flag &= ~(1 << 15);
                ENEMY_NEXT_SUB_STEP();
            }
            break;
        case 3:
            if (enCheckDeadPlayer() == 3) {
                ENEMY_STEP(ENEMY_IKE_STATE_TAKEPLAYER);
            } else {
                enAttackCheckHug(dp, 55);
                if (enReduceTimer(dp) <= 0) {
                    enSoundCall(((shRandI() >> 10) & 1) + 18504, 1.0f, &dp->scp->pos.x);
                    enSetTimer(dp, 120);
                }
                if (!enCheckHuggedPlayer()) {
                    enIKEAnimeSet(dp, 5);
                    ENEMY_NEXT_SUB_STEP();
                }
            }
            break;
        case 4:
            if (dp->anim_n == -1) {
                ENEMY_STEP(ENEMY_IKE_STATE_MOVE);
                dp->flag &= ~(1 << 15);
                enFlagResetCritical(dp);
                enSetNewSize(dp, 150.0f, 650.0f, 500.0f, 600.0f);
            }
            break;
    }
    enIKESoundSigns(dp);
}

#ifdef HOLY_CANDLE
/* static */ void enIKECtrlAttack2(EnLOCAL_DATA* dp) {
    if (enCheckDamage()) {
        ENEMY_STEP(ENEMY_IKE_STATE_DAMAGE);
        enSetNewSize(dp, 150.0f, 650.0f, 500.0f, 600.0f);
        return;
    }

    switch (dp->sslv) {
        case 0:
            enIKEAnimeSet(dp, 7);
            enAttackStart(dp);
            enSetNewSize(dp, 150.0f, 600.0f, 400.0f, 600.0f);
            enFlagSetCritical(dp);
            ENEMY_NEXT_SUB_STEP();

        case 1:
            enAttackCheck(dp, 56);
            if (dp->anim_n == -1) {
                ENEMY_STEP(ENEMY_IKE_STATE_MOVE);
                enSetNewSize(dp, 150.0f, 650.0f, 400.0f, 600.0f);
                enFlagResetCritical(dp);
                dp->ike.pipe_count = 0;
            }
            break;
    }
    enIKECheckNearPlayer(dp);
    enIKESoundSigns(dp);
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_ike", enIKECtrlAttack2);
#endif

#line 762
/* static */ void enIKECtrlTakePlayer(EnLOCAL_DATA* dp) {
    if (dp->sslv == 0) {
        enInitPath(&dp->path, dp->scp->rot.y);
        if (shFloatAbs(dp->scp->rot.y) <= QUARTER_TURN) {
            dp->path.markangle = 0.0f;
        } else {
            dp->path.markangle = PI;
        }
        {
            int i;
            EnLOCAL_DATA* tp = enLocalWork.Data;
            for (i = 0; i < ENEMY_MAX; i++, tp++) {
                if (tp->kind == 7) {
                    tp->weight = 0;
                }
            }
        }
        dp->weight = 4;
        enAnimePause(dp);
        ENEMY_NEXT_SUB_STEP();
    }
    enAttackCheckHug(dp, 55);
    enMoveAngle(&dp->path, TO_RAD(0.5));
    dp->scp->rot.y = dp->path.angle;
    if (dp->sslv == 2) {
        dp->vec[1] = -500.0f;
        if (dp->scp->pos.y < -4000.0f) {
            enSetGameOver();
        }
    } else if (dp->scp->pos.z < -21450.0f) {
            dp->scp->pos.z = -21500.0f;
            ENEMY_NEXT_SUB_STEP();            
    } else {
        dp->vec[2] = -500.0f;
        if (dp->scp->pos.z < -21300.0f) {
            dp->flag |= (1 << 3);
        }
    }       
}

/* static */ void enIKECtrlDamage(EnLOCAL_DATA* dp) {
    if (dp->sslv == 0) {
        if (dp->last_atk == 17) {
            
            dp->scp->battle.damage /= ++dp->ike.pipe_count;
            if (dp->ike.pipe_count > 4) {
                if (dp->ike.pipe_count >= 10) {
                    dp->ike.pipe_count = 0;
                }
                enReduceHP(dp);
                if (!enCheckDeath(dp)) {
                    ENEMY_STEP(ENEMY_IKE_STATE_KICK);
                    return;
                }
            }
        } else {
            dp->ike.pipe_count = 0;
        }
        enReduceHP(dp);
        if (enCheckSpray(dp)) {
            dp->scp->battle.hp = dp->scp->battle.hp_rate = 0.0f;
            ENEMY_STEP(ENEMY_IKE_STATE_DEAD);
            return;
        }
        enIKEAnimeSet(dp, enIKEGetDamageMotion(dp));
        enSetHitBack(dp);
        dp->hb_s *= 0.5f;
        enSetNewSize(dp, 150.0f, 500.0f, 400.0f, 600.0f);
        dp->trz = 0.0f;
        ENEMY_NEXT_SUB_STEP();
    }
    if (enCheckDamage(dp)) {
        enReduceHP(dp);
        enSetHitBack(dp);
        dp->hb_s *= 0.5f;
    }
    if (dp->anim_n == -1) {
        dp->scp->pos.y = -1640.0f;
        enSetNewSize(dp, 150.0f, 650.0f, 500.0f, 600.0f);
        if (enCheckDeath(dp)) {
            enKillCountUp(dp);
            ENEMY_STEP(ENEMY_IKE_STATE_DEAD);
        } else {
            ENEMY_STEP(ENEMY_IKE_STATE_CHASE);
        }
    }
    enIKECheckNearPlayer(dp);
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_ike", enIKECtrlDead);

/* static */ int enIKECountActive(EnLOCAL_DATA* dp) {
    EnLOCAL_DATA* tp = enLocalWork.Data;
    int i;
    int n = 0;
    for (i = 0; i < ENEMY_MAX; i++, tp++) 
        if (tp != dp) 
            if ((tp->kind == EnKIND_IKE) && (tp->slv != ENEMY_IKE_STATE_WAIT) && (tp->slv != ENEMY_IKE_STATE_DEAD)) {
                
                n++;
            
            }               
    return n;    
}

/* static */ int enIKECheckOther(EnLOCAL_DATA* dp) {
    EnLOCAL_DATA* tp = enLocalWork.Data;
    int i;
    for (i = 0; i < ENEMY_MAX; i++, tp++) {
        if (tp != dp) {
            if ((tp->kind == EnKIND_IKE) && (tp->slv != ENEMY_IKE_STATE_DEAD) && (tp->slv != ENEMY_IKE_STATE_DAMAGE)) 
                
                if (enGetPlayerDistance(tp) < 500.0f) return 1;                            
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_ike", enIKECheckOther2);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_ike", enIKECheckNearOther);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_ike", enIKECheckNearPlayer);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_ike", enIKEGetDamageMotion);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_ike", enIKECanSeePlayer);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_ike", enIKECanSeePlayer2);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_ike", enIKEAnimeSet);

/* static */ void enIKEAnimeExec(EnLOCAL_DATA* dp) {
    enAnimeExec(dp, EnIKEAnime, IKE_PLAY_ANIM(1));
}

/* static */ float enIKEGetMoveSpeed(EnLOCAL_DATA* dp) {
    float speed_rate[5] = { 0.5f,
                            0.8f,
                            1.0f,
                            1.2f,
                            1.5f };
    float r;

    r = speed_rate[enGetMode()];
    r *= (0.8f + (dp->scp->battle.hp_rate / 500.0f));
    return 500.0f * r;
}

/* static */ void enIKESoundSwing(EnLOCAL_DATA* dp) {
    
    enSoundCall(((shRandI() >> 20) & 3) + 18508, 1.0f, &dp->scp->pos);

}

/* static */ void enIKESoundSigns(EnLOCAL_DATA* dp) {
    int signs;
    if ((dp->ike.count -= shGetDF()) <= 0) {
        dp->ike.count = enCalcTimer(60);
        do {
            signs = (shRandI() >> 20) % 6;
        } while (signs == dp->ike.signs);
        dp->ike.signs = signs;
        
        enSoundCall(signs + 18512, 1.0f, &dp->scp->pos);
    }

}

INCLUDE_RODATA("asm/nonmatchings/Enemy/en_ike", @1522_0x0038E510);

INCLUDE_RODATA("asm/nonmatchings/Enemy/en_ike", @1562);

INCLUDE_RODATA("asm/nonmatchings/Enemy/en_ike", @1563);

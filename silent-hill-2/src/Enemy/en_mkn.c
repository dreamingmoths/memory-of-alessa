#include "sh2_common.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2dt.h"

#include "vec.h"

#include "Enemy/en_common.h"
#include "Chacter/m3_mkn.h"
#include "Chacter/sh2_battle_list.h"
#include "Font/fj_man.h"

static void enMKNAnimeSet(EnLOCAL_DATA* dp, int anim);
static void enMKNAnimeExec(EnLOCAL_DATA* dp);
static int enMKNCanSeePlayer2(EnLOCAL_DATA* dp);
static void enMKNAnimeReset(EnLOCAL_DATA* dp, int anim);
static void enMKNAutoRecovery(EnLOCAL_DATA* dp);
static int enMKNCanSeePlayer(EnLOCAL_DATA* dp);
static void enMKNSoundLife(EnLOCAL_DATA* dp);
static float enMKNGetWalkSpeed(EnLOCAL_DATA* dp);
static float enMKNGetRotSpeed(void);
static float enMKNGetFeelRange(void);
static float enMKNGetAttackSpeed(EnLOCAL_DATA* dp);
static float enMKNGetAttackProbability(void);
static float enMKNGetRepertAttackProbability(void);
static void enMKNSetDc(EnLOCAL_DATA* dp);
static void enMKNSetDownTime(EnLOCAL_DATA* dp);
static void enMKNCtrlAutomatic(EnLOCAL_DATA* dp);
static void enMKNCtrlSleep(EnLOCAL_DATA* dp);
static void enMKNCtrlGoPlayable(EnLOCAL_DATA* dp);
static void enMKNCtrlEvent(EnLOCAL_DATA* dp);
static void enMKNCtrlHand(void);
static void enMKNCtrlMannequin(EnLOCAL_DATA* dp);
static void enMKNCtrlMannequin2(EnLOCAL_DATA* dp);
static void enMKNCtrlWaitFall(EnLOCAL_DATA* dp);
static void enMKNCtrlWaitJump(EnLOCAL_DATA* dp);
static void enMKNCtrlWander(EnLOCAL_DATA* dp);
static void enMKNCtrlPrecaution(EnLOCAL_DATA* dp);
static void enMKNCtrlChase(EnLOCAL_DATA* dp);
static void enMKNCtrlAround(EnLOCAL_DATA* dp);
static void enMKNCtrlAttack(EnLOCAL_DATA* dp);
static void enMKNCtrlDamage(EnLOCAL_DATA* dp);
static void enMKNCtrlConfuse(EnLOCAL_DATA* dp);
static void enMKNCtrlDown(EnLOCAL_DATA* dp);
static void enMKNSetMoveCount(EnLOCAL_DATA* dp);

#define EN_MKN_ANIME_MAX 32

EnANIME_DATA EnMKNAnime[EN_MKN_ANIME_MAX] = {
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(1),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(2),
        /* .loop = */ true,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(1),
        /* .loop = */ true,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(3),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(4),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(5),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(6),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(7),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(8),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(9),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(10),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(11),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(12),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(5),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(13),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(14),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(15),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(16),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(17),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(18),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(19),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(20),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(22),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(21),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(26),
        /* .loop = */ true,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(25),
        /* .loop = */ true,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(34),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(33),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(29),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(30),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(31),
        /* .loop = */ false,
    },
    {
        /* .anime = */ MANNEQUIN_PLAY_ANIM(32),
        /* .loop = */ false,
    }
};

#define ENEMY_MKN_MODE_DUMMY            0
#define ENEMY_MKN_MODE_AUTOMATIC        1
#define ENEMY_MKN_MODE_SLEEP            2
#define ENEMY_MKN_MODE_GO_PLAYABLE      3
#define ENEMY_MKN_MODE_EVENT            4
#define ENEMY_MKN_MODE_HAND             5
#define ENEMY_MKN_MODE_WATER_REGENERATE 6

#define ENEMY_MKN_STATE_MANNEQUIN       0
#define ENEMY_MKN_STATE_MANNEQUIN2      1
#define ENEMY_MKN_STATE_WAITFALL        2
#define ENEMY_MKN_STATE_WAITJUMP        3
#define ENEMY_MKN_STATE_WANDER          4
#define ENEMY_MKN_STATE_PRECAUTION      5
#define ENEMY_MKN_STATE_CHASE           6
#define ENEMY_MKN_STATE_AROUND          7
#define ENEMY_MKN_STATE_ATTACK          8
#define ENEMY_MKN_STATE_DAMAGE          9
#define ENEMY_MKN_STATE_CONFUSE         10
#define ENEMY_MKN_STATE_DOWN            11
#define ENEMY_MKN_STATE_DYING           12

void enMKNInitData(EnLOCAL_DATA* dp) {
    float vitarity[5] = {
        400.0f,
        400.0f,
        700.0f,
        1500.0f,
        9999.0f
    };
    float endurance[5] = {
        10.0f,
        190.0f,
        285.0f,
        380.0f,
        450.0f
    }; // r29+0x60
    int mode = enGetMode();
    float rate;

    ENEMY_MLV(ENEMY_MKN_MODE_AUTOMATIC);
    ENEMY_RESET();

    enSetBattleTarget(dp, 0);
    shVectorCopy(dp->mkn.stpos, &dp->scp->pos);

    switch (enGetPlace()) {
        case 0:
            dp->type = 0;
            break;
        default:
            dp->type = 4;
            break;
    }

    enSetSize(dp, 150.0f, 800.0f, 750.0f, 750.0f);
    dp->weight = 2;
    enMKNAnimeSet(dp, 1);
    switch (dp->scp->en_first_status) {
        case 1:
            rate = 1.2f;
            break;
        case 2:
            rate = 0.5f;
            break;
        case 4:
            dp->type = 5;
        case 3:
            rate = 0.3f;
            ENEMY_STEP(ENEMY_MKN_STATE_DOWN);
            enMKNAnimeSet(dp, 26);
            enSetSize(dp, 250.0f, 200.0f, 100.0f, 200.0f);
            break;
        case 5:
            ENEMY_STEP(ENEMY_MKN_STATE_DYING);
            enMKNAnimeSet(dp, dp->lie + 26);
            return;
        case 13:
            enMKNAnimeSet(dp, 39);
            ENEMY_STEP(ENEMY_MKN_STATE_DYING);
            rate = 0.0f;
            break;
        case 14:
            enMKNAnimeSet(dp, 31);
            ENEMY_STEP(ENEMY_MKN_STATE_DYING);
            rate = 0.0f;
            break;
        case 10:
            dp->type = 2;
            ENEMY_STEP(ENEMY_MKN_STATE_WAITFALL);
            enMKNAnimeSet(dp, 28);
            dp->flag |= 2;
            dp->lie = 1;
            rate    = 1.0f;
            break;
        case 11:
            dp->type = 3;
            ENEMY_STEP(ENEMY_MKN_STATE_WAITJUMP);
            enMKNAnimeSet(dp, 28);
            dp->flag |= 2;
            dp->lie = 1;
            rate    = 1.0f;
            break;
        case 9:
            dp->type = 6;
            ENEMY_STEP(ENEMY_MKN_STATE_MANNEQUIN2);
            rate = 0.7f;
            break;
        default:
            rate = 1.0f;
    }
    enSetHP(dp, rate * vitarity[mode], rate * endurance[mode]);
    enSetSeeLightStatus(dp, 1500.0f, 2000.0f);
    if (enCheckSleepIn(dp)) {
        enSleepIn(dp);
    }
}

void enMKNCtrlMain(EnLOCAL_DATA* dp) {
    void (*enCtrlMKNFunc[7])(EnLOCAL_DATA*) = {
        enDummyCtrl,
        enMKNCtrlAutomatic,
        enMKNCtrlSleep,
        enMKNCtrlGoPlayable,
        enMKNCtrlEvent,
        enMKNCtrlHand,
        enWaitRegenerate
    };

    enCtrlMKNFunc[dp->mlv](dp);
}

static void enMKNCtrlAutomatic(EnLOCAL_DATA* dp) {
    void (*enCtrlMKNSubFunc[13])(EnLOCAL_DATA*) = {
        enMKNCtrlMannequin,
        enMKNCtrlMannequin2,
        enMKNCtrlWaitFall,
        enMKNCtrlWaitJump,
        enMKNCtrlWander,
        enMKNCtrlPrecaution,
        enMKNCtrlChase,
        enMKNCtrlAround,
        enMKNCtrlAttack,
        enMKNCtrlDamage,
        enMKNCtrlConfuse,
        enMKNCtrlDown,
        enDyingExec
    }; // r29+0x20

    enSetBattleTarget(dp, 0);

    enCtrlMKNSubFunc[dp->slv](dp);

    enMKNAnimeExec(dp);

    enMoveExec(dp);
    if (dp->slv <= ENEMY_MKN_STATE_DOWN &&
        enCheckSleepIn(dp)) {
        enSleepIn(dp);
    }
}

static void enMKNCtrlSleep(EnLOCAL_DATA* dp) {
    if (enCheckSleepOut(dp)) {
        enSleepOut(dp);
        switch (dp->type) {
            case 2:
                enFlagResetMoved(dp);
                ENEMY_STEP(ENEMY_MKN_STATE_WAITFALL);
                break;
            case 3:
                enFlagResetMoved(dp);
                ENEMY_STEP(ENEMY_MKN_STATE_WAITJUMP);
                break;
            case 1:
                ENEMY_STEP(ENEMY_MKN_STATE_WANDER);
                break;
            case 6:
                enFlagResetMoved(dp);
                ENEMY_STEP(ENEMY_MKN_STATE_MANNEQUIN2);
                break;
            default:
                enFlagResetMoved(dp);
                ENEMY_RESET();
        }
    }
}

static void enMKNCtrlGoPlayable(EnLOCAL_DATA* dp) {
    ENEMY_MLV(ENEMY_MKN_MODE_AUTOMATIC);
    ENEMY_STEP(ENEMY_MKN_STATE_WANDER);
}

static void enMKNCtrlEvent(EnLOCAL_DATA* dp) {
    void* tmp = NULL;
    /* empty */
}

static void enMKNCtrlHand(void) {
    /* empty */
}

static void enMKNCtrlMannequin(EnLOCAL_DATA* dp) {
    int t;
    EnANIME_RANGE pose[2] = {{3, 0, 11}, {0, 0, 11}};

    if (enCheckDamage(pose)) {
        enSetNewSize(dp, 150.0f, 800.0f, 750.0f, 750.0f);
        ENEMY_STEP(ENEMY_MKN_STATE_DAMAGE);
        enFlagSetMoved(dp);
        return;
    }

    switch (dp->sslv) {
        case 0:
            t = shFloatToInt(2.0f * shRandF());
            enMKNAnimeSet(dp, pose[t].Anime);
            dp->mkn.frame = shFloatToInt(pose[t].Start + (pose[t].End - pose[t].Start + 1) * shRandF());

            enAnimeSetDirectFrame(dp, dp->anim, EnMKNAnime[dp->anim].Anime, dp->mkn.frame);

            dp->timer = 5;
            ENEMY_NEXT_SUB_STEP();
            break;
        case 1:
            enAnimeFrameSet(dp, dp->mkn.frame);
            if (--dp->timer <= 0) {
                enAnimePause(dp);
                ENEMY_NEXT_SUB_STEP();
            }
            break;
        case 3:
            if (enReduceTimer(dp) <= 0) {
                enSetCommunication(2, 1, &dp->scp->pos, 1000.0f, 2);

                enFlagSetMoved(dp);
                enAnimeRestart(dp);
                enInitPath(&dp->path, dp->scp->rot.y);
                enAttackStart(dp);
                enSetNewSize(dp, 350.0f, 800.0f, 750.0f, 750.0f);
                ENEMY_NEXT_SUB_STEP();
            }
            return;
        case 4:
            enAttackCheck(dp, dp->anim == 3 ? (u_char) 38 : (u_char) 39);
            enMoveAngleToPlayer(dp, TO_RAD(1));
            if (dp->anim_n == -1) {
                enSetNewSize(dp, 150.0f, 800.0f, 750.0f, 750.0f);
                ENEMY_STEP(ENEMY_MKN_STATE_PRECAUTION);
                if (dp->type == 0) {
                    dp->type = 1;
                }
            }
            return;
    }

    t = enMKNCanSeePlayer2(dp);
    if (t == 2) {
        enSetCommunication(2, 1, &dp->scp->pos, 1000.0f, 2);
        ENEMY_STEP(ENEMY_MKN_STATE_ATTACK);
        enFlagSetMoved(dp);
        if (dp->type == 0) {
            dp->type = 1;
            return;
        }
    } else {
        if (t == 1) {
            enSetTimer(dp, 0);
            ENEMY_SUB_STEP(3);
            return;
        }
        if (enCommunicateTribe(2, &dp->scp->pos) != NULL && dp->sslv != 3) {
            enSetTimer(dp, 90);
            ENEMY_SUB_STEP(3);
        }
        return;
    }
}

static void enMKNCtrlMannequin2(EnLOCAL_DATA* dp) {
    switch (dp->sslv) {
        case 0:
            enMKNAnimeSet(dp, 27);
            enSetSize(dp, 250.0f, 200.0f, 100.0f, 200.0f);
            enFlagSetDead(dp);
            ENEMY_NEXT_SUB_STEP();
            break;
        case 1:
            if (dp->type == 7) {
                enMKNAnimeSet(dp, 23);
                enSetNewSize(dp, 150.0f, 800.0f, 750.0f, 750.0f);
                enFlagSetMoved(dp);
                enFlagSetNoDamage(dp);
                enFlagResetDead(dp);
                enSoundCall(shFloatToInt(4.0f * shRandF()) + 12505, 1.0f, &dp->scp->pos);
                switch (enGetPlace()) {
                    case 0:
                        dp->type = 1;
                        break;
                    default:
                        dp->type = 4;
                        break;
                }
                ENEMY_NEXT_SUB_STEP();
            }
            break;
        case 2:
            if (dp->anim_n == -1) {
                enResetDamage(dp);
                enFlagResetNoDamage(dp);
                ENEMY_STEP(ENEMY_MKN_STATE_PRECAUTION);
            }
            break;
    }
}

static void enMKNCtrlWaitFall(EnLOCAL_DATA* dp) {
    float d;
    float* ppos;
    sceVu0FVECTOR pos, vec; 
    if (enCheckDamage()) {
        enReduceHP(dp);
        enSetHitBack(dp);
    }
    switch (dp->sslv) {
        case 0:
            if (enGetPlayerDistance(dp) < 3000.0f) {
                dp->flag |= 1 << 15;
                enMKNAnimeReset(dp, 28);
                enSetNewSize(dp, 250.0f, 200.0f, 100.0f, 200.0f);
                
                d = enGetPlayerPos(dp)[1] - dp->scp->pos.y;
                d = SQRT((0.25f + ((2.0f * (30.0f * (30.0f * d))) / 9800.0f))) - 1.0f;
                dp->anim_s = shFloatToInt(30720.0f / d);
                dp->mkn.fall = 0.0f;
                ENEMY_NEXT_SUB_STEP();
            }
            break;
        case 1:
            ppos = enGetPlayerPos(dp);
            shSinCosV_Scale(vec, enGetPlayerAngle(dp), 1000.0f);
            shAddVector(pos, ppos, vec);
            if (enCheckPlayerHitEyes(dp, pos) >= 0.0f) {
                shSubVector(pos, ppos, vec);
            }
            shSubVector(vec, pos, (float*) &dp->scp->pos);
            if (vec3_length(vec) < 2500.0f) {
                shVectorCopy(dp->vec, vec);
            } else {
                shSinCosV_Scale(dp->vec, shAtanV(&vec), 2500.0f);
            }
            dp->mkn.fall += 9800.0f * shGetDT();
            dp->vec[1] = dp->mkn.fall;
            shVectorCopy(pos, &dp->scp->pos);
            if (pos[1] > ppos[1]) pos[1] = ppos[1];
            if (((ppos[1] - dp->scp->pos.y) < 50.0f) && enCheckFloor(pos)) {
                d = enLocalWork.HitResult.hobj.wall.cp[1];
                if (d > dp->scp->pos.y) break;
                    
                    
                switch (enGetStage()) {
                    case 2:
                        enSoundCall3D(40227, 1.0f, (float*) &dp->scp->pos);
                        break;
                    case 3:
                        enSoundCall3D(40238, 1.0f, (float*) &dp->scp->pos);
                        break;
                }
                
                
                
                
                dp->scp->pos.y = d;
                dp->vec[1] = 0.0f;
                enMKNAnimeSet(dp, 29);
                dp->flag &= ~((1 << 15) | (1 << 1));
                dp->type = 1;
                enFlagSetRotFloor(dp);
                enSetTimer(dp, 30);
                ENEMY_NEXT_SUB_STEP();
                
            } else if (enGetPlayerDistance(dp) < 550.0f) {
                
                dp->scp->pos.x = pos[0];
                dp->scp->pos.z = pos[2];
            }
            break;
        case 2:
            if (dp->anim_n == -1) {
                if (enReduceTimer(dp) > 0) return;
                enMKNAnimeSet(dp, 23);
                enFlagResetRotFloor(dp);
                enFlagSetMoved(dp);
                enSetNewSize(dp, 150.0f, 800.0f, 750.0f, 750.0f);
                enAddHP(dp, 100.0f);
                enFlagSetNoDamage(dp);
                ENEMY_NEXT_SUB_STEP();
            }

            break;
        case 3:
            if (dp->anim_n == -1) {
                enFlagResetNoDamage(dp);
                ENEMY_STEP(ENEMY_MKN_STATE_CHASE);
            }
            break;
    }
}

static void enMKNCtrlWaitJump(EnLOCAL_DATA* dp) {
    float d;
    float* ppos;
    sceVu0FVECTOR pos, vec; 
    if (enCheckDamage()) {
        enReduceHP(dp);
        enSetHitBack(dp);
    }
    switch (dp->sslv) {
        case 0:
            if (enGetPlayerDistance(dp) < 3000.0f) {
                dp->flag |= 1 << 15;
                enMKNAnimeReset(dp, 28);
                enSetNewSize(dp, 250.0f, 200.0f, 100.0f, 200.0f);       
                dp->mkn.fall = -7500.0f;
                ENEMY_NEXT_SUB_STEP();
            }
            break;
        case 1:
            ppos = enGetPlayerPos(dp);
            shSinCosV_Scale(dp->vec, dp->scp->rot.y, 2000.0f);
            d = dp->mkn.fall;
            dp->mkn.fall += 9800.0f * shGetDT();
            if (d < 0.0f) {
                dp->anim_s = 0;
                if (dp->mkn.fall >= 0.0f) {
                    d = enGetPlayerPos(dp)[1] - dp->scp->pos.y;
                    
                    d = SQRT((0.25f + ((2.0f * (30.0f * (30.0f * d))) / 9800.0f))) - 1.0f;
                    dp->anim_s = shFloatToInt(30720.0f / d);
                }
            }
            dp->vec[1] = dp->mkn.fall;
            shVectorCopy(pos, &dp->scp->pos);
            if (pos[1] > ppos[1]) pos[1] = ppos[1];
            if (((ppos[1] - dp->scp->pos.y) < 50.0f) && enCheckFloor(pos)) {
                d = enLocalWork.HitResult.hobj.wall.cp[1];
                if (d <= dp->scp->pos.y) {
                    
                    
                    switch (enGetStage()) {
                        case 2:
                            enSoundCall3D(40227, 1.0f, (float*) &dp->scp->pos);
                            break;
                        case 3:
                            enSoundCall3D(40238, 1.0f, (float*) &dp->scp->pos);
                            break;
                    }
                    
                    
                    
                    
                    dp->scp->pos.y = d;
                    dp->vec[1] = 0.0f;
                    enMKNAnimeSet(dp, 29);
                    dp->flag &= ~((1 << 15) | (1 << 1));
                    dp->type = 1;
                    enFlagSetRotFloor(dp);
                    enSetTimer(dp, 30);
                    ENEMY_NEXT_SUB_STEP();    
                }         
            }
            break;
        case 2:
            if (dp->anim_n == -1) {
                if (enReduceTimer(dp) <= 0) {
                    enMKNAnimeSet(dp, 23);
                    enFlagResetRotFloor(dp);
                    enFlagSetMoved(dp);
                    enSetNewSize(dp, 150.0f, 800.0f, 750.0f, 750.0f);
                    enAddHP(dp, 100.0f);
                    enFlagSetNoDamage(dp);
                    ENEMY_NEXT_SUB_STEP();
                }
            }
            break;
        case 3:
            if (dp->anim_n == -1) {
                enFlagResetNoDamage(dp);
                ENEMY_STEP(ENEMY_MKN_STATE_CHASE);
            }
            break;
    }
}

#line 783
static void enMKNCtrlWander(EnLOCAL_DATA* dp) {
    float d;
    float r;
    int t;
    sceVu0FVECTOR vec;
    if (enCheckDamage()) {
        ENEMY_STEP(ENEMY_MKN_STATE_DAMAGE);
        return;
    }
    switch (dp->sslv) {
        case 0:
            shVectorCopy(dp->mkn.stpos, &dp->scp->pos);
            enMKNAnimeSet(dp, 1);
            enMKNGetWalkSpeed(dp);
            enInitPath(&dp->path, dp->scp->rot.y);
            shSinCosV_Scale(&vec, dp->path.angle, 1500.0f);
            shAddVector(dp->mkn.target, (float*) &dp->scp->pos, vec);
            ENEMY_NEXT_SUB_STEP();
        case 1:
            d = shVectorDistXz(&dp->scp->pos, dp->mkn.stpos);
            if ((dp->type < 2) && d > 5000.0f) {

                shVectorCopy(dp->mkn.target, dp->mkn.stpos);
                ENEMY_SUB_STEP(2);
                enSetTimer(dp, 300);
            } else {
                r = shRandF();
                if ((shVectorDistXz(&dp->scp->pos, dp->mkn.target) < 600.0f) || (r < 0.02f)) {

                    d = dp->scp->rot.y + ((PI * (shRandF() - 0.5f)) / 2.0f);
                    shSinCosV_Scale(vec, d, 1500.0f);
                    shAddVector(dp->mkn.target, (float*) &dp->scp->pos, vec);
                    if ((dp->type < 2) && (shVectorDistXz(dp->mkn.stpos, dp->mkn.target) > 5000.0f)) {

                        d = dp->scp->rot.y + PI * ((shRandI() & 0x8000) ? 1 : -1) / 2.0f;

                        shSinCosV_Scale(&vec, d, 1500.0f);
                        shAddVector(dp->mkn.target, (float*) &dp->scp->pos, vec);
                    }
                } else if (r < 0.021f) {
                    enMKNAnimeSet(dp, 2);
                    ENEMY_SUB_STEP(3);
                }
            }
            break;
        case 2:
            dp->anim_s = shFloatToInt(4096.0f * enMKNGetWalkSpeed(dp) * enCalcSpeedRate(dp->path.angle, &dp->scp->pos, dp->ins.view_rot));

            d = shVectorDistXz(&dp->scp->pos, dp->mkn.stpos);
            if (d < 5000.0f) {
                dp->anim_s = 4096;
                ENEMY_SUB_STEP(1);
            } else if (enReduceTimer(dp) <= 0) {
                dp->anim_s = 4096;
                shVectorCopy(dp->mkn.stpos, &dp->scp->pos);
                ENEMY_SUB_STEP(1);
            } else if (shRandF() < 0.01f) {
                enMKNAnimeSet(dp, 2);
                ENEMY_SUB_STEP(3);
            }
            break;
        case 3:
            if (dp->anim_n == -1) {
                enMKNAnimeSet(dp, 1);
                enMKNGetWalkSpeed(dp);
                ENEMY_SUB_STEP(1);
            }
            break;
    }

    if (enSetPath(dp, dp->ins.rot_add, (float*) &dp->scp->pos)) {

        shSinCosV_Scale(&vec, dp->path.markangle, 1500.0f);
        shAddVector(dp->mkn.target, (float*) &dp->scp->pos, vec);
    }
    enMoveAngle(&dp->path, enMKNGetRotSpeed());
    dp->scp->rot.y = dp->path.angle;
    enMKNAutoRecovery(dp);

    t = enMKNCanSeePlayer(dp);
    if ((t == 2) && (dp->anim_loop)) {
        ENEMY_STEP(ENEMY_MKN_STATE_ATTACK);
    } else if (t == 1) {
        ENEMY_STEP(ENEMY_MKN_STATE_CHASE);
    } else if ((dp->anim_loop) && (dp->p_dist < enMKNGetFeelRange())) {

        ENEMY_STEP(ENEMY_MKN_STATE_PRECAUTION);
    }
    enMKNSoundLife(dp);
}

static void enMKNCtrlPrecaution(EnLOCAL_DATA* dp) {
    int t;
    if (enCheckDamage()) {
        ENEMY_STEP(ENEMY_MKN_STATE_DAMAGE);
        return;
    }
    if (dp->sslv == 0) {
        enMKNAnimeSet(dp, 2);
        ENEMY_NEXT_SUB_STEP();
    }
    if (dp->anim_n == -1) {
        t = enMKNCanSeePlayer(dp);
        if (t == 2) {
            ENEMY_STEP(ENEMY_MKN_STATE_ATTACK);
        } else if ((t == 1) && dp->p_dist > 350.0f) {
            ENEMY_STEP(ENEMY_MKN_STATE_CHASE);
        } else if (dp->p_dist > enMKNGetFeelRange()) {
            ENEMY_STEP(ENEMY_MKN_STATE_WANDER);
        } else {
            enMKNAnimeReset(dp, 2);
        }
    }
    enMoveAngleToPlayer(dp, enMKNGetRotSpeed());
    enMKNAutoRecovery(dp);
    enMKNSoundLife(dp);
}

static void enMKNCtrlChase(EnLOCAL_DATA* dp) {
    int t;
    if (enCheckDamage()) {
        ENEMY_STEP(ENEMY_MKN_STATE_DAMAGE);
        return;
    }
    if (dp->sslv == 0) {
        enMKNAnimeSet(dp, 1);
        ENEMY_NEXT_SUB_STEP();
    }

    enSetPath(dp, enGetPlayerPos(dp), &dp->scp->pos);

    enMoveAngle(&dp->path, enMKNGetRotSpeed());
    dp->scp->rot.y = dp->path.angle;

    dp->anim_s = shFloatToInt(4096.0f * enMKNGetWalkSpeed(dp) * enCalcSpeedRate(dp->scp->rot.y, &dp->scp->pos, enGetPlayerPos(dp)));

    enMKNAutoRecovery(dp);

    t = enMKNCanSeePlayer(dp);
    if ((t == 2) && (dp->anim_loop)) {
        ENEMY_STEP(ENEMY_MKN_STATE_ATTACK);
    } else if ((t == 0) && ((dp->p_dist > enMKNGetFeelRange()) || (enLocalWork.Status & 1))) {

        if ((dp->type >= 2) || (enGetMode() <= SH2_BATTLE_LEVEL_EASY)) {
            ENEMY_STEP(ENEMY_MKN_STATE_WANDER);
        } else {
            ENEMY_STEP(ENEMY_MKN_STATE_AROUND);
        }
    } else if ((dp->p_dist < 350.0f) && (dp->anim_loop)) {

        ENEMY_STEP(ENEMY_MKN_STATE_PRECAUTION);
    }
    enMKNSoundLife(dp);
}

static void enMKNCtrlAround(EnLOCAL_DATA* dp) {
    float a;
    int t;
    sceVu0FVECTOR vec;
    if (enCheckDamage()) {
        ENEMY_STEP(ENEMY_MKN_STATE_DAMAGE);
        return;
    }
    if (dp->sslv == 0) {
        enMKNAnimeSet(dp, 1);
        enMKNGetWalkSpeed(dp);
        ENEMY_NEXT_SUB_STEP();
    }

    a = enGetPlayerAngle(dp);
    if (shAngleRegulate(enGetPlayerDirection(dp) - a) < 0.0f) {
        a += TO_RAD(120);
    } else {
        a -= TO_RAD(120);
    }

    shSinCosV_Scale(&vec, a, 1000.0f);
    shAddVector(vec, enGetPlayerPos(dp), vec);
    enSetPath(dp, vec, &dp->scp->pos);
    if (shFloatAbs(dp->path.dist) < 500.0f) {
        ENEMY_STEP(ENEMY_MKN_STATE_CHASE);
    }

    enMoveAngle(&dp->path, enMKNGetRotSpeed());
    dp->scp->rot.y = dp->path.angle;
    enMKNAutoRecovery(dp);

    if ((enMKNCanSeePlayer(dp) == 2) && (dp->anim_loop)) {
        ENEMY_STEP(ENEMY_MKN_STATE_ATTACK);
    } else {
        if (dp->p_dist < enMKNGetFeelRange()) {
            ENEMY_STEP(ENEMY_MKN_STATE_CHASE);
        } else if ((dp->p_dist > 3500.0f)) {
            ENEMY_STEP(ENEMY_MKN_STATE_WANDER);
        }
    }
    enMKNSoundLife(dp);
}

static void enMKNCtrlAttack(EnLOCAL_DATA* dp) {
    if (enCheckDamage()) {
        ENEMY_STEP(ENEMY_MKN_STATE_DAMAGE);
        return;
    }
    switch (dp->sslv) {
        case 0:
            if (shRandF() < enMKNGetAttackProbability()) {
                if (dp->anim == 3) {
                    enMKNAnimeSet(dp, 4);
                } else if ((dp->anim == 4) || (shRandI() & 0x8000)) {
                    enMKNAnimeSet(dp, 3);
                } else {
                    enMKNAnimeSet(dp, 4);
                }
                enMKNGetAttackSpeed(dp);
            } else {
                enMKNAnimeSet(dp, 2);
                ENEMY_SUB_STEP(2);
                break;
            }
            enAttackStart(dp);
            ENEMY_NEXT_SUB_STEP();
            break;
        
        case 1:
            enAttackCheck(dp, dp->anim == 3 ? (u_char) 38 : (u_char) 39);
            
            if (dp->anim_n == -1) {
                if ((shRandF() < enMKNGetRepertAttackProbability()) &&
                    (enMKNCanSeePlayer(dp) == 2)) {
            
                    ENEMY_SUB_STEP(0);
                } else {
                    ENEMY_STEP(ENEMY_MKN_STATE_CHASE);
                }
                return;
            }
            break;
        case 2:
            enMKNSoundLife(dp);
            if (dp->anim_n == -1) {
                if (enMKNCanSeePlayer(dp) == 2) {
                    ENEMY_SUB_STEP(0);
                } else {
                    ENEMY_STEP(ENEMY_MKN_STATE_CHASE);
                }
            }
            break;
    }

        enMoveAngleToPlayer(dp, enMKNGetRotSpeed());
        enMKNAutoRecovery(dp);
}

static void enMKNCtrlDamage(EnLOCAL_DATA* dp) {
    float d;
    switch (dp->sslv) {
        case 0:
            enSetCommunication(2, 1, (float*) &dp->scp->pos, 1000.0f, 2);
            
            d = enReduceHP(dp);
            if (enCheckSpray(dp)) {
                ENEMY_STEP(ENEMY_MKN_STATE_CONFUSE);
                break;
            }
            if ((d <= 0.0f) || ((d < 100.0f) && (shRandF() > (0.8f + (0.002f * d))))) {
                
                enMKNAnimeSet(dp, enGetDownMotion(dp));
            } else {
                enMKNAnimeReset(dp, enGetDamageMotion(dp));
            }
            if ((dp->anim >= 14) && (dp->anim < 22)) {
                dp->lie = enGetLieDirection(dp->anim);
                enSetNewSize(dp, 400.0f, 200.0f, 100.0f, 200.0f);
                
                ENEMY_SUB_STEP(2);
            } else {
                ENEMY_SUB_STEP(1);
            }
            enSetHitBack(dp);
            break;
        case 1:
            if ((dp->anim_n == -1) && (dp->hb_s == 0.0f)) {
                ENEMY_STEP(ENEMY_MKN_STATE_PRECAUTION);
            } else if (enCheckDamage(dp)) {
                ENEMY_SUB_STEP(0);    
            }
            break;
        case 2:
            if (enCheckDamage(dp)) {
                enReduceHP(dp);
            }
            if (dp->anim_n == -1) {
                ENEMY_STEP(ENEMY_MKN_STATE_DOWN);
                enFlagResetNoDamage(dp);
            }
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_mkn", enMKNCtrlConfuse);

static void enMKNCtrlDown(EnLOCAL_DATA* dp) {
    switch (dp->sslv) {
        case 0:
            enResetDamage(dp);
            enFlagSetRotFloor(dp);
            enFlagSetLieDown(dp);
            enSetNewSize(dp, 250.0f, 200.0f, 100.0f, 200.0f);
            if (enCheckDeath(dp)) {
                enFlagResetMoved(dp);
                if ((enCheckAimedByHuman(dp) == 0) || (enCheckInstantDeath(dp))) {
                    enKillCountUp(dp);
                    ENEMY_STEP(ENEMY_MKN_STATE_DYING);
                    return;
                }
                enMKNSetDc(dp);
                ENEMY_SUB_STEP(4);
                return;
            }
            enMKNSetDownTime(dp);
            if ((dp->scp->en_first_status == 3) || (dp->scp->en_first_status == 4)) {
                dp->timer += enCalcTimer(600);
            }
            ENEMY_NEXT_SUB_STEP();
            return;
        case 1:
            if (enCheckDamage(dp)) {
                enMKNAnimeReset(dp, dp->lie + 26);
                enReduceHP(dp);
                enSetHitBack(dp);
                if (enCheckDeath(dp)) {
                    enFlagResetMoved(dp);
                    if ((enCheckAimedByHuman(dp) == 0) || (enCheckInstantDeath(dp))) {
                        enKillCountUp(dp);
                        ENEMY_STEP(ENEMY_MKN_STATE_DYING);
                        return;
                    }
                    enMKNSetDc(dp);
                    ENEMY_SUB_STEP(4);
                    return;
                }
                ENEMY_SUB_STEP(3);
                enSetTimer(dp, 90);
                return;
            }
            if ((enReduceTimer(dp) <= 0) && (enCheckFinishedByHuman(dp) == 0)) {
                if (enGetMode() == SH2_BATTLE_LEVEL_BEGINNER) {
                    dp->scp->battle.hp_rate = 0.0f;
                    dp->scp->battle.hp = 0.0f;
                    enKillCountUp(dp);
                    ENEMY_STEP(ENEMY_MKN_STATE_DYING);
                    return;
                }
                if (dp->type == 5) {
                    dp->timer += enCalcTimer(600);
                    return;
                }
                enMKNAnimeSet(dp, dp->lie + 22);
                enAddHP(dp, 50.0f);
                enFlagResetRotFloor(dp);
                enFlagResetLieDown(dp);
                enFlagSetNoDamage(dp);
                enSetNewSize(dp, 150.0f, 800.0f, 750.0f, 750.0f);
                ENEMY_SUB_STEP(2);
                return;
            }
            if (dp->flag & (1 << 13)) {
                if ((dp->anim >= 24) && (dp->anim < 26)) {
                    if (100.0f * shRandF() > dp->scp->battle.hp_rate) {
                        enMKNAnimeReset(dp, dp->lie + 26);
                        enAddHP(dp, 10.0f);
                        return;
                    }
                } else {
                    if ((200.0f * shRandF()) < (100.0f + dp->scp->battle.hp_rate)) {
                        enMKNAnimeSet(dp, dp->lie + 24);
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
                if (enMKNCanSeePlayer(dp) <= 0) {
                    ENEMY_STEP(ENEMY_MKN_STATE_PRECAUTION);
                    return;
                }
                ENEMY_STEP(ENEMY_MKN_STATE_CHASE);
                return;
            }
            break;
        case 3:
            if (enCheckDamage(dp)) {
                enReduceHP(dp);
                enSetHitBack(dp);
                if (enCheckDeath(dp)) {
                    enFlagResetMoved(dp);
                    if ((enCheckAimedByHuman(dp) == 0) || (enCheckInstantDeath(dp))) {
                        enKillCountUp(dp);
                        ENEMY_STEP(ENEMY_MKN_STATE_DYING);
                        return;
                    }
                    enMKNSetDc(dp);
                    ENEMY_SUB_STEP(4);
                    return;
                }
                if (enCheckInstantDeath(dp)) {
                    enKillCountUp(dp);
                    ENEMY_STEP(ENEMY_MKN_STATE_DYING);
                    return;
                }
                enSetTimer(dp, 90);
                return;
            }
            if (dp->hb_s == 0 && enReduceTimer(dp) <= 0) {
                if (enGetMode() == SH2_BATTLE_LEVEL_BEGINNER) {
                    dp->scp->battle.hp_rate = 0.0f;
                    dp->scp->battle.hp = 0.0f;
                    enKillCountUp(dp);
                    ENEMY_STEP(ENEMY_MKN_STATE_DYING);
                    return;
                }
                if (dp->type == 5) {
                    enSetTimer(dp, 600);
                    ENEMY_SUB_STEP(1);
                    return;
                }
                if (enCheckFinishedByHuman(dp)) {
                    ENEMY_SUB_STEP(5);
                    return;
                }
                enMKNAnimeSet(dp, dp->lie + 22);
                enAddHP(dp, 50.0f);
                enFlagResetRotFloor(dp);
                enFlagResetLieDown(dp);
                enFlagSetNoDamage(dp);
                enSetNewSize(dp, 150.0f, 800.0f, 750.0f, 750.0f);
                ENEMY_SUB_STEP(2);
                return;
            }
            break;
        case 4:
            if (enCheckDamage(dp)) {
                enReduceHP(dp);
                enSetHitBack(dp);
                dp->hb_s *= shIntToFloat(dp->mkn.dcm - dp->mkn.dc) / (dp->mkn.dcm + 1);
                if (++dp->mkn.dc >= dp->mkn.dcm || enCheckInstantDeath(dp)) {
                    enKillCountUp(dp);
                    ENEMY_STEP(ENEMY_MKN_STATE_DYING);
                    return;
                }
                enSetTimer(dp, 200);
                return;
            }
            if (enReduceTimer(dp) <= 0) {
                enKillCountUp(dp);
                ENEMY_STEP(ENEMY_MKN_STATE_DYING);
                return;
            }
            break;
        case 5:
            if (enCheckDamage(dp)) {
                enReduceHP(dp);
                enSetHitBack(dp);
                if (enCheckDeath(dp)) {
                    enFlagResetMoved(dp);
                    if ((enCheckAimedByHuman(dp) == 0) || (enCheckInstantDeath(dp))) {
                        enKillCountUp(dp);
                        ENEMY_STEP(ENEMY_MKN_STATE_DYING);
                        return;
                    }
                    enMKNSetDc(dp);
                    ENEMY_SUB_STEP(4);
                    return;
                }
                enSetTimer(dp, 90);
                ENEMY_SUB_STEP(3);
                return;
            }
            if (!enCheckFinishedByHuman(dp)) {
                enMKNAnimeSet(dp, dp->lie + 22);
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

static int enMKNCanSeePlayer(EnLOCAL_DATA* dp) {
    float* ppos =  enGetPlayerPos(dp);
    float dist; float a; 
    int wcd = enGetWorldCondition();
    dist = enCheckPath2(dp, ppos, (float*) &dp->scp->pos);
    if (dist >= 0.0f) {
        if ((wcd >= 2) && enCheckSeeLight(dp) && !(enLocalWork.Status & 1)) {
            
            return 1;
        }
        return 0;
    }
    dist = dp->p_dist;
    switch (wcd) {
        case 0:
            if (dist > 5000.0f) return 0;        
            break;
        case 1:
            if (dist > 2000.0f) return 0;        
            break;
            
        case 2: case 3:
            if (dist > 4000.0f) return 0;        
            break;
        case 4:
            if (dist > 1100.0f) return 0;        
            break;
    }
    a = enCalcDirection(ppos, (float*) &dp->scp->pos);
    a = enCalcAngleDifference(a, dp->scp->rot.y);
    if ((dist < 1100.0f) && (a < TO_RAD(15)) && !(enCheckNoDamageHuman(dp))) {
        
        return 2;
    }
    if (enLocalWork.Status & 1) return 0;
    if ((wcd >= 2) && (enCheckSeeLight(dp))) return 1;
    
    if (a > TO_RAD(60)) return 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_mkn", enMKNCanSeePlayer2);

static void enMKNAnimeSet(EnLOCAL_DATA* dp, int anim) {
    if (anim == dp->anim) {
        enAnimeRestart(dp);
        dp->anim_s = 4096;
        if (anim == 2) {
            enMKNSetMoveCount(dp);
        }
        return;
    }
    FJ_ASSERT_ON_LINE(anim >= 0 && anim < sizeof(EnMKNAnime) / sizeof(EnANIME_DATA), 1440);
    if (anim == 28) {
        enAnimeSetDirectFrame(dp, anim, EnMKNAnime[anim].Anime, 0);
        return;
    }
    enAnimeSet(dp, anim, EnMKNAnime[anim].Anime);
    if (anim == 2) {
        enMKNSetMoveCount(dp);
    }
}

static void enMKNAnimeReset(EnLOCAL_DATA* dp, int anim) {
    FJ_ASSERT_ON_LINE(anim >= 0 && anim < sizeof(EnMKNAnime) / sizeof(EnANIME_DATA), 1455);
    if (anim == 28) {
        enAnimeSetDirectFrame(dp, anim, EnMKNAnime[anim].Anime, 0);
        return;
    }
    enAnimeSet(dp, anim, EnMKNAnime[anim].Anime);
    if (anim == 2) {
        enMKNSetMoveCount(dp);
    }
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_mkn", enMKNAnimeExec);

static void enMKNAutoRecovery(EnLOCAL_DATA* dp) {
    short recover_rate[5] = { 0, 10, 30, 60, 100 };

    enAddEnduranceDT(dp, shIntToFloat(recover_rate[enGetMode()]));
}

static float enMKNGetWalkSpeed(EnLOCAL_DATA* dp) {
    float speed_rate[5] = { 0.7f, 0.8f, 1.0f, 1.2f, 1.5f };
    float r;

    r = speed_rate[enGetMode()];
    r *= 0.5f + (dp->scp->battle.hp_rate / 200.0f);
    dp->anim_s = shFloatToInt(4096.0f * r);
    return r;
}

static float enMKNGetFeelRange(void) {
    float feel_range[5] = { 400.0f, 750.0f, 1000.0f, 1500.0f, 1500.0f };

    if (enGetWorldCondition() == 4) {
        return 500.0f;
    }
    return feel_range[enGetMode()];
}

static float enMKNGetAttackProbability(void) {
    float attack_rate[5] = { 0.02f, 0.5f, 0.8f, 0.9f, 1.0f };

    if (BgIsOut(0)) {
        return 1.0f;
    }
    return attack_rate[enGetMode()];
}

static float enMKNGetRepertAttackProbability(void) {
    float attack_rate[5] = { 0.0f, 0.0f, 0.2f, 0.6f, 1.0f };

    return attack_rate[enGetMode()];
}

static float enMKNGetAttackSpeed(EnLOCAL_DATA* dp) {
    float speed_rate[5] = { 0.5f, 0.8f, 1.0f, 1.2f, 1.5f };
    float r;

    r = speed_rate[enGetMode()];
    r *= (0.75f + (dp->scp->battle.hp_rate / 400.0f));
    dp->anim_s = shFloatToInt(4096.0f * r);
    return r;
}

static float enMKNGetRotSpeed(void) {
    float rot_rate[5] = { 0.5f, 0.8f, 1.0f, 1.2f, 1.5f };

    return TO_RAD(3) * rot_rate[enGetMode()];
}

static void enMKNSetDownTime(EnLOCAL_DATA* dp) {
    short down_time[5] = { 900, 500, 400, 300, 240 };

    enSetTimer(dp, down_time[enGetMode()]);
}

static void enMKNSetMoveCount(EnLOCAL_DATA* dp) {
    int n;

    n = shFloatToInt(6.0f - (0.2f * enGetMode()) + shSway1f(-2.0f, 0.5f));
    enSetAnimeCount(dp, n << 11);
}

#pragma divbyzerocheck off
static void enMKNSetDc(EnLOCAL_DATA* dp) {
    enSetTimer(dp, 200);
    dp->mkn.dc  = 0;
    dp->mkn.dcm = (shRandI() >> 10) % (enGetMode() + 2) + 4;
}

static void enMKNSoundLife(EnLOCAL_DATA* dp /* r16 */) {
    if (dp->sound_wait < 300) {
        dp->sound_wait++;
        return;
    }
    if ((dp->anim != 2) && (shRandF() >= (0.2f * shGetDT()))) {
        return;
    }
    enSoundCall(shFloatToInt(4.0f * shRandF()) + 12505, 1.0f, &dp->scp->pos);
    dp->sound_wait = 0;
}

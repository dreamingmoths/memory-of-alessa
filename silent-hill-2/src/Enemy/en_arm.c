#include "sce/libvu0.h"
#include "Enemy/en_effect.h"
#include "Enemy/en_arm.h"

#include "Chacter/sh_character_status.h"
#include "Chacter/sh_character_battle.h"
#include "Chacter/player_result.h"
#include "Chacter/sh2_character_manage.h"
#include "Chacter/m3_sc.h"
#include "Chacter/m3_arm.h"
#include "Chacter_Draw/sh2gfw_model_light.h"

#include "Collision/cl_main.h"

#include "Event/event.h"
#include "Event/item.h"
#include "Event/stg_name.h"

#include "Effect2/hh_class_object_execute.h"

#include "GFW/sh2gfw_LightSet.h"
#include "GFW/sh2gfw_2d_filters.h"

#include "shared/Fog/fog.h"
#include "Fog/fog.h"

#include "sound/sh_sound.h"
#include "sound/sh_sd_call.h"

#include "SH2_common/sh2dt.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/playing_info.h"

#include "vec.h"

#include "view/vb_main.h"

#include "Font/fj_man.h"
#pragma fast_fptosi on
#define ENEMY_ARM_ANIME_5251     5251
#define ENEMY_ARM_ANIME_5252     5252
#define ENEMY_ARM_ANIME_5253     5253
#define ENEMY_ARM_ANIME_5254     5254
#define ENEMY_ARM_ANIME_5255     5255
#define ENEMY_ARM_ANIME_5256     5256
#define ENEMY_ARM_ANIME_5257     5257
#define ENEMY_ARM_ANIME_5258     5258
#define ENEMY_ARM_ANIME_5259     5259
#define ENEMY_ARM_ANIME_5260     5260
#define ENEMY_ARM_ANIME_5261     5261
#define ENEMY_ARM_ANIME_5262     5262
#define ENEMY_ARM_ANIME_5263     5263

extern struct EnANIME_DATA EnARMAnime[14] = {
    { ENEMY_ARM_ANIME_5251, false },
    { ENEMY_ARM_ANIME_5251, true },
    { ENEMY_ARM_ANIME_5252, false },
    { ENEMY_ARM_ANIME_5253, false },
    { ENEMY_ARM_ANIME_5254, false },
    { ENEMY_ARM_ANIME_5255, false },
    { ENEMY_ARM_ANIME_5256, false },
    { ENEMY_ARM_ANIME_5257, false },
    { ENEMY_ARM_ANIME_5258, false },
    { ENEMY_ARM_ANIME_5259, false },
    { ENEMY_ARM_ANIME_5260, false },
    { ENEMY_ARM_ANIME_5261, false },
    { ENEMY_ARM_ANIME_5262, false },
    { ENEMY_ARM_ANIME_5263, false },
};

static void enARMCtrlAutomatic(EnLOCAL_DATA* dp);
static void enARMCtrlSleep(EnLOCAL_DATA* dp);
static void enARMCtrlGoPlayable(EnLOCAL_DATA* dp);
static void enARMCtrlEvent(EnLOCAL_DATA* dp);
static void enARMCtrlHand(EnLOCAL_DATA* dp);
static void enARMCtrlWander(EnLOCAL_DATA* dp);
static void enARMCtrlTurn(EnLOCAL_DATA* dp);
static void enARMCtrlDamage(EnLOCAL_DATA* dp);
static void enARMCtrlDead(EnLOCAL_DATA* dp);
static void enARMCheckNearPlayer(EnLOCAL_DATA* dp);
static int enARMGetDamageMotion(EnLOCAL_DATA* dp);
static int enARMCanSeePlayer(EnLOCAL_DATA* dp);
static int enARMCheckNearOther(EnLOCAL_DATA* dp);
static void enARMAnimeSet(EnLOCAL_DATA* dp, int anim);
static void enARMAnimeReset(EnLOCAL_DATA* dp, int anim);
static void enARMAnimeExec(EnLOCAL_DATA* dp);
static void enARMSetHandPos(EnLOCAL_DATA* dp, int d);
static int enARMCheckFloor(EnLOCAL_DATA* dp, int d);
static float enARMGetMoveSpeed(EnLOCAL_DATA* dp);
static void enARMSoundSigns(EnLOCAL_DATA* dp);

#ifdef HOLY_CANDLE
void enARMInitData(EnLOCAL_DATA* dp) {
    float vitarity[5] = { 500.0f, 800.0f, 1200.0f, 2500.0f, 4000.0f };
    int mode; // r17





    mode = enGetMode();
    
    ENEMY_MLV(1);
    ENEMY_STEP(0);
    
    enSetBattleTarget(dp, 0);
    
    enSetSize(dp, 300.0f, 500.0f, 600.0f, 600.0f);
    dp->weight = 3;
    enSetHP(dp, vitarity[mode], vitarity[mode]);
    enFlagSetMoved(dp);
    
    dp->flag |= (1 << 15) | (1 << 10) | (1 << 6) | (1 << 1);
    enARMAnimeSet(dp, 1);
    dp->arm.arm = -1;
    if (enCheckSleepIn(dp)) {
        enSleepIn(dp);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_arm", enARMInitData);
float vitarity[5] = { 500.0f, 800.0f, 1200.0f, 2500.0f, 4000.0f };
#endif

void enARMCtrlMain(EnLOCAL_DATA* dp) {
    void (*enCtrlARMFunc[6])(EnLOCAL_DATA*) = {
        enDummyCtrl,
        enARMCtrlAutomatic,
        enARMCtrlSleep,
        enARMCtrlGoPlayable,
        enARMCtrlEvent,
        enARMCtrlHand
    };

    enCtrlARMFunc[dp->mlv](dp);
}

static void enARMCtrlAutomatic(EnLOCAL_DATA* dp) {
    void (*enCtrlARMSubFunc[4])(EnLOCAL_DATA* dp) = { 
        enARMCtrlWander,
        enARMCtrlTurn,
        enARMCtrlDamage,
        enARMCtrlDead 
    };
    
    enSetBattleTarget(dp, 0);
    
    
    switch (dp->anim) {
    case 2:
    case 4:
        enARMSetHandPos(dp, 0);
        dp->arm.arm = 0;
        break;
    case 3:
    case 5:
        enARMSetHandPos(dp, 1);
        dp->arm.arm = 1;
        break;
    default:
        dp->arm.arm = -1;
        break;
    }

    enCtrlARMSubFunc[dp->slv](dp);
    
    
    enARMAnimeExec(dp);
    
    enMoveExec(dp);
    shVectorCopy(&dp->arm.old_pos, &dp->scp->pos);
    
    if (dp->slv < 2) {
        enARMSoundSigns(dp);
    }
    if (enCheckSleepIn(dp)) {
        enSleepIn(dp);
    }
}

static void enARMCtrlSleep(EnLOCAL_DATA* dp) {
    if (enCheckSleepOut(dp)) {
        enSleepOut(dp);
        ENEMY_MLV(3);
        ENEMY_STEP(0);
    }
    dp->arm.arm = -1;
}

static void enARMCtrlGoPlayable(EnLOCAL_DATA* dp) {
    ENEMY_MLV(1);
    ENEMY_STEP(0);
    dp->arm.arm = -1;
}

static void enARMCtrlEvent(EnLOCAL_DATA* dp) {
    /* @note empty function */ void* tmp;
}

static void enARMCtrlHand(EnLOCAL_DATA* dp) {
    /* @note empty function */
}

static void enARMCtrlWander(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec;
    s_char s;
    if (enCheckDamage(dp)) {
        ENEMY_STEP(2);
        return;
    }
    if (dp->sslv == 0) {
        enInitPath(&dp->path, dp->scp->rot.y);
        dp->anim_n = -1;
    }
    enReduceTimer(dp);
    if (dp->anim_n == -1) {
        if (enARMCheckNearOther(dp)) {
            ENEMY_STEP(1);
            enSetTimer(dp, 0);
            dp->arm.attack = 0;
            return;
        }
        switch (enARMCanSeePlayer(dp)) {
            case 0:
                s = 1;
                dp->arm.attack = 0;
                break;
            case 1:
                if (dp->timer == 0) {
                    s = 2;
                } else {
                    s = 1;
                }
                dp->arm.attack = 0;
                break;
            case 2:
                s = 3;
                dp->arm.attack++;
                
        }
        if (dp->sslv >= 2 && (dp->sslv != s && s < 3 || !(dp->flag & (1 << 2))) 
        || dp->arm.attack > 4) {
            enSetTimer(dp, (60 * 3));
            dp->arm.attack = 0;
            s = 1;
        }
        dp->sslv = s;
        if (dp->arm.arm == -1) {
            if (dp->anim == 7 || dp->anim == 10 || dp->anim == 11) {
              
                
                dp->arm.arm = 0;
            } else {
                dp->arm.arm = 1;
            }
        }
        if (s < 3) {
            enARMAnimeSet(dp, 3 - dp->arm.arm);
        } else {
            enARMAnimeSet(dp, 5 - dp->arm.arm);
            enAttackStart(dp);
        }
    }
    enARMGetMoveSpeed(dp);
    if (dp->sslv == 1) {
        shSinCosV_Scale(&vec, dp->scp->rot.y, 1000.0f);
        shAddVector(&vec, &dp->scp->pos, &vec);
        enSetPath(dp, &vec, &dp->scp->pos);
    } else {
        if (dp->sslv == 3) {
            enAttackCheck(dp, (dp->anim == 4 ? (u_char) 64 : (u_char) 65));
        }
        
        enSetPath(dp, enGetPlayerPos(dp), &dp->scp->pos);
    }
    enMoveAngle(&dp->path, TO_RAD(3));
    dp->scp->rot.y = dp->path.angle;
    enARMCheckNearPlayer(dp);
}

static void enARMCtrlTurn(EnLOCAL_DATA* dp) {
    if (enCheckDamage(dp)) {
        ENEMY_STEP(2);
        return;
    }
    if (dp->sslv == 0) {
        enInitPath(&dp->path, dp->scp->rot.y);
        dp->anim_n = -1;
        if (dp->arm.arm == -1) {
            if (dp->anim == 7
            || dp->anim == 10 
            || dp->anim == 11) {
                dp->arm.arm = 0;
            } else {
                dp->arm.arm = 1;
            }
        }
        if (enARMCanSeePlayer(dp) == 2) {
            enARMAnimeSet(dp, 5 - dp->arm.arm);
            enAttackStart(dp);
        } else {
            enARMAnimeSet(dp, 3 - dp->arm.arm);
        }
        dp->sslv++;
    }
    if (dp->anim == 4) {
        enAttackCheck(dp, 64);
    } else if (dp->anim == 5) {
        enAttackCheck(dp, 65);
    }
    enARMGetMoveSpeed(dp);
    if (dp->p_dist > 5000.0f) {
        dp->anim_s /= 4;
        dp->arm.scount = 4;
    }
    dp->path.markangle = dp->path.angle + (TO_RAD(3) * dp->arm.dir);
    enMoveAngle(&dp->path, TO_RAD(3));
    dp->scp->rot.y = dp->path.angle;
    enARMCheckNearPlayer(dp);
    if (dp->anim_n == -1) {
        if (++dp->sslv < 4) {
            if (enARMCanSeePlayer(dp) == 2) {
                enARMAnimeSet(dp, 5 - dp->arm.arm);
                enAttackStart(dp);
                return;}
            enARMAnimeSet(dp, 3 - dp->arm.arm);
            
            return;}
        ENEMY_STEP(0);
    }

}

static void enARMCtrlDamage(EnLOCAL_DATA* dp) {
    switch (dp->sslv) {
        case 0:
            enReduceHP(dp);
            dp->flag &= ~(1 << 15); 
            enARMAnimeReset(dp, enARMGetDamageMotion(dp));
            ENEMY_NEXT_SUB_STEP();
            break;
        case 1:
            if (enCheckDamage(dp)) {
                enReduceHP(dp);
            }
            if (dp->anim_n == -1) {
                if (enCheckDeath(dp)) {
                    if (dp->anim == 6 
                    || dp->anim == 8 
                    || dp->anim == 9) {
                        enARMAnimeSet(dp, 12);
                    } else {
                        enARMAnimeSet(dp, 13);
                    }
                    fogEraseObj(dp - enLocalWork.Data + 10);
                    enFlagSetNoDamage(dp);
                    enFlagResetMoved(dp);
                    enFlagSetDead(dp);
                    enKillCountUp(dp);
                    ENEMY_NEXT_SUB_STEP();
                } else {
                    ENEMY_STEP(0);
                    enSetTimer(dp, 0);
                    dp->arm.attack = 0;
                    dp->flag |= (1 << 15);                    
                }
            }
            break;
        case 2:
            if (dp->anim_n == -1) {
                ENEMY_STEP(3);
            }
    }
    
    enARMCheckNearPlayer(dp);
}

static void enARMCtrlDead(EnLOCAL_DATA* dp) {

    
    
    
    
    
    
    if (dp->sslv == 0) {
        enSetTimer(dp, 60);
        ENEMY_NEXT_SUB_STEP();
    }
    if (enReduceTimer(dp) <= 0) {
    
        enDeleteCharacter(dp);
    }
}

static void enARMCheckNearPlayer(EnLOCAL_DATA* dp) {
    enCheckNearPlayer(dp, &dp->arm.near_count, &dp->arm.dist, 200.0f);
}

static int enARMGetDamageMotion(EnLOCAL_DATA* dp) {
    int m; int id; int dd; int arm;
    float a;

    
    a = shAngleRegulate(shAtanV(&dp->scp->battle.vec) - dp->scp->rot.y);
    if (shFloatAbs(a) > QUARTER_TURN) id = 0;
    else id = 1;
    
    switch (dp->anim) {
        case 2:
        case 3:
        case 4:
        case 5:
            dd = dp->anim_n >= 19201 ^ (dp->arm.arm == 0 ? 0 : 1);
            break;
        case 1:
        case 6:
        case 8:
        case 9:
            dd = 0;
            break;
        default:
            dd = 1;
    }

    m = dp->last_atk;
    switch (m) {
        case 2:
        case 1:
            arm = dd + 6;
            break;
        case 4:
        case 6:
            arm = dd * 2 + 6 + id;
            break;
        default:
            arm = 0;
            printf("Illegal damage type!(%d)\n", dp->last_atk);
    }
    return arm;
}


static int enARMCanSeePlayer(EnLOCAL_DATA* dp) {
    float a = enCalcAngleDifference(enGetPlayerDirection(dp), dp->scp->rot.y); sceVu0FVECTOR vec;
    if (enLocalWork.Status & 1) return 0;
    if ((dp->p_dist > 2500.0f || a > TO_RAD(120)) && dp->anim < 6) {
        return 0;
    } else if (dp->p_dist < 1000.0f && enARMCheckFloor(dp, 0) != 1 && enARMCheckFloor(dp, 1) != 1) {
        
        
        shSinCosV_Scale(&vec, dp->scp->rot.y, 1000.0f);
        shAddVector(&vec, &dp->scp->pos, &vec);
        if (enCheckFloor(&vec) != 1) return 2;
    }
    
    return 1;
}

static int enARMCheckNearOther(EnLOCAL_DATA* dp) {
    EnLOCAL_DATA* tp = &enLocalWork.Data[0]; 
    int i; float* tpos; float d;

    for (i = 0; i < ENEMY_MAX; i++, tp++) {
        if (tp != dp && tp->kind == 10) {
            tpos = &tp->scp->pos;
            if (shVectorDist(&dp->scp->pos, tpos) < 1000.0f) {
                d = shAngleRegulate(dp->scp->rot.y - enCalcDirection(tpos, &dp->scp->pos));
                if (shFloatAbs(d) < QUARTER_TURN) {
                    if (d >= 0.0f) {
                        dp->arm.dir = 1;
                    } else {
                        dp->arm.dir = -1;
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

static void enARMAnimeSet(EnLOCAL_DATA* dp, int anim) {
    if (anim == dp->anim) {
        enAnimeRestart(dp);
        return;
    }
    
    FJ_ASSERT_ON_LINE(anim >= 0 && anim < sizeof(EnARMAnime) / sizeof(EnANIME_DATA), 579);
    enAnimeSet(dp, anim, (&EnARMAnime)[anim].Anime);
    dp->arm.arm = -1;
}

static void enARMAnimeReset(EnLOCAL_DATA* dp, int anim) {
    
    FJ_ASSERT_ON_LINE(anim >= 0 && anim < sizeof(EnARMAnime) / sizeof(EnANIME_DATA), 588);
    enAnimeSet(dp, anim, (&EnARMAnime)[anim].Anime);
    dp->arm.arm = -1;
}

static void enARMAnimeExec(EnLOCAL_DATA* dp) {
    int of; sceVu0FVECTOR pos;
    enAnimeExec(dp, &EnARMAnime, 5251);
    if (dp->anim >= 2 && dp->anim < 6
    && dp->anim_step == 0 && dp->anim_n == -1) {
        dp->anim_step = 1;
        if (dp->p_dist < 5000.0f || ++dp->arm.scount >= 4) {
            
            dp->arm.scount = 0;
            enARMGetHandPos(&pos, dp, dp->arm.arm ^ 1);
            shAddVector(&pos, &dp->scp->pos,&pos);
            pos[1] = dp->scp->pos.y;
            
            switch (enCheckFloor(&pos)) {
                case 2:
                    enSoundCall(12250, 0.8f, &pos);
                break;
                default:
                    enSoundCall(12251, 0.8f, &pos);
            }
        }
    }
    
    
    if (dp->anim_n == -1 || dp->flag & 1) return;
}

static void enARMSetHandPos(EnLOCAL_DATA* dp, int d) {
    sceVu0FVECTOR vec;
    enARMGetHandPos(&vec, dp, d);
    shAddVector(&dp->arm.hand_pos, &dp->scp->pos, &vec);
}

static void enARMGetHandPos(float* vec, EnLOCAL_DATA* dp, int d) {
    sceVu0FMATRIX mat;
    enGetSkeletonMatrix(mat, dp, d + 11);
    shVectorZeroXyz(vec);
    vec[0] = 550.0f;
    shVectorTransform(vec, mat);
    
    shUnitMatrix(mat);
    shRotMatrixY(mat, mat, dp->scp->rot.y);
    shVectorTransform(vec, mat);
}

static int enARMCheckFloor(EnLOCAL_DATA* dp, int d) {
    sceVu0FVECTOR pos;
    enARMGetHandPos(pos, dp, d);
    return enCheckFloor(pos);
}

static float enARMGetMoveSpeed(EnLOCAL_DATA* dp) {
    float speed_rate[5] = { 0.7f, 0.8f, 1.0f, 1.2f, 1.5f };
    float r;


    
    
    
    r = speed_rate[enGetMode()];
    r *= (0.6f + (dp->scp->battle.hp_rate / 250.0f));
    if (dp->p_dist > 5000.0f) r *= 4.0f;
    dp->anim_s = ftoi(4096.0f * r);
    return r;
}

#ifdef HOLY_CANDLE
static void enARMSoundSigns(EnLOCAL_DATA* dp) {
    int signs;
    if ((dp->arm.count -= shGetDF()) <= 0) {
        dp->arm.count = enCalcTimer(60);
        do {
            signs = (shRandI() >> 20) & 3;
        } while (signs == dp->arm.signs);
        dp->arm.signs = signs;
        
        enSoundCall(signs + 12258, 1.0f, &dp->scp->pos);
    }

}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_arm", enARMSoundSigns);
#endif

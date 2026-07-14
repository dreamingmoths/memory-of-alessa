#include "sh2_common.h"
#include "SH2_common/pad.h"
#include "SH2_common/sh_vu0.h"

#include "vec.h"
#include "sce/libvu0.h"

#include "Enemy/en_common.h"
#include "Enemy/en_insect.h"
#include "Enemy/en_bos.h"

#include "Event/event.h"
#include "Font/fj_man.h"

#define ENEMY_BOS_STATE_APPROACH 0
#define ENEMY_BOS_STATE_DISTANCE 1
#define ENEMY_BOS_STATE_GENERATE 2
#define ENEMY_BOS_STATE_ATTACK   3
#define ENEMY_BOS_STATE_ATTACK2  4
#define ENEMY_BOS_STATE_DEAD     5

#define ENEMY_BOS_ANIME_5801     5801
#define ENEMY_BOS_SIGNS_SOUND    18862
#define ENEMY_BOS_MOTH_COUNT     32

static void enBOSCtrlAutomatic(EnLOCAL_DATA* dp);
static void enBOSCtrlGoPlayable(EnLOCAL_DATA* dp);
static void enBOSCtrlHand(void);
static void enBOSCtrlApproach(EnLOCAL_DATA* dp);
static void enBOSCtrlDistance(EnLOCAL_DATA* dp);
static void enBOSCtrlGenerate(EnLOCAL_DATA* dp);
static void enBOSCtrlAttack(EnLOCAL_DATA* dp);
static void enBOSCtrlAttack2(EnLOCAL_DATA* dp);
static void enBOSCtrlDead(EnLOCAL_DATA* dp);
static int enBOSCheckPlayerLastBullet(EnLOCAL_DATA* dp);
static int enBOSCanAttackPlayer(EnLOCAL_DATA* dp);
static void enBOSResetSpeed(EnLOCAL_DATA* dp);
static int enBOSCheckDamage(EnLOCAL_DATA* dp);
static int enBOSCheckFloor(EnLOCAL_DATA* dp);
static void enBOSCheckNearPlayer(EnLOCAL_DATA* dp);
static void enBOSMoveExec(EnLOCAL_DATA* dp);
static void enBOSAnimeSet(EnLOCAL_DATA* dp, int anim);
static void enBOSAnimeExec(EnLOCAL_DATA* dp);
static float enBOSGetMoveSpeed(void);
static void enBOSSoundSigns(EnLOCAL_DATA* dp);

extern /* static */ EnANIME_DATA EnBOSAnime[10]; // size: 0x28, address: 0x2A9A60
extern /* static */ float bed_pos[4];            // size: 0x10, address: 0x2A9AF0
extern /* static */ float stair_pos[4];          // size: 0x10, address: 0x2A9B00

void enBOSInitData(EnLOCAL_DATA* dp /* r17 */) {
    float vitarity[5] = {
        5000.0f,
        7500.0f,
        10000.0f,
        20000.0f,
        40000.0f,
    }; // r29+0x30
    int mode = enGetMode(); // r16

    ENEMY_MLV(1);
    enSetHP(dp, vitarity[mode], vitarity[mode]);
    enSetSize(dp, 250.0f, 800.0f, 100.0f, -150.0f);
    dp->weight = 2;
    dp->flag |= (1 << 10) | (1 << 1);
    if (mode < 3) {
        dp->bos.end_count = 1800;
    } else {
        dp->bos.end_count = 18000;
    }
    if (dp->scp->en_first_status == 13) {
        enBOSAnimeSet(dp, 9);
        enSetSize(dp, 350.0f, 250.0f, 125.0f, 250.0f);
        ENEMY_STEP(ENEMY_BOS_STATE_DEAD);
        return;
    }
    ENEMY_STEP(ENEMY_BOS_STATE_APPROACH);
}

void enBOSCtrlMain(EnLOCAL_DATA* dp /* r2 */) {
    void (*enCtrlBOSFunc[6])(EnLOCAL_DATA*) = {
        enDummyCtrl,
        enBOSCtrlAutomatic,
        enDummyCtrl,
        enBOSCtrlGoPlayable,
        enDummyCtrl
    }; // r29+0x10
    enCtrlBOSFunc[dp->mlv](dp);
}

static void enBOSCtrlAutomatic(EnLOCAL_DATA* dp /* r16 */) {
    void (*enCtrlBOSSubFunc[6])(EnLOCAL_DATA*) = {
        enBOSCtrlApproach,
        enBOSCtrlDistance,
        enBOSCtrlGenerate,
        enBOSCtrlAttack,
        enBOSCtrlAttack2,
        enBOSCtrlDead,
    }; // r29+0x20

    enSetBattleTarget(dp, 1);
    enCtrlBOSSubFunc[dp->slv](dp);
    enBOSAnimeExec(dp);
    if (dp->slv < 5) {
        enBOSMoveExec(dp);
        enBOSSoundSigns(dp);
        fogSetStayPoint(&dp->scp->pos);
        return;
    }

    enMoveExec(dp);
    fogResetStayPoint();
}

static void enBOSCtrlGoPlayable(EnLOCAL_DATA* dp /* r2 */) {
    ENEMY_MLV(1);
    ENEMY_STEP(ENEMY_BOS_STATE_APPROACH);
}

static void enBOSCtrlHand(void) {
    /* empty */
}

static inline void vec_add_reverse(void* x, void* y, void* out) {
    asm("\
        lqc2 vf4, 0(%1)\n\
        lqc2 vf5, 0(%0)\n\
        vadd.xyzw vf4, vf4, vf5\n\
        sqc2 vf4, 0(%2)"
        : "+r"(x), "+r"(y), "+r"(out));
}

static void enBOSCtrlApproach(EnLOCAL_DATA* dp /* r16 */) {
    sceVu0FVECTOR pos, vec; // r29+0x20, r29+0x30
    float a;
    if (enBOSCheckPlayerLastBullet(dp))
        return;
    if (enBOSCheckDamage(dp) != 2) {
        if (dp->sslv != 0)
            dp->sslv = dp->sslv; // @hack? something got optimized out here
        else {
            if ((dp->anim != 8) && (dp->anim != 1)) {
                enBOSAnimeSet(dp, 1);
            }
            ENEMY_NEXT_SUB_STEP();
        }

        shSinCosV_Scale(&vec, enGetPlayerAngle(dp), 600.0f);
        vec_add_reverse(vec, enGetPlayerPos(dp), pos);
        if (enCheckPlayerHitEyes(dp, pos) >= 0.0f) {
            vec_sub_reverse(vec, enGetPlayerPos(dp), pos);
        }

        a                 = enCalcDirection(pos, &dp->scp->pos);
        a                 = shAngleRegulate(a - dp->path.angle);
        dp->bos.rot_speed = 0.05f * a;

        switch (enBOSCanAttackPlayer(dp)) {
            case 1:
                ENEMY_STEP(ENEMY_BOS_STATE_ATTACK2);
                break;

            case 2:
                if (enBOSCheckFloor(dp)) {
                    ENEMY_STEP(ENEMY_BOS_STATE_ATTACK2);
                } else {
                    ENEMY_STEP(ENEMY_BOS_STATE_ATTACK);
                }
                break;

            default:
                if (dp->p_dist >= 1500.0f && enCheckIntoScreen(dp)) {
                    if (dp->bos.insect_dp) {
                        if (*(s_char*) dp->bos.insect_dp == 0) {
                            dp->bos.insect_dp = NULL;
                        } else {
                            break;
                        }
                    }
                    ENEMY_STEP(ENEMY_BOS_STATE_GENERATE);
                }
                enBOSCheckNearPlayer(dp);
                break;
        }
    }
}

static void enBOSCtrlDistance(EnLOCAL_DATA* dp /* r16 */) {
    sceVu0FVECTOR pos, vec; // r29+0x20,  r29+0x30
    float a;                // r29+0x40
    if (enBOSCheckPlayerLastBullet(dp))
        return;
    switch (enBOSCheckDamage(dp)) {
        case 2:
            return;

        case 1:
            ENEMY_STEP(ENEMY_BOS_STATE_APPROACH);
            break;

        default:
            if (dp->sslv)
                dp->sslv = dp->sslv;
            else {
                if ((dp->anim != 8) && (dp->anim != 1)) {
                    enBOSAnimeSet(dp, 1);
                }
                enSetTimer(dp, 0x78);
                ENEMY_NEXT_SUB_STEP();
            }

            shSinCosV_Scale(&vec, enGetPlayerDirection(dp), 1500.0f);
            vec_sub_reverse(vec, enGetPlayerPos(dp), pos);
            dp->bos.rot_add = 0.05f * shAngleRegulate(enCalcDirection(&pos, &dp->scp->pos.x) - dp->path.angle);
            if ((enReduceTimer(dp) <= 0) || (enBOSCanAttackPlayer(dp) != 0)) {
                ENEMY_STEP(ENEMY_BOS_STATE_APPROACH);
            }
            enBOSCheckNearPlayer(dp);
            break;
    }
}

static void enBOSCtrlGenerate(EnLOCAL_DATA* dp /* r17 */) {
    int i;              // r18
    EnLOCAL_DATA* tp;   // r16
    sceVu0FVECTOR pos;  // r29+0x60
    sceVu0FVECTOR vec;  // r29+0x70
    float a;            // r20
    SubCharacter* tscp; // r19

    if (enBOSCheckDamage(dp) == 2)
        return;
    tp = dp->bos.insect_dp;
    if (enBOSCheckPlayerLastBullet(dp))
        return;

    switch (dp->sslv) {
        case 0:
            if ((dp->anim != 8) && (dp->anim != 1)) {
                enBOSAnimeSet(dp, 1);
            }
            if ((tp = enEntryEnemy(15)) == NULL) {
                ENEMY_STEP(ENEMY_BOS_STATE_APPROACH);
                return;
            }
            tscp = enINSGetSubCharacter(tp);
            volatile_vec_copy(&tscp->pos, &dp->scp->pos);
            vec_zero(&tscp->rot);
            a           = enGetPlayerDirection(dp);
            tscp->rot.y = a;
            enInitData(tp, tscp);
            dp->bos.insect_dp = tp;
            for (i = 0; i < ENEMY_BOS_MOTH_COUNT; i++) {
                if ((tp = enEntryEnemy(15)) == NULL)
                    break;
                tscp = enINSGetSubCharacter(tp);
                volatile_vec_copy(&tscp->pos, &dp->scp->pos);
                tscp->rot.y = a;
                enInitData(tp, tscp);
            }
            tp           = dp->bos.insect_dp;
            dp->bos.mode = 1;
            enAttackStart(dp);
            ENEMY_NEXT_SUB_STEP();
            break;

        case 1:
            if (tp->slv == 1) {
                enAttackCheck(dp, 62);
                if (!(dp->flag & 4)) {
                    enAttackStart(dp);
                    ENEMY_NEXT_SUB_STEP();
                }
            } else if (tp->slv == 2) {
                ENEMY_STEP(ENEMY_BOS_STATE_DISTANCE);
            }
            break;
        case 2:
            enAttackCheckHug(dp, 63);
            if (enCheckHuggedPlayer() == 0) {
                tp->slv = 2;
                ENEMY_NEXT_SUB_STEP();
            }
            break;
        case 3:
            if (enBOSCanAttackPlayer(dp) == 2) {
                if (enBOSCheckFloor(dp) == 0) {
                    ENEMY_STEP(ENEMY_BOS_STATE_ATTACK);
                    return;
                }
                ENEMY_STEP(ENEMY_BOS_STATE_ATTACK2);
                return;
            }
            break;
    }
    shSinCosV_Scale(&vec, enGetPlayerAngle(dp), 600.0f);
    vec_add_reverse(&vec, enGetPlayerPos(dp), &pos);
    if (enCheckPlayerHitEyes(dp, &pos) >= 0.0f) {
        enGetPlayerPos(dp);
        vec_sub_reverse(enGetPlayerPos(dp), &vec, &pos);
    }
    a               = enCalcDirection(&pos, &dp->scp->pos) - dp->path.angle;
    dp->bos.rot_add = 0.05f * shAngleRegulate(a);
    if (*(s_char*) dp->bos.insect_dp == 0) {
        ENEMY_STEP(ENEMY_BOS_STATE_APPROACH);
        dp->bos.mode      = 0.0f;
        dp->bos.insect_dp = NULL;
    }
    enBOSCheckNearPlayer(dp);
}

static void enBOSCtrlAttack(EnLOCAL_DATA* dp /* r16 */) {
    sceVu0FVECTOR vec; // r29+0x20

    if (enCheckDamage(dp)) {
        if (enCheckHuggedPlayer()) {
            enResetDamage(dp);
        } else if (enBOSCheckDamage(dp) != 2) {
            ENEMY_STEP(ENEMY_BOS_STATE_DISTANCE);
            return;
        }
    }

    switch (dp->sslv) {
        case 0:
            enBOSAnimeSet(dp, 2);
            enAttackStart(dp);
            dp->flag |= 1 << 15;
            enFlagSetCritical(dp);
            dp->bos.mode = 0;
            ENEMY_NEXT_SUB_STEP();
            return;

        case 1:
            shSinCosV_Scale(&vec, enGetPlayerAngle(dp), 600.0f);

            vec_add(enGetPlayerPos(dp), &vec, &vec);
            vec_sub_reverse(&vec, dp->vec, &dp->scp->pos);
            dp->vec[3] = 0.0f;
            dp->vec[1] = 0.0f;
            enAttackCheck(dp, 59);
            if (dp->anim_n == -1) {
                if (dp->flag & (1 << 2)) {
                    enBOSAnimeSet(dp, 6);
                    ENEMY_SUB_STEP(4);
                    return;
                }
                enBOSAnimeSet(dp, 3);
                enAttackStart(dp);
                ENEMY_NEXT_SUB_STEP();
            }
            return;

        case 2:
            if (dp->anim_n == -1) {
                enBOSAnimeSet(dp, 4);
                dp->flag &= 0xFFFF7FFF;
                ENEMY_NEXT_SUB_STEP();
                return;
            }
            break;

        case 3:
            enAttackCheckHug(dp, 60);
            if (enCheckHuggedPlayer() == 0) {
                enBOSAnimeSet(dp, 5);
                ENEMY_NEXT_SUB_STEP();
                return;
            }
            break;

        case 4:
            if (dp->anim_n == -1) {
                ENEMY_STEP(ENEMY_BOS_STATE_DISTANCE);
                dp->flag &= 0xFFFF7FFF;
                enFlagResetCritical(dp);
                enBOSResetSpeed(dp);
            }
            break;
    }
}

static void enBOSCtrlAttack2(EnLOCAL_DATA* dp /* r16 */) {
    if (enCheckDamage(dp)) {
        if (enBOSCheckDamage(dp) != 2) {
            ENEMY_STEP(ENEMY_BOS_STATE_DISTANCE);
        }
    } else {
        switch (dp->sslv) {
            case 0:
                enBOSAnimeSet(dp, 7);
                enAttackStart(dp);
                enFlagSetCritical(dp);
                ENEMY_NEXT_SUB_STEP();
                /* fallthrough */
            case 1:
                enAttackCheck(dp, 61);
                if (dp->anim_n == -1) {
                    ENEMY_STEP(ENEMY_BOS_STATE_APPROACH);
                    enFlagResetCritical(dp);
                }
                break;
        }
        enBOSCheckNearPlayer(dp);
    }
}

static void enBOSCtrlDead(EnLOCAL_DATA* dp /* r16 */) {
    if (dp->scp->en_first_status == 13) {
        if (dp->sslv == 1) {
            if (enReduceTimer(dp) <= 0) {
                enResetFilter();
                SET_GAME_FLAG(GAME_FLAG_508);
            }
            return;
        }
        if (enCheckDamage(dp) != 0) {
            enKillCountUp(dp);
            enSetFadeOut();
            enSetTimer(dp, 120);
            dp->flag |= 1 << 3;
            ENEMY_NEXT_SUB_STEP();
        }
    } else {
        if (dp->sslv == 0) {
            enSetTimer(dp, 60);
            enSetBlur();
            dp->flag |= 1 << 3;
            ENEMY_NEXT_SUB_STEP();
        }
        if (enReduceTimer(dp) <= 0) {
            enResetFilter();
            SET_GAME_FLAG(GAME_FLAG_506);
        }
    }
}

static int enBOSCheckPlayerLastBullet(EnLOCAL_DATA* dp /* r16 */) {
    EnLOCAL_DATA* tp; // r3

    if (!enCheckPlayerBulletEmpty()) {
        return 0;
    }
    if ((dp->bos.end_count -= shGetDT()) > 0) {
        return 0;
    }

    tp = dp->bos.insect_dp;
    if (tp && tp->kind != 0 && tp->slv < 2) {
        tp->slv = 2;
    }
    SET_GAME_FLAG(GAME_FLAG_506);
    return 1;
}

static int enBOSCanAttackPlayer(EnLOCAL_DATA* dp /* r16 */) {
    float dist; // r20
    float a;    // r21

    dist = dp->p_dist = enGetPlayerDistance(dp);
    a                 = enCalcAngleDifference(enGetPlayerDirection(dp), dp->scp->rot.y);
    if (dist < 700.0f && dist > 500.0f && a < TO_RAD(5) && enCalcAngleDifference(enGetPlayerAngle(dp), dp->scp->rot.y) > 1.3962634f && (enCheckNoDamageHuman(dp) == 0)) {
        return 2;
    }
    if ((dist < 600.0f) && (a < TO_RAD(5)) && (enCheckNoDamageHuman(dp) == 0)) {
        return 1;
    }
    return 0;
}

static void enBOSResetSpeed(EnLOCAL_DATA* dp /* r2 */) {
    dp->bos.move_speed = 0.0f;
    dp->bos.y_speed    = 0.0f;
    dp->bos.rot_add    = 0.0f;
    dp->bos.rot_speed  = 0.0f;
    dp->bos.mode       = 0;
}

static int enBOSCheckDamage(EnLOCAL_DATA* dp /* r16 */) {
    EnLOCAL_DATA* tp; // r3

    if (!enCheckDamage(dp)) {
        return 0;
    }

    if (shPadGetPort() == 6 && shPadPress(0, PAD_KEY_L2)) {
        dp->endurance           = 0.0f;
        dp->scp->battle.hp_rate = 0.0f;
        dp->scp->battle.hp      = 0.0f;
    }

    if (dp->last_atk >= 21 && dp->last_atk < 23) {
        dp->scp->battle.damage *= 10.0f;
    }

    enReduceHP(dp);
    enSetHitBack(dp);
    dp->flag &= 0xffff7fff; // @note using tilde doesn't match.
    if (enCheckDeath(dp) != 0) {
        tp = dp->bos.insect_dp;
        if ((tp != NULL) && (tp->kind != 0) && (tp->slv < 2)) {
            tp->slv = 2;
        }
        ENEMY_STEP(ENEMY_BOS_STATE_DEAD);
        return 2;
    }
    enBOSAnimeSet(dp, 8);
    return 1;
}

static int enBOSCheckFloor(EnLOCAL_DATA* dp /* r2 */) {
    if (vec3_dist_xz(bed_pos, &dp->scp->pos) < bed_pos[3] || vec3_dist_xz(stair_pos, &dp->scp->pos) < stair_pos[3]) {
        return true;
    }
    return false;
}

static void enBOSCheckNearPlayer(EnLOCAL_DATA* dp /* r2 */) {
    enCheckNearPlayer(dp, &dp->bos.near_count, &dp->bos.dist, 200.0f);
}

static void enBOSMoveExec(EnLOCAL_DATA* dp /* r17 */) {
    float add;               // r20
    float d;                 // r21
    float s;                 // r29+0x50
    int mode = dp->bos.mode; // r16
    EnPATH_DATA tpath;       // r29+0x40

    if (mode < 2) {
        dp->bos.rot_speed  = (0.95f * dp->bos.rot_speed) + dp->bos.rot_add;
        dp->path.markangle = dp->path.angle + dp->bos.rot_speed;
        enMoveAngle(&dp->path, 0.034906585f);
        add = 250.0f * shGetDT();
        d   = dp->bos.move_speed;
        if (dp->anim == 8) {
            d -= add;
            if (d < 0.0f) {
                d = 0.0f;
            }
            mode = 1;
            if (dp->anim_n == -1) {
                enBOSAnimeSet(dp, 1);
            }
        } else {
            s = enBOSGetMoveSpeed();
            d += add;
            if (d > s) {
                d = s;
            }
        }
        dp->bos.move_speed = d;
        shSinCosV_Scale(dp->vec, dp->path.angle, d);
    }
    tpath.markangle = enGetPlayerDirection(dp);
    tpath.angle     = dp->path.angle;
    enMoveAngle(&tpath, 0.017453292f);
    dp->path.angle = tpath.angle;
    if (mode != 0) {
        s = (-17500.0f - (dp->scp->pos).y) * 0.2f;
    } else {
        s = shSway1f(-250.0f, 0.1f);
    }
    dp->bos.y_speed = 0.98f * s;
    if (((dp->scp->pos.y < -17700.0f) && (dp->bos.y_speed < 0.0f)) || (dp->scp->pos.y >= -17300.0f && dp->bos.y_speed > 0.0f)) {
        dp->bos.y_speed *= 0.5f;
    }
    if ((dp->scp->pos.y <= -17300.0f) || (dp->bos.y_speed < 0.0f)) {
        dp->vec[1] = dp->bos.y_speed;
    }
    enMoveExec(dp);
}

static void enBOSAnimeSet(EnLOCAL_DATA* dp /* r17 */, int anim /* r16 */) {
    if (anim == dp->anim) {
        enAnimeRestart(dp);
        return;
    }
    FJ_ASSERT_ON_LINE(anim >= 0 && anim < sizeof(EnBOSAnime) / sizeof(EnANIME_DATA), 725);
    enAnimeSet(dp, anim, (s32) EnBOSAnime[anim].Anime);
}

static void enBOSAnimeExec(EnLOCAL_DATA* dp /* r16 */) {
    enAnimeExec(dp, EnBOSAnime, ENEMY_BOS_ANIME_5801);
    if ((dp->anim_n == -1) || ((dp->flag & 1) != 0)) {
        return;
    }
    if (dp->anim == 2) {
        if ((dp->anim_n >= 28800) && (dp->anim_n < 33600) && (dp->flag & 4)) {
            dp->anim_s = 1024;
            return;
        }
        dp->anim_s = 1024;
    }
}

static float enBOSGetMoveSpeed(void) {
    float speed_rate[5] = {
        0.69f,
        0.8f,
        1.0f,
        1.5f,
        2.0f,
    }; // r29+0x10
    return 500.0f * speed_rate[enGetMode()];
}

static void enBOSSoundSigns(EnLOCAL_DATA* dp /* r16 */) {
    int signs; // r3

    if ((dp->bos.count -= shGetDF()) <= 0) {
        dp->bos.count = enCalcTimer(60);
        do {
            signs = (shRandI() >> 20) & 3;
        } while (signs == dp->bos.signs);
        dp->bos.signs = signs;
        if (signs) {
            enSoundCall(signs + ENEMY_BOS_SIGNS_SOUND, 0.4f, &dp->scp->pos);
            return;
        }
        enSoundCall3D(ENEMY_BOS_SIGNS_SOUND, 0.4f, &dp->scp->pos);
    }
}

#include "sh2_common.h"
#include "SH2_common/mem_share.h"
#include "SH2_common/sh2dt.h"
#include "SH2_common/sh_vu0.h"

#include "vec.h"

#include "sound/sh_sound.h"

#include "Enemy/en_common.h"
#include "Enemy/en_insect.h"

static void enINSCtrlApproach(EnLOCAL_DATA* dp);
static void enINSCtrlAttack(EnLOCAL_DATA* dp);
static void enINSCtrlEscape(EnLOCAL_DATA* dp);
static void enINSCtrlChase(EnLOCAL_DATA* dp);
static void enINSCtrlStay(EnLOCAL_DATA* dp);
static void enINSMove(EnLOCAL_DATA* dp, float* target, float rot_rate, float rot_delta, float speed);
static void enINSCheckWall(EnLOCAL_DATA* dp);
static void enINSAnimeExec(EnLOCAL_DATA* dp);

#define ENEMY_INS_STATE_APPROACH 0
#define ENEMY_INS_STATE_ATTACK   1
#define ENEMY_INS_STATE_ESCAPE   2
#define ENEMY_INS_STATE_CHASE    3
#define ENEMY_INS_STATE_STAY     4
#pragma fast_fptosi on

static sceVu0FVECTOR escape_point[3] = {
    { 58600.0f, -16500.0f, 63600.0f, 0.0f },
    { 61400.0f, -16500.0f, 63600.0f, 0.0f },
    { 58600.0f, -16500.0f, 56400.0f, 0.0f },
}; // size: 0x30, address: 0x375B60
UNMIGRATED(sceVu0FVECTOR stay_pos); // size: 0x10, address: 0x1202F90

#line 65
void enINSInitData(EnLOCAL_DATA* dp) {
    EnLOCAL_DATA* tp = enLocalWork.Data; // r17
    int i; // r2
    enSetHP(dp, 1.0f, 1.0f);
    for (i = 0; i < ENEMY_MAX; i++, tp++) {
        if (tp == dp) continue;
        if (tp->kind == EnKIND_INS) {
            dp->ins.leader = tp;
            break;
        }
    }
    ENEMY_MLV(1);
    if (i == ENEMY_MAX) {
        ENEMY_STEP(ENEMY_INS_STATE_APPROACH);
    } else {
        ENEMY_STEP(ENEMY_INS_STATE_CHASE);
    }
    dp->flag = (1 << 1) | (1 << 3);
    enSetSize(dp, 50.0f, 0.0f, 0.0f, 0.0f);
    dp->anim_n = (int) (shRandI() >> 4) % 9600;
    dp->anim_s = 1024;
    shRandV_Scale(dp->ins.view_rot, PI);
    shRandV_Scale(dp->ins.rot_add, TO_RAD(720));
    dp->scp->battle.status = 0;
    dp->ins.twin_dist = 25.0f;
}

#ifdef NON_MATCHING
#line 96
void enSetInsect(float* pos, int num) {
    EnLOCAL_DATA* dp; // r16
    SubCharacter* scp; // r20
    sceVu0FVECTOR vec; // r29+0x60
    int i; // r17
    shVectorCopy(stay_pos, pos);
    for (i = 0; i < num; i++) {
        if ((dp = enEntryEnemy(EnKIND_INS)) == NULL) break;
        // create `num` insects, facing in a random direction
        // end copied from `enINSInitData`
        scp = enINSGetSubCharacter(dp);
        shRandV_Scale(vec, 500.0f);
        shAddVector(&scp->pos.x, pos, vec);
        shVectorCopy(&scp->b_pos, pos);
        dp->scp = scp;
        scp->battle.status = 0;
        dp->type = 0;
        enSetHP(dp, 1.0f, 1.0f);
        ENEMY_MLV(1);
        ENEMY_STEP(ENEMY_INS_STATE_STAY);
        dp->flag = (1 << 1) | (1 << 3);
        enSetSize(dp, 50.0f, 0.0f, 0.0f, 0.0f);
        dp->anim_n = (int) (shRandI() >> 4) % 9600;
        dp->anim_s = 1024;
        shRandV_Scale(dp->ins.view_rot, PI);
        shRandV_Scale(dp->ins.rot_add, TO_RAD(720));
        dp->ins.twin_dist = 25.0f;
        dp->randseed = shRandI() ^ shRandI();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_insect", enSetInsect);
#endif


#line 129
void enKillAllInsect(void) {
    EnLOCAL_DATA* tp = enLocalWork.Data; // r5
    int i; // r6
    for (i = 0; i < ENEMY_MAX; i++, tp++) {
        if (tp->kind == EnKIND_INS) {   
            tp->kind = 0;
        }
    }
}


#line 141
void enWaitAllInsect(void) {
    EnLOCAL_DATA* tp = enLocalWork.Data; // r5
    int i; // r6
    if (enLocalWork.Status & (1 << 1)) {
        for (i = 0; i < ENEMY_MAX; i++, tp++) {
            if (tp->kind == EnKIND_INS && tp->type < 3) {   
                shVectorCopy(stay_pos, &tp->scp->pos);
                break;
            }
        }
    }
    for (i = 0; i < ENEMY_MAX; i++, tp++) {
        if (tp->kind == EnKIND_INS) {   
            tp->type = -1;
        }
    }
}



#line 162
SubCharacter* enINSGetSubCharacter(EnLOCAL_DATA* dp) {
    return (SubCharacter*) (MemShare_gp_data_buf + MCW_HEAP_ADDRESS) + ((int) dp - (int) &enLocalWork) / (int) sizeof(EnLOCAL_DATA);
}


#line 168
void enINSCtrlMain(EnLOCAL_DATA* dp) {
    void (*enCtrlINSSubFunc[5])(EnLOCAL_DATA*) = {
        enINSCtrlApproach,
        enINSCtrlAttack,
        enINSCtrlEscape,
        enINSCtrlChase,
        enINSCtrlStay 
    }; // r29+0x20

    enSetBattleTarget(dp, 1);

    if (dp->type == -1) {
        SubCharacter* scp; // r2
        scp = enINSGetSubCharacter(dp);
        shVectorCopy(&scp->pos, stay_pos);
        shVectorCopy(&scp->b_pos, stay_pos);
        dp->scp = scp;
        scp->battle.status = 0;
        dp->type = 0;
        enSetHP(dp, 1.0f, 1.0f);
        dp->sslv = 0;
    }

    enCtrlINSSubFunc[dp->slv](dp);

    // update animation
    enINSAnimeExec(dp);

    // update movement
    enMoveExec(dp);

    // draw
    enEfctDrawInsect(dp);
}



static void enINSCtrlApproach(EnLOCAL_DATA* dp) {
    float speed, d; // r29+0x40
    sceVu0FVECTOR tpos; // r29+0x30
    if (dp->sslv == 0) {
        enInitPath(&dp->path, dp->scp->rot.y);
        dp->ins.def_speed = dp->ins.move_speed = 500.0f;
        enSetTimer(dp, 15);
        ENEMY_NEXT_SUB_STEP();
        
        
        enSoundCall(18866, 0.6f, (float*) &dp->scp->pos);
    }

    shVectorCopy(tpos, enGetPlayerPos(dp));
    d = shVectorDistXz(&dp->scp->pos.x, tpos);
    (dp->ins).def_speed = (dp->ins).def_speed + shGetDT() * 250.0f;
    speed = (dp->ins).def_speed * SQRT(d / 500.0f);
    tpos[1] = -16800.0f;
    enINSMove(dp, tpos, 0.8f, TO_RAD(5), speed);
    if (d < 250.0f) {
        if (enCheckPlayerSprayNow()) {
            ENEMY_STEP(ENEMY_INS_STATE_ESCAPE);
        } else if (enReduceTimer(dp) < 1) {
            ENEMY_STEP(ENEMY_INS_STATE_ATTACK);
        }
    }
}

#define NYOOM 1500.0f
#line 235
static void enINSCtrlAttack(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR tpos; // r29+0x20
    shVectorCopy(tpos, enGetPlayerPos(dp));
    tpos[1] = -16800.0f;
    enINSMove(dp, tpos, 0.9f, TO_RAD(5), NYOOM);

    SeCallPosChange(18866, 0.6f, (float*) &dp->scp->pos, 0);

}


#line 247
static void enINSCtrlEscape(EnLOCAL_DATA* dp) {
    float* ppos = enGetPlayerPos(dp); // r2
    sceVu0FVECTOR vec; // r29+0x30
    if (dp->sslv == 0) {
        int i; // r5
        float d; // r29+0x40
        float dm = 0.0f;
        for (i = 0; i < sizeof(escape_point) / sizeof(sceVu0FVECTOR); i++) {
            d = shVectorDist(escape_point[i], &dp->scp->pos);
            if (d > dm) {
                dm = d;
                dp->type = i;
            }
        }
        ENEMY_NEXT_SUB_STEP();
    }
    shVectorCopy(vec, escape_point[dp->type]);
    if (dp->sslv == 2) {
        vec[1] = -15000.0f;
    }
    enINSMove(dp, vec, 0.8f, TO_RAD(5), 2500.0f);
    
    SeCallPosChange(18866, 0.6f, (float*) &dp->scp->pos, 0);

    if (dp->sslv == 1) {
        if (shVectorDist(vec, (float*)  &dp->scp->pos) >= 1500.0f) return;
        ENEMY_NEXT_SUB_STEP();
        return;
    } else if (dp->scp->pos.y > -15500.0f) {
        int i; // r16
        EnLOCAL_DATA* tp = enLocalWork.Data; // r17
        for (i = 0; i < ENEMY_MAX; i++, tp++) {
            if (tp->kind == EnKIND_INS) {
                enDeleteEnemy(tp);
            }
        }
        
        enSoundStop(18866);
    }

    return;
}


#define LEADER() ((EnLOCAL_DATA*) dp->ins.leader)
static void enINSCtrlChase(EnLOCAL_DATA* dp) {
    if (dp->sslv == 0) {
        enInitPath(&dp->path, dp->scp->rot.y + shSway1f(TO_RAD(-30), 0.1f));
        dp->ins.move_speed = 1500.0f;
    }
    if (LEADER()->slv == ENEMY_INS_STATE_ATTACK) {
        sceVu0FVECTOR tpos; // r29+0x20
        shVectorCopy(tpos, enGetPlayerPos(dp));
        tpos[1] = -16800.0f;
        enINSMove(dp, tpos, 0.8f, TO_RAD(5), 1500.0f);
    } else {
        
        enINSMove(dp, &LEADER()->scp->pos, 0.8f, TO_RAD(10), (shVectorDist((float*) &LEADER()->scp->pos, (float*) &dp->scp->pos) / 500.0f) * 1500.0f);
    }

}

#ifdef NON_MATCHING
#line 311
static void enINSCtrlStay(EnLOCAL_DATA* dp) {
    if (dp->sslv == 0) {
        enInitPath(&dp->path, dp->scp->rot.y + shSway1f(TO_RAD(-30), 0.1f));
        dp->ins.move_speed = 500.0f;
    }
    if (enCheckPlayerLight() && enCheckHitEyes(dp, &dp->scp->pos, enGetPlayerPos(dp)) < 0.0f) {
        sceVu0FVECTOR vec; // r29+0x20
        
        shSinCosV_Scale(vec, enGetPlayerAngle(dp), 600.0f);
        shAddVector(vec, enGetPlayerPos(dp), vec);
        vec[1] = dp->scp->b_pos.y;
        enINSMove(dp, vec, 0.9f, TO_RAD(10), 1500.0f);
    } else {
        enINSMove(dp, (float*) &dp->scp->b_pos, 0.9f, TO_RAD(5), 500.0f);
    }
    
    dp->vec[1] *= 3.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_insect", enINSCtrlStay);
#endif

#line 333
static void enINSMove(EnLOCAL_DATA* dp, float* target, float rot_rate, float rot_delta, float speed) {
    float a;
    sceVu0FVECTOR vec;
    (dp->ins).y_speed = (((dp->ins).y_speed + shSway1f(-250.0f, 0.1f)) \
                         - ((dp->scp->pos).y - target[1]) * 0.05f) * 0.95f;
    a = shAngleRegulate(enCalcDirection(target, (float*) &dp->scp->pos) - dp->path.angle);
    (dp->ins).rot_speed = a * 0.1f + (dp->ins).rot_speed * rot_rate;
    (dp->path).markangle = (dp->path).angle + (dp->ins).rot_speed;
    enMoveAngle(&dp->path, rot_delta);
    dp->ins.speed_add = ((dp->ins.speed_add + shSway1f(-250.0f, 0.1f)) \
                         - (dp->ins.move_speed  - speed) * 0.1f) * 0.98f;
    dp->ins.move_speed += dp->ins.speed_add;
    if (dp->ins.move_speed < 0.5f * speed) {
        dp->ins.move_speed = 0.5f * speed;
        dp->ins.speed_add = 0.0f;
    } else if (dp->ins.move_speed > 2.0f * speed) {
        dp->ins.move_speed = 2.0f * speed;
        dp->ins.speed_add = 0.0f;
    }
    shSinCosV_Scale(dp->vec, (dp->scp->rot.y = dp->path.angle), dp->ins.move_speed);
    dp->vec[1] = dp->ins.y_speed;
    shScaleVector(vec, dp->ins.rot_add, shGetDT());
    shAddVector(vec, dp->ins.view_rot, vec);
    dp->ins.view_rot[0] = shAngleRegulate(vec[0]);
    dp->ins.view_rot[1] = shAngleRegulate(vec[1]);
    dp->ins.view_rot[2] = shAngleRegulate(vec[2]);
    dp->ins.dist_add = (((dp->ins).dist_add + shSway1f(-5.0f, 0.1f)) - ((dp->ins).twin_dist - 25.0f) * 0.05f) * 0.95f;
    
    dp->ins.twin_dist += dp->ins.dist_add;
    enINSCheckWall(dp);
}

#ifdef NON_MATCHING
#line 367
static void enINSCheckWall(EnLOCAL_DATA* dp) {
    CL_VHIT_RESULT* res = &enLocalWork.HitResult; // r16
    sceVu0FVECTOR sp, ep, vec; // r29+0x30, r29+0x40, r29+0x50

    shSinCosV_Scale(vec, dp->scp->rot.y, 500.0f);
    shSubVector(sp, &dp->scp->pos, vec);
    shAddVector(ep, &dp->scp->pos, vec);
    clCheckHitEyesOnlyWall(res, sp, ep);
    if (res->kind == 1) {
        float d = shVectorDistXz(res->hobj.wall.cp, sp) - 50.0f; // r2
        if (d < 500.0f) {
            sceVu0FVECTOR tpos; // r29+0x60
            shNormalizeVector(res->hobj.wall.nl, vec);
            shScaleVector(vec, vec, 50.0f);
            shAddVector(tpos, res->hobj.wall.cp, vec);
            clCheckHitEyesOnlyWall(res, &dp->scp->pos, tpos);
            if (res->kind != 1) {
                shVectorCopyXyz(&dp->scp->pos, tpos);
                shVectorZero(dp->vec);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_insect", enINSCheckWall);
#endif


#line 393
static void enINSAnimeExec(EnLOCAL_DATA* dp) {
    int n = dp->anim_n; // r16
    n += (dp->anim_s * (int) (144000.0f * shGetDT()) >> 12);
    if (n >= 9600) {
        n -= 9600;
    }
    dp->anim_n = n;
    dp->anim = n / 2400;
}

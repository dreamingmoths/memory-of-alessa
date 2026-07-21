#include "Enemy/en_common.h"
#include "Enemy/en_effect.h"
#include "Enemy/en_arm.h"

#include "Chacter/sh_character_status.h"
#include "Chacter/sh_character_battle.h"
#include "Chacter/player_result.h"
#include "Chacter/sh2_character_manage.h"
#include "Chacter/m3_sc.h"

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

extern /* static */ int (* EnAnimeSetFunc[12])(struct SubCharacter*, int, int); 

extern /* static */ EnLOCAL_WORK enLocalWork; // size: 0x1E10, address: 0x5506A0

static inline float angle_add(struct EnPATH_DATA* p, float a0) { // what is the best place for this?
    float a1 = p->markangle;
    float temp_f0 = shAngleRegulate(a1 - p->angle);
    if (temp_f0 < -a0) {
        a1 = p->angle - a0;
    } else if (temp_f0 > a0) {
        a1 = p->angle + a0;
    }
    return shAngleRegulate(a1);
}

void enInitEnemy(void) {
    shQzero(&enLocalWork, sizeof(EnLOCAL_WORK));
    enLocalWork.Max3DSounds = 2;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enExecTask);

EnLOCAL_DATA* enEntryEnemy(int kind) {
    int i = 0;
    struct EnLOCAL_DATA* dp = &enLocalWork.Data[0];
    while (dp->kind) {
        if (++i >= EN_LOCAL_DATA_COUNT) {
            printf("enemy task empty.\n", i);
            return NULL;
        }
        dp++;
    }
    dp->kind = kind;
    dp->mlv = 0;
    return dp;
}

#ifdef NON_MATCHING
void enInitData(EnLOCAL_DATA* dp /* r18 */, SubCharacter* scp /* r17 */) {
    int kind; // r16    
    void (*enInitDataFunc[15])(EnLOCAL_DATA*) = {
        enSCUInitData,
        enMKNInitData,
        enTYUInitData,
        enREDInitData,
        enONIInitData,
        enNSEInitData,
        enIKEInitData,
        enPAPInitData,
        enEDBInitData,
        enARMInitData,
        enBOSInitData,
        enNIKInitData,
        enTY2InitData,
        enTY3InitData, 
        enINSInitData
    };    
        
    if ((dp == NULL) || (scp == NULL)) return;
    kind = dp->kind;
    ASSERT_ON_LINE(kind > EnKIND_NONE && kind <= EnKIND_INS, 372);

    enLocalWork.This = dp;
    shQzero(dp, sizeof(EnLOCAL_DATA));
    dp->kind = kind;
    dp->scp = scp;
    dp->path.markangle = dp->path.angle = dp->scp->rot.y;
    volatile_vec_copy(&dp->scp->b_pos, &dp->scp->pos);
    
    
    dp->scp->battle.status &= ~0x4F;
    
    
    enInitDataFunc[kind - 1](dp);
    
    
    dp->randseed = shRandI() ^ shRandI();
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enInitData)
#endif

void enDeleteEnemy(struct EnLOCAL_DATA* dp /* r2 */) {
    if (dp != NULL) {
        dp->kind = 0;
        fogEraseObj((dp - enLocalWork.Data) + 10);
    }
}

void enDummyCtrl(struct EnLOCAL_DATA* dp /* r2 */) {
    void* tmp; // r2 // nice function
}

int enTransID(int id /* r2 */) {
    switch (id) {
        case EN_SCU_CHARA_KIND:
            return 1;
        case EN_MKN_CHARA_KIND:
            return 2;
        case EN_TYU_CHARA_KIND:
            return 3;
        case EN_TY2_CHARA_KIND:
            return 13;
        case EN_TY3_CHARA_KIND:
            return 14;
        case EN_RED_CHARA_KIND:
            return 4;
        case EN_ONI_CHARA_KIND:
            return 5;
        case EN_NSE_CHARA_KIND:
        case EN_XOO_CHARA_KIND:
            return 6;
        case EN_IKE_CHARA_KIND:
            return 7;
        case EN_PAP_CHARA_KIND:
            return 8;
        case EN_LLL_EDI_CHARA_KIND:
            return 9;
        case EN_ARM_CHARA_KIND:
            return 10;
        case EN_BOS_CHARA_KIND:
            return 11;
        case ITEM_B_NIK_CHARA_KIND:
            return 12;
        default:
            return 0;
    }
}

int enGetWorldCondition(void) {
    if (sh2gfw_Get_NightOrDay()) {
        if (item.light_switch) {
            return BgIsOut(stage->glb_crd) ? 2 : 3;
        }
        return 4;
    }
    return 1;
}

int enGetPlace(void) {
    u_int ret = 0;
    int place = stage->glb_crd; // r2
    
    switch (place) {
        case 9:
            ret = 1;break;
        case 10:
            ret = 2;break;
        case 11:
            ret = 3;
        break;
        case 12:
            ret = 4;
        break;
        case 13:
            ret =5;
        break;
    }

    return ret;
}

int enGetStage(void) {
    int ret = 0;
    int s = stage->glb_crd; // r2
    switch (s) { 
        case 1:
            ret = 0;
            break;
        case 2:
            if (GET_GAME_FLAG(GAME_FLAG_251)) {
                ret = 2;
                break;
            }
            ret = 1;
            break;
        case 3:
            if (GET_GAME_FLAG(GAME_FLAG_251)) {
                ret = 4;
                break;
            }
            ret = 3;
            break;
        case 4:
            ret = 5;
            break;
    }
    return ret;
}

int enGetMode(void) {
    return playing.battle_level;
}

int enCheckDarkOrBright(struct SubCharacter* scp /* r2 */) {
    return sh2gfw_Check_CharaDarkOrBright(scp);
}

int enCheckDarkOrBrightPlayer(void) {
    return enCheckDarkOrBright(sh2jms.player);
}
 
int enCheckWater(EnLOCAL_DATA* dp) {
    float y = 3.4028235e38f; // r20
    switch (RoomName(0, dp->scp->pos.x, dp->scp->pos.z)) {
        case 0x63:
        case 0x62:
            y = -200.0f;
            break;
        case 0x80:
        case 0x85:
        case 0x7E:
        case 0x82:
            y = -180.0f;
            break;
        case 0x7A:
        case 0x7C:
            y = -165.0f;
            break;
        case 0xBB:
            y = 160.0f;
            break;
        case 0xB6:
            y = -280.0f;
            break;
        case 0xB7:
            y = -310.0f;
            break;
        case 0xAB:
            y = -320.0f;
            break;
        case 0xB8:
            y = -360.0f;
            break;
        case 0xB9:
            y = -350.0f;
            break;
    }

    return dp->scp->pos.y >= y;


}

void enSetBattleTarget(struct EnLOCAL_DATA* dp /* r16 */, u_int type /* r2 */) {
    dp->scp->battle.target = shBattleGetTargetHuman(dp->scp, type);
}

void enSetHP(struct EnLOCAL_DATA* dp /* r17 */, float hp /* r21 */, float endurance /* r20 */) {
    struct shBattleInfo* bi = &dp->scp->battle; // r16
    
    if ((dp->kind == 1) || (dp->kind == 2) || (dp->kind == 6)) {
        switch (enGetPlace()) {
            case 2:
                hp *= 1.5f;
                break;
            case 3:
                hp *= 1.5f;
                endurance *= 1.2f;
                break;
            case 4:
            case 5:
                hp *= 2.0f;
                endurance *= 1.5f;
                break;
        }
    }
    bi->hp_max = hp;
    bi->hp = hp;
    bi->hp_rate = 100.0f;
    dp->endurance = endurance;
    dp->endurance_max = endurance;
    bi->damage = 0.0f;
}

float enReduceHP(struct EnLOCAL_DATA* dp /* r2 */) {
    struct shBattleInfo* bi = &dp->scp->battle; // r16
    
    bi->hp -= bi->damage;
    if (bi->hp < 0.0f) {
        bi->hp = 0.0f;
    }
    dp->endurance -= bi->damage;
    if (dp->endurance < 0.0f) {
        dp->endurance = 0.0f;
    }
    bi->damage = 0.0f;
    bi->hp_rate = (100.0f * (bi->hp / bi->hp_max));
    return dp->endurance;
}

float enAddHP(struct EnLOCAL_DATA* dp /* r2 */, float n /* r29 */) {
    struct shBattleInfo* bi = &dp->scp->battle; // r16    
    if ((bi->hp += n) > bi->hp_max) {
        bi->hp = bi->hp_max;
    }
    dp->endurance = dp->endurance_max;
    if ((dp->endurance > bi->hp)) {
        dp->endurance = bi->hp;
    }
    bi->hp_rate = (100.0f * (bi->hp / bi->hp_max));
    return bi->hp;
}

float enAddEnduranceDT(struct EnLOCAL_DATA* dp /* r17 */, float n /* r20 */) {
    struct shBattleInfo* bi = &dp->scp->battle; // r16
    float en; // r29+0x40

    en = dp->endurance + (n * shGetDT());
    if (en > dp->endurance_max) {
        en = dp->endurance_max;
    }
    if (en > bi->hp) {
        en = bi->hp;
    }
    return dp->endurance = en;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckDamage);

int enCheckSpray(struct EnLOCAL_DATA* dp /* r2 */) {
    if ((dp->last_atk == 8) || (dp->last_atk == 9)) {
        return 1;
    }
    return 0;
}

void enResetDamage(struct EnLOCAL_DATA* dp /* r2 */) {
    dp->scp->battle.id = 0;
    dp->scp->battle.damage = 0.0f;
    dp->scp->battle.shock = 0.0f;
}

int enCheckDeath(EnLOCAL_DATA* dp) {
    if (dp->scp->battle.hp <= 0.0f) return 1;
    return 0;
}

void enSetHitBack(struct EnLOCAL_DATA* dp /* r2 */) {
    Vector4 vec; // r29
    struct shBattleInfo* bi = &dp->scp->battle; // r3
    vec_normalize((float*)&bi->vec, (float*)&vec);
    dp->hb_x = vec.x;
    dp->hb_z = vec.z;
    dp->hb_s = (2.0f * bi->shock);
    bi->shock = 0.0f;
}

int enCheckInstantDeath(struct EnLOCAL_DATA* dp /* r2 */) {
    if ((dp->last_atk >= 0x19) && (dp->last_atk < 0x23)) {
        return 1;
    }
    return 0;
}

void enSetSize(struct EnLOCAL_DATA* dp /* r2 */, float size /* r29 */, float tall /* r29 */, float center /* r29 */, float eye /* r29 */) {
    dp->size = dp->new_size = size;
    dp->tall = dp->new_tall = tall;
    dp->center_y = dp->new_center = center;    
    dp->eye_y = dp->new_eye = eye;
}

void enSetNewSize(struct EnLOCAL_DATA* dp /* r2 */, float size /* r29 */, float tall /* r29 */, float center /* r29 */, float eye /* r29 */) {
    dp->new_size = size;
    dp->new_tall = tall;
    dp->new_center = center;
    dp->new_eye = eye;
}

void enSetSeeLightStatus(struct EnLOCAL_DATA* dp /* r2 */, float center /* r29 */, float radius /* r29 */) {
    struct shBattleInfo* bi = &dp->scp->battle; // r2
    bi->look.center = center;
    bi->look.radius = radius;
    bi->feel.radius = 0.0f;
    bi->feel.center = 0.0f;
}

int enCheckSeeLight(struct EnLOCAL_DATA* dp /* r2 */) {
    return shBattleSeeHumanLight(dp->scp) == 1;
}

int enCheckAimedByHuman(struct EnLOCAL_DATA* dp /* r2 */) {
    return shBattleAimedByHuman(dp->scp);
}

int enCheckFinishedByHuman(struct EnLOCAL_DATA* dp /* r2 */) {
    return shBattleFinishedByHuman(dp->scp);
}

int enCheckNoDamageHuman(struct EnLOCAL_DATA* dp /* r2 */) {
    if (dp->scp->battle.target->kind != 0x105) {
        return shBattleNoDamageHumanJames();
    }
    
    return shBattleNoDamageHumanMaria();
}

void enAttackStart(struct EnLOCAL_DATA* dp /* r16 */) {
    shBattleAttackHitCheckInit(dp->scp);
    SET_BIT(dp->flag, 2);
}

int enAttackCheck(struct EnLOCAL_DATA* dp /* r2 */, int ID /* r2 */) {
    int result; // r16
    if (!(dp->flag & 0x4)) return 0;
    result = dp->scp->battle.atk_result;
    if (result != NULL) {
        dp->flag &= ~0x4;
        return result;
    }



    
    shBattleAttackHitCheckToHuman(dp->scp, ID);
    
    return result;
}

int enAttackCheckHug(struct EnLOCAL_DATA* dp /* r16 */, int ID /* r2 */)  {
    shBattleAttackHitCheckToHuman(dp->scp, ID);
    return dp->scp->battle.atk_result;
}

int enCheckHuggedPlayer(void) {
    return shBattleHuggedHuman();
}

int enCheckSleepIn(struct EnLOCAL_DATA* dp) {
    if ((!(dp->scp->battle.status & 0x400) || ((BgIsOut(0) != 0) && !(dp->p_dist <= 15000.0f))) && !(dp->scp->battle.status & 2)) {
        return 1;
    }
    return 0;
}

int enCheckSleepOut(struct EnLOCAL_DATA* dp) {
    if ((dp->scp->battle.status & 0x400) && ((BgIsOut(0) == 0) || (dp->p_dist < 7500.0f))) {
        return 1;
    }
    return 0;
}

void enSleepIn(struct EnLOCAL_DATA* dp /* r2 */) {
    dp->mlv = 2;
    dp->scp->battle.status &= ~1;
}

void enSleepOut(struct EnLOCAL_DATA* dp /* r2 */) {
    dp->mlv = 1;
    dp->scp->battle.status &= ~0x4C;
    dp->scp->battle.status |= 1;
}

void enKillCountUp(struct EnLOCAL_DATA* dp /* r2 */) {
    GameKillEnemyCountUp(dp->last_atk);
}

float* enGetPlayerPos(struct EnLOCAL_DATA* dp /* r2 */) {
    if (dp->scp->battle.target == sh2jms.player) {
        return &sh2jms.column_mov.p;
    }
    return (float*)&dp->scp->battle.target->pos;
}

float enGetPlayerDistance(EnLOCAL_DATA* dp) {
    return vec3_dist_xz_reverse(enGetPlayerPos(dp), &dp->scp->pos);
}

float enGetPlayerDirection(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec; // r29+0x20
    vu0_sub_vector(vec, enGetPlayerPos(dp), &dp->scp->pos);
    return shAtanV(&vec);
}

int enGetPlayerWeapon(void) {
    return (u_char) sh2jms.weapon;
}

int enCheckPlayerWeapon(void) {
    switch ((u_char)sh2jms.weapon) {
        case 1:
        case 2:
        case 3: return 1;            
    }
    return 0;
}

float enGetPlayerAngle(struct EnLOCAL_DATA* dp /* r2 */) {
    return dp->scp->battle.target->rot.y;
}

float enGetPlayerSize(void) {
    return sh2jms.column_mov.p[1][3];
}

int enCheckPlayerSound(struct EnLOCAL_DATA* dp /* r2 */) {
    return shBattleListenHumanSound(dp->scp, dp->scp->battle.target);
}

int enCheckPlayerCondition(struct EnLOCAL_DATA* dp /* r17 */) {
    int r = 0; // r16
    int w; // r2
    float a; // r29+0x30
    if (sh2jms.lock_on) {
        r |= 1;
    }
    w = enGetPlayerWeapon();
    if ((u_int)(w - 1) < 3) {
        r |= 2;
    }
    a = enCalcAngleDifference(enGetPlayerAngle(dp) + PI, dp->scp->rot.y);
    if (a >= QUARTER_TURN) {
        r |= 4;
    }
    return r;
}

int enCheckPlayerLight(void) {
    return item.light_switch;
}

int enCheckPlayerSprayNow(void) {
    if (((u_char)sh2jms.weapon == 4) && (sh2jms.upper_st_flg & 0x10000000) && ((sh2jms.attack_no == 8) || (sh2jms.attack_no == 9))) {
        return 1;
    }
    return 0;
}

int enGetSprayPower(void) {
    int n = playing.spray_pow; // r2
    if (n == 1) n = 0;        
    return n;
}

int enCheckPlayerBulletEmpty(void) {
    if ((item.number[4] != 0) || (item.number[5] != 0) || (item.number[6] != 0) || (item.number[7] != 0) || (item.number[8] != 0) || (item.number[9] != 0)) {
        return 0;
    }
    return 1;
}

int enCheckDeadPlayer(void) {
    return sh2jms.dead;
}

void enSetGameOver(void) {
    sh2jms.dead = 2;
}

void enFlagSetMoved(struct EnLOCAL_DATA* dp) {
    dp->scp->battle.status |= 1;
}

void enFlagResetMoved(struct EnLOCAL_DATA* dp) {
    dp->scp->battle.status &= ~1;
}

void enFlagSetLieDown(struct EnLOCAL_DATA* dp) {
    dp->scp->battle.status |= 4;
}

void enFlagResetLieDown(struct EnLOCAL_DATA* dp) {
    dp->scp->battle.status &= ~4;
}

void enFlagSetCritical(struct EnLOCAL_DATA* dp) {
    dp->scp->battle.status |= 8;
}

void enFlagResetCritical(struct EnLOCAL_DATA* dp) {
    dp->scp->battle.status &= ~8;
}

int enCheckCritical(struct EnLOCAL_DATA* dp) {
    return (dp->scp->battle.status & 8) != 0;
}

void enFlagSetNoDamage(struct EnLOCAL_DATA* dp) {
    dp->scp->battle.status |= 0x40;
}

void enFlagResetNoDamage(struct EnLOCAL_DATA* dp) {
    dp->scp->battle.status &= ~0x40;
}

void enFlagSetDead(struct EnLOCAL_DATA* dp) {
    dp->scp->battle.status |= 2;
}

void enFlagResetDead(struct EnLOCAL_DATA* dp) {
    dp->scp->battle.status &= ~2;
}

void enFlagSetRotFloor(struct EnLOCAL_DATA* dp) {
    dp->flag |= 0x800;
    dp->scp->status |= 0x80;
}

void enFlagResetRotFloor(struct EnLOCAL_DATA* dp) {
    dp->flag &= ~0x800;
    dp->trx = dp->trz = 0.0f;
}

void enFlagResetRotFloorJust(struct EnLOCAL_DATA* dp) {
    dp->flag &= ~0x800;
    dp->trx = dp->trz = 0.0f;
    dp->scp->rot.x = dp->scp->rot.z = 0.0f;
    dp->scp->status &= ~0x80;
}

void enFlagSetDisplay(struct EnLOCAL_DATA* dp) {
    dp->scp->status |= 0x410;
}

void enFlagResetDisplay(struct EnLOCAL_DATA* dp) {
    dp->scp->status &= ~0x410;
}

float enCalcDirection(float* pa, float* pb) {
    sceVu0FVECTOR vec; // r29+0x10
    vu0_sub_vector(vec, pa, pb);    
    return shAtanV(&vec);
}

float enCalcAngleDifference(float angle1, float angle2) {
    return float_abs(shAngleRegulate(angle1 - angle2));
}

float enCalcSpeedRate(float angle, float* mpos, float* tpos) { // not line matched
    float d; // r29+0x20
    d = (PI - float_abs(shAngleRegulate(enCalcDirection(tpos, mpos) - angle)));
    return 0.5f + (0.5f * (d / PI));    
}

void enMakeRotVector(float* vec, float* rot, float range) {
    sceVu0FMATRIX rmat; // r29+0x40
    vu0_unit_matrix(rmat);
    shRotMatrixZ(rmat, rmat, rot[2]); shRotMatrixY(rmat, rmat, rot[1]); shRotMatrixX(rmat, rmat, rot[0]);   
    vec_zero(vec);
    vec[2] = range;
    vu0_transform_vector(vec, rmat);
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckIntoScreen);

SubCharacter* enGetNearCharacter(EnLOCAL_DATA* dp) {
    float dist, d;
    int i;
    EnLOCAL_DATA* tp = enLocalWork.Data;
    SubCharacter* scp = shBattleGetTargetHuman(dp->scp, 0);
    dist = vec3_dist_xz_reverse(&scp->pos, &dp->scp->pos);   
    for (i = 0; i < EN_LOCAL_DATA_COUNT; i++, tp++) {
        if ((tp->kind != 0) && (tp != dp) && (tp->scp->battle.hp > 0.0f)) {
            d = vec3_dist_xz_reverse(&tp->scp->pos, &dp->scp->pos);
            if (d < dist) {
                dist = d;
                scp = tp->scp;
            }
        }
    }
    return scp;
}

int enCalcTimer(int t /* r2 */) {
    return (t * 60) / 60;
}

void enSetTimer(struct EnLOCAL_DATA* dp /* r16 */, int t /* r2 */) {
    if ((dp->timer = enCalcTimer(t) - 1) < 0) dp->timer = 0.0f;
    dp->flag &= ~0x2000;
}

int enReduceTimer(struct EnLOCAL_DATA* dp /* r18 */) {    
    int t = dp->timer; // r16
    int n = t / 60; // r17
    t -= shGetDF();
    if (t < 0) {
        t = 0;
    }
    if ((t / 60) < n) {
        dp->flag |= 0x2000;
    } else {
        dp->flag &= ~0x2000;
    }
    dp->timer = t;
    return t;
}

EnLOCAL_DATA* enGetNearOtherEnemy(EnLOCAL_DATA* dp) {
    int i; // r6
    EnLOCAL_DATA* tp; // r7
    EnLOCAL_DATA* rp; // r2
    float d; // r29    
    float m; // r29
   
    tp = enLocalWork.Data;
    rp = NULL;
    
    m = MAX_FLOAT;
    for (i = 0; i < EN_LOCAL_DATA_COUNT; i++, tp++) {
        if ((tp->kind != 0) && (tp != dp) && !(tp->scp->battle.status & 2)) {
            d = vec3_dist(&dp->scp->pos, &tp->scp->pos);
            if (d < m) {
                rp = tp;
                m = d;
            }
        }
    }    
    return rp;
}

void enCheckNearPlayer(EnLOCAL_DATA* dp, int* count, float* dist, float limit) {
    float d; // r29+0x60
    sceVu0FVECTOR vec; // r29+0x50
    if ((enCheckAimedByHuman(dp) == 0) || (d = vec3_dist_xz_reverse(&dp->scp->pos, enGetPlayerPos(dp)), (d > limit))) {
        
        *count = 0;
        return;
    }
    if (*count <= 0) {
        *count += shGetDF();
        if (*count > 0) {
            *dist = d;
        }
        return;
    }
    *count += shGetDF();
    if (60 < *count) {
        *count = -10;
        return;
    }
    if (d < *dist) {
        *dist = d;
    } else {
        d = *dist;
    }
    shSinCosV_Scale(vec, enGetPlayerAngle(dp), d);  
    vu0_add_vector(vec, enGetPlayerPos(dp), vec);
    dp->scp->pos.x = vec[0];
    dp->scp->pos.z = vec[2];
    vec_zero(dp->vec);
}

void enSetRadioVolume(struct EnLOCAL_DATA* dp /* r2 */) {
    if ((dp->kind == 4) && (dp->type == 0)) {
        dp->radio = 1.0f;
        return;
    }
    if ((dp->kind == 7) || (dp->kind == 9) || (dp->kind == 4) || (dp->kind == 5) || (dp->kind == 0xB) || !(dp->scp->status & 0x10)) {
        dp->radio = 0;
        return;
    }
    if (dp->scp->battle.status & 1) {
        if (dp->kind == 3) {
            dp->radio = 0.5f;
            return;
        }
        if (dp->scp->battle.status & 4) {
            dp->radio = 0.8;
            return;
        }
        dp->radio = 1.0f;
        return;
    }
    dp->radio = 0;
}

void enMoveAngle(struct EnPATH_DATA* p /* r16 */, float delta /* r20 */) {
    p->angle = angle_add(p, 60.0f * delta * shGetDT());
}

void enMoveAngleToPlayer(EnLOCAL_DATA* dp, float delta) {
    dp->path.markangle = enGetPlayerDirection(dp);
    enMoveAngle(&dp->path, delta);
    dp->scp->rot.y = dp->path.angle;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enMoveExec);

void enSetRotFloor(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec; // r29+0x30
    float inv_rot_y = -dp->scp->rot.y; // @note: not present in DWARF but cant match without
    shRotVectorY(&vec, &dp->scp->grnd_normal, inv_rot_y); // if u have a better match that would be nice
    dp->trx = -shAtan2(-vec[1], vec[2]);
    dp->trz = shAtan2(-vec[1], vec[0]);
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetHitColumn);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enIKETrans);

void enARMTrans(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec; // r29+0x20
    if ((dp == NULL) || (dp->scp->battle.status & 2) != 0) return;    
    volatile_vec_copy(&dp->scp->b_pos, &dp->scp->pos);    
    vu0_sub_vector(vec,&dp->scp->pos, dp->arm.old_pos);   
    vec_add_xyz(dp->arm.hand_pos, vec, dp->arm.hand_pos);
    if (dp->scu.dc >= 0) {
        enARMGetHandPos(vec, dp, dp->scu.dc);
        vec_sub_xyz(dp->arm.hand_pos, vec, vec);
        dp->scp->pos.x = vec[0];
        dp->scp->pos.z = vec[2];
    }
    
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enDyingExec);

void enWaitRegenerate(EnLOCAL_DATA* dp) {
    
    
    
    
    
    
    switch (dp->sslv) {
        case 0:
            if (!(dp->scp->battle.status & 0x400) || ((BgIsOut(0) != 0) && (dp->p_dist > 30000.0f))) {
                
                ENEMY_NEXT_SUB_STEP();          
            }
            break;
        case 1:
            if ((dp->scp->battle.status & 0x400) && ((BgIsOut(0) == 0) || (dp->p_dist < 15000.0f))) {
                
                enInitData(dp, dp->scp);
            }
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enFlyingFunc);

void enDeleteCharacter(struct EnLOCAL_DATA* dp /* r2 */) {
    shCharacter_Manage_Delete(dp->scp, dp->scp->kind, dp->scp->id);
}

void enInitPath(EnPATH_DATA* p, float angle) {
    p->markangle = p->angle =  shAngleRegulate(angle);
    p->step = 0;
    p->timer = 0;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetPath);

float enCheckPath(EnLOCAL_DATA* dp, float* tpos, float* mpos) {
    sceVu0FVECTOR sp, ep; // r29+0x10
    volatile_vec_copy(sp, mpos);
    volatile_vec_copy(ep, tpos);
    if (dp->flag & 0x40) {
        if (dp->flag & 0x100) {
            
            sp[1] = ep[1] = dp->scp->pos.y + dp->eye_y;
        } else {
            
            sp[1] = ep[1] = 50.0f + dp->scp->pos.y;
        }
    } else {
        if (dp->flag & 0x100) {
                
            sp[1] = ep[1] = dp->scp->pos.y - dp->eye_y;
        } else {
            
            sp[1] = ep[1] = dp->scp->pos.y - 50.0f;
        }
    } 
    return enCheckHitEyes(dp, sp, ep);
}

float enCheckPath2(EnLOCAL_DATA* dp, float* tpos, float* mpos) {
    sceVu0FVECTOR sp, ep;
    volatile_vec_copy(sp, mpos);
    volatile_vec_copy(ep, tpos);
    if (dp->flag & 0x40) {
        
        sp[1] = ep[1] = dp->scp->pos.y + dp->eye_y;
    } else {
        
        sp[1] = ep[1] = dp->scp->pos.y - dp->eye_y;
    }
    return enCheckHitEyes2(dp, sp, ep);
}

float enCheckForward(EnLOCAL_DATA* dp, float* pos, float* rot, float range) {
    sceVu0FVECTOR tp; // r29+0x30
    enMakeRotVector(tp, rot, range);
    vu0_add_vector(tp, pos, tp);
    return enCheckHitEyes(dp, pos, tp);
}


INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckHitEyes);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckHitEyes2);

float enCheckPlayerHitEyes(EnLOCAL_DATA* dp, float* ep) {
    CL_VHIT_RESULT* res = &enLocalWork.HitResult; // r16
    sceVu0FVECTOR p1; // r29+0x20    
    sceVu0FVECTOR p2; // r29+0x30


    volatile_vec_copy(p1, &dp->scp->battle.target->pos);
    volatile_vec_copy(p2, ep);
    p2[1] = p1[1] = dp->scp->battle.target->eye_y;
    clCheckHitEyes(res, (u_int) dp->scp->battle.target, p1, p2, 0);
    if (res->kind == 0) {
        return -vec3_dist_reverse(p2, p1);
    } else if (res->kind == 3) {
        return vec3_dist(p1, res->hobj.wall.nl);
    }
    return vec3_dist(p1, res->hobj.wall.cp);
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckFloor);

void enGetSkeletonVector(float* vec, EnLOCAL_DATA* dp, int n) {
    shSkelton* sp; // r5
    int i; // r7
    Matrix4* m; // not present in DWARF
    
    sp = dp->scp->sk_top;
    if (!(dp->scp->status & 0x10)) {
        vec_zero(vec);
        return;
    }
    i = 0;
    while ((i < n) && (sp->next != NULL)) {
        sp = sp->next;
        i++;
    }
    m = &sp->src_m;
    vec_copy_vu0(vec, m->d[3]);
}


void enGetSkeletonMatrix(float (*mat)[4], EnLOCAL_DATA* dp, int n) {
    shSkelton* sp; // r5
    int i; // r7

    sp = dp->scp->sk_top;
    
    if (!(dp->scp->status & 0x10)) {
        vec_zero(mat[0]);
        vec_zero(mat[1]);
        vec_zero(mat[2]);
        vec_zero(mat[3]);
        return;
    }    
    for (i = 0; (i < n) && (sp->next != NULL); i++) sp = sp->next;    
    mat_copy(mat, &sp->src_m);
}

#ifdef NON_MATCHING
int enGetDamageMotion(EnLOCAL_DATA* dp) { // @note: left like this since I dont know how those variables were used
    struct shBattleInfo* bi; // r16   
    int m; // r18
    int id; // r2
    int dd; // r2    
    float a; // r29+0x40
    
    int var_s2;
    int var_v0;

    bi = &dp->scp->battle;
    a = shAngleRegulate(shAtanV(&bi->vec) - dp->scp->rot.y);
    if (float_abs(a) > QUARTER_TURN) {
        var_v0 = 0;
    } else {
        var_v0 = 1;
    }

    switch (dp->last_atk) {
        case 2:
        case 1:
        case 36:
            var_s2 = 5;
            break;
        case 4:
        case 6:
            var_s2 = var_v0 + 6;
            break;
        case 23:
            bi->shock = 0.0f;
            dp->hb_s = 0.0f;
            /* fallthrough */
        case 12:
        case 13:
        case 15:
        case 16:
        case 38:
        case 39:
        case 40:
        case 44:
        case 46:
        case 50:
            if (a < 0.0f) {
                var_s2 = 8;
            } else {
                var_s2 = 9;
            }
            break;
        case 14:
        case 17:
            var_s2 = 0xA;
            break;
        case 18:
        case 41:
        case 49:
            var_s2 = var_v0 + 0xB;
            bi->shock = 0.0f;
            dp->hb_s = 0.0f;
            break;
        case 19:
        case 20:
            if (a < 0.0f) {
                var_s2 = 0x11;
            } else {
                var_s2 = 0x12;
            }
            break;
        case 21:
        case 22:
        case 45:
            var_s2 = 0x13;
            break;
        case 24:
            var_s2 = 0xD;
            bi->shock = 0.0f;
            dp->hb_s = 0.0f;
            break;
        default:
            var_s2 = 5;
            printf("Illegal damage type!(%d)\n", dp->last_atk);
            break;
    }
    return var_s2;
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetDamageMotion)
#endif

#ifdef NON_MATCHING
int enGetDownMotion(EnLOCAL_DATA* dp) {
    shBattleInfo* bi; // r16
    int m; // r17
    int id; // r2
    int dd; // r2 idk how this is used
    float a; // r29+0x40
    
    bi = &dp->scp->battle;
    a = shAngleRegulate(shAtanV(&bi->vec) - dp->scp->rot.y);
    if (float_abs(a) > QUARTER_TURN) {
        id = 0;
    } else {
        id = 1;
    }
       
    switch (dp->last_atk) {
        case 2:
        case 1: 
        case 36: 
            m = 0xE;
            break;
        case 4: 
        case 6: 
            m = id + 0xF;
            break;
        case 12:
        case 13:
        case 15:
        case 16:
        case 19:
        case 20:
        case 23:
        case 38:
        case 39:
        case 40:
        case 44:
        case 46:
        case 50:
            if (a < 0.0f) {
                m = 0x11;
            } else {
                m = 0x12;
            }
            break;
        case 14:
        case 17:
        case 21:
        case 22:
        case 45:
            m = 0x13;
            break;

        case 18:
        case 24:
        case 41:
        case 49:
            m = id + 0x14;
            bi->shock = 0.0f;
            dp->hb_s = 0.0f;
            break;
        default:
            m = 0xE;
            printf("Illegal down type!(%d)\n", dp->last_atk);
            break;
    }
    return m;
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetDownMotion)
#endif

#ifdef NON_MATCHING
int enGetLieDirection(int dm) {
    int m; // r16
    switch (dm) {
    case 14:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
        m = 0;
        break;
    case 15:
        m = 1;
        break;
    default:
        m = 0;
        printf("Illegal down motion!(%d)\n", dm);
    }
    return m;
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetLieDirection)
#endif

void enAnimeSet(struct EnLOCAL_DATA* dp /* r17 */, int anim /* r18 */, int id /* r16 */) {
    enAnimeRestart(dp);
    dp->anim = anim;
    dp->anim_s = 0x1000;
    dp->anim_n = 0;
    dp->anim_loop = 0;
    dp->anim_step = 0;
    dp->flag &= ~0x4080;
    if (EnAnimeSetFunc[dp->kind] != NULL) {
        EnAnimeSetFunc[dp->kind](dp->scp, id, !(dp->flag & 0x8000) ? 1 : 0);
    }
    enSetTrans(dp);
    dp->tx2 = dp->tx;
    dp->tz2 = dp->tz;
}

void enAnimeSetDirectFrame(EnLOCAL_DATA* dp, int anim, int id, int frame) {
    AnimeInfo* ai; // r2    
    enAnimeRestart(dp);
    dp->anim = anim;
    dp->anim_s = 0x1000;
    dp->anim_loop = 0;
    dp->anim_step = 0;
    dp->flag &= ~0x4080;
    EnAnimeSetFunc[dp->kind](dp->scp, id, 0);
    ai = shCharacterAnimeGetInfo(dp->scp);
    if (frame < 0) {
        frame = ai->frame + frame;
        if (frame < 0) frame = 0;
    } else {
        if (frame >= ai->frame) frame = ai->frame - 1;
    }
    shCharacterAnimeFrameSet(dp->scp, frame);
    dp->anim_n = frame * 0x960;
    
    enSetTrans(dp);
    dp->tx2 = dp->tx;
    dp->tz2 = dp->tz;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enAnimeExec);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetTrans);

void enSetTransN(EnLOCAL_DATA* dp, int n) {
    sceVu0FVECTOR vec;
    enGetSkeletonVector(vec, dp, n);
    dp->tx = vec[0];
    dp->tz = vec[2];
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetTransWalk);

void enSetTransForward(EnLOCAL_DATA* dp, float s) {
    dp->tx = dp->tx2 = dp->tz2 = 0.0f;
    dp->tz = ((-s * dp->anim_s) / 4096.0f) * shGetDT();
}

void enAnimePause(struct EnLOCAL_DATA* dp /* r2 */) {
    dp->flag |= 1;
    shCharacterAnimePause(dp->scp);
}

void enAnimeRestart(struct EnLOCAL_DATA* dp /* r2 */) {
    dp->flag &= ~1;
    shCharacterAnimeRestart(dp->scp);
}

void enAnimeFrameSet(struct EnLOCAL_DATA* dp /* r2 */, u_short frame /* r2 */) {
    dp->anim_n = frame * 0x960;
    shCharacterAnimeFrameSet(dp->scp, frame);
}

void enAnimeReverse(struct EnLOCAL_DATA* dp /* r16 */) {
    AnimeInfo* ai = shCharacterAnimeGetInfo(dp->scp); // r2    
    if (dp->anim_s > 0) {
        dp->anim_s = -dp->anim_s;
        if (dp->anim_n == 0) {
            dp->anim_n = ai->frame * 0x960;
        }
    }
}

void enSetAnimeCount(struct EnLOCAL_DATA* dp /* r17 */, int count /* r16 */) {
    int limit = shCharacterAnimeGetInfo(dp->scp)->frame; // r2    
    dp->flag |= 0x80;
    dp->anim_step = (count * (limit * 0x960)) >> 0xC;
}

void enEfctBloodPool(struct EnLOCAL_DATA* dp /* r2 */) {
    float pos[4]; // r29+0x10   
    vec_copy_vu0(pos, (float*)&dp->scp->pos);    
    pos[1] -= 3.0f;
    HH_Effect_Object_Blood_Pool_Impact_Post(pos, 0);
}

void enEfctPoisonFog(float* pos /* r2 */, float* vec /* r2 */) {
    enEfctSetPoisonFog(pos, vec);
}

void enSetBlur(void) {
    sh2gfw_Set_FilterBlur(0x60); // 96
}

void enSetFadeOut(void) {
    sh2gfw_Set_FadeOut_Black(2.0f);
}

void enResetFilter(void) {
    sh2gfw_Reset_FilterCommand();
}

void enSoundCall(int num /* r2 */, float vol /* r29+0x10 */, float* pos /* r2 */) {
    SeCallPos(num, vol, pos, 0);
}

void enSoundCall3D(int num /* r2 */, float vol /* r29+0x10 */, float* pos /* r2 */) {
    SeCallPos(num, vol, pos, 1);
}

void enSoundStop(int num /* r2 */) {
    shSdSeStop(num);
}

void enSoundSetQueue(struct SubCharacter* scp /* r2 */, int num /* r2 */, float vol /* r29 */, float time /* r29 */) {
    EnSOUND_QUEUE* que; // r2
    
    if (enLocalWork.SoundQueueNum < 8) {
        que = &enLocalWork.SoundQueue[enLocalWork.SoundQueueNum++];      
        que->scp = scp;
        que->num = num;
        que->vol = vol;
        que->time = time;
    }
}

struct EnCOMMUNICATION* enSetCommunication(int kind, int type, float* pos, float dist, int time) {
    int i = 0;
    EnCOMMUNICATION* p = enLocalWork.Communication;
    
    while (p->kind != 0) {
        i++;
        if (i >= 8) return NULL;
        p++;
    }
    volatile_vec_copy(&p->pos, pos);
    p->kind = kind;
    p->type = type;
    p->dist = dist;
    if (p->time >= 0) {
        p->time = enCalcTimer(time);
    } else {
        p->time = time;
    }
    enLocalWork.CommunicationNum++;
    return p;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCommunicateTribe);

void enResetForbiddenArea(void) {
    enLocalWork.ForbiddenNum = 0;
}

#ifdef NON_MATCHING
#define EN_FORBIDDENAREA_MAX 2
void enSetForbiddenArea(float x0, float z0, float x1, float z1) {
    int n = enLocalWork.ForbiddenNum; // r16   
    FJ_ASSERT_ON_LINE(n < EN_FORBIDDENAREA_MAX, 2969);
    enLocalWork.ForbiddenArea[n].x0 = x0;
    enLocalWork.ForbiddenArea[n].z0 = z0;
    enLocalWork.ForbiddenArea[n].x1 = x1;
    enLocalWork.ForbiddenArea[n].z1 = z1;
    enLocalWork.ForbiddenNum = n + 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetForbiddenArea)
#endif

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enRoomForbiddenArea);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckForbiddenArea);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckForbiddenAreaSub);

void enEventDriven(int event /* r2 */, int id /* r2 */) {
    int i; // r3
    struct EnLOCAL_DATA* dp = enLocalWork.Data; // r6

    switch (event) {
        case 0:
            for (i = 0; i < EN_LOCAL_DATA_COUNT; i++, dp++) {
                if ((dp->kind != 0) && (dp->mlv != 0)) {
                    dp->mlv = 0;
                }
            }
            break;
        case 1:
            for (i = 0; i < EN_LOCAL_DATA_COUNT; i++, dp++) {
                if ((dp->kind != 0) && (dp->mlv != 1)) {
                    dp->mlv = 3;
                }
            }
            break;
        case 2:
            for (i = 0; i < EN_LOCAL_DATA_COUNT; i++, dp++) {
                if ((dp->kind == 2) && (dp->type == 6)) {
                    dp->type = 7;
                }
            }
            break;
        case 3:
            for (i = 0; i < EN_LOCAL_DATA_COUNT; i++, dp++) {
                if (dp->kind == 4) {
                    dp->mlv = 4;
                    dp->slv = 3;
                }
            }
            break;
        case 4:
            for (i = 0; i < EN_LOCAL_DATA_COUNT; i++, dp++) {
                if ((dp->kind == 5) && (dp->mlv == 4)) {
                    dp->slv = event;
                    dp->sslv = id;
                }
            }
            break;
    }
}

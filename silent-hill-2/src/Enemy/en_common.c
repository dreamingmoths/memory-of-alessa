#include "Enemy/en_common.h"
#include "Enemy/en_scu.h"
#include "sce/libvu0.h"
#include "Enemy/en_effect.h"
#include "Enemy/en_arm.h"

#include "Chacter/sh_character_status.h"
#include "Chacter/sh_character_battle.h"
#include "Chacter/player_result.h"
#include "Chacter/sh2_character_manage.h"
#include "Chacter/m3_sc.h"
#include "Chacter/m3_bos.h"
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
EnLOCAL_WORK enLocalWork; // size: 0x1E10, address: 0x5506A0

static int (* EnAnimeSetFunc[12])(SubCharacter*, int, int) = {
    NULL,
    shCharacterEnemySCUAnimeSetP,
    shCharacterEnemyMKNAnimeSetP,
    shCharacterEnemyTYUAnimeSetP,
    shCharacterEnemyREDAnimeSetP,
    shCharacterEnemyONIAnimeSetP,
    shCharacterEnemyNSEAnimeSetP,
    shCharacterEnemyIKEAnimeSetP,
    shCharacterEnemyPAPAnimeSetP,
    shCharacterEnemyEDBAnimeSetP,
    shCharacterEnemyARMAnimeSetP,
    shCharacterEnemyBOSAnimeSetP
};

static EnSKELETON_DATA EnSkeletonData[16] = { // size: 0x80, address: 0x2A9B60
    {
        /* .num1 */ 0,
        /* .num2 */ 0,
        /* .float */ 0,
    },
    {
        /* .num1 */ 20,
        /* .num2 */ 21,
        /* .float */ 0.75,
    },
    {
        /* .num1 */ 15,
        /* .num2 */ 16,
        /* .float */ 0.6,
    },
    {
        /* .num1 */ 0,
        /* .num2 */ 0,
        /* .float */ 0,
    },
    {
        /* .num1 */ 12,
        /* .num2 */ 13,
        /* .float */ 0.75,
    },
    {
        /* .num1 */ 12,
        /* .num2 */ 13,
        /* .float */ 0.75,
    },
    {
        /* .num1 */ 12,
        /* .num2 */ 13,
        /* .float */ 0.75,
    },
    {
        /* .num1 */ 0,
        /* .num2 */ 0,
        /* .float */ 0,
    },
    {
        /* .num1 */ 20,
        /* .num2 */ 24,
        /* .float */ 0.75,
    },
    {
        /* .num1 */ 18,
        /* .num2 */ 19,
        /* .float */ 0.75
    },
    {
        /* .num1 */ 0,
        /* .num2 */ 0,
        /* .float */ 0,
    },
    {
        /* .num1 */ 0,
        /* .num2 */ 0,
        /* .float */ 0,
    },
    {
        /* .num1 */ 0,
        /* .num2 */ 0,
        /* .float */ 0,
    },
    {
        /* .num1 */ 0,
        /* .num2 */ 0,
        /* .float */ 0,
    },
    {
        /* .num1 */ 0,
        /* .num2 */ 0,
        /* .float */ 0,
    },
    {
        /* .num1 */ 0,
        /* .num2 */ 0,
        /* .float */ 0,
    },
};

static char EnSkeletonDataC[16] = {
    0,0,0,0,1,1,1,3,3,0,0,0,0,0,0,0,
};

static float EnBattleCollisionRate[16] = {
    0.0f, 0.8f, 0.8f, 2.0f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 1.0f, 0.8f, 1.0f, 2.0f, 2.0f, 0.0f
};

static inline float shAngleAdd(EnPATH_DATA* p, float a0) {
    float a1 = p->markangle;
    float temp_f0 = shAngleRegulate(a1 - p->angle);
    if (temp_f0 < -a0) {
        a1 = p->angle - a0;
    } else if (temp_f0 > a0) {
        a1 = p->angle + a0;
    }
    return shAngleRegulate(a1);
}

static inline float shAddRotX(SubCharacter* scp, float a0, float a2) {
    float r = a0;
    Vector4 *rot = &scp->rot;
    float temp_f0 = shAngleRegulate(r - rot->x);
    if (temp_f0 < -a2) {
        r = rot->x - a2;
    } else if (temp_f0 > a2) {
        r = rot->x + a2;
    }
    rot->x = shAngleRegulate(r);
}

static inline float shAddRotZ(SubCharacter* scp, float a0, float a2) {
    float r = a0;
    Vector4 *rot = &scp->rot;
    float* zz = &rot->z;
    float temp_f0 = shAngleRegulate(r - *zz);
    if (temp_f0 < -a2) {
        r = *zz - a2;
    } else if (temp_f0 > a2) {
        r = *zz + a2;
    }
    *zz = shAngleRegulate(r);
}

void enInitEnemy(void) {
    shQzero(&enLocalWork, sizeof(EnLOCAL_WORK));
    enLocalWork.Max3DSounds = 2;
}

#line 193
void enExecTask(void) {
    int i; /* r16 */
    EnLOCAL_DATA* dp; /* r17 */
    Vector4* p_pos; /* r2 */
    void (*enEnemyControlFunc[15])(EnLOCAL_DATA*) = {
        enSCUCtrlMain,
        enMKNCtrlMain,
        enTYUCtrlMain,
        enREDCtrlMain,
        enONICtrlMain,
        enNSECtrlMain,
        enIKECtrlMain,
        enPAPCtrlMain,
        enEDBCtrlMain,
        enARMCtrlMain,
        enBOSCtrlMain,
        enNIKCtrlMain,
        enTY2CtrlMain,
        enTY3CtrlMain,
        enINSCtrlMain,
    }; /* r29+0x40 */
    float dist[32]; /* r29+0x80 */ int num[32]; /* r29+0x100 */ int j; /* r5 */
    int max; /* r2 */ int max2; /* r3 */ int n; /* r6 */ float d; /* r1 */
    EnFORBIDDENAREA* fa; /* r4 */ EnCOMMUNICATION* cp; /* r4 */ EnSOUND_QUEUE* que; /* r17 */ int f; /* r18 */
    p_pos = &sh2jms.player->pos;
    
    
    
    
    
    dp = enLocalWork.Data;
    max = 0;
    for (i = 0; i < 32; i++, dp ++) {
        if (dp->kind > 0 && dp->kind < 16) {
            dp->p_dist = shVectorDist((float*) &dp->scp->pos, (float*) p_pos);dist[max] = dp->p_dist;
            num[max] = i;
            dp->flag &= ~0x1000;
            max++;
        }
    }
    max2 = max;
    if (enLocalWork.Max3DSounds < max) {max2 = enLocalWork.Max3DSounds;}
    for (i = 0; i < max2; i++) {
        d = dist[i];
        f = i;
        for (j = i + 1; j < max; j++) {
            if (dist[j] < d) {
                d = dist[j];
                f = j;
            }
        }
        enLocalWork.Data[num[f]].flag |= 0x1000;
        dist[f] = dist[i];
        num[f] = i;
    }

    
    
    enRoomForbiddenArea();
    
    fa = enLocalWork.ForbiddenArea;
    enLocalWork.Status &= ~1;
    for (i = 0; i < enLocalWork.ForbiddenNum; i++, fa++) {
        if (p_pos->x >= fa->x0 && p_pos->x  <= fa->x1 && p_pos->z >= fa->z0 && p_pos->z <= fa->z1) {
   
            enLocalWork.Status |= 1;
            break;
        } 
    }
    
    
    
    dp = enLocalWork.Data;
    for (i = 0; i < 32; i++, dp++) {
        if ((dp->kind > 0) && (dp->kind < 16)) {
            enLocalWork.This = dp;
            shPushRandSeed(dp->randseed);
            shBattleGetResult(dp->scp);
            enEnemyControlFunc[dp->kind - 1](dp);
            enSetRadioVolume(dp);
            dp->scp->battle.id = 0;
            dp->randseed = shPopRandSeed();
        }
    }
    
    enResetForbiddenArea();
    
    
    if (enLocalWork.CommunicationNum != 0) {
        cp = enLocalWork.Communication;
        for (i = 0; i < 8;i++,cp++) {
            if ((cp->kind != 0) && (cp->time > 0) && (--cp->time) <= 0) {
                cp->kind = 0;
                enLocalWork.CommunicationNum--;
            }
        }
    }
    
    
    if (enLocalWork.SoundQueueNum != 0) {
    
    
        for (i = 0; i < enLocalWork.SoundQueueNum; i++) {
            que = &enLocalWork.SoundQueue[i];
            n = 0;
            if (que->scp->kind == 0) {
                n = 1;
            } else if ((que->time -= shGetDT()) <= 0.0f) {
                enSoundCall(que->num, que->vol, (float*) &que->scp->pos.x);
                n = 1;
            }
            if (n != 0) {
                if(i != (--enLocalWork.SoundQueueNum)) {
    
                
                    *que = enLocalWork.SoundQueue[enLocalWork.SoundQueueNum];
                    i--;
                } else {break;}
            } 
        }}
    
    
    enLocalWork.This = NULL;
}

EnLOCAL_DATA* enEntryEnemy(int kind) {
    int i = 0;
    EnLOCAL_DATA* dp = enLocalWork.Data;
    while (dp->kind) {
        if (++i >= ENEMY_MAX) {
            printf("enemy task empty.\n", i);
            return NULL;
        }
        dp++;
    }
    dp->kind = kind;
    dp->mlv = 0;
    return dp;
}

#ifdef HOLY_CANDLE
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
    shVectorCopy(&dp->scp->b_pos, &dp->scp->pos);
    
    
    ENEMY_BATTLE_FLAG_UNSET((MOVED_FLAG | DEAD_FLAG | LIE_DOWN_FLAG | CRITICAL_FLAG | NO_DAMAGE_FLAG));

    
    
    enInitDataFunc[kind - 1](dp);
    
    
    dp->randseed = shRandI() ^ shRandI();
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enInitData);
void (*enInitDataFunc[15])(EnLOCAL_DATA*) = { enSCUInitData, enMKNInitData, enTYUInitData, enREDInitData, enONIInitData, enNSEInitData, enIKEInitData, enPAPInitData, enEDBInitData, enARMInitData, enBOSInitData, enNIKInitData, enTY2InitData, enTY3InitData, enINSInitData };
#endif

void enDeleteEnemy(EnLOCAL_DATA* dp /* r2 */) {
    if (dp != NULL) {
        dp->kind = 0;
        fogEraseObj((dp - enLocalWork.Data) + 10);
    }
}

void enDummyCtrl(EnLOCAL_DATA* dp /* r2 */) {
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

int enCheckDarkOrBright(SubCharacter* scp /* r2 */) {
    return sh2gfw_Check_CharaDarkOrBright(scp);
}

int enCheckDarkOrBrightPlayer(void) {
    return enCheckDarkOrBright(sh2jms.player);
}
 
int enCheckWater(EnLOCAL_DATA* dp) {
    float y = MAX_FLOAT; // r20
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

void enSetBattleTarget(EnLOCAL_DATA* dp /* r16 */, u_int type /* r2 */) {
    dp->scp->battle.target = shBattleGetTargetHuman(dp->scp, type);
}

void enSetHP(EnLOCAL_DATA* dp /* r17 */, float hp /* r21 */, float endurance /* r20 */) {
    shBattleInfo* bi = &dp->scp->battle; // r16
    
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

float enReduceHP(EnLOCAL_DATA* dp /* r2 */) {
    shBattleInfo* bi = &dp->scp->battle; // r16
    
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

float enAddHP(EnLOCAL_DATA* dp /* r2 */, float n /* r29 */) {
    shBattleInfo* bi = &dp->scp->battle; // r16
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

float enAddEnduranceDT(EnLOCAL_DATA* dp /* r17 */, float n /* r20 */) {
    shBattleInfo* bi = &dp->scp->battle; // r16
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

//#line 777
int enCheckDamage(EnLOCAL_DATA* dp /* r17 */) {
   shBattleInfo * bi = &dp->scp->battle; /* r16 */
   if (bi->damage == 0.0f) {
        dp->d_count = (char) 0;
        return 0;
    }
    if ((bi->status & 0x40) 
    || (bi->id >= 25 && bi->id < 35 && !(bi->status & 0x4))
    || (dp->kind == 1 && bi->id == 36) 
    || (dp->kind == 3 && bi->id == 51)) {    
        
        
        bi->damage = 0.0f;
        bi->shock = 0.0f;
        return 0;
    }
    if ((bi->id == 8) || (bi->id == 9)) {
        if (dp->kind != 1 && dp->kind != 2 
        && dp->kind != 6 && dp->kind != 3 
        && dp->kind != 15 && dp->kind != 8 
        && (enGetSprayPower() >= 0) && enGetSprayPower() < 2) {
            
            bi->damage = 0.0f;
            bi->shock = 0.0f;
            return 0;
        }
    }
    
    if (shPadGetPort() == 6 && shPadPress(0, 0x40000)) {
        dp->endurance = 0.0f;bi->hp_rate = 0.0f;bi->hp = 0.0f;
    }
    
    bi->damage /= itof(++dp->d_count);
    dp->last_atk = bi->id;
    return 1;
}

int enCheckSpray(EnLOCAL_DATA* dp /* r2 */) {
    if ((dp->last_atk == 8) || (dp->last_atk == 9)) {
        return 1;
    }
    return 0;
}

void enResetDamage(EnLOCAL_DATA* dp /* r2 */) {
    dp->scp->battle.id = 0;
    dp->scp->battle.damage = 0.0f;
    dp->scp->battle.shock = 0.0f;
}

int enCheckDeath(EnLOCAL_DATA* dp) {
    if (dp->scp->battle.hp <= 0.0f) return 1;
    return 0;
}

void enSetHitBack(EnLOCAL_DATA* dp /* r2 */) {
    Vector4 vec; // r29
    shBattleInfo* bi = &dp->scp->battle; // r3
    shNormalizeVector((float*)&bi->vec, (float*)&vec);
    dp->hb_x = vec.x;
    dp->hb_z = vec.z;
    dp->hb_s = (2.0f * bi->shock);
    bi->shock = 0.0f;
}

int enCheckInstantDeath(EnLOCAL_DATA* dp /* r2 */) {
    if ((dp->last_atk >= 0x19) && (dp->last_atk < 0x23)) {
        return 1;
    }
    return 0;
}

void enSetSize(EnLOCAL_DATA* dp /* r2 */, float size /* r29 */, float tall /* r29 */, float center /* r29 */, float eye /* r29 */) {
    dp->size = dp->new_size = size;
    dp->tall = dp->new_tall = tall;
    dp->center_y = dp->new_center = center;    
    dp->eye_y = dp->new_eye = eye;
}

void enSetNewSize(EnLOCAL_DATA* dp /* r2 */, float size /* r29 */, float tall /* r29 */, float center /* r29 */, float eye /* r29 */) {
    dp->new_size = size;
    dp->new_tall = tall;
    dp->new_center = center;
    dp->new_eye = eye;
}

void enSetSeeLightStatus(EnLOCAL_DATA* dp /* r2 */, float center /* r29 */, float radius /* r29 */) {
    shBattleInfo* bi = &dp->scp->battle; // r2
    bi->look.center = center;
    bi->look.radius = radius;
    bi->feel.radius = 0.0f;
    bi->feel.center = 0.0f;
}

int enCheckSeeLight(EnLOCAL_DATA* dp /* r2 */) {
    return shBattleSeeHumanLight(dp->scp) == 1;
}

int enCheckAimedByHuman(EnLOCAL_DATA* dp /* r2 */) {
    return shBattleAimedByHuman(dp->scp);
}

int enCheckFinishedByHuman(EnLOCAL_DATA* dp /* r2 */) {
    return shBattleFinishedByHuman(dp->scp);
}

int enCheckNoDamageHuman(EnLOCAL_DATA* dp /* r2 */) {
    if (dp->scp->battle.target->kind != 0x105) {
        return shBattleNoDamageHumanJames();
    }
    
    return shBattleNoDamageHumanMaria();
}

void enAttackStart(EnLOCAL_DATA* dp /* r16 */) {
    shBattleAttackHitCheckInit(dp->scp);
    ENEMY_FLAG_SET(ENEMY_FLAG_2);
}

int enAttackCheck(EnLOCAL_DATA* dp /* r2 */, int ID /* r2 */) {
    int result; // r16
    if (!ENEMY_FLAG_CHECK(ENEMY_FLAG_2)) return 0;
    result = dp->scp->battle.atk_result;
    if (result != NULL) {
        ENEMY_FLAG_UNSET(ENEMY_FLAG_2);
        return result;
    }



    
    shBattleAttackHitCheckToHuman(dp->scp, ID);
    
    return result;
}

int enAttackCheckHug(EnLOCAL_DATA* dp /* r16 */, int ID /* r2 */)  {
    shBattleAttackHitCheckToHuman(dp->scp, ID);
    return dp->scp->battle.atk_result;
}

int enCheckHuggedPlayer(void) {
    return shBattleHuggedHuman();
}

int enCheckSleepIn(EnLOCAL_DATA* dp) {
    if ((!ENEMY_BATTLE_FLAG_CHECK(BATTLE_STATS_FLAG_10) || ((BgIsOut(0) != 0) && (dp->p_dist > 15000.0f))) && !(ENEMY_BATTLE_FLAG_CHECK(DEAD_FLAG))) {
        return 1;
    }
    return 0;
}

int enCheckSleepOut(EnLOCAL_DATA* dp) {
    if (ENEMY_BATTLE_FLAG_CHECK(BATTLE_STATS_FLAG_10) && ((BgIsOut(0) == 0) || (dp->p_dist < 7500.0f))) {
        return 1;
    }
    return 0;
}

void enSleepIn(EnLOCAL_DATA* dp /* r2 */) {
    dp->mlv = 2;
    ENEMY_BATTLE_FLAG_UNSET(MOVED_FLAG);
}

void enSleepOut(EnLOCAL_DATA* dp /* r2 */) {
    dp->mlv = 1;
    ENEMY_BATTLE_FLAG_UNSET((LIE_DOWN_FLAG | CRITICAL_FLAG | NO_DAMAGE_FLAG));
    ENEMY_BATTLE_FLAG_SET(MOVED_FLAG);
}

void enKillCountUp(EnLOCAL_DATA* dp /* r2 */) {
    GameKillEnemyCountUp(dp->last_atk);
}

float* enGetPlayerPos(EnLOCAL_DATA* dp /* r2 */) {
    if (dp->scp->battle.target == sh2jms.player) {
        return &sh2jms.column_mov.p;
    }
    return (float*)&dp->scp->battle.target->pos;
}

float enGetPlayerDistance(EnLOCAL_DATA* dp) {
    return shVectorDistXz_reverse(enGetPlayerPos(dp), &dp->scp->pos);
}

float enGetPlayerDirection(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec; // r29+0x20
    shSubVector(vec, enGetPlayerPos(dp), &dp->scp->pos);
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

float enGetPlayerAngle(EnLOCAL_DATA* dp /* r2 */) {
    return dp->scp->battle.target->rot.y;
}

float enGetPlayerSize(void) {
    return sh2jms.column_mov.p[1][3];
}

int enCheckPlayerSound(EnLOCAL_DATA* dp /* r2 */) {
    return shBattleListenHumanSound(dp->scp, dp->scp->battle.target);
}

int enCheckPlayerCondition(EnLOCAL_DATA* dp /* r17 */) {
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

void enFlagSetMoved(EnLOCAL_DATA* dp) {
    ENEMY_BATTLE_FLAG_SET(MOVED_FLAG);
}

void enFlagResetMoved(EnLOCAL_DATA* dp) {
    ENEMY_BATTLE_FLAG_UNSET(MOVED_FLAG);
}

void enFlagSetLieDown(EnLOCAL_DATA* dp) {
    ENEMY_BATTLE_FLAG_SET(LIE_DOWN_FLAG);
}

void enFlagResetLieDown(EnLOCAL_DATA* dp) {
    ENEMY_BATTLE_FLAG_UNSET(LIE_DOWN_FLAG);
}

void enFlagSetCritical(EnLOCAL_DATA* dp) {
    ENEMY_BATTLE_FLAG_SET(CRITICAL_FLAG)
}

void enFlagResetCritical(EnLOCAL_DATA* dp) {
    ENEMY_BATTLE_FLAG_UNSET(CRITICAL_FLAG)
}

int enCheckCritical(EnLOCAL_DATA* dp) {
    return ENEMY_BATTLE_FLAG_CHECK(CRITICAL_FLAG) != 0;
}

void enFlagSetNoDamage(EnLOCAL_DATA* dp) {
    ENEMY_BATTLE_FLAG_SET(NO_DAMAGE_FLAG);
}

void enFlagResetNoDamage(EnLOCAL_DATA* dp) {
    ENEMY_BATTLE_FLAG_UNSET(NO_DAMAGE_FLAG);
}

void enFlagSetDead(EnLOCAL_DATA* dp) {
    ENEMY_BATTLE_FLAG_SET(DEAD_FLAG);
}

void enFlagResetDead(EnLOCAL_DATA* dp) {
    ENEMY_BATTLE_FLAG_UNSET(DEAD_FLAG);
}

void enFlagSetRotFloor(EnLOCAL_DATA* dp) {
    ENEMY_FLAG_SET(ENEMY_FLAG_11);
    dp->scp->status |= 0x80;
}

void enFlagResetRotFloor(EnLOCAL_DATA* dp) {
    ENEMY_FLAG_UNSET(ENEMY_FLAG_11);
    dp->trx = dp->trz = 0.0f;
}

void enFlagResetRotFloorJust(EnLOCAL_DATA* dp) {
    ENEMY_FLAG_UNSET(ENEMY_FLAG_11);
    dp->trx = dp->trz = 0.0f;
    dp->scp->rot.x = dp->scp->rot.z = 0.0f;
    dp->scp->status &= ~0x80;
}

void enFlagSetDisplay(EnLOCAL_DATA* dp) {
    dp->scp->status |= 0x410;
}

void enFlagResetDisplay(EnLOCAL_DATA* dp) {
    dp->scp->status &= ~0x410;
}

float enCalcDirection(float* pa, float* pb) {
    sceVu0FVECTOR vec; // r29+0x10
    shSubVector(vec, pa, pb);    
    return shAtanV(&vec);
}

float enCalcAngleDifference(float angle1, float angle2) {
    return shFloatAbs(shAngleRegulate(angle1 - angle2));
}

float enCalcSpeedRate(float angle, float* mpos, float* tpos) { // not line matched
    float d; // r29+0x20
    d = (PI - shFloatAbs(shAngleRegulate(enCalcDirection(tpos, mpos) - angle)));
    return 0.5f + (0.5f * (d / PI));    
}

void enMakeRotVector(float* vec, float* rot, float range) {
    sceVu0FMATRIX rmat; // r29+0x40
    shUnitMatrix(rmat);
    shRotMatrixZ(rmat, rmat, rot[2]); shRotMatrixY(rmat, rmat, rot[1]); shRotMatrixX(rmat, rmat, rot[0]);   
    shVectorZero(vec);
    vec[2] = range;
    shVectorTransform(vec, rmat);
}

int enCheckIntoScreen(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec; // r29+0x10
    shVectorCopyVu0(vec, &dp->scp->pos);    
    vec[1] -= dp->eye_y;
    shTransformVectorPerspective(vec, VbWvsMatrix.wsm);    
    if (shScreenClipF(vec)) {
        return 0;
    }
    return 1;
}

SubCharacter* enGetNearCharacter(EnLOCAL_DATA* dp) {
    float dist, d;
    int i;
    EnLOCAL_DATA* tp = enLocalWork.Data;
    SubCharacter* scp = shBattleGetTargetHuman(dp->scp, 0);
    dist = shVectorDistXz_reverse(&scp->pos, &dp->scp->pos);   
    for (i = 0; i < ENEMY_MAX; i++, tp++) {
        if ((tp->kind != 0) && (tp != dp) && (tp->scp->battle.hp > 0.0f)) {
            d = shVectorDistXz_reverse(&tp->scp->pos, &dp->scp->pos);
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

void enSetTimer(EnLOCAL_DATA* dp /* r16 */, int t /* r2 */) {
    if ((dp->timer = enCalcTimer(t) - 1) < 0) dp->timer = 0.0f;
    ENEMY_FLAG_UNSET(ENEMY_FLAG_13);
}

int enReduceTimer(EnLOCAL_DATA* dp /* r18 */) {    
    int t = dp->timer; // r16
    int n = t / 60; // r17
    t -= shGetDF();
    if (t < 0) {
        t = 0;
    }
    if ((t / 60) < n) {
        ENEMY_FLAG_SET(ENEMY_FLAG_13);
    } else {
        ENEMY_FLAG_UNSET(ENEMY_FLAG_13);
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
    for (i = 0; i < ENEMY_MAX; i++, tp++) {
        if ((tp->kind != 0) && (tp != dp) && !(tp->scp->battle.status & 2)) {
            d = shVectorDist(&dp->scp->pos, &tp->scp->pos);
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
    if ((enCheckAimedByHuman(dp) == 0) || (d = shVectorDistXz_reverse(&dp->scp->pos, enGetPlayerPos(dp)), (d > limit))) {
        
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
    shAddVector(vec, enGetPlayerPos(dp), vec);
    dp->scp->pos.x = vec[0];
    dp->scp->pos.z = vec[2];
    shVectorZero(dp->vec);
}

void enSetRadioVolume(EnLOCAL_DATA* dp /* r2 */) {
    if ((dp->kind == 4) && (dp->type == 0)) {
        dp->radio = 1.0f;
        return;
    }
    if ((dp->kind == 7) || (dp->kind == 9) || (dp->kind == 4) || (dp->kind == 5) || (dp->kind == 0xB) || !(dp->scp->status & 0x10)) {
        dp->radio = 0;
        return;
    }
    if (ENEMY_BATTLE_FLAG_CHECK(MOVED_FLAG)) {
        if (dp->kind == 3) {
            dp->radio = 0.5f;
            return;
        }
        if (ENEMY_BATTLE_FLAG_CHECK(LIE_DOWN_FLAG)) {
            dp->radio = 0.8;
            return;
        }
        dp->radio = 1.0f;
        return;
    }
    dp->radio = 0;
}

void enMoveAngle(EnPATH_DATA* p /* r16 */, float delta /* r20 */) {
    p->angle = shAngleAdd(p, 60.0f * delta * shGetDT());
}

void enMoveAngleToPlayer(EnLOCAL_DATA* dp, float delta) {
    dp->path.markangle = enGetPlayerDirection(dp);
    enMoveAngle(&dp->path, delta);
    dp->scp->rot.y = dp->path.angle;
}

#ifdef HOLY_CANDLE
#line 1624
void enMoveExec(EnLOCAL_DATA* dp /* r16 */) {
    /* r29+0x40 */ sceVu0FVECTOR vec; /* r29+0x50 */ sceVu0FVECTOR vec2;
    /* f20 */ float s; /* f3 */ float t; /* f3 */ float c; /* f3 */ float e; /* f21 */ float dt; /* r29+0x60 */ float hb;
    dt = 30.0f * shGetDT();
    
    if (dp->flag & (1 << ENEMY_FLAG_11)) {
        enSetRotFloor(dp);
    }
    shAddRotX(dp->scp, s = dp->trx, TO_RAD(5) * dt);
    shAddRotZ(dp->scp, s = dp->trz, TO_RAD(5) * dt);
    
    s = dp->size;
    if (dp->new_size != s) {
        if ((dp->new_size - s) < -25.0f) { s -= 25.0f; } else if ((dp->new_size - s) > 25.0f) { s += 25.0f; } else { s = dp->new_size; }
        dp->size = s;
    }
    
    t = dp->tall;
    if (dp->new_tall != t) {
        if ((dp->new_tall - t) < -(20.0f * dt)) { t -=  20.0f * dt; } else if ((dp->new_tall - t) > ( 20.0f * dt)) { t +=  20.0f * dt; } else { t = dp->new_tall; }
        dp->tall = t;
    }

    c = dp->center_y;
    if (dp->new_center != c) {
        if ((dp->new_center - c) < -(20.0f * dt)) { c -= (dp->new_center - c); } else if ((dp->new_center - c) > (20.0f * dt)) { c += (dp->new_center - c); } else { c = dp->new_center; }
        dp->center_y = c;
    }

    e = dp->eye_y;
    if (dp->new_eye != e) {
        if ((dp->new_eye - e) < -(20.0f * dt)) { e -= (20.0f * dt); } else if ((dp->new_eye - e) > (20.0f * dt)) { e += (20.0f * dt); } else { e = dp->new_eye; }
        dp->eye_y = e;
    }
    if (dp->scp->battle.status & 2) {
        if ((dp->kind != 7) && (dp->kind != 12) && (dp->kind != 5) && ((dp->kind != 8) || (dp->type != 1))) {
            
            
            return;
        }
    }
    if ((dp->kind != 7) && (dp->kind != 10) && (dp->kind != 15)) {
        
        vec_copy_reverse(&dp->scp->pos, &dp->scp->b_pos);
    }
    shScaleVector(&vec, &dp->vec, shGetDT());
    
    if ((dp->tx != dp->tx2) || (dp->tz != dp->tz2)) {
       shVectorZero(vec2);
        vec2[0] = dp->tx2 - dp->tx;
        vec2[2] = dp->tz2 - dp->tz;
        dp->tx2 = dp->tx;
        dp->tz2 = dp->tz;
        shRotVectorY(&vec2, &vec2, dp->scp->rot.y);
        shAddVectorXyz(&vec, &vec2, &vec);
    }
    
    if (dp->hb_s != 0.0f) {
        dp->hb_s *= 0.5f; 
        hb = dp->size; if (dp->size > (dp->size - 50.0f)) { hb = 50.0f; }
        shVectorZero(vec2);
        vec2[0] = dp->hb_x;
        vec2[2] = dp->hb_z;
        shScaleVector(&vec2, &vec2, hb);
        shAddVectorXyz(&vec, &vec2, &vec);
        if (dp->hb_s < 1.0f) { dp->hb_s = 0.0f; }
    }
    shAddVectorXyz(&dp->scp->pos, &vec, &vec);
    enCheckForbiddenArea(&dp->scp->pos.x, &vec, e);
    shVectorCopyVu0(&vec, &dp->scp->pos);
    shVectorZero(dp->vec);
    
    enSetHitColumn(dp);
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enMoveExec)
#endif

void enSetRotFloor(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec; // r29+0x30
    float inv_rot_y = -dp->scp->rot.y; // @note: not present in DWARF but cant match without
    shRotVectorY(&vec, &dp->scp->grnd_normal, inv_rot_y); // if u have a better match that would be nice
    dp->trx = -shAtan2(-vec[1], vec[2]);
    dp->trz = shAtan2(-vec[1], vec[0]);
}

#ifdef HOLY_CANDLE
#line 1712
void enSetHitColumn(EnLOCAL_DATA* dp /* r17 */) {
    CL_HITPOLY_COLUMN column; /* r29+0x40 */ CL_HITPOLY_COLUMN column2; /* r29+0x70 */ sceVu0FVECTOR vec; /* r29+0xA0 */
    float s; /* r20 */ float t; /* r21 */ float c; /* r22 */ float e; /* r23 */ float* pos; /* r2 */ int ID; /* r16 */
    FOG_OBJ_DATA* od; /* r2 */

    if ((dp->flag & 8) || ((dp->kind != 12) && !(dp->scp->status & 16))) {
        
        
        fogEraseObj(dp - enLocalWork.Data + 10);
        return;
    }
    pos =  &dp->scp->pos;
    s = dp->size;
    t = dp->tall;
    c = dp->center_y;
    e = dp->eye_y;
    column.kind = 1;
    column.shape = 3;
    column.weight = dp->weight;
    column.material = 12;
    shVectorCopyVu0(column.p[0], pos);
    shVectorZero(column.p[1]);
    if (dp->flag & 0x20) {
        column.p[0][1] += s;
        column.p[1][1] = pos[1] - s;
        column.p[1][3] = t;
        dp->scp->center_y = pos[1];
        dp->scp->eye_y = pos[1];
    } else if (dp->flag & 0x40) {
        if (!(dp->flag & 0x400)) {
            
            if (dp->kind == 12) {
                shScaleVector(vec, &(dp->arm.hand_pos), 0.8f);
            } else {
                enGetSkeletonVector(&vec, dp, EnSkeletonDataC[dp->kind]);
                shRotVectorY(&vec, &vec, dp->scp->rot.y);
            }
            column.p[0][0] += vec[0];
            column.p[0][2] += vec[2];
        }
        if (dp->kind == 10) {
            column.p[1][1] = 500.0f + pos[1];
            column.p[0][1] += 500.0f + t;
        } else {
            column.p[1][1] = pos[1];
            column.p[0][1] += t;
        }
        column.p[1][3] = s;
        dp->scp->center_y = pos[1] + c;
        dp->scp->eye_y = pos[1] + e;
    } else {
        if (!(dp->flag & 0x400)) {
            
            enGetSkeletonVector(&vec, dp, EnSkeletonDataC[dp->kind]);
            shRotVectorY(&vec, &vec, dp->scp->rot.y);
            column.p[0][0] += vec[0];
            column.p[0][2] += vec[2];
        }
        if ((dp->kind == 11) && (dp->slv < 5)) {
            column.p[0][1] = 400.0f + pos[1];
            column.p[1][1] = 400.0f + (pos[1] - t);
        } else {
            column.p[1][1] = pos[1] - t;
        }
        column.p[1][3] = s;
        dp->scp->center_y = pos[1] - c;
        dp->scp->eye_y = pos[1] - e;
    }
    column2 = column;
    column2.p[1][3] *= EnBattleCollisionRate[dp->kind];
    if (dp->scp->battle.status & 4) {
        column2.p[1][3] *= 1.5f;
    }
    if (dp->flag & 16) { column.p[1][3] = 0.0f; }
    if (dp->flag & 2) {
        clSetCharaHitColumn(&column, &column2, dp->scp, &enFlyingFunc);
    } else {
        clSetCharaHitColumn(&column, &column2, dp->scp, NULL);
        
        ID = dp - enLocalWork.Data + 10;
        od = fogGetObj(ID);
        column.p[0][1] = column.p[1][1];
        if (od != 0) {
            fogMoveObj(ID, &column.p);
            fogSetObjSize(ID, 0.8f * column.p[1][3]);
        } else {
            fogSetObj2(ID, &column.p, 0.8f * column.p[1][3]);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetHitColumn)
#endif

static inline void shRotMatrix(sceVu0FMATRIX out) {
    asm("\
        vsub.xyzw vf5, vf0, vf0\n\
        vsub.xyzw vf6, vf0, vf0\n\
        vmr32.xyzw vf4, vf0\n\
        vaddw.y vf5, vf0, vf0\n\
        vaddw.x vf6, vf0, vf0\n\
        sqc2 vf0, 0x30(%0)\n\
        sqc2 vf4, 0x20(%0)\n\
        sqc2 vf5, 0x10(%0)\n\
        sqc2 vf6, 0(%0)"
        : "+r"(out));
}

static inline void buildRotMatrix(sceVu0FMATRIX mat, float * rot) {
    shRotMatrixZ(mat, mat, rot[2]);
    shRotMatrixX(mat, mat, rot[0]);
    shRotMatrixY(mat, mat, rot[1]);
}

static inline void shIKEVectorTransform(sceVu0FVECTOR vec, sceVu0FMATRIX mat) {
    asm("\
        lqc2         vf4, 0x0(%0)\n\
        lqc2         vf5, 0x0(%1)\n\
        lqc2         vf6, 0x10(%1)\n\
        vmulax.xyzw  ACC, vf5, vf4x\n\
        lqc2         vf5, 0x20(%1)\n\
        vmadday.xyzw ACC, vf6, vf4y\n\
        lqc2         vf6, 0x30(%1)\n\
        vmaddaz.xyzw ACC, vf5, vf4z\n\
        vmaddw.xyzw  vf4, vf6, vf0w\n\
        sqc2         vf4, 0x0(%0)"
        : "+r"(vec): "r"(mat));
}

#line 1806
void enIKETrans(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec; // r29+0x30
    sceVu0FMATRIX rot; // r29+0x40
    if (dp != NULL) {
        shVectorCopy(&dp->scp->b_pos, &dp->scp->pos);
        if ((dp->slv == 0) || (dp->slv == 1)) {
            enGetSkeletonVector(dp->bos.target, dp, 0xC);
            return;
        }
        shVectorCopy(vec, &dp->oni);
        enGetSkeletonVector(dp->bos.target, dp, 0xC);
        shSubVector(vec, &dp->oni, vec);
        shUnitMatrix(rot);
        buildRotMatrix(rot, (float*) &dp->scp->rot);
        shIKEVectorTransform((float*) &vec, &rot);
        vec_sub_xyz(&dp->scp->pos, &vec, &dp->scp->pos);
    }
}

void enARMTrans(EnLOCAL_DATA* dp) {
    sceVu0FVECTOR vec; // r29+0x20
    if ((dp == NULL) || (ENEMY_BATTLE_FLAG_CHECK(DEAD_FLAG)) != 0) return;
    shVectorCopy(&dp->scp->b_pos, &dp->scp->pos);
    shSubVector(vec, &dp->scp->pos, dp->arm.old_pos);
    shAddVectorXyz(dp->arm.hand_pos, vec, dp->arm.hand_pos);
    if (dp->scu.dc >= 0) {
        enARMGetHandPos(vec, dp, dp->scu.dc);
        vec_sub_xyz(dp->arm.hand_pos, vec, vec);
        dp->scp->pos.x = vec[0];
        dp->scp->pos.z = vec[2];
    }
    
}

#line 1845
void enDyingExec(EnLOCAL_DATA* dp /* r16 */) {
    if (dp->sslv == 0) {
        if ((dp->scp->en_first_status != 13) && (dp->scp->en_first_status != 14)) {
            
            
            enEfctBloodPool(dp);
        }
        enFlagSetDead(dp);
        enFlagResetLieDown(dp);
        enFlagResetMoved(dp);
        fogEraseObj(dp - enLocalWork.Data + 10);
        if ((dp->kind == 1) || (dp->kind == 2) || (dp->kind == 6) || (dp->kind == 3)) {

            float regenerate_rate[5] = {0.0f, 0.05f, 0.2f, 0.6f, 0.8f}; // r29+0x30
            
            
            
            
            
            
            if (shRandF() < regenerate_rate[enGetMode()]) {
                dp->mlv = 6;
                return;
            }
        }
        ENEMY_NEXT_SUB_STEP();
    }





}

void enWaitRegenerate(EnLOCAL_DATA* dp) {
    
    
    
    
    
    
    switch (dp->sslv) {
        case 0:
            if (!ENEMY_BATTLE_FLAG_CHECK(BATTLE_STATS_FLAG_10) || ((BgIsOut(0) != 0) && (dp->p_dist > 30000.0f))) {
                
                ENEMY_NEXT_SUB_STEP();          
            }
            break;
        case 1:
            if (ENEMY_BATTLE_FLAG_CHECK(BATTLE_STATS_FLAG_10) && ((BgIsOut(0) == 0) || (dp->p_dist < 15000.0f))) {
                
                enInitData(dp, dp->scp);
            }
            break;
    }
}

//#line 1911
void enFlyingFunc(SubCharacter* scp /* r2 */) {
    void* tmp; // r2
}

void enDeleteCharacter(EnLOCAL_DATA* dp /* r2 */) {
    shCharacter_Manage_Delete(dp->scp, dp->scp->kind, dp->scp->id);
}

void enInitPath(EnPATH_DATA* p, float angle) {
    p->markangle = p->angle =  shAngleRegulate(angle);
    p->step = 0;
    p->timer = 0;
}

#ifdef HOLY_CANDLE
#line 1941
int enSetPath(EnLOCAL_DATA* dp /* r19 */, float* target /* r17 */, float* pos /* r18 */) {
    EnPATH_DATA* p = &dp->path; // r16
    sceVu0FVECTOR vec; /* r29+0x70 */ float dist; /* r20 */ float ma; /* r21 */ 
    float a; /* r29+0x90 */ float a1; /* r22 */ float a2; /* r24 */
    float d1; /* r23 */ float d2; /* r29+0x90 */ int k; /* r17 */
    /* r29+0x80 */ s_char timer[12] = {
        0, 
        30, 
        20,
        0,
        20,
        20,
        15,
        12,
        30,
        15,
        12,
        12
    };




    dist = enCheckPath(dp, target, pos);
    vec_sub(target, pos, vec);
    ma = shAtanV(&vec);
    if (dist < 0.0f) {
        p->markangle = ma;
        p->dist = -dist;
        p->step = 0;
        p->timer = 0;
        p->deadend = 0;
        return 0;
    }
    if (p->timer > 0) {
        p->timer -= shGetDF();
        return 1;
    }
    p->dist = dist;
    dist += 50.0f;
    switch (k = p->step) {
    case 0:
        p->step = 1;
        a1 = TO_RAD(15) + ma;
        shSinCosV_Scale(&vec, a1, dist);
        vec_add(pos, vec, vec);
        d1 = enCheckPath(dp, &vec, pos);
        a2 = ma - TO_RAD(15);
        shSinCosV_Scale(&vec, a2, dist);
        vec_add(pos, vec, vec);
        a = enCheckPath(dp, &vec, pos);
        if (d1 < 0.0f && a >= 0.0f) {
            ma = a1;
        } else if (d1 >= 0.0f && a < 0.0f) {
            ma = a2;
        } 
        else if (d1 >= 0.0f && a >= 0.0f && ((++p->deadend) >= 3)) {
            ma += PI;
            p->step = -1;
        } else {
            ma -= TO_RAD(1);
            p->step = 2;
        }
        
        break;
    case 1:
        a2 = shAngleRegulate(ma - p->angle);
        if (a2 == 0.0f) { a2 = TO_RAD(1); }
        if (shFloatAbs(a2) < TO_RAD(15)) { a1 = ma; }
        else { a1 = p->angle + TO_RAD(15) * float_sign(a2); };
        shSinCosV_Scale(&vec, a1, dist);
        vec_add(pos, vec, vec);
        d1 = enCheckPath(dp, &vec, pos);
        if (d1 < 0.0f) {
            ma = a1;
            p->timer = (dist = (timer[dp->kind] * 60) / 60.0f) * (1.0f + shSway1f(-0.5f, 0.5f));
            
            break;
        } 
        shSinCosV_Scale(&vec, ma, dist);
        vec_add(pos, vec, vec);
        d2 = enCheckPath(dp, &vec, pos);
        if (d2 < 0.0f) {
            p->timer = (timer[dp->kind] * 60) / 60.0f;
            break;
        } 
        if (d1 < d2) {
            a1 = ma;
            d1 = d2;
        }
        d1 = float_sign(d1); a2 = p->angle - TO_RAD(15) * a2;
        shSinCosV_Scale(&vec, a2, dist);
        vec_add(pos, vec, vec);
        if (enCheckPath(dp, &vec, pos) < 0.0f) {
            
            ma = a2;
            p->timer = (timer[dp->kind] * 60) / 60.0f;
        } else if (d1 < 0.0f) {
            ma = a1;
            p->timer = (timer[dp->kind] * 60) / 60.0f;
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
        a1 = ma + (TO_RAD(15) * k);
        shSinCosV_Scale(&vec, a1, dist);
        vec_add(pos, vec, vec);
        d1 = enCheckPath(dp, &vec, pos);
        a2 = ma - (TO_RAD(15) * k);
        shSinCosV_Scale(&vec, a2, dist);
        vec_add(pos, vec, vec);
        a = enCheckPath(dp, &vec, pos);
        if (d1 < 0.0f) {
            if (a < 0.0f) {
                if (++k >= 6) {
                    ma = a1;
                    k = 1;
                }
            } else {
                ma = a1;
                k = 1;
            }
        } else if (a < 0.0f) {
            ma = a2;
            k = 1;
        } else {
            if (d1 > a) {
                ma = a1;
            } else {
                ma = a2;
            }
            if (++k >= 6) {
                
                ma += PI;
                k = -1;
            }
        }
        p->step = k;
    }
    p->markangle = shAngleRegulate(ma);
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetPath)
char timer[12] = { 0, 30, 20, 0, 20, 20, 15, 12, 30, 15, 12, 12 };
#endif

float enCheckPath(EnLOCAL_DATA* dp, float* tpos, float* mpos) {
    sceVu0FVECTOR sp, ep; // r29+0x10
    shVectorCopy(sp, mpos);
    shVectorCopy(ep, tpos);
    if (ENEMY_FLAG_CHECK(ENEMY_FLAG_6)) {
        if (ENEMY_FLAG_CHECK(ENEMY_FLAG_8)) {
            
            sp[1] = ep[1] = dp->scp->pos.y + dp->eye_y;
        } else {
            
            sp[1] = ep[1] = 50.0f + dp->scp->pos.y;
        }
    } else {
        if (ENEMY_FLAG_CHECK(ENEMY_FLAG_8)) {
                
            sp[1] = ep[1] = dp->scp->pos.y - dp->eye_y;
        } else {
            
            sp[1] = ep[1] = dp->scp->pos.y - 50.0f;
        }
    } 
    return enCheckHitEyes(dp, sp, ep);
}

float enCheckPath2(EnLOCAL_DATA* dp, float* tpos, float* mpos) {
    sceVu0FVECTOR sp, ep;
    shVectorCopy(sp, mpos);
    shVectorCopy(ep, tpos);
    if (ENEMY_FLAG_CHECK(ENEMY_FLAG_6)) {
        
        sp[1] = ep[1] = dp->scp->pos.y + dp->eye_y;
    } else {
        
        sp[1] = ep[1] = dp->scp->pos.y - dp->eye_y;
    }
    return enCheckHitEyes2(dp, sp, ep);
}

float enCheckForward(EnLOCAL_DATA* dp, float* pos, float* rot, float range) {
    sceVu0FVECTOR tp; // r29+0x30
    enMakeRotVector(tp, rot, range);
    shAddVector(tp, pos, tp);
    return enCheckHitEyes(dp, pos, tp);
}


float enCheckHitEyes(EnLOCAL_DATA* dp, float* sp, float* ep) {
    CL_VHIT_RESULT* res = &enLocalWork.HitResult; // r16
    int f = 0; // r19
    sceVu0FVECTOR cp; // r29+0x50
    

    shVectorCopy(cp, ep);
    if (enCheckForbiddenArea(sp, cp, dp->size) != 0) f = 1;
    clCheckHitEyes(res, (u_int) dp->scp, sp, cp, 2);
    if (res->kind == 0) 
        if (f != 0) return shVectorDist(sp, cp);
        else return -shVectorDist(sp, cp);    
    if (res->kind == 3) {
        if (((res->hobj.chara.sc)->kind < 302) && !ENEMY_FLAG_CHECK(ENEMY_FLAG_9)) 
            
            return -shVectorDist(sp, &((res->hobj.chara.sc)->pos));
        
        return shVectorDist(sp, res->hobj.wall.nl);
    }
    
    return shVectorDist(sp, res->hobj.wall.cp);
}

float enCheckHitEyes2(EnLOCAL_DATA* dp, float* sp, float* ep) {
    CL_VHIT_RESULT* res = &enLocalWork.HitResult; // r16
    
    
    
    clCheckHitEyes(res, (u_int) dp->scp, sp, ep, 0);
    if (res->kind == 0) 
        return -shVectorDist(sp, ep);    
    if (res->kind == 3) {
        if (((res->hobj.chara.sc)->kind < 302) && !ENEMY_FLAG_CHECK(ENEMY_FLAG_9)) {
            
            return -shVectorDist(sp, &((res->hobj.chara.sc)->pos));
        }
        return shVectorDist(sp, res->hobj.wall.nl);
    }
    
    return shVectorDist(sp, res->hobj.wall.cp);
}

float enCheckPlayerHitEyes(EnLOCAL_DATA* dp, float* ep) {
    CL_VHIT_RESULT* res = &enLocalWork.HitResult; // r16
    sceVu0FVECTOR p1; // r29+0x20    
    sceVu0FVECTOR p2; // r29+0x30


    shVectorCopy(p1, &dp->scp->battle.target->pos);
    shVectorCopy(p2, ep);
    p2[1] = p1[1] = dp->scp->battle.target->eye_y;
    clCheckHitEyes(res, (u_int) dp->scp->battle.target, p1, p2, 0);
    if (res->kind == 0) {
        return -vec3_dist_reverse(p2, p1);
    } else if (res->kind == 3) {
        return shVectorDist(p1, res->hobj.wall.nl);
    }
    return shVectorDist(p1, res->hobj.wall.cp);
}

int enCheckFloor(float* pos) {
    CL_VHIT_RESULT* res = &enLocalWork.HitResult;
    sceVu0FVECTOR vec1, vec2;
    int m; // r3
    shVectorCopy(vec1, pos);
    shVectorCopy(vec2, pos);
    vec1[1] -= 100.0f;
    vec2[1] += 100.0f;
    clCheckHitEyesOnlyFloor(res, NULL, vec1, vec2);
    if (res->kind == 0) {
        return 0;
    }
    m = res->hobj.wall.pd->material;
    if ((m == 9) || (m == 11)) {
        return 2;
    }
    
    return 1;
}

void enGetSkeletonVector(float* vec, EnLOCAL_DATA* dp, int n) {
    shSkelton* sp; // r5
    int i; // r7
    Matrix4* m; // not present in DWARF
    
    sp = dp->scp->sk_top;
    if (!(dp->scp->status & 0x10)) {
        shVectorZero(vec);
        return;
    }
    i = 0;
    while (i < n && sp->next != NULL) {
        sp = sp->next;
        i++;
    }
    m = &sp->src_m;
    shVectorCopyVu0(vec, m->d[3]);
}


void enGetSkeletonMatrix(float (*mat)[4], EnLOCAL_DATA* dp, int n) {
    shSkelton* sp; // r5
    int i; // r7

    sp = dp->scp->sk_top;
    
    if (!(dp->scp->status & (1 << SCP_STATUS_BIT_4))) {
        shVectorZero(mat[0]);
        shVectorZero(mat[1]);
        shVectorZero(mat[2]);
        shVectorZero(mat[3]);
        return;
    }    
    for (i = 0; (i < n) && (sp->next != NULL); i++) sp = sp->next;    
    shMatrixCopy(mat, &sp->src_m);
}

#ifdef HOLY_CANDLE
int enGetDamageMotion(EnLOCAL_DATA* dp) { // @note: left like this since I dont know how those variables were used
    shBattleInfo* bi; // r16   
    int m; // r18
    int id; // r2
    int dd; // r2    
    float a; // r29+0x40
    
    int var_s2;
    int var_v0;

    bi = &dp->scp->battle;
    a = shAngleRegulate(shAtanV(&bi->vec) - dp->scp->rot.y);
    if (shFloatAbs(a) > QUARTER_TURN) {
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

#ifdef HOLY_CANDLE
int enGetDownMotion(EnLOCAL_DATA* dp) {
    shBattleInfo* bi; // r16
    int m; // r17
    int id; // r2
    int dd; // r2 idk how this is used
    float a; // r29+0x40
    
    bi = &dp->scp->battle;
    a = shAngleRegulate(shAtanV(&bi->vec) - dp->scp->rot.y);
    if (shFloatAbs(a) > QUARTER_TURN) {
        id = 0;
    } else {
        id = 1;
    }
       
    switch (dp->last_atk) {
        case 2:
        case 1: 
        case 36: 
            m = 14;
            break;
        case 4: 
        case 6: 
            m = id + 15;
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
                m = 17;
            } else {
                m = 18;
            }
            break;
        case 14:
        case 17:
        case 21:
        case 22:
        case 45:
            m = 19;
            break;

        case 18:
        case 24:
        case 41:
        case 49:
            m = id + 20;
            bi->shock = 0.0f;
            dp->hb_s = 0.0f;
            break;
        default:
            m = 14;
            printf("Illegal down type!(%d)\n", dp->last_atk);
            break;
    }
    return m;
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetDownMotion)
#endif

#ifdef HOLY_CANDLE
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

void enAnimeSet(EnLOCAL_DATA* dp /* r17 */, int anim /* r18 */, int id /* r16 */) {
    enAnimeRestart(dp);
    dp->anim = anim;
    dp->anim_s = 0x1000;
    dp->anim_n = 0;
    dp->anim_loop = 0;
    dp->anim_step = 0;
    ENEMY_FLAG_UNSET((ENEMY_FLAG_14 | ENEMY_FLAG_7));
    if (EnAnimeSetFunc[dp->kind] != NULL) {
        EnAnimeSetFunc[dp->kind](dp->scp, id, !ENEMY_FLAG_CHECK(ENEMY_FLAG_15) ? 1 : 0);
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
    ENEMY_FLAG_UNSET((ENEMY_FLAG_14 | ENEMY_FLAG_7));
    EnAnimeSetFunc[dp->kind](dp->scp, id, 0);
    ai = shCharacterAnimeGetInfo(dp->scp);
    if (frame < 0) {
        frame = ai->frame + frame;
        if (frame < 0) frame = 0;
    } else {
        if (frame >= ai->frame) frame = ai->frame - 1;
    }
    shCharacterAnimeFrameSet(dp->scp, frame);
    dp->anim_n = frame * 2400;
    
    enSetTrans(dp);
    dp->tx2 = dp->tx;
    dp->tz2 = dp->tz;
}

#line 2554
void enAnimeExec(EnLOCAL_DATA * dp /* r22 */, EnANIME_DATA * pa /* r21 */, short anm_none /* r20 */) {
    int n; /* r16 */ int limit; /* r17 */ int speed; /* r18 */ int loop; /* r2 */ int f; /* r19 */
    AnimeInfo* ai; /* r2 */
    if (ENEMY_FLAG_CHECK(ENEMY_FLAG_0) || dp->anim_n < 0) { return; }
    pa += dp->anim;
    ai = shCharacterAnimeGetInfo(dp->scp);
    limit = ai->frame;
    speed = ai->speed;
    pa->Anime != anm_none ? 0 : 0; // TODO: figure out the proper source

    
    
    
    f = shCharacterAnimeFrameGet(dp->scp) * 2400;
    if (ENEMY_FLAG_CHECK(ENEMY_FLAG_14)) {
        n = f;
        ENEMY_FLAG_UNSET(ENEMY_FLAG_14);
    } else {
        n = dp->anim_n;
    } // TODO: Figure out cast on below line
    n += ((dp->anim_s * ((ftoi(144000.0f * shGetDT()) * shAbs(speed)) >> 0xC)) >> 0xC);
    if (ENEMY_FLAG_CHECK(ENEMY_FLAG_7)) {
        if (dp->anim_s > 0) {
            if (n >= dp->anim_step) {
                n = -1;
            }    
        } 
        else if (n <= -dp->anim_step) {
            n = -1;
        }
    
    } 
    else if (pa->Loop == 0 && pa->Anime != anm_none) {
        if (f == 0) {
            ENEMY_FLAG_SET(ENEMY_FLAG_14);
        } else if (n >= 24000 && shCharacterAnimeIsEnd(dp->scp) != 0) {
            
            n = -1;
        }
    } 
    else if (dp->anim_s > 0) {
        if (n >= (limit * 2400)) {
            if (pa->Loop != 0) {
                n = 0;
                ENEMY_FLAG_SET(ENEMY_FLAG_14);
                dp->anim_loop++;
            } else {
                n = -1;
            }
        } else if (f == 0) {
            ENEMY_FLAG_SET(ENEMY_FLAG_14);
        }
    }
    else if (n <= 0) {
        if (pa->Loop != 0) {
            if (f != 0) {
                n = limit * 2400;
                dp->anim_loop++;
            } else {
                n = 0;
            }
            ENEMY_FLAG_SET(ENEMY_FLAG_14);
        } else {
            n = -1;
        }
    } else if (f == 0) {
        ENEMY_FLAG_SET(ENEMY_FLAG_14);
    }

    
    dp->anim_n = n;
    
   shCharacterAnimeSpeedAdd(dp->scp, ((speed * dp->anim_s) / 4096) - speed);
}

#line 2633
void enSetTrans(EnLOCAL_DATA* dp /* r16 */) {
    EnSKELETON_DATA* sd = &EnSkeletonData + dp->kind; // r17
    float vec1[4]; /* r29+0x30 */ float vec2[4]; /* r29+0x40 */
    if (sd->rate != 0.0f) {
        enGetSkeletonVector(vec1, dp, sd->num1);
        enGetSkeletonVector(vec2, dp, sd->num2);
        vec_add(vec1, vec2, vec1);
        vec_scale(sd->rate, vec1, vec1);
        dp->tx = vec1[0];
        dp->tz = vec1[2];
    }
}

void enSetTransN(EnLOCAL_DATA* dp, int n) {
    sceVu0FVECTOR vec;
    enGetSkeletonVector(vec, dp, n);
    dp->tx = vec[0];
    dp->tz = vec[2];
}

#line 2660
void enSetTransWalk(EnLOCAL_DATA* dp /* r17 */) {
    sceVu0FVECTOR vec[2]; /* r29+0x40 */ int sn[2]; /* r29+0x68 */ int d; /* r16 */ float od; /* r20 */
    
    
    od = dp->tz - dp->tz2;
    sn[0] = EnSkeletonData[dp->kind].num1;
    sn[1] = EnSkeletonData[dp->kind].num2;
    enGetSkeletonVector(vec[0], dp, sn[0]);
    enGetSkeletonVector(vec[1], dp, sn[1]);
    if ((d = dp->anim_step - 1) < 0) {
        d = ((vec[0][1] > vec[1][1]));
    }
    if ((vec[0][1 + d * 4] < vec[0][1 + (d ^ 1) * 4]) != 0) d ^= 1; 
    enSetTransN(dp, sn[0 + d]);
    dp->tx2 = 0; dp->tx = 0;
    if (dp->anim_step != d + 1) {
        dp->anim_step = d + 1;
        dp->tz2 = (dp->tz - od);
    }
}

void enSetTransForward(EnLOCAL_DATA* dp, float s) {
    dp->tx = dp->tx2 = dp->tz2 = 0.0f;
    dp->tz = ((-s * dp->anim_s) / 4096.0f) * shGetDT();
}

void enAnimePause(EnLOCAL_DATA* dp /* r2 */) {
    ENEMY_FLAG_SET(ENEMY_FLAG_0)
    shCharacterAnimePause(dp->scp);
}

void enAnimeRestart(EnLOCAL_DATA* dp /* r2 */) {
    ENEMY_FLAG_UNSET(ENEMY_FLAG_0)
    shCharacterAnimeRestart(dp->scp);
}

void enAnimeFrameSet(EnLOCAL_DATA* dp /* r2 */, u_short frame /* r2 */) {
    dp->anim_n = frame * 2400;
    shCharacterAnimeFrameSet(dp->scp, frame);
}

void enAnimeReverse(EnLOCAL_DATA* dp /* r16 */) {
    AnimeInfo* ai = shCharacterAnimeGetInfo(dp->scp); // r2    
    if (dp->anim_s > 0) {
        dp->anim_s = -dp->anim_s;
        if (dp->anim_n == 0) {
            dp->anim_n = ai->frame * 2400;
        }
    }
}

void enSetAnimeCount(EnLOCAL_DATA* dp /* r17 */, int count /* r16 */) {
    int limit = shCharacterAnimeGetInfo(dp->scp)->frame; // r2    
    ENEMY_FLAG_SET(ENEMY_FLAG_7)
    dp->anim_step = (count * (limit * 2400)) >> 0xC;
}

void enEfctBloodPool(EnLOCAL_DATA* dp /* r2 */) {
    float pos[4]; // r29+0x10   
    shVectorCopyVu0(pos, (float*)&dp->scp->pos);    
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

void enSoundSetQueue(SubCharacter* scp /* r2 */, int num /* r2 */, float vol /* r29 */, float time /* r29 */) {
    EnSOUND_QUEUE* que; // r2
    
    if (enLocalWork.SoundQueueNum < 8) {
        que = &enLocalWork.SoundQueue[enLocalWork.SoundQueueNum++];      
        que->scp = scp;
        que->num = num;
        que->vol = vol;
        que->time = time;
    }
}

EnCOMMUNICATION* enSetCommunication(int kind, int type, float* pos, float dist, int time) {
    int i = 0;
    EnCOMMUNICATION* p = enLocalWork.Communication;
    
    while (p->kind != 0) {
        i++;
        if (i >= 8) return NULL;
        p++;
    }
    shVectorCopy(&p->pos, pos);
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

EnCOMMUNICATION* enCommunicateTribe(int kind, float* pos) {
    EnCOMMUNICATION* mp; // r2
    EnCOMMUNICATION* p; // r2
    int i; // r6
    float d; // r29    
    float dist; // r1
   
    mp = NULL;
    p = enLocalWork.Communication;
    
    
    if (enLocalWork.CommunicationNum == 0) return NULL;    
    d = MAX_FLOAT;
    for (i = 0; i < 8; i++, p++) {
        if (p->kind == kind) {
            dist = shVectorDist(pos, p->pos);            
            if ((dist < p->dist) && (dist < d)) {
                d = dist;
                mp = p;
            }
        }       
    }
    return mp;
}

void enResetForbiddenArea(void) {
    enLocalWork.ForbiddenNum = 0;
}

#ifdef HOLY_CANDLE
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

#ifdef HOLY_CANDLE
#line 2981
void enRoomForbiddenArea(void) {
    int f = 0;
    switch(stage->glb_crd) {
    case 3:
        
        enSetForbiddenArea(-20000.0f, 40000.0f, -4000.0f, 57000.0f);
        
        enSetForbiddenArea(-100000.0f, 60000.0f, -80000.0f, 100000.0f);
        break;
    default:
        switch (RoomNameJms()) {
        case 48:
        case 101:
        case 187:
            f = 1;
            break;
        case 7:
            enSetForbiddenArea(83500.0f, -71300.0f, 85000.0f, -69600.0f);
            break;
        case 146:
            enSetForbiddenArea(-20800.0f, 18400.0f, -19200.0f, 22800.0f);
            break;
        case 153:
            enSetForbiddenArea(-64000.0f, 20800.0f, -63200.0f, 23500.0f);
            enSetForbiddenArea(-60750.0f, 20750.0f, -59250.0f, 25600.0f);
            break;
        case 160:
        case 178:
            enSetForbiddenArea(60000.0f, -19400.0f, 60750.0f, -16800.0f);
            enSetForbiddenArea(61200.0f, -19400.0f, 62000.0f, -16800.0f);
            break;
        case 163:
        case 181:
            enSetForbiddenArea(16000.0f, 20000.0f, 16800.0f, 22600.0f);
            break;
        case 168:
            enSetForbiddenArea(-20800, -60000.0f, -19200.0f, -55600.0f);
            break;
        }
    } 
    if (f != 0) {
        enLocalWork.Status |= 2;
    } else {
        enLocalWork.Status &= ~2;
        enLocalWork.ActiveEnemy = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enRoomForbiddenArea)
#endif

int enCheckForbiddenArea(float* sp, float* ep, float size) {
    int i, f; 
    f = 0;    
    for (i = 0; i < enLocalWork.ForbiddenNum; i++) {        
        f |= enCheckForbiddenAreaSub(&enLocalWork.ForbiddenArea[i], sp, ep, size);
    }

    return f;
}

#ifdef HOLY_CANDLE
int enCheckForbiddenAreaSub(EnFORBIDDENAREA* fa /* r2 */, float* sp /* r2 */, float* ep /* r2 */, float size /* r29 */) {
    float x0; // r1
    float z0; // r2
    float x1; // r3
    float z1; // r4
    float sx; // r5
    float sz; // r6
    float vx; // r7
    float vz; // r8
    float c; // r29
    int f; // r2

    x0 = fa->x0 - size;
    z0 = fa->z0 - size;
    x1 = fa->x1 + size;
    z1 = fa->z1 + size;
    sx = sp[0];
    sz = sp[2];
    if ((sx <= x0 && ep[0] <= x0) || ((sx >= x1) && (ep[0] >= x1)) 
        || (sz <= z0 && ep[2] <= z0) || ((sz >= z1) && (ep[2] >= z1))) {
        
        return 0;
    }
    f = 0;
    vx = ep[0] - sx;
    vz = ep[2] - sz;
    if (sx < (x0 + (2.0f * size))) {
        c = sz + ((vz * (x0 - sx)) / vx);
        if ((c >= z0) && (c <= z1)) {
            f = 1;
            ep[0] = x0;
            ep[2] = c;
            vx = c;
            vz = c - sz;
        }
    }
    if ((sx > (x1 - (2.0f * size)))) {
        c = sz + ((vz * (x1 - sx)) / vx);
        if ((c >= z0) && (c <= z1)) {
            f = 1;
            ep[0] = x1;
            ep[2] = c;
            vx = c;
            vz = c - sz;
        }
    }
    if (sz < (z0 + (2.0f * size))) {
        c = sx + ((vx * (z0 - sz)) / vz);
        if ((c >= x0) && (c <= x1)) {
            f = 1;
            ep[0] = c;
            ep[2] = z0;
            vx = c - sx;
            vz = c;
        }
    }
    if ((sz > (z1 - (2.0f * size)))) {
        c = sx + ((vx * (z1 - sz)) / vz);
        if ((c >= x0) && (c <= x1)) {
            f = 1;
            ep[0] = c;
            ep[2] = z1;
        }
    }
    return f;


}
#else
INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckForbiddenAreaSub);
#endif

void enEventDriven(int event /* r2 */, int id /* r2 */) {
    int i; // r3
    EnLOCAL_DATA* dp = enLocalWork.Data; // r6

    switch (event) {
        case 0:
            for (i = 0; i < ENEMY_MAX; i++, dp++) {
                if (dp->kind != 0 && dp->mlv != 0) {
                    dp->mlv = 0;
                }
            }
            break;
        case 1:
            for (i = 0; i < ENEMY_MAX; i++, dp++) {
                if (dp->kind != 0 && dp->mlv != 1) {
                    dp->mlv = 3;
                }
            }
            break;
        case 2:
            for (i = 0; i < ENEMY_MAX; i++, dp++) {
                if (dp->kind == 2 && dp->type == 6) {
                    dp->type = 7;
                }
            }
            break;
        case 3:
            for (i = 0; i < ENEMY_MAX; i++, dp++) {
                if (dp->kind == 4) {
                    dp->mlv = 4;
                    dp->slv = 3;
                }
            }
            break;
        case 4:
            for (i = 0; i < ENEMY_MAX; i++, dp++) {
                if (dp->kind == 5 && dp->mlv == 4) {
                    dp->slv = event;
                    dp->sslv = id;
                }
            }
            break;
    }
}

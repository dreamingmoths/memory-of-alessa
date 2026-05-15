#include "Enemy/en_common.h"
#include "shared/Fog/fog.h"
#include "Fog/fog.h"
#include "SH2_common/playing_info.h"
#include "sound/sh_sound.h"
#include "sound/sh_sd_call.h"
#include "Event/event.h"
#include "Event/item.h"
#include "Event/stg_name.h"
#include "GFW/sh2gfw_LightSet.h"
#include "Chacter_Draw/sh2gfw_model_light.h"
#include "Chacter/sh_character_status.h"
#include "SH2_common/sh2dt.h"

void enInitEnemy(void) {
    shQzero(&enLocalWork, sizeof(EnLOCAL_WORK));
    enLocalWork.Max3DSounds = 2;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enExecTask);

EnLOCAL_DATA* enEntryEnemy(int kind) {
    int i = 0;
    struct EnLOCAL_DATA* dp = &enLocalWork.Data[0];
    while (dp->kind) {
        if (++i >= 0x20) {
            printf("enemy task empty.\n", i);
            return NULL;
        }
        dp++;
    }
    dp->kind = kind;
    dp->mlv = 0;
    return dp;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enInitData);

void enDeleteEnemy(struct EnLOCAL_DATA* dp /* r2 */) {
    if (dp != NULL) {
        dp->kind = 0;
        fogEraseObj((dp - enLocalWork.Data) + 0xA);
    }
}

void enDummyCtrl(struct EnLOCAL_DATA* dp /* r2 */) {
    void* tmp; // r2 // nice function
}

int enTransID(int id /* r2 */) {
    switch (id) {
        case 0x200:
            return 1;
        case 0x201:
            return 2;
        case 0x202:
            return 3;
        case 0x20C:
            return 13;
        case 0x20D:
            return 14;
        case 0x208:
            return 4;
        case 0x209:
            return 5;
        case 0x207:
        case 0x20B:
            return 6;
        case 0x203:
            return 7;
        case 0x204:
            return 8;
        case 0x205:
            return 9;
        case 0x20A:
            return 10;
        case 0x206:
            return 11;
        case 0x421:
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

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetStage);

int enGetMode(void) {
    return playing.battle_level;
}

int enCheckDarkOrBright(struct SubCharacter* scp /* r2 */) {
    return sh2gfw_Check_CharaDarkOrBright(scp);
}

int enCheckDarkOrBrightPlayer(void) {
    return enCheckDarkOrBright(sh2jms.player);
}
 
INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckWater);

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

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enAddHP); // https://decomp.me/scratch/eoWuF 93%

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

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckSpray);

void enResetDamage(struct EnLOCAL_DATA* dp /* r2 */) {
    dp->scp->battle.id = 0;
    dp->scp->battle.damage = 0.0f;
    dp->scp->battle.shock = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckDeath);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetHitBack);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckInstantDeath);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetSize);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetNewSize);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetSeeLightStatus);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckSeeLight);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckAimedByHuman);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckFinishedByHuman);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckNoDamageHuman);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enAttackStart);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enAttackCheck);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enAttackCheckHug);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckHuggedPlayer);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckSleepIn);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckSleepOut);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSleepIn);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSleepOut);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enKillCountUp);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetPlayerPos);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetPlayerDistance);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetPlayerDirection);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetPlayerWeapon);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckPlayerWeapon);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetPlayerAngle);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetPlayerSize);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckPlayerSound);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckPlayerCondition);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckPlayerLight);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckPlayerSprayNow);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetSprayPower);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckPlayerBulletEmpty);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckDeadPlayer);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetGameOver);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enFlagSetMoved);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enFlagResetMoved);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enFlagSetLieDown);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enFlagResetLieDown);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enFlagSetCritical);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enFlagResetCritical);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckCritical);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enFlagSetNoDamage);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enFlagResetNoDamage);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enFlagSetDead);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enFlagResetDead);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enFlagSetRotFloor);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enFlagResetRotFloor);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enFlagResetRotFloorJust);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enFlagSetDisplay);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enFlagResetDisplay);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCalcDirection);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCalcAngleDifference);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCalcSpeedRate);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enMakeRotVector);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckIntoScreen);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetNearCharacter);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCalcTimer);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetTimer);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enReduceTimer);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetNearOtherEnemy);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckNearPlayer);

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

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enMoveAngle);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enMoveAngleToPlayer);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enMoveExec);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetRotFloor);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetHitColumn);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enIKETrans);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enARMTrans);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enDyingExec);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enWaitRegenerate);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enFlyingFunc);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enDeleteCharacter);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enInitPath);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetPath);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckPath);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckPath2);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckForward);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckHitEyes);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckHitEyes2);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckPlayerHitEyes);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckFloor);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetSkeletonVector);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetSkeletonMatrix);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetDamageMotion);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetDownMotion);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetLieDirection);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enAnimeSet);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enAnimeSetDirectFrame);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enAnimeExec);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetTrans);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetTransN);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetTransWalk);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetTransForward);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enAnimePause);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enAnimeRestart);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enAnimeFrameSet);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enAnimeReverse);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetAnimeCount);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enEfctBloodPool);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enEfctPoisonFog);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetBlur);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetFadeOut);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enResetFilter);

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

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetCommunication);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCommunicateTribe);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enResetForbiddenArea);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetForbiddenArea);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enRoomForbiddenArea);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckForbiddenArea);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckForbiddenAreaSub);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enEventDriven);

#include "en_common.h"

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enInitEnemy);

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

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enDeleteEnemy);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enDummyCtrl);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enTransID);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetWorldCondition);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetPlace);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetStage);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enGetMode);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckDarkOrBright);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckDarkOrBrightPlayer);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckWater);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetBattleTarget);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetHP);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enReduceHP);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enAddHP);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enAddEnduranceDT);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckDamage);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckSpray);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enResetDamage);

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

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetRadioVolume);

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

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSoundCall);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSoundCall3D);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSoundStop);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSoundSetQueue);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetCommunication);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCommunicateTribe);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enResetForbiddenArea);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enSetForbiddenArea);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enRoomForbiddenArea);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckForbiddenArea);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enCheckForbiddenAreaSub);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_common", enEventDriven);

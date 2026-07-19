#ifndef EN_COMMON_H
#define EN_COMMON_H

#include "sh2_common.h"
#include "Chacter/character.h"

#define SET_DP_STATE_LV(_dp, _slv, _sslv) do { \
    _dp->slv = _slv; \
    _dp->sslv = _sslv; \
} while (0)

#define ENEMY_STEP(_slv) SET_DP_STATE_LV(dp, _slv, 0)
#define ENEMY_NEXT_SUB_STEP() do { dp->sslv++; } while (0)
#define ENEMY_SUB_STEP(_sslv) do { dp->sslv = _sslv; } while (0)
#define ENEMY_MLV(_mlv) do { dp->mlv = _mlv; } while (0)

typedef struct EnSOUND_QUEUE {
    // total size: 0x10
    struct SubCharacter* scp; // offset 0x0, size 0x4
    int num;                  // offset 0x4, size 0x4
    float vol;                // offset 0x8, size 0x4
    float time;               // offset 0xC, size 0x4
} EnSOUND_QUEUE;

typedef struct EnFORBIDDENAREA {
    // total size: 0x10
    float x0; // offset 0x0, size 0x4
    float z0; // offset 0x4, size 0x4
    float x1; // offset 0x8, size 0x4
    float z1; // offset 0xC, size 0x4
} EnFORBIDDENAREA;

typedef struct EnLOCAL_WORK {
    // total size: 0x1E10
    struct EnLOCAL_DATA Data[32];            // offset 0x0, size 0x1C00
    struct EnCOMMUNICATION Communication[8]; // offset 0x1C00, size 0x100
    struct EnFORBIDDENAREA ForbiddenArea[2]; // offset 0x1D00, size 0x20
    struct EnSOUND_QUEUE SoundQueue[8];      // offset 0x1D20, size 0x80
    int CommunicationNum;                    // offset 0x1DA0, size 0x4
    int ForbiddenNum;                        // offset 0x1DA4, size 0x4
    int SoundQueueNum;                       // offset 0x1DA8, size 0x4
    u_int Status;                            // offset 0x1DAC, size 0x4
    struct EnLOCAL_DATA* This;               // offset 0x1DB0, size 0x4
    struct _CL_VHIT_RESULT HitResult;        // offset 0x1DC0, size 0x40
    int Max3DSounds;                         // offset 0x1E00, size 0x4
    int ActiveEnemy;                         // offset 0x1E04, size 0x4
} EnLOCAL_WORK;

// total size: 0x4
typedef struct EnANIME_DATA {
    // Members
    u_short Anime; // offset 0x0, size 0x2
    u_char Loop;   // offset 0x2, size 0x1
} EnANIME_DATA;

extern EnLOCAL_WORK enLocalWork; // size: 0x1E10, address: 0x5506A0

void enInitEnemy(void);
EnLOCAL_DATA* enEntryEnemy(int kind /* r2 */);
void enDeleteEnemy(EnLOCAL_DATA* dp /* r2 */);
void enDummyCtrl(EnLOCAL_DATA* dp /* r2 */);
int enTransID(int id /* r2 */);
int enGetWorldCondition(void);
int enGetPlace(void);
int enGetStage(void);
int enGetMode(void);
int enCheckDarkOrBright(SubCharacter* scp /* r2 */);
int enCheckDarkOrBrightPlayer(void);
void enSetBattleTarget(EnLOCAL_DATA* dp /* r16 */, u_int type /* r2 */);
void enSetHP(EnLOCAL_DATA* dp /* r17 */, float hp /* r21 */, float endurance /* r20 */);
float enReduceHP(EnLOCAL_DATA* dp /* r2 */);
float enAddHP(EnLOCAL_DATA* dp /* r2 */, float n /* r29 */);
float enAddEnduranceDT(EnLOCAL_DATA* dp /* r17 */, float n /* r20 */);

int enCheckSpray(EnLOCAL_DATA* dp /* r2 */);
void enResetDamage(EnLOCAL_DATA* dp /* r2 */);
int enCheckDeath(EnLOCAL_DATA* dp /* r2 */);
void enSetHitBack(EnLOCAL_DATA* dp /* r2 */);
int enCheckInstantDeath(EnLOCAL_DATA* dp /* r2 */);
void enSetSize(EnLOCAL_DATA* dp /* r2 */, float size /* r29 */, float tall /* r29 */, float center /* r29 */, float eye /* r29 */);
void enSetNewSize(EnLOCAL_DATA* dp /* r2 */, float size /* r29 */, float tall /* r29 */, float center /* r29 */, float eye /* r29 */);
void enSetSeeLightStatus(EnLOCAL_DATA* dp /* r2 */, float center /* r29 */, float radius /* r29 */);
int enCheckSeeLight(EnLOCAL_DATA* dp /* r2 */);
int enCheckAimedByHuman(EnLOCAL_DATA* dp /* r2 */);
int enCheckFinishedByHuman(EnLOCAL_DATA* dp /* r2 */);
int enCheckNoDamageHuman(EnLOCAL_DATA* dp /* r2 */);
void enAttackStart(EnLOCAL_DATA* dp /* r16 */);
int enAttackCheck(EnLOCAL_DATA* dp /* r2 */, int ID /* r2 */);
int enAttackCheckHug(EnLOCAL_DATA* dp /* r16 */, int ID /* r2 */);
int enCheckHuggedPlayer(void);
int enCheckSleepIn(EnLOCAL_DATA* dp);
int enCheckSleepOut(EnLOCAL_DATA* dp);
void enSleepIn(EnLOCAL_DATA* dp /* r2 */);
void enSleepOut(EnLOCAL_DATA* dp /* r2 */);
void enKillCountUp(EnLOCAL_DATA* dp /* r2 */);
float* enGetPlayerPos(EnLOCAL_DATA* dp /* r2 */);
float enCheckPlayerHitEyes(EnLOCAL_DATA* dp, float* ep);
float enCalcDirection(float* pa, float* pb);
float enGetPlayerDistance(EnLOCAL_DATA* dp /* r2 */);
float enGetPlayerDirection(EnLOCAL_DATA* dp /* r2 */);
int enGetPlayerWeapon(void);
int enCheckPlayerWeapon(void);
float enGetPlayerAngle(EnLOCAL_DATA* dp /* r2 */);
float enGetPlayerSize(void);
int enCheckPlayerSound(EnLOCAL_DATA* dp /* r2 */);
int enCheckPlayerCondition(EnLOCAL_DATA* dp /* r17 */);
int enCheckPlayerLight(void);
int enCheckPlayerSprayNow(void);
int enGetSprayPower(void);
int enCheckPlayerBulletEmpty(void);
int enCheckDeadPlayer(void);
void enSetGameOver(void);
void enFlagSetMoved(EnLOCAL_DATA* dp /* r2 */);
void enFlagResetMoved(EnLOCAL_DATA* dp /* r2 */);
void enFlagSetLieDown(EnLOCAL_DATA* dp /* r2 */);
void enFlagResetLieDown(EnLOCAL_DATA* dp /* r2 */);
void enFlagSetCritical(EnLOCAL_DATA* dp /* r2 */);
void enFlagResetCritical(EnLOCAL_DATA* dp /* r2 */);
int enCheckCritical(EnLOCAL_DATA* dp /* r2 */);
void enFlagSetNoDamage(EnLOCAL_DATA* dp /* r2 */);
void enFlagResetNoDamage(EnLOCAL_DATA* dp /* r2 */);
void enFlagSetDead(EnLOCAL_DATA* dp /* r2 */);
void enFlagResetDead(EnLOCAL_DATA* dp /* r2 */);
void enFlagSetRotFloor(EnLOCAL_DATA* dp /* r2 */);
void enFlagResetRotFloor(EnLOCAL_DATA* dp /* r2 */);
void enFlagResetRotFloorJust(EnLOCAL_DATA* dp /* r2 */);
void enFlagSetDisplay(EnLOCAL_DATA* dp /* r2 */);
void enFlagResetDisplay(EnLOCAL_DATA* dp /* r2 */);

float enCalcDirection(float* pa /* r2 */, float* pb /* r2 */);
float enCalcAngleDifference(float angle1 /* r29+0x10 */, float angle2 /* r29+0x10 */);
float enCalcSpeedRate(float angle, float* mpos, float* tpos);
void enMakeRotVector(float* vec, float* rot, float range);

SubCharacter* enGetNearCharacter(EnLOCAL_DATA* dp);
int enCalcTimer(int t /* r2 */);
void enSetTimer(EnLOCAL_DATA* dp /* r16 */, int t /* r2 */);
int enReduceTimer(EnLOCAL_DATA* dp /* r18 */);

EnLOCAL_DATA* enGetNearOtherEnemy(EnLOCAL_DATA* dp);

void enCheckNearPlayer(EnLOCAL_DATA* dp, int* count, float* dist, float limit);

void enSetRadioVolume(EnLOCAL_DATA* dp /* r2 */);
void enMoveAngle(EnPATH_DATA* p /* r16 */, float delta /* r20 */);
void enMoveAngleToPlayer(EnLOCAL_DATA* dp, float delta);

void enSetRotFloor(EnLOCAL_DATA* dp);

void enDeleteCharacter(EnLOCAL_DATA* dp /* r2 */);

float enCheckForward(EnLOCAL_DATA* dp, float* pos, float* rot, float range);

void enInitPath(EnPATH_DATA* p /* r16 */, float angle /* r29+0x20 */);
int enSetPath(EnLOCAL_DATA* dp /* r19 */, float* target /* r17 */, float* pos /* r18 */);

void enAnimeSet(EnLOCAL_DATA* dp /* r17 */, int anim /* r18 */, int id /* r16 */);

void enAnimePause(EnLOCAL_DATA* dp /* r2 */);
void enAnimeRestart(EnLOCAL_DATA* dp /* r2 */);
void enAnimeFrameSet(EnLOCAL_DATA* dp /* r2 */, u_short frame /* r2 */);
void enAnimeReverse(EnLOCAL_DATA* dp /* r16 */);
void enSetAnimeCount(EnLOCAL_DATA* dp /* r17 */, int count /* r16 */);
void enEfctBloodPool(EnLOCAL_DATA* dp /* r2 */);
void enEfctPoisonFog(float* pos /* r2 */, float* vec /* r2 */);
void enSetBlur(void);
void enSetFadeOut(void);
void enResetFilter(void);
void enSoundCall(int num /* r2 */, float vol /* r29+0x10 */, float* pos /* r2 */);
void enSoundCall3D(int num /* r2 */, float vol /* r29+0x10 */, float* pos /* r2 */);
void enSoundStop(int num /* r2 */);
void enSoundSetQueue(SubCharacter* scp /* r2 */, int num /* r2 */, float vol /* r29 */, float time /* r29 */);
EnCOMMUNICATION* enSetCommunication(int kind, int type, float* pos, float dist, int time);

void enResetForbiddenArea(void);

void enEventDriven(int event /* r2 */, int id /* r2 */);

#endif

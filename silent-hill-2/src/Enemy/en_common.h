#ifndef EN_COMMON_H
#define EN_COMMON_H

#include "sh2_common.h"
#include "Chacter/character.h"

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
struct EnLOCAL_DATA* enEntryEnemy(int kind /* r2 */);
void enDeleteEnemy(struct EnLOCAL_DATA* dp /* r2 */);
void enDummyCtrl(struct EnLOCAL_DATA* dp /* r2 */);
int enTransID(int id /* r2 */);
int enGetWorldCondition(void);
int enGetPlace(void);
int enGetStage(void);
int enGetMode(void);
int enCheckDarkOrBright(struct SubCharacter* scp /* r2 */);
int enCheckDarkOrBrightPlayer(void);
void enSetBattleTarget(struct EnLOCAL_DATA* dp /* r16 */, u_int type /* r2 */);
void enSetHP(struct EnLOCAL_DATA* dp /* r17 */, float hp /* r21 */, float endurance /* r20 */);
float enReduceHP(struct EnLOCAL_DATA* dp /* r2 */);
float enAddHP(struct EnLOCAL_DATA* dp /* r2 */, float n /* r29 */);
float enAddEnduranceDT(struct EnLOCAL_DATA* dp /* r17 */, float n /* r20 */);

int enCheckSpray(struct EnLOCAL_DATA* dp /* r2 */);
void enResetDamage(struct EnLOCAL_DATA* dp /* r2 */);
int enCheckDeath(struct EnLOCAL_DATA* dp /* r2 */);
void enSetHitBack(struct EnLOCAL_DATA* dp /* r2 */);
int enCheckInstantDeath(struct EnLOCAL_DATA* dp /* r2 */);
void enSetSize(struct EnLOCAL_DATA* dp /* r2 */, float size /* r29 */, float tall /* r29 */, float center /* r29 */, float eye /* r29 */);
void enSetNewSize(struct EnLOCAL_DATA* dp /* r2 */, float size /* r29 */, float tall /* r29 */, float center /* r29 */, float eye /* r29 */);
void enSetSeeLightStatus(struct EnLOCAL_DATA* dp /* r2 */, float center /* r29 */, float radius /* r29 */);
int enCheckSeeLight(struct EnLOCAL_DATA* dp /* r2 */);
int enCheckAimedByHuman(struct EnLOCAL_DATA* dp /* r2 */);
int enCheckFinishedByHuman(struct EnLOCAL_DATA* dp /* r2 */);
int enCheckNoDamageHuman(struct EnLOCAL_DATA* dp /* r2 */);
void enAttackStart(struct EnLOCAL_DATA* dp /* r16 */);
int enAttackCheck(struct EnLOCAL_DATA* dp /* r2 */, int ID /* r2 */);
int enAttackCheckHug(struct EnLOCAL_DATA* dp /* r16 */, int ID /* r2 */);
int enCheckHuggedPlayer(void);
int enCheckSleepIn(struct EnLOCAL_DATA* dp);
int enCheckSleepOut(struct EnLOCAL_DATA* dp);
void enSleepIn(struct EnLOCAL_DATA* dp /* r2 */);
void enSleepOut(struct EnLOCAL_DATA* dp /* r2 */);
void enKillCountUp(struct EnLOCAL_DATA* dp /* r2 */);
float* enGetPlayerPos(struct EnLOCAL_DATA* dp /* r2 */);
float enGetPlayerDistance(struct EnLOCAL_DATA* dp /* r2 */);
float enGetPlayerDirection(struct EnLOCAL_DATA* dp /* r2 */);
int enGetPlayerWeapon(void);
int enCheckPlayerWeapon(void);
float enGetPlayerAngle(struct EnLOCAL_DATA* dp /* r2 */);
float enGetPlayerSize(void);
int enCheckPlayerSound(struct EnLOCAL_DATA* dp /* r2 */);
int enCheckPlayerCondition(struct EnLOCAL_DATA* dp /* r17 */);
int enCheckPlayerLight(void);
int enCheckPlayerSprayNow(void);
int enGetSprayPower(void);
int enCheckPlayerBulletEmpty(void);
int enCheckDeadPlayer(void);
void enSetGameOver(void);
void enFlagSetMoved(struct EnLOCAL_DATA* dp /* r2 */);
void enFlagResetMoved(struct EnLOCAL_DATA* dp /* r2 */);
void enFlagSetLieDown(struct EnLOCAL_DATA* dp /* r2 */);
void enFlagResetLieDown(struct EnLOCAL_DATA* dp /* r2 */);
void enFlagSetCritical(struct EnLOCAL_DATA* dp /* r2 */);
void enFlagResetCritical(struct EnLOCAL_DATA* dp /* r2 */);
int enCheckCritical(struct EnLOCAL_DATA* dp /* r2 */);
void enFlagSetNoDamage(struct EnLOCAL_DATA* dp /* r2 */);
void enFlagResetNoDamage(struct EnLOCAL_DATA* dp /* r2 */);
void enFlagSetDead(struct EnLOCAL_DATA* dp /* r2 */);
void enFlagResetDead(struct EnLOCAL_DATA* dp /* r2 */);
void enFlagSetRotFloor(struct EnLOCAL_DATA* dp /* r2 */);
void enFlagResetRotFloor(struct EnLOCAL_DATA* dp /* r2 */);
void enFlagResetRotFloorJust(struct EnLOCAL_DATA* dp /* r2 */);
void enFlagSetDisplay(struct EnLOCAL_DATA* dp /* r2 */);
void enFlagResetDisplay(struct EnLOCAL_DATA* dp /* r2 */);

float enCalcAngleDifference(float angle1 /* r29+0x10 */, float angle2 /* r29+0x10 */);

int enCalcTimer(int t /* r2 */);
void enSetTimer(struct EnLOCAL_DATA* dp /* r16 */, int t /* r2 */);
int enReduceTimer(struct EnLOCAL_DATA* dp /* r18 */);

void enSetRadioVolume(struct EnLOCAL_DATA* dp /* r2 */);
void enMoveAngle(struct EnPATH_DATA* p /* r16 */, float delta /* r20 */);
void enMoveAngleToPlayer(EnLOCAL_DATA* dp, float delta);

void enDeleteCharacter(struct EnLOCAL_DATA* dp /* r2 */);

void enAnimeSet(struct EnLOCAL_DATA* dp /* r17 */, int anim /* r18 */, int id /* r16 */);

void enAnimePause(struct EnLOCAL_DATA* dp /* r2 */);
void enAnimeRestart(struct EnLOCAL_DATA* dp /* r2 */);
void enAnimeFrameSet(struct EnLOCAL_DATA* dp /* r2 */, u_short frame /* r2 */);
void enAnimeReverse(struct EnLOCAL_DATA* dp /* r16 */);
void enSetAnimeCount(struct EnLOCAL_DATA* dp /* r17 */, int count /* r16 */);
void enEfctBloodPool(struct EnLOCAL_DATA* dp /* r2 */);
void enEfctPoisonFog(float* pos /* r2 */, float* vec /* r2 */);
void enSetBlur(void);
void enSetFadeOut(void);
void enResetFilter(void);
void enSoundCall(int num /* r2 */, float vol /* r29+0x10 */, float* pos /* r2 */);
void enSoundCall3D(int num /* r2 */, float vol /* r29+0x10 */, float* pos /* r2 */);
void enSoundStop(int num /* r2 */);
void enSoundSetQueue(struct SubCharacter* scp /* r2 */, int num /* r2 */, float vol /* r29 */, float time /* r29 */);
struct EnCOMMUNICATION* enSetCommunication(int kind, int type, float* pos, float dist, int time);

void enResetForbiddenArea(void);

void enEventDriven(int event /* r2 */, int id /* r2 */);

// extern void shQzero(void*, int);

#endif

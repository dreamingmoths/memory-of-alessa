#ifndef EN_COMMON_H
#define EN_COMMON_H

#include "Chacter/character.h"

typedef struct EnSOUND_QUEUE {
    // total size: 0x10
    struct SubCharacter* scp; // offset 0x0, size 0x4
    int num; // offset 0x4, size 0x4
    float vol; // offset 0x8, size 0x4
    float time; // offset 0xC, size 0x4
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
    struct EnLOCAL_DATA Data[32]; // offset 0x0, size 0x1C00
    struct EnCOMMUNICATION Communication[8]; // offset 0x1C00, size 0x100
    struct EnFORBIDDENAREA ForbiddenArea[2]; // offset 0x1D00, size 0x20
    struct EnSOUND_QUEUE SoundQueue[8]; // offset 0x1D20, size 0x80
    int CommunicationNum; // offset 0x1DA0, size 0x4
    int ForbiddenNum; // offset 0x1DA4, size 0x4
    int SoundQueueNum; // offset 0x1DA8, size 0x4
    u_int Status; // offset 0x1DAC, size 0x4
    struct EnLOCAL_DATA* This; // offset 0x1DB0, size 0x4
    struct _CL_VHIT_RESULT HitResult; // offset 0x1DC0, size 0x40
    int Max3DSounds; // offset 0x1E00, size 0x4
    int ActiveEnemy; // offset 0x1E04, size 0x4
} EnLOCAL_WORK;

struct EnLOCAL_WORK enLocalWork; // size: 0x1E10, address: 0x5506A0

void enInitEnemy(void);
struct EnLOCAL_DATA* enEntryEnemy(int kind /* r2 */);
void enDeleteEnemy(struct EnLOCAL_DATA* dp /* r2 */);
void enDummyCtrl(struct EnLOCAL_DATA* dp /* r2 */);
int enTransID(int id /* r2 */);
int enGetWorldCondition(void);
int enGetPlace(void);
int enGetMode(void);
int enCheckDarkOrBright(struct SubCharacter* scp /* r2 */);
int enCheckDarkOrBrightPlayer(void);
void enSetBattleTarget(struct EnLOCAL_DATA* dp /* r16 */, u_int type /* r2 */);
void enSetHP(struct EnLOCAL_DATA* dp /* r17 */, float hp /* r21 */, float endurance /* r20 */);
float enReduceHP(struct EnLOCAL_DATA* dp /* r2 */);
float enAddEnduranceDT(struct EnLOCAL_DATA* dp /* r17 */, float n /* r20 */);
void enResetDamage(struct EnLOCAL_DATA* dp /* r2 */);
int enCheckDeath(struct EnLOCAL_DATA* dp /* r2 */);
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

void enKillCountUp(struct EnLOCAL_DATA* dp /* r2 */);

int enCheckPlayerLight(void);

int enCheckDeadPlayer(void);
void enSetGameOver(void);

void enSetRadioVolume(struct EnLOCAL_DATA* dp /* r2 */);

void enDeleteCharacter(struct EnLOCAL_DATA* dp /* r2 */);

void enSoundCall(int num /* r2 */, float vol /* r29+0x10 */, float* pos /* r2 */);
void enSoundCall3D(int num /* r2 */, float vol /* r29+0x10 */, float* pos /* r2 */);
void enSoundStop(int num /* r2 */);
void enSoundSetQueue(struct SubCharacter* scp /* r2 */, int num /* r2 */, float vol /* r29 */, float time /* r29 */);

void enEventDriven(int event /* r2 */, int id /* r2 */);

extern void shQzero(void*, int);

#endif

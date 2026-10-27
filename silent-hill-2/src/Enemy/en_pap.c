#include "sh2_common.h"

#include "Enemy/en_common.h"

//* abstract daddy *//

static void enPAPCtrlAutomatic(EnLOCAL_DATA* dp);
static void enPAPCtrlSleep(EnLOCAL_DATA* dp);
static void enPAPCtrlGoPlayable(EnLOCAL_DATA* dp);
static void enPAPCtrlEvent(EnLOCAL_DATA* dp);
static void enPAPCtrlHand(EnLOCAL_DATA* dp);
static void enPAPCtrlWander(EnLOCAL_DATA* dp);
static void enPAPCtrlStraight(EnLOCAL_DATA* dp);
static void enPAPCtrlChase(EnLOCAL_DATA* dp);
static void enPAPCtrlRush(EnLOCAL_DATA* dp);
static void enPAPCtrlAttack(EnLOCAL_DATA* dp);
static void enPAPCtrlDamage(EnLOCAL_DATA* dp);
static void enPAPCtrlConfuse(EnLOCAL_DATA* dp);
static void enPAPCtrlDown(EnLOCAL_DATA* dp);
static void enPAPCtrlLastMove(EnLOCAL_DATA* dp);
static void enPAPMoveAngle(EnLOCAL_DATA* dp);
static int enPAPCanSeePlayer(EnLOCAL_DATA* dp);
static void enPAPAnimeSet(EnLOCAL_DATA* dp, int anim);
static void enPAPAnimeExec(EnLOCAL_DATA* dp);
static void enPAPAutoRecovery(EnLOCAL_DATA* dp);
static float enPAPGetWalkSpeed(EnLOCAL_DATA* dp);
static float enPAPGetRotSpeed(void);
static float enPAPGetTurnSpeed(EnLOCAL_DATA* dp);
static void enPAPSetDownTime(EnLOCAL_DATA* dp);
static void enPAPSetMoveCount(EnLOCAL_DATA* dp);
static void enPAPSetDc(EnLOCAL_DATA* dp);
static void enPAPDrawBoad(EnLOCAL_DATA* dp);
static void enPAPSoundSigns(EnLOCAL_DATA* dp);

UNLINKED(EnANIME_DATA EnPAPAnime[33], {
    { /* .anime = */ 5701, /* .loop  = */ false },
    { /* .anime = */ 5702, /* .loop  = */ true  },
    { /* .anime = */ 5701, /* .loop  = */ true  },
    { /* .anime = */ 5704, /* .loop  = */ true  },
    { /* .anime = */ 5727, /* .loop  = */ true  },
    { /* .anime = */ 5706, /* .loop  = */ false },
    { /* .anime = */ 5707, /* .loop  = */ false },
    { /* .anime = */ 5708, /* .loop  = */ false },
    { /* .anime = */ 5709, /* .loop  = */ false },
    { /* .anime = */ 5710, /* .loop  = */ false },
    { /* .anime = */ 5711, /* .loop  = */ false },
    { /* .anime = */ 5712, /* .loop  = */ false },
    { /* .anime = */ 5713, /* .loop  = */ false },
    { /* .anime = */ 5709, /* .loop  = */ false },
    { /* .anime = */ 5714, /* .loop  = */ false },
    { /* .anime = */ 5715, /* .loop  = */ false },
    { /* .anime = */ 5716, /* .loop  = */ false },
    { /* .anime = */ 5717, /* .loop  = */ false },
    { /* .anime = */ 5718, /* .loop  = */ false },
    { /* .anime = */ 5719, /* .loop  = */ false },
    { /* .anime = */ 5720, /* .loop  = */ false },
    { /* .anime = */ 5721, /* .loop  = */ false },
    { /* .anime = */ 5701, /* .loop  = */ false },
    { /* .anime = */ 5722, /* .loop  = */ false },
    { /* .anime = */ 5701, /* .loop  = */ true  },
    { /* .anime = */ 5723, /* .loop  = */ true  },
    { /* .anime = */ 5701, /* .loop  = */ false },
    { /* .anime = */ 5725, /* .loop  = */ false },
    { /* .anime = */ 5703, /* .loop  = */ false },
    { /* .anime = */ 5705, /* .loop  = */ false },
    { /* .anime = */ 5724, /* .loop  = */ false },
    { /* .anime = */ 5726, /* .loop  = */ false },
    { /* .anime = */ 5728, /* .loop  = */ false }
});

#define ENEMY_PAP_MODE_DUMMY         0
#define ENEMY_PAP_MODE_AUTOMATIC     1
#define ENEMY_PAP_MODE_SLEEP         2
#define ENEMY_PAP_MODE_GO_PLAYABLE   3
#define ENEMY_PAP_MODE_EVENT         4
#define ENEMY_PAP_MODE_HAND          5

#define ENEMY_PAP_STATE_WANDER       0
#define ENEMY_PAP_STATE_STRAIGHT     1
#define ENEMY_PAP_STATE_CHASE        2
#define ENEMY_PAP_STATE_RUSH         3
#define ENEMY_PAP_STATE_ATTACK       4
#define ENEMY_PAP_STATE_DAMAGE       5
#define ENEMY_PAP_STATE_CONFUSE      6
#define ENEMY_PAP_STATE_DOWN         7
#define ENEMY_PAP_STATE_LAST_MOVE    8
#define ENEMY_PAP_STATE_DYING        9

#pragma fast_fptosi on

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPInitData);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlMain);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlAutomatic);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlSleep);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlGoPlayable);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlEvent);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlHand);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlWander);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlStraight);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlChase);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlRush);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlAttack);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlDamage);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlConfuse);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlDown);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCtrlLastMove);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPMoveAngle);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPCanSeePlayer);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPAnimeSet);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPAnimeExec);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPAutoRecovery);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPGetWalkSpeed);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPGetRotSpeed);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPGetTurnSpeed);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPSetDownTime);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPSetMoveCount);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPSetDc);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPDrawBoad);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_pap", enPAPSoundSigns);

INCLUDE_RODATA("asm/nonmatchings/Enemy/en_pap", @1688);

INCLUDE_RODATA("asm/nonmatchings/Enemy/en_pap", @1689);

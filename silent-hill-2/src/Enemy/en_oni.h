#ifndef EN_ONI_H
#define EN_ONI_H

#include "sh2_common.h"
#include "Enemy/en_common.h"

#define ENEMY_ONI_MODE_DUMMY         0
#define ENEMY_ONI_MODE_AUTOMATIC     1
#define ENEMY_ONI_MODE_SLEEP         2
#define ENEMY_ONI_MODE_GO_PLAYABLE   3
#define ENEMY_ONI_MODE_EVENT         4
#define ENEMY_ONI_MODE_HAND          5

#define ENEMY_ONI_STATE_WANDER       0
#define ENEMY_ONI_STATE_CHASE        1
#define ENEMY_ONI_STATE_BOTH_ATTACK  2
#define ENEMY_ONI_STATE_WAIT         3
#define ENEMY_ONI_STATE_BERSERK      4
#define ENEMY_ONI_STATE_ATTACK       5
#define ENEMY_ONI_STATE_ATTACK3      6
#define ENEMY_ONI_STATE_DAMAGE       7
#define ENEMY_ONI_STATE_CONFUSE      8
#define ENEMY_ONI_STATE_SUICIDE      9
#define ENEMY_ONI_STATE_DEAD         10

void enONIInitData(EnLOCAL_DATA* dp);
void enONICtrlMain(EnLOCAL_DATA* dp);

#endif // EN_ONI_H

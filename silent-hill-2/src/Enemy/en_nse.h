#ifndef EN_NSE_H
#define EN_NSE_H

#include "sh2_common.h"
#include "Enemy/en_common.h"

#define ENEMY_NSE_MODE_DUMMY                    0
#define ENEMY_NSE_MODE_AUTOMATIC                1
#define ENEMY_NSE_MODE_SLEEP                    2
#define ENEMY_NSE_MODE_GO_PLAYABLE              3
#define ENEMY_NSE_MODE_EVENT                    4
#define ENEMY_NSE_MODE_HAND                     5
#define ENEMY_NSE_MODE_WAIT_REGENERATE          6

#define ENEMY_NSE_STATE_WANDER       0
#define ENEMY_NSE_STATE_PRECAUTION   1
#define ENEMY_NSE_STATE_CHASE        2
#define ENEMY_NSE_STATE_ATTACK       3
#define ENEMY_NSE_STATE_DAMAGE       4
#define ENEMY_NSE_STATE_CONFUSE      5
#define ENEMY_NSE_STATE_DOWN         6
#define ENEMY_NSE_STATE_DYING        7

void enNSEInitData(EnLOCAL_DATA* dp);
void enNSECtrlMain(EnLOCAL_DATA* dp);

#endif // EN_NSE_H

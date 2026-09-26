#ifndef DBSWITCH_H
#define DBSWITCH_H

#include "common.h"

typedef enum DBSW_ID {
    DBSW_SYS = 0,
    DBSW_MAP = 1,
    DB_SWITCH_MAX = 2,
} DBSW_ID;

void dbSwitchDispIndicator(int enable /* r2 */, int o /* r2 */, int x /* r2 */, int dx /* r2 */, int dy /* r2 */);

int dbSwitchDispEnable(int enable);

int dbSwitchInit(DBSW_ID _X, u_long bit_pattern);

int dbSwitchSet(DBSW_ID _X /* r2 */, int Y /* r2 */, int set /* r2 */);

int dbSwitch(DBSW_ID _X /* r2 */, int Y /* r2 */);

int dbSwitchGetPos(int * Xp /* r2 */, int * Yp /* r2 */);

#endif // DBSWITCH_H

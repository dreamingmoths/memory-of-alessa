#ifndef DBSW_ALL_H
#define DBSW_ALL_H

#include "SH2_common/pad.h"
#include "DBG/dbsw_sys.h"
#include "DBG/dbswitch.h"
#include "DBG/dbsw_map.h"

void dbSwitchAllInit(int enable /* r16 */);

int dbSwitchIsVisible(void);

void dbSwitchAllPrint(void);

#endif // DBSW_ALL_H

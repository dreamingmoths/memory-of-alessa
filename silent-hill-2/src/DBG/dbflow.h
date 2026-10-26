#ifndef DBFLOW_H
#define DBFLOW_H

#include "sh2_common.h"

#include "Exec_Env/exec_env.h"
#include "Multi_thr/intc/syncv.h"

#define dbFlowSetCheckPoint(checkpoint) ___dbFlowSetCheckPoint("`" checkpoint "'(" __FILE__ ":" ASSTR(__LINE__) ")")
#define dbFlowSetCheckPointOnLine(checkpoint, line) ___dbFlowSetCheckPoint("`" checkpoint "'(" __FILE__ ":" ASSTR(line) ")")

void ___dbFlowSetCheckPoint(s_char* check_point /* r2 */);

int dbFlowCheck(void);

void dbFlowStartCheck(int enable /* r2 */);

void dbFlowCheckSleepTime(int flow_ok /* r2 */);

#endif

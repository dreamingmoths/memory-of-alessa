#ifndef CMD_SERV_H
#define CMD_SERV_H

#include "common.h"

int CmdServInit(u_long* work /* r22 */, int workSize /* r2 */, void* stack /* r21 */, int stackSize /* r20 */, int prio /* r19 */);
int CmdQueueSync(u_long* work /* r2 */, int mode /* r20 */, int id /* r19 */);
int CmdQueueGetCurrentCommandId(u_long* work /* r2 */);
int CmdQueueCmpCmdId(int cid0 /* r2 */, int cid1 /* r2 */);
int CmdQueuePut0(u_long* work /* r2 */, int (* func)(void) /* r17 */);
int CmdQueuePut1(u_long* work /* r2 */, int (* func)(void) /* r20 */, u_long a0 /* r19 */); 

#endif // CMD_SERV_H

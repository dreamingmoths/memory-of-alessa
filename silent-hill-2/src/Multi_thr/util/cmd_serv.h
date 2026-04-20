#ifndef CMD_SERV_H
#define CMD_SERV_H

#include "common.h"

// total size: 0x14
typedef struct CmdServStat {
    // Members
    signed int qsize; // offset 0x0, size 0x4
    signed int qlen; // offset 0x4, size 0x4
    signed int id; // offset 0x8, size 0x4
    signed int last_id; // offset 0xC, size 0x4
    signed int clen; // offset 0x10, size 0x4
} CmdServStat;

int CmdServInit(u_long128* work /* r22 */, int workSize /* r2 */, void* stack /* r21 */, int stackSize /* r20 */, int prio /* r19 */);
int CmdQueueSync(u_long128* work /* r2 */, int mode /* r20 */, int id /* r19 */);
int CmdQueueGetCurrentCommandId(u_long128* work /* r2 */);
int CmdQueueCmpCmdId(int cid0 /* r2 */, int cid1 /* r2 */);
int CmdQueuePut0(u_long128* work /* r2 */, int (* func)(void) /* r17 */);
int CmdQueuePut1(u_long128* work /* r2 */, int (* func)(void) /* r20 */, u_long128 a0 /* r19 */); 

int CmdServGetStat(u_long128* work /* r2 */, CmdServStat* stat /* r21 */);

#endif // CMD_SERV_H

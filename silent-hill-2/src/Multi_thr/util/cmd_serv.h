#ifndef CMD_SERV_H
#define CMD_SERV_H

#include "sh2_common.h"

// total size: 0x14
typedef struct CmdServStat {
    // Members
    int qsize;   // offset 0x0, size 0x4
    int qlen;    // offset 0x4, size 0x4
    int id;      // offset 0x8, size 0x4
    int last_id; // offset 0xC, size 0x4
    int clen;    // offset 0x10, size 0x4
} CmdServStat;

typedef struct CmdServWork {
    // Members
    int exclusive_sid; // offset 0x0, size 0x4
    int kick_sid; // offset 0x4, size 0x4
    int sync_sid; // offset 0x8, size 0x4
    int cmdexec_tid; // offset 0xC, size 0x4
    int qsize; // offset 0x10, size 0x4
    u_long128* queue; // offset 0x14, size 0x4
    int next_id; // offset 0x18, size 0x4
    int qlen; // offset 0x1C, size 0x4
    int qhead; // offset 0x20, size 0x4
    int qnext; // offset 0x24, size 0x4
    int oldest_id; // offset 0x28, size 0x4
    int newest_id; // offset 0x2C, size 0x4
    int last_ret; // offset 0x30, size 0x4
    int (*last_cmd)(); // offset 0x34, size 0x4
    int kick_req; // offset 0x38, size 0x4
    int sync_req; // offset 0x3C, size 0x4
    int debug[16]; // offset 0x40, size 0x40
} CmdServWork;

int CmdServInit(u_long128* work /* r22 */, int workSize /* r2 */, void* stack /* r21 */, int stackSize /* r20 */, int prio /* r19 */);
int CmdQueueSync(u_long128* work /* r2 */, int mode /* r20 */, int id /* r19 */);
int CmdQueueGetCurrentCommandId(u_long128* work /* r2 */);
int CmdQueueCmpCmdId(int cid0 /* r2 */, int cid1 /* r2 */);
int CmdQueuePut0(u_long128* work /* r2 */, int (*func)(void) /* r17 */);
int CmdQueuePut1(u_long128* work /* r2 */, int (*func)(void) /* r20 */, u_long128 a0 /* r19 */);
int CmdQueuePut2(u_long128* work, int (* func)(void), u_long128 a0, u_long128 a1);
int CmdQueuePut3(u_long128* work, int (* func)(void), u_long128 a0, u_long128 a1, u_long128 a2);
int CmdQueuePut4(u_long128* work, int (* func)(void), u_long128 a0, u_long128 a1, u_long128 a2, u_long128 a3);
int CmdServGetStat(u_long128* work /* r2 */, CmdServStat* stat /* r21 */);

#endif // CMD_SERV_H

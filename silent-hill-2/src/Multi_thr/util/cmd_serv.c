#include "Multi_thr/util/cmd_serv.h"
#include "sce/eekernel.h"

INCLUDE_ASM("asm/nonmatchings/Multi_thr/util/cmd_serv", CmdServFuncNull);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/util/cmd_serv", CmdServThread);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/util/cmd_serv", CmdServInit);

int CmdQueuePut0(u_long128* work, int (*func)()) {
    CmdServWork* serv;  // r16
    int qsize; // r18
    u_long128* queue; // r19
    int id; // r20
    int kick_req; // r21
    int qlen; // r3
    int qnext; // r4
    
    serv = (CmdServWork*) work;
    qsize = serv->qsize;
    queue = serv->queue;
    
    WaitSema(serv->exclusive_sid);
    qlen = serv->qlen;
    
    kick_req = 0;
    id = -1;

    
    if ((2 + qlen) <= qsize) {
        
        if (func != NULL) {
            qnext = serv->qnext;
            *(int*)&queue[qnext++] = (int)func;
            while (qnext >= qsize) qnext -= qsize;
            *(int*)&queue[qnext++] = 0;
            while (qnext >= qsize) qnext -= qsize;    
            id = serv->newest_id;
            id = (id + 1) & 0x7FFFFFFF;
            serv->newest_id = id;
            serv->qlen = qlen + 2;
            serv->qnext = qnext;
            kick_req = serv->kick_req;
            serv->kick_req = 0;
        }
    }
    SignalSema(serv->exclusive_sid);
    if (kick_req != 0) SignalSema(serv->kick_sid);
    return id;
}

INCLUDE_ASM("asm/nonmatchings/Multi_thr/util/cmd_serv", CmdQueuePut1);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/util/cmd_serv", CmdQueuePut2);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/util/cmd_serv", CmdQueuePut3);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/util/cmd_serv", CmdQueuePut4);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/util/cmd_serv", CmdQueueSync);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/util/cmd_serv", CmdQueueGetCurrentCommandId);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/util/cmd_serv", CmdQueueCmpCmdId);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/util/cmd_serv", CmdServGetStat);

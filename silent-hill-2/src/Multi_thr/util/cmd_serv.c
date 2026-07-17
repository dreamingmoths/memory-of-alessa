#include "Multi_thr/util/cmd_serv.h"
#include "sce/eekernel.h"

INCLUDE_ASM("asm/nonmatchings/Multi_thr/util/cmd_serv", CmdServFuncNull);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/util/cmd_serv", CmdServThread);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/util/cmd_serv", CmdServInit); // https://decomp.me/scratch/sx3OZ

int CmdQueuePut0(u_long128* work, int (*func)()) {
    CmdServWork* serv;  // r16
    int qsize; // r18
    u_long128* queue; // r19
    int id; // r20
    int kick_req; // r21
    int qlen; // r3
    int qnext; // r4
    
    serv = work;
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

int CmdQueuePut1(u_long128* work, int (*func)(), u_long128 a0) {
    CmdServWork* serv; // r16
    int qsize; // r17
    u_long128* queue; // r18
    int id; // r21
    int kick_req; // r22
    int qlen; // r4    
    int qnext; // r5

    serv = work;
    qsize = serv->qsize;
    queue = serv->queue;
    
    WaitSema(serv->exclusive_sid);
    qlen = serv->qlen;
    
    kick_req = 0;
    id = -1;

    
    if ((3 + qlen) <= qsize) {
        
        if (func != NULL) {
            qnext = serv->qnext;
            *(int*)&queue[qnext++] = (int)func;
            while (qnext >= qsize) qnext -= qsize;
            *(int*)&queue[qnext++] = 1;
            while (qnext >= qsize) qnext -= qsize;   
            queue[qnext++] = a0;
            while (qnext >= qsize) qnext -= qsize;    
            id = serv->newest_id;
            id = (id + 1) & 0x7FFFFFFF;
            serv->newest_id = id;
            serv->qlen = qlen + 3;
            serv->qnext = qnext;
            kick_req = serv->kick_req;
            serv->kick_req = 0;
        }
    }
    SignalSema(serv->exclusive_sid);
    if (kick_req != 0) SignalSema(serv->kick_sid);
    return id;
}

int CmdQueuePut2(u_long128* work, int (*func)(), u_long128 a0, u_long128 a1) {
    CmdServWork* serv;
    int qsize;
    u_long128* queue;
    int id;
    int kick_req;
    int qlen;  
    int qnext;
    
    serv = work;
    qsize = serv->qsize;
    queue = serv->queue;
    
    WaitSema(serv->exclusive_sid);
    qlen = serv->qlen;
    
    kick_req = 0;
    id = -1;

    
    if ((4 + qlen) <= qsize) {
        
        if (func != NULL) {
            qnext = serv->qnext;
            *(int*)&queue[qnext++] = (int)func;
            while (qnext >= qsize) qnext -= qsize;
            *(int*)&queue[qnext++] = 2;
            while (qnext >= qsize) qnext -= qsize;   
            queue[qnext++] = a0;
            while (qnext >= qsize) qnext -= qsize;
            queue[qnext++] = a1;
            while (qnext >= qsize) qnext -= qsize;  
            id = serv->newest_id;
            id = (id + 1) & 0x7FFFFFFF;
            serv->newest_id = id;
            serv->qlen = qlen + 4;
            serv->qnext = qnext;
            kick_req = serv->kick_req;
            serv->kick_req = 0;
        }
    }
    SignalSema(serv->exclusive_sid);
    if (kick_req != 0) SignalSema(serv->kick_sid);
    return id;
}

INCLUDE_ASM("asm/nonmatchings/Multi_thr/util/cmd_serv", CmdQueuePut3); // https://decomp.me/scratch/en4Ru

INCLUDE_ASM("asm/nonmatchings/Multi_thr/util/cmd_serv", CmdQueuePut4); // https://decomp.me/scratch/en4Ru

INCLUDE_ASM("asm/nonmatchings/Multi_thr/util/cmd_serv", CmdQueueSync);

int CmdQueueGetCurrentCommandId(u_long128* work) {
    CmdServWork* serv; // r17
    serv = work; 
    if (serv->cmdexec_tid == GetThreadId()) return serv->oldest_id;
    return -1;
}

int CmdQueueCmpCmdId(int cid0, int cid1) {
    int cmp;// r2
    cmp = cid0 - cid1;
    
    return (cmp << 1) >> 1;
}

int CmdServGetStat(u_long128* work, CmdServStat* stat) { // not line matched
    int ret; // r2 how is this used?
    CmdServWork* serv; // r16
    int qsize; // r17
    int qlen; // r18
    int id; // r19
    int last_id; // r20
    int clen; // r3
    
    if (stat != NULL) {
        serv = work;
        WaitSema(serv->exclusive_sid);
        qsize = serv->qsize;
        qlen = serv->qlen;
        id = serv->oldest_id;
        last_id = serv->newest_id;
        SignalSema(serv->exclusive_sid);
        clen = CmdQueueCmpCmdId(last_id, id) + 1;
        if (clen < 0) clen = 0;
        stat->qsize = qsize;
        stat->qlen = qlen;
        stat->id = id;
        stat->last_id = last_id + 1;
        stat->clen = clen;
        return 1;
    }
    return 0;
}

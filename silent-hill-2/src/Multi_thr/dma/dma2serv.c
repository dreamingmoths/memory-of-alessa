#include "dma2serv.h"





















static void * d2sCmdWorkP; // size: 0x4, address: 0x10138B8

int d2sInit(int th_prio /* r11 */, void* stack /* r10 */, int stackSize /* r9 */, void* queue /* r16 */, int queueSize /* r2 */) {
    int ret = 0;
    if (d2sCmdWorkP == NULL) {
        ret = CmdServInit(queue, queueSize, stack, stackSize, th_prio);
        if (ret) {
            d2sCmdWorkP = queue;
        }
    }
    return ret;
}

















int d2sSync(int mode /* r3 */, int cid /* r2 */) {
    int ret = 0;
    if (d2sCmdWorkP != NULL) {
        ret = CmdQueueSync(d2sCmdWorkP, mode, cid);
    }
    return ret;
}








int d2sGetCurCmdId(void) {
    int ret = -1;
    if (d2sCmdWorkP != NULL) {
        ret = CmdQueueGetCurrentCommandId(d2sCmdWorkP);
    }
    return ret;
}








int d2sCmpCID(int cid0 /* r2 */, int cid1 /* r2 */) {
    return CmdQueueCmpCmdId(cid0, cid1);
}




























int d2sPutCmd0(int (*f0)() /* r2 */) {
    int ret = -1;
    if (d2sCmdWorkP != NULL) {
        ret = CmdQueuePut0(d2sCmdWorkP, f0);
    }

    return ret;
}


int d2sPutCmd1(int (*f1)() /* r3 */, u_long128 a1 /* r2 */) {
    int ret = -1;
    if (d2sCmdWorkP != NULL) {
        ret = CmdQueuePut1(d2sCmdWorkP, f1, a1);
    }

    return ret;
}











int d2sPutCmd3(int (*f3)() /* r10 */, u_long128 a1 /* r9 */, u_long128 a2 /* r3 */, u_long128 a3 /* r2 */) {
    int ret = -1;
    if (d2sCmdWorkP != NULL) {
        ret = CmdQueuePut3(d2sCmdWorkP, f3, a1, a2, a3);
    }

    return ret;
}

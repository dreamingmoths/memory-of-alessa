#include "Multi_thr/dma/dma1serv.h"
#include "Multi_thr/util/cmd_serv.h"

static void* d1sCmdWorkP; // correct place for this?

#line 25
int d1sInit(int th_prio /* r11 */, void* stack /* r10 */, int stackSize /* r9 */, void* queue /* r16 */, int queueSize /* r2 */) {
    int ret = 0; // r2    
    if (d1sCmdWorkP == 0) {
        ret = CmdServInit(queue, queueSize, stack, stackSize, th_prio);
        if (ret != 0) {
            d1sCmdWorkP = queue;
        }
    }
    return ret;
}

#line 52
int d1sSync(int mode /* r3 */, int cid /* r2 */) {
    int ret = 0;
    if (d1sCmdWorkP != 0) 
        ret = CmdQueueSync(d1sCmdWorkP, mode, cid);
    
    return ret;    
}

#line 67
int d1sGetCurCmdId(void) {
    int ret = -1; // r2
    if (d1sCmdWorkP != 0) 
        ret = CmdQueueGetCurrentCommandId(d1sCmdWorkP);  
    
    return ret;    
}

#line 82
int d1sCmpCID(int cid0 /* r2 */, int cid1 /* r2 */)  {
    return CmdQueueCmpCmdId(cid0, cid1); // not 100% sure
}

#line 113
int d1sPutCmd0(int (* f0)() /* r2 */) {
    int ret = -1; // r2
    if (d1sCmdWorkP != 0)
        ret = CmdQueuePut0(d1sCmdWorkP, f0);

    
    return ret;
}

#line 123
int d1sPutCmd1(int (* f1)() /* r3 */, u_long a1 /* r2 */) {
    int ret = -1; // r2
    if (d1sCmdWorkP != 0) 
        ret = CmdQueuePut1(d1sCmdWorkP, f1, a1);

    
    return ret;
}

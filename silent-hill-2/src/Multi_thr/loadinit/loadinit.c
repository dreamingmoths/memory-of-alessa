#include "Multi_thr/loadinit/loadinit.h"

extern /* static */ void* lisCmdWorkP;

int lisInit(int th_prio /* r11 */, void* stack /* r10 */, int stackSize /* r9 */, void* queue /* r16 */, int queueSize /* r2 */) {
    int ret = 0; // r2
    if (lisCmdWorkP == NULL) {
        ret = CmdServInit(queue, queueSize, stack, stackSize, th_prio);
        if (ret != 0) 
            lisCmdWorkP = queue;
        
    }
    return ret;
}

int lisSync(int mode /* r3 */, int cid /* r2 */)  {
    int ret = 0;    
    if (lisCmdWorkP != NULL) 
        ret = CmdQueueSync(lisCmdWorkP, mode, cid);
    
    return ret;
}

int lisGetStat(CmdServStat* stat /* r2 */) {
    int ret; // r2    

    ret = lisCmdWorkP != NULL ? CmdServGetStat(lisCmdWorkP, stat) : 0;
    
    return ret;
}

int lisPutCmd0(int (* f0)(void) /* r2 */)  {
    int ret = -1; // r2
    if (lisCmdWorkP != NULL) 
        ret = CmdQueuePut0(lisCmdWorkP, f0);  

    
    return ret;
}

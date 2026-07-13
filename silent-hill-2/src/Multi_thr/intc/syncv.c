#include "common.h"
#include "sce/eeregs.h"

static int shSyncVHandler2(int arg, void* arg1, void* arg2);
static int shSyncVInitSub(int* sid_p, int* hid_p, int intc_cause);
static int shSyncVSub(int mode, int sid);

extern int shSyncVStart_sid; // size: 0x4, address: 0x33B408
extern int shSyncVStart_hid; // size: 0x4, address: 0x33B410
extern int shSyncVEnd_sid; // size: 0x4, address: 0x33B418
extern int shSyncVEnd_hid; // size: 0x4, address: 0x33B420





















static int shSyncVHandler2(int arg, void* arg1, void* arg2) {

    
    
    
    iReleaseSema(arg1, arg1);
    
    
    
    
    
    
    
    
    
    asm("sync; ei");
    return 1;
}








int shSyncVInitSub(int* sid_p, int* hid_p, int intc_cause) {
    int hid;
    int sid;
    VERBOSE_ON_LINE(60, 2, "start to init syncv\n");
    if (*sid_p == -1) {
        VERBOSE_ON_LINE(62, 2, "start to create semaphore\n");
        
        sid = CreateSema2(NULL, 0x100, 0);
        
        
        
        
        
        
        
        
        
        if (sid != -1) {
            VERBOSE_ON_LINE(75, 2, "init semaphore\n");
            *sid_p = sid;
        } else 
            return 0;
    }

    if (*hid_p == -1) {
        VERBOSE_ON_LINE(82, 2, "start to add handler\n");
        hid = AddIntcHandler2(intc_cause, shSyncVHandler2, 0, (void* ) sid);
        if (hid != -1) {
            VERBOSE_ON_LINE(85, 2, "init handler\n");
            *hid_p = hid;
            EnableIntc(intc_cause);
        } else
            return 0;
    }

    VERBOSE_ON_LINE(92, 2, "success to init syncv\n");
    return 1;
}


int shSyncVStartInit(void) {
    return shSyncVInitSub(&shSyncVStart_sid, &shSyncVStart_hid, 2);
}


int shSyncVEndInit(void) {
    return shSyncVInitSub(&shSyncVEnd_sid, &shSyncVEnd_hid, 3);
}


int shSyncVSub(int mode, int sid) {
    int count; // r2
    u_short cnt0; // r2
    u_short cnt1; // r2
    

    
    
    if (sid == -1) {
        VERBOSE_ON_LINE(116, 2, "no init syncv\n");
        return -1;
    }
    if (mode != 0) {
        cnt0 = *T3_COUNT;
        WaitSema(sid);
        cnt1 = *T3_COUNT;
        count = (u_short) (cnt1 - cnt0);
        return count;
    }
    WaitSema(sid);
    count = 0;
    return count;
}


int shSyncVStart(int mode) {
    return shSyncVSub(mode, shSyncVStart_sid);
}


int shSyncVEnd(int mode) {
    return shSyncVSub(mode, shSyncVEnd_sid);
}

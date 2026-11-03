#include "Multi_thr/intc/th_vbs.h"

static void shMtIncVStartCount(void);

static void ThreadVbs(void* arg);

static u_long vcount_total; // size: 0x4, address: 0x11765B0
static u_long vcount; // size: 0x4, address: 0x11765A8
static int finish_sid = -1; // size: 0x4, address: 0x346B90
static int vbs_tid    = -1; // size: 0x4, address: 0x346B98




















static void shMtIncVStartCount(void) {
    vcount++;
    vcount_total++;
}




static void ThreadVbs(void* arg) {
    int wait_sid; // r2
    int ret; // r2

    wait_sid = (int)arg;

    if (wait_sid != -1) {


        SignalSema(WaitSema());
    }





    SignalSemaMax(finish_sid);



    vcount = 0;
    while(true) {


        shSyncVStart(0);
        shMtIncVStartCount();



        ret = dbFlowCheck();
        dbFlowCheckSleepTime(ret);








        Vcallback_test(GetThreadId());




    }
}
















int ThreadVbsStart(void* stack, int stackSize, int prio, int option, int wait_sid) {
    void* arg; // r16
    arg = (void*)wait_sid;
    if (finish_sid == -1) finish_sid = CreateSema2(0, 256, NULL);
    if (finish_sid != -1) {
        if (vbs_tid == -1) {
            vbs_tid = CreateThread2(ThreadVbs, stack, stackSize, prio, option);
            if (vbs_tid != -1) StartThread(vbs_tid, arg);
        }
    }


    return vbs_tid != -1 ? finish_sid : -1;
}

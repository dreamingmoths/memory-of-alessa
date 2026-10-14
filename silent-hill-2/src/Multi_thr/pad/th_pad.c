#include "th_pad.h"

static int finish_sid = -1; // size: 0x4, address: 0x33B588
static int pad_tid = -1; // size: 0x4, address: 0x33B590
//@note: reported in dwarf but never used.
thPadStruct curPad; // size: 0x20, address: 0x0
thPadStruct prvPad; // size: 0x20, address: 0x0

void ThreadPad(void*);

#line 36
static void ThreadPad(void* arg /* r2 */)  {
    int wait_sid; // r16
    u_int pow0;   // r16
    u_int pow1;   // r17
    if ((int)arg != -1) {
        VERBOSE(2, "wait by semaphore(mtapman.irx).\n"); //line 41

        SignalSema(WaitSema(arg));
    }

    VERBOSE(2, "going to init pad.\n"); //line 46


    libShPadEnable00();






    libShPadEnable10();


















    libShPadInit();
    if (dbFlag(16)) {
        scePadSetWarningLevel(0);
    }

    libShPadStart(0, 0);






    libShPadStart(1, 0);







    libShPadSetMode(0, 0, 1, 1, 1, 1);






    VERBOSE(2, "finished to init pad.\n"); //line 102

    SignalSemaMax(finish_sid);









    do {
        shSyncVEnd(0);

        libShPadTrans();


        if (dbFlag(8) != 0) {
            continue;
        }

        utilExclLockOtherThread();


        DSS_Wrapper_DualShock2_Sequencer();




        pow0 = DSS_Wrapper_DualShock2_Send_ActuaterLV_Get(0, 0);
        pow1 = DSS_Wrapper_DualShock2_Send_ActuaterLV_Get(0, 1);


        DSS_Wrapper_DualShock2_Send_ActuaterLV_Claer(0, 0);
        DSS_Wrapper_DualShock2_Send_ActuaterLV_Claer(0, 1);

        utilExclUnlockOtherThread();

        libShPadSend(0, 0, pow0, pow1);


































































    } while(true);
}






RODATA_PAD_TO(0x00391AD0);





int ThreadPadStart(void* stack /* r20 */, int stackSize /* r19 */, int prio /* r18 */, int option /* r17 */, int wait_sid /* r2 */) {

    void* arg = (void*)wait_sid;
    if (finish_sid == -1)  finish_sid = CreateSema2(NULL, 256, 0);
    if (finish_sid != -1) {
        if (pad_tid == -1) {
            pad_tid = CreateThread2(&ThreadPad, stack, stackSize, prio, option);
            if (pad_tid != -1) StartThread(pad_tid, arg);
        }
    }



    if (pad_tid != -1) return finish_sid; return -1;
}

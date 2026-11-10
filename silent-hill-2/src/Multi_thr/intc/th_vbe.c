#include "Multi_thr/intc/th_vbe.h"

static void ThreadVbe(void* arg);

static int finish_sid = -1; // size: 0x4, address: 0x33B428
static int vbe_tid    = -1; // size: 0x4, address: 0x33B430








static void ThreadVbe(void* arg) {
    int wait_sid; // r2
    int count; // r16

    wait_sid = (int)arg;
    if (wait_sid != -1)  {


        SignalSema(WaitSema());
    }





    SignalSemaMax(finish_sid);


    count = 0;
    while (true) {
        do {
            count++;

            shSyncVEnd(0);



            shSdVSync();





        } while(count % 300);
    fsSync(1, -1);











    }
}
















int ThreadVbeStart(void* stack, int stackSize, int prio, int option, int wait_sid) {

    void* arg = (void*)wait_sid; // r16
    if (finish_sid == -1) finish_sid = CreateSema2(0, 256, NULL);
    if (finish_sid != -1) {
        if (vbe_tid == -1) {
            vbe_tid = CreateThread2(ThreadVbe, stack, stackSize, prio, option);
            if (vbe_tid != -1) StartThread(vbe_tid, arg);
        }
    }


    return vbe_tid != -1 ? finish_sid : -1;
}


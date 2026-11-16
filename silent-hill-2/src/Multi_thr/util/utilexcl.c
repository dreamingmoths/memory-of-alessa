#include "Multi_thr/util/utilexcl.h"

static int lock_tid;      // size: 0x4, address: 0x0
static int excl_sid = -1; // size: 0x4, address: 0x2B64A0
















int utilExclInit(void) {
    int sid = -1; // r2
    if (excl_sid == sid) {
        sid = CreateSema2(0, 1, NULL);
        if (sid == -1) return 0;
        excl_sid = sid;
        SignalSema(excl_sid);
    }
    return 1;
}



int utilExclLockOtherThread(void) {
    if (excl_sid == -1) return 0;
    WaitSema(excl_sid);
    return 1;
}



int utilExclUnlockOtherThread(void) {
    if (excl_sid == -1) return 0;
    SignalSemaLimit(excl_sid);
    return 1;
}

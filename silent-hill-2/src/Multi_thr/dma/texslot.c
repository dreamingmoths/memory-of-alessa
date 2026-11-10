#include "Multi_thr/dma/texslot.h"
#include "sdk.h"


static texSlotCtrlT texSlotCtrl[5] = {}; // size: 0x50, address: 0x2B6450













int texSlotInit(void) {
    int i; // r16
    int sid; // r2
    for (i = 0; i < 5; i++) {
        if (!texSlotCtrl[i].init) {
            sid = CreateSema2(1, 1, "for exclusively using one of tex slots");
            if (sid != -1) {
                texSlotCtrl[i].sid = sid;
                texSlotCtrl[i].init = 1;
                texSlotCtrl[i].cur_texid = -1;
            }
        }
    }
    return true;
}


int texSlotBeginToUse(int slot) {
    if (0 <= slot && slot < 5) {
        WaitSema(texSlotCtrl[slot].sid);
        return true;
    }
    return false;
}


int texSlotFinishToUse(int slot) {
    if (0 <= slot && slot < 5) {
        SignalSema(texSlotCtrl[slot].sid);
        return true;
    }
    return false;
}


int texSlotGetCurTexID(int slot) {
    if (0 <= slot && slot < 5) {
        return texSlotCtrl[slot].cur_texid;
    }
    return -1;
}


int texSlotSetCurTexID(int slot, int texid) {
    if (0 <= slot && slot < 5) {
        texSlotCtrl[slot].cur_texid = texid; return texid;
    }
    return -1;
}


int texSlotClearAll(void) {
    int i; // r1
    for (i = 0; i < 5; i++) {
        texSlotSetCurTexID(i, -1);
    }
    return true;
}

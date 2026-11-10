#include "dma2tscmd.h"












int d2tscCmdBeginToUseSlot(int slot /* r2 */) {
    return texSlotBeginToUse(slot);
}

int d2tscBeginToUseSlot(int slot /* r2 */) {
    return D2S_PUT_CMD(1, d2tscCmdBeginToUseSlot, slot);
}






int d2tscCmdSend(int slot /* r19 */, int texid /* r18 */, void* tag /* r17 */) {
    int ret = 1; // r16
    int cur_texid; // r2
    cur_texid = texSlotGetCurTexID(slot);
    if (texid != cur_texid) {
        texSlotSetCurTexID(slot, texid);
        ret = d2cCmdSend(tag);
    }
    return ret;
}

int d2tscSend(int slot /* r8 */, int texid /* r3 */, void* tag /* r2 */) {
    return D2S_PUT_CMD(3, d2tscCmdSend, slot, texid, tag);
}



int d2tscCmdClearSlots(void) {
    return texSlotClearAll();
}

int d2tscClearSlots(void) {
    return D2S_PUT_CMD(0, d2tscCmdClearSlots);
}

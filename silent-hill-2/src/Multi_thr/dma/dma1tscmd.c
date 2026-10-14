#include "dma1tscmd.h"









int d1tscCmdSync(int d2cid) {
    return d2sSync(0, d2cid);
}

int d1tscSync(int d2cid) {
    return DMA1_PUT(1, d1tscCmdSync, d2cid);
}






int d1tscCmdFinishToUseSlot(int slot) {



    return texSlotFinishToUse(slot);
}

int d1tscFinishToUseSlot(int slot) {
    return DMA1_PUT(1, d1tscCmdFinishToUseSlot, slot);
}

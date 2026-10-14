#include "dma2cmd.h"







































int last_regist_cid; // size: 0x4, address: 0x10138B0
int last_flush_cid; // size: 0x4, address: 0x10138A8

static int d2cCmdInit(void);

void d2cSubCmdUpdataLastRegistCid(int cid /* r16 */) {

    utilExclLockOtherThread();
    if (cid >= 0) last_regist_cid = cid;
    utilExclUnlockOtherThread();
}



int d2cSubSubCmdCheckFlushCache(void) {
    int ret = 0; // r16
    int cur_id; // r17
    cur_id = d2sGetCurCmdId();
    utilExclLockOtherThread();
    if (d2sCmpCID(last_flush_cid, cur_id) < 0) {
        last_flush_cid = last_regist_cid;
        ret = 1;
    }
    utilExclUnlockOtherThread();
    return ret;
}


void d2cSubCmdFlushCache(void) {











    if (d2cSubSubCmdCheckFlushCache()) FlushCache(WRITEBACK_DCACHE);


}










static int d2cCmdInit(void) {
    return shDmaGifInit();
}


int d2cInit(void) {

    int ret = DMA2_PUT(0, d2cCmdInit);
    d2cSubCmdUpdataLastRegistCid(ret);
    return ret;
}












int d2cCmdSend(void* tag /* r16 */) {
    d2cSubCmdFlushCache();
    return shDmaGifSend(tag);
}

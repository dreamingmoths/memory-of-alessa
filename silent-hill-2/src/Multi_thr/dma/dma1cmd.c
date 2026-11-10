#include "dma1cmd.h"
#include "dma1serv.h"

static int last_regist_cid; // size: 0x4, address: 0x1013898
static int last_flush_cid; // size: 0x4, address: 0x1013890

static int d1cCmdInit(void);







































void d1cSubCmdUpdataLastRegistCid(int cid /* r16 */)  {

    utilExclLockOtherThread();
    if (cid >= 0) last_regist_cid = cid;
    utilExclUnlockOtherThread();
}



int d1cSubSubCmdCheckFlushCache(void) {
    int ret = 0; // r16
    int cur_cid; // r17
    cur_cid = d1sGetCurCmdId();
    utilExclLockOtherThread();
    if (d1sCmpCID(last_flush_cid, cur_cid) < 0) {
        last_flush_cid = last_regist_cid;
        ret = 1;
    }
    utilExclUnlockOtherThread();
    return ret;
}


void d1cSubCmdFlushCache(void) {











    if (d1cSubSubCmdCheckFlushCache()) FlushCache(WRITEBACK_DCACHE);


}










static int d1cCmdInit(void) {
    return shDmaVif1Init();
}


int d1cInit(void) {
    int ret;
    ret = D1S_PUT_CMD(0, d1cCmdInit);
    d1cSubCmdUpdataLastRegistCid(ret);
    return ret;
}












int d1cCmdSend(void* tag) {
    d1cSubCmdFlushCache();
    shDmaVif1Send(tag);
}


int d1cSend(void* tag) {
    int ret;
    ret = D1S_PUT_CMD(1, d1cCmdSend, tag);
    d1cSubCmdUpdataLastRegistCid(ret);
    return ret;
}

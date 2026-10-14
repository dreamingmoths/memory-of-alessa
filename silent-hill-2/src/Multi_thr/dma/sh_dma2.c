#include "sh_dma2.h"

static int excl_sid = -1; // size: 0x4, address: 0x2B6438
static int wait_sid = -1; // size: 0x4, address: 0x2B6440
static int dmac_hid = -1; // size: 0x4, address: 0x2B6448
int AA2_check; // size: 0x4, address: 0x10138C8

static int shDmaGifHandler(void);
static void shDmaGifHalt(void);
static int shDmaGifWait(void);




























static int shDmaGifHandler(void) {










    iSignalSemaLimit(wait_sid);
    ExitHandler();
    return 1;
}


static void shDmaGifHalt(void) {
    u_int chcr; // r4
    u_int enable; // r5

    enable = DGET_D_ENABLER();
    DPUT_D_ENABLEW(enable | D_ENABLER_CPND_M); // suspend channel transfers
    chcr = DGET_D2_CHCR();

    DPUT_D2_CHCR(chcr & ~D_CHCR_STR_M); // stop DMA
    DPUT_D_ENABLEW(enable); // return channel transfers to previous state
}



static int shDmaGifWait(void) {
    int count ; // r16
    u_short h0; // r2
    u_short h1; // r17
    count = 0;
    h1 = DGET_T3_COUNT();
    while (DGET_D2_CHCR() & D_CHCR_STR_M) { // is DMA running?

        h0 = h1;
        h1 = DGET_T3_COUNT();
        if (h0 != h1) {
            count++;
            if (!(count % 263)) {
                VERBOSE(3, "DMA-2 busy...\n"); //line 83
            }
        }
    }
    return count;
}










int shDmaGifInit(void) {
    u_int chcr; // r2
    int ret; // r16


    if (excl_sid == -1) excl_sid = CreateSema2(NULL, 1, 0);
    else WaitSema(excl_sid);

    if (wait_sid == -1) wait_sid = CreateSema2(NULL, 1, 0);

    shDmaGifHalt();
    DPUT_D_STAT(D_STAT_CIS2_M); // clear CIS2 interrupts

    DPUT_D2_CHCR(D_CHCR_TTE_M); // transfer DMAtag


    if ((excl_sid != -1) && (wait_sid != -1) && (dmac_hid == -1)) {

        dmac_hid = AddDmacHandler(2, shDmaGifHandler, -1);
        EnableDmac(2);
    }

    ret = dmac_hid != -1;
    if (ret) SignalSemaLimit(excl_sid);
    return ret;
}



int shDmaGifSend(void* packet) {
    u_int chcr;
    if (dmac_hid != -1) {

        AA2_check = 1;

        WaitSema(excl_sid);

        AA2_check = 2;

        DPUT_D2_TADR((u_int)packet);
        DPUT_D2_QWC(D_QWC_QWC_O);
        chcr = DGET_D2_CHCR();



        FlushCache(WRITEBACK_DCACHE);

        PollSemaAll(wait_sid);

        DPUT_D2_CHCR((chcr & ~(D_CHCR_MOD_M | D_CHCR_DIR_M)) | D_CHCR_DIR_M | (D_CHCR_MOD_M & 1 << 2) | D_CHCR_STR_M); // from memory on chain mode. Set busy

        AA2_check = 3;

        WaitSema(wait_sid);

        AA2_check = 4;

        if (shDmaGifWait() > 0) {


            verbose(3, "why wait for stop DMA-2 ?\n"); //no line num
        }

        chcr = DGET_D2_CHCR();
        if ((chcr & 0x70000000) != 0x70000000) { //is dma tag id equal to end?
            verbose(3,
                    DEBUG_TEXT("DMA-2 don't normally finished.\n")
                    DEBUG_TEXT("    D2_CHCR: 0x%08x\n")
                    DEBUG_TEXT("    D2_TADR: 0x%08x\n")
                    DEBUG_TEXT("    D2_MADR: 0x%08x\n")
                    DEBUG_TEXT("    D2_QWC : 0x%08x\n"),
                    chcr, DGET_D2_TADR(), DGET_D2_MADR(), DGET_D2_QWC()); // line 165-169
        }


        AA2_check = 5;

        SignalSemaLimit(excl_sid);

        AA2_check = 6;
    }
    return 1;
}

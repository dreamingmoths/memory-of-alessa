#include "sh_dma1.h"

static int excl_sid = -1; // size: 0x4, address: 0x2B6420
static int wait_sid = -1; // size: 0x4, address: 0x2B6428
static int dmac_hid = -1; // size: 0x4, address: 0x2B6430
int AA1_check; // size: 0x4, address: 0x10138C0

static int shDmaVif1Handler(void);
static void shDmaVif1Halt(void);
static int shDmaVif1Wait(void);
































static int shDmaVif1Handler(void) {










    iSignalSemaLimit(wait_sid);
    ExitHandler();
    return 1;
}


static void shDmaVif1Halt(void) {
    u_int chcr; // r4
    u_int enable; // r5

    enable = *D_ENABLER;
    DPUT_D_ENABLEW(enable | D_ENABLER_CPND_M); // suspend channel transfers
    chcr = DGET_D1_CHCR();

    DPUT_D1_CHCR(chcr & ~D_CHCR_STR_M); // stop DMA
    DPUT_D_ENABLEW(enable); // return channel transfers to previous state
}



static int shDmaVif1Wait(void) {
    int count; // r16
    u_short h0; // r2
    u_short h1; // r17
    count = 0;
    h1 = DGET_T3_COUNT();
    while (DGET_D1_CHCR() & D_CHCR_STR_M) { // is DMA running?

        h0 = h1;
        h1 = DGET_T3_COUNT();
        if (h0 != h1) {
            count++;
            if (!(count % 263)) {
                VERBOSE(3, "DMA-1 busy...\n"); // line 87
            }
        }
    }
    return count;
}










int shDmaVif1Init(void) {
    u_int chcr; // r2
    int ret; // r16


    if (excl_sid == -1) excl_sid = CreateSema2(NULL, 1, 0);
    else WaitSema(excl_sid);

    if (wait_sid == -1) wait_sid = CreateSema2(NULL, 1, 0);

    shDmaVif1Halt();
    DPUT_D_STAT(D_STAT_CIS1_M); // clear CIS1 interrupts

    DPUT_D1_CHCR(D_CHCR_TTE_M); // transfer DMAtag


    if ((excl_sid != -1) && (wait_sid != -1) && (dmac_hid == -1)) {

        dmac_hid = AddDmacHandler(1, shDmaVif1Handler, -1);
        EnableDmac(1);
    }

    ret = dmac_hid != -1;
    if (ret) SignalSemaLimit(excl_sid);
    return ret;
}



int shDmaVif1Send(void* packet) {
    u_int chcr;
    if (dmac_hid != -1) {

        AA1_check = 1;

        WaitSema(excl_sid);

        AA1_check = 2;

        DPUT_D1_TADR((u_int)packet);
        DPUT_D1_QWC(D_QWC_QWC_O);
        chcr = DGET_D1_CHCR();





        PollSemaAll(wait_sid);

        DPUT_D1_CHCR((chcr & ~(D_CHCR_MOD_M | D_CHCR_DIR_M)) | D_CHCR_DIR_M | (D_CHCR_MOD_M & 1 << 2) | D_CHCR_STR_M); // from memory on chain mode. Set busy

        AA1_check = 3;

        WaitSema(wait_sid);

        AA1_check = 4;

        if (shDmaVif1Wait() > 0) {


            VERBOSE(3, "why wait for stop DMA-1 ?\n"); //line 163
        }

        chcr = DGET_D1_CHCR();
        if ((chcr & 0x70000000) != 0x70000000) {
            verbose(3,
                    DEBUG_TEXT("DMA-1 don't normally finished.\n")
                    DEBUG_TEXT("    D1_CHCR: 0x%08x\n")
                    DEBUG_TEXT("    D1_TADR: 0x%08x\n")
                    DEBUG_TEXT("    D1_MADR: 0x%08x\n")
                    DEBUG_TEXT("    D1_QWC : 0x%08x\n"),
                    chcr, DGET_D1_TADR(), DGET_D1_MADR(), DGET_D1_QWC()); //line 169-173
        }


        AA1_check = 5;

        SignalSemaLimit(excl_sid);

        AA1_check = 6;
    }
    return 1;
}

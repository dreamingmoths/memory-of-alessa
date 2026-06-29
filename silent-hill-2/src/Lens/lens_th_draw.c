#include "sh2_common.h"
#include "eestruct.h"
#include "eeregs.h"
#include "libgraph.h"

#define MAXWAIT	0x1000000

/* #define ENABLE_LENS_TH_DRAW_REMOVED_CODE */

int sh2gfw_GsSetDefStoreImage(sceGsStoreImage* sp, short sbp, short sbw, short spsm, short x, short y, short w, short h) {
    sp->vifcode[0] = 0 /* nop */;
    sp->vifcode[1] = 0 /* nop */;
    sp->vifcode[2] = SCE_VIF1_SET_FLUSHA(0);
    sp->vifcode[3] = SCE_VIF1_SET_DIRECT(6, 0);
    *(u_long128*)&sp->giftag = 0;
    sp->giftag.NLOOP = 5;
    sp->giftag.EOP = 1;
    sp->giftag.NREG = 1;
    sp->giftag.REGS0 = SCE_GIF_PACKED_AD;

    *(u_long*)&sp->bitbltbuf =
        SCE_GS_SET_BITBLTBUF(sbp, sbw, spsm, 0, 0, 0);
    sp->bitbltbufaddr = (long)SCE_GS_BITBLTBUF;

    *(u_long*)&sp->trxpos = SCE_GS_SET_TRXPOS(x, y, 0, 0, 0);
    sp->trxposaddr = (long)SCE_GS_TRXPOS;

    *(u_long*)&sp->trxreg = SCE_GS_SET_TRXREG(w, h);
    sp->trxregaddr = (long)SCE_GS_TRXREG;

    *(u_long*)&sp->finish = (u_long)0;
    sp->finishaddr = (long)SCE_GS_FINISH;

    *(u_long*)&sp->trxdir = SCE_GS_SET_TRXDIR(1);
    sp->trxdiraddr = (long)SCE_GS_TRXDIR;

    asm volatile("sync.l");

    return 7;
}

int sh2gfw_GsExecStoreImage(sceGsStoreImage* sp, u_long128* dstaddr) {
    static u_int init_mp3[4] __attribute__((aligned(16))) = {
        0x06000000,
        0x00000000,
        0x00000000,
        0x00000000,
    };
    u_int vcnt = 0;
    int w, h, i;
    int dmasizeq, allsizeq, rsizeq;
    int remq, remb, ah, sizeb;
    u_char tmpbuf[16];
    u_long oldIMR;

    w = sp->trxreg.RRW;
    h = sp->trxreg.RRH;

    switch (sp->bitbltbuf.SPSM) {
        case SCE_GS_PSMCT32:
        case SCE_GS_PSMZ32:
            sizeb = (((int)w * (int)h) << 2);
            remb = sizeb & 0xf;
            remq = (sizeb >> 4) & 0x7;
            dmasizeq = (sizeb >> 4) & 0xfffffff8;
            if (remb == 0) {
                rsizeq = 0;
                ah = h;
            } else {
                ah = (h + 3) & 0xfffffffc;
                allsizeq = ((int)w * ah) >> 2;
                rsizeq = allsizeq - dmasizeq - remq - 1;
            }
            break;
        case SCE_GS_PSMCT24:
        case SCE_GS_PSMZ24:
            sizeb = ((int)w * (int)h * 3);
            remb = sizeb & 0xf;
            remq = (sizeb >> 4) & 0x7;
            dmasizeq = (sizeb >> 4) & 0xfffffff8;
            if (remb == 0) {
                rsizeq = 0;
                ah = h;
            } else {
                ah = (h + 15) & 0xfffffff0;
                allsizeq = ((int)w * ah * 3) >> 4;
                rsizeq = allsizeq - dmasizeq - remq - 1;
            }
            break;
        case SCE_GS_PSMCT16:
        case SCE_GS_PSMCT16S:
        case SCE_GS_PSMZ16:
        case SCE_GS_PSMZ16S:
            sizeb = (((int)w * (int)h) << 1);
            remb = sizeb & 0xf;
            remq = (sizeb >> 4) & 0x7;
            dmasizeq = (sizeb >> 4) & 0xfffffff8;
            if (remb == 0) {
                rsizeq = 0;
                ah = h;
            } else {
                ah = (h + 7) & 0xfffffff8;
                allsizeq = ((int)w * ah) >> 3;
                rsizeq = allsizeq - dmasizeq - remq - 1;
            }
            break;
        case SCE_GS_PSMT8:
        case SCE_GS_PSMT8H:
            sizeb = ((int)w * (int)h);
            remb = sizeb & 0xf;
            remq = (sizeb >> 4) & 0x7;
            dmasizeq = (sizeb >> 4) & 0xfffffff8;
            if (remb == 0) {
                rsizeq = 0;
                ah = h;
            } else {
                ah = (h + 7) & 0xfffffff8;
                allsizeq = ((int)w * ah) >> 4;
                rsizeq = allsizeq - dmasizeq - remq - 1;
            }
            break;
        case SCE_GS_PSMT4:
        case SCE_GS_PSMT4HL:
        case SCE_GS_PSMT4HH:
            sizeb = (((int)w * (int)h) >> 1);
            remb = sizeb & 0xf;
            remq = (sizeb >> 4) & 0x7;
            dmasizeq = (sizeb >> 4) & 0xfffffff8;
            if (remb == 0) {
                rsizeq = 0;
                ah = h;
            } else {
                ah = (h + 7) & 0xfffffff8;
                allsizeq = ((int)w * ah) >> 5;
                rsizeq = allsizeq - dmasizeq - remq - 1;
            }
            break;
    }

    if (remb != 0) {
        *(u_long*)(((u_int)(&(sp->trxreg))) | 0x20000000) =
            (u_long)(sp->trxreg.RRW) | ((u_long)ah << 32);
    }

#ifdef ENABLE_LENS_TH_DRAW_REMOVED_CODE
    while (DGET_D1_CHCR() & 0x0100) {
        if ((vcnt++) > MAXWAIT) {
            scePrintf("sceGsExecStoreImage: DMA Ch.1 does not terminate\r\n");
            return -1;
        }
    }
#endif

    d1sSync(0, -1);
    d2sSync(0, -1);

    oldIMR = sceGsPutIMR(sceGsGetIMR() | 0x0200);
    DPUT_GS_CSR(0x02);

    DPUT_D1_QWC(7);
    if (((u_int)sp & 0x70000000) == 0x70000000)
        DPUT_D1_MADR((((u_int)sp & 0x0fffffff) | 0x80000000));
    else
        DPUT_D1_MADR(((u_int)sp & 0x0fffffff));
    DPUT_D1_CHCR((1 | (1 << 8)));

    while (DGET_D1_CHCR() & 0x0100) {
#ifdef ENABLE_LENS_TH_DRAW_REMOVED_CODE
        if ((vcnt++) > MAXWAIT) {
            scePrintf("sceGsExecStoreImage: DMA Ch.1 does not terminate\r\n");
            return -1;
        }
#endif
    }

    while ((DGET_GS_CSR() & 0x02) == 0) {
#ifdef ENABLE_LENS_TH_DRAW_REMOVED_CODE
        if ((vcnt++) > MAXWAIT) {
            scePrintf("sceGsExecStoreImage: GS does not terminate\r\n");
            DPUT_VIF1_FIFO(*(u_long128*)init_mp3);
            return -1;
        }
#endif
    }

    *VIF1_STAT = 0x00800000;
    DPUT_GS_BUSDIR((u_long)0x00000001);

    DPUT_D1_QWC(dmasizeq);

    if (((u_int)dstaddr & 0x70000000) == 0x70000000)
        DPUT_D1_MADR((((u_int)dstaddr & 0x0fffffff) | 0x80000000));
    else
        DPUT_D1_MADR(((u_int)dstaddr & 0x0fffffff));

    DPUT_D1_CHCR(1 << 8);

    while (DGET_D1_CHCR() & 0x0100) {
#ifdef ENABLE_LENS_TH_DRAW_REMOVED_CODE
        if ((vcnt++) > MAXWAIT) {
            scePrintf("sceGsExecStoreImage: DMA Ch.1 (GS->MEM) does not terminate\r\n");
            DPUT_GS_CSR((u_long)0x00000100);
            DPUT_GS_BUSDIR((u_long)0);
            DPUT_GIF_CTRL(0x00000001);
            DPUT_VIF1_FBRST(1);
            return -1;
        }
#endif
    }

    for (i = 0; i < remq; i++) {
#ifdef ENABLE_LENS_TH_DRAW_REMOVED_CODE
        while ((*VIF1_STAT & 0x1f000000) == 0) {
            if ((vcnt++) > MAXWAIT) {
                scePrintf("sceGsExecStoreImage: Enough data does not reach VIF1\n");
                DPUT_GS_CSR((u_long)0x00000100);
                DPUT_GS_BUSDIR((u_long)0);
                DPUT_GIF_CTRL(0x00000001);
                DPUT_VIF1_FBRST(1);
                return -1;
            }
        }
#endif

        ((u_long128*)dstaddr)[dmasizeq + i] = DGET_VIF1_FIFO();
    }

    if (remb) {
#ifdef ENABLE_LENS_TH_DRAW_REMOVED_CODE
        while ((*VIF1_STAT & 0x1f000000) == 0) {
            if ((vcnt++) > MAXWAIT) {
                scePrintf("sceGsExecStoreImage: Enough data does not reach VIF1\n");
                DPUT_GS_CSR((u_long)0x00000100);
                DPUT_GS_BUSDIR((u_long)0);
                DPUT_GIF_CTRL(0x00000001);
                DPUT_VIF1_FBRST(1);
                return -1;
            }
        }
#endif
        *(u_long128*)&tmpbuf = DGET_VIF1_FIFO();
        for (i = 0; i < remb; i++) {
            ((u_char*)((u_long128*)&dstaddr[dmasizeq + remq]))[i] =
                tmpbuf[i];
        }
        for (i = 0; i < rsizeq; i++) {
#ifdef ENABLE_LENS_TH_DRAW_REMOVED_CODE
            while ((*VIF1_STAT & 0x1f000000) == 0) {
                if ((vcnt++) > MAXWAIT) {
                    scePrintf("sceGsExecStoreImage: Enough data does not reach VIF1\n");
                    DPUT_GS_CSR((u_long)0x00000100);
                    DPUT_GS_BUSDIR((u_long)0);
                    DPUT_GIF_CTRL(0x00000001);
                    DPUT_VIF1_FBRST(1);
                    return -1;
                }
            }
#endif
            *(u_long128*)&tmpbuf = DGET_VIF1_FIFO();
        }
    }

    *VIF1_STAT = 0;
    DPUT_GS_BUSDIR((u_long)0);

    sceGsPutIMR(oldIMR);
    DPUT_GS_CSR(0x02);

    DPUT_VIF1_FIFO(*(u_long128*)init_mp3);

    DPUT_D1_CHCR(0x45);
}

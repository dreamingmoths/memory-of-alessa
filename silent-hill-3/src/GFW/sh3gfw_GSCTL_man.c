#include "common.h"
#include "GFW/sh3gfw_GSCTL_man.h"

/**
 * @note: this file is unfinished!
 */

#define GSCTL_man Gman
extern Q_WORDDATA GSENV_CTL_PACK[1024];
extern G_MAN GSCTL_man;

void sh3gfw_init_GSPACKMAN(void) {
    Gman.main_num = 0;
    Gman.transnum = 0;
    Gman.GS_kick  = GSENV_CTL_PACK;
    Gman.GS_tail  = GSENV_CTL_PACK;
    return;
}

Q_WORDDATA* func_001CDAF0(void) {
    // @note: size of `GSENV_CTL_PACK` could be wrong?
    return &GSENV_CTL_PACK[0x100];
}

void sh3gfw_setREF_gsctl(Q_WORDDATA* gt) {
    Q_WORDDATA* qwd = GSCTL_man.GS_tail;

    u_short leng      = ((gt->us16[0] & 0x7FFF) + 1);
    qwd->ui32[0]      = DMAref | leng;
    qwd->ui32[1]      = (u_long) gt & 0x7FFFFFFF;
    qwd->ui32[2]      = 0;
    qwd->ui32[3]      = 0;
    qwd->ui32[3]      = DMAcall | leng;
    GSCTL_man.GS_tail = qwd + 1;
}

void sh3gfw_setREF_tagchain(Q_WORDDATA** pqwd, Q_WORDDATA* gt) {
    Q_WORDDATA* qwd = *pqwd;

    u_short leng = ((gt->us16[0] & 0x7FFF) + 1);
    qwd->ui32[0] = DMAref | leng;
    qwd->ui32[1] = (u_long) gt & 0x7FFFFFFF;
    qwd->ui32[2] = 0;
    qwd->ui32[3] = 0;
    qwd->ui32[3] = DMAcall | leng;
    *pqwd        = qwd + 1;
}

Q_WORDDATA* sh3gfw_setEND_gsctl(void) {
    Q_WORDDATA* qwd = GSCTL_man.GS_tail;

    qwd->ui32[0]      = DMAend;
    qwd->ui32[1]      = 0;
    qwd->ul64[1]      = 0;
    qwd               = GSCTL_man.GS_kick;
    GSCTL_man.GS_tail = GSCTL_man.GS_tail + 1;
    GSCTL_man.GS_kick = GSCTL_man.GS_tail;
    return qwd;
}

#define SCE_VIF1_SET_FLUSH(irq) (((u_int)0x11 << 24) | ((u_int)(irq) << 31))

#define SCE_VIF1_SET_DIRECT(count, irq) ((u_int)(count) | ((u_int)(0x50) << 24) | ((u_int)(irq) << 31))

/* perhaps: sh3gfw_setCOUNT_TEXFLUSH */
/* was a reftag in sh2 */
void sh3gfw_0x001cdbf0(void) {
    Q_WORDDATA* qwd = GSCTL_man.GS_tail;
    qwd->ui32[0]    = DMAcnt | 2;
    qwd->ui32[1]    = 0 /* (u_int) shGs_AllEnv.GsSync_DummyTEXFLUSH */;
    qwd->ui32[2]    = SCE_VIF1_SET_FLUSH(0);
    qwd->ui32[3]    = SCE_VIF1_SET_DIRECT(2, 0);

    // @todo: add macros
    qwd[1].ui32[3]    = 0;
    qwd[1].ui32[2]    = 0xE;
    qwd[1].ui32[1]    = DMAcnt;
    qwd[1].ui32[0]    = 0x8001;
    qwd[2].ul64[1]    = 0x3F;
    qwd[2].ul64[0]    = 0;
    GSCTL_man.GS_tail = qwd + 3;
}

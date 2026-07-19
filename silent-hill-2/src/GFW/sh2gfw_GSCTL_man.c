#include "sh2_common.h"
#include "GFW/sh2gfw_GSCTL_man.h"
#include "GFW/sh2_GsAllEnv.h"

Q_WORDDATA GSENV_CTL_PACK[1024]; // size: 0x4000, address: 0xE3C260
G_MAN GSCTL_man; // size: 0x10, address: 0xE3C250

void sh2gfw_init_GSPACKMAN(G_MAN* Gman) {
    Gman->GS_kick  = GSENV_CTL_PACK;
    Gman->GS_tail  = GSENV_CTL_PACK;
    Gman->main_num = 0;
    Gman->transnum = 0;
    return;
}

void sh2gfw_setREF_gsctl(Q_WORDDATA* gt) {
    Q_WORDDATA* qwd = GSCTL_man.GS_tail; // r6

    u_short leng      = ((gt->us16[0] & 0x7FFF) + 1); // r2
    qwd->ui32[0]      = DMAref | leng;
    qwd->ui32[1]      = (u_long) gt & 0x7FFFFFFF;
    qwd->ui32[2]      = 0;
    qwd->ui32[3]      = 0;
    qwd->ui32[3]      = DMAcall | leng;
    GSCTL_man.GS_tail = qwd + 1;
}

void sh2gfw_setREF_tagchain(Q_WORDDATA** pqwd, Q_WORDDATA* gt) {
    Q_WORDDATA* qwd = *pqwd; // r6

    u_short leng = ((gt->us16[0] & 0x7FFF) + 1); // r2
    qwd->ui32[0] = DMAref | leng;
    qwd->ui32[1] = (u_long) gt & 0x7FFFFFFF;
    qwd->ui32[2] = 0;
    qwd->ui32[3] = 0;
    qwd->ui32[3] = DMAcall | leng;
    *pqwd        = qwd + 1;
}

Q_WORDDATA* sh2gfw_setEND_gsctl(void) {
    Q_WORDDATA* qwd = GSCTL_man.GS_tail;

    qwd->ui32[0]      = DMAend;
    qwd->ui32[1]      = 0;
    qwd->ul64[1]      = 0;
    GSCTL_man.GS_tail = qwd + 1;
    qwd               = GSCTL_man.GS_kick;
    GSCTL_man.GS_kick = GSCTL_man.GS_tail;
    return qwd;
}

#define SCE_VIF1_SET_MARK(mark, irq) ((u_int)(mark) | ((u_int)0x07 << 24) | ((u_int)(irq) << 31))

void sh2gfw_setCALL_gsctl(Q_WORDDATA* pf) {
    Q_WORDDATA* qwd   = GSCTL_man.GS_tail;
    qwd->ui32[0]      = DMAcall;
    qwd->ui32[1]      = (u_int) pf;
    qwd->ui32[2]      = SCE_VIF1_SET_MARK(0x9999, 0);
    qwd->ui32[3]      = 0;
    GSCTL_man.GS_tail = qwd + 1;
}

#define SCE_VIF1_SET_FLUSH(irq) (((u_int)0x11 << 24) | ((u_int)(irq) << 31))

#define SCE_VIF1_SET_DIRECT(count, irq) ((u_int)(count) | ((u_int)(0x50) << 24) | ((u_int)(irq) << 31))

void sh2gfw_setREF_TEXFLUSH(void) {
    Q_WORDDATA* qwd   = GSCTL_man.GS_tail;
    qwd->ui32[0]      = DMAref | 2;
    qwd->ui32[1]      = (u_int) shGs_AllEnv.GsSync_DummyTEXFLUSH;
    qwd->ui32[2]      = SCE_VIF1_SET_FLUSH(0);
    qwd->ui32[3]      = SCE_VIF1_SET_DIRECT(2, 0);
    GSCTL_man.GS_tail = qwd + 1;
}

#include "common.h"
#include "sce/libgraph.h"
#include "GFW/sh3gfw_GSCTL_man.h"

extern Q_WORDDATA GSENV_CTL_PACK[1024];
extern G_MAN GSCTL_man;

// @sh3 in the sh2 proto the G-man was passed in as a pointer
void sh3gfw_init_GSPACKMAN(void) {
    GSCTL_man.main_num = 0;
    GSCTL_man.transnum = 0;
    GSCTL_man.GS_kick  = GSENV_CTL_PACK;
    GSCTL_man.GS_tail  = GSENV_CTL_PACK;
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

#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_GSCTL_man", sh3gfw_setEND_gsctl);
#endif

static inline void set_giftag(Q_WORDDATA* qwd, u_long arg0, u_long arg1) {
    qwd->ui32[3] = arg1 >> 0x20;
    qwd->ui32[2] = arg1;
    qwd->ui32[1] = arg0 >> 0x20;
    qwd->ui32[0] = arg0;
}

/* perhaps: sh3gfw_setCOUNT_TEXFLUSH */
/* was a reftag in sh2 */
void sh3gfw_0x001cdbf0(void) {
    Q_WORDDATA* qwd = GSCTL_man.GS_tail;
    qwd->ui32[0]    = DMAcnt | 2;
    qwd->ui32[1]    = 0 /* @sh3: in the sh2 proto, (u_int) shGs_AllEnv.GsSync_DummyTEXFLUSH */;
    qwd->ui32[2]    = SCE_VIF1_SET_FLUSH(0);
    qwd->ui32[3]    = SCE_VIF1_SET_DIRECT(2, 0);

    // thanks ethanol for the macros :)
    set_giftag(&qwd[1], SCE_GIF_SET_TAG(1, SCE_GS_TRUE, 0, 0, SCE_GIF_PACKED, 1), 0xE);
    qwd[2].ul64[1]    = SCE_GS_TEXFLUSH;
    qwd[2].ul64[0]    = 0;
    GSCTL_man.GS_tail = qwd + 3;
}

#ifndef SH3GFW_GSCTL_MAN_H
#define SH3GFW_GSCTL_MAN_H

#include "common.h"

typedef struct /* @anon3 */ {
    // total size: 0x10
    Q_WORDDATA* GS_kick; // offset 0x0, size 0x4
    Q_WORDDATA* GS_tail; // offset 0x4, size 0x4
    u_short main_num; // offset 0x8, size 0x2
    u_short transnum; // offset 0xA, size 0x2
    u_int pad1; // offset 0xC, size 0x4
} G_MAN;

void sh3gfw_init_GSPACKMAN(void);
void sh3gfw_setREF_gsctl(Q_WORDDATA* gt);
void sh3gfw_setREF_tagchain(Q_WORDDATA** pqwd, Q_WORDDATA* gt);
Q_WORDDATA* sh3gfw_setEND_gsctl(void);
void sh3gfw_setCALL_gsctl(Q_WORDDATA* pf);
void sh3gfw_setREF_TEXFLUSH(void);

#endif // SH3GFW_GSCTL_MAN_H

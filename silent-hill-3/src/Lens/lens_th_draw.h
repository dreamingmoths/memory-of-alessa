#ifndef LENS_TH_DRAW_H
#define LENS_TH_DRAW_H

#include "eetypes.h"
#include "libgraph.h"

int sh3gfw_GsExecStoreImage(sceGsStoreImage* sp, u_long128* dstaddr);
int sh3gfw_GsSetDefStoreImage(sceGsStoreImage* sp, short sbp, short sbw, short spsm, short x, short y, short w, short h);

#endif // LENS_TH_DRAW_H

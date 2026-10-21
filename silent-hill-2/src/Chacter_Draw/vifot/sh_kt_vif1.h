#ifndef SH_KT_VIF1_H
#define SH_KT_VIF1_H

#include "sce/libdma.h"

typedef struct Vif1Work {
    sceDmaChan* dma;
} Vif1Work;

void ktVif1Init(void);

#endif // SH_KT_VIF1_H

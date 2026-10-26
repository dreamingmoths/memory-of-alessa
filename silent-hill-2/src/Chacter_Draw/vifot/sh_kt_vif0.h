#ifndef SH_KT_VIF0
#define SH_KT_VIF0

#include "sce/libdma.h"

typedef struct {
    sceDmaChan* dma;
} Vif0Work;

void ktVif0Init(void);

void ktVif0Wait(void);

void ktVif0Wait2(void);

void ktVif0Send(void* p, int tte);

#endif

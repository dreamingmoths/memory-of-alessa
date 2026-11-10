#include "Chacter_Draw/vifot/sh_kt_vif1.h"
#include "sce/libdma.h"

Vif1Work vif1_work;


#line 34
void ktVif1Init() {
    memset(&vif1_work, 0, sizeof(vif1_work));

    vif1_work.dma = sceDmaGetChan(SCE_DMA_VIF1);
}

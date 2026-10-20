#include "Chacter_Draw/vifot/sh_kt_vif1.h"

extern sceDmaChan* sceDmaGetChan(int id);
extern Vif1Work vif1_work;


#line 34
void ktVif1Init(void) {
    memset(&vif1_work, 0, sizeof(vif1_work));

    vif1_work.dma = sceDmaGetChan(SCE_DMA_VIF1);
}
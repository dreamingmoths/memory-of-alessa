#include "sh2_common.h"
#include "Chacter_Draw/vifot/sh_kt_vif0.h"
#include "sce/eeregs.h"

UNMIGRATED(Vif0Work vif0_work); // size: 0x4, address: 0x3E66D0


#line 34
void ktVif0Init() {
    memset(&vif0_work, 0, 4);
    
    vif0_work.dma = sceDmaGetChan(0);
}

#line 56
void ktVif0Wait() {
    
    
    
    
    
    
    
    BLOCK_WHILE((sceDmaSync(vif0_work.dma, 0, 0)));





}

#line 79
void ktVif0Wait2() {
    ktVif0Wait();
    
    BLOCK_WHILE((*VIF0_STAT & 0x0F000003));
}

#line 91
void ktVif0Send(void* p, int tte) {
    ktVif0Wait();
    vif0_work.dma->chcr.TTE = tte;
    sceDmaSend(vif0_work.dma, p);
}

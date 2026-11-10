#ifndef DMA1TSCMD_H
#define DMA1TSCMD_H

#include "Multi_thr/dma/dma1serv.h"
#include "Multi_thr/dma/dma2serv.h"
#include "Multi_thr/dma/texslot.h"

int d1tscCmdSync(int d2cid);

int d1tscSync(int d2cid);

int d1tscCmdFinishToUseSlot(int slot);

int d1tscFinishToUseSlot(int slot);

#endif // DMA1TSCMD_H

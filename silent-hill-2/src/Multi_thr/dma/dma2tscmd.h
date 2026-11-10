#ifndef DMA2TSCMD_H
#define DMA2TSCMD_H

#include "Multi_thr/dma/dma2serv.h"
#include "Multi_thr/dma/texslot.h"

int d2tscCmdBeginToUseSlot(int slot);

int d2tscBeginToUseSlot(int slot);

int d2tscCmdSend(int slot, int texid, void* tag);

int d2tscSend(int slot, int texid, void* tag);

int d2tscCmdClearSlots(void);

int d2tscClearSlots(void);

#endif // DMA2TSCMD_H

#ifndef DMA1CMD_H
#define DMA1CMD_H

#include "Multi_thr/dma/dma1serv.h"
#include "Multi_thr/util/utilexcl.h"
#include "sce/sif.h"

void d1cSubCmdUpdataLastRegistCid(int cid /* r16 */);

int d1cSubSubCmdCheckFlushCache(void);

void d1cSubCmdFlushCache(void);

int d1cInit(void);

int d1cCmdSend(void* tag /* r16 */);

int d1cSend(void* tag /* r2 */);

#endif // DMA1CMD_H

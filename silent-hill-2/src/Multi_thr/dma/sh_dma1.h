#ifndef SH_DMA1_H
#define SH_DMA1_H

#include "sce/eekernel.h"
#include "sce/eeregs.h"
#include "sce/sif.h"

int shDmaVif1Init(void);

int shDmaVif1Send(void* packet /* r16 */);

#endif // SH_DMA1_H

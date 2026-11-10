#ifndef SH2_CH_MALLOC_H
#define SH2_CH_MALLOC_H

#include "sh2_common.h"
#include "Heap/utilheap.h"

utilHeapCtrl* shCh_ASC_InitHead(void* bufhead, int size);
void* shCh_ASC_Malloc(u_int n);
void shCh_ASC_Free(void* p);
void kari_ChAlloc_Init(void);

#endif // SH2_CH_MALLOC_H

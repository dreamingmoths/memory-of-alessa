#ifndef SH2_CH_MALLOC_H
#define SH2_CH_MALLOC_H

#include "common.h"
#include "Heap/utilheap.h"

void * shCh_ASC_Malloc(u_int n /* r17 */);
utilHeapCtrl * shCh_ASC_InitHead(void * bufhead /* r16 */, int size /* r2 */);
void shCh_ASC_Free(void * p /* r2 */);
void kari_ChAlloc_Init(void);

extern utilHeapCtrl * shCh_ASCDAT_Ctrl; // size: 0x4, address: 0xF8E708
extern u_long128 Anim_Skl_Cls_Data[32772]; // size: 0x80040, address: 0xF8E710

#endif // SH2_CH_MALLOC_H

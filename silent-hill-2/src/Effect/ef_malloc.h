#ifndef EF_MALLOC_H
#define EF_MALLOC_H

#include "common.h"
#include "Heap/utilheap.h"

void * EfctInitHeap(void * buf /* r16 */, u_int size /* r2 */);
void * EfctMalloc(u_int n /* r17 */);
void EfctFree(void * obj);

extern utilHeapCtrl * EfctCtrl;

#endif // EF_MALLOC_H

#include "ef_malloc.h"

void * EfctInitHeap(void * buf /* r16 */, u_int size /* r2 */) {
    EfctCtrl = utilHeapInit(buf, size);
    if (buf != EfctCtrl) {
        printf("ef_malloc.c:18> address mismatch.\n");
    }
    return EfctCtrl;
}

void * EfctMalloc(u_int n /* r17 */) {
    void * p;    
    if (EfctCtrl == NULL) {
        return NULL;
    }    
    p = utilHeapMalloc(EfctCtrl, n);    
    if (p == NULL) {
        printf("ef_malloc.c:36> can't allocated.\n");
    } else {
        memset(p, 0, n);
    }
    return p;
}

void EfctFree(void * obj) {
    utilHeapFree(obj);
}

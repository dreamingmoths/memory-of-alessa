#include "sh2_common.h"
#include "Chacter_Draw/vifot/sh_kt_pkbuf.h"

#line 48
void ktPkBufInit(ktPkBuf* p, void* buf0, void* buf1, int size) {
    p->page = 0;
    p->current = buf0;
    p->buffers[0] = buf0;
    p->buffers[1] = buf1;
    p->buffer_size = size;
}

#line 61
void* ktPkBufNext(ktPkBuf* p) {
    p->page ^= 1;
    p->current = p->buffers[p->page];
    return p->current;
}

#line 84
void* ktPkBufCurrent(ktPkBuf* p) {
    return p->current;
}

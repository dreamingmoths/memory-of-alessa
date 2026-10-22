#ifndef SH_KT_PKBUF_H
#define SH_KT_PKBUF_H

typedef struct ktPkBuf {
    // Members
    int page; // offset 0x0, size 0x4
    void* current; // offset 0x4, size 0x4
    void* buffers[2]; // offset 0x8, size 0x8
    int buffer_size; // offset 0x10, size 0x4
} ktPkBuf;

void ktPkBufInit(ktPkBuf* p, void* buf0, void* buf1, int size);

void* ktPkBufNext(ktPkBuf* p);

void* ktPkBufCurrent(ktPkBuf* p);

#endif // SH_KT_PKBUF_H

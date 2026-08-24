#ifndef MOVIE_H
#define MOVIE_H

#include "shared/movie/movie.h"
#include "sce/libgraph.h"

#define min(x, y) (((x) > (y)) ? (y) : (x))
#define max(x, y) (((x) > (y))? (x): (y))

#define STACK_SIZE    (16*1024)
#define DEF_STACK_SIZE    2048
#define IOP_BUFF_SIZE (12288*2) // 512 * 48

typedef struct _PssCommonWork {
    // total size: 0x13B00
    u_char* mpegWorkp; // offset 0x0, size 0x4
    ReadBuf* readBufp; // offset 0x4, size 0x4
    u_long128* viBufDatap; // offset 0x8, size 0x4
    TimeStamp timeStamp[VIBUF_TS_SIZE] __attribute__((aligned(64))); // offset 0x40, size 0x3000
    VoData* voBufDatap; // offset 0x3040, size 0x4
    u_char audioBuff[IOP_BUFF_SIZE * 2] __attribute__((aligned(64))); // offset 0x3080, size 0xC000
    u_int* tagInterDatap; // offset 0xF080, size 0x4
    int videoDecTh; // offset 0xF084, size 0x4
    int defaultTh; // offset 0xF088, size 0x4
    s_char defStack[DEF_STACK_SIZE] __attribute__((aligned(64))); // offset 0xF0C0, size 0x800
    s_char videoDecStack[STACK_SIZE] __attribute__((aligned(64))); // offset 0xF8C0, size 0x4000
    sceGsDBuff db; // offset 0x138C0, size 0x230
} PssCommonWork;
int x = sizeof(PssCommonWork);

#endif // MOVIE_H

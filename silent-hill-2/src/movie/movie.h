#ifndef MOVIE_H
#define MOVIE_H

#include "shared/movie/movie.h"
#include "sce/libgraph.h"
#include "data/fs_structs.h"

#define min(x, y) (((x) > (y)) ? (y) : (x))
#define max(x, y) (((x) > (y))? (x): (y))

#define STACK_SIZE      (16*1024)
#define DEF_STACK_SIZE  2048
#define DEF_PRIORITY    0x24
#define IOP_BUFF_SIZE   (12288*2) // 512 * 48

extern struct /* @anon25 */ {
    // total size: 0x34
    int status; // offset 0x0, size 0x4
    int ctrl; // offset 0x4, size 0x4
    fsFileIndex * file; // offset 0x8, size 0x4
    int readrest; // offset 0xC, size 0x4
    int writerest; // offset 0x10, size 0x4
    int isPaused; // offset 0x14, size 0x4
    int isStarted; // offset 0x18, size 0x4
    short proceed_zero_count; // offset 0x1C, size 0x2
    int cnt; // offset 0x20, size 0x4
    int stFrame; // offset 0x24, size 0x4
    int movieabort; // offset 0x28, size 0x4
    int framecnt; // offset 0x2C, size 0x4
    int maskon; // offset 0x30, size 0x4
} pssExecCtrl; // size: 0x34, address: 0x1217B10

#endif // MOVIE_H

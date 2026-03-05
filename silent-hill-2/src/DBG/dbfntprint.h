#ifndef DB_FNT_PRINT_H
#define DB_FNT_PRINT_H

#include "common.h"

// E:\work\sh2(CVS全取得)\src\DBG\dbfntprint.c
static void _dbfntprint(char* buf);

static signed int printline(char * cp /* r2 */, char * top /* r2 */);

typedef struct DebugPrintInfo {
    // total size: 0x28
    signed int xofs; // offset 0x0, size 0x4
    signed int yofs; // offset 0x4, size 0x4
    signed int x; // offset 0x8, size 0x4
    signed int y; // offset 0xC, size 0x4
    signed int w; // offset 0x10, size 0x4
    signed int h; // offset 0x14, size 0x4
    signed int tab; // offset 0x18, size 0x4
    signed int xofsR; // offset 0x1C, size 0x4
    signed int yofsR; // offset 0x20, size 0x4
    signed int yR; // offset 0x24, size 0x4
} DebugPrintInfo;

extern DebugPrintInfo d;

static void _dbfntprint(char * buf /* r2 */);

#endif

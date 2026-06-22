#ifndef DB_FNT_PRINT_H
#define DB_FNT_PRINT_H

#include "common.h"

// E:\work\sh2(CVS全取得)\src\DBG\dbfntprint.c
static void _dbfntprint(char* buf);

static int printline(char* cp /* r2 */, char* top /* r2 */);

typedef struct DebugPrintInfo {
    // total size: 0x28
    int xofs;  // offset 0x0, size 0x4
    int yofs;  // offset 0x4, size 0x4
    int x;     // offset 0x8, size 0x4
    int y;     // offset 0xC, size 0x4
    int w;     // offset 0x10, size 0x4
    int h;     // offset 0x14, size 0x4
    int tab;   // offset 0x18, size 0x4
    int xofsR; // offset 0x1C, size 0x4
    int yofsR; // offset 0x20, size 0x4
    int yR;    // offset 0x24, size 0x4
} DebugPrintInfo;

#ifdef DEBUG
#define shDBG_print_string(...) _shDBG_print_string(...)
#else
#define shDBG_print_string(...)
#endif
extern void _shDBG_print_string(char* st /* r2 */, int ix /* r2 */, int iy /* r2 */);

extern DebugPrintInfo d_0x0033BEC0;

void dbfntlocate(int x, int y);

void dbfntlocateR(int x, int y);

static int printline(char* cp, char* top);

static void _dbfntprint(char* buf /* r2 */);

#endif

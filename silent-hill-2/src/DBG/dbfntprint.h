#ifndef DB_FNT_PRINT_H
#define DB_FNT_PRINT_H

#include "sh2_common.h"
#include "mw/mw_stdarg.h"
#include "DBG/shDBG_fontHandle.h"

#ifdef DEBUG
#define shDBG_print_string(...) _shDBG_print_string(...)
#else
#define shDBG_print_string(...)
#endif

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

void dbfntlocate(int x /* r2 */, int y /* r2 */);

void dbfntlocateR(int x /* r2 */, int y /* r2 */);

void dbfntprint(s_char* buf /* r16 */);

void dbfntprintR(s_char* buf /* r16 */);

int dbfntprintf(s_char* fmt /* r29+0x228 */, ...);

int dbfntprintfR(s_char* fmt /* r29+0x228 */, ...);

#endif

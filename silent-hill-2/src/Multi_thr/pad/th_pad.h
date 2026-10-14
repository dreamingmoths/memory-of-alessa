#ifndef TH_PAD_H
#define TH_PAD_H

#include "common.h"
#include "debug.h"
#include "shPad/lib_sh_pad.h"
//@todo: This struct might belong somewhere else.
// total size: 0x20
typedef struct thPadStruct /* @anon0 */ {
    // Members
    u_int key; // offset 0x0, size 0x4
    int pow0;  // offset 0x4, size 0x4
    int pow1;  // offset 0x8, size 0x4
    int apr;   // offset 0xC, size 0x4
    int act;   // offset 0x10, size 0x4
    int lck;   // offset 0x14, size 0x4
    int alg;   // offset 0x18, size 0x4
    int step;  // offset 0x1C, size 0x4
} thPadStruct;

int ThreadPadStart(void* stack /* r20 */, int stackSize /* r19 */, int prio /* r18 */, int option /* r17 */, int wait_sid /* r2 */);

#endif // TH_PAD_H

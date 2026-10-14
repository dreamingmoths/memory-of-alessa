#ifndef DMA1SERV_H
#define DMA1SERV_H

#include "Multi_thr/dma/dma1serv.h"
#include "Multi_thr/util/cmd_serv.h"

#define DMA1_PUT(_index, ...) (((int (*)(int (*)(void), ...))(&d1sPutCmd##_index))(__VA_ARGS__))

int d1sInit(int th_prio /* r11 */, void* stack /* r10 */, int stackSize /* r9 */, void* queue /* r16 */, int queueSize /* r2 */);

int d1sSync(int mode /* r3 */, int cid /* r2 */);

int d1sGetCurCmdId(void);

int d1sCmpCID(int cid0 /* r2 */, int cid1 /* r2 */);

int d1sPutCmd0(int (*f0)(void) /* r2 */);

int d1sPutCmd1(int (*f1)(void) /* r3 */, u_long128 a1 /* r2 */);

// int d1sPutCmd2(int (*f2)(void), u_long128 a1, u_long128 a2);
//@note: mentioned once in dwarf and never again. dead code?

#endif // DMA1SERV_H

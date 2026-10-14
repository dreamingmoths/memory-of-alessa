#ifndef DMA2SERV_H
#define DMA2SERV_H

#include "Multi_thr/util/cmd_serv.h"

#define DMA2_PUT(_index, ...) (((int (*)(int (*)(void), ...))(&d2sPutCmd##_index))(__VA_ARGS__))

int d2sInit(int th_prio /* r11 */, void* stack /* r10 */, int stackSize /* r9 */, void* queue /* r16 */, int queueSize /* r2 */);

int d2sSync(int mode /* r3 */, int cid /* r2 */);

int d2sGetCurCmdId(void);

int d2sCmpCID(int cid0 /* r2 */, int cid1 /* r2 */);

int d2sPutCmd0(int (*f0)() /* r2 */);

int d2sPutCmd1(int (*f1)() /* r3 */, u_long128 a1 /* r2 */);

// int d2sPutCmd2(int (*f2)(), u_long128 a1, u_long128, a2);
//@note: ^ mentioned once in dwarf and never again. dead code?
int d2sPutCmd3(int (*f3)() /* r10 */, u_long128 a1 /* r9 */, u_long128 a2 /* r3 */, u_long128 a3 /* r2 */);

#endif // DMA2SERV_H

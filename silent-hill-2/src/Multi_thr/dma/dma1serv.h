#ifndef DMA1SERV_H
#define DMA1SERV_H

#include "common.h"

int d1sInit(int th_prio /* r11 */, void* stack /* r10 */, int stackSize /* r9 */, void* queue /* r16 */, int queueSize /* r2 */);
int d1sSync(int mode /* r3 */, int cid /* r2 */);
int d1sGetCurCmdId(void);
int d1sCmpCID(int cid0 /* r2 */, int cid1 /* r2 */);
int d1sPutCmd0(int (* f0)(void) /* r2 */);
int d1sPutCmd1(int (* f1)(void) /* r3 */, u_long a1 /* r2 */);

#endif // DMA1SERV_H

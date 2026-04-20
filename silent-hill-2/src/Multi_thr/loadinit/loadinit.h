#ifndef LOADINIT_H
#define LOADINIT_H

#include "common.h"
#include "Multi_thr/util/cmd_serv.h"

int lisInit(int th_prio /* r11 */, void* stack /* r10 */, int stackSize /* r9 */, void* queue /* r16 */, int queueSize /* r2 */);
int lisSync(int mode /* r3 */, int cid /* r2 */);
int lisGetStat(CmdServStat* stat /* r2 */);
int lisPutCmd0(int (* f0)(void) /* r2 */);

#endif // LOADINIT_H

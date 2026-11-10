#ifndef DBSW_SYS_H
#define DBSW_SYS_H

#include "sh2_common.h"
#include "SH2_common/pad.h"
#include "DBG/dbswitch.h"
#include "Multi_thr/loadinit/loadinit.h"
#include "Multi_thr/pad/keydata.h"
#include "shPad/lib_sh_pad.h"
//@note: for RTC struct. Probably not a very appropriate include
#include "Multi_thr/filesys/sh_cdvd.h"

s_char * dbSwitchSysHelp(int Y /* r2 */);

void dbSwitchSysPrint(void);

int dbSwitchSysPrintHelp(void);

int dbSwitchSysPadPort(void);

int dbSwitchSysPrintAllPages(void);

int dbSwitchSysPrintNotOnlyPort1(void);

void dbSwitchSysInit(void);

#endif // DBSW_SYS_H

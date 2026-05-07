#ifndef FILESERV_H
#define FILESERV_H

#include "common.h"
#include "FilesList/fileslist_bg.h" // correct?
#include "Multi_thr/util/cmd_serv.h"

int fsInit(int th_prio /* r11 */, void* stack /* r10 */, int stackSize /* r9 */, void* queue /* r16 */, int queueSize /* r2 */);
int fsSync(int mode /* r17 */, int fid /* r16 */);
int fsGetStat(CmdServStat* stat /* r2 */);
int fsGetTrayStat(void);

int fcDiskSelectC(void);
int fcDiskSelectCH(void);
int fcDiskSelectHC(void);

int fcDiskSelect(int mode /* r2 */);

int fcRead(union fsFile* fp /* r17 */, void* buf /* r16 */);
int fcFixFile(union fsFile* fp /* r2 */);

#endif // FILESERV_H

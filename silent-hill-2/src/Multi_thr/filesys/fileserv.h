#ifndef FILESERV_H
#define FILESERV_H

#include "sh2_common.h"
#include "data/fs_structs.h"
#include "Multi_thr/util/cmd_serv.h"

int fsInit(int th_prio, void* stack, int stackSize, void* queue, int queueSize);
int fsSync(int mode, int fid);
int fsGetStat(CmdServStat* stat);
int fsGetTrayStat(void);
int fcSifInit(void);
int fcCdInitW(int cb_prio, void* stack, int stackSize);
int fcIopLoadMod(char* module);
int fcDiskSelectC(void);
int fcDiskSelectCH(void);
int fcDiskSelectHC(void);
int fcHdInit(int mode);
int fcDiskSelect(int mode);
int fcExecDevSelect(int mode);
int fcSetParamForCheckDisk(int media_permission, fsFile** fplist, void** buflist, int (*check_func)(fsFile**, void**));
int fcCdCheckDisk(int force_check);
int fcRead(fsFile* fp, void* buf);
int fcReadPart(fsFile* fp, void* buf, int offset, int size);
int fcFixFile(fsFile* fp);

#endif // FILESERV_H

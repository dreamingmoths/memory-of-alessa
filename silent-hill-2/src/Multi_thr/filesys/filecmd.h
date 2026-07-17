#ifndef FILECMD_H
#define FILECMD_H

#include "sh2_common.h"
#include "data/fs_structs.h"

fsFile* fsCmdCheckFixFile(fsFile* fp);
int fsCmdCheckExistFile(fsFile* fp);
int fsCmdSetRealFile(fsFile* realfp, fsFile* fp);
int fsCmdDiskSelectC(void);
int fsCmdDiskSelectCH(void);
int fsCmdDiskSelectHC(void);
int fsCmdExecDevSelect(int mode);
int fsCmdFixFile(fsFile* fp);
int fsCmdHdInit(int enable);
int fsCmdRead(fsFile* fp, void* buf);
int fsCmdReadPart(fsFile* fp, void* buf, int offset, int size);
int fsCmdSetParamForCheckDisk(int media_permission, fsFile** fplist, void** buflist, int (* check_func)(fsFile* *, void* *));
int fsCmdCdCheckDisk(int force_check);
int fsCmdCdCheckDisk2(int force_check, int media_permission, fsFile** fplist, void** buflist, int (* check_func)(fsFile* *, void* *));
int fsCmdGetTrayStat(void);

#endif // FILECMD_H

#ifndef FILECMD_H
#define FILECMD_H

#include "sh2_common.h"
#include "data/fs_structs.h"
#include "Multi_thr/filesys/sh_cdvd.h"

// total size: 0x38
typedef struct fsSubCmdStatT {
    // Members
    int (**fix_func_list)(fsFile *);      // offset 0x0, size 0x4
    int media_permission;                 // offset 0x4, size 0x4
    int media_reset;                      // offset 0x8, size 0x4
    int media_checking;                   // offset 0xC, size 0x4
    int media_type;                       // offset 0x10, size 0x4
    int media_illegal;                    // offset 0x14, size 0x4
    int media_empty;                      // offset 0x18, size 0x4
    int disk_check;                       // offset 0x1C, size 0x4
    int disk_number;                      // offset 0x20, size 0x4
    int disk_count;                       // offset 0x24, size 0x4
    int disk_prohibition;                 // offset 0x28, size 0x4
    int disk_emulation;                   // offset 0x2C, size 0x4
    int now_reading;                      // offset 0x30, size 0x4
    int exec_dev;                         // offset 0x34, size 0x4
} fsSubCmdStatT;

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
int fsCmdSetParamForCheckDisk(int media_permission, fsFile** fplist, void** buflist, int (*check_func)(fsFile**, void**));
int fsCmdCdCheckDisk(int force_check);
int fsCmdCdCheckDisk2(int force_check, int media_permission, fsFile** fplist, void** buflist, int (*check_func)(fsFile**, void**));
int fsCmdGetTrayStat(void);

#endif // FILECMD_H

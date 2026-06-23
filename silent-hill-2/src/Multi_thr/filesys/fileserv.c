#include "Multi_thr/filesys/fileserv.h"
#include "Multi_thr/intc/syncv.h"
#include "Multi_thr/filesys/filecmd.h"

static void checkReadAlign(void* buffer /* r2 */);

extern /* static */ u_long128* fsCmdWork;

int fsInit(int th_prio /* r11 */, void* stack /* r10 */, int stackSize /* r9 */, void* queue /* r16 */, int queueSize /* r2 */) {
    int ret = 0; // r2
    if (!fsCmdWork) {
        ret = CmdServInit(queue, queueSize, stack, stackSize, th_prio);
        if (ret) {
            fsCmdWork = queue;
        }
    }
    return ret;
}

int fsSync(int mode /* r17 */, int fid /* r16 */) {
    int ret; // r2 
    
    if ((mode == 0) && (shSyncVEnd(1) < 0xA)) {
        shSyncVEnd(0);
    }
    ret = CmdQueueSync(fsCmdWork, mode, fid);
    return ret;
}

int fsGetStat(CmdServStat* stat /* r2 */) {
    return CmdServGetStat(fsCmdWork, stat);
}

int fsGetTrayStat(void) {
    return fsCmdGetTrayStat();
}

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/fileserv", fcSifInit);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/fileserv", fcCdInitW);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/fileserv", fcIopLoadMod);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/fileserv", fcDiskSelectC);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/fileserv", fcDiskSelectCH);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/fileserv", fcDiskSelectHC);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/fileserv", fcHdInit);

int fcDiskSelect(int mode /* r2 */) {
    switch (mode) {
        default:
            return fcDiskSelectC();
        case 1:
            return fcDiskSelectCH();
        case 2:
            return fcDiskSelectHC();
    }
}

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/fileserv", fcExecDevSelect);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/fileserv", fcSetParamForCheckDisk);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/fileserv", fcCdCheckDisk);

static void checkReadAlign(void* buffer /* r2 */) {
    if ((int)buffer & 0x3F) {
        printf("fileserv.c:493> buffer alignment error! 0x%08x\n", buffer);
        while(1);
    }
}

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/fileserv", fcRead);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/fileserv", fcReadPart);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/fileserv", fcFixFile);

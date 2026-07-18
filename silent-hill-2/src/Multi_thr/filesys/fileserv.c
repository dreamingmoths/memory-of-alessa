#include "Multi_thr/filesys/fileserv.h"
#include "Multi_thr/filesys/filecmd.h"
#include "Multi_thr/filesys/sh_cdvd.h"
#include "Multi_thr/filesys/iopload.h"
#include "Multi_thr/intc/syncv.h"

#define CMD_QUEUE_PUT(_index, ...) ((((int (*)(u_long128*, ...))(&CmdQueuePut##_index))(fsCmdWork, __VA_ARGS__)))

static void checkReadAlign(void* buffer /* r2 */);

static u_long128* fsCmdWork = NULL;

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
    
    if ((mode == 0) && (shSyncVEnd(1) < 10)) {
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

int fcSifInit(void) {
    return CMD_QUEUE_PUT(0, shSifInit);
}

int fcCdInitW(int cb_prio, void* stack, int stackSize) {    
    return CMD_QUEUE_PUT(3, shCdInitW, cb_prio, stack, stackSize);
}

int fcIopLoadMod(char* module) {    
    return CMD_QUEUE_PUT(1, shIopLoadMod, module);
}

int fcDiskSelectC(void) {
    return CMD_QUEUE_PUT(0, fsCmdDiskSelectC);
}

int fcDiskSelectCH(void) {
    return CMD_QUEUE_PUT(0, fsCmdDiskSelectCH);
}

int fcDiskSelectHC(void) {
    return CMD_QUEUE_PUT(0, fsCmdDiskSelectHC);
}

int fcHdInit(int mode) {
    return CMD_QUEUE_PUT(1, fsCmdHdInit, mode);
}

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

int fcExecDevSelect(int mode) {
    return CMD_QUEUE_PUT(1, fsCmdExecDevSelect, mode);
}

int fcSetParamForCheckDisk(int media_permission, fsFile** fplist, void** buflist, int (*check_func)(fsFile**, void**)) {
    return CMD_QUEUE_PUT(4, fsCmdSetParamForCheckDisk, media_permission, fplist, buflist, check_func);
}

int fcCdCheckDisk(int force_check) {
    return CMD_QUEUE_PUT(1, fsCmdCdCheckDisk, force_check);
}

static void checkReadAlign(void* buffer /* r2 */) {
    if ((int)buffer & 0x3F) {
        DEBUG_LOG_ON_LINE(493, "buffer alignment error! 0x%08x\n", buffer);
        while(1);
    }
}

int fcRead(fsFile* fp, void* buf) {
    checkReadAlign(buf);
    return CMD_QUEUE_PUT(2, fsCmdRead, fp, buf);
}

int fcReadPart(fsFile* fp, void* buf, int offset, int size) {
    return CMD_QUEUE_PUT(4, fsCmdReadPart, fp, buf, offset, size);
}

int fcFixFile(fsFile* fp) {
    return CMD_QUEUE_PUT(1, fsCmdFixFile, fp);
}

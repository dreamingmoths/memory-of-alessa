#include "Multi_thr/filesys/fileserv.h"
#include "Multi_thr/filesys/filecmd.h"
#include "Multi_thr/filesys/sh_cdvd.h"
#include "Multi_thr/filesys/iopload.h"
#include "Multi_thr/intc/syncv.h"

typedef int (fileserv_func_t)(void);
typedef int (fileserv_func2_t)(fileserv_func_t*);
typedef int (fileserv_func3_t)(u_long128*, fileserv_func_t*);
typedef int (fileserv_func4_t)(int, void*, int);
//typedef int (fileserv_func5_t)(u_long128*, fileserv_func4_t*, u_long128, u_long128, u_long128);
typedef int (fileserv_func5_t)(u_long128*, fileserv_func4_t*, ...);
typedef int (fileserv_func6_t)(char*);
typedef int (fileserv_func7_t)(u_long128*, fileserv_func6_t*, char*);
typedef int (fileserv_func8_t)(int);
typedef int (fileserv_func9_t)(u_long128*, fileserv_func8_t*, ...);
typedef int (fileserv_func10_t)(fsFile**, void**);
typedef int (fileserv_func11_t)(int, fsFile**, void**, fileserv_func10_t);
typedef int (fileserv_func12_t)(u_long128*, fileserv_func11_t*, ...);
typedef int (fileserv_func13_t)(fsFile*, void*);
typedef int (fileserv_func14_t)(u_long128*, fileserv_func13_t*, ...);
typedef int (fileserv_func15_t)(fsFile*, void*, int, int);
typedef int (fileserv_func16_t)(u_long128*, fileserv_func15_t*, ...);
typedef int (fileserv_func17_t)(fsFile*);
typedef int (fileserv_func18_t)(u_long128*, fileserv_func17_t*, ...);

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
    return (((fileserv_func3_t*)&CmdQueuePut0))(fsCmdWork, shSifInit);
}

int fcCdInitW(int cb_prio, void* stack, int stackSize) {    
    return (((fileserv_func5_t*)&CmdQueuePut3)(fsCmdWork, shCdInitW, cb_prio, stack, stackSize));
}

int fcIopLoadMod(char* module) {    
    return ((fileserv_func7_t*)&CmdQueuePut1)(fsCmdWork, shIopLoadMod, module);
}

int fcDiskSelectC(void) {
    return ((fileserv_func3_t*)&CmdQueuePut0)(fsCmdWork, fsCmdDiskSelectC);
}

int fcDiskSelectCH(void) {
    return ((fileserv_func3_t*)&CmdQueuePut0)(fsCmdWork, fsCmdDiskSelectCH);
}

int fcDiskSelectHC(void) {
    return ((fileserv_func3_t*)&CmdQueuePut0)(fsCmdWork, fsCmdDiskSelectHC);
}

int fcHdInit(int mode) {
    return ((fileserv_func9_t*)&CmdQueuePut1)(fsCmdWork, fsCmdHdInit, mode);
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
    return ((fileserv_func9_t*)&CmdQueuePut1)(fsCmdWork, fsCmdExecDevSelect, mode);
}

int fcSetParamForCheckDisk(int media_permission, fsFile** fplist, void** buflist, int (*check_func)(fsFile**, void**)) {
    return ((fileserv_func12_t*)&CmdQueuePut4)(fsCmdWork, fsCmdSetParamForCheckDisk, media_permission, fplist, buflist, check_func);
}

int fcCdCheckDisk(int force_check) {
    return ((fileserv_func9_t*)&CmdQueuePut1)(fsCmdWork, fsCmdCdCheckDisk, force_check);
}

static void checkReadAlign(void* buffer /* r2 */) {
    if ((int)buffer & 0x3F) {
        printf("fileserv.c:493> buffer alignment error! 0x%08x\n", buffer);
        while(1);
    }
}

int fcRead(fsFile* fp, void* buf) {
    checkReadAlign(buf);
    return ((fileserv_func14_t*)&CmdQueuePut2)(fsCmdWork, fsCmdRead, fp, buf);
}

int fcReadPart(fsFile* fp, void* buf, int offset, int size) {
    return ((fileserv_func16_t*)&CmdQueuePut4)(fsCmdWork, fsCmdReadPart, fp, buf, offset, size);
}

int fcFixFile(fsFile* fp) {
    return ((fileserv_func18_t*)&CmdQueuePut1)(fsCmdWork, fsCmdFixFile, fp);
}

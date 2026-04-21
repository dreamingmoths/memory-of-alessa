#include "sh_cdvd.h"

static int WaitExec(void);
static int SignalExec(void);
static int WaitCmd(void);
static int SignalCmd(void);
static int ___shCdMmode(int mmode /* r16 */);
static int ___shCdInit(int initmode /* r16 */);

// ???
int CreateSema2(int, int, int);

// eekernel.h
void WaitSema(int);

// eekernel.h
int SignalSema(int);

// include/libcdvd.h
int sceCdInit(int init_mode);

// ???
int iSignalSema(int);

// ???
int CreateSema2(int, int, int);

// ???
void sceCdCallback(void f(void));

// ???
int sceCdInitEeCB(int, void*, int);

// sifdev.h ?
int sceFsReset(void);         

// sifrpc.h ?
void sceSifInitRpc(u_int mode);

// ???
void sceSifLoadFileReset(void);

// sifdev.h
int sceSifSyncIop(void);

static int WaitExec(void)  {
    int ret; // r2 how is this used?
    if (shCdWork.exec_sid != -1) {
        WaitSema(shCdWork.exec_sid);
    } else {
        shCdWork.exec_sid = CreateSema2(0, 1, 0);
    }
    exec_cnt++;
}

static int SignalExec(void) {
    exec_cnt--;
    return SignalSema(shCdWork.exec_sid);
}


static int WaitCmd(void) {
    int ret; // r2 how is this used?
    if (shCdWork.cmd_sid != -1) {
        WaitSema(shCdWork.cmd_sid);
    } else {
        shCdWork.cmd_sid = CreateSema2(0, 1, 0);
    }
    cmd_cnt++;
}

static int SignalCmd(void) {
    cmd_cnt--;
    return SignalSema(shCdWork.cmd_sid);
}

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", ___shCdMmode);

static int ___shCdInit(int initmode /* r16 */) {
    int ret; // r16
    WaitCmd();
    shCdWork.rtc_ok = 1;
    ret = sceCdInit(initmode);
    SignalCmd();
    return ret;
}

int shCdInit(int initmode /* r16 */, int mmode /* r17 */) {
    signed int ret; // r16
    WaitExec();
    ret = ___shCdInit(initmode);
    if (ret != 0) {
        ret = mmode;
        ___shCdMmode(mmode);
    }
    SignalExec();
    return ret;
}

int shCdMmode(int mmode /* r16 */) {
    int ret; // Not present in the dwarf
    WaitExec();
    ret = ___shCdMmode(mmode);
    SignalExec();
    return ret;
}

int shCdInitR(int initmode /* r17 */, int mmode /* r16 */) {
    int ret; // r2 how is this used????
    do {

    } while (shCdInit(initmode, mmode) == 0);
}

void shCdCallbackFunc(void) {
    iSignalSema(shCdWork.wait_sid);
}

int shCdInitW(int cb_prio /* r18 */, void* stack /* r17 */, int stack_size /* r16 */) {
    int ret;
    if (shCdWork.wait_sid == -1) {
        shCdWork.wait_sid = CreateSema2(0, 1, 0);
    }
    ret = sceCdInitEeCB(cb_prio, stack, stack_size);
    sceCdCallback(&shCdCallbackFunc);
    return ret;
}

int shSifInit(void) {
    int ret; // r16
    WaitExec();
    WaitCmd();
    sceSifInitRpc(0);
    sceSifLoadFileReset();
    ret = sceFsReset();
    SignalCmd();
    SignalExec();
    return ret;
}

int shSdSifInit(void) {
    return 1;
}

int shSifSyncIop(void) {
    int ret;
    WaitExec();
    WaitCmd();
    ret = sceSifSyncIop();
    SignalCmd();
    SignalExec();
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shSifLoadModule);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shSifLoadModuleR);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shSifRebootIop);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shSifRebootIopR);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", checkReadAlign);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shCdRead);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shCdSeek);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shCdReadW);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shCdSeekW);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shCdReadClockRecover);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shCdReadClock);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", name_skip_cdrom0);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shCdSearchFile);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", ___shCdSearchFile);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shCdDiskReady);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", ___shCdDiskReady);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shCdGetDiskType);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shCdTrayReq);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shCdGetError);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shCdStatus);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shCdSync);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shCdSdStart);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shCdSdEnd);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", WaitHd);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", SignalHd);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shHdInit);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shHdOpen);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shHdRead);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shHdClose);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", shHdLseek);

INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/sh_cdvd", ___shHdGetFileSize);

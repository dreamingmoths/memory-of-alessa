#include "Multi_thr/filesys/sh_cdvd.h"
#include "eekernel.h"
#include "eeregs.h"
#include "sifdev.h"
#include "sifrpc.h"
#include "debug.h"

static int WaitExec(void);
static int SignalExec(void);
static int WaitCmd(void);
static int SignalCmd(void);
static int ___shCdMmode(int mmode /* r16 */);
static int ___shCdInit(int initmode /* r16 */);
static void checkReadAlign(void* buffer /* r2 */);
static char* name_skip_cdrom0(char* name);
static void shCdReadClockRecover(int, u_short, void*);
static int ___shCdDiskReady(int mode /* r16 */);
static int WaitHd(void);
static int SignalHd(void);

static int WaitExec(void)  {
    int ret; // @todo how is this used?
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
    int ret;
    if (shCdWork.cmd_sid != -1) {
        ret = WaitSema(shCdWork.cmd_sid);
    } else {
        ret = CreateSema2(0, 1, 0);
        shCdWork.cmd_sid = ret;
    }
    cmd_cnt++;
    return ret;
}

static int SignalCmd(void) {
    cmd_cnt--;
    return SignalSema(shCdWork.cmd_sid);
}

static int ___shCdMmode(int mmode) {
    WaitCmd();
    while (!mmode) {
        sceCdDiskReady(0);
        switch (sceCdGetDiskType()) {
            case SCECdPS2DVD:
            case SCECdDVDV:
                mmode = 2;
                break;
            case SCECdPS2CD:
            case SCECdPS2CDDA:
            case SCECdPSCD:
            case SCECdPSCDDA:
            case SCECdCDDA:
                mmode = 1;
                break;
            case SCECdDETCT:
            case SCECdNODISC:
                break;
            case SCECdIllegalMedia:
            default:
                printf("sh_cdvd.c:149> assert:(%s)\n", "!\"illegal media.\"");
                while (1);
        }
    }
    if (!sceCdMmode(mmode)) {
        mmode = 0;
    }
    SignalCmd();
    return mmode;
}

static int ___shCdInit(int initmode /* r16 */) {
    int ret; // r16
    WaitCmd();
    shCdWork.rtc_ok = 1;
    ret = sceCdInit(initmode);
    SignalCmd();
    return ret;
}

int shCdInit(int initmode /* r16 */, int mmode /* r17 */) {
    int ret; // r16
    WaitExec();
    ret = ___shCdInit(initmode);
    if (ret) {
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
    int ret;
    do {
        ret = shCdInit(initmode, mmode);
    } while (!ret);
    return ret;
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

int shSifLoadModule(char* module /* r18 */, int args /* r17 */, char* argp /* r16 */) {
    int ret; // r16
    WaitExec();
    WaitCmd();
    ret = sceSifLoadModule(module, args, argp);
    SignalCmd();
    SignalExec();
    return ret;
}

int shSifLoadModuleR(char* module /* r20 */, int args /* r19 */, char* argp /* r18 */) {
    int ret; // r2
    int count = 0x14; // r16    
    int i; // r17
    while ((ret = shSifLoadModule(module, args, argp)) < 0) {
        if (count-- < 0) {
            VERBOSE_ON_LINE(298, 1, "%s: can't load iop");
            count = 0x14;
        }
        for (i = 0x3C; i > 0; i--) {
            shSyncVEnd(0);
        }
    }
    
    return ret;
}

int shSifRebootIop(char* imgfile /* r16 */) {
    int ret; // r16
    WaitExec();
    WaitCmd();
    ret = sceSifRebootIop(imgfile);
    SignalCmd();
    SignalExec();
    return ret;
}

int shSifRebootIopR(char* imgfile /* r18 */) {    
    int ret; // r16 why is this called ret?
    int i; // r17

    ret = 0x14;
    while (!shSifRebootIop(imgfile)) {
        if (ret-- < 0) {
            VERBOSE_ON_LINE(329, 1, "%s: can't reboot");
            ret = 0x14;
        }
        for (i = 0x3C; i > 0; i--) {
            shSyncVEnd(0);
        }
    }
    ret = 5;
    while (!shSifSyncIop()) {
        if (ret-- < 0) {
            VERBOSE_ON_LINE(340, 1, "%s: can't sync iop");
            ret = 5;
        }
        for (i = 0x3C; i > 0; i--) {
            shSyncVEnd(0);
        }
    }
    return 1;
}


static void checkReadAlign(void* buffer /* r2 */) {
    if ((int)buffer & 0x3F) {
        printf("sh_cdvd.c:384> buffer alignment error! 0x%08x\n", buffer);
        while(1);
    }
}

int shCdRead(int lsn /* r19 */, int sectors /* r18 */, void* buf /* r17 */, sceCdRMode* mode /* r16 */) {
    int ret; // r16
    checkReadAlign(buf);
    WaitCmd();
    ret = sceCdRead(lsn, sectors, buf, mode);
    SignalCmd();
    return ret;
}

int shCdSeek(int lsn /* r16 */) {
    int ret; // r16
    WaitCmd();
    ret = sceCdSeek(lsn);
    SignalCmd();
    return ret;
}

int shCdReadW(int lsn /* r21 */, int sectors /* r20 */, void* buf /* r19 */, sceCdRMode* mode /* r18 */) {
    int ret; // r16
    u_short hcnt0; // r17
    u_short hcnt1; // r2
    hcnt0 = *T3_COUNT;
    VERBOSE_ON_LINE(442, 2, "now CD reading...\n");
    WaitExec();    
    SyncDCache(buf, (u_char*)buf + (sectors << 0xB));
    InvalidDCache(buf, (u_char*)buf + (sectors << 0xB));
    do {        
        ret = shCdRead(lsn, sectors, buf, mode);
        if (ret != 0) {
            WaitSema(shCdWork.wait_sid);
            ret = shCdGetError();
            break;
        }
        ret = SCECdErTRMOPN; // 0x31
    } while (___shCdDiskReady(1) == 2);
    InvalidDCache(buf, (u_char*)buf + (sectors << 0xB));
    SyncDCache(buf, (u_char*)buf + (sectors << 0xB));
    SignalExec();
    hcnt1 = *T3_COUNT;
    VERBOSE_ON_LINE(469, 2, "cd read time:%d\n", (u_short) (hcnt1 - hcnt0));
    return ret;   
}

int shCdSeekW(int lsn /* r18 */) {
    int ret; // r16    
    u_short hcnt0; // r17
    u_short hcnt1; // r2
    hcnt0 = *T3_COUNT;
    WaitExec();
    do {
        ret = shCdSeek(lsn);
        if (ret != 0) {
            WaitSema(shCdWork.wait_sid);
            ret = shCdGetError();
            break;
        }
        ret = SCECdErTRMOPN; // 0x31
    } while (___shCdDiskReady(1) == 2);
    SignalExec();
    hcnt1 = *T3_COUNT;
    VERBOSE_ON_LINE(496, 2, "cd seek time:%d\n", (u_short) (hcnt1 - hcnt0));
    return ret;
}

static void shCdReadClockRecover(int, u_short, void *) { 
    shCdWork.rtc_ok = 1;
    ExitHandler();
}

int shCdReadClock(Old_Rtc* rtc /* r17 */) {
    int ret; // r16
    
    WaitCmd();
    if (shCdWork.rtc_ok) {
        shCdWork.rtc_ok = 0;
        ret = sceCdReadClock((sceCdCLOCK*)rtc);
        old_rtc = *rtc;
        
        SetAlarm(0x1275, shCdReadClockRecover, 0);
    } else {
        ret = 0;
        *rtc = old_rtc;
    }

    
    SignalCmd();
    
    return ret;
}

static char* name_skip_cdrom0(char* name) {
    char* ret; // r2
    
    if (*name == '\\') do { ret = name; } while (0);
    else {
        do { ret = name; } while (0);
        while (*name != '\0' && *name != ':') name++;
        if (*name == ':') name++;
    }
    ret = name;
    return ret;
}

int shCdSearchFile(sceCdlFILE* file /* r2 */, char* fullpath /* r2 */) {   
    u_short hcnt0; // r2
    u_short hcnt1; // r2
    int ret; // r17       
    hcnt0 = *T3_COUNT;




    
    ret = ___shCdSearchFile(file, fullpath);
    hcnt1 = *T3_COUNT;
    VERBOSE_ON_LINE(639, 2, "cd search-file time:%d\n", (u_short) (hcnt1 - hcnt0));
    return ret;
}

int ___shCdSearchFile(sceCdlFILE* fp /* r17 */, char* name /* r16 */) {
    int ret; // r16    
    WaitExec();
    WaitCmd();
    
    name = name_skip_cdrom0(name);
    if (*name == '\\') {
        ret = sceCdSearchFile(fp, name);
    } else {
        ret = 0;
    }
    SignalCmd();
    SignalExec();
    return ret;
}

int shCdDiskReady(int mode /* r16 */) {
    int ret; // r16

    WaitExec();
    ret = ___shCdDiskReady(mode);
    SignalExec();
    return ret;
}

static int ___shCdDiskReady(int mode /* r16 */) {
    int ret; // r16
    char* str = NULL; // r2 how is this used??

    WaitCmd();
    ret = sceCdDiskReady(mode);
    SignalCmd();
    return ret;
}

int shCdGetDiskType(void) {
    int ret; // r16
    char* str = NULL; // r2 how is this used? 

    WaitExec();
    WaitCmd();
    ret = sceCdGetDiskType();
    SignalCmd();
    SignalExec();
    return ret;
}

int shCdTrayReq(int mode /* r17 */, u_int* traycnt /* r16 */) {
    int ret; // r16
    WaitExec();
    WaitCmd();
    ret = sceCdTrayReq(mode, traycnt);
    SignalCmd();
    SignalExec();

    
    return ret;
}

int shCdGetError(void) {
    int error; // r16

    WaitCmd();
    error = sceCdGetError();
    SignalCmd();
    return error;
}

int shCdStatus(void) {
    int stat; // r16

    WaitExec();
    WaitCmd();
    stat = sceCdStatus();
    SignalCmd();
    SignalExec();
    return stat;
}

int shCdSync(int mode /* r16 */) {
    int ret; // r16

    WaitCmd();
    ret = sceCdSync(mode);
    SignalCmd();
    return ret;
}

void shCdSdStart(void) {
    WaitExec();
}

void shCdSdEnd(void) {
    SignalExec();
}

static int WaitHd(void) {
    int ret; // r2 how is this used?
    if (shHdWork.hd_sid != -1) {
        WaitSema(shHdWork.hd_sid);
    } else {
        shHdWork.hd_sid = CreateSema2(0, 1, 0);
    }
    exec_cnt++;
}

static int SignalHd(void) {
    exec_cnt--;
    return SignalSema(shHdWork.hd_sid);
}

int shHdInit(void) {
    int ret; // r2
    WaitHd();
    shHdWork.last_fd = -1;
    shHdWork.last_filename = 0;
    shHdWork.last_offset = 1;
    ret = SignalHd(); 
    return ret; // not sure
}

int shHdOpen(char* name /* r17 */, int mode /* r16 */) {
    int ret; // r2

    WaitHd();
    if (name != NULL) {
        ret = sceOpen(name, mode);
    } else {
        ret = -1;
    }
    SignalHd();
    return ret;
}

int shHdRead(int fd /* r18 */, void* buffer /* r17 */, int size /* r16 */) {
    int ret; // r16

    checkReadAlign(buffer);
    WaitHd();
    ret = sceRead(fd, buffer, size);
    SignalHd();
    return ret;
}

int shHdClose(int fd /* r16 */) {
    int ret; // r16

    WaitHd();
    ret = sceClose(fd);
    SignalHd();
    return ret;
}

int shHdLseek(int fd /* r18 */, int offset /* r17 */, int where /* r16 */) {
    int ret; // r16

    WaitHd();
    ret = sceLseek(fd, offset, where);
    SignalHd();
    return ret;
}

int ___shHdGetFileSize(char* name /* r16 */) {
    int ret; // r16    
    int fd; // r17

    WaitExec();
    WaitCmd();
    fd = shHdOpen(name, 1);
    if (fd >= 0) {
        ret = shHdLseek(fd, 0, 2);
        if (ret < 0) {
            ret = 0;
        }
        shHdClose(fd);
    } else {
        ret = -1;
    }
    SignalCmd();
    SignalExec();
    return ret;
}

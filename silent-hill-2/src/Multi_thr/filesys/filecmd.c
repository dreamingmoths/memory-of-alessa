#include "Multi_thr/filesys/filecmd.h"
#include "filecmd.h"

static fsFile* ___fsSubCmdCheckRootFile(fsFile * fp /* r2 */);
static fsFile* ___fsSubCmdCheckCdHdFixFile(fsFile* fp);
static int ___fsSubCmdCheckCdHdExistFile(fsFile* fp /* r2 */);
static fsFile* fsSubCmdSetRealFile0(fsFile* realfp /* r17 */, fsFile* fp /* r16 */);
static fsFile* ___fsSubCmdSetRealFile0(fsFile* realfp /* r17 */, fsFile* fp /* r16 */);
static fsFile* fsSubCmdSetRealFile(fsFile* realfp /* r18 */, fsFile* fp /* r17 */);
static int ___fsSubCmdNullDevFixFile(fsFile * fp /* r2 */);
static int ___fsSubCmdCdCommonFixFile(fsFile* fp /* r16 */);
static int ___fsSubCmdCd1stFixFile(fsFile* fp /* r2 */);
static int ___fsSubCmdCdFixFile(fsFile* fp /* r2 */);
static int ___fsSubCmdHdCommonFixFile(fsFile* fp /* r16 */);
static int ___fsSubCmdHd1stFixFile(fsFile* fp /* r2 */);
static int ___fsSubCmdHdFixFile(fsFile* fp /* r2 */);
static int ___fsSubCmdFixFile(fsFile* fp /* r17 */);
static int fsSubCmdCdCheckTrayOpen(void);
static int fsSubCmdCdGetMedia(void);
static int fsSubCmdCdGetMmode(int media /* r2 */);
static int fsSubCmdCdRead(int lsn /* r18 */, int sectors /* r17 */, void* buf /* r16 */);
static int strcmp__(char * s /* r2 */, char * t /* r2 */);
static int shHdOpenC(char* fullpath /* r17 */, int mode /* r16 */);
static int shHdCloseC(int fd /* r2 */);
static int fsSubCmdHdRead0(char* name /* r30 */, int offset /* r29+0xAC */, int size /* r23 */, void* buf /* r22 */);
static int fsSubCmdHdError();
static int fsSubCmdRealRead(fsFile* fp /* r17 */, void* buf /* r16 */);
static int fsSubCmdRead(fsFile* fp /* r2 */, void* buf /* r16 */);
static int ___fsCmdRead(fsFile* fp /* r17 */, void* buf /* r16 */);


UNMIGRATED(fsFileIndex data_null_dev); // size: 0x8, address: 0x39C600
static int (* ___fsSubCmdFixFuncListC[2])(fsFile *) = {___fsSubCmdCdFixFile}; // size: 0x8, address: 0x33B258
static int (* ___fsSubCmdFixFuncListCH[5])(fsFile *) = {
    ___fsSubCmdCd1stFixFile,
    ___fsSubCmdHd1stFixFile,
    ___fsSubCmdCdFixFile,
    ___fsSubCmdHdFixFile}; // size: 0x14, address: 0x33B260
static int (* ___fsSubCmdFixFuncListHC[5])(fsFile *) = {
    ___fsSubCmdHd1stFixFile,
    ___fsSubCmdCd1stFixFile,
    ___fsSubCmdHdFixFile,
    ___fsSubCmdCdFixFile}; // size: 0x14, address: 0x33B280
static int (* ___fsSubCmdFixFuncListH[2])(fsFile *) = {___fsSubCmdHdFixFile}; // size: 0x8, address: 0x33B298
static int (* fsSubCmdHdRead)() = fsSubCmdHdError; // size: 0x4, address: 0x33B2A8
static fsSubCmdStatT fs_stat = {___fsSubCmdFixFuncListC, 255};

static char hdopen_lastpath[256] = {}; // size: 0x100, address: 0x33B2B0
static int hdopen_lastmode; // size: 0x4, address: 0x11591E0
static int hdopen_lastfd = -1; // size: 0x4, address: 0x33B3B0
static int fsCmdParam_media_permission; // size: 0x4, address: 0x11591E8
static fsFile** fsCmdParam_fplist; // size: 0x4, address: 0x11591F0
static void** fsCmdParam_buflist; // size: 0x4, address: 0x11591F8
static int (* fsCmdParam_check_func)(fsFile**, void**); // size: 0x4, address: 0x1159200


static inline fsFile* ID_fsFile(fsFileIndex* fileidx) {
    return fileidx->index.fp;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", ___fsSubCmdCheckCdHdFile);
static fsFile* ___fsSubCmdCheckCdHdFile(fsFile * fp /* r2 */) {
    if (fp == NULL) return NULL;
    if (fp->cd.type & 0x10) return NULL;
    if (!(fp->hd.type & 0xF)) return NULL;
    return fp;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", ___fsSubCmdCheckRootFile);
static fsFile* ___fsSubCmdCheckRootFile(fsFile * fp /* r2 */) {
    s_char* start; // r2
    s_char* end;   // r2
    int offset;    // r2
    int size;      // r3

    while (true) {
        if (fp == NULL) break;
        if (!(fp->hd.type & 0x10)) break;
        if (!(fp ->hd.type & 0x40)) {
            start = fp->mgc.start;
            end = fp->mgc.end;
            size = end - start;
            // offset = (int)start;

            fp->hd.offset = (int)start;
            fp->hd.size =  size;
            fp->check.type = 0x50;


        }
        fp = fp->mgf.parent;
        // fp = (fsFile *)fp->pack;
        // if (!(fp->hd.type & 0xF)) return NULL;
    }
    return fp;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", ___fsSubCmdCheckCdHdFixFile);
static fsFile* ___fsSubCmdCheckCdHdFixFile(fsFile* fp) {
    if (fp->check.type & 0x40) {

        if (
            (fp->check.type & 5)
            && (fp->check.number)
            && (fs_stat.disk_number != 0)
        ) {

            fp->check.type &= 0x7f;

            if (
                (fp->check.number > 0)
                && (fp->check.number != fs_stat.disk_number)
                || ((fp->check.number < 0)
                && (fs_stat.disk_number < fp->check.number))
            ) {
                fp->check.type &= ~0x40;
                return fp;
            }
        }

        return NULL;
    }
    return fp;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsCmdCheckFixFile);
fsFile* fsCmdCheckFixFile(fsFile* fp /* r16 */) {
    fsFile* ret; // r16




    utilExclLockOtherThread();
    ret = ___fsSubCmdCheckRootFile(fp);
    if (!___fsSubCmdCheckCdHdFile(ret)) {
        ret = NULL;
    } else {
        ret = ___fsSubCmdCheckCdHdFixFile(ret);
    }
    utilExclUnlockOtherThread();




    return ret;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", ___fsSubCmdCheckCdHdExistFile);
static int ___fsSubCmdCheckCdHdExistFile(fsFile* fp /* r2 */) {




    if (___fsSubCmdCheckCdHdFixFile(fp)) {

        return 0;
    }
    if (fp->cd.type & 5 && fp->cd.number) {


        return 1;
    }
    if (fp->hd.type & 10 && fp->hd.type & 0x80) {


        return 2;
    }

    return -1;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsCmdCheckExistFile);
int fsCmdCheckExistFile(fsFile* fp /* r16 */) {
    int ret; // r16
    utilExclLockOtherThread();
    fp = ___fsSubCmdCheckRootFile(fp);
    if (___fsSubCmdCheckCdHdFile(fp) == NULL) {
        ret = -2;
    } else {
        ret = ___fsSubCmdCheckCdHdExistFile(fp);
    }
    utilExclUnlockOtherThread();
    return ret;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsSubCmdSetRealFile0);
static fsFile* fsSubCmdSetRealFile0(fsFile* realfp /* r17 */, fsFile* fp /* r16 */) {
    fsFile* ret; // r16
    utilExclLockOtherThread();
    ret = ___fsSubCmdSetRealFile0(realfp, fp);
    utilExclUnlockOtherThread();
    return ret;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", ___fsSubCmdSetRealFile0);
static fsFile* ___fsSubCmdSetRealFile0(fsFile* realfp /* r17 */, fsFile* fp /* r16 */) {
    fsFile* ret; // r2
    int offset; // r3
    int size; // r4
    // signed int plsn; // r5
    // signed int psize; // r2
    // signed int poffset; // r2
    // signed int psize; // r5


    if (___fsSubCmdCheckCdHdFile(fp) != NULL) {

        if (___fsSubCmdCheckCdHdExistFile(fp) <= 0) {

            return fp;
        }

        realfp->pack = fp->pack;
        return NULL;
    }
    if ((fp->check.type & 0x50) == 0x50) {



        ret = ___fsSubCmdSetRealFile0(realfp, fp->mgp.file);
        if (ret != NULL) {

            return ret;
        }

        offset = (fp->hd.offset / 2048) * 2048;
        size = fp->hd.size;

        if ((realfp->check.type & 5) && (realfp->check.number != 0)) {
            int plsn; // r5
            int psize; // r2



            plsn = realfp->cd.lsn;
            psize = realfp->cd.size;
            if (psize < offset) {
                size = 0;
            } else { psize -= offset; if (psize < size)
                size = psize;
            }
            realfp->hd.offset = realfp->hd.offset +  (offset / 2048);
            realfp->hd.size = size;
            return NULL;
        }

        if (realfp->check.type & 0xA) {
            int poffset; // r2
            int psize; // r5



            poffset = realfp->hd.offset;
            psize = realfp->hd.size;
            if (psize < offset) {
                size = 0;
            } else { psize -= offset; if (psize < size)
                size = psize;
            }
            realfp->hd.offset = poffset + offset;
            realfp->hd.size = size;
            return NULL;
        }


        return fp;
    }



    return fp;

}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsSubCmdSetRealFile);
static fsFile * fsSubCmdSetRealFile(fsFile* realfp /* r18 */, fsFile* fp /* r17 */) {
    fsFile* ret; // r16
    int err = 0; // r2

    utilExclLockOtherThread();
    ret = ___fsSubCmdCheckRootFile(fp);
    err = ___fsSubCmdCheckCdHdFile(ret) == NULL;
    if (!err) {
        ret = ___fsSubCmdSetRealFile0(realfp, fp);
    }
    utilExclUnlockOtherThread();
    return ret;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsCmdSetRealFile);
int fsCmdSetRealFile(fsFile* realfp /* r2 */, fsFile* fp /* r2 */) {
    return fsSubCmdSetRealFile(realfp, fp) == NULL;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", ___fsSubCmdNullDevFixFile);
static int ___fsSubCmdNullDevFixFile(fsFile * fp /* r2 */) {
    ASSERT(fp ==ID_fsFile(&data_null_dev));

    if (fp->check.type & 0x40) {
        return 1;
    }
    // fp->unk0 = (s32) (((s32) fp->unk0 & ((-1 << 0x20) | 0xFF)) | (((u64) (0 << 0x28) >> 0x28) << 8));
    fp->check.number &= 0;
    fp->check.type |= ~0x3F;
    fp->check.pad1 = 0; // @todo which struct does this go to?
    fp->check.pad2 = 0x40000000;
    return 2;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", ___fsSubCmdCdCommonFixFile);
static int ___fsSubCmdCdCommonFixFile(fsFile* fp /* r16 */) {
    sceCdlFILE file[1]; /* r29+0x30 */
    char fullpath[256]; // r29+0x60
    int ret; // r17



    if (fp == ID_fsFile(&data_null_dev)) {
        ret = ___fsSubCmdNullDevFixFile(fp);
    } else if (fp->check.type & 0x40) {
        ret = 1;
    } else {




        ret = 1;
        if (fp->check.type & 0x20) {
            if (___shPathMakeCdDataBase(fullpath, fp->cd.name) == 0) ret = 0;
        } else if (___shPathMakeCdData(fullpath, fp->cd.name) == 0) {
            ret = 0;
        }
        if ((ret != 0) && (fs_stat.disk_number == 0)) {
            ret = 0;
        }
        if ((ret != 0) && (___shCdSearchFile(file, fullpath) == 0)) {
            fp->check.number &= 0;
            ret = -1;
        }
        if (ret != 0) {

            fp->cd.type &= 0x7F;
            fp->cd.type |= 0x40;

            fp->cd.number = fs_stat.disk_number;
            fp->cd.lsn = file->lsn;
            fp->cd.size = file->size;
            ret = 2;
        }
    }
    return ret;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", ___fsSubCmdCd1stFixFile);
static int ___fsSubCmdCd1stFixFile(fsFile* fp /* r2 */) {
    if (fp->cd.type & 1)
        return ___fsSubCmdCdCommonFixFile(fp);
    return 0;
}
// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", ___fsSubCmdCdFixFile);
static int ___fsSubCmdCdFixFile(fsFile* fp /* r2 */) {
    if (fp->cd.type & 5)
        return ___fsSubCmdCdCommonFixFile(fp);
    return 0;
}
// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", ___fsSubCmdHdCommonFixFile);
static int ___fsSubCmdHdCommonFixFile(fsFile* fp /* r16 */) {
    signed int size; // r2
    char fullpath[256]; // r29+0x30
    signed int ret; // r17

    if (fp == ID_fsFile(&data_null_dev)) {
        ___fsSubCmdNullDevFixFile(fp);
    } else {
        if (fp->check.type & 0x40) {
            ret = 1;
        } else {
            ret = 1;
            if (fp->hd.type & 0x20) {
                if (___shPathMakeHdDataBase(fullpath, fp->hd.name) == 0) {
                    ret = 0;
                }
            } else if (___shPathMakeHdData(fullpath, fp->hd.name) == 0) {
                ret = 0;
            }
            if (ret != 0) {
                size = ___shHdGetFileSize(fullpath);
                if (size < 0) {
                    fp->hd.type &= 0x7F;
                    ret = -1;
                } else {
                    fp->hd.padding &= 0;
                    fp->hd.type |= ~0x3F;
                    fp->hd.offset = 0;
                    fp->hd.size = size;
                    ret = 2;
                }
            }
        }
    }
    return ret;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", ___fsSubCmdHd1stFixFile);
static int ___fsSubCmdHd1stFixFile(fsFile* fp /* r2 */) {
    if (fp->hd.type & 2)
        return ___fsSubCmdHdCommonFixFile(fp);
    return 0;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", ___fsSubCmdHdFixFile);
static int ___fsSubCmdHdFixFile(fsFile* fp /* r2 */) {
    if (fp->hd.type & 10)
        return ___fsSubCmdHdCommonFixFile(fp);
    return 0;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsCmdDiskSelectC);
int fsCmdDiskSelectC() {
    fs_stat.fix_func_list = ___fsSubCmdFixFuncListC;
    return 1;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsCmdDiskSelectCH);
int fsCmdDiskSelectCH() {
    fs_stat.fix_func_list = ___fsSubCmdFixFuncListCH;
    return 1;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsCmdDiskSelectHC);
int fsCmdDiskSelectHC() {
    fs_stat.fix_func_list = ___fsSubCmdFixFuncListHC;
    return 1;
}
// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsCmdExecDevSelect);
int fsCmdExecDevSelect(int mode /* r2 */) {
    fs_stat.exec_dev = mode;
    return 1;
}
// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", ___fsSubCmdFixFile);
static int ___fsSubCmdFixFile(fsFile* fp /* r17 */) {
    int (**funcp)(fsFile*); // r18
    int (*___fsFunc)(fsFile*); // r2
    int ret; // r16

    ret = 0;
    if (___fsSubCmdCheckCdHdFixFile(fp) == NULL) {
        ret = 1;
    } else {
        funcp = fs_stat.fix_func_list;
        if ((fp->check.type & 0xF) && (shPathCheckExecRoot(fp->cd.name) != 0)) {
            switch (fs_stat.exec_dev) {             /* irregular */
                case 1:
                    funcp = &___fsSubCmdFixFuncListC;
                    break;
                case 2:
                    funcp = &___fsSubCmdFixFuncListH;
                    break;
            }
        }
        for (; ___fsFunc = *funcp, ___fsFunc != NULL; ___fsFunc = *++funcp) {
            ret = ___fsFunc(fp);
            if (ret) break;
        }
    }
    if (ret == 0) {
        // fp->unk0 = (s32) (((s32) fp->unk0 & ((-1 << 0x20) | 0xFF)) | (((u64) (0 << 0x28) >> 0x28) << 8));
        fp->check.number &= 0;
        // fp->unk0 = (s8) (fp->unk0 & 0x7F);
        // fp->unk0 = (s8) (fp->unk0 | 0x40);
        fp->check.type &= 0x7F;
        fp->check.type |= 0x40;
    }

    return ret;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsCmdFixFile);
int fsCmdFixFile(fsFile* fp /* r16 */) {
    int ret; // r16

    utilExclLockOtherThread();
    fp = ___fsSubCmdCheckRootFile(fp);
    if (___fsSubCmdCheckCdHdFile(fp) == NULL) {
        ret = 0;
    } else {
        ret = ___fsSubCmdFixFile(fp);
    }
    utilExclUnlockOtherThread();
    return ret;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsSubCmdCdCheckTrayOpen);
static int fsSubCmdCdCheckTrayOpen(void) {
    int stat; // r2
    u_int traycnt; // r29+0x1C

    while (!shCdTrayReq(2, &traycnt)) {
        shSyncVEnd(0);
        shCdSync(1);
    }

    if (traycnt) return 1;

    stat = shCdStatus();


    if (stat == 1)
        return 1;
    return stat == 32;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsSubCmdCdGetMedia);
static int fsSubCmdCdGetMedia(void) {
    int cur_media; // r2

    switch (shCdGetDiskType()) {
        /* irregular */
        case 0x14:
            cur_media = 1;
            break;
        case 0x12:
            cur_media = 2;
            break;
        case 0x13:
            cur_media = 4;
            break;
        case 0x10:

            cur_media = 8;
            break;
        case 0x11:
            cur_media = 0x10;
            break;
        case 0xFD:

            cur_media = 0x20;
            break;
        case 0xFE:
            cur_media = 0x40;
            break;
        case 0x0:

            cur_media = 0x200;
            break;
        case 0x1:
            cur_media = 0x100;
            break;
        case 0xFF:
            cur_media = 0x400;
            break;
        case 5:
        default:
            cur_media = 0x80;
    }

    return cur_media;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsSubCmdCdGetMmode);
static int fsSubCmdCdGetMmode(int media /* r2 */) {
    int mmode; // r2

    if (media & 0x3E)
        mmode = 1;
    else if (media & 0x41)
        mmode = 2;
    else
        mmode = 0;

    return mmode;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsSubCmdCdRead);
static int fsSubCmdCdRead(int lsn /* r18 */, int sectors /* r17 */, void* buf /* r16 */) {
    static sceCdlFILE* rmode = (sceCdlFILE*)256; // @ 0x0033B2A0
    int ret; // r4

    do {
        switch (buf != NULL ? shCdReadW(lsn, sectors, buf, rmode) : shCdSeekW(lsn)) {                           /* irregular */
            case 0:
                ret = 1;
                break;
            case 48:
                ret = 0;
                break;
            case 49:
                ret = 0;
                break;
            case 1:
                ret = 0;
                break;
            case 50:
            case 19:
            case -1:
            case 20:
            default:
                ret = 0;
                break;

        }

        if (ret != 0) {
            return 1;
        }
        fsCmdCdCheckDisk(0);
    } while (true);
}


// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsCmdHdInit);
int fsCmdHdInit(int enable /* r2 */) {
    if (enable) {
        shHdInit();
        fs_stat.disk_emulation = 1;
        fsSubCmdHdRead = fsSubCmdHdRead0;
    } else {
        fs_stat.disk_emulation = 0;
        fsSubCmdHdRead = fsSubCmdHdError;
    }
    return 1;
    // fs_stat.disk_emulation = 1;
}
static int strcmp__(char * s /* r2 */, char * t /* r2 */) {
    for (; *s == *t; s++, t++) {
        if (*s == 0) return 0;
    }
    return *s - *t;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", shHdOpenC);
static int shHdOpenC(char* fullpath /* r17 */, int mode /* r16 */) {
    if ((strcmp__(fullpath, hdopen_lastpath) != 0) || (hdopen_lastmode != mode)) {
        if (hdopen_lastpath[0]) {
            shHdClose(hdopen_lastfd);
        }
        hdopen_lastfd = shHdOpen(fullpath, mode);
        hdopen_lastmode = mode;
        strcpy(&hdopen_lastpath, fullpath);
    }
    return hdopen_lastfd;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", shHdCloseC);
static int shHdCloseC(int fd /* r2 */) {
    if (hdopen_lastfd == fd)
        return 0;
    return -1;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsSubCmdHdRead0);
static int fsSubCmdHdRead0(char* name /* r30 */, int offset /* r29+0xAC */, int size /* r23 */, void* buf /* r22 */) {
    int retry; // r16
    int ret; // r17
    char* fullpath; // r2
    int fd; // r18
    int remainsize; // r19
    int readsize; // r20
    char* readbuf; // r21
    retry = 0xA;













    do {
        do {
            fs_stat.now_reading = 1;



            if (buf != NULL) {
                SyncDCache(buf, (char*)buf + size);
                InvalidDCache(buf, (char*)buf + size);
            }



            fd = shHdOpenC(name, 1);
            if (fd >= 0) {
                remainsize = size;
                readsize = 0x40000;
                readbuf = buf;

                ret = 1;
                if (shHdLseek(fd, offset, 0) == -1) ret = 0;


                if (readbuf != NULL) {
                    while ((fs_stat.now_reading != 0) && (ret != 0) && (remainsize > 0)) {
                        if (remainsize < readsize) {
                            readsize = remainsize;
                        }
                        if (shHdRead(fd, readbuf, readsize) == -1) ret = 0;
                        readbuf += readsize;
                        remainsize -= readsize;
                    }
                }







                if (fs_stat.now_reading == 0) ret = 0;
                fs_stat.now_reading = 0;


                if (shHdCloseC(fd) == -1) ret = 0;
            } else {
                ret = 0;
            }















            if (ret != 0) {
                return 1;
            }
            retry -= 1;
        } while (retry > 0);
        retry = 0x3c;



    } while (true); // hack, probably
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsSubCmdHdError);
static int fsSubCmdHdError() {
    return 0;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsSubCmdRealRead);
static int fsSubCmdRealRead(fsFile* fp /* r17 */, void* buf /* r16 */) {
    if (fp ==ID_fsFile(&data_null_dev)) {

        if (buf != NULL) UtilMemSet(buf, 0, fp->cd.lsn);
        return 1;
    } else if (fp->check.number) {
        return fsSubCmdCdRead(fp->cd.lsn, (fp->cd.size + 0x7ff) / 2048, buf);
    } else if (fp->hd.type & 0x80) {
        char fullpath[256]; // r29+0x30
        char* name; // r2
        name = fp->hd.name;
        if (fp->hd.type & 0x20) {
            if (!shPathMakeHdDataBase(fullpath, name)) {

                return 0;
            }

        } else if (!shPathMakeHdData(fullpath, name)) {

            return 0;
        }

        return (*fsSubCmdHdRead)(fullpath, fp->hd.offset, fp->hd.size, buf);
    }



    return 0;

}
// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsSubCmdRead);
static int fsSubCmdRead(fsFile* fp /* r2 */, void* buf /* r16 */) {
    int ret; // r16
    fsFile realfp; // r29+0x20
    if (fsSubCmdSetRealFile0(&realfp, fp) != NULL) {
        return 0;
    } else {
        ret = fsSubCmdRealRead(&realfp, buf);
        VERBOSE(3, "%s", realfp.hd.name);
    }
    return ret;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", ___fsCmdRead);
static int ___fsCmdRead(fsFile* fp /* r17 */, void* buf /* r16 */) {
    int ret; // r16

    if (!fsCmdFixFile(fp)) {
        return 0;
    } else {
        ret = fsSubCmdRead(fp, buf);
        verbose(3, ": read %s.\n", ret ? "finished" : "failed");
    }
    return ret;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsCmdRead);
int fsCmdRead(fsFile* fp /* r2 */, void* buf /* r2 */) {
    if (fp == ID_fsFile(&data_null_dev))
        ASSERT(!"can't read null.dev"); // @todo: additional string here
    return ___fsCmdRead(fp, buf);
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsCmdReadPart);
int fsCmdReadPart(fsFile* fp /* r2 */, void* buf /* r2 */, int offset /* r2 */, int size /* r2 */) {
    fsFile partfile; // r29+0x10

    ASSERT(offset%2048==0);
    ASSERT(size%2048==0);

    partfile.mgf.type = 0x50;
    partfile.mgf.parent = fp;
    partfile.mgf.offset = offset;
    partfile.mgf.size = size;

    return ___fsCmdRead(&partfile, buf);
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsCmdSetParamForCheckDisk);
int fsCmdSetParamForCheckDisk(int media_permission /* r2 */, fsFile** fplist /* r2 */, void** buflist /* r2 */, int (* check_func)(fsFile**, void**) /* r2 */) {
    fsCmdParam_media_permission = media_permission;
    fsCmdParam_fplist = fplist;
    fsCmdParam_buflist = buflist;
    fsCmdParam_check_func = check_func;

    return 1;
}

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsCmdCdCheckDisk);
int fsCmdCdCheckDisk(int force_check /* r2 */) {
    return fsCmdCdCheckDisk2(force_check, fsCmdParam_media_permission, fsCmdParam_fplist, fsCmdParam_buflist, fsCmdParam_check_func);
}

// INCLUDE_RODATA("asm/nonmatchings/Multi_thr/filesys/filecmd", @229_0x00391520);
//
// INCLUDE_RODATA("asm/nonmatchings/Multi_thr/filesys/filecmd", @230);
//
// INCLUDE_RODATA("asm/nonmatchings/Multi_thr/filesys/filecmd", @595_0x00391560);
//
// INCLUDE_RODATA("asm/nonmatchings/Multi_thr/filesys/filecmd", @605_0x00391578);
//
// INCLUDE_RODATA("asm/nonmatchings/Multi_thr/filesys/filecmd", @606_0x00391588);
//
// INCLUDE_RODATA("asm/nonmatchings/Multi_thr/filesys/filecmd", @607_0x00391598);

// INCLUDE_RODATA("asm/nonmatchings/Multi_thr/filesys/filecmd", @628);
//
// INCLUDE_RODATA("asm/nonmatchings/Multi_thr/filesys/filecmd", @629);
//
// INCLUDE_RODATA("asm/nonmatchings/Multi_thr/filesys/filecmd", @654);
//
// INCLUDE_RODATA("asm/nonmatchings/Multi_thr/filesys/filecmd", @655);
//
// INCLUDE_RODATA("asm/nonmatchings/Multi_thr/filesys/filecmd", @656);
//
// INCLUDE_RODATA("asm/nonmatchings/Multi_thr/filesys/filecmd", @657);

// INCLUDE_ASM("asm/nonmatchings/Multi_thr/filesys/filecmd", fsCmdCdCheckDisk2);
int fsCmdCdCheckDisk2(int force_check /* r2 */, int media_permission /* r29+0xAC */, fsFile** fplist /* r22 */, void** buflist /* r21 */, int (* check_func)(fsFile**, void**) /* r30 */) {
    fsFile** fpp = NULL; // r16
    fsFile* fp = NULL; // r17
    void** bufp = NULL; // r18
    void* buf = NULL; // r23
    int media = 0; // r19
    int step = 0; // r20
    int open = 0; // r2
    int mmode = 0; // r2
    int number = 0; // r2


    if (force_check != 0) {
        step = 1;
    }
    do {
        open = fsSubCmdCdCheckTrayOpen();
        switch (step) {
            case 0:
                if (open == 1) {
                    fs_stat.disk_number = 0;
                    step = 1;
                }
                break;
            default:
                if (open == 1) {
                    fs_stat.disk_number = 0;
                    step = 1;
                    shSyncVEnd(0);
                    shCdSync(1);
                } else {
                    step = 2;
                    if (shCdDiskReady(1) == 2) {
                        shSyncVEnd(0);
                        shCdSync(1);
                        media = fsSubCmdCdGetMedia();
                        if (media & 0x180) {
                            shSyncVEnd(0);
                            shCdSync(1);
                        } else if (media & media_permission) {
                            fs_stat.disk_count++;
                            fs_stat.disk_count = fs_stat.disk_count & 0xFFFFFF;
                            if (fs_stat.disk_count == 0) fs_stat.disk_count += 1;
                            fs_stat.disk_number = -fs_stat.disk_count;
                            step = 5;
                        } else if (media & 0x200) {
                            step = 3;
                        } else {
                            step = 4;
                        }
                    }
                }
                break;
            case 3:
            case 4:
                if (open == 1) {
                    step = 1;
                    break;
                }
                shSyncVEnd(0);
                shCdSync(1);
                break;
            case 5:
                if (open == 1) {
                    step = 1;
                    break;
                } else {
                    mmode = fsSubCmdCdGetMmode(media);
                    fs_stat.media_type = mmode;
                    shCdMmode(mmode);
                    step = 6;
                }
                break;
            case 6:

                if (check_func == NULL || fplist == NULL || (fpp = fplist, fp = *fpp, fp == NULL)) {
                    step = 0;
                    break;
                }
                step = 7;
            case 7:
                if (open == 1) {
                    step = 1;
                } else {
                    fsCmdFixFile(fp);
                    fpp++;
                    fp = *fpp;
                    if (fp != NULL) {
                        break;
                    }
                    fpp = fplist;
                    fp = *fplist;
                    bufp = buflist;
                    buf = *buflist;
                    step = 8;

                }
                break;
            case 8:
                if (open == 1) {
                    step = 1;
                } else {
                    if ((buf != NULL) && (fsCmdCheckExistFile(fp) > 0)) {
                        if (fsSubCmdRead(fp, buf) != 0) {
                            fpp++;
                            bufp++;
                        } else {
                            shSyncVEnd(0);
                            shCdSync(1);
                        }
                    } else {
                        fpp++;
                        bufp++;
                    }
                    fp = *fpp;
                    if (fp == NULL) {
                        number = check_func(fplist, buflist);
                        if (number > 0) {
                            fs_stat.disk_number = number;
                            step = 0;
                        } else {
                            step = 4;
                        }
                    }
                }
                break;
        }
        fs_stat.disk_check = step;
    } while (step != 0);
    return 1;
}

int fsCmdGetTrayStat(void) {
    int step = fs_stat.disk_check; // r4
    switch (step) {
        case 0:
            return 0;
        case 1:
            return 1;
        case 3:
            return 3;
        case 2:
            return 4;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        default:
            return 2;
    }
}



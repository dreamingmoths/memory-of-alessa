#include "Multi_thr/filesys/fcread.h"
#include "Multi_thr/filesys/filecmd.h"
#include "Multi_thr/filesys/fileserv.h"

static void warning_no_entry(union fsFileIndex* id /* r2 */);
static int file_trans_merge_to_direct(union fsFileIndex* id /* r2 */);

static void warning_no_entry(union fsFileIndex* id /* r2 */) {
    printf("fcread.c:20> WARNING! file entry is none! %x\n", id);
}

static int file_trans_merge_to_direct(union fsFileIndex* id /* r2 */) {    
    int ret = 0; // r2
    union fsFile* file; // r6

    file = id->index.fp;
    if ((execEnv_hd_merge_file != 0) && (file->check.type & 0x10)) {
        file->check.pad2 = 0;
        file->check.type = 3;
        file->check.number = 0;
        file->check.pad0 = (int) id->index.name;
        file->check.pad1 = 0;
        file->check.pad2 = 0;
        ret = 1;
    }
    return ret;
}

int FcFixFile(union fsFileIndex* id /* r2 */) {
    union fsFile *file; // r7

    if (id == NULL) {
        warning_no_entry(id);
        return -1;
    }
    file = id->index.fp;
    file_trans_merge_to_direct(id);
    file = fsCmdCheckFixFile(file);
    if (execEnv_hd_merge_file) {
        if (!file) {
            return -1;
        }
        return fcFixFile(file);
    } 
    if (!file) {
        return -1;
    }
    return fcFixFile(file);    
}

int fcGetFileSize(union fsFile* file /* r2 */) {
    union fsFile real[1];
    
    fsCmdSetRealFile(real, file);    
    return real[0].check.pad2;
}

int FcGetFileSize(union fsFileIndex *id) {
    union fsFile* file; // r2 not used?
    int fid; // r2

    if (id == NULL) {
        warning_no_entry(id);
        return 0;
    }
    fid = FcFixFile(id);
    if (fid != -1) {
        fsSync(0, fid);
    }
    return fcGetFileSize(id->index.fp);
}

int FcRead(union fsFileIndex* id /* r2 */, void* databuf /* r17 */) {
    union fsFile* file; // r16
    if (id == NULL) {
        warning_no_entry(id);
        return -1;
    }
    file = id->index.fp;
    file_trans_merge_to_direct(id);
    fcFixFile(file);
    return fcRead(file, databuf);
}

int FcReadPart(union fsFileIndex* id /* r2 */, void* databuf /* r19 */, int offset /* r18 */, int size /* r17 */) {
    union fsFile* file;

    if (id == NULL) {
        warning_no_entry(id);
        return -1;
    }
    file = id->index.fp;
    file_trans_merge_to_direct(id);
    fcFixFile(file);
    return fcReadPart(file, databuf, offset, size);
}

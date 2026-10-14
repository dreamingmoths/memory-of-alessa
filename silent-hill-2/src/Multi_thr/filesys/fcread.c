#include "Multi_thr/filesys/fcread.h"
#include "Multi_thr/filesys/filecmd.h"
#include "Multi_thr/filesys/fileserv.h"

static void warning_no_entry(fsFileIndex* id);
static int file_trans_merge_to_direct(fsFileIndex* id);

static void warning_no_entry(fsFileIndex* id) {
    printf("fcread.c:20> WARNING! file entry is none! %x\n", id);
}

static int file_trans_merge_to_direct(fsFileIndex* id) {    
    int ret = 0;
    fsFile* file;

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

int FcFixFile(fsFileIndex* id) {
    fsFile *file;

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

int fcGetFileSize(fsFile* file) {
    fsFile real[1];
    
    fsCmdSetRealFile(real, file);    
    return real[0].check.pad2;
}

int FcGetFileSize(fsFileIndex* id) {
    fsFile* file; 
    int fid; 

    if (id == NULL) {
        warning_no_entry(id);
        return 0;
    }
    
    
    fid = FcFixFile(id);
    if (fid != -1) fsSync(0, fid);
    
    file = id->index.fp;
    return fcGetFileSize(file);
}

int FcRead(fsFileIndex* id, void* databuf) {
    fsFile* file;
    if (id == NULL) {
        warning_no_entry(id);
        return -1;
    }
    file = id->index.fp;
    file_trans_merge_to_direct(id);
    fcFixFile(file);
    return fcRead(file, databuf);
}

int FcReadPart(fsFileIndex* id, void* databuf, int offset, int size) {
    fsFile* file;

    if (id == NULL) {
        warning_no_entry(id);
        return -1;
    }
    file = id->index.fp;
    file_trans_merge_to_direct(id);
    fcFixFile(file);
    return fcReadPart(file, databuf, offset, size);
}

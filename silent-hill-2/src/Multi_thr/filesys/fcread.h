#ifndef FCREAD_H
#define FCREAD_H

#include "sh2_common.h"
#include "data/fs_structs.h"

int FcFixFile(fsFileIndex* id);
int fcGetFileSize(fsFile* file);
int FcGetFileSize(fsFileIndex* id);
int FcRead(fsFileIndex* id, void* databuf);
int FcReadPart(fsFileIndex* id, void* databuf, int offset, int size);

extern int execEnv_hd_merge_file; // size: 0x4, address: 0x5526B8

#endif // FCREAD_H

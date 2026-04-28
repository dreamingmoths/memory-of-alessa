#ifndef FCREAD_H
#define FCREAD_H

#include "common.h"
#include "FilesList/fileslist_bg.h" // correct?

int FcFixFile(union fsFileIndex* id /* r2 */);
int FcRead(union fsFileIndex* id /* r2 */, void* databuf /* r17 */);
int FcGetFileSize(union fsFileIndex* id);
int fcGetFileSize(union fsFile* file /* r2 */);
int FcReadPart(union fsFileIndex* id /* r2 */, void* databuf /* r19 */, int offset /* r18 */, int size /* r17 */);

extern int execEnv_hd_merge_file; // size: 0x4, address: 0x5526B8

#endif // FCREAD_H

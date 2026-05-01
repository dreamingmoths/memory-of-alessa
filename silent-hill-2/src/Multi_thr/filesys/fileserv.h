#ifndef FILESERV_H
#define FILESERV_H

#include "common.h"
#include "FilesList/fileslist_bg.h" // correct?

int fsSync(int mode /* r17 */, int fid /* r16 */);
int fcRead(union fsFile* fp /* r17 */, void* buf /* r16 */);
int fcFixFile(union fsFile* fp /* r2 */);

#endif // FILESERV_H

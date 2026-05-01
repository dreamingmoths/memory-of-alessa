#ifndef FILECMD_H
#define FILECMD_H

#include "common.h"
#include "FilesList/fileslist_bg.h" // correct?

int fsCmdSetRealFile(union fsFile* realfp /* r2 */, union fsFile* fp /* r2 */);
union fsFile* fsCmdCheckFixFile(union fsFile* fp /* r16 */);

#endif // FILECMD_H

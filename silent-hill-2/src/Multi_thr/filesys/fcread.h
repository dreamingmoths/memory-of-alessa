#ifndef FCREAD_H
#define FCREAD_H

#include "common.h"
#include "FilesList/fileslist_bg.h" // correct?

int FcRead(union fsFileIndex* id /* r2 */, void* databuf /* r17 */);

#endif // FCREAD_H

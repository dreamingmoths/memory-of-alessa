#ifndef UTILEXCL_H
#define UTILEXCL_H

#include "sh2_common.h"

int utilExclInit(void);

int utilExclLockOtherThread(void);

int utilExclUnlockOtherThread(void);

#endif // UTILEXCL_H

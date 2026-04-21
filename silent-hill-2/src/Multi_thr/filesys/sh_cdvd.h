#ifndef SH_CDVD_H
#define SH_CDVD_H

#include "common.h"

int shCdInitR(int initmode /* r17 */, int mmode /* r16 */);
int shSifInit(void);
int shSifLoadModuleR(char* module /* r20 */, int args /* r19 */, char* argp /* r18 */);
int shSifRebootIopR(char* imgfile /* r18 */);

#endif // SH_CDVD_H

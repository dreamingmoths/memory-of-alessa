#ifndef SH_CDVD_H
#define SH_CDVD_H

#include "common.h"

// ???
extern int CreateSema2(int, int, int);

// total size: 0x10
typedef struct shCdWorkT {
    // Members
    int wait_sid; // offset 0x0, size 0x4
    int exec_sid; // offset 0x4, size 0x4
    int cmd_sid; // offset 0x8, size 0x4
    int rtc_ok; // offset 0xC, size 0x4
} shCdWorkT;

int shCdInit(int initmode /* r16 */, int mmode /* r17 */);
int shCdMmode(int mmode /* r16 */);
int shCdInitR(int initmode /* r17 */, int mmode /* r16 */);
void shCdCallbackFunc(void);
int shCdInitW(int cb_prio /* r18 */, void* stack /* r17 */, int stack_size /* r16 */);
int shSifInit(void);
int shSdSifInit(void);
int shSifSyncIop(void);
int shSifLoadModuleR(char* module /* r20 */, int args /* r19 */, char* argp /* r18 */);
int shSifRebootIopR(char* imgfile /* r18 */);

extern shCdWorkT shCdWork; // size: 0x10, address: 0x33B3D0
extern int exec_cnt; // size: 0x4, address: 0x1159248
extern int cmd_cnt; // size: 0x4, address: 0x1159240

#endif // SH_CDVD_H

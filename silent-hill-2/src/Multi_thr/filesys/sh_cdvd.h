#ifndef SH_CDVD_H
#define SH_CDVD_H

#include "common.h"
#include "eekernel.h"
#include "sifdev.h"
#include "sifrpc.h"

// I will find their correct place another time

// ???
extern int CreateSema2(int, int, int);

// ee/include/eekernel.h
// extern void WaitSema(int);

// ee/include/eekernel.h
// extern int SignalSema(int);

// common/include/libcdvd.h
extern int sceCdInit(int init_mode);

// ee/include/eekernel.h
// extern int iSignalSema(int);

// ???
extern int CreateSema2(int, int, int);

// common/include/libcdvd.h
// int *sceCdCallback(void (*func)(int)); this is the signature from the sdk, I dont remember from where I got the one below
extern void sceCdCallback(void f(void));

// common/include/libcdvd.h
extern int sceCdInitEeCB(int cb_prio, void *stack_addr, int stack_size);

// ee/include/sifdev.h
// extern int sceFsReset(void);         

// ee/include/sifrpc.h
//extern void sceSifInitRpc(u_int mode);

// ee/include/sifdev.h
// extern void sceSifLoadFileReset(void);

// ee/include/sifdev.h
// extern int sceSifSyncIop(void);

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

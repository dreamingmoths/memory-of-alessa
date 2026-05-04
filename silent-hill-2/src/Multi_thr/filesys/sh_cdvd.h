#ifndef SH_CDVD_H
#define SH_CDVD_H

#include "common.h"
#include "libcdvd.h"

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

// total size: 0x8
typedef struct Old_Rtc {
    // Members
    u_char stat; // offset 0x0, size 0x1
    u_char second; // offset 0x1, size 0x1
    u_char minute; // offset 0x2, size 0x1
    u_char hour; // offset 0x3, size 0x1
    u_char pad; // offset 0x4, size 0x1
    u_char day; // offset 0x5, size 0x1
    u_char month; // offset 0x6, size 0x1
    u_char year; // offset 0x7, size 0x1
} Old_Rtc;

// total size: 0x14
typedef struct shHdWorkT {
    // Members
    volatile int hd_sid; // offset 0x0, size 0x4
    int last_fd; // offset 0x4, size 0x4
    char* last_filename; // offset 0x8, size 0x4
    int last_offset; // offset 0xC, size 0x4
    int read_size; // offset 0x10, size 0x4
} shHdWorkT;

int shCdInit(int initmode /* r16 */, int mmode /* r17 */);
int shCdMmode(int mmode /* r16 */);
int shCdInitR(int initmode /* r17 */, int mmode /* r16 */);
void shCdCallbackFunc(void);
int shCdInitW(int cb_prio /* r18 */, void* stack /* r17 */, int stack_size /* r16 */);
int shSifInit(void);
int shSdSifInit(void);
int shSifSyncIop(void);
int shSifLoadModule(char* module /* r18 */, int args /* r17 */, char* argp /* r16 */);
int shSifLoadModuleR(char* module /* r20 */, int args /* r19 */, char* argp /* r18 */);
int shSifRebootIop(char* imgfile /* r16 */);
int shSifRebootIopR(char* imgfile /* r18 */);
int shCdRead(int lsn /* r19 */, int sectors /* r18 */, void* buf /* r17 */, sceCdRMode* mode /* r16 */);
int shCdSeek(int lsn /* r16 */);
int shCdReadClock(Old_Rtc* rtc /* r17 */);
int shCdSearchFile(sceCdlFILE* file /* r2 */, char* fullpath /* r2 */);
int ___shCdSearchFile(sceCdlFILE* fp /* r17 */, char* name /* r16 */);
int shCdTrayReq(int mode /* r17 */, u_int* traycnt /* r16 */);
int shCdReadW(int lsn /* r21 */, int sectors /* r20 */, void* buf /* r19 */, sceCdRMode* mode /* r18 */);
int shCdSeekW(int lsn /* r18 */);
int shCdDiskReady(int mode /* r16 */);
int shCdGetDiskType(void);
int shCdGetError(void);
int shCdStatus(void);
int shCdSync(int mode /* r16 */);
void shCdSdStart(void);
void shCdSdEnd(void);
int shHdInit(void);
int shHdOpen(char* name /* r17 */, int mode /* r16 */);
int shHdRead(int fd /* r18 */, void* buffer /* r17 */, int size /* r16 */);
int shHdClose(int fd /* r16 */);
int shHdLseek(int fd /* r18 */, int offset /* r17 */, int where /* r16 */);
int ___shHdGetFileSize(char* name /* r16 */);

extern shCdWorkT shCdWork; // size: 0x10, address: 0x33B3D0
extern int exec_cnt; // size: 0x4, address: 0x1159248
extern int cmd_cnt; // size: 0x4, address: 0x1159240
extern Old_Rtc old_rtc; // size: 0x8, address: 0x1159238
extern shHdWorkT shHdWork;

#endif // SH_CDVD_H

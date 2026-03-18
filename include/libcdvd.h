// all credits to https://github.com/Mikompilation/Himuro/blob/828c49053f0d0a67694ae678463dfa3b770b6ef3/include/sce/libcdvd.h

#ifndef SCE_LIBCDVD_H
#define SCE_LIBCDVD_H

#include "common.h"

#define STMNBLK 0
#define STMBLK 1

#define SCECdINIT 0
#define SCECdINoD 1
#define SCECdEXIT 5

#define SCECdCD 1
#define SCECdDVD 2

#define SCECdSpinMax 0
#define SCECdSpinNom 1
#define SCECdSpinStm 0
#define SCECdSpinDvdDL0 0
#define SCECdSpinX1 2

#define SCECdSecS2048 0
#define SCECdSecS2328 1
#define SCECdSecS2340 2

typedef struct
{
    u_char stat;
    u_char second;
    u_char minute;
    u_char hour;
    u_char pad;
    u_char day;
    u_char month;
    u_char year;
} sceCdCLOCK;

typedef struct
{
    u_char trycount;
    u_char spindlctrl;
    u_char datapattern;
    u_char pad;
} sceCdRMode;

typedef struct
{
    u_int lsn;
    u_int size;
    char name[16];
    u_char date[8];
    u_int flag;
} sceCdlFILE;

int sceCdInit(int init_mode);
int sceCdMmode(int media);
int sceCdReadClock(sceCdCLOCK *rtc);
int sceCdStRead(u_int size, u_int *buf, u_int mode, u_int *err);
int sceCdStStop(void);

int sceCdDiskReady(int mode);
int sceCdStInit(u_int bufmax, u_int bankmax, u_int iop_bufaddr);
int sceCdSearchFile(sceCdlFILE *fp, const char *name);
int sceCdStStart(u_int lbn, sceCdRMode *mode);

#endif // SCE_LIBCDVD_H
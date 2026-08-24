#ifndef PSS_COMMON_H
#define PSS_COMMON_H

#include "sh2_common.h"

#include "movie/movie.h"
#include "movie/pss_videodec.h"
#include "movie/pss_audiodec.h"
#include "movie/pss_readbuf.h"
#include "movie/pss_vobuf.h"
#include "movie/pss_read.h"
#include "movie/pss_main.h"

typedef struct _PssCommonWork {
    // total size: 0x13B00
    u_char* mpegWorkp; // offset 0x0, size 0x4
    ReadBuf* readBufp; // offset 0x4, size 0x4
    u_long128* viBufDatap; // offset 0x8, size 0x4
    TimeStamp timeStamp[VIBUF_TS_SIZE] __attribute__((aligned(64))); // offset 0x40, size 0x3000
    VoData* voBufDatap; // offset 0x3040, size 0x4
    u_char audioBuff[IOP_BUFF_SIZE * 2] __attribute__((aligned(64))); // offset 0x3080, size 0xC000
    u_int* tagInterDatap; // offset 0xF080, size 0x4
    int videoDecTh; // offset 0xF084, size 0x4
    int defaultTh; // offset 0xF088, size 0x4
    s_char defStack[DEF_STACK_SIZE] __attribute__((aligned(64))); // offset 0xF0C0, size 0x800
    s_char videoDecStack[STACK_SIZE] __attribute__((aligned(64))); // offset 0xF8C0, size 0x4000
    sceGsDBuff db; // offset 0x138C0, size 0x230
} PssCommonWork;
extern PssCommonWork* pss_common_work;

typedef struct _PSS_MESSAGE_TIME {
    // total size: 0x4
    u_short start; // offset 0x0, size 0x2
    u_short end; // offset 0x2, size 0x2
} PSS_MESSAGE_TIME;

typedef struct _PSS_SUBTITLE_CTRL {
    // total size: 0x10
    int msg_start; // offset 0x0, size 0x4
    int msg_no; // offset 0x4, size 0x4
    u_short* msg_bufp; // offset 0x8, size 0x4
    struct _PSS_MESSAGE_TIME* adr_msg_time; // offset 0xC, size 0x4
} PSS_SUBTITLE_CTRL;

extern PSS_SUBTITLE_CTRL pssSubTitleCtrl;

void PssBreakPoint(void);

int WaitSemaPss(void);

int SignalSemaPss(void);

#endif // PSS_COMMON_H

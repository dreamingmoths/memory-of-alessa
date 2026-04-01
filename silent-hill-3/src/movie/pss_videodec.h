#ifndef PSS_VIDEODEC_H
#define PSS_VIDEODEC_H

#include "movie.h"
#include "mpeg/videodec.h"
#include "pss_vobuf.h"

typedef struct
{
    unsigned int *micro[3][2];
} CscVu1;

typedef struct
{ // 0xb8
  // /* 0x00 */ sceMpeg mpeg;
    /* 0x48 */ ViBuf vibuf;
    // /* 0xa8 */ u_int state;
    int state;
    /* 0xac */ int sema;
    /* 0xb0 */ int hid_endimage;
    /* 0xb4 */ int hid_vblank;
    CscVu1 cscvu1;
} VideoDec;

extern sceMpeg sys_mpeg;

extern VideoDec videoDec;
extern VoBuf voBuf;

int videoDecCreate(VideoDec *vd, u_char *mpegWork, int mpegWorkSize, u_long128 *data, u_long128 *tag, int tagSize, TimeStamp *pts, int n_pts);
void videoDecSetDecodeMode(VideoDec *vd, int ni, int np, int nb);
int videoDecSetStream(VideoDec *vd, int strType, int ch, sceMpegCallback cb, void *data);
void videoDecBeginPut(VideoDec *vd, u_char **ptr0, int *len0, u_char **ptr1, int *len1);
void videoDecEndPut(VideoDec *vd, int size);
void videoDecReset(VideoDec *vd);
int videoDecDelete(VideoDec *vd);
void videoDecAbort(VideoDec *vd);
u_int videoDecGetState(VideoDec *vd);
u_int videoDecSetState(VideoDec *vd, u_int state);
int videoDecPutTs(VideoDec *vd, long int pts_val, long int dts_val, u_char *start, int len);
int videoDecInputCount(VideoDec *vd);
int videoDecInputSpaceCount(VideoDec *vd);
int videoDecFlush(VideoDec *vd);
int videoDecIsFlushed(VideoDec *vd);
void videoDecMain(VideoDec *vd);
int decBs0(VideoDec *vd);
int mpegError(sceMpeg *mp, sceMpegCbDataError *cberror, void *anyData);
int mpegNodata(sceMpeg *mp, sceMpegCbData *cbdata, void *anyData);
int mpegStopDMA(sceMpeg *mp, sceMpegCbData *cbdata, void *anyData);
int mpegRestartDMA(sceMpeg *mp, sceMpegCbData *cbdata, void *anyData);
int mpegTS(sceMpeg *mp, sceMpegCbDataTimeStamp *cbts, void *anyData);
static int cpy2area(u_char *pd0, int d0, u_char *pd1, int d1, u_char *ps0, int s0, u_char *ps1, int s1);

#endif

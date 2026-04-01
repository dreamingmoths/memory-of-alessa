#include "pss_videodec.h"

int videoDecCreate(VideoDec *vd, u_char *mpegWork, int mpegWorkSize, u_long128 *data, u_long128 *tag, int tagSize, TimeStamp *pts, int n_pts)
{
    sceMpegCreate(&sys_mpeg, mpegWork, mpegWorkSize);
    sceMpegAddCallback(&sys_mpeg, sceMpegCbError, (sceMpegCallback)mpegError, NULL);
    sceMpegAddCallback(&sys_mpeg, sceMpegCbNodata, mpegNodata, NULL);
    sceMpegAddCallback(&sys_mpeg, sceMpegCbStopDMA, mpegStopDMA, NULL);
    sceMpegAddCallback(&sys_mpeg, sceMpegCbRestartDMA, mpegRestartDMA, NULL);
    sceMpegAddCallback(&sys_mpeg, sceMpegCbTimeStamp, (sceMpegCallback)mpegTS, NULL);

    vd->state = 0;

    viBufCreate(&vd->vibuf, data, tag, tagSize, pts, n_pts);
    cscVu1Init(&vd->cscvu1);

    return 1;
}

int videoDecSetStream(VideoDec *vd, int strType, int ch, sceMpegCallback cb, void *data)
{
    sceMpegAddStrCallback(&sys_mpeg, strType, ch, cb, data);

    return 1;
}

void videoDecBeginPut(VideoDec *vd, u_char **ptr0, int *len0, u_char **ptr1, int *len1)
{
    viBufBeginPut(&vd->vibuf, ptr0, len0, ptr1, len1);
}

void videoDecEndPut(VideoDec *vd, int size)
{
    viBufEndPut(&vd->vibuf, size);
}

int videoDecDelete(VideoDec *vd)
{
    viBufDelete(&vd->vibuf);

    sceMpegDelete(&sys_mpeg);

    return 1;
}

void videoDecAbort(VideoDec *vd)
{
    vd->state = 1;
}

u_int videoDecGetState(VideoDec *vd)
{
    return vd->state;
}

u_int videoDecSetState(VideoDec *vd, u_int state)
{
    u_int old;

    old = vd->state;

    vd->state = state;

    return old;
}

int videoDecPutTs(VideoDec *vd, long int pts_val, long int dts_val, u_char *start, int len)
{
    TimeStamp ts;

    ts.pts = pts_val;
    ts.dts = dts_val;
    ts.pos = start - (u_char *)vd->vibuf.data;
    ts.len = len;

    return viBufPutTs(&videoDec.vibuf, &ts);
}

#ifdef NON_MATCHING
int videoDecFlush(VideoDec *vd)
{
    u_char *pd0;
    u_char *pd1;
    u_char seq_end_code[4] = "\x00\x00\x01\xb7";
    int d0;
    int d1;
    u_char *pd0_unc;
    u_char *pd1_unc;
    int size;

    videoDecBeginPut(vd, &pd0, &d0, &pd1, &d1);

    if (d0 + d1 < 4)
    {
        return 0;
    }

    pd0_unc = (u_char*)UncAddr(pd0);
    pd1_unc = (u_char*)UncAddr(pd1);

    size = cpy2area(pd0_unc, d0, pd1_unc, d1, seq_end_code, 4, NULL, 0);

    videoDecEndPut(&videoDec, size);

    viBufFlush(&vd->vibuf);

    if (vd->state == VD_STATE_NORMAL)
    {
        vd->state = VD_STATE_FLUSH;
    }

    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/movie/pss_videodec", videoDecFlush);
#endif

void videoDecMain(VideoDec* vd) {
    viBufReset(&vd->vibuf);

    voBufReset(&voBuf);

    if (decBs0(vd) < 0) {
        debugPrintf("decBs0() failed\n");
    }

    while(voBuf.count != 0) {
        if (videoDecGetState(vd) == VD_STATE_ABORT) {
            debugPrintf("decBs0() failed\n");
            break;
        }
    }

    videoDecSetState(vd, VD_STATE_END);
}

int decBs0(VideoDec *vd) {
    VoData *voData;
    sceIpuRAW8 *raw8;
    int ret;
    int status = 1;
    sceMpeg *mp = &sys_mpeg;
    int picture_structure;
    extern int csct;

    while (sceMpegIsEnd(&sys_mpeg) == 0) {
        if (videoDecGetState(vd) == VD_STATE_ABORT) {
            status = -1;
            debugPrintf("decode thread: aborted\n");
            break;
        }

        while ((voData = voBufGetData(&voBuf)) == 0) {
            switchThread();
        }
        raw8 = (sceIpuRAW8*) voData->v;

        if (viBufAddDMA(&vd->vibuf) != 1) {
            debugPrintf("viBufAddDMA() failed\n");
            status = -1;
            break;
        }

        WaitSemaPss();
        ret = sceMpegGetPictureRAW8(sys_mpeg, raw8, MAX_WIDTH/16 * MAX_HEIGHT/16);
        SignalSemaPss();

        if (ret < 0) {
            debugPrintf("sceMpegGetPictureRAW8() failed\n");
            status = -1;
            break;
        }

        picture_structure = (int)((sys_mpeg.flags >> 3) & 3);
        if (picture_structure == SCE_MPEG_FRAME) {
            csct = (sys_mpeg.flags & 0x180) ? CSCVU1_PROG_FRAME : CSCVU1_INTER_FRAME;
        } else {
            csct; // @hack?
            debugPrintf("pss_videodec.c:342> assert:(%s)\n", "@576_0x0039C028");
        }

        if (ret < 0) {
            ErrMessage("sceMpegGetPicture() decode error");
        }

        if (sys_mpeg.frameCount == 0) {
            int i;

            for (i = 0; i < N_VOBUF; i++) {
                cscVu1SetTag(
                    voBuf.tagInter[i].v,
                    0,
                    voBuf.data[i].v,
                    sys_mpeg.width,
                    sys_mpeg.height
                );
            }
        }

        voBufIncCount(&voBuf);
        switchThread();
    }

    sceMpegReset(mp);
    return status;
}


int mpegError(sceMpeg *mp, sceMpegCbDataError *cberror, void *anyData)
{
    return 1;
}

int mpegNodata(sceMpeg *mp, sceMpegCbData *cbdata, void *anyData)
{
    SignalSemaPss();
    switchThread();
    WaitSemaPss();

    viBufAddDMA(&videoDec.vibuf);

    return 1;
}

int mpegStopDMA(sceMpeg *mp, sceMpegCbData *cbdata, void *anyData)
{
    viBufStopDMA(&videoDec.vibuf);

    return 1;
}

int mpegRestartDMA(sceMpeg *mp, sceMpegCbData *cbdata, void *anyData)
{
    viBufRestartDMA(&videoDec.vibuf);

    return 1;
}

int mpegTS(sceMpeg *mp, sceMpegCbDataTimeStamp *cbts, void *anyData)
{
    TimeStamp ts;

    viBufGetTs(&videoDec.vibuf, &ts);

    cbts->pts = ts.pts;
    cbts->dts = ts.dts;

    return 1;
}

static int cpy2area(u_char *pd0, int d0, u_char *pd1, int d1, u_char *ps0, int s0, u_char *ps1, int s1)
{
    if (d0 + d1 < s0 + s1)
    {
        return 0;
    }

    if (s0 >= d0)
    {
        memcpy(pd0, ps0, d0);
        memcpy(pd1, ps0 + d0, s0 - d0);
        memcpy(pd1 + s0 - d0, ps1, s1);
    }
    else if (s1 >= d0 - s0)
    {
        memcpy(pd0, ps0, s0);
        memcpy(pd0 + s0, ps1, d0 - s0);
        memcpy(pd1, ps1 + d0 - s0, s1 - (d0 - s0));
    }
    else
    {
        memcpy(pd0, ps0, s0);
        memcpy(pd0 + s0, ps1, s1);
    }

    return s0 + s1;
}


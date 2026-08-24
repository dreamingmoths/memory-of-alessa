#include "sh2_common.h"

#include "sce/eekernel.h"

#include "movie/movie.h"
#include "movie/pss_common.h"
#include "movie/pss_videodec.h"
#include "movie/pss_audiodec.h"
#include "movie/pss_readbuf.h"
#include "movie/pss_read.h"
#include "movie/pss_main.h"

#include "data/fs_structs.h"


extern int intc_gs_changed; // size: 0x4, address: 0x1217FC8
extern int handler_endimage(int); // size: 0x0, address: 0x28A520
extern int intc_vs_changed; // size: 0x4, address: 0x1217FD0
extern int vblankHandler(int); // size: 0x0, address: 0x289DD0
extern int isWithAudio; // size: 0x4, address: 0x37B4F0

extern u_long128 viBufTag[257];
extern VoTag voBufTagInter[5]; // size: 0x140, address: 0x1219180

extern void* _gp; // size: 0x4, address: 0x3CFC70

static int initAll(fsFileIndex* id);
static void termAll();
static void defMain(void* param);
static u_int movie(char *name);
static int readMpeg(VideoDec *vd, ReadBuf *rb, StrFile *file);
static int isAudioOK();
static void usage();

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", pssSystemColdInit);

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", pssSetWorkAddress);

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", pssInit);

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", pssExit);

INCLUDE_RODATA("asm/nonmatchings/movie/pss_main", @470_0x0039BD50);

INCLUDE_RODATA("asm/nonmatchings/movie/pss_main", @471_0x0039BD70);

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", pssSetControlData);

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", pssMain);

// ////////////////////////////////////////////////////////////////
//
// Read MPEG data
//
// return value
//     1: normal end
//     -1: aborted
static int readMpeg(VideoDec* vd, ReadBuf* rb, StrFile* file) {
    u_char* put_ptr; // r29+0x58
    u_char* get_ptr; // r29+0x5C
    int putsize; // r2
    int getsize; // r2
    int count; // r16
    int proceed; // r16
        
    s32 temp_a1;

    if ((pssExecCtrl.isPaused != 0) || ((pssExecCtrl.writerest > 4) && (videoDecGetState(vd) == VD_STATE_NORMAL))) {
        // /////////////////////////////////////////////////
    	//
    	// Read data to the read buffer
    	//
        putsize = readBufBeginPut(rb, &put_ptr);
        if ((pssExecCtrl.readrest > 0) && (putsize >= READ_UNIT_SIZE)) {
            count = strFileRead(put_ptr, READ_UNIT_SIZE);
            if (count < 0) {
                videoDecAbort(&videoDec);
            } else {
                int tmp = readBufEndPut(rb, count);
                if (tmp != count) {
                    printf("readBufEndPut: count=%d, tmp=%d\n", count, tmp);
                    PssBreakPoint();
                }
                pssExecCtrl.readrest -= tmp;
            }
        }
        switchThread();
        getsize = readBufBeginGet(rb, &get_ptr);
        ASSERT_ON_LINE(getsize >= 0, 420);
        if (getsize > 0) {
            proceed = sceMpegDemuxPssRing(&sys_mpeg, get_ptr, getsize, rb, rb->size);
            if ((pssExecCtrl.isStarted != 0) && (proceed == 0)) {
                u_short diff = (*T0_COUNT - pssExecCtrl.proceed_zero_count);
                if (0x64000 < diff) { // @bug: comparing a u_short to something bigger than a u_short
                    printf("sceMpegDemuxPssRing() proceed timeout: %d\n", diff);
                    videoDecAbort(&videoDec);
                    return -1;
                }
            } else  {
                pssExecCtrl.proceed_zero_count = *T0_COUNT;
            }
            {
                int tmp = readBufEndGet(rb, proceed);
                if (tmp != proceed) {
                    printf("readBufEndGet: proceed=%d, tmp=%d\n", proceed, tmp);
                }
                pssExecCtrl.writerest -= tmp;
            }
        }
        proceedAudio();
        if ((pssExecCtrl.isStarted == 0) && (voBufIsFull(&voBuf) != 0) && (isAudioOK() != 0)) {
            if ((pssExecCtrl.status == 2) && (sys_mpeg.frameCount >= pssExecCtrl.stFrame)) {
                pssMpegPlayStart(pssExecCtrl.status);
            } else if ((pssExecCtrl.status == 1) && (sys_mpeg.frameCount >= pssExecCtrl.stFrame)) {
                pssExecCtrl.status = 3;
            }
        }
    }

    if (((pssExecCtrl.writerest < 5) && (videoDecGetState(vd) == 0)) || (videoDecGetState(vd) == 1) || (videoDecGetState(vd) == 3)) {
        return -1;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", pssMpegFinish);

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", pssMpegPlayStart);

// /////////////////////////////////////////////////
//
// Switch to another thread
//
void switchThread()
{
    RotateThreadReadyQueue(DEF_PRIORITY);
}

// /////////////////////////////////////////////////
//
// Check audio
//
static int isAudioOK()
{
    return (isWithAudio)? audioDecIsPreset(&audioDec): 1;
}

// ////////////////////////////////////////////////////////////////
//
// Initialize all modules
//
static int initAll(fsFileIndex* id)
{
    int i; // r5
    int result; // r2
    ThreadParam th_param; // r29+0x80

    // /////////////////////////////
    // 
    //  Create read buffer
    // 
    readBufCreate(pss_common_work->readBufp);

    // /////////////////////////////
    // 
    //  Initialize video decoder
    // 
    sceMpegInit();
    videoDecCreate(&videoDec,
    	pss_common_work->mpegWorkp, 886784/* @todo: SCE_MPEG_BUFFER_SIZE(MAX_WIDTH, MAX_HEIGHT) */,
    	pss_common_work->viBufDatap, viBufTag, VIBUF_SIZE, pss_common_work->timeStamp, VIBUF_TS_SIZE);

    // /////////////////////////////
    // 
    //  Initialize audio decoder
    // 
    audioDecCreate(&audioDec, pss_common_work->audioBuff, sizeof(pss_common_work->audioBuff), IOP_BUFF_SIZE);

    ///////////////////////////////
    // 
    //  Choose stream to be played
    // 
    videoDecSetStream(&videoDec,
	    sceMpegStrM2V, 0, (sceMpegCallback)videoCallback, pss_common_work->readBufp);
    if (isWithAudio) {
        videoDecSetStream(&videoDec,
            sceMpegStrPCM, 0, (sceMpegCallback)pcmCallback, pss_common_work->readBufp);
    }
    for (i = 0; i < N_VOBUF; i++) {
        voBufTagInter[i].v = (u_char*) &pss_common_work->tagInterDatap[i * INTER_TAG_SIZE];
    }

    // /////////////////////////////
    // 
    //  Initialize video output buffer
    // 
    voBufCreate(&voBuf, UncAddr(pss_common_work->voBufDatap), NULL, voBufTagInter, 0, 0, N_VOBUF);

    // /////////////////////////////
    // 
    //  Create 'default' thread
    // 
    th_param.entry = defMain;
    th_param.stack = pss_common_work->defStack;
    th_param.stackSize = DEF_STACK_SIZE;
    th_param.initPriority = DEF_PRIORITY;
    th_param.gpReg = &_gp;
    th_param.option = 0;
    pss_common_work->defaultTh = CreateThread(&th_param);
    StartThread(pss_common_work->defaultTh, NULL);

    // /////////////////////////////
    // 
    //  Create docode thread
    // 
    th_param.entry = videoDecMain;
    th_param.stack = pss_common_work->videoDecStack;
    th_param.stackSize = STACK_SIZE;
    th_param.initPriority = DEF_PRIORITY;
    th_param.gpReg = &_gp;
    th_param.option = 0;
    pss_common_work->videoDecTh = CreateThread(&th_param);
    StartThread(pss_common_work->videoDecTh, &videoDec);
    switchThread();

    // /////////////////////////////
    // 
    //  Open bitstream file
    // 
    while ((result = strFileOpen(id)) == 0) {           /* CD/DVD Streaming */
        printf("Can't open file %s\n", id->index.name); /* CD/DVD Streaming */
    }                                                   /* CD/DVD Streaming */

    return 0;
}

// ////////////////////////////////////////////////////////////////
//
// Terminate all modules
//
static void termAll()
{
    int tmp;

    readBufDelete(pss_common_work->readBufp);
    voBufDelete(&voBuf);

    WaitSemaPss();
    TerminateThread(pss_common_work->videoDecTh);
    DeleteThread(pss_common_work->videoDecTh);
    SignalSemaPss();

    TerminateThread(pss_common_work->defaultTh);
    DeleteThread(pss_common_work->defaultTh);

/*
    DisableDmac(DMAC_GIF);
    RemoveDmacHandler(DMAC_GIF, videoDec.hid_endimage);

    sceGsSyncVCallback(NULL);
*/  
    DisableIntc(0);
    tmp = RemoveIntcHandler(0,videoDec.hid_endimage);
    if ((intc_gs_changed == 0) && (tmp != 0)) {
        EnableIntc(0);
    }
    DisableIntc(2);
    tmp = RemoveIntcHandler(2,videoDec.hid_vblank);
    if ((intc_vs_changed == 0) && (tmp != 0)) {
        EnableIntc(2);
    }

    videoDecDelete(&videoDec);
    audioDecDelete(&audioDec);

    strFileClose();
}

// ////////////////////////////////////////////////////////////////
//
// Main function of default thread
//
static void defMain(void* param)
{
	(void)(param);

    while (1) {
	switchThread();
    }
}

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", pssGetPssStatus);

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", pssGetPssAbortFlag);

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", pssGetMaskSwitch);

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", pssSetMaskSwitch);

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", pssCheckMovieCancel);

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", pssSetSubTitleData);

void ErrMessage(char* message) {
    printf("[ Error ] %s\n", message);
}

// ////////////////////////////////////////////////////////////////
//
//  Send audio data to IOP
//
void proceedAudio()
{
    audioDecSendToIOP(&audioDec);
}

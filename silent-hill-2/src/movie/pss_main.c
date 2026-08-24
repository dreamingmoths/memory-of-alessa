#include "sh2_common.h"

#include "sce/eekernel.h"

#include "movie/pss_videodec.h"
#include "movie/pss_audiodec.h"
#include "movie/pss_readbuf.h"
#include "movie/movie.h"

extern PssCommonWork* pss_common_work;

extern int intc_gs_changed; // size: 0x4, address: 0x1217FC8
extern int handler_endimage(int); // size: 0x0, address: 0x28A520
extern int intc_vs_changed; // size: 0x4, address: 0x1217FD0
extern int vblankHandler(int); // size: 0x0, address: 0x289DD0

static void initAll(char *bsfilename);
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

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", pssSetControlData);

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", pssMain);

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", readMpeg);

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", pssMpegFinish);

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", pssMpegPlayStart);

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", switchThread);

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", isAudioOK);

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", initAll);

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

INCLUDE_ASM("asm/nonmatchings/movie/pss_main", ErrMessage);

// ////////////////////////////////////////////////////////////////
//
//  Send audio data to IOP
//
void proceedAudio()
{
    audioDecSendToIOP(&audioDec);
}

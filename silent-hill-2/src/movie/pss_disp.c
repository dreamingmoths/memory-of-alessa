#include "sh2_common.h"

#include "sce/eeregs.h"
#include "sce/libdma.h"

#include "Font/font.h"

#include "movie/movie.h"
#include "movie/pss_common.h"
#include "movie/pss_disp.h"
#include "movie/pss_vobuf.h"
#include "movie/pss_videodec.h"

static void MovePicture(u_int* tags, u_short fbp);

static void SetDrawFBP(u_int* tags, u_short fbp);

static void SetUndoXYOFFSET(u_int* tags);

extern volatile int isCountVblank;
extern volatile int vblankCount;
extern volatile int isFrameEnd;
extern volatile int isUp;
extern volatile int handler_error;

extern int frd;
extern int csct;
extern u_int Movpictag[256]; // size: 0x400, address: 0x1217BC0

INCLUDE_ASM("asm/nonmatchings/movie/pss_disp", pssInitDisplay);

INCLUDE_ASM("asm/nonmatchings/movie/pss_disp", pssDispClear);

// ///////////////////////////////////////////////////////////////////
//
// Clear finish bit
//
void clearFinish()
{
    *GS_CSR |= GS_CSR_FINISH_M;
}



// /////////////////////////////////////////////////////////////////////
//
// vblank handler
//
int vblankHandler(void) {
    sceDmaChan* dmaGif_loadimage; // r16
    sceDmaChan* dmaGif2; // r17
    VoTag* tag; // r18
    void* adr; // r17


    dmaGif_loadimage = sceDmaGetChan(SCE_DMA_VIF1);
    dmaGif2 = sceDmaGetChan(SCE_DMA_GIF);
    isUp = ((*GS_CSR) >> 13) & 1; // odd == 1, even == 0
    if ((isCountVblank != 0) && (pssExecCtrl.status == 4)) {
        vblankCount++;
        handler_error = sceGsSyncPath(1, 0);
        if (handler_error == 0) {
            VoTag* tag = voBufGetTag(&voBuf);
            if (tag == NULL) {
                frd++;
                ExitHandler();
                return 0;
            }
            sceGsSetHalfOffset((isUp&1)?(sceGsDrawEnv1*)UncAddr(&pss_common_work->db.draw1)
    			 :(sceGsDrawEnv1*)UncAddr(&pss_common_work->db.draw0),
    			 2048, 2048, isUp^0x1);
            if ((isUp != 0) && (tag->status == 2)) {
                sceGsSwapDBuff(pss_common_work->db, 0);
                SetDrawFBP(Movpictag, 256);
                iFlushCache(0);
                sceDmaSend(dmaGif2, Movpictag);
        		cscVu1Xyz2offset(
        		    &videoDec.cscvu1,
        		    csct,
        		    false,
        		    0x7000, // @todo: what's this?
        		    0x7000
        		);
                cscVu1Kick(tag->v);
                tag->status = 1;
                sceGsSyncPath(0, 0);
                SetDrawFBP(Movpictag, pss_common_work->db.disp[1].dispfb.FBP - 8);
                iFlushCache(0);
                sceDmaSend(dmaGif2, Movpictag);
                sceGsSyncPath(0, 0);
                MovePicture(Movpictag, 256);
                sceDmaSend(dmaGif2, Movpictag);
            } else if ((isUp == 0) && (tag->status == 1)) {
                sceGsSwapDBuff(pss_common_work->db, 1);
                SetDrawFBP(Movpictag, 320);
                iFlushCache(0);
                sceDmaSend(dmaGif2, Movpictag);
                cscVu1Xyz2offset(
        		    &videoDec.cscvu1,
        		    csct,
        		    true,
        		    0x7000, // @todo: what's this?
        		    0x7000
        		);
                cscVu1Kick(tag->v);
                tag->status = 0;
                isFrameEnd = 1;
                sceGsSyncPath(0, 0);
                SetDrawFBP(Movpictag, pss_common_work->db.disp[0].dispfb.FBP - 8);
                iFlushCache(0);
                sceDmaSend(dmaGif2, Movpictag);
                sceGsSyncPath(0, 0);
                MovePicture(Movpictag, 320);
                sceDmaSend(dmaGif2, Movpictag);
            }
            sceGsSyncPath(0, 0);
            if (isUp & 1) {
                SetUndoXYOFFSET(Movpictag);
                sceDmaSend(dmaGif2, Movpictag);
                sceGsSyncPath(0, 0);
            }
            spkResetOT();
            if (pssDrawSubTitle() != 0) {
                adr = fontTexLoad(0x3000, 0x3600);
                iFlushCache(0);
                sceDmaSend(dmaGif_loadimage, adr);
                sceGsSyncPath(0, 0);
                adr = fontFlushNoSPR();
                iFlushCache(0);
                sceDmaSend(dmaGif_loadimage, (u_int*) adr);
                sceDmaSend(dmaGif_loadimage, fontAfterEnv());
                sceGsSyncPath(0, 0);
            }
        }
    } else if (sys_mpeg.frameCount < pssExecCtrl.stFrame) {
        vblankCount++;
        handler_error = sceGsSyncPath(1, 0);
        if (handler_error == 0) {
            VoTag* tag = voBufGetTag(&voBuf);
            if (tag == NULL) {
                frd++;
                ExitHandler();
                return 0;
            }
            if ((isUp != 0) && (tag->status == 2)) {
                tag->status = 1;
            } else if ((isUp == 0) && (tag->status == 1)) {
                tag->status = 0;
                isFrameEnd = 1;
            }
        }
        if (isFrameEnd != 0) {
            voBufDecCount(&voBuf);
            isFrameEnd = 0;
        }

    }

    ExitHandler();
    return 0;
}


int pssDrawSubTitle(void) {
    if (pssSubTitleCtrl.adr_msg_time != NULL) {
        if (pssSubTitleCtrl.adr_msg_time[pssSubTitleCtrl.msg_no]. end < pssExecCtrl.framecnt) {
            fontClear();
            pssSubTitleCtrl.msg_no++;
        }
        if (pssSubTitleCtrl.adr_msg_time[pssSubTitleCtrl.msg_no]. start < pssExecCtrl.framecnt) {
            fontMessageNum(pssSubTitleCtrl.msg_bufp, pssSubTitleCtrl.msg_start + pssSubTitleCtrl.msg_no);
            return 1;
        }
    }
    return 0;
}

// ///////////////////////////////////////////////////////////////
// 
//  Handler to check the end of image transfer
// 
int handler_endimage(int val)
{
    clearFinish();

    if (isFrameEnd) {
        voBufDecCount(&voBuf);
        isFrameEnd = 0;
        pssExecCtrl.framecnt++;
    }
    ExitHandler();
    return 0;
}

// ///////////////////////////////////////////////////////////////////
// 
//  Wait until even/odd field
//  Start to count vblank
// 
void startDisplay(int waitEven)
{
    // wait untill even field
    while (sceGsSyncV(0) == waitEven)
    	;

    frd = 0;
    isCountVblank = 1;
    vblankCount = 0;
}

// ///////////////////////////////////////////////////////////////////
// 
//  Stop to count vblank
// 
void endDisplay()
{
    sceGsSyncPath(0, 0);
    isCountVblank =  0;
    frd = 0;
}



INCLUDE_ASM("asm/nonmatchings/movie/pss_disp", MovePicture);

INCLUDE_ASM("asm/nonmatchings/movie/pss_disp", SetDrawFBP);

INCLUDE_ASM("asm/nonmatchings/movie/pss_disp", SetUndoXYOFFSET);

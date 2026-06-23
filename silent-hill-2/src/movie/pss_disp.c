#include "sh2_common.h"
#include "eeregs.h"
#include "movie/pss_disp.h"
#include "movie/pss_vobuf.h"
#include "movie/pss_videodec.h"

extern volatile int isCountVblank;
extern volatile int vblankCount;
extern volatile int isFrameEnd;
extern volatile int isUp;
extern volatile int handler_error;

extern int frd;

INCLUDE_ASM("asm/nonmatchings/movie/pss_disp", pssInitDisplay);

INCLUDE_ASM("asm/nonmatchings/movie/pss_disp", pssDispClear);

INCLUDE_ASM("asm/nonmatchings/movie/pss_disp", clearFinish);



// /////////////////////////////////////////////////////////////////////
//
// vblank handler
//

INCLUDE_ASM("asm/nonmatchings/movie/pss_disp", vblankHandler);

INCLUDE_ASM("asm/nonmatchings/movie/pss_disp", pssDrawSubTitle);

// ///////////////////////////////////////////////////////////////
// 
//  Handler to check the end of image transfer
// 

INCLUDE_ASM("asm/nonmatchings/movie/pss_disp", handler_endimage);

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

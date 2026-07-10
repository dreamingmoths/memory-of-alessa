#include "common.h"
#include "eeregs.h"
#include "libgraph.h"
#include "gs.h"

/* sets vif0 chcr */
INCLUDE_ASM("asm/nonmatchings/sh3_init", func_0012BBC0);

void sceDmaReset_(void) {
    sceDmaReset(1);
}

/* 0012BC70 */ void sh3_initGS(void) {
    sceGsResetPath();
    sceGsResetGraph(0, 1, 2, 0);
    *GS_IMR = ~GS_IMR_SIGMSK_M;
    *GS_SIGLBLID = 0;
    *GS_CSR = GS_CSR_VSINT_O;
    *GIF_MODE = GIF_MODE_IMT_M;
    *GS_PMODE =  SCE_GS_SET_PMODE(0, 1, 0, 1, 1, 0, 0);
    *GS_SMODE2 = GS_SMODE2_DPMS_O;
    *GS_DISPFB2 = SCE_GS_SET_DISPFB(0, 512 / 64, SCE_GS_PSMCT24, 0, 32);
    *GS_DISPLAY2 = SCE_GS_SET_DISPLAY(16, 0, 4, 0, 4 * SCREEN_WIDTH - 1, 895);
}

/* 0012BD30 */ void sh3_initVU(void) {
    sceVpu0Reset();
    *VIF1_MARK = 0;
    *VIF1_ERR = 0 /* no interrupt */ | VIF1_ERR_ME0_M | VIF1_ERR_ME1_M;
}

/* 0012BD60 */ void sh3_initTimers(void) {
    /* hcount timer setting */
    *T0_MODE = T_MODE_CLKS_M | T_MODE_CUE_M;
    *T1_MODE = T_MODE_CLKS_M | T_MODE_CUE_M;
}

/* maybe: systemColdInit? */
void func_0012BD80(void) {
  sceDmaReset_();
  sh3_initGS();
  sh3_initVU();
  sh3_initTimers();
}

void func_0012BDC0(void) {
    sh3_initVU();
    func_0012BBC0();
}

void sh3_initFilesys(void) {
    int result;

    func_0012BF40();
    iopLoadMod("iop_modules/sio2man.irx", 0, NULL);
    iopLoadMod("iop_modules/sio2d.irx", 0, NULL);
    iopLoadMod("iop_modules/mcman.irx", 0, NULL);
    iopLoadMod("iop_modules/mcserv.irx", 0, NULL);
    iopLoadMod("iop_modules/dbcman.irx", 0, NULL);
    iopLoadMod("iop_modules/ds2u.irx", 0, NULL);
    iopLoadMod("iop_modules/ds2u.irx", 0, NULL); // @bug loads this module twice?
    iopLoadMod("iop_modules/libsd.irx", 0, NULL);
    iopLoadMod("iop_modules/sdrdrv.irx", 0, NULL);

    if (func_001E4E20()) { // only called by this function...
        result = iopLoadMod("iop_sound/cri_adxi.irx", 11, "spucore=1");
    } else {
        iopLoadMod("iop_sound/libsmf2.irx", 0, NULL);
        iopLoadMod("iop_sound/sd_call.irx", 0, NULL);
        result = iopLoadMod("iop_sound/cri_adxi.irx", 11, "spucore=1");
    }

    func_00151130(result, 0);
}

INCLUDE_ASM("asm/nonmatchings/sh3_init", func_0012BF40);

INCLUDE_ASM("asm/nonmatchings/sh3_init", func_0012C750);

/* inits scf and some data */
INCLUDE_ASM("asm/nonmatchings/sh3_init", func_0012C980);

INCLUDE_ASM("asm/nonmatchings/sh3_init", func_0012C9B0);

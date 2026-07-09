#include "sh2gfw_all_sysinit.h"

#include "eeregs.h"
#include "libgraph.h"
#include "libvu0.h"

#include "Chacter_Draw/vifot/sh_kt_vif0.h"
#include "Chacter_Draw/vifot/sh_kt_vif1.h"
#include "Chacter_Draw/vifot/sh_kt_vif0pkbuf.h"
#include "Chacter_Draw/vifot/sh_kt_vif1pkbuf.h"
#include "Chacter_Draw/sh2gfw_CharacterOT.h"

#include "Collision/cl_main.h"
#include "Collision/kari_atari_allinit.h"

#include "DBG/shDBG_fontHandle.h"
#include "DBG/sh2gfw_SyncDBG.h"

#include "Event/event.h"

#include "Effect/ef_common.h"

// #include "Fog/fog.h"
#include "Fog/sh2gfw_fogtest_main.h"

#include "Font/font.h"

#include "FilesList/fileslist_bg.h"

#include "GFW/sh2_DrawEnvData.h"
#include "GFW/sh2gfw_read_process.h"
#include "GFW/sh2gfw_blockman.h"
#include "GFW/sh2gfw_2d_filters.h"
#include "GFW/gfw_test/sh2gfw_shcamtest.h"

#include "sh2shd/sh2shd_shadow_model.h"

#include "LoadBg/loadbg_camdata.h"
#include "LoadBg/loadbg_1x1.h"

int Vcallback_test(int ca) {
    mct.ui32[0]++;
    mct.ui32[2]++;
    return ca;
}

void init_PS2(void) {
    
    sceGsResetPath();
    sceGsResetGraph(0, 1, 2, 0);
    
    sceVpu0Reset();
    
    
    *T0_MODE = 0x83;
    *T1_MODE = 0x83;
    
    mct.ul128 = 0;
    
    
    
    *GS_SIGLBLID = 0;
    
    
    
    sceGsPutIMR(~GS_IMR_SIGMSK_M);
    
    *GS_CSR = 3;
    
    *VIF1_MARK = 0;
    *VIF1_ERR = 6;
    
    *GIF_MODE = 4;






    
}

void step_init_ONE(void) {
    
    loadBgTEX_Replace(0, 0, NULL, 0);    
    loadBgTEX_Replace(1, 0, NULL, 0);
    loadBgMAP_AllClear();
    
    
    
    
    init_GSandVU();
    
    
    ktVif0Init();
    ktVif1Init();
    
    
    sh2_ktVif1kBufInit();
    
    
    sh2_ktVif0PkBufInit();
    
    
    sh2gfw_AllInit_CharacterOT();
    
    
    
    
    
    shDBG_InitFontEnv();
    
    
    sh2gfw_init_shcamera();
    
    sh2shd_init_shadow();
    
    
    fontClear();
    
    sh2gfw_test_MakeNoise();
    
    
    HH_MemoryManager_MemoryBlock_All_Allocate();
    
    
    HH_Effect_Object_Texture_AlwaysTexture_Initialize();
    
    
    
    
    fjInitAll();
    
    
    
    
    shLensFlareInit();

}


void step_init_STAGE(void) {
    struct FilesBgBlock* bgfiles;






    
    init_Env_ctl();
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    fogInit();
    
    
    
    sh2gfw_init_fogTexture();
    
    
    
    
    
    EFCTInit();
    
    
    
    
    
    
    
    HH_Effect_Object_Texture_DesignateEntryLevel_Initialize(2);
    
    
    
    
    
    
    
    
    
    
    
    sh2gfw_process_AreaDATA(stage->glb_crd << 0x10, Area_Data_Man);
    
    
    
    
    
    
    
    
    
    
    
    bgfiles = FilesGetBgBlock((enum STAGE_ID) stage->glb_crd, 0);
    if (bgfiles != NULL) {
        loadBgCAM_LoadData(0, bgfiles->cam, stage->glb_crd << 0x10);
    }

}

void map_DATA_LOAD(int arg0) {
    int i; // r16
    int mapid; // r16
    void* trfile; // r17

    
    
    loadBgTEX_Replace(1, 0, NULL, 0);
    loadBgMAP_AllClear();
    
    
    for (i = 0; i < 4; i++) sh2gfw_init_zeroQ_BMAN(&(&b_man)[i]);
    
    
    sh2gfw_AllClear_TrMAN();
    
    
    
    
    clAllInitCollisionData();
    
    kari_init_colidata();
    
    
    sh2gfw_util_zeroq((union Q_WORDDATA*)&sh2_TR_MAN, 0x25);
    sh2gfw_Init_AllVertCounter();
    
    
    
    
    
    
    trfile = loadBg1x1_GetTrTexFile();
    mapid = loadBg1x1_GetIdForDrawEnv();
    Set_DrawEnvData(mapid, 1);
    sh2gfw_LoadSet_SemiTransTEX(mapid, trfile);

}

/* static */ int init_Env_ctl(void) {
    return;
}

INCLUDE_ASM("asm/nonmatchings/sh2gfw_all_sysinit", init_GSandVU); // I will leave this for now, I am tired of moving structs

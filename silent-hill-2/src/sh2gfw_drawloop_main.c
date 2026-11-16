#include "sh2_common.h"

#include "sce/eeregs.h"

#include "sh2gfw_drawloop_main.h"

#include "GFW/sh2_GsAllEnv.h"
#include "GFW/gfw_test/sh2gfw_shcamtest.h"
#include "GFW/sh2_DrawEnvData.h"
#include "GFW/sh2gfw_LightSet.h"
#include "GFW/sh2gfw_2d_filters.h"
#include "GFW/sh2_shadow_main.h"
#include "GFW/sh2gfw_GSCTL_man.h"

#include "Multi_thr/intc/syncv.h"

#include "Chacter_Draw/sh2gfw_Draw_Character.h"
#include "Effect/ef_common.h"

#include "Effect2/hh_class_object_execute.h"
#include "Effect2/hh_effect_object_texture.h"

#include "Chacter_Draw/sh2_JmsSpot_Man.h"
#include "DBG/sh2gfw_SyncDBG.h"

#include "Font/fj_man.h"
#include "view/camera_dat.h"

#include "Event/event.h"

static void Exec_PreDraw_OVfunc(void);
static void Noise_and_FontDraw(int loopmode);
static void GSFilterExec4NextLoop(void);
static void Calc_Set_Matrix(void);
static void gs_loppstart_init(void);
static void kari_setdmatag_and_draw(void);
static void Draw_Character_And_Shadow(void);
static void Spack_All_Draw(void);
static int FOG_ROOM(void);
static int DrawSpecialPolyforDemo(void);
static int Check_DrawOrder(void);

void all_Frame_Buffer_Clear(void) {
    Q_WORDDATA* kick;
    sh2gfw_init_GSPACKMAN(&GSCTL_man);
    sh2gfw_RotateTBuff(&shGs_AllEnv);
    sh2gfw_setREF_gsctl(shGs_AllEnv.DefaultEnv);
    sh2gfw_InclimentLoopCounter(&shGs_AllEnv);
    
    sh2gfw_RotateTBuff(&shGs_AllEnv);
    sh2gfw_setREF_gsctl(shGs_AllEnv.DefaultEnv);
    sh2gfw_InclimentLoopCounter(&shGs_AllEnv);
    
    sh2gfw_RotateTBuff(&shGs_AllEnv);
    sh2gfw_setREF_gsctl(shGs_AllEnv.DefaultEnv);
    
    
    
    kick = sh2gfw_setEND_gsctl();
    d1cSend(kick);
    
    d1sSync(0, -1);
    
    shDBG_font_init(); sh2gfw_init_Perf();

}

UNMIGRATED(Q_WORDDATA mct); // size: 0x10, address: 0x2ADB80
UNMIGRATED(u_long res);
UNMIGRATED(u_long res2);

#line 139
void DrawLopp_Pre(void) {
    
    *T0_COUNT = 0;
    mct.ui32[0] = 0;
    
    
    
    
    gs_loppstart_init();
    
    
    
    sh2gfw_init_TexTrans_Manage_Table();
    
    
    
    d2tscClearSlots();
    
    
    
    
    sh2gfw_set_LoopDrawEnv(&shGs_AllEnv);
    
    
    
    
    spkResetOT();
    
    
    
    
    sh2gfw_Init_spkTexManage();
    
    
    
    
    shDBG_font_init(); sh2gfw_init_Perf();
    
    
    
    
    mfontClear();
    

    sh2shd_reset_shadow();
}

void kari_drawloop_main_2dSYNC(void) {
    
    
    
    
    
    
    
    
    fjFontDrawExecVif1();
    
    
    GSFilterExec4NextLoop();
    
    
    d2sSync(0, -1);
    d1sSync(0, -1);
}

void draw_main_3dSYNC(void) {
    
    
    
    GSFilterExec4NextLoop();
    
    
    
    
    
    
    
    d2sSync(0, -1);
    d1sSync(0, -1);
    
    res = *T0_COUNT;
    kari_DBG_print_junbi(&res, &res2);












}

#line 252
void DrawLopp_Post(void) {
    /* 
    
    there's missing code in this line number gap
    confirmed in a different prototype:
    */
    #ifdef NEVER
    int enable = dbSwitchDispEnable(-1);
    
    if (enable || dbFlag(16))
        shDBG_font_PrintDrawAll(); // not in this prototype
    #endif
    
    
    
    d2sSync(0, -1);
    d1sSync(0, -1);




    
    if (mct.ui32[0] == 0) {
    
        
        shSyncVStart(0);
        shSyncVStart(0);
    
    
    
    
    } else {
    
        
        
        shSyncVStart(0);
    
    
    
    
    
    
    }
    mct.ui32[3]++;
    sh2gfw_InclimentLoopCounter(&shGs_AllEnv);
    
    
    
    
    
    
    
    mct.ui32[1] = mct.ui32[0];
}

u_int Get_FrameRate(void) {
    return mct.ui32[1];
}

static void Exec_PreDraw_OVfunc(void) {
    if ((stage != NULL) && (stage->gfw_func != NULL) && (stage->gfw_func->PreDraw != NULL)) {            
        stage->gfw_func->PreDraw();            
    }    
}

void draw_main(void) {
    sh2gfw_Store_Perf2(*T0_COUNT, DRAW_MAIN_PERF_MD);

    sh2gfw_test_shcamera_main();
    Exec_PreDraw_OVfunc();

    *T1_COUNT = 0;

    Calc_Set_Matrix();
    sh2gfw_Set_JmsSpot_OnOrOff();
    Programed_Light_Set();
    
    kari_setdmatag_and_draw();

    Draw_Character_And_Shadow();

    fjMoveEffect();
    HH_Effect_Object_SPK_Texture_Post();
    Spack_All_Draw();

    Exec_PostDraw_OVfunc();

    if (!Check_Filter_Soft())
        Noise_and_FontDraw(0);

    res2 = *T1_COUNT;
}

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", Noise_and_FontDraw);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", GSFilterExec4NextLoop);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", Calc_Set_Matrix);

static void gs_loppstart_init(void) {
    Q_WORDDATA* kick;
    
    sh2gfw_init_GSPACKMAN(&GSCTL_man);
    
    sh2gfw_RotateTBuff(&shGs_AllEnv);
    sh2gfw_setREF_gsctl(shGs_AllEnv.DefaultEnv);
    
    
    kick = sh2gfw_setEND_gsctl();
    d1cSend(kick);
}

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", kari_setdmatag_and_draw);

void Draw_Character_And_Shadow(void) {
    int count = *T0_COUNT;

    if (Check_DrawOrder()) {
        sh2gfw_Exec_AnimeAndCollision();

        sh2gfw_Exec_Character_Draw(cam0.world_screen, true);

        HH_Effect_Object_Texture_TransportPriority_Initialize();
        HH_Effect_Object_Texture_Send();
        HH_Class_Object_Execute();

        EFCTDoTask();

        HH_Effect_Object_Texture_Sync();
        HH_Class_Object_Packet_Kick();

        EFCTKickPacket();

        HH_Effect_Object_Texture_Finish();

        sh2gfw_test_MakeNoise();
        
        sh2gfw_ShadowControl_Main();
    } else {
        sh2gfw_Exec_AnimeAndCollision();
        sh2gfw_Exec_Character_Draw_ShadowOnly();
    
        if (sh2gfw_Get_NightOrDay())
            sh2gfw_ShadowControl_Main();
    
        sh2gfw_Exec_Character_Draw(cam0.world_screen, false);

        HH_Effect_Object_Texture_TransportPriority_Initialize();
        HH_Effect_Object_Texture_Send();
        HH_Class_Object_Execute();

        EFCTDoTask();
        
        HH_Effect_Object_Texture_Sync();
        HH_Class_Object_Packet_Kick();
        
        EFCTKickPacket();
        
        HH_Effect_Object_Texture_Finish();
        
        sh2gfw_test_MakeNoise();
    }
}

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", Spack_All_Draw);

static int FOG_ROOM(void) {
    int* mp;

    mp = Get_NowMapId();
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    switch (*mp) {
        case 0x50001:
        case 0x90048:
        case 0xB00B9:
        case 0xB00BD:
        case 0xB00C1:
        case 0xC0029:
        case 0xC0047:
        case 0xC005B:
        case 0xD0035:
        case 0xD0049:
        case 0xE0005:
            return 1;
    }
    
    
    
    return 0;
}

static int DrawSpecialPolyforDemo(void) {
    
    if ((stage != NULL) && (stage->gfw_func != NULL) && (stage->gfw_func->SpecDraw != NULL)) {
        stage->gfw_func->SpecDraw();
        return 1;        
    }
    
    return 0;

}

static int Check_DrawOrder(void) {
    int* mp;
    if (DramaDemoNumber()) {
        
        return 1;
    }
   
    mp = Get_NowMapId();
    
    switch (*mp) {        
        case 0x90016:
        case 0xA007D:
            return 0;
    }

    return 1;

}

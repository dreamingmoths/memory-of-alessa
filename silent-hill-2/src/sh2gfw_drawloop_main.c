#include "sh2_common.h"

#include "sce/eeregs.h"

#include "sh2gfw_drawloop_main.h"

#include "GFW/sh2_GsAllEnv.h"
#include "GFW/gfw_test/sh2gfw_shcamtest.h"
#include "GFW/sh2gfw_LightSet.h"
#include "GFW/sh2gfw_2d_filters.h"

#include "Multi_thr/intc/syncv.h"

#include "Effect2/hh_effect_object_texture.h"
#include "Chacter_Draw/sh2_JmsSpot_Man.h"
#include "DBG/sh2gfw_SyncDBG.h"
#include "Font/fj_man.h"

static void Calc_Set_Matrix(void);
static void Spack_All_Draw(void);
static void kari_setdmatag_and_draw(void);
static void Exec_PreDraw_OVfunc(void);
static void Draw_Character_And_Shadow(void);
static void Noise_and_FontDraw(int loopmode);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", all_Frame_Buffer_Clear);

UNMIGRATED(Q_WORDDATA mct); // size: 0x10, address: 0x2ADB80
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


INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", kari_drawloop_main_2dSYNC);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", draw_main_3dSYNC);

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

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", Get_FrameRate);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", Exec_PreDraw_OVfunc);

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

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", gs_loppstart_init);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", kari_setdmatag_and_draw);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", Draw_Character_And_Shadow);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", Spack_All_Draw);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", FOG_ROOM);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", DrawSpecialPolyforDemo);

INCLUDE_ASM("asm/nonmatchings/sh2gfw_drawloop_main", Check_DrawOrder);

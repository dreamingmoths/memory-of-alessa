#include "sh2_common.h"
#include "GFW/sh2_DrawEnvData.h"
#include "view/vb_main.h"
#include "view/vw_main.h"
#include "Event/stg_name.h"

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_viewclip_block);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_ClipDraw_BG);

static void sh2gfw_get_blockORIGIN(float (* bbox)[4], float* origin){
    int ix; // r16
    int iz; // r4
    int tmp[4]; // r29+0x40
    
    sceVu0ScaleVector(origin, origin, 0.0f);
    for (ix = 0; ix < 4; ix++) {
        sceVu0AddVector(origin, origin, bbox[ix]);
    }
    
    sceVu0ScaleVector(origin, origin, 0.25f);
    sceVu0FTOI0Vector(tmp, origin);

    ix = tmp[0] / 20000;    
    iz = tmp[2] / 20000;

    
    
    if (tmp[0] < 0) ix--;
    if (tmp[2] < 0) iz--;
    
    origin[0] = 20000.0f * ix;
    origin[1] = 0.0f;
    origin[2] = 20000.0f * iz;
    origin[3] = 1.0f;

}

int sh2gfw_Get_CamTilePos(float* origin) {
    int ssx, ssz;
    float svt[4]; // r29+0x20
    vwGetViewPosition(svt);
    sceVu0SubVector(svt, svt, origin);

    ssz = svt[2] / 2500.0f;
    ssx = svt[0] / 2500.0f;
    return ssx + (ssz * 8);
}

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_get_ViewRecTangle);

extern /* static */ float inclip;
void sh2gfw_get_viewTriangle(sceVu0FMATRIX view_triangle) {
    sceVu0FMATRIX work; // r29+0x60
    int i; // r17
    float z;

    
    sceVu0UnitMatrix(work);
    sceVu0RotMatrixY(work, work, Env_ctl.camera_rot[1]);
    
    if (RoomName(0, 0.0f, 0.0f) == 3 && DramaDemoNumber() == 0) {
       // some special logic for the first cutscene?
        z = (512.0f * (Env_ctl.camera_parms2[2] - 2000.0f)) / VbScreenInfo.scr_z;
    } else {
        z = (512.0f * Env_ctl.camera_parms2[2]) / VbScreenInfo.scr_z;
    }
    
    
    Env_ctl.camera_parms[2] = VbScreenInfo.scr_z;
    
    for (i = 0; i < 3; i++) {
        sceVu0ScaleVector(view_triangle[i], view_triangle[i], 0.0f);
    }
    
    view_triangle[1][0] = 0.5f * z * inclip;
    view_triangle[1][2] = Env_ctl.camera_parms2[2];
    view_triangle[2][0] = -0.5f * z * inclip;
    view_triangle[2][2] = Env_ctl.camera_parms2[2];
    
    for (i = 0; i < 3; i++) {
        sceVu0ApplyMatrix(view_triangle[i], work, view_triangle[i]);
        sceVu0AddVector(view_triangle[i], view_triangle[i], Env_ctl.camera_p);
        view_triangle[i][1] = 0.0f;
    }
}

void sh2gfw_init_vctagbuf(void* vc) {
    Q_WORDDATA* VcBuf = vc;
    Q_WORDDATA cleardata = { 0x10101010, 0x10101010, 0x10101010, 0x10101010 };

    
    VcBuf[0] = cleardata;
    VcBuf[1] = cleardata;
    VcBuf[2] = cleardata;
    VcBuf[3] = cleardata;
}


INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_make_tagclipdata);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2_ClipHitCheckSquare);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", kari_set_vu0cal);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_setVCTAG_DrawSys);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_set_objclip_matrix);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_Set_DispOnOffObj);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_Init_DispOnOffObj);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_FastSet_DispOnOffObj);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_Get_ChrClip_FLG);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_Check_ChrClip_FLG);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_Check_ClipOKChar);

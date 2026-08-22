#include "sh2_common.h"
#include "sce/libvu0.h"
#include "GFW/sh2_DrawEnvData.h"
#include "view/vb_main.h"
#include "view/vw_main.h"
#include "Event/stg_name.h"
#include "GFW/sh2gfw_blockman.h"
#include "GFW/sh2gfw_viewclip.h"
#include "vec.h"

static void sh2gfw_ClipDraw_BG(sh2gfw_BLOCK_MAN* pB_man, sceVu0FMATRIX bbox, sceVu0FMATRIX view_triangle,  Q_WORDDATA** qwd_data);
static void sh2gfw_get_blockORIGIN(sceVu0FMATRIX bbox, float* origin);
static int sh2gfw_Get_CamTilePos(float* origin);
static void sh2gfw_get_ViewRecTangle(float* origin, sceVu0FMATRIX view_triangle, int* view_rect, int view_tile);
static void sh2gfw_get_viewTriangle(sceVu0FMATRIX view_triangle);
static void sh2gfw_init_vctagbuf(void* vc);
static void sh2gfw_make_tagclipdata(float* origin, sceVu0FMATRIX view_triangle, int* view_rect, sh2gfw_BLOCK_MAN* pBM);
static int sh2_ClipHitCheckSquare(sceVu0FMATRIX mat, float* box, float* view_triangle);
static void kari_set_vu0cal(void);
static void sh2gfw_setVCTAG_DrawSys(sh2gfw_BLOCK_MAN* pB_man);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_viewclip_block);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_ClipDraw_BG);

static void sh2gfw_get_blockORIGIN(sceVu0FMATRIX bbox, float* origin) {
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

extern Q_WORDDATA cleardata_002AE090;
void sh2gfw_init_vctagbuf(void* vc) {
    Q_WORDDATA* VcBuf = vc;
    Q_WORDDATA cleardata = cleardata_002AE090; /* = { 0x10101010, 0x10101010, 0x10101010, 0x10101010 } */;

    
    VcBuf[0] = cleardata;
    VcBuf[1] = cleardata;
    VcBuf[2] = cleardata;
    VcBuf[3] = cleardata;
}


void sh2gfw_make_tagclipdata(sceVu0FVECTOR origin, sceVu0FMATRIX view_triangle, sceVu0IVECTOR view_rect, sh2gfw_BLOCK_MAN* pBM) {
    /* v0 */ int stx; /* v0 */ int enx; /* v0 */ int stz; /* v0 */ int enz; /* s0 */ int ix; /* v0 */ int iz; /* v0 */ int index;
    sceVu0FMATRIX rect; // r29+0xF0
    /* s1 */ u_char* tagbuffer;
    /* v0 */ int* mp; /* v0 */ int clip; /* v0 */ int ssx; /* s2 */ int ssz; sceVu0FVECTOR svt; // r29+0x130
    
    sceVu0IVECTOR vrect; // @todo this is not present in the dwarf, temp required for match

    vrect[0] = view_rect[0];
    vrect[1] = view_rect[1];
    vrect[2] = view_rect[2];
    vrect[3] = view_rect[3];
    
    stx = vrect[0];
    enx = vrect[1];
    stz = vrect[2];
    enz = vrect[3];

    mp = Get_NowMapId();
    
    stx = view_rect[0];
    enx = view_rect[1];
    
    stz = view_rect[2];
    enz = view_rect[3];
    
    
    if (stx >= 8) stx = 7;
    if (enx < 0) enx = 0;
    if (stz >= 8) stz = 7;
    if (enz < 0) enz = 0;
    
    
    
    
    
    
    rect[0][0] = enx * 0x9C4;
    rect[0][1] = 0;
    rect[0][2] = enz * 0x9C4;
    rect[0][3] = 0;
    sceVu0AddVector(rect[0], rect[0], origin);
    
    sceVu0CopyVector(rect[1], rect[0]);
    rect[1][2] += 2500.0f;
    
    sceVu0CopyVector(rect[2], rect[0]);
    rect[2][0] += 2500.0f;
    
    sceVu0CopyVector(rect[3], rect[0]);
    rect[3][0] += 2500.0f;
    rect[3][2] += 2500.0f;
    
    
    
    tagbuffer = (u_char*) pBM->tileViewClipInfo;
    
    
    
    
    
    
    for (iz = enz; iz <= stz; iz++) {
        for (ix = enx; ix <= stx; ix++) {
            
            
            clip = sh2_ClipHitCheckSquare(Env_ctl.objclip_mat, rect, view_triangle);
            
            if (clip) {
                
                index = ix + iz * 8;
                
                tagbuffer[index] = 0x20;
            }
            
            sceVu0CopyVector(rect[0], rect[2]);
            sceVu0CopyVector(rect[1], rect[3]);
            rect[2][0] += 2500.0f;
            rect[3][0] += 2500.0f;
        }
        
        rect[0][2] = rect[1][2];
        rect[2][2] = rect[3][2];
        rect[1][2] += 2500.0f;
        rect[3][2] += 2500.0f;
        
        rect[0][0] = *origin + enx * 0x9C4;
        rect[1][0] = rect[0][0];
        rect[2][0] = rect[0][0] + 2500.0f;
        rect[3][0] = rect[2][0];
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    vwGetViewPosition(svt);
    sceVu0SubVector(svt, svt, origin);
    
    ssz = svt[2] / 2500.0f;
    ssx = svt[0] / 2500.0f;
    
    pBM->view_tile = ssx + ssz * 8;
    
    
    for (iz = ssz - 1; iz <= ssz + 1; iz++) {
        if (iz < 0 || iz >= 8) continue;
            
        for (ix = ssx - 1; ix <= ssx + 1; ix++) {
            if (ix < 0 || ix >= 8) continue;
        
            tagbuffer[ix + iz * 8] = 0x20;
        }
    }




}

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2_ClipHitCheckSquare);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", kari_set_vu0cal);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_setVCTAG_DrawSys);

void sh2gfw_set_objclip_matrix(void) {
    float gsx; // r29+0x70
    float gsy; // r20



    
    float NearZ = VbScreenInfo.nearz; // r21
    float FarZ = VbScreenInfo.farz; // r22
    float tmp[4]; // r29+0x20
    float wvm[4][4]; // r29+0x30

    
    
    
    extern float clip_volume[4];
    extern float y_dirvec[4];
    
    
    
    
    
    
    
    gsx = gsy = clip_volume[2];
    sceVu0UnitMatrix(Env_ctl.objclip_mat);
    sceVu0UnitMatrix(wvm);
    
    
    sh2gde_Get_EyeDir(tmp); tmp[1] = 0.0f;
    vec_normalize(tmp, wvm[2]);
    vec_cross_product(wvm[2], y_dirvec, wvm[0]);
    vec_copy_reverse(y_dirvec, wvm[1]); // fixed?
    vwGetViewPosition(tmp);
    
    tmp[1] = -1125.0;
    sceVu0TransMatrix(wvm, wvm, tmp);
    sceVu0InversMatrix(wvm, wvm);
    
    
    
    
    
    
    
    
    Env_ctl.objclip_mat[0][0] = (2.0f * NearZ) / (gsx + gsx);
    Env_ctl.objclip_mat[1][1] = (2.0f * NearZ) / (gsy + gsy);
    Env_ctl.objclip_mat[2][2] = (FarZ + NearZ) / (FarZ - NearZ);
    Env_ctl.objclip_mat[3][2] = (-2.0f * (FarZ * NearZ)) / (FarZ - NearZ);
    Env_ctl.objclip_mat[2][3] = 1.0f;
    Env_ctl.objclip_mat[3][3] = 0.0f;
    
    
    
    sceVu0MulMatrix(Env_ctl.objclip_mat, Env_ctl.objclip_mat, wvm);
}

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_Set_DispOnOffObj);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_Init_DispOnOffObj);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_FastSet_DispOnOffObj);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_Get_ChrClip_FLG);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_Check_ChrClip_FLG);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_viewclip", sh2gfw_Check_ClipOKChar);

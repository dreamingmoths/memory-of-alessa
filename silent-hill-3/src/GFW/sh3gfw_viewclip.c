#include "common.h"
#include "GFW/sh3gfw_viewclip.h"
#include "GFW/sh3_DrawEnvData.h"
#include "vec.h"

#pragma optimization_level 2

static void sh3gfw_init_vctagbuf(void* vc) {
    Q_WORDDATA* VcBuf = vc;

   extern Q_WORDDATA D_00361D00;
   extern Q_WORDDATA D_00361D10;
   Q_WORDDATA cleardata1 = D_00361D00;
   Q_WORDDATA cleardata2 = D_00361D10;

    if (!func_001AAD60()) {
        VcBuf[0] = cleardata2;
        VcBuf[1] = cleardata2;
        VcBuf[2] = cleardata2;
        VcBuf[3] = cleardata2;
        return;
    }
    VcBuf[0] = cleardata1;
    VcBuf[1] = cleardata1;
    VcBuf[2] = cleardata1;
    VcBuf[3] = cleardata1;
}

static void sh3gfw_get_blockORIGIN(float (* bbox)[4], float* origin) {
    int ix;
    int iz;
    int tmp[4];
 
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


int sh3gfw_Get_CamTilePos(float* origin) {
    int ssx, ssz;
    float svt[4];

    vwGetViewPosition(svt);
    svt[3] = 1.0f;
    sceVu0SubVector(svt, svt, origin);

    ssz = svt[2] / 2500.0f;
    ssx = svt[0] / 2500.0f;
    return ssx + (ssz * 8);
}

void sh3gfw_set_objclip_matrix(void) {
    float gsx;
    float gsy;

    float NearZ = func_001B4130();
    float FarZ = func_001B4110();
    float tmp[4];
    float wvm[4][4];

    gsx = gsy = func_001B4140();
    sceVu0UnitMatrix(Env_ctl.objclip_mat);
    sceVu0UnitMatrix(wvm);
    
    sh3gde_Get_EyeDir(tmp); tmp[1] = 0.0f;
    vec_normalize(tmp, wvm[2]);
    vec_cross_product(wvm[2], y_dirvec, wvm[0]);
    vec_copy_reverse(y_dirvec, wvm[1]);
    func_001B3E80(tmp);
    
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

extern /* static */ float inclip;
void sh3gfw_get_viewTriangle(sceVu0FMATRIX view_triangle) {
    sceVu0FMATRIX work;
    sceVu0FVECTOR camera_params;
    int i;
    float z;
    float x;
    
    sceVu0UnitMatrix(work);
    func_001B3F00(camera_params);
    sceVu0RotMatrixY(work, work, camera_params[1]);

    z = func_001B4110();
    x = 512.0f * z / func_001B4100();
    
    for (i = 0; i < 3; i++) {
        sceVu0ScaleVector(view_triangle[i], view_triangle[i], 0.0f);
    }
    
    view_triangle[1][0] = 0.5f * x * inclip;
    view_triangle[1][2] = z;
    view_triangle[2][0] = -0.5f * x * inclip;
    view_triangle[2][2] = z;
    func_001B3E80(camera_params);
    
    for (i = 0; i < 3; i++) {
        sceVu0ApplyMatrix(view_triangle[i], work, view_triangle[i]);
        sceVu0AddVector(view_triangle[i], view_triangle[i], camera_params);
        view_triangle[i][1] = 0.0f;
    }
}

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_viewclip", sh3gfw_get_ViewRecTangle);

void sh3gfw_make_tagclipdata(sceVu0FVECTOR origin, sceVu0FMATRIX view_triangle, sceVu0IVECTOR view_rect, u_char* tagbuffer) {
    int ix;
    int iz;
    int stx;
    int enx;
    int stz;
    int enz;
    int index;
    sceVu0FMATRIX rect;
    int clip;
    int ssx;
    int ssz;
    sceVu0FVECTOR svt;
    
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

    for (iz = enz; iz <= stz; iz++) {
        for (ix = enx; ix <= stx; ix++) {
            clip = sh3_ClipHitCheckSquare(Env_ctl.objclip_mat, rect, view_triangle);
            
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
    svt[3] = 1.0f;
    sceVu0SubVector(svt, svt, origin);
    
    ssz = svt[2] / 2500.0f;
    ssx = svt[0] / 2500.0f;
    
    for (iz = ssz - 1; iz <= ssz + 1; iz++) {
        if (iz >= 0 && iz < 8) {
            for (ix = ssx - 1; ix <= ssx + 1; ix++) {
                if (ix >= 0 && ix < 8) {
                    tagbuffer[ix + iz * 8] = 0x20;
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_viewclip", sh3_ClipHitCheckSquare);

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_viewclip", func_001AA9B0);

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_viewclip", func_001AA9E0);

#ifdef NON_MATCHING
void func_001AAA90(Sh3Gfw_Work* arg0) {
    float sp20[4];
    float sp30[4][4];
    int sp70[4];

    func_001AEA40(sp30, arg0);
    sh3gfw_init_vctagbuf(&arg0->pBM);
    sh3gfw_get_blockORIGIN(sp30, sp20);
    sh3gfw_get_ViewRecTangle(sp20, &D_01D97090, sp70, sh3gfw_Get_CamTilePos(sp20));
    sh3gfw_make_tagclipdata(sp20, &D_01D97090, sp70, &arg0->pBM);
    func_001AAB60(arg0);
}
#else
INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_viewclip", func_001AAA90)
#endif

void func_001AAB30(void) {
    sh3gfw_get_viewTriangle(Env_ctl.camera_mat);
}

#ifdef NON_MATCHING
void func_001AAB60(Sh3Gfw_Work* arg0) {
    func_001AACD0();
    func_001AAD30(arg0);
    arg0->unk76C = func_001C2C00();
}
#else
INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_viewclip", func_001AAB60)
#endif

INCLUDE_ASM("asm/nonmatchings/GFW/sh3gfw_viewclip", func_001AABB0);

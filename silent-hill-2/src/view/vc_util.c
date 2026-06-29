#include "vc_util.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2sys.h"
#include "common.h"

// @todo: move to vec.h/common.h - currently moving this to `common.h` underneath `vec_scale` causes mismatch?
static inline void vec_div_xyz(void* v, float s, void* out) {
    asm("lui t7, 0x3f80\n\
         mtc1 t7, f8\n\
         nop\n\
         div.s f8, f8, %1\n\
         lqc2 vf4, 0(%0)\n\
         mfc1 t7, f8;\
         qmtc2 t7, vf5\n\
         vmulx.xyz vf4, vf4, vf5x\n\
         sqc2 vf4, 0(%2)"
        : "+r"(v), "+f"(s), "+r"(out)::"t7");
}

// switched %1 and %0
static inline void vec_add_alt(void* x, void* y, void* out) {
    asm("\
        lqc2 vf4, 0(%1)\n\
        lqc2 vf5, 0(%0)\n\
        vadd.xyzw vf4, vf4, vf5\n\
        sqc2 vf4, 0(%2)"
        : "+r"(x), "+r"(y), "+r"(out));
}

#line 63
void vcInitCamera(VC_ROAD_DATA** roadarray_list) {

    vcCameraInternalInfo.mode = 0;
    vcCameraInternalInfo.mv_smooth = 0;
    vcCameraInternalInfo.ev_cam_rate = 0.0f;


    vcPreSetCharaDataForCamera();

    vcSetCameraUseWarp(sys.hero.pos, sys.hero.ang[1]);

    vwInitViewInfo();

    vcInitVCSystem(roadarray_list);



    vcStartCameraSystem();
    vcSetProjectionValue(0.0f, 0);

    vcWork.flags |= VC_PROJ_MOMENT_CHANGE_F;



    sys.cam_ang_z = 0.0f;
    sys.cam_r_xz = 1500.0f;
    sys.cam_y = 0.0f;
}

#line 108
void vcSetCameraUseWarp(sceVu0FVECTOR chr_pos, float chr_ang_y) {
    sceVu0FVECTOR cam_pos;
    sceVu0FVECTOR cam_ang;


    vec_zero(cam_ang); // @bug: Arrays are set but never used, vec_zero uses asm that makes compiler forget this?
    cam_ang[1] = chr_ang_y;


    cam_pos[0] = chr_pos[0] - (795.0f * shSinF(chr_ang_y));
    cam_pos[1] = -900.0f + chr_pos[1];
    cam_pos[2] = chr_pos[2] - (795.0f * shCosF(chr_ang_y));
    cam_pos[3] = 1.0f;


    vcSetFirstCamWork(chr_pos, chr_ang_y, GET_BIT(Sh2sys.main_status, 2));
    UNSET_BIT(Sh2sys.main_status, 2);
}

#line 142
int vcRetCamMvSmoothF(void) {
    return vcCameraInternalInfo.mv_smooth;
}

INCLUDE_ASM("asm/nonmatchings/view/vc_util", vcMoveAndSetCamera);

#line 429
void vcMakeHeroHeadPos(sceVu0FVECTOR head_pos) {
    sceVu0FMATRIX neck_lwm;
    sceVu0FVECTOR fpos;



    mat_copy(neck_lwm, vcPreInfo.hero_neck_lwm);

    vec_zero(fpos);
    fpos[1] = -50.0f;
    vbApplyMatrixWithoutTr(fpos, neck_lwm, fpos);



    vec_add_alt(neck_lwm[3], fpos, head_pos);
    head_pos[1] += -150.0f;
    head_pos[3] = 1.0f;
}

#line 468
void vcAddOfsToPos(sceVu0FVECTOR out_pos, sceVu0FVECTOR in_pos, float ofs_xz_r, float ang_y, float ofs_y) {
    out_pos[0] = in_pos[0] + (ofs_xz_r * shSinF(ang_y));
    out_pos[2] = in_pos[2] + (ofs_xz_r * shCosF(ang_y));
    out_pos[1] = in_pos[1] + ofs_y;
}

#line 497
void vcSetRefPosAndSysRef2CamParam(sceVu0FVECTOR ref_pos, SYS_W* sys_p, int for_f, int back_f, int right_f, int left_f, int up_f, int down_f) {






    if (for_f) sys_p->cam_r_xz -= 50.0f;
    if (back_f) sys_p->cam_r_xz += 50.0f;
    if (right_f) sys_p->cam_ang_y -= TO_RAD(1.0f);
    if (left_f) sys_p->cam_ang_y += TO_RAD(1.0f);
    if (up_f) sys_p->cam_y -= 50.0f;
    if (down_f) sys_p->cam_y += 50.0f;

    sys_p->cam_ang_y = shAngleRegulate(sys_p->cam_ang_y);

    if (sys_p->cam_r_xz < 500.0f) sys_p->cam_r_xz = 500.0f;


    vcAddOfsToPos(ref_pos, sys.hero.pos, 250.0f, sys.hero.ang[1], -500.0f);


}

#line 539
void vcSetRefPosAndCamPosAngByPad(void) {
    sceVu0FVECTOR cam_ang;
    sceVu0FVECTOR cam_pos;

    vwGetViewPosition(cam_pos);
    vec_div_xyz(cam_pos, 500.0f, cam_pos);

    vwGetViewAngle(cam_ang);

    #line 623 // line 547 -> 623? Commented-out code? SH1 version of this func does a lot more.
}

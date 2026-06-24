#include "vw_main.h"
#include "vec.h"
#include "SH2_common/sh_vu0.h"

#line 52
void vwInitViewInfo(void) {
    vec_zero(&vwViewPointInfo.rview.vp);
    vec_zero(&vwViewPointInfo.rview.vr);
    vwViewPointInfo.rview.vr[2] = 1.0f;

    vwViewPointInfo.rview.rz = 0.0f;

    vwViewPointInfo.rview.super = &vwViewPointInfo.vwcoord;

    vbInitCoordinate(NULL, &vwViewPointInfo.vwcoord);

    vwSetViewInfo();
}

#line 100
void vwGetViewPosition(sceVu0FVECTOR pos) {
    vec_copy(pos, vwViewPointInfo.worldpos);
}

#line 119
void vwGetViewAngle(sceVu0FVECTOR pos) {
    vec_copy(pos, vwViewPointInfo.worldang);
}

#line 184
void vwSetCoordRefAndEntou(VbCOORDINATE* parent_p, sceVu0FVECTOR ref, float cam_ang_y, float cam_ang_z, float cam_y, float cam_xz_r) {
    sceVu0FVECTOR view_ang;

    vwViewPointInfo.vwcoord.flg = 0;
    vwViewPointInfo.vwcoord.super = parent_p;

    view_ang[0] = shAtan2(cam_xz_r, -cam_y);
    view_ang[1] = cam_ang_y;
    view_ang[2] = cam_ang_z;
    view_ang[3] = 1.0f;


    view_ang[0] *= -1.0f;
    view_ang[1] += PI;

    view_ang[0] = shAngleRegulate(view_ang[0]);
    view_ang[1] = shAngleRegulate(view_ang[1]);
    view_ang[2] = shAngleRegulate(view_ang[2]);

    vu0_unit_matrix(vwViewPointInfo.vwcoord.coord);
    vwRotMatrixYXZ(view_ang, vwViewPointInfo.vwcoord.coord);

    vwViewPointInfo.vwcoord.coord[3][0] = ref[0] + (cam_xz_r * shSinF(cam_ang_y));
    vwViewPointInfo.vwcoord.coord[3][1] = ref[1] + cam_y;
    vwViewPointInfo.vwcoord.coord[3][2] = ref[2] + (cam_xz_r * shCosF(cam_ang_y));
}

#line 227
void vwSetViewInfo(void) {
    vbSetRefView(&vwViewPointInfo.rview);



    volatile_vec_copy(vwViewPointInfo.worldpos, vwViewPointInfo.vwcoord.lw[3]);

    vwMatrixToAngleYXZ(vwViewPointInfo.worldang, vwViewPointInfo.vwcoord.lw);
}

#line 253
void vwSetViewInfoDirectMatrix(VbCOORDINATE* pcoord, sceVu0FMATRIX cammat) {
    vwViewPointInfo.vwcoord.flg = 0;
    vwViewPointInfo.vwcoord.super = pcoord;
    mat_copy(vwViewPointInfo.vwcoord.coord, cammat); } // @note: closing bracket needs to be here to match line number?

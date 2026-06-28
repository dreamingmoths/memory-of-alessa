#include "vc_calc.h"
#include "Chacter/m3_play.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2dt.h"
#include "view/vb_main.h"

#line 30
float vcRetNearRatioSwitchAreaInXZPos(VC_NEAR_ROAD_DATA cur_near_road, sceVu0FVECTOR chr_pos, sceVu0FVECTOR cam_tgt_pos) {
    float near_ratio = 0.0f;
    float ofs_ang_y;
    sceVu0FVECTOR ppos;

    ofs_ang_y = shAngleRegulate(shAtan2(chr_pos[2] - cam_tgt_pos[2], chr_pos[0] - cam_tgt_pos[0]));




    vcTransRotRoadArea(ppos, cur_near_road.sw_rzm, chr_pos);

    switch (cur_near_road.rd_dir_type) {
        case VC_RD_DIR_Z: // @note: Enum name might be switched with `VC_RD_DIR_X` (these names came from outside SH2 symbols)
            if (TO_RAD(0.0f) <= ofs_ang_y && ofs_ang_y < TO_RAD(180.0f)) {
                near_ratio = (cur_near_road.sw.max_hx - ppos[0]) / (cur_near_road.sw.max_hx - cur_near_road.sw.min_hx);


            } else {
                near_ratio = (ppos[0] - cur_near_road.sw.min_hx) / (cur_near_road.sw.max_hx - cur_near_road.sw.min_hx);


            }
            break;
        case VC_RD_DIR_X: // @note: Enum name might be switched with `VC_RD_DIR_Z`
            if (TO_RAD(-90.0f) <= ofs_ang_y && ofs_ang_y < TO_RAD(90.0f)) {
                near_ratio = (cur_near_road.sw.max_hz - ppos[2]) / (cur_near_road.sw.max_hz - cur_near_road.sw.min_hz);


            } else {
                near_ratio = (ppos[2] - cur_near_road.sw.min_hz) / (cur_near_road.sw.max_hz - cur_near_road.sw.min_hz);


            }
            break;
    }

    return near_ratio;
}

// @note: weird line numbering?
#line 80
float vcRetNearRatioSwitchAreaForCircleCam(VC_NEAR_ROAD_DATA cur_near_road, VC_CIR_CAM_MANAGER cir_man, sceVu0FVECTOR chr_pos) {
    float near_ratio;
    float ofs_ang_y;
    sceVu0FVECTOR ppos;

    ofs_ang_y = shAngleRegulate(shAtan2(chr_pos[2] - cir_man.origin[2], chr_pos[0] - cir_man.origin[0]));







    vcTransRotRoadArea(ppos, cur_near_road.sw_rzm, chr_pos);

    if ((TO_RAD(-135.0f) <= ofs_ang_y && ofs_ang_y < TO_RAD(-45.0f)) ||
        (TO_RAD(45.0f) <= ofs_ang_y && ofs_ang_y < TO_RAD(135.0f))) {


        near_ratio = float_abs((cir_man.origin[0] - chr_pos[0]) / cir_man.sw_l[0]);

    } else {
        near_ratio = float_abs((cir_man.origin[2] - chr_pos[2]) / cir_man.sw_l[2]);

    }



    return near_ratio;
}

#line 127
void vcTransRotRoadArea(sceVu0FVECTOR v0, sceVu0FMATRIX m, sceVu0FVECTOR v1) {
    vec_add(v1, m[3], v0);
    vbApplyMatrixWithoutTr(v0, m, v0);

}

#line 150
void vcRotTransRoadArea(sceVu0FVECTOR v0, sceVu0FMATRIX m, sceVu0FVECTOR v1) {

    vbApplyMatrixWithoutTr(v0, m, v1);
    vec_add(v0, m[3], v0);
}

#line 162
float vcGetMinInRoadDist(void) {
    return (BgIsOut(0) != 0) ? 500.0f : 400.0f;
}

// @note line numbers are close but has mismatch in the if blocks.
#line 175
void vcConvertCamFile(VC_ROAD_DATA* road_ary) {
    VC_ROAD_DATA* rd_p;

    rd_p = road_ary;
    while (!(rd_p->flags & VC_RD_END_DATA_F)) {

        rd_p->kind_id <<= 0x10;
        rd_p->kind_id >>= 0x10;


        if (rd_p->ofs_watch_hy == 10000.0f) {
            rd_p->ofs_watch_hy = -300.0f;
        } else if (rd_p->ofs_watch_hy == 10001.0f) {
            rd_p->ofs_watch_hy = -375.0f;
        } else if (rd_p->ofs_watch_hy == 10002.0f) {
            rd_p->ofs_watch_hy = -600.0f;
        }

        if (!rd_p->projection) {
            rd_p->projection = 448.0f;
        } else if (rd_p->projection == 10001.0f) {
            rd_p->projection = 384.0f;
        }

        if (rd_p->trace_btm_hy == 10000.0f) {
            rd_p->trace_btm_hy = -300.0f;
        } else if (rd_p->trace_btm_hy == 10001.0f) {
            rd_p->trace_btm_hy = -150.0f;
        } else if (rd_p->trace_btm_hy == 10002.0f) {
            rd_p->trace_btm_hy = 150.0f;
        }
        switch (rd_p->cam_mv_type) {
            case 0:
                if (rd_p->tmp.chs.ofs_hy == 10000.0f) {
                    rd_p->tmp.chs.ofs_hy = -500.0f;
                }
                if (rd_p->tmp.chs.ofs_hy == 10001.0f) {
                    rd_p->tmp.chs.ofs_hy = -125.0f;
                }
                break;
            case 2:
                if (rd_p->tmp.chs.ofs_hy == 10000.0f) {
                    rd_p->tmp.chs.ofs_hy = -0.5235988f;
                }
                break;
        }
        rd_p++;
    }
}

#include "sh2_common.h"

#include "Lens/lens_flare.h"
#include "Lens/lens_th_draw.h"

#include "libgraph.h"
#include "Chacter/character.h"
#include "Event/demoview.h"

#include "GFW/sh2gfw_structs.h"
#include "GFW/sh2gfw_alltexman.h"
#include "GFW/sh2_DrawEnvData.h"
#include "GFW/sh2_get_drawenv.h"
#include "GFW/sh2gfw_Texpacket.h"

#include "view/vb_main.h"
#include "view/camera_dat.h"

static void shLensFlareGetScreenInfo(void);
static void shLensFlareSetLightSeed(LensFlareWork* lf_work, ScreenInfo* sc_info, int type);
static void _sceVu0RotTransPers(sceVu0IVECTOR dest, sceVu0FMATRIX mat, sceVu0FVECTOR src, int mode);
static float shLensFlareOresenHokan(float* Y_ary, int Y_suu, float input_X /* r29+0x40 */, float min_X /* r29+0x40 */, float max_X /* r29+0x40 */);
static float shLensFlareMakeEffectTargetRate(float light_eff_pow /* r29+0x30 */, LensFlareWork* lf_work);
static void shLensFlareMakeScreenPos(LensFlareWork* lf_work, Vector4* ws_l_sxyz_p, Vector4* ws_l_vec_p, int scr_z);
static void shLensFlareMakeScreenAngle(LensFlareWork* lf_work, Vector4* ws_l_sxyz_p, Vector4* ws_l_vec_p);
static void ktVectorNormal(Vector4* dest, Vector4* src);
static void _sceVu0Normalize(sceVu0FVECTOR v0, sceVu0FVECTOR v1);
static void shGetJamesLightInfo(SubCharacter* scp, LightInfo* l_info, int type);
static void shLensFlareMakeScreenInfo(LensFlareWork* lf_work, LightInfo* l_info);
void sh2gde_getWorldScreenMatrix(sceVu0FMATRIX wsm);

extern /* static */ int lf_flicker_on; // size: 0x4, address: 0x1013750
extern /* static */ int lf_flicker_off; // size: 0x4, address: 0x0

extern float atan2f(float, float);

static void shLensFlareGetScreenInfo(void) {
    screen_info.center_x = VbScreenInfo.cx;
    screen_info.center_y = VbScreenInfo.cy;
    screen_info.width = VbScreenInfo.sx;
    screen_info.height = VbScreenInfo.sy;
}

int shLensFlareCameraIsSmooth(void) {
    int ret = !(demo_status & 1);

    return ret;
}

int shLensFlareLightCenterIsVisible(LensFlareWork* lf_info /* r16 */) {
    sceGsStoreImage* StoreIm; // r2
    u_short* now_z_value;     // r2
    u_int zbuffer;            // r2 @todo dwarf symbol is unused here
    int zval;                 // r2
    if (lf_info->draw_center_f == 0)
        return 0;

    StoreIm = (sceGsStoreImage*)SCRATCHPAD_START;
    sh2gfw_GsSetDefStoreImage(StoreIm,
                              0x3800 /* sbp */, 8 /* sbw */, 0x3A /* spsm */,
                              (lf_info->l_screen_pos.x >> 4) - 0x700,
                              (lf_info->l_screen_pos.y >> 4) - 0x700,
                              1, 64);
    now_z_value = (void*)(SCRATCHPAD_START | 0x2000);
    sh2gfw_GsExecStoreImage(StoreIm, (u_long128*)now_z_value);

    zval = *now_z_value;

    if (zval <= lf_info->l_screen_pos.z) {
        if (3 < lf_flicker_on)
            return 1;

        lf_flicker_on++;
        return 0;
    }

    lf_flicker_on = 0;
    return 0;
}


static inline u_char check_screen_bounds(LensFlareWork* lf_work, ScreenInfo* sc_info) {
    float half_width;
    float center_x;
    float screen_l_pos_x;
    int above_top_y;
    int below_bottom_y;
    int within_z_range;
    int ret;
    int in_x_bounds;
    float left_x;

    // @note: assignments need to be reversed from declaration order for match?
    ret = 0;
    within_z_range = 0;
    below_bottom_y = 0;
    above_top_y = 0;

    left_x = sc_info->center_x - (sc_info->width / 2.0f);

    in_x_bounds = (lf_work->scr_l_pos.x >= sc_info->center_x - (sc_info->width / 2.0f));
    if (in_x_bounds) {
        in_x_bounds = lf_work->scr_l_pos.x <= sc_info->center_x + (sc_info->width / 2.0f);
    }
    
    if (in_x_bounds && lf_work->scr_l_pos.y >= sc_info->center_y - (sc_info->height / 2.0f)) {
        above_top_y = 1;
    }
    if (above_top_y && lf_work->scr_l_pos.y <= sc_info->center_y + (sc_info->height / 2.0f)) {
        below_bottom_y = 1;
    }
    if (below_bottom_y && lf_work->l_screen_pos.z >= 0) {
        within_z_range = 1;
    }
    if (within_z_range && lf_work->scr_l_ang_z >= TO_RAD(78)) {
        ret = 1;
    }

    return ret;
}

static void shLensFlareSetLightSeed(LensFlareWork* lf_work /* r17 */, ScreenInfo* sc_info /* r16 */, int type /* r18 */) {
    IVector4 vi0;      // r29+0x40
    sceVu0FMATRIX wsm; // r29+0x50

    sh2gde_getWorldScreenMatrix(wsm);
    shLensFlareGetScreenInfo();
    _sceVu0RotTransPers((int*)&vi0, wsm, &light_info[type].world_light_pos, 1);
    lf_work->l_screen_pos = vi0;

    lf_work->draw_center_f = check_screen_bounds(lf_work, sc_info);
}

static void _sceVu0RotTransPers(sceVu0IVECTOR dest /* r2 */, sceVu0FMATRIX mat /* r2 */, sceVu0FVECTOR src /* r2 */, int mode /* r2 */) {
    asm volatile(".set noreorder\n\
        lqc2	vf8,0x0(%2)\n\
    	lqc2	vf4,0x0(%1)\n\
    	lqc2	vf5,0x10(%1)\n\
    	lqc2	vf6,0x20(%1)\n\
    	lqc2	vf7,0x30(%1)\n\
    	vmulax.xyzw     ACC, vf4,vf8\n\
    	vmadday.xyzw    ACC, vf5,vf8\n\
    	vmaddaz.xyzw    ACC, vf6,vf8\n\
    	vmaddw.xyzw      vf8,vf7,vf8\n\
    	vdiv    Q,vf0w,vf8w\n\
    	vwaitq\n\
    	vmulq.xyz	vf8,vf8,Q\n\
    	beqz	%3,_rotTP\n\
    	vftoi4.xyzw	vf9,vf8\n\
    	vftoi0.zw	vf9,vf8	\n\
    _rotTP:\
    	sqc2	vf9,0x0(%0)\n\
        .set reorder\n\
    " : : "r"(dest), "r"(mat), "r"(src), "r"(mode) : "memory");
}


void sh2gde_getWorldScreenMatrix(sceVu0FMATRIX wsm) {
    sceVu0CopyMatrix(wsm, cam0.world_screen);
}

// @todo: local names may be mixed up...
static float shLensFlareOresenHokan(float* Y_ary /* r17 */, int Y_suu /* r16 */, float input_X /* r29+0x40 */, float min_X /* r29+0x40 */, float max_X /* r29+0x40 */) {
    float output_Y; // r29+0x40

    if (input_X >= max_X) {
        output_Y = Y_ary[Y_suu - 1];
    } else if (input_X < min_X) {
        output_Y = *Y_ary;
    } else {
        float amari;   // あまり // r29+0x40
        float kukan_w; // くかん // r20
        int kukan_no;  // r2
        amari = (max_X - min_X) / (Y_suu - 1);
        kukan_w = input_X - min_X, kukan_no = (int)(kukan_w / amari);
        if (kukan_no >= (Y_suu - 1)) {
            output_Y = Y_ary[Y_suu - 1];
        } else if (kukan_no < 0) {
            output_Y = *Y_ary;
        } else {

            do {
                float tmp = 0;
            } while (0);
            while (kukan_w >= amari) {
                kukan_w -= amari;
            }

            output_Y = (Y_ary[kukan_no] * (amari - kukan_w) + kukan_w * (Y_ary[kukan_no + 1])) / amari;
        }
    }

    return output_Y;
}

// @hack float memes in `shLensFlareMakeEffectTargetRate`
static inline int uncurse_lens_flare_blood(void) {
    float x;
}

static float pow_rate_dat[2] = {0.0f, 1.0f}; // @ 0x002B63C0
static float dist_rate_dat[7] = { 4.0f, 1.3f, 0.89999998f, 0.69999999f, 0.5f, 0.34999999f, 0.2f}; // @ 0x002B63D0
static float ang_z_rate_dat[7] = {0.15f, 0.2f, 0.25f, 0.3f, 0.34999999f, 0.5f, 1.3f}; // @ 0x002B63F0
static float shLensFlareMakeEffectTargetRate(float light_eff_pow /* r29+0x30 */, LensFlareWork* lf_work /* r16 */) {
    float ret_tgt_rate = uncurse_lens_flare_blood(); // r29+0x30

    float pow_rate = shLensFlareOresenHokan(
        pow_rate_dat,
        2,
        light_eff_pow,
        0.0f,
        1.0f
    ); // r20

    float dist_rate = shLensFlareOresenHokan(
        dist_rate_dat,
        7,
        lf_work->scr_l_pos.z,
        204.8f,
        3328.0f
    ); // r21


    float ang_z_rate = shLensFlareOresenHokan(
        ang_z_rate_dat, 7, lf_work->scr_l_ang_z,
        TO_RAD(78.0f),
        TO_RAD(167.000009f)
    ); // r29+0x30

    ret_tgt_rate = ang_z_rate * pow_rate * dist_rate;
    if (2.0f > ret_tgt_rate) {
        return ret_tgt_rate;
    }
    return 2.0f;
}

static void shLensFlareMakeScreenPos(LensFlareWork* lf_work /* r2 */, Vector4* ws_l_sxyz_p /* r2 */, Vector4* ws_l_vec_p /* r2 */, int scr_z /* r2 */) {
    // Range: 0x1875F0 -> 0x187720
    float geom_x;    // r2
    float geom_y;    // r3
    Vector4 tmp_pos; // r29
    if (ws_l_sxyz_p->z > (scr_z / 2)) {

        tmp_pos = *ws_l_sxyz_p;
    } else {
        float tmp_vec_z; // r29+0x10

        tmp_vec_z = ws_l_vec_p->z == 0.0f ? 1.0f : ws_l_vec_p->z;

        tmp_pos.z = scr_z / 2;
        tmp_pos.x = ws_l_sxyz_p->x + ((ws_l_vec_p->x * (scr_z / 2 - ws_l_sxyz_p->z)) / tmp_vec_z);

        tmp_pos.y = ws_l_sxyz_p->y + ((ws_l_vec_p->y * (tmp_pos.z - ws_l_sxyz_p->z)) / tmp_vec_z);
    }

    geom_x = VbScreenInfo.cx;
    geom_y = VbScreenInfo.cy;

    lf_work->scr_l_pos.z = tmp_pos.z;
    lf_work->scr_l_pos.x = geom_x + ((tmp_pos.x * scr_z) / tmp_pos.z);
    lf_work->scr_l_pos.y = geom_y + ((tmp_pos.y * scr_z) / tmp_pos.z);
}

static void shLensFlareMakeScreenAngle(LensFlareWork* lf_work /* r17 */, Vector4* ws_l_sxyz_p /* r2 */, Vector4* ws_l_vec_p /* r16 */) {
    Vector4 one_pos, one_l_vec, one_op_vec;
    float cos_z, sin_z; // r20
    Vector4 vec;        // r29+0x70

    ktVectorNormal(&one_pos, ws_l_sxyz_p);
    ktVectorNormal(&one_l_vec, ws_l_vec_p);

    sceVu0OuterProduct(&one_op_vec, &one_pos, &one_l_vec);

    ktVectorNormal(&one_op_vec, &one_op_vec);

    lf_work->scr_l_ang_xy = atan2f(one_op_vec.y, one_op_vec.x);

    cos_z = sceVu0InnerProduct(&one_pos, &one_l_vec);

    sceVu0OuterProduct(&vec, &one_op_vec, &one_pos);

    sin_z = sceVu0InnerProduct(&one_l_vec, &vec);

    lf_work->scr_l_ang_z = atan2f(sin_z, cos_z);
}

static void ktVectorNormal(Vector4* dest /* r2 */, Vector4* src /* r2 */) {
    _sceVu0Normalize(dest, src);
}

static void _sceVu0Normalize(sceVu0FVECTOR v0 /* r2 */, sceVu0FVECTOR v1 /* r2 */) {
    asm volatile("lqc2    vf4,0x0(%1)\n\
        vmul.xyz vf5,vf4,vf4\n\
        vaddy.x vf5,vf5,vf5\n\
        vaddz.x vf5,vf5,vf5\n\
        vrsqrt Q, vf0w, vf5x\n\
        vsub.w vf4, vf0, vf0\n\
        vwaitq\n\
        vmulq.xyz  vf4,vf4,Q\n\
        sqc2    vf4,0x0(%0)\n\
        " : : "r"(v0), "r"(v1) : "memory");
}

static void shGetJamesLightInfo(SubCharacter* scp, LightInfo* l_info /* r17 */, int type /* r16 */) {
    if (sh2gde_CheckSpot_JmsOrBG()) {
        if (type) {
            shGetJamesLightPosOriginal_Reverse(&l_info->world_light_pos, &l_info->world_light_vector);
        } else {
            shGetJamesLightPosOriginal(&l_info->world_light_pos, &l_info->world_light_vector);
        }
    } else {
        sceVu0CopyVector(&l_info->world_light_pos.x, sh2gde_Get_BGSpotPos());
        sceVu0CopyVector(&l_info->world_light_vector.x, sh2gde_Get_BGSpotDir());
        l_info->world_light_pos.y += (50.0f * l_info->world_light_vector.y) - 3.0f;
        l_info->world_light_pos.z += (50.0f * l_info->world_light_vector.z) - 20.0f;
    }

    l_info->light_pow = type ? 0.6f : 1.0f;
}

static void shLensFlareMakeScreenInfo(LensFlareWork* lf_work /* r17 */, LightInfo* l_info /* r16 */) {
    Vector4 ws_l_pos;  // r29+0x30
    Vector4 ws_l_vec;  // r29+0x40
    sceVu0FMATRIX wsm; // r29+0x50

    sh2gde_getWorldViewMatrix(wsm);
    sceVu0ApplyMatrix(&ws_l_pos, wsm, &l_info->world_light_pos);
    sceVu0ApplyMatrix(&ws_l_vec, wsm, &l_info->world_light_vector);
    shLensFlareMakeScreenAngle(lf_work, &ws_l_pos, &ws_l_vec);
    shLensFlareMakeScreenPos(lf_work, &ws_l_pos, &ws_l_vec, VbScreenInfo.scr_z);
}

void sh2gde_getWorldViewMatrix(sceVu0FMATRIX wsm) {
    sceVu0CopyMatrix(wsm, &VbWvsMatrix);
}

void shLensFlareInit(void) {
    int i;                  // r3
    sh2gfw_TEX_HEAD* pTH;   // r2
    sh2gfw_CLUTS_HEAD* pCH; // r2

    for (i = 0; i < 2; i++) {
        (&light_flare_work)[i].flare_inhibit_f = 0;

        (&light_flare_work)[i].lfl_sync_draw_func_exec_f = 0;
        (&light_flare_work)[i].now_l_eff_rate = 0;
    }

    pTH = &Lens_Fl_Head;
    pCH = (u_char*)pTH + pTH->allsize;

    LF_Tex_Work.pTexMAN = sh2gfw_set_TexToTrasMan(&AllTexSync_Man, pTH, pCH, &LF_Tex_Work, 0xEE00 /* @todo: ??? */);

    LF_Tex_Work.valid_id = 0xEF04;
}

void shLensFlareExec(SubCharacter* scp /* r2 */, float light_intensity /* r20 */, int type /* r18 */) {
    int count = *T0_COUNT; // r2
    int proj;              // r2 @todo symbol usage may be wrong
    float pow;

    pow = 3.0f;
    pow = pow * Env_ctl.SpotL0.color.fl32[0] / 7.0f;

    shGetJamesLightInfo(scp, &light_info[type], type);
    if ((&light_flare_work)[type].flare_inhibit_f == 0) {
        shLensFlareMakeScreenInfo(&(&light_flare_work)[type], &light_info[type]);
        if (type) {
            float angle_z = (&light_flare_work)[type].scr_l_ang_z; // @note not in dwarf
            if (angle_z < QUARTER_TURN) {
                angle_z = 0.0f;
            } else {
                angle_z = (2.0f / PI) * (angle_z - QUARTER_TURN);
            }
            reverse_light_rate = angle_z;
        }
        proj = (int)VbScreenInfo.scr_z;
        if ((&light_flare_work)[type].scr_l_pos.z > proj / 2) {
            (&light_flare_work)[type].lfl_sync_draw_func_exec_f = 1;
            (&light_flare_work)[type].tgt_l_eff_rate = shLensFlareMakeEffectTargetRate(pow, &(&light_flare_work)[type]);
            shLensFlareSetLightSeed(&(&light_flare_work)[type], &screen_info, type);
        }
    }
}

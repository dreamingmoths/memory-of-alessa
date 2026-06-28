#include "common.h"
#include "libgraph.h"

#include "Lens/lens_flare.h"
#include "Lens/lens_th_draw.h"
#include "Chacter/character.h"

static void shLensFlareGetScreenInfo(void);
static void shLensFlareSetLightSeed(LensFlareWork* lf_work, ScreenInfo* sc_info, int type);
static void _sceVu0RotTransPers(sceVu0IVECTOR dest, sceVu0FMATRIX mat, sceVu0FVECTOR src, int mode);
static float shLensFlareOresenHokan(float* Y_ary, int Y_suu, float input_X, float min_X, float max_X);
static float shLensFlareMakeEffectTargetRate(float light_eff_pow, LensFlareWork* lf_work);
static void shLensFlareMakeScreenPos(LensFlareWork* lf_work, Vector4* ws_l_sxyz_p, Vector4* ws_l_vec_p, float scr_z);
static void shLensFlareMakeScreenAngle(LensFlareWork* lf_work, Vector4* ws_l_sxyz_p, Vector4* ws_l_vec_p);
static void ktVectorNormal(Vector4* dest, Vector4* src);
static void _sceVu0Normalize(sceVu0FVECTOR v0, sceVu0FVECTOR v1);
static void shGetJamesLightInfo(SubCharacter* scp, LightInfo* l_info, int type);
static void shLensFlareMakeScreenInfo(LensFlareWork* lf_work, LightInfo* l_info);
void sh2gde_getWorldScreenMatrix(sceVu0FMATRIX wsm);

float func_001B4230(void);
float func_001B4250(void);
float func_001B4270(void);
float func_001B4290(void);
extern int func_001BF910(void);

extern int D_0038A660;
extern short D_01F2F6E8;
extern int D_01F2F6F0;
extern short lf_flicker_on;

void shLensFlareGetScreenInfo(void) {
    screen_info.center_x = func_001B4230(); /* VbScreenInfo.cx */
    screen_info.center_y = func_001B4250(); /* VbScreenInfo.cy */
    screen_info.width = func_001B4270();    /* VbScreenInfo.sx */
    screen_info.height = func_001B4290();   /* VbScreenInfo.sy */
}

int shLensFlareCameraIsSmooth(void) {
    return func_001BF910() != 0;
}

int shLensFlareLightCenterIsVisible(LensFlareWork* lf_info) {
    sceGsStoreImage* StoreIm;
    u_short* now_z_value;
    u_int zbuffer;
    int zval;
    if (lf_info->draw_center_f == 0)
        return 0;

    StoreIm = (sceGsStoreImage*)SCRATCHPAD_START;
    sh3gfw_GsSetDefStoreImage(StoreIm,
                              func_001D0670() << 5 /* sbp */, 8 /* sbw */, 0x3A /* spsm */,
                              (lf_info->l_screen_pos.x >> 4) - 0x700,
                              (lf_info->l_screen_pos.y >> 4) - 0x700,
                              1, 64);
    now_z_value = (void*)(SCRATCHPAD_START | 0x2000);
    sh3gfw_GsExecStoreImage(StoreIm, (u_long128*)now_z_value);

    zval = *now_z_value;

    if (zval + D_01F2F6F0 <= lf_info->l_screen_pos.z) {
        if (lf_flicker_on > D_0038A660) {
            D_01F2F6E8 = 1;
            return 1;
        }

        D_01F2F6E8 = 0;
        lf_flicker_on++;
        return 0;
    }

    lf_flicker_on = 0;
    D_01F2F6E8 = 0;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Lens/lens_flare", shLensFlareSetLightSeed);

// @todo: local names may be mixed up...
static float shLensFlareOresenHokan(float* Y_ary, int Y_suu, float input_X, float min_X, float max_X) {
    float output_Y;

    if (input_X >= max_X) {
        output_Y = Y_ary[Y_suu - 1];
    } else if (input_X < min_X) {
        output_Y = *Y_ary;
    } else {
        float amari;   // あまり
        float kukan_w; // くかん
        int kukan_no;
        amari = (max_X - min_X) / (f32)(Y_suu - 1);
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

extern /* static*/ float pow_rate_dat[2];   // = {0.0f, 1.0f};
extern /* static*/ float dist_rate_dat[7];  // = { 4.0f, 1.3f, 0.89999998f, 0.69999999f, 0.5f, 0.34999999f, 0.2f};
extern /* static*/ float ang_z_rate_dat[7]; // = {0.15f, 0.2f, 0.25f, 0.3f, 0.34999999f, 0.5f, 1.3f};

static float shLensFlareMakeEffectTargetRate(float light_eff_pow, LensFlareWork* lf_work) {
    float ret_tgt_rate;

    float pow_rate = shLensFlareOresenHokan(
        pow_rate_dat,
        2,
        light_eff_pow,
        0.0f,
        1.0f);

    float dist_rate = shLensFlareOresenHokan(
        dist_rate_dat,
        7,
        lf_work->scr_l_pos.z,
        204.8f,
        3328.0f);

    float ang_z_rate = shLensFlareOresenHokan(
        &ang_z_rate_dat, 7, lf_work->scr_l_ang_z,
        TO_RAD(78),
        TO_RAD(167.000009f));
    ret_tgt_rate = ang_z_rate * pow_rate * dist_rate;
    if (2.0f > ret_tgt_rate) {
        return ret_tgt_rate;
    }
    return 2.0f;
}

INCLUDE_ASM("asm/nonmatchings/Lens/lens_flare", func_0023C5A0);

float func_0012BB58(float y, float x);
#define atan2f func_0012BB58

static void shLensFlareMakeScreenAngle(LensFlareWork* lf_work, Vector4* ws_l_sxyz_p, Vector4* ws_l_vec_p) {
    Vector4 one_pos, one_l_vec, one_op_vec;
    float cos_z, sin_z;
    Vector4 vec;

    sceVu0Normalize(&one_pos, ws_l_sxyz_p); // @sh3: was ktVectorNormal
    sceVu0Normalize(&one_l_vec, ws_l_vec_p);

    sceVu0OuterProduct(&one_op_vec, &one_pos, &one_l_vec);

    sceVu0Normalize(&one_op_vec, &one_op_vec);

    lf_work->scr_l_ang_xy = atan2f(one_op_vec.y, one_op_vec.x);

    cos_z = sceVu0InnerProduct(&one_pos, &one_l_vec);

    sceVu0OuterProduct(&vec, &one_op_vec, &one_pos);

    sin_z = sceVu0InnerProduct(&one_l_vec, &vec);

    lf_work->scr_l_ang_z = atan2f(sin_z, cos_z);
}

INCLUDE_ASM("asm/nonmatchings/Lens/lens_flare", func_0023C760);

float func_001B6460(void);
static void shLensFlareMakeScreenInfo(LensFlareWork* lf_work, LightInfo* l_info) {
    Vector4 ws_l_pos;
    Vector4 ws_l_vec;
    sceVu0FMATRIX wsm;
    sh3gde_getWorldViewMatrix(wsm);
    sceVu0ApplyMatrix(&ws_l_pos, wsm, &l_info->world_light_pos);
    sceVu0ApplyMatrix(&ws_l_vec, wsm, &l_info->world_light_vector);
    shLensFlareMakeScreenAngle(lf_work, &ws_l_pos, &ws_l_vec);
    shLensFlareMakeScreenPos(lf_work, &ws_l_pos, &ws_l_vec, func_001B6460() /* VbScreenInfo.scr_z */);
}

INCLUDE_ASM("asm/nonmatchings/Lens/lens_flare", func_0023C850);

INCLUDE_ASM("asm/nonmatchings/Lens/lens_flare", func_0023C890);

INCLUDE_ASM("asm/nonmatchings/Lens/lens_flare", func_0023C8B0);

INCLUDE_ASM("asm/nonmatchings/Lens/lens_flare", shLensFlareExec);

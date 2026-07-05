#include "common.h"

#include "Lens/lens_flare.h"
#include "Lens/kari_lf_draw.h"

#include "libgraph.h"
#include "libvifpk.h"
#include "vec.h"

static void shLensFlarePolyFT4AddPacketGif(sceVif1Packet* packet, IVector4* rgbaq, IVector4* xyz0, IVector4* xyz1, IVector4* xyz2, IVector4* xyz3, Vector4* stq0, Vector4* stq1, Vector4* stq2, Vector4* stq3); // @note many arguments not in dwarf
static void shLensFlareDrawCommon(sceVif1Packet* packet, LensFlareWork* lf_work, ScreenInfo* sc_info, IVector4* base_color, float base_r, float base_vector, Vector4* t0, Vector4* t1, u_short z_value);
static void shLensFlareGetScreenInfo(void);
static void shLensFlareSetAlphaEnvironment(sceVif1Packet* packet);
static void* kari_shLensFlareEffect_Draw(int center_visible_f, LensFlareWork* lf_work, ScreenInfo* sc_info, int unknown);
static void shLensFlareSpriteAddPacketGif(sceVif1Packet* packet, IVector4* rgbaq, IVector4* xyz0, IVector4* xyz1, Vector4* stq0, Vector4* stq1); // @note many arguments not in dwarf

float D_0038A3E0 = 1.0f;

extern u_long128 kari_kick_packet[1280];
extern float D_01F2A6D0; // light intensity?
extern float D_01F2A6D0;

// @todo: find proper homes for these
extern float func_001B4170(void);
extern float func_001B41C0(void);
extern float func_001B4230(void);
extern float func_001B4250(void);
extern float func_001B4270(void);
extern float func_001B4290(void);
extern float func_001B6460(void);
extern int func_001D0670(void);
extern u_long* func_001D0740(void);
extern u_long* func_001D0720(void);
extern float func_002394F0(void); /* Env_ctl.SpotL0.color.fl32[0] */

// @sh3 unchanged from sh2 proto
void kari_Thr_LFD2TextureSend(void) {
    ASSERT_ON_LINE(LF_Tex_Work.valid_id==EFF_VALID_ID, 193);
    sh3gfw_Thr_d2TextureSend(LF_Tex_Work.pTexMAN, 0, &LF_Tex_Work.thr_cid, &LF_Tex_Work.thr_sid);
    LF_Tex_Work.Tex0Data = *(u_long128*) sh3gfw_Get_RegTEX0(LF_Tex_Work.pTexMAN, 0, 1);
}

// @sh3 unchanged from sh2 proto
void kari_Thr_LFD1D2SyncKick(void* pktop) {
    sh3gfw_Thr_d1d2SyncKick(pktop, LF_Tex_Work.thr_cid, LF_Tex_Work.thr_sid);
}

// @sh3 unchanged
static void shLensFlarePolyFT4AddPacketGif(sceVif1Packet* packet, IVector4* rgbaq, IVector4* xyz0, IVector4* xyz1, IVector4* xyz2, IVector4* xyz3, Vector4* stq0, Vector4* stq1, Vector4* stq2, Vector4* stq3) {
    IVector4 c = *rgbaq; 
    IVector4 v0 = *xyz0; 
    IVector4 v1 = *xyz1; 
    IVector4 v2 = *xyz2; 
    IVector4 v3 = *xyz3; 
    Vector4 st0 = *stq0; 
    Vector4 st1 = *stq1; 
    Vector4 st2 = *stq2; 
    Vector4 st3 = *stq3; 
    u_long giftag_polyf4[2] = {
        SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 14),
        GIF_REG(SCE_GS_PRIM, 0)   | 
        GIF_REG(SCE_GS_TEX0_1, 1) | 
        GIF_REG(SCE_GS_ST, 2)     | 
        GIF_REG(SCE_GS_RGBAQ, 3)  | 
        GIF_REG(SCE_GS_XYZ2, 4)   | 
        GIF_REG(SCE_GS_ST, 5)     | 
        GIF_REG(SCE_GS_RGBAQ, 6)  | 
        GIF_REG(SCE_GS_XYZ2, 7)   | 
        GIF_REG(SCE_GS_ST, 8)     | 
        GIF_REG(SCE_GS_RGBAQ, 9)  | 
        GIF_REG(SCE_GS_XYZ2, 10)  | 
        GIF_REG(SCE_GS_ST, 11)    | 
        GIF_REG(SCE_GS_RGBAQ, 12) | 
        GIF_REG(SCE_GS_XYZ2, 13)
    }; 
    float q = 1.0f; 
    
    u_long128* pTex0; 

    sceVif1PkOpenGifTag(packet, *(u_long128*) &giftag_polyf4);
    sceVif1PkAddGsData(packet, 
                       SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 
                           true /* gouraud */, 
                           true /* texture mapping */, 
                           false, 
                           true /* alpha blending */, 
                           false, false, false, false
                       )
    );
    pTex0 = &LF_Tex_Work.Tex0Data;
    sceVif1PkAddGsData(packet, ((u_long*)pTex0)[0]);
    sceVif1PkAddGsData(packet, SCE_GS_SET_ST(reinterpret_as_u_int(st0.x * q), reinterpret_as_u_int(st0.y * q)));
    sceVif1PkAddGsData(packet, SCE_GS_SET_RGBAQ(c.x, c.y, c.z, 0x80, *(u_int*) &q));
    sceVif1PkAddGsData(packet, SCE_GS_SET_XYZ(v0.x, v0.y, v0.z));
    sceVif1PkAddGsData(packet, SCE_GS_SET_ST(reinterpret_as_u_int(st1.x * q), reinterpret_as_u_int(st1.y * q)));
    sceVif1PkAddGsData(packet, SCE_GS_SET_RGBAQ(c.x, c.y, c.z, 0x80, *(u_int*) &q));
    sceVif1PkAddGsData(packet, SCE_GS_SET_XYZ(v1.x, v1.y, v1.z));
    sceVif1PkAddGsData(packet, SCE_GS_SET_ST(reinterpret_as_u_int(st2.x * q), reinterpret_as_u_int(st2.y * q)));
    sceVif1PkAddGsData(packet, SCE_GS_SET_RGBAQ(c.x, c.y, c.z, 0x80, *(u_int*) &q));
    sceVif1PkAddGsData(packet, SCE_GS_SET_XYZ(v2.x, v2.y, v2.z));
    sceVif1PkAddGsData(packet, SCE_GS_SET_ST(reinterpret_as_u_int(st3.x * q), reinterpret_as_u_int(st3.y * q)));
    sceVif1PkAddGsData(packet, SCE_GS_SET_RGBAQ(c.x, c.y, c.z, 0x80, *(u_int*) &q));
    sceVif1PkAddGsData(packet, SCE_GS_SET_XYZ(v3.x, v3.y, v3.z));
    sceVif1PkCloseGifTag(packet);
}

static void shLensFlareDrawCommon(sceVif1Packet* packet, LensFlareWork* lf_work, ScreenInfo* sc_info, IVector4* base_color, float base_r, float base_vector, Vector4* t0, Vector4* t1, u_short z_value) {
    Vector4 st0 = *t0;
    Vector4 st1 = *t1;
    IVector4 color;
    IVector4 prim_p[4];
    float r;
    float _rate = lf_work->now_l_eff_rate;
    float rate_scale_x = func_001B4170(); // @sh3
    float rate_scale_y = func_001B41C0(); // @sh3
    float rx, ry;

    set_color_clamped_vec(&color, lf_work->now_l_eff_rate, base_color);

    r = base_r * ((3.0f + lf_work->now_l_eff_rate) / 4.0f);

    prim_p[0].x = (int)(16.0f * ((sc_info->center_x + (base_vector * (lf_work->scr_l_pos.x - sc_info->center_x))) - (r * rate_scale_x)));

    prim_p[0].y = (int)(16.0f * ((sc_info->center_y + (base_vector * (lf_work->scr_l_pos.y - sc_info->center_y))) - (r * rate_scale_y)));

    prim_p[1].x = (int)(16.0f * ((sc_info->center_x + (base_vector * (lf_work->scr_l_pos.x - sc_info->center_x))) + (r * rate_scale_x)));

    prim_p[1].y = (int)(16.0f * ((sc_info->center_y + (base_vector * (lf_work->scr_l_pos.y - sc_info->center_y))) + (r * rate_scale_y)));

    prim_p[0].z = prim_p[1].z = z_value;

    shLensFlareSpriteAddPacketGif(packet, &color, &prim_p[0], &prim_p[1], &st0, &st1);
}

void shLensFlareGetScreenInfo(void) {
    screen_info.center_x = func_001B4230(); /* VbScreenInfo.cx */
    screen_info.center_y = func_001B4250(); /* VbScreenInfo.cy */
    screen_info.width = func_001B4270();    /* VbScreenInfo.sx */
    screen_info.height = func_001B4290();   /* VbScreenInfo.sy */
}

void* kari_shLensFlareDraw(void) {
    int center_visible_f; // r16
    int count = *T0_COUNT; // r2
    float add_rate; // r29+0x40
    float add_rate_scaled; // @ note not in dwarf

    kari_Thr_LFD2TextureSend();
    shLensFlareExec(NULL, D_0038A3E0, 0, 0);
    D_0038A3E0 = 1.0f;
    if (!light_flare_work->lfl_sync_draw_func_exec_f) {
        return NULL;
    }
    light_flare_work->lfl_sync_draw_func_exec_f = 0;
    if (light_flare_work->flare_inhibit_f) {
        return NULL;
    }

    // @sh3 is `!GET_BIT(item.flag[0], 15) && sh2gde_CheckSpot_JmsOrBG()` in the sh2 proto?
    if ((func_00239450() == 0) || (func_002394F0() <= 0.01f)) {
        return NULL;
    }

    center_visible_f = shLensFlareLightCenterIsVisible(&light_flare_work);
    if (center_visible_f != 0) {
        add_rate = light_flare_work->tgt_l_eff_rate - light_flare_work->now_l_eff_rate;
    } else {
        add_rate = -light_flare_work->now_l_eff_rate;
    }

    add_rate_scaled = add_rate * 0.3f; // @sh3 was a double in the sh2 proto, maybe fixed in sh2 retail?
    light_flare_work->now_l_eff_rate += add_rate_scaled;
    if (shLensFlareCameraIsSmooth() == 0) {
        light_flare_work->now_l_eff_rate = 0.0f;
        center_visible_f = 0;
    }
    return kari_shLensFlareEffect_Draw(center_visible_f, &light_flare_work, &screen_info, 0);
}

static void shLensFlareSetAlphaEnvironment(sceVif1Packet* packet) {
    u_long giftag_alpha[2] = {
        SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1),
        GIF_REG(SCE_GIF_PACKED_AD, 0) | GIF_REG(SCE_GS_PRIM, 1) | GIF_REG(SCE_GS_PRIM, 2) | GIF_REG(SCE_GS_PRIM, 3)
    };
    sceVif1PkOpenGifTag(packet, *(u_long128*) &giftag_alpha);
    sceVif1PkAddGsAD(packet, SCE_GS_TEXFLUSH, 0);
    sceVif1PkAddGsAD(packet, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(0, 2, 0, 1, 0x80));
    sceVif1PkAddGsAD(packet, SCE_GS_TEST_1, SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 2));
    sceVif1PkAddGsAD(packet, SCE_GS_ZBUF_1, SCE_GS_SET_ZBUF(func_001D0670(), 58, 1));
    sceVif1PkAddGsAD(packet, SCE_GS_FRAME_1, SCE_GS_SET_FBA(*func_001D0720()));
    sceVif1PkCloseGifTag(packet);
}

void* kari_shLensFlareEffect_Draw(int center_visible_f, LensFlareWork* lf_work, ScreenInfo* sc_info, int arg3) {
    IVector4 color;
    IVector4 prim_p[4];
    float temp_f20          = func_001B4170();
    float temp_f21          = func_001B41C0();
    static float D_0038A410 = 0.039999999f;

    Vector4 prim_st[7][2] = {
        0.0, 0.0, 0.0, 0.0,
        0.5, 0.5, 0.0, 0.0,
        0.5, 0.0, 0.0, 0.0,
        1.0, 0.5, 0.0, 0.0,
        0.25, 0.5, 0.0, 0.0,
        0.625, 1.0, 0.0, 0.0,
        0.625, 0.5, 0.0, 0.0,
        1.0, 1.0, 0.0, 0.0,
        0.054699998, 0.5547, 0.0, 0.0,
        0.25, 0.5547, 0.0, 0.0,
        0.054699998, 1.0, 0.0, 0.0,
        0.25, 1.0, 0.0, 0.0,
        0.0, 0.5, 0.0, 0.0,
        0.25, 1.0, 0.0, 0.0
    };

    float hensin_x;
    float hensin_y;
    float r;
    float hensin_rate_x;
    float hensin_rate_y;
    int no;
    int i1;
    int i2;

    float add_flare_ang;
    float add_mask_ang;
    float line_r;
    sceVif1Packet* vif1pk;
    sceVif1Packet vif1packet;
    Vector4 pos[4];
    int repeat_num;
    int flare_drawn;

    float base_vector[7] = {0.4f, 0.2f, -0.3f, -0.69999999f, -1.4f, -2.2f, -2.5f};
    float base_r[7]      = {12.0f, 10.0f, 28.0f, 20.0f, 20.0f, 58.0f, 50.0f};
    int base_st_index[7] = {3, 2, 2, 3, 2, 3, 6};

    IVector4 base_color[7] = {
        0x48, 0x30, 0x48, 0x00,
        0x28, 0x2c, 0x2c, 0x00,
        0x28, 0x2e, 0x28, 0x00,
        0x24, 0x24, 0x24, 0x00,
        0x28, 0x28, 0x20, 0x00,
        0x40, 0x30, 0x28, 0x00,
        0x80, 0x80, 0x80, 0x00
    };
    static u_short D_0038A5D0 = 100;

    float _rate;
    float add_ang, add_ang2;

    vif1pk = &vif1packet;
    sceVif1PkInit(vif1pk, kari_kick_packet);

    sceVif1PkCnt(vif1pk, 0);
    sceVif1PkAddCode(vif1pk, SCE_VIF1_SET_FLUSH(0));
    sceVif1PkOpenDirectCode(vif1pk, false);

    shLensFlareGetScreenInfo();

    flare_drawn = 0;
    for (no = 0; no < 1; no++, lf_work++) {

        if ((lf_work->scr_l_pos.x >= (sc_info->center_x - sc_info->width)) &&
            (lf_work->scr_l_pos.x <= (sc_info->center_x + sc_info->width)) &&
            (!(lf_work->scr_l_pos.y < (sc_info->center_y - sc_info->height)) && (lf_work->scr_l_pos.y <= (sc_info->center_y + sc_info->height)))) {

            flare_drawn = 1;

            line_r = 128.0f - SQRT(1.5f * lf_work->scr_l_pos.z);
            if (line_r < 0.0f)
                line_r = 0.0f;

            shLensFlareSetAlphaEnvironment(vif1pk);

            hensin_rate_x = sinf(lf_work->scr_l_ang_xy) * cosf(lf_work->scr_l_ang_xy);
            hensin_rate_y = sinf(lf_work->scr_l_ang_z) * sinf(lf_work->scr_l_ang_xy);

            if (func_002394F0() /* Env_ctl.SpotL0.color.fl32[0] */ >= D_0038A410) {

                hensin_x = 5.0f * hensin_rate_x;
                hensin_y = 5.0f * hensin_rate_y;

                set_color_clamped(&color, (lf_work->now_l_eff_rate + 3.0f) * 0.25f, 40.0f, 40.0f, 38.0f);
                if (no != 0) {
                    color.x = (int) ((float) color.x * reverse_light_rate);
                    color.y = (int) ((float) color.y * reverse_light_rate);
                    color.z = (int) ((float) color.z * reverse_light_rate);
                }
                if ((center_visible_f != 0) || (no != 0))
                    r = line_r * ((2.0f + lf_work->now_l_eff_rate) * 0.25f);
                else
                    r = (lf_work->l_screen_pos.z * (3.5f * (line_r * (0.25f * (2.0f + lf_work->now_l_eff_rate))))) / 65536.0f;

                prim_p[0].x = lf_work->l_screen_pos.x - (int) (temp_f20 * (16.0f * (-hensin_x + r)));
                prim_p[0].y = lf_work->l_screen_pos.y - (int) ((512.0f * (temp_f21 * (16.0f * (-hensin_y + r))) / 448.0f));
                prim_p[1].x = lf_work->l_screen_pos.x + (int) (temp_f20 * (16.0f * (hensin_x + r)));
                prim_p[1].y = lf_work->l_screen_pos.y + (int) ((512.0f * (temp_f21 * (16.0f * (hensin_y + r))) / 448.0f));
                prim_p[0].w = prim_p[1].w = prim_p[2].w = prim_p[3].w = 1;

                if ((center_visible_f != 0) || (no != 0)) {

                    prim_p[0].z = prim_p[1].z = 0xFFFC;
                } else if (lf_work->scr_l_ang_z > QUARTER_TURN) {

                    prim_p[0].z = prim_p[1].z = lf_work->l_screen_pos.z + D_0038A5D0; // @sh3

                } else {

                    prim_p[0].z = prim_p[1].z = lf_work->l_screen_pos.z;
                }

                shLensFlareSpriteAddPacketGif(vif1pk, &color, &prim_p[0], &prim_p[1], &prim_st[0][0], &prim_st[0][1]);

                color.x = color.y = color.z = 0x20;
                if (no != 0) {
                    color.x = (int) ((float) color.x * reverse_light_rate);
                    color.y = (int) ((float) color.y * reverse_light_rate);
                    color.z = (int) ((float) color.z * reverse_light_rate);
                }
                prim_p[0].x = lf_work->l_screen_pos.x - (int) (176.0f * temp_f20);
                prim_p[0].y = lf_work->l_screen_pos.y - (int) ((512.0f * (176.0f * temp_f21)) / 448.0f);
                prim_p[1].x = lf_work->l_screen_pos.x + (int) (176.0f * temp_f20);
                prim_p[1].y = lf_work->l_screen_pos.y + (int) ((512.0f * (176.0f * temp_f21)) / 448.0f);

                if ((center_visible_f != 0) || (no != 0)) {

                    prim_p[0].z = prim_p[1].z = 0xFFFC;
                } else if (lf_work->scr_l_ang_z > QUARTER_TURN) {
                    prim_p[0].z = prim_p[1].z = lf_work->l_screen_pos.z;
                    ;
                } else {

                    prim_p[0].z = prim_p[1].z = lf_work->l_screen_pos.z;
                }

                shLensFlareSpriteAddPacketGif(vif1pk, &color, &prim_p[0], &prim_p[1], &prim_st[0][0], &prim_st[0][1]);

                hensin_x = 9.0f * hensin_rate_x;
                hensin_y = 9.0f * hensin_rate_y;
                set_color_clamped(&color, (1.0f > (2.0f * lf_work->now_l_eff_rate)) ? 2.0f * lf_work->now_l_eff_rate : 1.0f, 40.0f, 40.0f, 40.0f);
                if (no != 0) {
                    color.x = (int) ((float) color.x * reverse_light_rate);
                    color.y = (int) ((float) color.y * reverse_light_rate);
                    color.z = (int) ((float) color.z * reverse_light_rate);
                }
                r           = 2.0f * (0.5f * line_r * ((3.0f + lf_work->now_l_eff_rate) / 4.0f));
                prim_p[0].x = lf_work->l_screen_pos.x - (int) (temp_f20 * (16.0f * (-hensin_x + r)));
                prim_p[0].y = lf_work->l_screen_pos.y - (int) ((512.0f * (temp_f21 * (16.0f * (-hensin_y + r))) / 448.0f));
                prim_p[1].x = lf_work->l_screen_pos.x + (int) (temp_f20 * (16.0f * (hensin_x + r)));
                prim_p[1].y = lf_work->l_screen_pos.y + (int) ((512.0f * (temp_f21 * (16.0f * (hensin_y + r))) / 448.0f));

                prim_p[1].z = 0xFFFC;
                prim_p[0].z = 0xFFFC;
                shLensFlareSpriteAddPacketGif(vif1pk, &color, &prim_p[0], &prim_p[1], &prim_st[1][0], &prim_st[1][1]);
            }

            if (lf_work->now_l_eff_rate > 0.001f) {

                if (no == 0) {
                    static float ang_dat_0[4] = {-PI, -QUARTER_TURN, 0.0f, QUARTER_TURN}; // @ 0x002AE2A0

                    pos[0].x = -(line_r * 0.061f);
                    pos[0].y = -(line_r * 0.03f);
                    pos[1].x = line_r - (line_r * 0.061f);
                    pos[1].y = -(line_r * 0.03f);
                    pos[2].x = -(line_r * 0.061f);
                    pos[2].y = line_r - (line_r * 0.03f);
                    pos[3].x = line_r - (line_r * 0.061f);
                    pos[3].y = line_r - (line_r * 0.03f);

                    for (i1      = 0,
                        add_ang  = ((lf_work->scr_l_pos.x + lf_work->scr_l_pos.y) * 0.006136f) + (-lf_work->scr_l_ang_z * 0.5f) + 1.0471976f,
                        add_ang2 = ((lf_work->scr_l_pos.x + lf_work->scr_l_pos.y) * 0.024544f) + (lf_work->scr_l_pos.z * 0.006136f);
                         i1 < 4; i1++) {
                        float sin_val, cos_val;

                        float ang = add_ang + ang_dat_0[i1];

                        sin_val = sinf(ang);
                        cos_val = cosf(ang);

                        prim_p[0].z = prim_p[1].z = prim_p[2].z = prim_p[3].z = 0xFFFA;

                        set_color_clamped(&color, lf_work->now_l_eff_rate, 28.0f, 28.0f, 28.0f);

                        prim_p[0].x = lf_work->l_screen_pos.x + (int) (temp_f20 * (16.0f * (pos[0].x * cos_val - pos[0].y * sin_val)));

                        prim_p[0].y = lf_work->l_screen_pos.y + (int) ((512.0f * (temp_f21 * (16.0f * (pos[0].x * sin_val + pos[0].y * cos_val))) / 448.0f));

                        prim_p[1].x = lf_work->l_screen_pos.x + (int) (temp_f20 * (16.0f * (pos[1].x * cos_val - pos[1].y * sin_val)));

                        prim_p[1].y = lf_work->l_screen_pos.y + (int) ((512.0f * (temp_f21 * (16.0f * (pos[1].x * sin_val + pos[1].y * cos_val))) / 448.0f));

                        prim_p[2].x = lf_work->l_screen_pos.x + (int) (temp_f20 * (16.0f * (pos[2].x * cos_val - pos[2].y * sin_val)));

                        prim_p[2].y = lf_work->l_screen_pos.y + (int) ((512.0f * (temp_f21 * (16.0f * (pos[2].x * sin_val + pos[2].y * cos_val))) / 448.0f));

                        prim_p[3].x = lf_work->l_screen_pos.x + (int) (temp_f20 * (16.0f * (pos[3].x * cos_val - pos[3].y * sin_val)));

                        prim_p[3].y = lf_work->l_screen_pos.y + (int) ((512.0f * (temp_f21 * (16.0f * (pos[3].x * sin_val + pos[3].y * cos_val))) / 448.0f));

                        shLensFlarePolyFT4AddPacketGif(vif1pk, &color, &prim_p[0], &prim_p[1], &prim_p[2], &prim_p[3], &prim_st[4][0], &prim_st[4][1], &prim_st[5][0], /* extra? */ &prim_st[5][1]);
                    }
                    i1 = 0;

                    {
                        for (add_ang = -(lf_work->scr_l_ang_z) / 2.0f + (((lf_work->scr_l_pos).x + (lf_work->scr_l_pos).y) * 0.006136f) + 1.0471976f, add_ang2 = (lf_work->scr_l_pos).z * 0.006136f +
                                                                                                                                                                 ((lf_work->scr_l_pos).x + (lf_work->scr_l_pos).y) * 0.024544f;
                             i1 < 0xC; i1++) {
                            static float ang_dat_1[12] = {
                                -2.9321532,
                                -2.268928,
                                -1.0471976,
                                -0.87266463,
                                -0.2617994,
                                0.34906587,
                                0.69813174,
                                1.2217306,
                                2.1293018,
                                2.5656343,
                                2.8797934,
                                0.0
                            }; // @ 0x002AE2B0
                            float cos_val, sin_val;
                            float _rate;
                            float ang = add_ang + ang_dat_1[i1];

                            _rate = (0.85f + cosf(ang - lf_work->scr_l_ang_xy)) * (0.5f * (0.5f + cosf((12.0f * ang) + add_ang2)));

                            _rate   = (0.75f > _rate) ? _rate : 0.75f;
                            sin_val = sinf(ang);
                            cos_val = cosf(ang);

                            prim_p[0].z = prim_p[1].z = prim_p[2].z = prim_p[3].z = 0xFFFC;

                            set_color_clamped(&color, lf_work->now_l_eff_rate * _rate, 16.0f, 16.0f, 16.0f);

                            prim_p[0].x = lf_work->l_screen_pos.x + (int) (temp_f20 * (16.0f * (pos[0].x * cos_val - pos[0].y * sin_val)));

                            prim_p[0].y = lf_work->l_screen_pos.y + (int) ((512.0f * (temp_f21 * (16.0f * (pos[0].x * sin_val + pos[0].y * cos_val))) / 448.0f));

                            prim_p[1].x = lf_work->l_screen_pos.x + (int) (temp_f20 * (16.0f * (pos[1].x * cos_val - pos[1].y * sin_val)));

                            prim_p[1].y = lf_work->l_screen_pos.y + (int) ((512.0f * (temp_f21 * (16.0f * (pos[1].x * sin_val + pos[1].y * cos_val))) / 448.0f));

                            prim_p[2].x = lf_work->l_screen_pos.x + (int) (temp_f20 * (16.0f * (pos[2].x * cos_val - pos[2].y * sin_val)));

                            prim_p[2].y = lf_work->l_screen_pos.y + (int) ((512.0f * (temp_f21 * (16.0f * (pos[2].x * sin_val + pos[2].y * cos_val))) / 448.0f));

                            prim_p[3].x = lf_work->l_screen_pos.x + (int) (temp_f20 * (16.0f * (pos[3].x * cos_val - pos[3].y * sin_val)));

                            prim_p[3].y = lf_work->l_screen_pos.y + (int) ((512.0f * (temp_f21 * (16.0f * (pos[3].x * sin_val + pos[3].y * cos_val))) / 448.0f));

                            shLensFlarePolyFT4AddPacketGif(vif1pk, &color, &prim_p[0], &prim_p[1], &prim_p[2], &prim_p[3], &prim_st[4][0], &prim_st[4][1], &prim_st[5][0], /* extra? */ &prim_st[5][1]);
                        }
                    }

                    for (i2 = 0; i2 < 6; i2++) {
                        shLensFlareDrawCommon(vif1pk, lf_work, sc_info, &base_color[i2], base_r[i2], base_vector[i2], &prim_st[base_st_index[i2]][0], &prim_st[base_st_index[i2]][1], 0xfffc);
                    }

                    set_color_clamped(&color, lf_work->now_l_eff_rate, 32.0f, 32.0f, 32.0f);
                    line_r      = 160.0f - SQRT(2.0f * lf_work->scr_l_pos.z);
                    r           = line_r;
                    D_01F2A6D0  = line_r;
                    prim_p[0].x = lf_work->l_screen_pos.x - (int) ((16.0f * line_r) * temp_f20);
                    prim_p[0].y = lf_work->l_screen_pos.y - (int) ((512.0f * ((16.0f * line_r) * temp_f21)) / 448.0f);
                    prim_p[1].x = lf_work->l_screen_pos.x + (int) ((16.0f * line_r) * temp_f20);
                    prim_p[1].y = lf_work->l_screen_pos.y + (int) ((512.0f * ((16.0f * line_r) * temp_f21)) / 448.0f);

                    prim_p[0].z = prim_p[1].z = 0xFFFC;
                    shLensFlareSpriteAddPacketGif(vif1pk, &color, &prim_p[0], &prim_p[1], &prim_st[0][0], &prim_st[0][1]);

                    set_color_clamped(&color, lf_work->now_l_eff_rate, 64.0f, 24.0f, 94.0f);
                    r           = 10.0f;
                    prim_p[0].x = lf_work->l_screen_pos.x - (int) ((160.0f * temp_f20));
                    prim_p[0].y = lf_work->l_screen_pos.y - (int) ((512.0f * (160.0f * temp_f21)) / 448.0f);
                    prim_p[1].x = lf_work->l_screen_pos.x + (int) ((160.0f * temp_f20));
                    prim_p[1].y = lf_work->l_screen_pos.y + (int) ((512.0f * (160.0f * temp_f21)) / 448.0f);
                    prim_p[0].z = prim_p[1].z = 0xFFFC;
                    shLensFlareSpriteAddPacketGif(vif1pk, &color, &prim_p[0], &prim_p[1], &prim_st[0][0], &prim_st[0][1]);
                }
            }
        }
    }

    if (flare_drawn != 0) {

        u_long giftag_Z[4] = {
            SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1),
            GIF_REG(SCE_GIF_PACKED_AD, 0) | GIF_REG(SCE_GS_PRIM, 1) | GIF_REG(SCE_GS_PRIM, 2) | GIF_REG(SCE_GS_PRIM, 3),
            0,
            0
        };
        sceVif1PkOpenGifTag(vif1pk, *(u_long128*) giftag_Z);

        sceVif1PkAddGsAD(vif1pk, SCE_GS_ZBUF_1, SCE_GS_SET_ZBUF(func_001D0670(), 58, 0));
        sceVif1PkAddGsAD(vif1pk, SCE_GS_FRAME_1, *func_001D0740());

        sceVif1PkCloseGifTag(vif1pk);

        sceVif1PkCloseDirectCode(vif1pk);
        sceVif1PkEnd(vif1pk, 0U);
        sceVif1PkTerminate(vif1pk);
        return vif1pk->pBase;
    }
    return NULL;
}

// @sh3 unchanged
static void shLensFlareSpriteAddPacketGif(sceVif1Packet* packet, IVector4* rgbaq, IVector4* xyz0, IVector4* xyz1, Vector4* stq0, Vector4* stq1) {
    IVector4 c  = *rgbaq; 
    IVector4 v0 = *xyz0; 
    IVector4 v1 = *xyz1; 
    Vector4 st0 = *stq0; 
    Vector4 st1 = *stq1; 
    u_long128* pTex0;    
    u_long giftag_alpha_test[2] = {
        SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 8),
        GIF_REG(SCE_GS_PRIM, 0)       |
            GIF_REG(SCE_GS_TEX0_1, 1) |
            GIF_REG(SCE_GS_ST, 2)     |
            GIF_REG(SCE_GS_RGBAQ, 3)  |
            GIF_REG(SCE_GS_XYZ2, 4)   |
            GIF_REG(SCE_GS_ST, 5)     |
            GIF_REG(SCE_GS_RGBAQ, 6)  |
            GIF_REG(SCE_GS_XYZ2, 7)   |
            GIF_REG(SCE_GS_PRIM, 8)   |
            GIF_REG(SCE_GS_PRIM, 9)   |
            GIF_REG(SCE_GS_PRIM, 10)  |
            GIF_REG(SCE_GS_PRIM, 11)  |
            GIF_REG(SCE_GS_PRIM, 12)  |
            GIF_REG(SCE_GS_PRIM, 13)
    }; 
    float q = 1.0f; 

    sceVif1PkOpenGifTag(packet, *(u_long128*) giftag_alpha_test);
    sceVif1PkAddGsData(packet,
                       SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE,
                                       true /* gouraud */,
                                       true /* texture mapping */,
                                       false,
                                       true /* alpha blending */,
                                       true /* antialiasing */,
                                       false, false, false));
    pTex0 = (u_long128*) &LF_Tex_Work.Tex0Data;
    sceVif1PkAddGsData(packet, ((u_long*) pTex0)[0]);
    sceVif1PkAddGsData(packet, SCE_GS_SET_ST(reinterpret_as_u_int(st0.x * q), reinterpret_as_u_int(st0.y * q)));
    sceVif1PkAddGsData(packet, SCE_GS_SET_RGBAQ(c.x, c.y, c.z, 0x80, *(u_int*) &q));
    sceVif1PkAddGsData(packet, SCE_GS_SET_XYZ(v0.x, v0.y, v0.z));
    sceVif1PkAddGsData(packet, SCE_GS_SET_ST(reinterpret_as_u_int(st1.x * q), reinterpret_as_u_int(st1.y * q)));
    sceVif1PkAddGsData(packet, SCE_GS_SET_RGBAQ(c.x, c.y, c.z, 0x80, *(u_int*) &q));
    sceVif1PkAddGsData(packet, SCE_GS_SET_XYZ(v1.x, v1.y, v1.z));
    sceVif1PkCloseGifTag(packet);
}


void Kari_LensFlare_DrawExec(void) {
    static Q_WORDDATA dum = {0x70000000};
    void* pak;
    
    
    // @sh3
    D_01F2A6D0 = 0;
    if ((func_00239450() == 0) || (func_002394F0() <= 0.01f)) {
        func_002397C0(&light_info->world_light_pos, &light_info->world_light_vector);
        shLensFlareExec(NULL, D_0038A3E0, 0, 0);
        shLensFlareLightCenterIsVisible(light_flare_work);
        light_flare_work->now_l_eff_rate = 0.0f;
        return;
    }


    pak  = kari_shLensFlareDraw(); 
    if (pak) {
        kari_Thr_LFD1D2SyncKick(pak);
        return;
    }
    kari_Thr_LFD1D2SyncKick(&dum);
}

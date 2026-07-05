#include "sh2_common.h"

#include "Lens/lens_flare.h"
#include "Lens/kari_lf_draw.h"

#include "libgraph.h"
#include "libvifpk.h"
#include "vec.h"

#include "GFW/sh2_DrawEnvData.h"

#define EFF_VALID_ID 0xEF04

static void shLensFlarePolyFT4AddPacketGif(sceVif1Packet* packet, IVector4*,  IVector4*, IVector4*, IVector4*, IVector4*, Vector4*, Vector4*, Vector4*, Vector4*); // @note many arguments not in dwarf
static void shLensFlareDrawCommon(sceVif1Packet* packet /* r21 */, LensFlareWork* lf_work /* r20 */, ScreenInfo* sc_info /* r19 */, IVector4* base_color /* r18 */, float base_r /* r20 */, float base_vector /* r22 */, Vector4*, Vector4*, u_short z_value /* r17 */);
static void shLensFlareGetScreenInfo(void) ;
static void shLensFlareSetAlphaEnvironment(sceVif1Packet* packet /* r16 */);
static void* kari_shLensFlareEffect_Draw(signed int center_visible_f /* r21 */, LensFlareWork* lf_work /* r20 */, ScreenInfo* sc_info /* r19 */, int unknown);
static void shLensFlareSpriteAddPacketGif(sceVif1Packet* packet, IVector4*, IVector4*, IVector4*, Vector4*, Vector4*); // @note many arguments not in dwarf

extern u_long128 kari_kick_packet[1280]; // size: 0x5000, address: 0x100E750

INCLUDE_ASM("asm/nonmatchings/Lens/kari_lf_draw", kari_Thr_LFD2TextureSend);

INCLUDE_ASM("asm/nonmatchings/Lens/kari_lf_draw", kari_Thr_LFD1D2SyncKick);

INCLUDE_ASM("asm/nonmatchings/Lens/kari_lf_draw", shLensFlarePolyFT4AddPacketGif);

INCLUDE_ASM("asm/nonmatchings/Lens/kari_lf_draw", shLensFlareDrawCommon);

INCLUDE_ASM("asm/nonmatchings/Lens/kari_lf_draw", shLensFlareGetScreenInfo);

static inline void set_color_clamped(IVector4* color, float c, float r, float g, float b) {
    color->x = (int) (r * c);
    color->y = (int) (g * c);
    color->z = (int) (b * c);

    if (color->x > 255) {
        color->x = 255;
    }
    if (color->y > 255) {
        color->y = 255;
    }
    if (color->z > 255) {
        color->z = 255;
    }
}

INCLUDE_ASM("asm/nonmatchings/Lens/kari_lf_draw", kari_shLensFlareDraw);

INCLUDE_ASM("asm/nonmatchings/Lens/kari_lf_draw", shLensFlareSetAlphaEnvironment);

void* kari_shLensFlareEffect_Draw(s32 center_visible_f, LensFlareWork* lf_work, ScreenInfo* sc_info, s32 arg3) {
    IVector4 color;     // r29+0xD0
    IVector4 prim_p[4]; // r29+0xE0

    Vector4 prim_st[7][2] = {
        0.0,
        0.0,
        0.0,
        0.0,
        0.5,
        0.5,
        0.0,
        0.0,
        0.5,
        0.0,
        0.0,
        0.0,
        1.0,
        0.5,
        0.0,
        0.0,
        0.25,
        0.5,
        0.0,
        0.0,
        0.625,
        1.0,
        0.0,
        0.0,
        0.625,
        0.5,
        0.0,
        0.0,
        1.0,
        1.0,
        0.0,
        0.0,
        0.054699998,
        0.5547,
        0.0,
        0.0,
        0.25,
        0.5547,
        0.0,
        0.0,
        0.054699998,
        1.0,
        0.0,
        0.0,
        0.25,
        1.0,
        0.0,
        0.0,
        0.0,
        0.5,
        0.0,
        0.0,
        0.25,
        1.0,
        0.0,
        0.0,
    }; // r29+0x120
    float hensin_x;      // r20
    float hensin_y;      // r21
    float r;             // r22
    float hensin_rate_x; // r23
    float hensin_rate_y; // r24
    int no;              // r16
    int i1;              // r17
    int i2;              // r16

    float add_flare_ang;      // r20
    float add_mask_ang;       // r21
    float line_r;             // r25
    sceVif1Packet* vif1pk;    // r18
    sceVif1Packet vif1packet; // r29+0x200
    Vector4 pos[4];           // r29+0x220
    int repeat_num;           // r23
    int flare_drawn;          // r30

    float base_vector[7] = {0.4f, 0.2f, -0.3f, -0.69999999f, -1.4f, -2.2f, -2.5f}; // r29+0x260
    float base_r[7]      = {12.0f, 10.0f, 28.0f, 20.0f, 20.0f, 58.0f, 50.0f};      // r29+0x280
    int base_st_index[7] = {3, 2, 2, 3, 2, 3, 6};                                  // r29+0x2A0

    u_short z_value[7]     = {0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff}; // r29+0x340
    IVector4 base_color[7] = {
        0x48, 0x30, 0x48, 0x00,
        0x28, 0x2c, 0x2c, 0x00,
        0x28, 0x2e, 0x28, 0x00,
        0x24, 0x24, 0x24, 0x00,
        0x28, 0x28, 0x20, 0x00,
        0x40, 0x30, 0x28, 0x00,
        0x80, 0x80, 0x80, 0x00
    }; // r29+0x2C0

    float _rate; // r20
    float add_ang, add_ang2;
    vif1pk = &vif1packet;
    sceVif1PkInit(vif1pk, kari_kick_packet);

    sceVif1PkCnt(vif1pk, 0);
    sceVif1PkAddCode(vif1pk, SCE_VIF1_SET_FLUSH(0));
    sceVif1PkOpenDirectCode(vif1pk, false);

    shLensFlareGetScreenInfo();

    if (PlayerReverseLightCalcIsOn()) {
        repeat_num = 2;
    } else {
        repeat_num = 1;
    }

    flare_drawn = 0;
    for (i2 = 0; i2 < repeat_num; i2++, lf_work++) {

        if ((lf_work->scr_l_pos.x >= (sc_info->center_x - sc_info->width)) &&
            (lf_work->scr_l_pos.x <= (sc_info->center_x + sc_info->width)) &&
            (!(lf_work->scr_l_pos.y < (sc_info->center_y - sc_info->height)) && (lf_work->scr_l_pos.y <= (sc_info->center_y + sc_info->height)))) {

            flare_drawn = 1;

            line_r = 128.0f - SQRT(1.5 * lf_work->scr_l_pos.z);
            if (line_r < 0.0f)
                line_r = 0.0f;

            shLensFlareSetAlphaEnvironment(vif1pk);

            hensin_rate_x = sinf(lf_work->scr_l_ang_xy) * cosf(lf_work->scr_l_ang_xy);
            hensin_rate_y = sinf(lf_work->scr_l_ang_z) * sinf(lf_work->scr_l_ang_xy);

            if (Env_ctl.SpotL0.color.fl32[0] >= 0.002f) {

                hensin_x = 5.0f * hensin_rate_x;
                hensin_y = 5.0f * hensin_rate_y;

                set_color_clamped(&color, (lf_work->now_l_eff_rate + 3.0) * 0.25, 40.0f, 40.0f, 38.0f);
                if (i2 != 0) {
                    color.x = (int) ((float) color.x * reverse_light_rate);
                    color.y = (int) ((float) color.y * reverse_light_rate);
                    color.z = (int) ((float) color.z * reverse_light_rate);
                }
                r = line_r * (0.25f * (2.0f + lf_work->now_l_eff_rate));

                prim_p[0].x = lf_work->l_screen_pos.x - (int) (16.0f * (-hensin_x + r));
                prim_p[0].y = lf_work->l_screen_pos.y - (int) ((512.0f * (16.0f * (-hensin_y + r))) / 448.0f);
                prim_p[1].x = lf_work->l_screen_pos.x + (int) (16.0f * (hensin_x + r));
                prim_p[1].y = lf_work->l_screen_pos.y + (int) ((512.0f * (16.0f * (hensin_y + r))) / 448.0f);
                prim_p[0].w = prim_p[1].w = prim_p[2].w = prim_p[3].w = 1;

                if ((center_visible_f != 0) && (i2 == 0)) {

                    prim_p[0].z = prim_p[1].z = 0xFFFF;
                } else if (lf_work->scr_l_ang_z > QUARTER_TURN) {

                    prim_p[0].z = prim_p[1].z = lf_work->l_screen_pos.z;

                } else {

                    prim_p[0].z = prim_p[1].z = lf_work->l_screen_pos.z;
                }

                shLensFlareSpriteAddPacketGif(vif1pk, &color, &prim_p[0], &prim_p[1], &prim_st[0][0], &prim_st[0][1]);

                color.x = color.y = color.z = 0x20;
                if (i2 != 0) {
                    color.x = (int) ((float) color.x * reverse_light_rate);
                    color.y = (int) ((float) color.y * reverse_light_rate);
                    color.z = (int) ((float) color.z * reverse_light_rate);
                }
                prim_p[0].x = lf_work->l_screen_pos.x - 0xB0;
                prim_p[0].y = lf_work->l_screen_pos.y - 0xC9;
                prim_p[1].x = lf_work->l_screen_pos.x + 0xB0;
                prim_p[1].y = lf_work->l_screen_pos.y + 0xC9;

                if ((center_visible_f != 0) && (i2 == 0)) {

                    prim_p[0].z = prim_p[1].z = 0xFFFF;
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
                if (i2 != 0) {
                    color.x = (int) ((float) color.x * reverse_light_rate);
                    color.y = (int) ((float) color.y * reverse_light_rate);
                    color.z = (int) ((float) color.z * reverse_light_rate);
                }
                r           = 2.0f * (0.5f * line_r * ((3.0f + lf_work->now_l_eff_rate) / 4.0f));
                prim_p[0].x = lf_work->l_screen_pos.x - (int) (16.0f * (-hensin_x + r));
                prim_p[0].y = lf_work->l_screen_pos.y - (int) ((512.0f * (16.0f * (-hensin_y + r))) / 448.0f);
                prim_p[1].x = lf_work->l_screen_pos.x + (int) (16.0f * (hensin_x + r));
                prim_p[1].y = lf_work->l_screen_pos.y + (int) ((512.0f * (16.0f * (hensin_y + r))) / 448.0f);

                prim_p[1].z = 0xFFFF;
                prim_p[0].z = 0xFFFF;
                shLensFlareSpriteAddPacketGif(vif1pk, &color, &prim_p[0], &prim_p[1], &prim_st[1][0], &prim_st[1][1]);
            }

            if (lf_work->now_l_eff_rate > 0.001f) {

                if (i2 == 0) {
                    static float ang_dat_1030[4] = {-PI, -QUARTER_TURN, 0.0f, QUARTER_TURN}; // @ 0x002AE2A0

                    pos[0].x = -(line_r * 0.061);
                    pos[0].y = -(line_r * 0.03);
                    pos[1].x = line_r - (line_r * 0.061);
                    pos[1].y = -(line_r * 0.03);
                    pos[2].x = -(line_r * 0.061);
                    pos[2].y = line_r - (line_r * 0.03);
                    pos[3].x = line_r - (line_r * 0.061);
                    pos[3].y = line_r - (line_r * 0.03);

                    for (i1      = 0,
                        add_ang  = ((lf_work->scr_l_pos.x + lf_work->scr_l_pos.y) * 0.006136) + (-lf_work->scr_l_ang_z * 0.5f) + 1.0471976f,
                        add_ang2 = ((lf_work->scr_l_pos.x + lf_work->scr_l_pos.y) * 0.024544) + (lf_work->scr_l_pos.z * 0.006136);
                         i1 < 4; i1++) {
                        float sin_val, cos_val;

                        float ang = add_ang + ang_dat_1030[i1];

                        sin_val = sinf(ang);
                        cos_val = cosf(ang);

                        prim_p[0].z = prim_p[1].z = prim_p[2].z = prim_p[3].z = 0xFFFF;

                        set_color_clamped(&color, lf_work->now_l_eff_rate, 28.0f, 28.0f, 28.0f);

                        prim_p[0].x = lf_work->l_screen_pos.x + (int) (16.0f * (pos[0].x * cos_val - pos[0].y * sin_val));

                        prim_p[0].y = lf_work->l_screen_pos.y + (int) ((512.0f * (16.0f * (pos[0].x * sin_val + pos[0].y * cos_val))) / 448.0f);

                        prim_p[1].x = lf_work->l_screen_pos.x + (int) (16.0f * (pos[1].x * cos_val - pos[1].y * sin_val));

                        prim_p[1].y = lf_work->l_screen_pos.y + (int) ((512.0f * (16.0f * (pos[1].x * sin_val + pos[1].y * cos_val))) / 448.0f);

                        prim_p[2].x = lf_work->l_screen_pos.x + (int) (16.0f * (pos[2].x * cos_val - pos[2].y * sin_val));

                        prim_p[2].y = lf_work->l_screen_pos.y + (int) ((512.0f * (16.0f * (pos[2].x * sin_val + pos[2].y * cos_val))) / 448.0f);

                        prim_p[3].x = lf_work->l_screen_pos.x + (int) (16.0f * (pos[3].x * cos_val - pos[3].y * sin_val));

                        prim_p[3].y = lf_work->l_screen_pos.y + (int) ((512.0f * (16.0f * (pos[3].x * sin_val + pos[3].y * cos_val))) / 448.0f);

                        shLensFlarePolyFT4AddPacketGif(vif1pk, &color, &prim_p[0], &prim_p[1], &prim_p[2], &prim_p[3], &prim_st[4][0], &prim_st[4][1], &prim_st[5][0], /* extra? */ &prim_st[5][1]);
                    }
                    i1 = 0;


                    {
                        for (add_ang = -(lf_work->scr_l_ang_z) / 2.0f + (((lf_work->scr_l_pos).x + (lf_work->scr_l_pos).y) * 0.006136) + 1.0471976f, add_ang2 = (lf_work->scr_l_pos).z * 0.006136 +
                                                                                                                                                                ((lf_work->scr_l_pos).x + (lf_work->scr_l_pos).y) * 0.024544;
                             i1 < 0xC; i1++) {
                            static float ang_dat_1042[12] = {
                                -2.9321532,
                                -2.268928 ,
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
                            float ang = add_ang + ang_dat_1042[i1];

                            _rate = (0.85f + cosf(ang - lf_work->scr_l_ang_xy)) * (0.5f * (0.5f + cosf((12.0f * ang) + add_ang2)));

                            _rate   = (0.75f > _rate) ? _rate : 0.75f;
                            sin_val = sinf(ang);
                            cos_val = cosf(ang);

                            prim_p[0].z = prim_p[1].z = prim_p[2].z = prim_p[3].z = 0xFFFF;

                            set_color_clamped(&color, lf_work->now_l_eff_rate * _rate, 16.0f, 16.0f, 16.0f);

                            prim_p[0].x = lf_work->l_screen_pos.x + (int) (16.0f * (pos[0].x * cos_val - pos[0].y * sin_val));

                            prim_p[0].y = lf_work->l_screen_pos.y + (int) ((512.0f * (16.0f * (pos[0].x * sin_val + pos[0].y * cos_val))) / 448.0f);

                            prim_p[1].x = lf_work->l_screen_pos.x + (int) (16.0f * (pos[1].x * cos_val - pos[1].y * sin_val));

                            prim_p[1].y = lf_work->l_screen_pos.y + (int) ((512.0f * (16.0f * (pos[1].x * sin_val + pos[1].y * cos_val))) / 448.0f);

                            prim_p[2].x = lf_work->l_screen_pos.x + (int) (16.0f * (pos[2].x * cos_val - pos[2].y * sin_val));

                            prim_p[2].y = lf_work->l_screen_pos.y + (int) ((512.0f * (16.0f * (pos[2].x * sin_val + pos[2].y * cos_val))) / 448.0f);

                            prim_p[3].x = lf_work->l_screen_pos.x + (int) (16.0f * (pos[3].x * cos_val - pos[3].y * sin_val));

                            prim_p[3].y = lf_work->l_screen_pos.y + (int) ((512.0f * (16.0f * (pos[3].x * sin_val + pos[3].y * cos_val))) / 448.0f);

                            shLensFlarePolyFT4AddPacketGif(vif1pk, &color, &prim_p[0], &prim_p[1], &prim_p[2], &prim_p[3], &prim_st[4][0], &prim_st[4][1], &prim_st[5][0], /* extra? */ &prim_st[5][1]);
                        }
                    }

                    for (i1 = 0; i1 < 6; i1++) {
                        shLensFlareDrawCommon(vif1pk, lf_work, sc_info, &base_color[i1], base_r[i1], base_vector[i1], &prim_st[base_st_index[i1]][0], &prim_st[base_st_index[i1]][1], z_value[i1]);
                    }

                    set_color_clamped(&color, lf_work->now_l_eff_rate, 32.0f, 32.0f, 32.0f);
                    line_r      = 160.0f - SQRT(2.0f * lf_work->scr_l_pos.z);
                    r           = line_r;
                    prim_p[0].x = lf_work->l_screen_pos.x - (int) (16.0f * line_r);
                    prim_p[0].y = lf_work->l_screen_pos.y - (int) ((512.0f * (16.0f * r)) / 448.0f);
                    prim_p[1].x = lf_work->l_screen_pos.x + (int) (16.0f * r);
                    prim_p[1].y = lf_work->l_screen_pos.y + (int) ((512.0f * (16.0f * r)) / 448.0f);

                    prim_p[0].z = prim_p[1].z = 0xFFFF;
                    shLensFlareSpriteAddPacketGif(vif1pk, &color, &prim_p[0], &prim_p[1], &prim_st[0][0], &prim_st[0][1]);

                    set_color_clamped(&color, lf_work->now_l_eff_rate, 64.0f, 24.0f, 94.0f);
                    r           = 10.0f;
                    prim_p[0].x = lf_work->l_screen_pos.x - (int) ((r * 16.0f));
                    prim_p[0].y = lf_work->l_screen_pos.y - (int) ((512.0f * (16.0f * r)) / 448.0f);
                    prim_p[1].x = lf_work->l_screen_pos.x + (int) ((16.0f * r));
                    prim_p[1].y = lf_work->l_screen_pos.y + (int) ((512.0f * (16.0f * r)) / 448.0f);
                    prim_p[0].z = prim_p[1].z = 0xFFFF;
                    shLensFlareSpriteAddPacketGif(vif1pk, &color, &prim_p[0], &prim_p[1], &prim_st[0][0], &prim_st[0][1]);
                }
            }
        }
    }

    if (flare_drawn != 0) {

        u_long giftag_Z[2] = {
            SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1),
            GIF_REG(SCE_GIF_PACKED_AD, 0) | GIF_REG(SCE_GS_PRIM, 1) | GIF_REG(SCE_GS_PRIM, 2) | GIF_REG(SCE_GS_PRIM, 3)};
        sceVif1PkOpenGifTag(vif1pk, *(u_long128*) giftag_Z);

        sceVif1PkAddGsAD(vif1pk, SCE_GS_ZBUF_1, SCE_GS_SET_ZBUF(448, 58, 1));

        sceVif1PkCloseGifTag(vif1pk);

        sceVif1PkCloseDirectCode(vif1pk);
        sceVif1PkEnd(vif1pk, 0U);
        sceVif1PkTerminate(vif1pk);
        return vif1pk->pBase;
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/Lens/kari_lf_draw", shLensFlareSpriteAddPacketGif);

INCLUDE_ASM("asm/nonmatchings/Lens/kari_lf_draw", Kari_LensFlare_DrawExec);

#include "sh2_common.h"
#include "SH2_common/sh2dt.h"

#include "math.h"
#include "gs.h"

#include "sce/eeregs.h"
#include "sce/libgraph.h"

#include "Event/event.h"

#include "GFW/sh2gfw_macros.h"
#include "GFW/sh2_DrawEnvData.h"
#include "GFW/sh2_GsAllEnv.h"
#include "GFW/sh2gfw_2d_filters.h"
#include "shGs/sh2gfw_GS_NewLoopEnv.h"

#define SH2_GS_FILTER_KIND_BLUR                 2
#define SH2_GS_FILTER_KIND_GLOW_BLUR            3
#define SH2_GS_FILTER_KIND_DARK_BLUR            4
#define SH2_GS_FILTER_KIND_SWAP_SOFT            5
#define SH2_GS_FILTER_KIND_GLOW_SOFT_6          6
#define SH2_GS_FILTER_KIND_GLOW_SOFT_7          7
#define SH2_GS_FILTER_KIND_SWAP_SOFT_8          8
#define SH2_GS_FILTER_KIND_SWAP_SOFT_9          9
#define SH2_GS_FILTER_KIND_SWAP_SOFT_10         10
#define SH2_GS_FILTER_KIND_FADE2_COLOR1         14
#define SH2_GS_FILTER_KIND_FADE2_COLOR0         15
#define SH2_GS_FILTER_KIND_FADEOUT_RETAIN_BORW2 16
#define SH2_GS_FILTER_KIND_FADEOUT_RETAIN_BORW1 17
#define SH2_GS_FILTER_KIND_FADEOUT_RETAIN_BORW0 18
#define SH2_GS_FILTER_KIND_FADE2_19             19
#define SH2_GS_FILTER_KIND_FADE2_20             20
#define SH2_GS_FILTER_KIND_FADE3                21
#define SH2_GS_FILTER_KIND_COPY_AND_RESET       22
#define SH2_GS_FILTER_KIND_RETAIN               23

// @todo: how did they write this?
#define SH2_FIO_RATIO 4.269999980926514

static void sh2gfw_Copy_FrameToWork(Q_WORDDATA** ppqwd);

/* @todo: find homes for these */
extern Q_WORDDATA Noise_Packet[160]; // size: 0xA00, address: 0x616020
extern Q_WORDDATA CalcTex_buffer[2304]; // size: 0x9000, address: 0xE40280
extern double fabs(double);

static inline void copy_drawenv_frame_mskalpha(Q_WORDDATA* qwd, int index) {
    shGsDrawEnv* env = &shGs_AllEnv.DrawEnv[index];
    qwd->ul128 = env->frame_mskalpha.ul128;
}

static inline void copy_defaultenv(Q_WORDDATA* qwd, int index) {
    Q_WORDDATA* env = &shGs_AllEnv.DefaultEnv[index];
    qwd->ul128 = env->ul128;
}

void sh2gfw_Copy_FrameToWork(Q_WORDDATA** ppqwd) {
    int id = 0;
    Q_WORDDATA* qwd = *ppqwd;
    int idd[3] = {2, 0, 1};

    SET_DMATAG(qwd, id, DMAcnt | 8, 0, SCE_VIF1_SET_NOP(0), SCE_VIF1_SET_DIRECT(8, 0));
    SET_GIFTAG(qwd, id, SCE_GIF_SET_TAG(7, SCE_GS_TRUE, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD);
    
    SET_ADDRESS_DATA(qwd, id, SCE_GS_TEXFLUSH, 0);
    SET_ADDRESS_DATA(qwd, id, SCE_GS_TEST_1, SCE_GS_SET_TEST(SCE_GS_FALSE, SCE_GS_ALPHA_ALWAYS, 0, 0, 0, 1, SCE_GS_TRUE, SCE_GS_DEPTH_ALWAYS));
    SET_ADDRESS_DATA(qwd, id, SCE_GS_ZBUF_1, SCE_GS_SET_ZBUF(448, SCE_GS_PSMZ16S, SCE_GS_TRUE));
    qwd[id].ui32[0] = SCE_GS_SET_FRAME(416, 1, SCE_GS_PSMCT32, 0); qwd[id].ui32[1] = 0; qwd[id++].ul64[1] = SCE_GS_FRAME_1;
    SET_ADDRESS_DATA(qwd, id, SCE_GS_TEX0_1, SCE_GS_SET_TEX0(sh2gfw_GetNowDispFBP(&shGs_AllEnv) << 5, 8, SCE_GS_PSMCT32, 9, 9, SCE_GS_TRUE /* rgba */, Env_ctl.CopyFilterColor.ui32[1], 0, 0, 0, 0, 0));
    qwd[id].ul64[0] = SCE_GS_SET_TEX1(0, 0, 0, 0, 0, 0, 0); qwd[id++].ul64[1] = SCE_GS_TEX1_1;
    SET_ADDRESS_DATA(qwd, id, SCE_GS_XYOFFSET_1, SH_GIF_PACK_XY(Q4(2016.0f), Q4(2016.0f)));
    
    SET_DMATAG(qwd, id, DMAcnt | 9, 0, SCE_VIF1_SET_NOP(0), SCE_VIF1_SET_DIRECT(9, 0));
    qwd[id].ul64[0] = SCE_GIF_SET_TAG(1, SCE_GS_TRUE, SCE_GS_TRUE, SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, /* Texture Mapping */ SCE_GS_TRUE, 0, /* Alpha Blend */ 0, 0, /* Use ST */ SCE_GS_TRUE, 0, 0), SCE_GIF_PACKED, 8);
    qwd[id++].ul64[1] = GIF_REGLIST(SCE_GS_UV, SCE_GS_RGBAQ, SCE_GS_XYZ2, SCE_GS_UV, SCE_GS_RGBAQ, SCE_GS_XYZ2, SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD);
    SH_GIF_SET_XYZ(qwd, id, Q4(2.0f), Q4(2.0f), 0, SCE_GS_FALSE);

    // @note not a macro or inline according to the line numbers
    qwd[id]  .ui32[0] = Env_ctl.CopyFilterColor.uc8[0];
    qwd[id]  .ui32[1] = Env_ctl.CopyFilterColor.uc8[1];
    qwd[id]  .ui32[2] = Env_ctl.CopyFilterColor.uc8[2];
    qwd[id++].ui32[3] = Env_ctl.CopyFilterColor.uc8[3];

    SH_GIF_SET_XYZ(qwd, id, Q4(2016.0f), Q4(2016.0f), 1, SCE_GS_FALSE);
    qwd[id].ul64[0] = SH_GIF_PACK_UV(Q4(510.0f), Q4(510.0f)); qwd[id++].ul64[1] = 0;

    // @note not a macro or inline according to the line numbers
    qwd[id]  .ui32[0] = Env_ctl.CopyFilterColor.uc8[0];
    qwd[id]  .ui32[1] = Env_ctl.CopyFilterColor.uc8[1];
    qwd[id]  .ui32[2] = Env_ctl.CopyFilterColor.uc8[2];
    qwd[id++].ui32[3] = Env_ctl.CopyFilterColor.uc8[3];

    SH_GIF_SET_XYZ(qwd, id, Q4(2080.0f), Q4(2080.0f), 1, SCE_GS_FALSE);
    copy_drawenv_frame_mskalpha(qwd + id++, idd[shGs_AllEnv.loop3]);
    SET_ADDRESS_DATA(qwd, id, SCE_GS_XYOFFSET_1, SH_GIF_PACK_XY(Q4(1792.0f), Q4(1792.0f)));

    qwd += id;
    SET_DMA_RET(qwd);

    *ppqwd = qwd;
}


void sh2gfw_Filter_JustCopy2(Q_WORDDATA** ppqwd) {
    int id = 0;
    int tx, ty;
    Q_WORDDATA* qwd;
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    qwd = *ppqwd;

    SET_DMATAG(qwd, id, DMAcnt | 7, 0, SCE_VIF1_SET_NOP(0), SCE_VIF1_SET_DIRECT(7, 0));
    
    SET_GIFTAG(qwd, id, SCE_GIF_SET_TAG(6, SCE_GS_TRUE, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD);
    SET_ADDRESS_DATA(qwd, id, SCE_GS_TEXFLUSH, 0);
    SET_ADDRESS_DATA(qwd, id, SCE_GS_TEST_1, SCE_GS_SET_TEST(SCE_GS_FALSE, SCE_GS_ALPHA_ALWAYS, 0, 0, 0, 1, SCE_GS_TRUE, SCE_GS_DEPTH_ALWAYS));
    SET_ADDRESS_DATA(qwd, id, SCE_GS_ZBUF_1, SCE_GS_SET_ZBUF(448, SCE_GS_PSMZ16S, SCE_GS_TRUE));
    SET_ADDRESS_DATA(qwd, id, SCE_GS_TEX0_1, SCE_GS_SET_TEX0(sh2gfw_GetTexTBP0(&shGs_AllEnv, 7), 8, SCE_GS_PSMCT32, 9, 9, SCE_GS_TRUE /* rgba */, Env_ctl.CopyFilterColor.ui32[1], 0, 0, 0, 0, 0));

    if (Env_ctl.mode_buf[0] == 0) {
        qwd[id].ul64[0] = SCE_GS_SET_TEX1(0, 0, SCE_GS_LINEAR, SCE_GS_LINEAR, 0, 0, 0); qwd[id++].ul64[1] = SCE_GS_TEX1_1;
        tx = pfp->base_Ix - 4;
        ty = pfp->base_Iy - 4;
    } else {
        qwd[id].ul64[0] = SCE_GS_SET_TEX1(0, 0, SCE_GS_LINEAR, SCE_GS_LINEAR, 0, 0, 0); qwd[id++].ul64[1] = SCE_GS_TEX1_1;
        ty = tx = 0;
    }

    SET_ADDRESS_DATA(qwd, id, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP(SCE_GS_CLAMP, SCE_GS_CLAMP, 0, 0, 0, 0));
    SET_DMATAG(qwd, id, DMAcnt | 8, 0, SCE_VIF1_SET_NOP(0), SCE_VIF1_SET_DIRECT(8, 0));
    qwd[id].ul64[0] = SCE_GIF_SET_TAG(1, SCE_GS_TRUE, SCE_GS_TRUE, SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, /* Texture Mapping */ SCE_GS_TRUE, 0, /* No Alpha Blend */ SCE_GS_FALSE, 0, /* Use ST */ SCE_GS_TRUE, 0, 0), SCE_GIF_PACKED, 7);
    qwd[id++].ul64[1] = GIF_REGLIST(SCE_GS_UV, SCE_GS_RGBAQ, SCE_GS_XYZ2, SCE_GS_UV, SCE_GS_RGBAQ, SCE_GS_XYZ2, SCE_GIF_PACKED_AD);
    qwd[id].ul64[0] = SH_GIF_PACK_UV(pfp->TexTrimSX, pfp->TexTrimSY); qwd[id++].ul64[1] = 0;

    // @note not a macro or inline according to the line numbers
    qwd[id]  .ui32[0] = Env_ctl.CopyFilterColor.uc8[0];
    qwd[id]  .ui32[1] = Env_ctl.CopyFilterColor.uc8[1];
    qwd[id]  .ui32[2] = Env_ctl.CopyFilterColor.uc8[2];
    qwd[id++].ui32[3] = Env_ctl.CopyFilterColor.uc8[3];
    SH_GIF_SET_XYZ(qwd, id, Q4(1792.0f) + tx, Q4(1792.0f) + ty, 1, SCE_GS_FALSE);    
    qwd[id].ul64[0] = SH_GIF_PACK_UV((pfp->TexTrimSX + 0x1ff) * 16, (pfp->TexTrimSY + 0x1ff) * 16); qwd[id++].ul64[1] = 0;

    // @note not a macro or inline according to the line numbers
    qwd[id]  .ui32[0] = Env_ctl.CopyFilterColor.uc8[0];
    qwd[id]  .ui32[1] = Env_ctl.CopyFilterColor.uc8[1];
    qwd[id]  .ui32[2] = Env_ctl.CopyFilterColor.uc8[2];
    qwd[id++].ui32[3] = Env_ctl.CopyFilterColor.uc8[3];

    SH_GIF_SET_XYZ(qwd, id, Q4(2304.0f) + tx, Q4(2304.0f) + ty, 1, SCE_GS_FALSE);
    if (Env_ctl.mode_buf[0] == 0) {
        qwd[id].ul64[1] = 0xf /* PACKED NOP */;
    } else {
        SET_QWORD_U64(qwd + id, SCE_GS_SET_TEX1(0, 0, SCE_GS_LINEAR, SCE_GS_LINEAR, 0, 0, 0), SCE_GS_TEX1_1);
    }

    id++;
    qwd += id;
    sh2gfw_setREF_tagchain(&qwd, shGs_AllEnv.DefaultEnv);
    SET_DMA_RET(qwd);
    
    qwd++;
    
    *ppqwd = qwd;
}

void sh2gfw_Filter_Blur(Q_WORDDATA** ppqwd, u_int bl_ratio) {
    int id;
    int tx, ty;
    int idd[3] = {2, 0, 1};
    Q_WORDDATA* qwd;

    id = 0;
    qwd = *ppqwd;

    SET_DMATAG(qwd, id, DMAcnt | 9, 0, SCE_VIF1_SET_NOP(0), SCE_VIF1_SET_DIRECT(9, 0));

    SET_GIFTAG(qwd, id, SCE_GIF_SET_TAG(8, SCE_GS_TRUE, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD);
    SET_ADDRESS_DATA(qwd, id, SCE_GS_TEXFLUSH, 0);
    SET_ADDRESS_DATA(qwd, id, SCE_GS_TEST_1, SCE_GS_SET_TEST(SCE_GS_FALSE, SCE_GS_ALPHA_ALWAYS, 0, 0, 0, 1, SCE_GS_TRUE, SCE_GS_DEPTH_ALWAYS));
    SET_ADDRESS_DATA(qwd, id, SCE_GS_ZBUF_1, SCE_GS_SET_ZBUF(448, SCE_GS_PSMZ16S, SCE_GS_TRUE));
    qwd[id].ul64[1] = SCE_GS_TEX0_1; qwd[id++].ul64[0] = SCE_GS_SET_TEX0(sh2gfw_GetNowDispFBP(&shGs_AllEnv) << 5, 8, SCE_GS_PSMCT32, 9, 9, 0, 0, 0, 0, 0, 0, 0);
    qwd[id].ul64[0] = SCE_GS_SET_TEX1(0, 0, 0, 0, 0, 0, 0); qwd[id++].ul64[1] = SCE_GS_TEX1_1;
    SET_ADDRESS_DATA(qwd, id, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP(SCE_GS_CLAMP, SCE_GS_CLAMP, 0, 0, 0, 0));
    SET_ADDRESS_DATA(qwd, id, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(SCE_GS_ALPHA_CS, SCE_GS_ALPHA_CD, SCE_GS_ALPHA_AS, SCE_GS_ALPHA_CD, 0));
    copy_drawenv_frame_mskalpha(qwd + id++, idd[shGs_AllEnv.loop3]);

    SET_DMATAG(qwd, id, DMAcnt | 8, 0, SCE_VIF1_SET_NOP(0), SCE_VIF1_SET_DIRECT(8, 0));
    qwd[id].ul64[0] = SCE_GIF_SET_TAG(1, SCE_GS_TRUE, SCE_GS_TRUE, SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, /* Texture Mapping */ SCE_GS_TRUE, 0, /* Alpha Blend */ SCE_GS_TRUE, 0, /* Use ST */ SCE_GS_TRUE, 0, 0), SCE_GIF_PACKED, 7);
    qwd[id++].ul64[1] = GIF_REGLIST(SCE_GS_UV, SCE_GS_RGBAQ, SCE_GS_XYZ2, SCE_GS_UV, SCE_GS_RGBAQ, SCE_GS_XYZ2, SCE_GIF_PACKED_AD);
    qwd[id].ul64[0] = SH_GIF_PACK_UV(Q4(0.0f), Q4(0.0f)); qwd[id++].ul64[1] = 0;
    SET_QWORD_U32(qwd, id, 128, 128, 128, bl_ratio);
    SH_GIF_SET_XYZ(qwd, id, Q4(1792.0f), Q4(1792.0f), 1, SCE_GS_FALSE);
    qwd[id].ul64[0] = SH_GIF_PACK_UV(Q4(512.0f), Q4(512.0f)); qwd[id++].ul64[1] = 0; // packed format uses << 32 for v
    SET_QWORD_U32(qwd, id, 128, 128, 128, bl_ratio);
    SH_GIF_SET_XYZ(qwd, id, Q4(2304.0f), Q4(2304.0f), 1, SCE_GS_FALSE);
    qwd[id].ul64[0] = SCE_GS_SET_TEX1(0, 0, SCE_GS_LINEAR, SCE_GS_LINEAR, 0, 0, 0); qwd[id++].ul64[1] = SCE_GS_TEX1_1;
    qwd[id].ul128 = 0; qwd[id++].ui32[0] = DMAret;
    *ppqwd = qwd + id;    
}

void sh2gfw_Filter_Dark_Blur(Q_WORDDATA** ppqwd, u_int bl_ratio, u_int aref) {
    int id = 0;
    int tx, ty;
    int idd[3] = {2, 0, 1};
    Q_WORDDATA* qwd = *ppqwd;

    SET_DMATAG(qwd, id, DMAcnt | 9, 0, SCE_VIF1_SET_NOP(0), SCE_VIF1_SET_DIRECT(9, 0));
    SET_GIFTAG(qwd, id, SCE_GIF_SET_TAG(8, SCE_GS_TRUE, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD);
    SET_ADDRESS_DATA(qwd, id, SCE_GS_TEXFLUSH, 0);
    SET_ADDRESS_DATA(qwd, id, SCE_GS_TEST_1, SCE_GS_SET_TEST(SCE_GS_TRUE /* alpha test on! */, SCE_GS_ALPHA_LEQUAL, aref, 0, 0, SCE_GS_TRUE, SCE_GS_TRUE, SCE_GS_DEPTH_ALWAYS));
    SET_ADDRESS_DATA(qwd, id, SCE_GS_ZBUF_1, SCE_GS_SET_ZBUF(448, SCE_GS_PSMZ16S, SCE_GS_TRUE));
    SET_ADDRESS_DATA(qwd, id, SCE_GS_TEX0_1, SCE_GS_SET_TEX0(sh2gfw_GetNowDispFBP(&shGs_AllEnv) << 5, 8, SCE_GS_PSMCT32, 9, 9, SCE_GS_TRUE /* rgba */, 0, 0, 0, 0, 0, 0));
    qwd[id].ul64[0] = SCE_GS_SET_TEX1(0, 0, 0, 0, 0, 0, 0); qwd[id++].ul64[1] = SCE_GS_TEX1_1;
    SET_ADDRESS_DATA(qwd, id, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP(SCE_GS_CLAMP, SCE_GS_CLAMP, 0, 0, 0, 0));
    SET_ADDRESS_DATA(qwd, id, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(0, 1, 2, 1, bl_ratio)); // 01 10 01 00
    copy_drawenv_frame_mskalpha(qwd + id++, idd[shGs_AllEnv.loop3]);

    SET_DMATAG(qwd, id, DMAcnt | 9, 0, SCE_VIF1_SET_NOP(0), SCE_VIF1_SET_DIRECT(9, 0));
    qwd[id].ul64[0] = SCE_GIF_SET_TAG(1, SCE_GS_TRUE, SCE_GS_TRUE, SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, 1, 0, 1, 0, 1, 0, 0), SCE_GIF_PACKED, 8);
    qwd[id++].ul64[1] = GIF_REGLIST(SCE_GS_UV, SCE_GS_RGBAQ, SCE_GS_XYZ2, SCE_GS_UV, SCE_GS_RGBAQ, SCE_GS_XYZ2, SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD);
    qwd[id].ul64[0] = SCE_GS_SET_UV(0, 0); qwd[id++].ul64[1] = 0;
    SET_QWORD_U32(qwd, id, 128, 128, 128, 128);
    SH_GIF_SET_XYZ(qwd, id, Q4(1791.75f), Q4(1791.75f), 1, SCE_GS_FALSE);
    qwd[id].ul64[0] = SH_GIF_PACK_UV(Q4(512.0f), Q4(512.0f)); qwd[id++].ul64[1] = 0; // packed format uses << 32 for v
    SET_QWORD_U32(qwd, id, 128, 128, 128, 128);
    SH_GIF_SET_XYZ(qwd, id, Q4(2303.75f), Q4(2303.75f), 1, SCE_GS_FALSE);
    copy_defaultenv(qwd + id++, 2);
    qwd[id].ul64[0] = SCE_GS_SET_TEX1(0, 0, SCE_GS_LINEAR, SCE_GS_LINEAR, 0, 0, 0); qwd[id++].ul64[1] = SCE_GS_TEX1_1;
    SET_DMA_RET(qwd + id); id++;
    *ppqwd = qwd + id;
}

static inline void copy_frame_mskalpha(Q_WORDDATA* qwd, shGsDrawEnv* env) {
    qwd->ul128 = env->frame_mskalpha.ul128;
}
static inline void qword_copy_ul128(Q_WORDDATA* dst, Q_WORDDATA* src) {
    dst->ul128 = src->ul128;
}

void sh2gfw_Filter_Glow_Blur(Q_WORDDATA** ppqwd, u_int aref, u_int bl_ratio, u_int pam) {
    int id = 0;
    int tx, ty;
    int idd[3] = {2, 0, 1};
    Q_WORDDATA* qwd = *ppqwd;

    SET_DMATAG(qwd, id, DMAcnt | 9, 0, SCE_VIF1_SET_NOP(0), SCE_VIF1_SET_DIRECT(9, 0));
    SET_GIFTAG(qwd, id, SCE_GIF_SET_TAG(8, SCE_GS_TRUE, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD);
    SET_ADDRESS_DATA(qwd, id, SCE_GS_TEXFLUSH, 0);
    SET_ADDRESS_DATA(qwd, id, SCE_GS_TEST_1, SCE_GS_SET_TEST(SCE_GS_TRUE /* alpha test on! */, SCE_GS_ALPHA_GEQUAL, aref, 0, 0, SCE_GS_TRUE, SCE_GS_TRUE, SCE_GS_DEPTH_ALWAYS));
    SET_ADDRESS_DATA(qwd, id, SCE_GS_ZBUF_1, SCE_GS_SET_ZBUF(448, SCE_GS_PSMZ16S, SCE_GS_TRUE));
    SET_ADDRESS_DATA(qwd, id, SCE_GS_TEX0_1, SCE_GS_SET_TEX0(sh2gfw_GetNowDispFBP(&shGs_AllEnv) << 5, 8, SCE_GS_PSMCT32, 9, 9, SCE_GS_TRUE /* rgba */, 0, 0, 0, 0, 0, 0));
    if (pam) {
        qwd[id].ul64[0] = SCE_GS_SET_TEX1(0, 0, 1, 1, 0, 0, 0); qwd[id++].ul64[1] = SCE_GS_TEX1_1;
    } else {
        qwd[id].ul64[0] = SCE_GS_SET_TEX1(0, 0, 0, 0, 0, 0, 0); qwd[id++].ul64[1] = SCE_GS_TEX1_1;
    }
    SET_ADDRESS_DATA(qwd, id, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP(SCE_GS_CLAMP, SCE_GS_CLAMP, 0, 0, 0, 0));
    SET_ADDRESS_DATA(qwd, id, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(0, 1, 2, 1, bl_ratio)); // 01 10 01 00
    copy_frame_mskalpha(qwd + id++, &shGs_AllEnv.DrawEnv[idd[shGs_AllEnv.loop3]]);

    SET_DMATAG(qwd, id, DMAcnt | 9, 0, SCE_VIF1_SET_NOP(0), SCE_VIF1_SET_DIRECT(9, 0));
    qwd[id].ul64[0] = SCE_GIF_SET_TAG(1, SCE_GS_TRUE, SCE_GS_TRUE, SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, 1, 0, 1, 0, 1, 0, 0), SCE_GIF_PACKED, 8);
    qwd[id++].ul64[1] = GIF_REGLIST(SCE_GS_UV, SCE_GS_RGBAQ, SCE_GS_XYZ2, SCE_GS_UV, SCE_GS_RGBAQ, SCE_GS_XYZ2, SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD);
    qwd[id].ul64[0] = SCE_GS_SET_UV(0, 0); qwd[id++].ul64[1] = 0;
    SET_QWORD_U32(qwd, id, 128, 128, 128, 128);
    SH_GIF_SET_XYZ(qwd, id, Q4(1791.75f), Q4(1791.75f), 1, SCE_GS_FALSE);
    qwd[id].ul64[0] = SH_GIF_PACK_UV(Q4(512.0f), Q4(512.0f)); qwd[id++].ul64[1] = 0; // packed format uses << 32 for v
    SET_QWORD_U32(qwd, id, 128, 128, 128, 128);
    SH_GIF_SET_XYZ(qwd, id, Q4(2303.75f), Q4(2303.75f), 1, SCE_GS_FALSE);
    copy_defaultenv(qwd + id++, 2);
    qwd[id].ul64[0] = SCE_GS_SET_TEX1(0, 0, SCE_GS_LINEAR, SCE_GS_LINEAR, 0, 0, 0); qwd[id++].ul64[1] = SCE_GS_TEX1_1;
    SET_DMA_RET(qwd + id); id++;
    *ppqwd = qwd + id;
}

/*
Numerical Recipes ranqd1, Chapter 7.1, §An Even Quicker Generator, Eq. 7.1.6 parameters
https://library.sciencemadness.org/lanl1_a/lib-www/numerica/f7-1.pdf
https://en.wikipedia.org/wiki/Linear_congruential_generator
*/
#line 572
void sh2gfw_test_MakeNoise(void) {
    u_int* noise_data1;
    u_int* noise_data2;
    u_int ira;
    u_int irc;
    u_int imsk;
    u_int itmp;
    u_int isd;
    int i;

    isd = Env_ctl.random_seeds.ui32[0];




    
    for (i = 0xFFF; i >= 0; i--) {
        ira = 0x19660D;
        irc = 0x3C6EF35F;









        
        isd  = isd * ira + irc;
        itmp = isd >> 24;

        isd  = isd * ira + irc;
        itmp = (itmp << 8) | (isd >> 24);

        isd  = isd * ira + irc;
        itmp = (itmp << 8) | (isd >> 24);

        isd  = isd * ira + irc;
        itmp = (itmp << 8) | (isd >> 24);

        *((int*)SCRATCHPAD_START + i) = itmp;
    
    }
    Env_ctl.random_seeds.ui32[0] = isd;
    
    do {
        /* wait */
    } while (*D8_CHCR & 0x100);
    
    *D8_QWC = 0x400;
    *(Q_WORDDATA**)D8_MADR = CalcTex_buffer;
    *D8_SADR = 0;
    *D8_CHCR = 0x100;
    
    
    while (*D8_CHCR & 0x100) {
        for (i = 0; i < 3; i++) isd++; // ??
    }


}


void sh2gfw_Black_Clear(void) {
    Q_WORDDATA* qwd = Noise_Packet; // qwd is in the dwarf, but the compiler does `lui at,%hi(Noise_Packet)` each time
    int id = 0;

    SET_DMATAG(qwd, id, DMAcnt | 3, 0, SCE_VIF1_SET_NOP(0), SCE_VIF1_SET_DIRECT(3, 0));
    SET_GIFTAG(qwd, id, SCE_GIF_SET_TAG(2, SCE_GS_TRUE, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD);
    SET_ADDRESS_DATA(qwd, id, SCE_GS_TEST_1, SCE_GS_SET_TEST(SCE_GS_FALSE, SCE_GS_ALPHA_GEQUAL, 0, 0, 0, SCE_GS_TRUE, SCE_GS_TRUE, SCE_GS_DEPTH_ALWAYS)); // @weird alpha test is off but it still sets some stuff lol
    SET_ADDRESS_DATA(qwd, id, SCE_GS_ZBUF_1, SCE_GS_SET_ZBUF(448, SCE_GS_PSMZ16S, SCE_GS_TRUE));

    SET_DMATAG(qwd, id, DMAcnt | 5, 0, SCE_VIF1_SET_NOP(0), SCE_VIF1_SET_DIRECT(5, 0));
    qwd[id].ul64[0] = SCE_GIF_SET_TAG(1, 1, 1, SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, 0, 0, 0, 0, 0, 0, 0), SCE_GIF_PACKED, 4); 
    qwd[id++].ul64[1] = GIF_REGLIST(SCE_GS_RGBAQ, SCE_GS_XYZ2, SCE_GS_RGBAQ, SCE_GS_XYZ2);
    SET_QWORD_U32(qwd, id, 128, 128, 128, 128);
    SH_GIF_SET_XYZ(qwd, id, Q4(1792.0f), Q4(1792.0f), 1, SCE_GS_FALSE);
    SET_QWORD_U32(qwd, id, 128, 128, 128, 128);
    SH_GIF_SET_XYZ(qwd, id, Q4(2304.0f), Q4(2304.0f), 1, SCE_GS_FALSE);

    SET_DMA_END(qwd + id);
    d1cSend(qwd);
}


int sh2gfw_2d_filters_data_990 [3] = {2, 0, 1};
int sh2gfw_2d_filters_data_1005[3] = {2, 0, 1};

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_SendDraw_Noise);

int sh2gfw_2d_filters_data_1047[3] = {2, 0, 1};
INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Swap_Soft);

int sh2gfw_2d_filters_data_1125[3] = {2, 0, 1};
INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Swap_GlowSoft);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_FadeOut_Retain);

void sh2gfw_Filter_Retain(Q_WORDDATA** ppqwd) {
    int id = 0;
    int tx;
    int ty;
    Q_WORDDATA* qwd;

    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();
    int colr, colg, colb;
    int pr, pg, pb;

    pr = pg = pb = 0;    
    tx = ty = 0;
    qwd = *ppqwd;

    SET_DMATAG(qwd, id, DMAcnt | 7, 0, SCE_VIF1_SET_NOP(0), SCE_VIF1_SET_DIRECT(7, 0));
    
    SET_GIFTAG(qwd, id, SCE_GIF_SET_TAG(6, SCE_GS_TRUE, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD);
    SET_ADDRESS_DATA(qwd, id, SCE_GS_TEXFLUSH, 0);
    SET_ADDRESS_DATA(qwd, id, SCE_GS_TEST_1, SCE_GS_SET_TEST(SCE_GS_FALSE, SCE_GS_ALPHA_ALWAYS, 0, 0, 0, 1, SCE_GS_TRUE, SCE_GS_DEPTH_ALWAYS));
    SET_ADDRESS_DATA(qwd, id, SCE_GS_ZBUF_1, SCE_GS_SET_ZBUF(0xE0000 / 2048, SCE_GS_PSMZ16S, SCE_GS_TRUE));
    qwd[id].ul64[0] = SCE_GS_SET_TEX1(0, 0, 0, 0, 0, 0, 0); qwd[id++].ul64[1] = SCE_GS_TEX1_1;
    SET_ADDRESS_DATA(qwd, id, SCE_GS_TEX0_1, SCE_GS_SET_TEX0(sh2gfw_GetNowDispFBP(&shGs_AllEnv) << 5, 8, SCE_GS_PSMCT32, /* 512 */ 9, /* 512 */ 9, 1, SCE_GS_MODULATE, 0, SCE_GS_PSMCT32, 0, 0, 0));
    SET_ADDRESS_DATA(qwd, id, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(SCE_GS_ALPHA_ZERO, SCE_GS_ALPHA_CS, SCE_GS_ALPHA_FIX, SCE_GS_ALPHA_CD, 128));

    if (pfp->FO_timer != 0) {
        colr = colg = colb = 0x80;
    } else {
        
        colr = Env_ctl.CopyFilterColor.uc8[0];
        colg = Env_ctl.CopyFilterColor.uc8[1];
        colb = Env_ctl.CopyFilterColor.uc8[2];
    }

    SET_DMATAG(qwd, id, DMAcnt | 7, 0, SCE_VIF1_SET_NOP(0), SCE_VIF1_SET_DIRECT(7, 0));
    qwd[id].ul64[0] = SCE_GIF_SET_TAG(1, 1, 1, SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, 1, 0, 0, 0, 1, 0, 0), SCE_GIF_PACKED, 6);
    qwd[id++].ul64[1] = GIF_REGLIST(SCE_GS_UV, SCE_GS_RGBAQ, SCE_GS_XYZ2, SCE_GS_UV, SCE_GS_RGBAQ, SCE_GS_XYZ2);
    qwd[id].ul64[0] = SH_GIF_PACK_UV(0, 0); qwd[id++].ul64[1] = 0;
    SET_QWORD_U32(qwd, id, colr, colb, colb, 128);
    // X = 0 and Y = 0 coords assuming the window coords are now 512x512
    SH_GIF_SET_XYZ(qwd, id, tx + Q4(1792.0f), ty + Q4(1792.0f), 1, SCE_GS_FALSE);
    qwd[id].ul64[0] = SH_GIF_PACK_UV(Q4(512.0f), Q4(512.0f)); qwd[id++].ul64[1] = 0; 
    SET_QWORD_U32(qwd, id, colr, colg, colb, 128);
    // X = 512 and Y = 512 coords assuming the window coords are now 512x512
    SH_GIF_SET_XYZ(qwd, id, tx + Q4(2304.0f), ty + Q4(2304.0f), 1, SCE_GS_FALSE);
    SET_DMA_RET(qwd + id); id++;

    *ppqwd = qwd + id;
    pfp->FO_timer++;
}

int sh2gfw_2d_filters_data_colordata[4] = {255, 255, 255, 255};
INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Fade2);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Fade3);

void sh2gfw_Set_FadeOutRetain_Black(float ra) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_FADEOUT_RETAIN_BORW1;
    shGsFilterWork.mode = shGsFilterWork.GsFilterKind;

    pfp->FIO_ratio = SH2_FIO_RATIO * fabs(ra);
    pfp->TargetSec = 10.0f * ra;
    pfp->FO_timer = 0;
}

void sh2gfw_Set_FadeOut_Black(float ra) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_FADE2_COLOR1;
    shGsFilterWork.mode = shGsFilterWork.GsFilterKind;

    pfp->FIO_ratio = SH2_FIO_RATIO * fabs(ra);
    pfp->TargetSec = ra;
    pfp->FO_timer = 0;
    pfp->Max_Timer = ra * shGetFPS();
}

void sh2gfw_Set_FadeOutRetain_White(float ra) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_FADEOUT_RETAIN_BORW0;
    shGsFilterWork.mode = shGsFilterWork.GsFilterKind;

    pfp->FIO_ratio = SH2_FIO_RATIO * fabs(ra);
    pfp->TargetSec = 10.0f * ra;
    pfp->FO_timer = 0;
}

void sh2gfw_Set_FadeOutRetain_Red(float ra) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_FADEOUT_RETAIN_BORW2;
    shGsFilterWork.mode = shGsFilterWork.GsFilterKind;

    pfp->FIO_ratio = SH2_FIO_RATIO * fabs(ra);
    pfp->TargetSec = 10.0f * ra;
    pfp->FO_timer = 0;
}

void sh2gfw_Set_FadeOut_White(float ra) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_FADE2_COLOR0;
    shGsFilterWork.mode = shGsFilterWork.GsFilterKind;

    pfp->FIO_ratio = SH2_FIO_RATIO * fabs(ra);
    pfp->TargetSec = ra;
    pfp->FO_timer = 0;
    pfp->Max_Timer = ra * shGetFPS();
}

void sh2gfw_Set_FadeIn_Black(float ra) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_FADE2_19;
    shGsFilterWork.mode = 19;

    pfp->FIO_ratio = SH2_FIO_RATIO * fabs(ra);
    pfp->TargetSec = ra;
    pfp->FO_timer = 0;
    pfp->Max_Timer = ra * shGetFPS();
}

void sh2gfw_Set_FadeIn_White(float ra) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_FADE2_20;
    shGsFilterWork.mode = 20;

    pfp->FIO_ratio = SH2_FIO_RATIO * fabs(ra);
    pfp->TargetSec = ra;
    pfp->FO_timer = 0;
    pfp->Max_Timer = ra * shGetFPS();
}

void sh2gfw_Set_FadeIn_Red(float ra) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_FADE3;
    shGsFilterWork.mode = 21;

    pfp->FIO_ratio = SH2_FIO_RATIO * fabs(ra);
    pfp->TargetSec = ra;
    pfp->FO_timer = 0;
    pfp->Max_Timer = ra * shGetFPS();
}

void sh2gfw_Set_FilterBlur(int rt) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_BLUR;
    pfp->blurRatio = rt;
}

void sh2gfw_Set_PauseRetain(void) {
    if (shGsFilterWork.GsFilterKind != SH2_GS_FILTER_KIND_RETAIN) {
        sh2gfw_Get_FilterCommandParams();

        shGsFilterWork.Kind_History = shGsFilterWork.GsFilterKind;
        shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_RETAIN;
    }
}

void sh2gfw_Reset_PauseRetain(void) {
    if (shGsFilterWork.GsFilterKind == SH2_GS_FILTER_KIND_RETAIN) {
        sh2gfw_Get_FilterCommandParams();

        shGsFilterWork.GsFilterKind = shGsFilterWork.Kind_History;
        shGsFilterWork.Kind_History = SH2_GS_FILTER_KIND_RETAIN;
    }
}

void sh2gfw_Reset_FilterCommand(void) {
    int mm;
    int kk;
    int ss;
    FilterParams* pfp;

    mm = shGsFilterWork.mode;
    kk = shGsFilterWork.GsFilterKind;
    pfp = sh2gfw_Get_FilterCommandParams();
    ss = pfp->sw_flg;

    memset(&shGsFilterWork, 0, sizeof(shGsFilterWork));
    shGsFilterWork.mode = mm;
    shGsFilterWork.Kind_History = kk;
    pfp->sw_flg = ss;
}

int sh2gfw_Get_FilterCommand(void) {
    return shGsFilterWork.GsFilterKind;
}

void* sh2gfw_Get_FilterCommandParams(void) {
    return shGsFilterWork.FilterData;
}

int sh2gfw_Set_CaptureNowFB(void) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_COPY_AND_RESET;
    pfp->sw_flg = 1;

    return 0x3400;
}

void Exec_PostDraw_OVfunc(void) {
    if (stage == NULL) return;
    if (stage->gfw_func == NULL) return;
    if (stage->gfw_func->PostDraw == NULL) return;
    stage->gfw_func->PostDraw();
}

int Check_Filter_Soft(void) {
    if (shGsFilterWork.GsFilterKind >= SH2_GS_FILTER_KIND_SWAP_SOFT && shGsFilterWork.GsFilterKind <= SH2_GS_FILTER_KIND_SWAP_SOFT_10) {
        return !shGsFilterWork.mode;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", DemoFadeDraw2);

void Make_Filter_Packet(void* pb) {
    Q_WORDDATA* qwd = pb;
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    if (pfp->sw_flg != 0) {
        d2sSync(0, -1);
        d1sSync(0, -1);
        sh2gfw_Copy_FrameToWork(&qwd);
        pfp->sw_flg = 0;
    }

    switch (shGsFilterWork.GsFilterKind) {
        case SH2_GS_FILTER_KIND_SWAP_SOFT:
            sh2gfw_Filter_JustCopy2(&qwd);
            qwd--;
            sh2gfw_Swap_Soft(&qwd, pfp->SoftIter, 0x80, pfp->SoftShift, pfp->SoftAref, pfp->SoftCit, 0);
            break;

        case SH2_GS_FILTER_KIND_GLOW_SOFT_6:
        case SH2_GS_FILTER_KIND_GLOW_SOFT_7:
            sh2gfw_Filter_JustCopy2(&qwd);
            qwd--;
            sh2gfw_Swap_GlowSoft(&qwd, pfp->SoftIter, pfp->SoftCit, pfp->SoftAref, pfp->SoftShift);
            break;

        default:
            sh2gfw_Filter_JustCopy2(&qwd);
            break;

        case SH2_GS_FILTER_KIND_BLUR:
            sh2gfw_Filter_JustCopy2(&qwd);
            qwd--;
            sh2gfw_Filter_Blur(&qwd, (u_char) pfp->blurRatio);
            break;

        case SH2_GS_FILTER_KIND_GLOW_BLUR:
            sh2gfw_Filter_JustCopy2(&qwd);
            qwd--;
            sh2gfw_Filter_Glow_Blur(&qwd, (u_char) (pfp->GreaterA + 224), (u_char) pfp->blurRatio, 0);
            break;

        case SH2_GS_FILTER_KIND_DARK_BLUR:
            sh2gfw_Filter_JustCopy2(&qwd);
            qwd--;
            sh2gfw_Filter_Dark_Blur(&qwd, (u_char) pfp->blurRatio, (u_char) (pfp->LesserA + 127));
            break;

        case SH2_GS_FILTER_KIND_FADE2_COLOR1:
            sh2gfw_Fade2(&qwd, 0, 1, 0);
            break;

        case SH2_GS_FILTER_KIND_FADEOUT_RETAIN_BORW1:
            sh2gfw_FadeOut_Retain(&qwd, 1);
            break;

        case SH2_GS_FILTER_KIND_FADE2_COLOR0:
            sh2gfw_Fade2(&qwd, 0, 0, 0);
            break;

        case SH2_GS_FILTER_KIND_FADEOUT_RETAIN_BORW0:
            sh2gfw_FadeOut_Retain(&qwd, 0);
            break;

        case SH2_GS_FILTER_KIND_FADEOUT_RETAIN_BORW2:
            sh2gfw_FadeOut_Retain(&qwd, 2);
            break;

        case SH2_GS_FILTER_KIND_FADE2_19:
            pfp->base_Ix = 0;
            pfp->base_Iy = 0;
            sh2gfw_Fade2(&qwd, 1, 1, 0);
            break;

        case SH2_GS_FILTER_KIND_FADE2_20:
            pfp->base_Ix = 0;
            pfp->base_Iy = 0;
            sh2gfw_Fade2(&qwd, 1, 0, 0);
            break;

        case SH2_GS_FILTER_KIND_FADE3:
            pfp->base_Ix = 0;
            pfp->base_Iy = 0;
            {   
                sceVu0IVECTOR col = {255, 0, 0, 0};
                sh2gfw_Fade3(&qwd, 1, col);
            }
            break;

        case SH2_GS_FILTER_KIND_RETAIN:
            sh2gfw_Filter_Retain(&qwd);
            break;

        case SH2_GS_FILTER_KIND_SWAP_SOFT_8:
        case SH2_GS_FILTER_KIND_SWAP_SOFT_9:
        case SH2_GS_FILTER_KIND_SWAP_SOFT_10:
            sh2gfw_Filter_JustCopy2(&qwd);
            qwd--;
            sh2gfw_Swap_Soft(&qwd, pfp->S1_iter, 128, pfp->S1_shift, pfp->S1_alpha, pfp->KeyAlpha + pfp->TrimAlpha, 1);
            sh2gfw_Swap_Soft(&qwd, pfp->S2_iter, 128, pfp->S2_shift, pfp->S2_alpha, pfp->KeyAlpha + pfp->TrimAlpha, 2);
            break;

        case SH2_GS_FILTER_KIND_COPY_AND_RESET:
            sh2gfw_Filter_JustCopy2(&qwd);
            qwd--;
            sh2gfw_Reset_FilterCommand();
            break;
    }

    if (shGsFilterWork.mode >= SH2_GS_FILTER_KIND_FADE2_19            && 
        shGsFilterWork.mode <= SH2_GS_FILTER_KIND_FADE3               && 
        shGsFilterWork.GsFilterKind < SH2_GS_FILTER_KIND_FADE2_COLOR1 && 
        shGsFilterWork.GsFilterKind != 0
    ) {
        switch (shGsFilterWork.mode) {
            case SH2_GS_FILTER_KIND_FADE2_19:
                sh2gfw_Fade2(&qwd, 1, 1, 1);
                return;

            case SH2_GS_FILTER_KIND_FADE2_20:
                sh2gfw_Fade2(&qwd, 1, 0, 1);
                return;

            case SH2_GS_FILTER_KIND_FADE3: {
                sceVu0IVECTOR col = {255, 0, 0, 0};
                sh2gfw_Fade3(&qwd, 1, col);
                break;
            }
        }
    }
}

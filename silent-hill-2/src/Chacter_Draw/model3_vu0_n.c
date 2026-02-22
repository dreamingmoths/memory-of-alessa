#include "sh2_common.h"
#include "eestruct.h"
#include "eeregs.h"
#include "libgraph.h"
#include "model3_vu0_n.h"
#include "model3_n.h"
#include "model3_sub_n.h"
#include "model_common.h"
#include "libdma.h"
#include "libdmapk.h"
#include "light_n.h"
#include "GFW/sh2gfw_Init_ModelDrawData.h"
#include "vifot/sh_kt_vif0.h"

void InitTriangleNormal(TriangleNormal* p) {
    int qwc = 12;
    p->dmatag.u64[0] = DMAnext | qwc;
    p->dmatag.u32[2] = SCE_VIF1_SET_NOP(0);
    p->dmatag.u32[3] = SCE_VIF1_SET_DIRECT(qwc, 0);

    p->n_giftag.u64[0] = SCE_GIF_SET_TAG(
        1,
        SCE_GS_TRUE,
        SCE_GS_TRUE,
        SCE_GS_SET_PRIM(SCE_GS_PRIM_TRI, 1, 1, 1, 1, 0, 0, 0, 0),
        SCE_GIF_PACKED,  qwc - 1
    );
    
    p->n_giftag.u64[1] = GIF_REG(SCE_GIF_PACKED_AD, 0) | GIF_REG(SCE_GIF_PACKED_AD, 1) | GIF_REG(SCE_GS_ST,         2)  | GIF_REG(SCE_GS_RGBAQ,      3)  | 
        GIF_REG(SCE_GS_XYZF2,      4)  | GIF_REG(SCE_GS_ST,         5)  | GIF_REG(SCE_GS_RGBAQ,      6)  | GIF_REG(SCE_GS_XYZF2,      7)  |
        GIF_REG(SCE_GS_ST,         8)  | GIF_REG(SCE_GS_RGBAQ,      9)  | GIF_REG(SCE_GS_XYZF2,      10) | GIF_REG(SCE_GS_PRIM,       11);
    
    p->n_tex0.s64[1] = 6;
    p->n_clamp.s64[1] = 8;
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", InitTriangleNormalEnviron);

void InitTriangleNormalSpecular(TriangleNormalSpecular* p) {
    int qwc = 26;

    p->dmatag.u64[0] = DMAnext | qwc;
    p->dmatag.u32[2] = SCE_VIF1_SET_NOP(0);
    p->dmatag.u32[3] = SCE_VIF1_SET_DIRECT(qwc, 0);

    // normal
    p->n_giftag.u64[0] = SCE_GIF_SET_TAG(
        1,
        SCE_GS_TRUE,
        SCE_GS_TRUE,
        SCE_GS_SET_PRIM(SCE_GS_PRIM_TRI, 1, 1, 1, 1, 0, 0, 0, 0),
        SCE_GIF_PACKED,
        11
    );
    p->n_giftag.u64[1] = GIF_REG(SCE_GIF_PACKED_AD, 0) | GIF_REG(SCE_GIF_PACKED_AD, 1) | GIF_REG(SCE_GS_ST,         2)  | GIF_REG(SCE_GS_RGBAQ,      3)  | 
        GIF_REG(SCE_GS_XYZF2,      4)  | GIF_REG(SCE_GS_ST,         5)  | GIF_REG(SCE_GS_RGBAQ,      6)  | GIF_REG(SCE_GS_XYZF2,      7)  |
        GIF_REG(SCE_GS_ST,         8)  | GIF_REG(SCE_GS_RGBAQ,      9)  | GIF_REG(SCE_GS_XYZF2,      10) | GIF_REG(SCE_GS_PRIM,       11);

    p->n_tex0.u64[1] = 6;
    p->n_clamp.u64[1] = 8;

    // specular
    p->s_giftag.u64[0] = SCE_GIF_SET_TAG(
        1,
        SCE_GS_TRUE,
        SCE_GS_TRUE,
        SCE_GS_SET_PRIM(SCE_GS_PRIM_TRI, 0, 1, 1, 1, 0, 0, 0, 0),
        SCE_GIF_PACKED,
        13
    );
    p->s_giftag.u64[1] =
        GIF_REG(SCE_GIF_PACKED_AD, 0)  | 
        GIF_REG(SCE_GIF_PACKED_AD, 1)  | 
        GIF_REG(SCE_GIF_PACKED_AD, 2)  | 
        GIF_REG(SCE_GIF_PACKED_AD, 3)  | 
        GIF_REG(SCE_GS_RGBAQ, 4)       | 
        GIF_REG(SCE_GS_ST, 5)          | 
        GIF_REG(SCE_GS_XYZF2, 6)       | 
        GIF_REG(SCE_GS_ST, 7)          | 
        GIF_REG(SCE_GS_XYZF2, 8)       | 
        GIF_REG(SCE_GS_ST, 9)          | 
        GIF_REG(SCE_GS_XYZF2, 10)      | 
        GIF_REG(SCE_GIF_PACKED_AD, 11) | 
        GIF_REG(SCE_GIF_PACKED_AD, 12);

  p->s_tex0.u64[0] = model_common_work->specular_mapping_tex0;
  p->s_tex0.u64[1] = 6;
  p->s_clamp.u64[0] = 5;
  p->s_clamp.u64[1] = 8;
  p->s_alpha.u64[0] = 72;
  p->s_alpha.u64[1] = 66;

  p->s_fogcol.u64[0] = 0;
  p->s_fogcol.u64[1] = 61;
  p->s_stq0.fv[2] = 1.0f;
  p->s_stq1.fv[2] = 1.0f;
  p->s_stq2.fv[2] = 1.0f;

  p->S_alpha.u64[0] = 68;
  p->S_alpha.u64[1] = 66;
  p->S_fogcol.u64[1] = 61;
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", InitTriangleNormalEnvironSpecular);

void InitTriangleSpecularNormal(TriangleSpecularNormal* p) {
    int qwc = 26;

    p->dmatag.u64[0] = DMAnext | qwc;
    p->dmatag.u32[2] = SCE_VIF1_SET_NOP(0);
    p->dmatag.u32[3] = SCE_VIF1_SET_DIRECT(qwc, 0);

    // specular
    p->s_giftag.u64[0] = SCE_GIF_SET_TAG(
        1,
        SCE_GS_TRUE,
        SCE_GS_TRUE,
        SCE_GS_SET_PRIM(SCE_GS_PRIM_TRI, 0, 1, 1, 1, 0, 0, 0, 0),
        SCE_GIF_PACKED,
        13
    );
    p->s_giftag.u64[1] =
        GIF_REG(SCE_GIF_PACKED_AD, 0)  | 
        GIF_REG(SCE_GIF_PACKED_AD, 1)  | 
        GIF_REG(SCE_GIF_PACKED_AD, 2)  | 
        GIF_REG(SCE_GIF_PACKED_AD, 3)  | 
        GIF_REG(SCE_GS_RGBAQ, 4)       | 
        GIF_REG(SCE_GS_ST, 5)          | 
        GIF_REG(SCE_GS_XYZF2, 6)       | 
        GIF_REG(SCE_GS_ST, 7)          | 
        GIF_REG(SCE_GS_XYZF2, 8)       | 
        GIF_REG(SCE_GS_ST, 9)          | 
        GIF_REG(SCE_GS_XYZF2, 10)      | 
        GIF_REG(SCE_GIF_PACKED_AD, 11) | 
        GIF_REG(SCE_GIF_PACKED_AD, 12);

    p->s_tex0.u64[0] = model_common_work->specular_mapping_tex0;
    p->s_tex0.u64[1] = 6;
    p->s_clamp.u64[0] = 5;
    p->s_clamp.u64[1] = 8;
    p->s_alpha.u64[0] = 72;
    p->s_alpha.u64[1] = 66;
    
    p->s_fogcol.u64[0] = 0;
    p->s_fogcol.u64[1] = 61;
    p->s_stq0.fv[2] = 1.0f;
    p->s_stq1.fv[2] = 1.0f;
    p->s_stq2.fv[2] = 1.0f;
    
    p->S_alpha.u64[0] = 68;
    p->S_alpha.u64[1] = 66;
    p->S_fogcol.u64[1] = 61;

    // normal
    p->n_giftag.u64[0] = SCE_GIF_SET_TAG(
        1,
        SCE_GS_TRUE,
        SCE_GS_TRUE,
        SCE_GS_SET_PRIM(SCE_GS_PRIM_TRI, 1, 1, 1, 1, 0, 0, 0, 0),
        SCE_GIF_PACKED,
        11
    );
    p->n_giftag.u64[1] = GIF_REG(SCE_GIF_PACKED_AD, 0) | GIF_REG(SCE_GIF_PACKED_AD, 1) | GIF_REG(SCE_GS_ST,         2)  | GIF_REG(SCE_GS_RGBAQ,      3)  | 
        GIF_REG(SCE_GS_XYZF2,      4)  | GIF_REG(SCE_GS_ST,         5)  | GIF_REG(SCE_GS_RGBAQ,      6)  | GIF_REG(SCE_GS_XYZF2,      7)  |
        GIF_REG(SCE_GS_ST,         8)  | GIF_REG(SCE_GS_RGBAQ,      9)  | GIF_REG(SCE_GS_XYZF2,      10) | GIF_REG(SCE_GS_PRIM,       11);

    p->n_tex0.u64[1] = 6;
    p->n_clamp.u64[1] = 8;
}

#ifdef NON_MATCHING
static void InitAllPacket0(AllPacket* p) {
    InitTriangleNormal(&p->normal[0]);
    InitTriangleNormal(&p->normal[1]);
    InitTriangleNormalEnviron(&p->normal_environ[0]);
    InitTriangleNormalEnviron(&p->normal_environ[1]);
    InitTriangleNormalSpecular(&p->normal_specular[0]);
    InitTriangleNormalSpecular(&p->normal_specular[1]);
    InitTriangleNormalEnvironSpecular(&p->normal_environ_specular[0]);
    InitTriangleNormalEnvironSpecular(&p->normal_environ_specular[1]);
    InitTriangleSpecularNormal(&p->specular_normal[0]);
    InitTriangleSpecularNormal(&p->specular_normal[1]);
}
#else
INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", InitAllPacket0);
#endif

static void LoadProgram_Vu0() {
    if (initialized == 0) {
        sceVif0Packet packet;
        sceVif0Packet* pk = &packet;
        sceVif0PkInit(pk, (u_long128*) READ_UNCACHED(&packet_buffer));
        sceVif0PkCall(pk, model3_mpg0_skel_load, 0U);
        sceVif0PkEnd(pk, 0U);
        sceVif0PkTerminate(pk);
        initialized = 1;
    }

    do {

    } while (*D0_CHCR & 0x100);

    *D0_QWC = 0;
    *(u_long**) D0_TADR = (u_long*)&packet_buffer;
    *D0_CHCR = 0x145;

    do {

    } while (*D0_CHCR & 0x100);
}

static void MakeData0()
{
    Lambert0Data *lmdata;
    Lambert1Data *lm1data;
    EMapData *emap;
    SMapData *smap;
    PersData *psdata;

    pAllData_Vu0 = &alldata_Vu0_Dblbuffer[(alldata_Vu0_page ^= 1)];

    /* parallel lights */
    {
        int n = LightNValidParallelMatrices();
        int i;
        for (i = 0; i < n; i++) {
            PLightData *pl =
                (PLightData *) READ_UNCACHED(&pAllData_Vu0->plight[i]);


            LightGetNthViewNLM(pl->nlm, i);

            LightGetNthLCM(pl->lcm, i);
        }
    }

    /* extra lights */
    {
        int n = LightNValidExtras();
        int i;
        for (i = 0; i < n; i++) {
            Light *light = LightNthValidExtra(i);
            ELightData *eldata =
                (ELightData *) READ_UNCACHED(&pAllData_Vu0->elight[i]);


            /* position & direction */
            sceVu0CopyVector(eldata->pos, light->vpos);
            sceVu0CopyVector(eldata->dir, light->vdir);
            /* color */
            sceVu0CopyVector(eldata->col, light->color);
            eldata->param[0] = light->f_ra;
            eldata->param[1] = light->f_rb;
            eldata->param[2] = light->s_a;
            eldata->param[3] = light->s_b;
        }
    }

    /* lambert0 */
    lmdata = (Lambert0Data *) READ_UNCACHED(&pAllData_Vu0->lambert0);

    LightGetNthViewNLM(lmdata->nlm, 0);
    LightGetNthLCM(lmdata->lcm, 0);

    /* lambert1 */
    lm1data = (Lambert1Data *) READ_UNCACHED(&pAllData_Vu0->lambert1);

    sceVu0CopyVector(lm1data->global_ambient,
                     model3_junk.global_ambient);

    lm1data->global_ambient[3] = 128.0f;

    /* environment map */
    emap = (EMapData *) READ_UNCACHED(&pAllData_Vu0->emap);

    sceVu0CopyMatrix(emap->vwm, model3_junk.vwm);
    sceVu0CopyVector(emap->mag, &mag_114);
    sceVu0CopyVector(emap->offset, &offset_115);

    /* shadow map */
    smap = (SMapData *) READ_UNCACHED(&pAllData_Vu0->smap);

    LightGetNthViewNHM(smap->nhm, 0);
    
    /* perspective data */
    psdata = (PersData *) READ_UNCACHED(&pAllData_Vu0->pers);

    sceVu0CopyVector(psdata->vsp[0], model_common_work->vsp[0]);
    sceVu0CopyVector(psdata->vsp[1], model_common_work->vsp[1]);
    sceVu0CopyVector(psdata->vcp[0], model_common_work->vcp[0]);
    sceVu0CopyVector(psdata->vcp[1], model_common_work->vcp[1]);

    sceVu0CopyVector(psdata->xyz_min, model3_junk.xyz_min_wide);
    sceVu0CopyVector(psdata->xyz_max, model3_junk.xyz_max_wide);
    sceVu0CopyVector(psdata->rgba_max, model3_junk.rgba_max);
}

static void MakePartTransferPacket_Vu0(Part *part, sceVif0Packet *pk)
{
    sceVif0PkRef(
        pk,
        (u_long128 *)((u_char *)part + part->packet_offset),
        part->packet_qwc, 0, 0, 0
    );
    {
        int n_cluster_data = part->n_cluster_data;
        ClusterData *cluster_data_top = (ClusterData *)((u_char *)part + part->cluster_data_offset);
        float (*cluster_nodes)[4] = model3_junk.cluster_nodes;
        int i;
        for (i = 0; i < n_cluster_data; i++) {
            ClusterData *cluster_data = &cluster_data_top[i];
            u32 src = cluster_data->src;
            u32 dst = cluster_data->dst;
            u32 n = cluster_data->n;
            sceVif0PkRef(
                pk,
                (u_long128 *)((u_char *)cluster_nodes + (src << 4)),
                n, 0x01000104, dst | (n << 16) | 0x6C000000, 0
            );
        }
    }
    {
        float (*matrices)[4][4] = model_common_work->skeleton_matrices;
        u_short *skeletons = (u_short *)((u_char *)part + part->skeletons_offset);
        int skeleton_no = part->n_skeletons;
        int dst_top = part->data_skeletons_offset;
        int i;
        for (i = 0; i < part->n_skeletons; i++) {
            u16 idx = skeletons[i];
            sceVif0PkRef(
                pk,
                (u_long128 *)(matrices[idx]), 4, 0x01000101,
                (dst_top + i * 4) | 0x6C040000, 0
            );
        }
    }
    {
        u16 *pairs = (u16 *)((u_char *)part + part->skeleton_pairs_offset);
        int dst_top = part->data_skeleton_pairs_offset;
        int i;
        for (i = 0; i < part->n_skeleton_pairs; i++) {
            u16 idx = pairs[i];
            float (*src)[4] = (float (*)[4]) & model_common_work->envelope_matrices[idx];
            sceVif0PkRef(
                pk,
                (u_long128 *)(src), 4, 0x01000101,
                (dst_top + i * 4) | 0x6C040000, 0
            );
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", MakeLambertShadingPacket);

void MakeClipPacket(Part* part, sceVif0Packet* pk) {
    if ((part->backclip != 0) || (model3_junk.view_clip_or != 0)) {
        if (part->backclip == 0) {
            if (model3_junk.view_clip_or != 0) {
                FlipXMTOP(part->backclip);
                sceVif0PkRefMpg(pk, xmtop, &_vu_0_0x0037F980, model3_mpg0_clip0v_size, 0);
                sceVif0PkCnt(pk, 0U);
                sceVif0PkAddCode(pk, xmtop | 0x14000000);
            }
        } else {
            FlipXMTOP(part->backclip);
            sceVif0PkRefMpg(pk, xmtop, &_vu_0_0x0037FB80, model3_mpg0_clip1_size, 0);
            sceVif0PkCnt(pk, 0U);
            sceVif0PkAddCode(pk, xmtop | 0x14000000);
            if (model3_junk.view_clip_or != 0) {
                FlipXMTOP();
                sceVif0PkRefMpg(pk, xmtop, &_vu_0_0x0037FDC0, model3_mpg0_clipv_size, 0);
                sceVif0PkCnt(pk, 0U);
                sceVif0PkAddCode(pk, xmtop | 0x14000000);
            }
        }
    }
}

static void FlipXMTOP() {
    xmtop ^= 0x80;
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", MakeCalcPartPacket);

void KickCalcPartPacket() {
    ktVif0Send(ktVif0PkBufCurrent(), 1);
}

void TransferToSPR() {
    sceDmaChan* toSPR = sceDmaGetChan(9);
    ktVif0Wait2();
    toSPR->sadr = (void*) calc_base;
    sceDmaSendN(toSPR, (void*) VU0_MEM, 240);
    calc_base ^= 0x1000;
}

void PrepareSort() {
    InitAllPacket0(all_packet);
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", SortTriangleNormal);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", SortTriangleNormalEnviron);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", SortTriangleNormalSpecular);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", SortTriangleNormalEnvironSpecular);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", SortTriangleSpecularNormal);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", DrawPart0);

void DrawParts0(struct ktVif1Ot2* ot, Model* model, ModelWork* work) {
    int n_parts; 
    Part * parts_top;

    n_parts = model->n_vu0_parts; // r18
    parts_top = (Part*)((u_int)model + model->vu0_parts_offset); // r19

    if (n_parts != 0) {
        Part* part = parts_top;
        int i; // r20

        LoadProgram_Vu0();

        MakeData0();

        MakeCalcPartPacket(part);
        KickCalcPartPacket();
        PrepareSort();
        for (i = 1; i < (int) n_parts; i++) {
            Part* next = (Part*)((u_int) part + part->size);
            MakeCalcPartPacket(next);
            TransferToSPR();
            KickCalcPartPacket();
            DrawPart0(ot, part, work);
            part = next;
        }
        TransferToSPR();
        DrawPart0(ot, part, work);
    }
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", Model3DrawVu0Parts);

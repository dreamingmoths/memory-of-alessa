#include "model3_vu0_n.h"

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

void InitTriangleNormalSpecular(TriangleNormalSpecular* p) {
    int qwc = 26;

    p->dmatag.u64[0] = DMAnext | qwc;
    p->dmatag.u32[2] = SCE_VIF1_SET_NOP(0);
    p->dmatag.u32[3] = SCE_VIF1_SET_DIRECT(qwc, 0);

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

  p->s_tex0.u64[0] = ((u_long*) model_common_work)[0xc54]; // model_common_work->specular_mapping_tex0
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

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D3EA0);

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

    p->s_tex0.u64[0] = ((u_long*) model_common_work)[0xc54]; // model_common_work->specular_mapping_tex0
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

static void LoadProgram_Vu0(void) {

    sceVif0Packet sp20;
    sceVif0Packet* pk = &sp20;

    sceVif0PkInit(pk, (u_long128*) READ_UNCACHED(&D_01EE30C0));
    if (model3_junk.cluster_nodes2 == 0) {
        func_0011FE80(pk, &D_003B63C0, 0);
    } else {
        func_0011FE80(pk, &D_003BA2C0, 0);
    }
    sceVif0PkEnd(pk, 0);
    sceVif0PkTerminate(pk);

    while (*D0_CHCR & 0x100);

    *D0_QWC = 0;
    *(u_long**) D0_TADR = (u_long*)&D_01EE30C0;
    *D0_CHCR = 0x145;

    while (*D0_CHCR & 0x100);
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", MakeData0);

static void MakePartTransferPacket_Vu0(Part *part, sceVif0Packet *pk)
{
    sceVif0PkRef(
        pk,
        (u_long128 *)((u_char *)part + part->packet_offset),
        part->packet_qwc, 0, 0, 0
    );
    if (func_001CC680() != 0) {

        int n_cluster_data = part->n_cluster_data;
        ClusterData *cluster_data_top =
            (ClusterData *)((u_char *)part + part->cluster_data_offset);
        float (*cluster_nodes)[4] = model3_junk.cluster_nodes;
        int i;

        for (i = 0; i < n_cluster_data; i++) {
            ClusterData *cd = &cluster_data_top[i];

            u32 src = cd->src;
            u32 dst = cd->dst;
            u32 n   = cd->n;

            sceVif0PkRef(
                pk,
                (u_long128 *)((u_char *)cluster_nodes + (src << 4)),
                n,
                0x01000104,
                dst | (n << 16) | 0x6C000000,
                0
            );
        }

        if (model3_junk._unknown_vi00 != NULL) {
            int n_cluster_data = part->n_cluster_data;
            ClusterData *cluster_data_top =
                (ClusterData *)((u_char *)part + part->cluster_data_offset);
            float (*cluster_nodes2)[4] =
                (float (*)[4])model3_junk.cluster_nodes2;
            int i;

            for (i = 0; i < n_cluster_data; i++) {
                ClusterData *cd = &cluster_data_top[i];

                u32 src = cd->src;
                u32 dst = cd->dst + 1;
                u32 n   = cd->n;

                sceVif0PkRef(
                    pk,
                    (u_long128 *)((u_char *)cluster_nodes2 + (src << 4)),
                    n,
                    0x01000104,
                    dst | (n << 16) | 0x6C000000,
                    0
                );
            }
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

static void MakeLambertShadingPacket(Part * part, sceVif0Packet * pk) {
    int n_parallels = LightNValidParallelMatrices();
    int n_extras    = LightNValidExtras();
    int i;
    float brightness;
    Data * lf_data;
        
    if (n_parallels > 0) {
        xmtop ^= 0x80;

        sceVif0PkRefMpg(
            pk,
            xmtop,
            &D_003B5E40,
            model3_mpg0_para_size,
            0
        );
    }

    for (i = 0; i < n_parallels; i++) {

        lf_data = (Data*)&pAllData_Vu0->plight[i];

        sceVif0PkRef(
            pk,
        (    u32 *)lf_data,
            8U,
            0x01000101U,
            (u_int)xitop | 0x6c080000,
            0
        );

        sceVif0PkCnt(pk, 0U);

        sceVif0PkAddCode(pk, xitop | 0x04000000);
        sceVif0PkAddCode(pk, xmtop | 0x14000000);

        xitop ^= 8;
    }

    for (i = 0; i < n_extras; i++) {
        int kind;
        xmtop ^= 0x80;
        kind  = func_001C4E80(i);

        switch (kind) {
        
            /* point light */
            case 10:
            case 11:
                sceVif0PkRefMpg(
                    pk,
                    (u16)xmtop,
                    &D_003B6200,
                    model3_mpg0_point_size,
                    0
                );
                break;
        
            /* spot light */
            case 13:
            case 14:
            case 16:
                sceVif0PkRefMpg(
                    pk,
                    (u16)xmtop,
                    &D_003B6A80,
                    model3_mpg0_spot_size,
                    0
                );
                break;
        }

        lf_data = (Data*)&pAllData_Vu0->elight[i];

        sceVif0PkRef(
            pk,
            (u32 *)lf_data,
            4U,
            0x01000101U,
            xitop | 0x6C040000,
            0
        );

        sceVif0PkCnt(pk, 0U);

        sceVif0PkAddCode(pk, xitop | 0x04000000);
        sceVif0PkAddCode(pk, xmtop | 0x14000000);

        xitop ^= 8;
    }


    xmtop ^= 0x80;

    sceVif0PkRefMpg(
        pk,
        (u16)xmtop,
        &D_003B5D00,
        model3_mpg0_lambert_size,
        0
    );

    lf_data = (Data*)&pAllData_Vu0->lambert0;

    sceVif0PkRef(
        pk,
        (u32 *)lf_data,
        8U,
        0x01000101U,
        xitop | 0x6C080000,
        0
    );

    sceVif0PkCnt(pk, 0U);

    sceVif0PkAddCode(pk, xitop | 0x04000000);
    sceVif0PkAddCode(pk, xmtop | 0x14000000);

    xitop ^= 8;

    brightness = LightReflectionBrightness();

    lf_data = (Data*)&pAllData_Vu0->lambert1;

    sceVif0PkRef(
        pk,
        (u32 *)lf_data,
        1U,
        0x01000101U,
        xitop | 0x6C010000,
        0
    );

    sceVif0PkCnt(pk, 0U);

    sceVif0PkAddCode(pk, 0x01000101U);
    sceVif0PkAddCode(pk, (xitop + 1) | 0x6C030000);

    lf_data = (Data*)sceVif0PkReserve(pk, 0xCU);

    sceVu0CopyVector(lf_data->rgba.fv, part->diffuse);
    lf_data->rgba.fv[3] = 1.0f;
    sceVu0CopyVector((&lf_data[1])->rgba.fv, part->ambient);
    (&lf_data[1])->rgba.fv[3] = 1.0f; 
    (&lf_data[2])->rgba.fv[2]= (part->phong_param_a * brightness); 
    (&lf_data[2])->rgba.fv[3]= (part->phong_param_b * brightness);

    sceVif0PkAddCode(pk, xitop | 0x04000000);
    sceVif0PkAddCode(pk, (xmtop + 2) | 0x14000000);

    xitop ^= 8;
}

static void MakeClipPacket(Part* part, sceVif0Packet* pk) {
    FlipXMTOP();

    if (part->backclip == 0) {
        sceVif0PkRefMpg(pk, xmtop, (u_int*)&D_003B5280, D_003B53B0, 0);
    } else {
        sceVif0PkRefMpg(pk, xmtop, (u_int*)&D_003B55C0, D_003B57D0, 0);

    }

    sceVif0PkCnt(pk, 0);
    sceVif0PkAddCode(pk, xmtop | 0x14000000);
}

static void FlipXMTOP() {
    xmtop ^= 0x80;
}

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

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D4D40);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D4FD0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", SortTriangleNormalEnviron);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D55F0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D5910);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D5C50);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D6000);

void MakeCalcPartPacket(Part *part)
{
    __int128 *packet_buffer = (__int128 *)ktVif0PkBufNext();
    sceVif0Packet packet;        // r29+0x30
    sceVif0Packet *pk = &packet; // r16;
    Data* data;

    sceVif0PkInit(pk, (u_int *)READ_UNCACHED(packet_buffer));

    xitop = 0xF0;
    xmtop = 0x100;
    model3_junk.xtop = (void *)((part->xtop * 0x10) + 0x70000000);

    MakePartTransferPacket_Vu0(part, pk);
    sceVif0PkCnt(pk, 0U);
    sceVif0PkAddCode(pk, part->xtop | 0x04000000);
    sceVif0PkAddCode(pk, xitop | 0x6C010000);
    if (part->shading_type == 1)
    {
        // @todo: these were each one line?
        float tmp, tmp2, tmp3;
        tmp = part->diffuse[0];
        sceVif0PkAddData(pk, *(u32 *)&tmp);
        tmp2 = part->diffuse[1];
        sceVif0PkAddData(pk, *(u32 *)&tmp2);
        tmp3 = part->diffuse[2];
        sceVif0PkAddData(pk, *(u32 *)&tmp3);
    }
    else
    {
        sceVif0PkAddData(pk, 0U);
        sceVif0PkAddData(pk, 0U);
        sceVif0PkAddData(pk, 0U);
    }
    sceVif0PkAddData(pk, 0U);
    sceVif0PkAddCode(pk, 0x14000008U);
    xitop ^= 8;
    switch (part->shading_type)
    {
    case 1:
        break;
    case 2:
    case 3:
    case 4:
        MakeLambertShadingPacket(part, pk);
        break;

    }
    if (part->shading_type == 4)
    {
        xmtop ^= 0x80;
        sceVif0PkRefMpg(pk, xmtop, &D_003B6940, model3_mpg0_specular_size, 0);
        // 
        sceVif0PkRef(pk, (u32 *)&pAllData_Vu0->smap, 4U, 0x01000101U, xitop | 0x6c040000, 0);
        sceVif0PkCnt(pk, 0U);
        sceVif0PkAddCode(pk, 0x01000101U);
        sceVif0PkAddCode(pk, (xitop + 4) | 0x6C010000);
        data = (Data*) sceVif0PkReserve(pk, 4U);
        data->rgba.fv[3] = (f32) part->blinn_param;
        sceVif0PkAddCode(pk, xitop | 0x04000000);
        sceVif0PkAddCode(pk, xmtop | 0x14000000);
        xitop ^= 8;
    }

    if (func_001C91F0() == 0)
    {
        xmtop ^= 0x80;
        sceVif0PkRefMpg(pk, xmtop, &D_003B6080, D_003B61C0, 0);
    }
    else
    {
        xmtop ^= 0x80;
        sceVif0PkRefMpg(pk, (u16)xmtop, &D_003BAB80, D_003BAD60, 0);
        sceVif0PkRef(pk, (u32 *)&pAllData_Vu0->emap, 2U, 0x01000101U, xitop | 0x6c020000, 0);
        sceVif0PkCnt(pk, 0U);
        sceVif0PkAddCode(pk, xitop | 0x04000000);
        sceVif0PkAddCode(pk, xmtop | 0x14000000);
        xitop ^= 8;
        xmtop ^= 0x80;
        sceVif0PkRefMpg(pk, xmtop, &D_003BAD80, D_003BAEB0, 0);
        sceVif0PkAddCode(pk, 0x10000000U);
    }

    sceVif0PkRef(pk, (u32 *)&pAllData_Vu0->pers, 7U, 0x01000101U, xitop | 0x6c070000, 0);
    sceVif0PkCnt(pk, 0U);
    sceVif0PkAddCode(pk, xitop | 0x04000000);
    sceVif0PkAddCode(pk, xmtop | 0x14000000);
    sceVif0PkAddCode(pk, 0x10000000U);
    xitop ^= 8;
    MakeClipPacket(part, pk);
    sceVif0PkCnt(pk, 0U);
    sceVif0PkAddCode(pk, 0x10000000U);
    sceVif0PkEnd(pk, 0U);
    sceVif0PkTerminate(pk);
}

void DrawPart0(ktVif1Ot2* ot, Part* part, ModelWork* work) {
    int func_no = 0;
    sceDmaChan* toSPR;

    if (Model3WorkEquipmentFlag(work, part->equipment_id) == 0) {
        return;
    }

    model3_junk.vi00 = (void*) (draw_base + 0x70000000);

    if (part->envmap_param != 0) {
        func_no |= 1;
    }
    
    if (part->shading_type == 4) {
        func_no |= 2;
        if (part->specular_pos != 0) {
            func_no |= 4;
        }
    }

    if (sort_functions[func_no] != NULL) {
        toSPR = sceDmaGetChan(9);

        while (sceDmaSync(toSPR, 0, 0) != 0);

        (*(void (*)(ktVif1Ot2 *, Part *))sort_functions[func_no])(ot, part);
    }

    draw_base ^= 0x1000;
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", DrawParts0);

void Model3DrawVu0Parts(Model* model, ModelWork* work) {
    ktVif1Ot2* ot = CharacterOt_KtVif1Ot2(model);

    func_001CC5B0();
    func_001CC5F0();
    func_0025C1C0();

    D_01EE3DE0 = 0;
    calc_base = 0;
    draw_base = 0;

    // arguments 2 & 3 seem to be function pointers:
    DrawParts0(ot, work, func_0025CF10(), func_0025CF00());
}


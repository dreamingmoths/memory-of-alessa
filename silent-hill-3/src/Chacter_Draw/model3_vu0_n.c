#include "common.h"
#include "eestruct.h"
#include "eeregs.h"
#include "libgraph.h"
#include "model3_vu0_n.h"
#include "model_common.h"
#include "libdmapk.h"
#include "GFW/sh3gfw_Init_ModelDrawData.h"

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

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D3FA0);

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

    func_0011FD28(pk, (u_long128*) READ_UNCACHED(&D_01EE30C0));
    if (model3_junk.cluster_nodes2 == 0) {
        func_0011FE80(pk, &D_003B63C0, 0);
    } else {
        func_0011FE80(pk, &D_003BA2C0, 0);
    }
    func_0011FEF0(pk, 0);
    func_0011FD38(pk);

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

        if (model3_junk.vi00 != NULL) {
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

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D4760);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D4BD0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D4C80);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D4CA0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D4CD0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D4D30);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D4D40);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D4FD0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", SortTriangleNormalEnviron);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D55F0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D5910);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D5C50);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D6000);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D6110);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", DrawPart0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", DrawParts0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D67E0);

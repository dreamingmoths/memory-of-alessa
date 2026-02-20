#include "common.h"
#include "eestruct.h"
#include "libgraph.h"
#include "model3_vu0_n.h"
#include "model_common.h"

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

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", InitTriangleSpecularNormal);

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

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", LoadProgram_Vu0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", MakeData0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", MakePartTransferPacket_Vu0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", MakeLambertShadingPacket);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", MakeClipPacket);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", FlipXMTOP);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", MakeCalcPartPacket);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", KickCalcPartPacket);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", TransferToSPR);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", PrepareSort);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", SortTriangleNormal);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", SortTriangleNormalEnviron);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", SortTriangleNormalSpecular);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", SortTriangleNormalEnvironSpecular);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", SortTriangleSpecularNormal);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", DrawPart0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", DrawParts0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", Model3DrawVu0Parts);

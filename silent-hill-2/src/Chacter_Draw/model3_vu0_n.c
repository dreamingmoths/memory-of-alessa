#include "common.h"
#include "eestruct.h"
#include "model3_vu0_n.h"

void InitTriangleNormal(TriangleNormal* p) {
    int qwc = 12;
    p->dmatag.u64[0] = 0x2000000C; // 12 quadwords
    p->dmatag.u32[2] = 0;
    p->dmatag.u32[3] = 0x5000000C; // payload?

    p->n_giftag.u64[0] = SCE_GIF_SET_TAG(
        1,
        1,
        1,
        SCE_GS_SET_PRIM(SCE_GS_PRIM_TRI, 1, 1, 1, 1, 0, 0, 0, 0),
        SCE_GIF_PACKED,
        11
    );
    p->n_giftag.u64[1] =
        GIF_REG(SCE_GIF_PACKED_AD, 0)  |
        GIF_REG(SCE_GIF_PACKED_AD, 1)  |
        GIF_REG(SCE_GS_ST,         2)  |
        GIF_REG(SCE_GS_RGBAQ,      3)  |
        GIF_REG(SCE_GS_XYZF2,      4)  |
        GIF_REG(SCE_GS_ST,         5)  |
        GIF_REG(SCE_GS_RGBAQ,      6)  |
        GIF_REG(SCE_GS_XYZF2,      7)  |
        GIF_REG(SCE_GS_ST,         8)  |
        GIF_REG(SCE_GS_RGBAQ,      9)  |
        GIF_REG(SCE_GS_XYZF2,      10) |
        GIF_REG(SCE_GS_PRIM,       11);
    p->n_tex0.s64[1] = 6;
    p->n_clamp.s64[1] = 8;
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", InitTriangleNormalEnviron);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", InitTriangleNormalSpecular);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", InitTriangleNormalEnvironSpecular);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", InitTriangleSpecularNormal);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", InitAllPacket0);

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

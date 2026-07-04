#include "sh2_common.h"

#include "Chacter/character.h"
#include "Chacter/anime.h"

/*
IEEE-754 half floats (16-bit), because why not

bit layout:
    s eeeee cccccccccc

(s = sign, e = exponent, c = coefficient)

1 sign bit / 5 exponent bits / 10 coefficient bits
*/
static float GetSF(void* adr) {
    u_short* sp;
    u_short value;

    int sign;
    int coeff;
    int exp;

    int i;
    FloatOrInt fi;

    sp = adr;
    value = *sp;
    sign = ((value >> 15) & 0b1);
    exp = (value >> 10) & 0b11111;
    coeff = value & 0b1111111111;

    if ((exp + 112 == 0) && ((coeff << 13) == 0)) {
        return 0.0f;
    }

    fi.i = i = (coeff << (23 - 10)) | ((sign << 31) | ((exp + 112) << 23));
    return fi.f;
}

INCLUDE_ASM("asm/nonmatchings/Chacter/anime", shExec);

INCLUDE_ASM("asm/nonmatchings/Chacter/anime", func_0013E5D0);

INCLUDE_ASM("asm/nonmatchings/Chacter/anime", func_0013E9A0);

INCLUDE_ASM("asm/nonmatchings/Chacter/anime", shCharacterAnimeReconstruct);

INCLUDE_ASM("asm/nonmatchings/Chacter/anime", func_0013F170);

void shCharacterAnimeSetSkelton(shAnime3d* ap /* r2 */, shSkelton* stp /* r2 */) {
    ap->top = stp;
    ap[-1].top = stp;
}

INCLUDE_ASM("asm/nonmatchings/Chacter/anime", shCharacterExecAnimeMain);

void shCharacterStayModelExecNthParts(shSkelton* stp /* r17 */, float* pos /* r16 */, float* rot /* r2 */) {
    Vector4 buf;

    buf = *(Vector4*)stp->src_m.d[3];
    stp->src_m.d[3][0] = stp->src_m.d[3][1] = stp->src_m.d[3][2] = 0;

    sceVu0RotMatrix(stp->src_m.d, stp->des_m.d, rot);

    stp->src_m.d[3][0] = pos[0];
    stp->src_m.d[3][1] = pos[1];
    stp->src_m.d[3][2] = pos[2];
    stp->src_t.x = pos[0];
    stp->src_t.y = pos[1];
    stp->src_t.z = pos[2];
}

INCLUDE_ASM("asm/nonmatchings/Chacter/anime", shCharacterAnimePartsControl);

INCLUDE_ASM("asm/nonmatchings/Chacter/anime", func_0013FF50);

INCLUDE_ASM("asm/nonmatchings/Chacter/anime", func_00140060);

INCLUDE_ASM("asm/nonmatchings/Chacter/anime", sh_HEATHER_SetUntouchUpper);

INCLUDE_ASM("asm/nonmatchings/Chacter/anime", sh_HEATHER_SetUntouchUnder);

INCLUDE_ASM("asm/nonmatchings/Chacter/anime", sh_HEATHER_ResetUntouchUnder);

INCLUDE_ASM("asm/nonmatchings/Chacter/anime", func_00140330);

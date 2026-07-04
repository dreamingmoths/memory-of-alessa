#include "common.h"

#include "vec.h"
#include "eeregs.h"
#include "libvu0.h"

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

// @todo: move to vu0 header?
static inline void _sceVu0RotMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1, float rx, float ry, float rz) {
    shRotMatrixZ(m0, m1, rz);
    shRotMatrixY(m0, m0, ry);
    shRotMatrixX(m0, m0, rx);
}

static inline _sceVu0TransposeMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1) {
    asm volatile("\n\
	lq 8,0x00(%1)\n\
	lq 9,0x10(%1)\n\
	lq 10,0x20(%1)\n\
	lq 11,0x30(%1)\n\
	\n\
	pextlw 12,9,8\n\
	pextuw 13,9,8\n\
	pextlw 14,11,10\n\
	pextuw 15,11,10\n\
	\n\
	pcpyld 8,14,12\n\
	pcpyud 9,12,14\n\
	pcpyld 10,15,13\n\
	pcpyud 11,13,15\n\
	\n\
	sq 8,0x00(%0)\n\
	sq 9,0x10(%0)\n\
	sq 10,0x20(%0)\n\
	sq 11,0x30(%0)\n\
	": : "r" (m0) , "r" (m1) : "memory");
}

extern Matrix4 kt_unit_matrix;

void shCharacterAnimePartsControl(shAnime3d* ap, shSkelton* stp, Vector4* rot) {
    Vector4 vec;
    Matrix4 test_mat;
    Matrix4 sp70;
    Vector4 spB0;
    float rx, ry, rz;

    vec_copy(&vec, stp->src_m.d[3]);

    shQzero(stp->src_m.d[3], sizeof(stp->src_m.d[3]));

    rx = -rot->x, ry = -rot->y, rz = -rot->z;
    _sceVu0RotMatrix(sp70.d, kt_unit_matrix.d, rx, ry, rz);
    _sceVu0TransposeMatrix(test_mat.d, sp70.d);
    sceVu0MulMatrix(stp->src_m.d, test_mat.d, stp->src_m.d);

    vec_copy(stp->src_m.d[3], &vec);
}

INCLUDE_ASM("asm/nonmatchings/Chacter/anime", func_0013FF50);

INCLUDE_ASM("asm/nonmatchings/Chacter/anime", func_00140060);

INCLUDE_ASM("asm/nonmatchings/Chacter/anime", sh_HEATHER_SetUntouchUpper);

INCLUDE_ASM("asm/nonmatchings/Chacter/anime", sh_HEATHER_SetUntouchUnder);

INCLUDE_ASM("asm/nonmatchings/Chacter/anime", sh_HEATHER_ResetUntouchUnder);

INCLUDE_ASM("asm/nonmatchings/Chacter/anime", func_00140330);

#include "sh2_common.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2dt.h"

#include "vec.h"
#include "eeregs.h"
#include "libvu0.h"

#include "Chacter/character.h"
#include "Chacter/chara_list.h"
#include "Chacter/anime.h"

#include "Event/demoview.h"

#pragma divbyzerocheck off

// @todo: fix remaining mismatches & clean up the file

#define ANIMATION_TYPE_NONE                  0
#define ANIMATION_TYPE_ROTATION              1
#define ANIMATION_TYPE_ISOMETRY              2 // translation + rotation
#define ANIMATION_TYPE_ROTATION_ABOUT_AXIS   3
#define ANIMATION_TYPE_ISOMETRY_ABOUT_AXIS   4
#define ANIMATION_TYPE_ISOMETRY_ABOUT_AXIS16 5
#define ANIMATION_TYPE_INTERPOLATED_ISOMETRY 6
#define ANIMATION_TYPE_IDENTITY              7

#define ANIMATION_INTERPOLATION_0     0
#define ANIMATION_INTERPOLATION_3     3
#define ANIMATION_INTERPOLATION_5     5
#define ANIMATION_INTERPOLATION_7     7
#define ANIMATION_INTERPOLATION_1     1
#define ANIMATION_INTERPOLATION_NONE -1

#define JAMES_BONE_8  8
#define JAMES_BONE_9  9
#define JAMES_BONE_10 10
#define JAMES_BONE_27 27
#define JAMES_BONE_28 28

#define ANIMATION_TYPE_0 0

static float GetSF(void* adr);
static void shCharacterAnimeInterMatrix(Matrix4* out, Matrix4* in1, Matrix4* in2, float t /* r29+0x20 */);
static void* shExec(void* anime, shSkelton* stp, int inter_type, int* ret);
static void shCharacterAnimeReconstruct(shAnime3d* ap, int inter_type, int type, int frame);
static void EigenVector(Matrix4* m, Vector4* t);
static void EigenVec2Mat(Vector4* ev, Matrix4* smat);
static void shCharacterAnimeCalcComplement(shAnime3d* ap);

static void _sceVu0ApplyMatrix_1(float* dest /* r2 */, float (*mat)[4] /* r2 */, float* src /* r2 */);
static void _sceVu0Normalize(sceVu0FVECTOR v0 /* r2 */, sceVu0FVECTOR v1 /* r2 */);

typedef struct _Gte {
    // total size: 0x40
    Matrix4 matrix; // offset 0x0, size 0x40
} Gte;

extern Matrix4 kt_unit_matrix; // size: 0x40, address: 0x2A7B90
Gte kt_gte;                    // size: 0x40, address: 0x3C7E60

static Vector4 trans_tmp_1111;
static Matrix4 mat_tmp_1112; // @ 0x003C7E10

/* inlines (@todo: find a different for these?) */
static inline float from_q12(void* x) {
    asm("lqc2 vf4, 0(%0); vitof12 vf5, vf4; sqc2 vf5, 0(%0)" : "+r"(x));
    return ((float*)x)[0];
}
static inline float from_q15(void* x) {
    asm("lqc2 vf4, 0(%0); vitof15 vf5, vf4; sqc2 vf5, 0(%0)" : "+r"(x));
    return ((float*)x)[0];
}
static inline float read_float_align2(void* adr) {
    FloatOrInt fi;
    u_short* a = adr;
    fi.i = a[0] | (a[1] << 16);
    return fi.f;
}
static inline int read_int_align2(void* adr) {
    u_short* a = adr;
    return a[0] | (a[1] << 16);
}
static inline float reinterpret_short_as_float(void* adr) {
    FloatOrInt fi;
    short* a = adr;
    fi.i = a[0];
    return fi.f;
}

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

static void shCharacterAnimeInterMatrix(Matrix4* out /* r2 */, Matrix4* in1 /* r2 */, Matrix4* in2 /* r2 */, float t /* r29+0x20 */) {
    Vector4 v1;
    Vector4 v2;
    int i1;
    for (i1 = 0; i1 < 4; i1++) {
        v1 = *(Vector4*)in1->d[i1];
        v2 = *(Vector4*)in2->d[i1];
        vec_lerp(out->d[i1], &v1, &v2, t);
    }
}
void shCharacterStayModelExecItem(shSkelton* stp /* r2 */, float* rot /* r2 */) {
    sceVu0FVECTOR pos = {0.0f, 0.0f, 0.0f, 1.0f};

    shCharacterStayModelExecNthParts(stp, pos, rot);
}

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

static inline void get_inverse_rotation_matrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1, Vector4* rot) {
    sceVu0FVECTOR inv_rot;
    sceVu0FMATRIX mat;
    inv_rot[0] = -rot->x;
    inv_rot[1] = -rot->y;
    inv_rot[2] = -rot->z;
    sceVu0RotMatrix(mat, m1, inv_rot);
    sceVu0TransposeMatrix(m0, mat);
}

static void* shExec(void* anime /* r2 */, shSkelton* stp /* r21 */, int inter_type /* r20 */, int* ret /* r19 */) {
    u_int flag;
    int bits;
    short* sp;
    int type;
    Vector4 rot;
    Vector4 axis;
    shSkelton dummy_st;

    if (anime == NULL)
        return NULL;

    sp = anime;
    flag = read_int_align2(sp);
    sp += 2;
    bits = 8;

    for (; stp != NULL; stp = stp->next) {
        if (bits-- == 0) {
            flag = read_int_align2(sp);
            sp += 2;
            bits = 7;
        }
        type = flag & 0xF;
        flag = flag >> 4;

        stp->is_key = type & 8;
        type &= ~8;

        if (type == ANIMATION_TYPE_NONE) {
            stp->change = 0;
        } else {

            *ret = stp->change = 1;

            if (stp->untouchable != NULL) {
                dummy_st.next = stp->next;
                dummy_st.parent = stp->parent;

                stp = &dummy_st;
            }

            switch (type) {
                case ANIMATION_TYPE_ISOMETRY:
                    if (inter_type == ANIMATION_INTERPOLATION_0) {
                        if (stp->parent != NULL) {
                            stp->src_t.x = GetSF(sp);
                            stp->src_t.y = GetSF(sp + 1);
                            stp->src_t.z = GetSF(sp + 2);
                            stp->src_t.w = 0.0f;
                            sp += 3;
                        } else {
                            stp->src_t.x = read_float_align2(sp);
                            stp->src_t.y = read_float_align2(sp + 2);
                            stp->src_t.z = read_float_align2(sp + 4);
                            stp->src_t.w = 0.0f;
                            sp += 6;
                        }
                    } else {
                        if (stp->parent != NULL) {
                            stp->des_t.x = GetSF(sp);
                            stp->des_t.y = GetSF(sp + 1);
                            stp->des_t.z = GetSF(sp + 2);
                            stp->des_t.w = 0.0f;
                            sp += 3;
                        } else {
                            stp->des_t.x = read_float_align2(sp);
                            stp->des_t.y = read_float_align2(sp + 2);
                            stp->des_t.z = read_float_align2(sp + 4);
                            stp->des_t.w = 0.0f;
                            sp += 6;
                        }
                    }
                    /* fallthrough */
                case ANIMATION_TYPE_ROTATION:
                    rot.x = reinterpret_short_as_float(sp);
                    rot.y = reinterpret_short_as_float(sp + 1);
                    rot.z = reinterpret_short_as_float(sp + 2);
                    sp += 3;

                    from_q12(&rot);

                    if (inter_type == ANIMATION_INTERPOLATION_0) {
                        get_inverse_rotation_matrix(stp->src_m.d, kt_unit_matrix.d, &rot);
                    } else {
                        get_inverse_rotation_matrix(stp->des_m.d, kt_unit_matrix.d, &rot);
                    }
                    break;

                case ANIMATION_TYPE_INTERPOLATED_ISOMETRY:
                    if (stp->parent != NULL) {
                        stp->src_t.x = GetSF(sp);
                        stp->src_t.y = GetSF(sp + 1);
                        stp->src_t.z = GetSF(sp + 2);
                        sp += 3;
                    } else {
                        stp->src_t.x = read_float_align2(sp);
                        stp->src_t.y = read_float_align2(sp + 2);
                        stp->src_t.z = read_float_align2(sp + 4);
                        sp += 6;
                    }
                    goto label_set_destination_translation;

                case ANIMATION_TYPE_ISOMETRY_ABOUT_AXIS:
                    stp->src_t = stp->des_t;

                label_set_destination_translation:

                    if (stp->parent != NULL) {
                        stp->des_t.x = GetSF(sp);
                        stp->des_t.y = GetSF(sp + 1);
                        stp->des_t.z = GetSF(sp + 2);
                        stp->des_t.w = 0.0f;
                        sp += 3;
                    } else {
                        stp->des_t.x = GetSF(sp);
                        stp->des_t.y = GetSF(sp + 2);
                        stp->des_t.z = GetSF(sp + 4);
                        stp->des_t.w = 0.0f;
                        sp += 6;
                    }

                label_rotate_about_axis:
                    rot.x = reinterpret_short_as_float(sp);
                    rot.y = reinterpret_short_as_float(sp + 1);
                    rot.z = reinterpret_short_as_float(sp + 2);
                    sp = sp + 3;

                    from_q12(&rot);

                    if (inter_type == ANIMATION_INTERPOLATION_0) {
                        get_inverse_rotation_matrix(stp->src_m.d, kt_unit_matrix.d, &rot);
                    } else {
                        get_inverse_rotation_matrix(stp->des_m.d, kt_unit_matrix.d, &rot);
                    }
                    axis.x = reinterpret_short_as_float(sp);
                    axis.y = reinterpret_short_as_float(sp + 1);
                    axis.z = reinterpret_short_as_float(sp + 2);
                    sp += 3;

                    from_q15(&axis);
                    stp->axis = axis;

                    rot.x = reinterpret_short_as_float(sp);

                    from_q12(&rot);
                    stp->axis.w = rot.x;

                    sp += 2;

                    break;

                case ANIMATION_TYPE_ROTATION_ABOUT_AXIS:
                    if (inter_type == ANIMATION_INTERPOLATION_0) {
                        stp->src_t = stp->des_t;
                    }
                    goto label_rotate_about_axis;

                case ANIMATION_TYPE_ISOMETRY_ABOUT_AXIS16:
                    if (stp->parent != NULL) {
                        stp->src_t.x = GetSF(sp);
                        stp->src_t.y = GetSF(sp + 1);
                        stp->src_t.z = GetSF(sp + 2);
                        stp->src_t.w = 0.0f;
                        sp += 3;
                    } else {
                        stp->src_t.x = read_float_align2(sp);
                        stp->src_t.y = read_float_align2(sp + 2);
                        stp->src_t.z = read_float_align2(sp + 4);
                        stp->src_t.w = 0.0f;
                        sp += 6;
                    }
                    stp->des_t = stp->src_t;
                    goto label_rotate_about_axis;
            }
        }
    }

    return sp;
}

void shCharacterAnimePartsControl(shAnime3d* ap /* r16 */, shSkelton* stp, Vector4* rot /* r2 */) {
    Matrix4 test_mat; // r29+0x30
    Matrix4 sp70;     // @note not present in dwarf
    Vector4 spB0;     // @note not present in dwarf
    float rx = stp->src_m.d[3][0], ry = stp->src_m.d[3][1], rz = stp->src_m.d[3][2];

    stp->src_m.d[3][2] = stp->src_m.d[3][1] = stp->src_m.d[3][0] = 0;
    spB0.x = -rot->x;
    spB0.y = -rot->y;
    spB0.z = -rot->z;
    sceVu0RotMatrix(sp70.d, kt_unit_matrix.d, &spB0.x);
    sceVu0TransposeMatrix(test_mat.d, sp70.d);

    sceVu0MulMatrix(stp->src_m.d, test_mat.d, stp->src_m.d);
    stp->src_m.d[3][0] = rx;
    stp->src_m.d[3][1] = ry;
    stp->src_m.d[3][2] = rz;
    stp->pad = 0;
}

Vector4 rot_1124_0x003C7E00;
#ifdef NON_MATCHING
static void shCharacterAnimeReconstruct(shAnime3d* ap, int inter_type, int type, int frame) {
    int i = 0;
    int count;
    int inter_rate;
    Matrix4 r_mat;
    shSkelton* stp;
    shSkelton* parent;

    inter_rate = frame * 4096;

    switch (inter_type) {
        case ANIMATION_INTERPOLATION_3:
        case ANIMATION_INTERPOLATION_5:
        case ANIMATION_INTERPOLATION_7:
            count = ap->c_count.y;

            break;
        case ANIMATION_INTERPOLATION_1:
            count = ap->c_count.x;
            break;
        case ANIMATION_INTERPOLATION_NONE:
            count = 0;
            break;
    }

    r_mat.d[0][3] = 0.0f;
    r_mat.d[1][3] = 0.0f;
    r_mat.d[2][3] = 0.0f;

    r_mat.d[3][0] = 0.0f;
    r_mat.d[3][1] = 0.0f;
    r_mat.d[3][2] = 0.0f;
    r_mat.d[3][3] = 1.0f;

    for (stp = ap->top; stp != NULL; stp = stp->next) {
        Vector4* pos;
        Matrix4* mat;
        shSkelton* p_stp;

        if (stp->untouchable == NULL) {
            float delta;
            float s;
            float c;
            float c_1;
            float d;
            float d2;
            Vector4* axis;

            pos = &trans_tmp_1111;
            mat = &mat_tmp_1112;

            delta = (1.0f / inter_rate) * (stp->theta * (frame * 4096 - count));

            c = cosf(delta);
            s = sinf(delta);
            c_1 = 1.0f - c;
            r_mat.d[0][0] = c + (c_1 * stp->xx);
            r_mat.d[1][1] = c + (c_1 * stp->yy);
            r_mat.d[2][2] = c + (c_1 * stp->zz);

            axis = &stp->axis;
            d = axis->z * s;
            d2 = c_1 * stp->xy;
            r_mat.d[1][0] = d2 + d;
            r_mat.d[0][1] = d2 - d;

            d = axis->y * s;
            d2 = c_1 * stp->zx;
            r_mat.d[2][0] = d2 - d;
            r_mat.d[0][2] = d2 + d;

            d = axis->x * s;
            d2 = c_1 * stp->yz;
            r_mat.d[2][1] = d2 + d;
            r_mat.d[1][2] = d2 - d;

            shMulMatrix(mat->d, stp->des_m.d, r_mat.d);

            vec_lerp(mat, &stp->des_t, &stp->src_t, count * (1.0f / inter_rate));

            parent = NULL;

            p_stp = stp->parent;
            stp->src_m.d[3][3] = 1.0f;

            if (p_stp == NULL) {

                if (ap->first_bone_type != 1)
                    stp->src_m.d = mat->d;

                if (type != ANIMATION_TYPE_0) {
                    stp->src_m.d[3][0] = stp->next->src_m.d[3][0];
                    stp->src_m.d[3][1] = stp->next->src_m.d[3][1];
                    stp->src_m.d[3][2] = stp->next->src_m.d[3][2];
                } else {
                    stp->src_m.d[3][0] = pos->x;
                    stp->src_m.d[3][1] = pos->y;
                    stp->src_m.d[3][2] = pos->z;
                }

                if (type != ANIMATION_TYPE_0) {

                    if (i == 0) {
                        Vector4 rot = {0.0f};

                        rot.x = ap->rot_body_neck.x;
                        rot.y = ap->rot_body_neck.y + ap->rot_body.y;
                        shCharacterAnimePartsControl(ap, stp, &rot);
                    }
                }
            } else {

                if (parent != p_stp) {

                    kt_gte.matrix = p_stp->src_m;
                }
                pos->w = 1.0f;
                sceVu0MulMatrix(stp->src_m.d, kt_gte.matrix.d, mat->d);

                _sceVu0ApplyMatrix_1(stp->src_m.d[3], kt_gte.matrix.d, pos);

                stp->src_m.d[3][3] = 1.0f;

                if (type != ANIMATION_TYPE_0) {

                    if (i == 8) {
                        shCharacterAnimePartsControl(ap, stp, &ap->rot_neck);
                    }

                    switch (PlayerGetJamesWeapon()) {
                        case (WEAPON_HANDGUN_CHARA_KIND & 0xFF):
                            if ((i == JAMES_BONE_27) || (i == JAMES_BONE_28)) {
                                shCharacterAnimePartsControl(ap, stp, &ap->rot_arms);
                            }
                            break;
                        case (WEAPON_RIFLGUN_CHARA_KIND & 0xFF):
                            if (i == JAMES_BONE_8 || i == JAMES_BONE_9 || i == JAMES_BONE_10) {
                                shCharacterAnimePartsControl(ap, stp, &ap->rot_arms);
                            }
                    }
                }
            }
        }

        stp->change = 1;

        stp->src_m.d[3][3] = 1.0f;

        i++;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Chacter/anime", shCharacterAnimeReconstruct);
#endif

static void _sceVu0ApplyMatrix_1(float* dest /* r2 */, float (*mat)[4] /* r2 */, float* src /* r2 */) {
    asm("\
        lqc2 vf4, 0x0(a1);\
        lqc2 vf5, 0x10(a1);\
        lqc2 vf6, 0x20(a1);\
        lqc2 vf7, 0x30(a1);\
        lqc2 vf8, 0x0(a2);\
        vmulax.xyzw ACC, vf4, vf8x;\
        vmadday.xyzw ACC, vf5, vf8y;\
        vmaddaz.xyzw ACC, vf6, vf8z;\
        vmaddw.xyzw vf8, vf7, vf0w;\
        sqc2 vf8, 0x0($a0);\
        jr ra;\
        nop");
}

/*
method:
compute all three cross products of columns (c0 x c1, c0 x c1, c1 x c2)
pick the one with the largest absolute value determinant

if at least two of the columns are linearly independent and the matrix has an eigenvector,
the result will be an eigenvector.
otherwise we return the cross product c0 x c1 anyway
*/
static void EigenVector(Matrix4* m, Vector4* t) {
    Matrix4 me;
    float sm[9];
    int maxs;
    float max;
    Vector4 v[2];
    Vector4 nv;
    int i;
    int j;

    // compute A - λI, where λ = 1.
    me.d[0][0] = m->d[0][0] - 1.0f;
    me.d[0][1] = m->d[0][1];
    me.d[0][2] = m->d[0][2];
    me.d[1][0] = m->d[1][0];
    me.d[1][1] = m->d[1][1] - 1.0f;
    me.d[1][2] = m->d[1][2];
    me.d[2][0] = m->d[2][0];
    me.d[2][1] = m->d[2][1];
    me.d[2][2] = m->d[2][2] - 1.0f;

    /*
    adjugate matrix
    ( a b c )
    ( d e f )
    ( g h i )

    Σ_{j=1}^m (-1)^(i+j) a_{i,j} M_{i,j}
    */

    // ef - hi
    sm[0] = me.d[1][1] * me.d[2][2] - me.d[2][1] * me.d[1][2];

    // be - hc
    sm[1] = me.d[0][1] * me.d[2][2] - me.d[2][1] * me.d[0][2];

    // bf - ec
    sm[2] = me.d[0][1] * me.d[1][2] - me.d[1][1] * me.d[0][2];

    // di - gf
    sm[3] = me.d[1][0] * me.d[2][2] - me.d[2][0] * me.d[1][2];

    // ai - gc
    sm[4] = me.d[0][0] * me.d[2][2] - me.d[2][0] * me.d[0][2];

    // af - dc
    sm[5] = me.d[0][0] * me.d[1][2] - me.d[1][0] * me.d[0][2];

    // dh - ge
    sm[6] = me.d[1][0] * me.d[2][1] - me.d[2][0] * me.d[1][1];

    // ah - gb
    sm[7] = me.d[0][0] * me.d[2][1] - me.d[2][0] * me.d[0][1];

    // ae - db
    sm[8] = me.d[0][0] * me.d[1][1] - me.d[1][0] * me.d[0][1];

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (sm[j + i * 3] < 0.0f) {
                sm[j + i * 3] = -sm[j + i * 3];
            }
        }
    }

    maxs = 0;
    max = sm[0];
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (max < sm[j + (i * 3)]) {
                maxs = j + (i * 3);
                max = sm[j + (i * 3)];
            }
        }
    }

    switch (maxs) {
        case 6:
        case 7:
        case 8:
            v[0].x = me.d[0][0];
            v[0].y = me.d[1][0];
            v[0].z = me.d[2][0];
            v[1].x = me.d[0][1];
            v[1].y = me.d[1][1];
            v[1].z = me.d[2][1];
            break;

        case 3:
        case 4:
        case 5:
            v[0].x = me.d[0][0];
            v[0].y = me.d[1][0];
            v[0].z = me.d[2][0];
            v[1].x = me.d[0][2];
            v[1].y = me.d[1][2];
            v[1].z = me.d[2][2];
            break;

        case 0:
        case 1:
        case 2:
            v[0].x = me.d[0][1];
            v[0].y = me.d[1][1];
            v[0].z = me.d[2][1];
            v[1].x = me.d[0][2];
            v[1].y = me.d[1][2];
            v[1].z = me.d[2][2];
            break;
    }
    vec_cross_product_reverse(&v[1], &v[0], &nv);
    _sceVu0Normalize(t, &nv);
}

static void _sceVu0Normalize(sceVu0FVECTOR v0 /* r2 */, sceVu0FVECTOR v1 /* r2 */) {
    asm volatile("lqc2    vf4,0x0(%1)\n\
        vmul.xyz vf5,vf4,vf4\n\
        vaddy.x vf5,vf5,vf5\n\
        vaddz.x vf5,vf5,vf5\n\
        vrsqrt Q, vf0w, vf5x\n\
        vsub.w vf4, vf0, vf0\n\
        vwaitq\n\
        vmulq.xyz  vf4,vf4,Q\n\
        sqc2    vf4,0x0(%0)\n\
        " : : "r"(v0), "r"(v1) : "memory");
}

#ifdef NON_MATCHING
static void EigenVec2Mat(Vector4* ev, Matrix4* smat) {
    Vector4 v1, v2;
    Vector4 mv0, mv1, mv2;

    _sceVu0Normalize(&mv0, ev);

    smat->d[0][0] = mv0.x;
    smat->d[0][1] = mv0.y;
    smat->d[0][2] = mv0.z;

    if (fabsf(mv0.y) > fabsf(mv0.x)) {
        if (fabsf(mv0.x) > fabsf(mv0.z)) {
            v1.x = mv0.y;
            v1.y = -mv0.x;
            if (mv0.z)
                v1.z = -(mv0.x * v1.x + mv0.y * v1.y) / mv0.z;
            else
                v1.z = 0.0f;
        } else {
            if (mv0.y) {
                v1.z = mv0.y;
                v1.y = -mv0.z;
            } else {
                v1.z = -mv0.y;
                v1.y = mv0.z;
            }
            if (mv0.x)
                v1.x = -(mv0.z * v1.z + mv0.y * v1.y) / mv0.x;
            else
                v1.x = 0;
        }
    } else {
        if (fabsf(mv0.y) > fabsf(mv0.z)) {
            v1.x = mv0.y;
            v1.y = -mv0.x;
            if (mv0.z)
                v1.z = -(mv0.x * v1.x + mv0.y * v1.y) / mv0.z;
            else
                v1.z = 0.0f;
        } else {
            if (mv0.z) {
                v1.x = mv0.z;
                v1.z = -mv0.x;
            } else {
                v1.x = -mv0.z;
                v1.z = mv0.x;
            }
            if (mv0.y)
                v1.y = -(mv0.x * v1.x + mv0.z * v1.z) / mv0.x;
            else
                v1.y = 0.0f;
        }
    }

    _sceVu0Normalize(&mv1, &v1);

    smat->d[1][0] = mv1.x;
    smat->d[1][1] = mv1.y;
    smat->d[1][2] = mv1.z;

    vec_cross_product_reverse(&mv1, &mv0, &v2);

    _sceVu0Normalize(&mv2, &v2);

    smat->d[2][0] = mv2.x;
    smat->d[2][1] = mv2.y;
    smat->d[2][2] = mv2.z;

    smat->d[3][0] = 0.0f;
    smat->d[3][1] = 0.0f;
    smat->d[3][2] = 0.0f;
    smat->d[3][3] = 1.0f;
    smat->d[0][3] = 0.0f;
    smat->d[1][3] = 0.0f;
    smat->d[2][3] = 0.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/Chacter/anime", EigenVec2Mat);
#endif

static inline void vu0_transpose_matrix(sceVu0FMATRIX out, sceVu0FMATRIX matrix) {
    asm("
        lq t0, 0x00(%1);\
        lq t1, 0x10(%1);\
        lq t2, 0x20(%1);\
        lq t3, 0x30(%1);\
        pextlw t4, t1, t0;\
        pextuw t5, t1, t0;\
        pextlw t6, t3, t2;\
        pextuw t7, t3, t2;\
        pcpyld t0, t6, t4;\
        pcpyud t1, t4, t6;\
        pcpyld t2, t7, t5;\
        pcpyud t3, t5, t7;\
        sq t0, 0x00(%0);\
        sq t1, 0x10(%0);\
        sq t2, 0x20(%0);\
        sq t3, 0x30(%0)": "=r"(out): "r"(matrix): "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7");
}

static inline vec_square(sceVu0FVECTOR vec) {
    asm("lqc2 vf4, 0(%0);\
        vmove vf5, vf4;\
        vmul vf6, vf4, vf5;\
        sqc2 vf6, 0(%0)" : "+r"(vec));
}

static void shCharacterAnimeCalcComplement(shAnime3d* ap) {
    shSkelton* stp;
    Matrix4 mat;
    Matrix4 eig;
    Matrix4 ieig;
    Vector4 axis;
    float theta;

    for (stp = ap->top; stp != NULL; stp = stp->next) {
        if (stp->untouchable != NULL)
            continue;

        vu0_transpose_matrix(mat.d, stp->des_m.d);
        shMulMatrix(mat.d, mat.d, stp->src_m.d);
        EigenVector(&mat, &axis);
        EigenVec2Mat(&axis, &eig);
        vu0_transpose_matrix(ieig.d, eig.d);
        shMulMatrix(mat.d, ieig.d, mat.d);
        shMulMatrix(mat.d, mat.d, eig.d);
        stp->theta = -atan2f(mat.d[1][2], mat.d[1][1]);
        stp->axis = axis;
        stp->xy = axis.x * axis.y;
        stp->yz = axis.y * axis.z;
        stp->zx = axis.z * axis.x;
        vec_square(&axis);
        stp->xx = axis.x;
        stp->yy = axis.y;
        stp->zz = axis.z;
    }
}

void shCharacterAnimeSetSkelton(shAnime3d* ap /* r2 */, shSkelton* stp /* r2 */) {
    ap->top = stp;
    ap[-1].top = stp;
}

int shCharacterDramaAnimeExecMain(shAnime3d* ap) {

    int dt = shGetDF();
    int inter_cont;
    short src_frame, des_frame;
    shSkelton* stp;
    void* adr;
    int result = 0;
    int frame = 0;
    u_short a1;

    switch (ap->comp_type) { /* irregular */
        case -1:

            frame = ap->cur_frame.y - ap->cur_frame.x != 0 ? ap->cur_frame.y - ap->cur_frame.x : 1;
            shCharacterAnimeReconstruct(ap, 1, 0, frame);
            break;

        case 0:
            adr = ap->frame_top;

            shExec(adr, ap->top, 0, &result);
            shExec(adr, ap->top, 1, &result);
            ap->comp_type = -1;
            break;

        case 1:
            src_frame = ap->cur_frame.x;
            a1 = ap->cur_frame.y, des_frame = a1;
            if (ap->cur_frame.x == a1)
                inter_cont = 1;
            else
                inter_cont = 0;

            ap->total_speed.x = dt * (ap->anim_b->speed + ap->c_speed.x);
            ap->c_count.x += ap->total_speed.x;

            frame = (ap->cur_frame.y - ap->cur_frame.x != 0) ? ap->cur_frame.y - ap->cur_frame.x : 1;

            while (ap->c_count.x >= frame << 0xC) {
                ap->cur_frame.x += frame & 0xFFFF;
                ap->c_count.x -= frame << 0xC;
                inter_cont = 1;
            }
            ap->total_count += ap->total_speed.x;

            if (ap->cur_frame.x >= ap->anim_b->end) {
                ap->cur_frame.x = ap->anim_b->end;
                ap->total_count = ap->cur_frame.x << 0xC;
                ap->c_count.x = 0;
                ap->comp_type = -1;
            }

            if ((demo_status >> 6) & 1) {
                ap->cur_frame.x = ap->anim_b->end;
                inter_cont = 1;
            }

            if (ap->anim_b->loop == 1) {
                ap->total_count = ap->total_count % (ap->anim_b->frame << 0xC);
            } else {
                ap->total_count = (ap->total_count > (ap->anim_b->end << 0xC)) ? (ap->anim_b->end << 0xC) : ap->total_count;

                if (ap->total_count == (ap->anim_b->end << 0xC)) {
                    ap->c_count.x = 0;
                    ap->cur_frame.x = ap->anim_b->end;
                }
            }

            if (inter_cont != 0) {

                ap->cur_frame.x %= ap->anim_b->frame;

                if (des_frame != ap->cur_frame.x) {

                    for (stp = ap->top; stp != NULL; stp = stp->next) {
                        if (stp->untouchable == NULL) {
                            stp->src_m = stp->des_m;
                            stp->src_t = stp->des_t;
                        }
                    }

                    adr = ap->frame_top;

                    while (ap->cur_frame.y != ap->cur_frame.x) {
                        adr = shExec(adr, ap->top, 0, &result);
                        ap->cur_frame.y++;
                    }
                    ap->frame_top = adr;

                    for (stp = ap->top; stp != NULL; stp = stp->next) {
                        if (stp->untouchable == NULL) {
                            stp->des_m = stp->src_m;
                            stp->des_t = stp->src_t;
                        }
                    }

                } else {

                    for (stp = ap->top; stp != NULL; stp = stp->next) {
                        if (stp->untouchable == NULL) {
                            stp->src_m = stp->des_m;
                            stp->src_t = stp->des_t;
                        }
                    }
                }

                adr = ap->frame_top;

                result = 0;
                frame = 0;

                while (!result) {
                    ap->cur_frame.y++;
                    frame++;
                    adr = shExec(adr, ap->top, 1, &result);
                    if (ap->cur_frame.y == ap->anim_b->end)
                        break;
                }

                if (ap->anim_b->loop == 1) {
                    ap->cur_frame.y %= ap->anim_b->frame;
                } else {
                    if (ap->cur_frame.x == (ap->anim_a->frame - 1)) {
                        ap->comp_type = -1;
                    }
                    if (ap->cur_frame.y == ap->anim_b->frame) {
                        ap->cur_frame.y--;
                    }
                }

                ap->frame_top = adr;
                shCharacterAnimeCalcComplement(ap);
            }

            shCharacterAnimeReconstruct(ap, 1, 0, frame);

            break;

        case 2:
            adr = ap->frame_top;
            ap->frame_top = shExec(adr, ap->top, 0, &result);

            result = 0;
            while (!result) {
                adr = shExec(adr, ap->top, 1, &result);
                frame++;
                if (ap->anim_b->end == frame) {
                    break;
                }
            }

            ap->frame_top = adr;
            ap->cur_frame.y += frame & 0xFFFF;
            ap->comp_type = 1;

            shCharacterAnimeCalcComplement(ap);

            shCharacterAnimeReconstruct(ap, 1, 0, frame);

            if (GET_BIT(demo_status, 6)) {
                shCharacterDramaAnimeExecMain(ap);
            }
    }

    return 0;
}

int shCharacterPlayingAnimeExecMain(shAnime3d* ap, int type) {

    int dt = shGetDF();
    Matrix4 backup[41];
    float t;
    int i1;
    int inter_cont;
    int result;
    short src_frame;
    short des_frame;
    shSkelton* stp;

    switch (ap->comp_type) { /* switch 1 */
        case -1:             /* switch 1 */
            shCharacterAnimeReconstruct(ap, 1, type, 1);
            break;
        case 0: {
            void* adr = ap->frame_top;

            adr = shExec(adr, ap->top, 0, &result);
            adr = shExec(adr, ap->top, 1, &result);
            ap->cur_frame.y++;
            ap->comp_type = 1;
            ap->frame_top = adr;

            shCharacterAnimeCalcComplement(ap);
            shCharacterAnimeReconstruct(ap, 1, type, 1);
            break;
        }

        case 1: {
            int start;
            int end;
            int t_count;
            u_short var_a0, var_v1;

            var_a0 = ap->cur_frame.x, src_frame = var_a0;
            var_v1 = ap->cur_frame.y, des_frame = var_v1;

            inter_cont = var_a0 == var_v1;

            start = ap->anim_b->start;
            end = ap->anim_b->end;

            ap->c_count.x = ap->total_count % 4096;
            ap->cur_frame.x = start + (ap->total_count >> 0xC);

            if ((ap->cur_frame.x != src_frame) && (ap->comp_type != -1))
                inter_cont = 1;
            if (ap->anim_b->pad == -1)
                inter_cont = 1;

            if (inter_cont != 0) {

                ap->cur_frame.y = ap->cur_frame.x + 1;

                if (ap->anim_b->loop == 1) {
                    if (ap->cur_frame.x == end) {
                        ap->cur_frame.y = start;
                    }

                } else {
                    if (ap->cur_frame.x == end) {
                        ap->cur_frame.y = ap->cur_frame.x;
                    }
                }

                if (ap->total_speed.x < 0) {

                    ap->frame_top = (u_char*)ap->anime + (ap->frame_size * ap->cur_frame.x);

                    shExec(ap->frame_top, ap->top, 0, &result);
                    ap->frame_top = (u_char*)ap->anime + (ap->frame_size * ap->cur_frame.y);

                    shExec(ap->frame_top, ap->top, 1, &result);
                } else {

                    if ((ap->cur_frame.x == (start + (short)(des_frame))) && (ap->anim_b->pad != -1)) {

                        for (stp = ap->top; stp != NULL; stp = stp->next) {
                            if (stp->untouchable == NULL) {
                                stp->src_m.d = stp->des_m.d;
                                stp->src_t = stp->des_t;
                            }
                        }
                        ap->frame_top = (u_char*)ap->anime + (ap->frame_size * ap->cur_frame.y);

                        shExec(ap->frame_top, ap->top, 1, &result);
                    } else {

                        ap->frame_top = (u_char*)ap->anime + (ap->frame_size * ap->cur_frame.x);

                        shExec(ap->frame_top, ap->top, 0, &result);
                        ap->frame_top = (u_char*)ap->anime + (ap->frame_size * ap->cur_frame.y);

                        shExec(ap->frame_top, ap->top, 1, &result);
                    }
                }
                shCharacterAnimeCalcComplement(ap);
            }

            shCharacterAnimeReconstruct(ap, 1, type, 1);

            if (ap->comp_type != -1) {

                ap->total_speed.x = dt * (ap->anim_b->speed + ap->c_speed.x);

                ap->total_count += ap->total_speed.x;
            }

            t_count = ap->total_count;

            if (ap->anim_b->loop == 1) {

                if (t_count < 0) {
                    t_count += ((end - start) + 1) * 4096;
                } else if (t_count >= ((end - start) + 1) * 4096) {
                    t_count -= ((end - start) + 1) * 4096;
                }
            } else if (t_count <= 0) {
                t_count = 0;
                ap->comp_type = -1;
                ap->cur_frame.x = start;
            } else if (t_count >= (end - start) * 4096) {
                t_count = (end - start) * 4096;
                ap->comp_type = -1;
            }

            ap->total_count = t_count;

            break;
        }

        case 3: /* switch 1 */
        case 5: /* switch 1 */
        case 7: /* switch 1 */
            if (ap->comp_type == 5) {
                ap->total_speed.y = 4096;
            } else {
                ap->total_speed.y = (ap->c_speed.y + 0x200) * dt;
            }

            ap->c_count.y += ap->total_speed.y;

            if (ap->c_count.y >= 4096) {
                int comp_tmp = ap->comp_type;
                switch (comp_tmp) {
                    case 3:

                        if (ap->anim_b->speed < 0) {
                            ap->total_count = (ap->anim_b->end - ap->anim_b->start) * 4096;

                        } else {
                            ap->total_count = 0;
                        }

                        ap->c_count.x = 0;
                        ap->c_speed.x = 0;
                        break;

                    case 5:
                        break;

                    case 7:
                        ap->total_count = ap[1].total_count;
                        ap->c_count.x = ap[1].c_count.x;
                        ap->c_speed.x = ap[1].c_speed.x;
                        ap->cur_frame.y = ap[1].cur_frame.y;
                        break;
                }

                ap->c_speed.y = 0;
                ap->c_count.y = 0;
                ap->total_speed.x = dt * (ap->anim_b->speed + ap->c_speed.x);

                ap->total_speed.y = 0;
                ap->cur_frame.x = ap->cur_frame.y;
                ap->anim_a = ap->anim_b;
                ap->comp_type = 1;
                shCharacterPlayingAnimeExecMain(ap, type);
                if (comp_tmp == 7) {

                    ap->total_count = ap[1].total_count;
                    ap->c_count.x = ap[1].c_count.x;
                    ap->c_speed.x = ap[1].c_speed.x;
                    ap->cur_frame.y = ap[1].cur_frame.y;
                }
            } else {

                if (ap->comp_type == 7) {
                    shExec(ap->p_frame_top, ap->top, 0, &result);
                    ap->frame_top = ap[1].frame_top;
                    shExec(ap->frame_top, ap->top, 1, &result);
                    shCharacterAnimeCalcComplement(ap);
                }
                shCharacterAnimeReconstruct(ap, 3, type, 1);
            }

            break;

        case 4: /* switch 1 */
        case 6: /* switch 1 */
        case 8: /* switch 1 */
            if (ap->anim_a->speed > 0) {

                for (stp = ap->top; stp != NULL; stp = stp->next) {
                    if (stp->untouchable == NULL) {
                        stp->src_m.d = stp->des_m.d;
                        stp->src_t = stp->des_t;
                    }
                }
            } else {

                ap->p_frame_top = (u_char*)ap->p_anime + (ap->frame_size * ap->cur_frame.x);

                shExec(ap->p_frame_top, ap->top, 0, &result);
            }

            if (ap->comp_type == 8) {
                ap->frame_top = ap[1].frame_top;
            }
            shExec(ap->frame_top, ap->top, 1, &result);

            shCharacterAnimeCalcComplement(ap);

            ap->comp_type--;

            shCharacterAnimeReconstruct(ap, 3, type, 1);
            break;

        case 9: {
            int start;
            int end;
            int t_count;
            int c_frame_x;
            int c_frame_y;
            int count;

            count = *T0_COUNT;

            start = ap->anim_b->start;
            end = ap->anim_b->end;

            ap->c_count.x = ap->total_count % 4096;

            c_frame_x = ap->total_count >> 0xC;
            c_frame_y = c_frame_x + 1;

            if (c_frame_x == end - start) {
                c_frame_y = 0;
            }

            ap->cur_frame.x = start + c_frame_x;
            ap->cur_frame.y = start + c_frame_y;

            ap->total_speed.x = dt * (ap->anim_b->speed + ap->c_speed.x);
            ap->total_count += ap->total_speed.x;

            t_count = ap->total_count;

            if (t_count < 0) {
                t_count += (end - start + 1) * 4096;
            } else if (t_count >= (end - start + 1) * 4096) {
                t_count -= (end - start + 1) * 4096;
            }

            ap->total_count = t_count;

            ap->total_speed.y = ap->c_speed.y * dt;
            ap->c_count.y += ap->total_speed.y;

            if (ap->c_count.y >= 4096) {

                ap->c_count.y = 0;
                ap->total_speed.y = 0;
                ap->c_speed.y = 0;
                ap->comp_type = 1;
                ap->anim_a = ap->anim_b;

                ap->cur_frame.y = ap->cur_frame.x;
                shCharacterPlayingAnimeExecMain(ap, type);

            } else {

                ap->p_frame_top = (u_char*)ap->anime + (ap->frame_size * (c_frame_x + ap->anim_a->start));

                shExec(ap->p_frame_top, ap->top, 0, &result);
                ap->frame_top = (u_char*)ap->anime + (ap->frame_size * (c_frame_x + ap->anim_b->start));

                shExec(ap->frame_top, ap->top, 1, &result);

                shCharacterAnimeCalcComplement(ap);

                shCharacterAnimeReconstruct(ap, 3, type, 1);

                i1 = 0;
                for (stp = ap->top; stp != NULL; stp = stp->next) {
                    if (stp->untouchable == NULL) {
                        backup[i1] = stp->src_m;
                    }
                    i1++;
                }

                ap->p_frame_top = (u_char*)ap->anime + (ap->frame_size * (c_frame_y + ap->anim_a->start));

                shExec(ap->p_frame_top, ap->top, 0, &result);
                ap->frame_top = (u_char*)ap->anime + (ap->frame_size * (c_frame_y + ap->anim_b->start));

                shExec(ap->frame_top, ap->top, 1, &result);

                shCharacterAnimeCalcComplement(ap);

                shCharacterAnimeReconstruct(ap, 3, type, 1);

                i1 = 0;
                t = ap->c_count.x * (1.0f / 4096.0f);
                for (stp = ap->top; stp != NULL; stp = stp->next) {
                    if (stp->untouchable == NULL) {
                        shCharacterAnimeInterMatrix(&stp->src_m, &stp->src_m, &backup[i1], t);
                    }
                    i1++;
                }
            }

            break;
        }

        case 10: {
            int start;
            int end;
            int t_count;
            int c_frame_x;
            int c_frame_y;

            start = ap->anim_b->start;
            end = ap->anim_b->end;

            ap->c_count.x = ap->total_count % 4096;

            c_frame_x = (int)ap->total_count >> 0xC;
            c_frame_y = c_frame_x + 1;

            if (c_frame_x == end - start) {
                c_frame_y = 0;
            }

            ap->cur_frame.x = start + c_frame_x;
            ap->cur_frame.y = start + c_frame_y;

            ap->total_speed.x = dt * (ap->anim_b->speed + ap->c_speed.x);
            ap->total_count += ap->total_speed.x;

            t_count = ap->total_count;

            if (t_count < 0) {
                t_count += (end - start + 1) * 4096;
            } else if (t_count >= (end - start + 1) * 4096) {
                t_count -= (end - start + 1) * 4096;
            }

            ap->total_count = t_count;

            ap->total_speed.y = ap->c_speed.y * dt;
            ap->c_count.y += ap->total_speed.y;

            ap->p_frame_top = (u_char*)ap->anime + (ap->frame_size * (c_frame_x + ap->anim_a->start));

            shExec(ap->p_frame_top, ap->top, 0, &result);
            ap->frame_top = (u_char*)ap->anime + (ap->frame_size * (c_frame_x + ap->anim_b->start));

            shExec(ap->frame_top, ap->top, 1, &result);

            shCharacterAnimeCalcComplement(ap);

            shCharacterAnimeReconstruct(ap, 3, type, 1);

            i1 = 0;
            for (stp = ap->top; stp != NULL; stp = stp->next) {
                if (stp->untouchable == NULL) {
                    backup[i1] = stp->src_m;
                }
                i1++;
            }

            ap->p_frame_top = (u_char*)ap->anime + (ap->frame_size * (c_frame_y + ap->anim_a->start));

            shExec(ap->p_frame_top, ap->top, 0, &result);
            ap->frame_top = (u_char*)ap->anime + (ap->frame_size * (c_frame_y + ap->anim_b->start));

            shExec(ap->frame_top, ap->top, 1, &result);

            shCharacterAnimeCalcComplement(ap);

            shCharacterAnimeReconstruct(ap, 3, type, 1);

            i1 = 0;
            t = ap->c_count.x * (1.0f / 4096.0f);
            for (stp = ap->top; stp != NULL; stp = stp->next) {
                if (stp->untouchable == NULL) {
                    shCharacterAnimeInterMatrix(&stp->src_m, &stp->src_m, &backup[i1], t);
                }

                i1++;
            }

            ap->comp_type = 9;

            break;
        }

        case 2: /* switch 1 */
            if (ap->comp_type != -1) {

                ap->total_speed.x = dt * (ap->anim_b->speed + ap->c_speed.x);

                ap->total_count += ap->total_speed.x;
            }

            ap->comp_type = 1;
            shCharacterPlayingAnimeExecMain(ap, type);
            break;
    }

    if (ap->total_count < 0) {
        printf("%d %d \n", ap->total_count, ap->comp_type);
    }
    ASSERT_ON_LINE(ap->total_count >= 0, 2110);

    return 0;
}

void shCharacterStayModelScale(shAnime3d* ap /* r2 */) {
    float scale = ap->scale;
    shSkelton* stp;

    for (stp = ap->top; stp != NULL; stp = stp->next) {
        sceVu0ScaleVectorXYZ(stp->src_m.d[0], stp->src_m.d[0], scale);
        sceVu0ScaleVectorXYZ(stp->src_m.d[1], stp->src_m.d[1], scale);
        sceVu0ScaleVectorXYZ(stp->src_m.d[2], stp->src_m.d[2], scale);
        sceVu0ScaleVectorXYZ(stp->des_m.d[0], stp->des_m.d[0], scale);
        sceVu0ScaleVectorXYZ(stp->des_m.d[1], stp->des_m.d[1], scale);
        sceVu0ScaleVectorXYZ(stp->des_m.d[2], stp->des_m.d[2], scale);
    }
}
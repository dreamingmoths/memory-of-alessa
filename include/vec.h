#ifndef SILENT_VEC_H
#define SILENT_VEC_H

/**
 * miscellaneous vector functions. all of the vector functions in common.h may
 * eventually be moved here
 */

static inline void vu0_add_vector(sceVu0FVECTOR v0, sceVu0FVECTOR v1, sceVu0FVECTOR v2) {
    asm volatile("\
	lqc2      vf4,0x0(%1)\n\
	lqc2      vf5,0x0(%2)\n\
	vadd.xyzw vf4,vf4,vf5\n\
	sqc2      vf4,0x0(%0)\n\
	": : "r" (v0) , "r" (v1), "r" (v2) : "memory");
}

static inline void vu0_sub_vector(sceVu0FVECTOR v0, sceVu0FVECTOR v1, sceVu0FVECTOR v2) {
    asm volatile("\
	lqc2      vf4,0x0(%1)\n\
	lqc2      vf5,0x0(%2)\n\
	vsub.xyzw vf4,vf4,vf5\n\
	sqc2      vf4,0x0(%0)\n\
	": : "r" (v0) , "r" (v1), "r" (v2) : "memory");
}

static inline float vec_normalize(float* out, float* in) {
    asm("lqc2 vf4, 0(%0)\n\
        vmul.xyz vf5, vf4, vf4\n\
        vaddy.x vf5, vf5, vf5y\n\
        vaddz.x vf5, vf5, vf5z\n\
        vrsqrt Q, vf0w, vf5x\n\
        vwaitq\n\
        vmulq.xyz vf4, vf4, Q\n\
        sqc2 vf4, 0(%1)"
        : "=r"(out), "+r"(in));
}

static inline float vec_cross_product(float* v, float* w, float* out) {
    asm("lqc2 vf5, 0(%0)\n\
        lqc2 vf6, 0(%1)\n\
        vsub.w vf4, vf0, vf0\n\
        vopmula.xyz ACC, vf5, vf6\n\
        vopmsub.xyz vf4, vf6, vf5\n\
        sqc2 vf4, 0(%2)"
        : "+r"(v), "+r"(w), "=r"(out));
}

static inline float vec_cross_product_reverse(float* w, float* v, float* out) {
    asm("lqc2 vf5, 0(%1)\n\
        lqc2 vf6, 0(%2)\n\
        vsub.w vf4, vf0, vf0\n\
        vopmula.xyz ACC, vf5, vf6\n\
        vopmsub.xyz vf4, vf6, vf5\n\
        sqc2 vf4, 0(%0)"
        : "=r"(out): "r"(v), "r"(w));
}

static inline void vec_copy_reverse(void* src, void* dst) {
    asm("\
         lq t7, 0(%1)\n\
         sq t7, 0(%0)"
        : "+r"(dst), "+r"(src)::"t7");
}

static inline void vec_copy_vu0(void* dst, void* src) {
    asm("\
         lqc2 vf4, 0(%1)\n\
         vmove.w vf4, vf0\n\
         sqc2 vf4, 0(%0)"
        : "+r"(dst), "+r"(src));
}

static inline void vec_copy_xyz(void* dst, void* src) {
    asm("\
         lq t7, 0(%1)\n\
         sd t7, 0(%0)\n\
         pcpyud t7, t7, zero\n\
         sw t7, 8(%0)"
        : "+r"(dst), "+r"(src)::"t7");
}

static inline float vec3_length(void* v) {
    float d;
    asm("lwc1    %1,0(%0)\n\
        lwc1     f8,4(%0)\n\
        lwc1     f9,8(%0)\n\
        mula.s   %1,%1;\
        madda.s  f8,f8\n\
        madd.s   %1,f9,f9\n\
        sqrt.s   %1, %1"
        : "+r"(v), "+f"(d)::"f8", "f9");
    return d;
}

// @todo: combine with the inline from `vc_play.h`
static inline float vec2_length(float* a, float* b) {
    float result;
    asm volatile("lwc1   $f13,0(%1)\n\
        lwc1   $f8,0(%2)\n\
        mula.s $f13, $f13\n\
        madd.s %0, $f8, $f8\n\
        sqrt.s %0, %0"
                 : "=f"(result) : "m"(a), "m"(b) : "f20", "f8", "f13");
    return result;
}

inline void vec_sub_reverse(void* y, void* x, void* out) {
    asm("\
        lqc2 vf4, 0(%0)\n\
        lqc2 vf5, 0(%1)\n\
        vsub.xyzw vf4, vf4, vf5\n\
        sqc2 vf4, 0(%2)"
        : "+r"(x), "+r"(y), "+r"(out));
}

static inline void vec_sub_xyz(void* x, void* y, void* out) {
    asm("\
        lqc2 vf4, 0(%0)\n\
        lqc2 vf5, 0(%1)\n\
        vsub.xyz vf4, vf4, vf5\n\
        sqc2 vf4, 0(%2)"
        : "+r"(x), "+r"(y), "+r"(out));
}

static inline vec_lerp(float* out, float* v, float* w, float t) {
    asm("mfc1 t7, %3;\
         qmtc2 t7, vf6x;\
         vsubx.w vf6w, vf0, vf6x;\
         lqc2 vf4, 0(%1);\
         lqc2 vf5, 0(%2);\
         vmulax ACC, vf4, vf6;\
         vmaddw vf4, vf5, vf6;\
         sqc2 vf4, 0(%0)" : "=r"(out) : "r"(v), "r"(w), "f"(t) : "t7");
}

static inline float vec_length(float* a) {
    float result;
    asm volatile("lwc1   %0,0(%1);\
        lwc1   $f8,8(%1);\
        mula.s %0, %0;\
        madd.s %0, $f8, $f8;\
        sqrt.s %0, %0"
                 : "=f"(result) : "m"(a) : "f20", "f8", "f13");
    return result;
}

/* @todo deduplicate with sh3 version in subway overlay (vec3_dot_product) */
static inline float vec3_dot_product(void* v, void* w) {
    float d;

    asm("\
        lwc1 %0, 0(%1)\n\
        lwc1 f8, 0(%2)\n\
        lwc1 f9, 4(%1)\n\
        lwc1 f10, 4(%2)\n\
        mula.s %0, f8\n\
        lwc1 %0, 8(%1)\n\
        lwc1 f8, 8(%2)\n\
        madda.s f9, f10\n\
        madd.s %0, %0, f8"
        : "+f"(d) : "r"(v), "r"(w) : "f8", "f9", "f10");

    return d;
}

static inline float vec3_dist(sceVu0FVECTOR v, sceVu0FVECTOR w) {
    float d;
    asm("lwc1 %2, 0(%0)\n\
         lwc1 f8, 0(%1)\n\
         lwc1 f9, 4(%0)\n\
         sub.s %2, %2, f8;\
         lwc1 f10, 4(%1)\n\
         mula.s %2, %2;\
         lwc1 %2, 8(%0)\n\
         lwc1 f8, 8(%1)\n\
         sub.s f9, f9, f10\n\
         sub.s %2, %2, f8\n\
         madda.s f9, f9\n\
         madd.s %2, %2, %2;\
         sqrt.s %2, %2"
        : "+r"(v), "+r"(w), "=&f"(d)::"f8", "f9", "f10");
    return d;
}

static inline float vec3_dist_reverse(sceVu0FVECTOR v, sceVu0FVECTOR w) {
    float d;
    asm("lwc1 %2, 0(%0)\n\
         lwc1 f8, 0(%1)\n\
         lwc1 f9, 4(%0)\n\
         sub.s %2, %2, f8;\
         lwc1 f10, 4(%1)\n\
         mula.s %2, %2;\
         lwc1 %2, 8(%0)\n\
         lwc1 f8, 8(%1)\n\
         sub.s f9, f9, f10\n\
         sub.s %2, %2, f8\n\
         madda.s f9, f9\n\
         madd.s %2, %2, %2;\
         sqrt.s %2, %2"
        : "+r"(w), "+r"(v), "=&f"(d)::"f8", "f9", "f10");
    return d;
}

/* build 4x4 identity matrix using VU0 */
static inline void vu0_unit_matrix(sceVu0FMATRIX out) {
    asm("\
        vsub.xyzw vf5, vf0, vf0\n\
        vsub.xyzw vf6, vf0, vf0\n\
        vmr32.xyzw vf4, vf0\n\
        vaddw.y vf5, vf0, vf0\n\
        vaddw.x vf6, vf0, vf0\n\
        sqc2 vf0, 0x30(%0)\n\
        sqc2 vf4, 0x20(%0)\n\
        sqc2 vf5, 0x10(%0)\n\
        sqc2 vf6, 0(%0)"
        : "+r"(out));
}

static inline void vu0_transform_vector(sceVu0FVECTOR vec, sceVu0FMATRIX mat) {
    asm("\
        lqc2         vf4, 0x0(%0)\n\
        lqc2         vf5, 0x0(%1)\n\
        lqc2         vf6, 0x10(%1)\n\
        vmulax.xyzw  ACC, vf5, vf4x\n\
        lqc2         vf5, 0x20(%1)\n\
        vmadday.xyzw ACC, vf6, vf4y\n\
        lqc2         vf6, 0x30(%1)\n\
        vmaddaz.xyzw ACC, vf5, vf4z\n\
        vmaddw.xyzw  vf4, vf6, vf4w\n\
        sqc2         vf4, 0x0(%0)"
        : "+r"(vec): "r"(mat));
}

static inline void vu0_unit_vector(sceVu0FVECTOR out) {
    asm("\
        sqc2 vf0, 0x0(%0)"
        : "+r"(out));
}

/* sqrt function for when `pragma fastmath` is not available */
static inline float SQRT(float x) {
    float result = x;
    asm("sqrt.s  %0, %0"
        : "+f"(result));
    return result;
}

#endif // SILENT_VEC_H

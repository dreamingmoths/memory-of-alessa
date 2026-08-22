#include "sh2_common.h"
#include "sce/libvu0.h"

#include "vec.h"

#include "Chacter/character.h"

#include "Chacter_Draw/light_n.h"
#include "Chacter_Draw/sh_kt_vu0.h"
#include "Chacter_Draw/sh2gfw_model_light.h"

#include "GFW/sh2gfw_viewclip.h"
#include "GFW/sh2gfw_LightSet.h"
#include "GFW/sh2_DrawEnvData.h"
#include "GFW/sh2gfw_Init_ModelDrawData.h"

#include "Event/demoview.h"

#include "view/vb_main.h"

#define LIGHT_KIND_NONE       0
#define LIGHT_KIND_PARALLEL   1
#define LIGHT_KIND_POINT      2
#define LIGHT_KIND_3          3
#define LIGHT_KIND_REFLECTION 4
#define LIGHT_KIND_5          5
#define LIGHT_KIND_6          6

#define LIGHT_FAKE_KIND_POINT 1
#define LIGHT_FAKE_KIND_SPOT  2

#define EXTRA_MAX             6
#define LIGHT_MAX             12

static void UpdateIntensity(Light* l);
static void UpdateFParam(Light* l);
static void UpdateSParam(Light* l);
static void CalcInfluence(Light* l, float* center, float radius);
static int CompareByIntensity(void* xx, void* yy);
static int CompareByInfluence(void* xx, void* yy);
static void UpdateExtras(float* center, float radius);

/* migrated data */
static float monochrome_vector[4] = {0.3f, 0.6f, 0.1f, 0.0f};          // size: 0x10, address: 0x2A9540

/* unmigrated data, may not belong here */
extern sceVu0FVECTOR unit_fvector_z; /* = {0.0f, 0.0f, 1.0f, 0.0f}; */ // size: 0x10, address: 0x2A94D0
extern sceVu0FVECTOR unit_fvector_w;                                   // size: 0x10, address: 0x2A94E0
extern sceVu0FVECTOR unit_fvector_y;                                   // size: 0x10, address: 0x2A94C0
extern sceVu0FVECTOR zero_fvector;                                     // size: 0x10, address: 0x2A94B0
extern sceVu0FMATRIX zero_fmatrix;                                     // size: 0x40, address: 0x2A94F0

/* unmigrated bss */
extern LightWork light_work; // size: 0x9E0, address: 0x419380

float ktClampFloat(float x /* r29 */, float l /* r29 */, float h /* r29 */) {
    return (x < l) ? l : (x > h) ? h
                                 : x;
}

Light* LightPointer(int n /* r2 */) {
    ASSERT_ON_LINE((u_int)n < LIGHT_MAX, 58);
    return &light_work.lights[n];
}

static void UpdateIntensity(Light* l /* r16 */) {
    float* c;    // @note: unsure how this was used, possibly an inline. // r2
    float color; // @note: not in dwarf.
    color         = sceVu0InnerProduct(l->color, monochrome_vector);
    l->intensity2 = color, l->intensity = fabsf(color);
}

static void UpdateFParam(Light* l /* r2 */) {
    float a; // r1
    float b; // r29

    a      = 1.0f / (l->f_start - l->f_end);
    b      = -(a * l->f_end);
    l->f_a = a;
    l->f_b = b;

    l->f_rb = l->f_start / (l->f_start - l->f_end);
    l->f_ra = -l->f_rb * l->f_end;
}

static void UpdateSParam(Light* l /* r2 */) {
    float a; // r1
    float b; // r29

    a      = 1.0f / (l->s_start - l->s_end);
    b      = -(a * l->s_end);
    l->s_a = a;
    l->s_b = b;
}

void LightDelete(int n /* r2 */) {
    Light* l = LightPointer(n); // r2
    l->kind  = LIGHT_KIND_NONE;
}

void LightDeleteAll(void) {
    int i;
    for (i = 0; i < LIGHT_MAX; i++) {
        LightDelete(i);
    }
}

void LightSetParallel(int n /* r19 */, float* dir /* r18 */, float* color /* r17 */) {
    Light* l = LightPointer(n); // r16
    memset(l, 0, sizeof(Light));
    l->kind = LIGHT_KIND_PARALLEL;
    LightSetDir(n, dir);
    LightSetColor(n, color);
}

void LightSetPoint(int n /* r19 */, float* pos /* r18 */, float* color /* r17 */, float f_start /* r21 */, float f_end /* r20 */) {
    Light* l = LightPointer(n); // r16
    memset(l, 0, sizeof(Light));
    l->kind = LIGHT_KIND_POINT;
    LightSetPos(n, pos);
    LightSetDir(n, unit_fvector_z);
    LightSetColor(n, color);
    LightSetFalloff(n, f_start, f_end);
}

void LightSetFakePoint(int n /* r19 */, float* pos /* r18 */, float* color /* r17 */, float f_start /* r21 */, float f_end /* r20 */) {
    Light* l = LightPointer(n); // r16
    memset(l, 0, sizeof(Light));
    l->kind     = LIGHT_KIND_PARALLEL;
    l->fakekind = LIGHT_FAKE_KIND_POINT;
    LightSetPos(n, pos);
    LightSetDir(n, unit_fvector_z);
    LightSetColor(n, color);
    LightSetFalloff(n, f_start, f_end);
}

void LightSetFakeSpot(int n /* r19 */, float* pos /* r18 */, int unused /* @note not in dwarf */, float* color /* r17 */, float f_start /* r23 */, float f_end /* r22 */, float s_start /* r21 */, float s_end /* r20 */) {
    Light* l = LightPointer(n); // r16
    memset(l, 0, sizeof(Light));
    l->kind     = LIGHT_KIND_PARALLEL;
    l->fakekind = LIGHT_FAKE_KIND_SPOT;
    LightSetPos(n, pos);
    LightSetDir(n, unit_fvector_z);
    LightSetColor(n, color);
    LightSetFalloff(n, f_start, f_end);
    LightSetSpread(n, s_start, s_end);
}

void sh_Set_DrawEnvLightData(int n /* r2 */, void* ded /* r16 */) {
    Light* plight;
    plight                    = LightPointer(n); // r2
    plight->DrawEnv_LightData = ded;
}

void sh_Kari_LightSetSpot(int n /* r21 */, float* pos /* r20 */, float* dir /* r19 */, float* color /* r18 */, float* sv /* r17 */) {
    Light* l; // r16

    l = LightPointer(n);
    memset(l, 0, sizeof(Light));
    l->kind = 3;
    LightSetPos(n, pos);
    LightSetDir(n, dir);
    LightSetColor(n, color);

    l->f_start = sv[2];
    l->f_end   = sv[3];

    l->s_start = 1.0f;
    l->s_end   = sv[0];

    l->f_rb = sv[2] / (sv[2] - sv[3]);
    l->f_ra = (sv[3] * sv[2]) / (sv[3] - sv[2]);

    l->s_a = 1.0f;
    l->s_b = 0.8f * -sv[0];

    l->f_a = 1.0f / (sv[2] - sv[3]);
    l->f_b = -(l->f_a) * sv[3];
}

void LightSetReflection(int n /* r19 */, float* dir /* r18 */, float* color /* r17 */) {
    Light* l;
    l = LightPointer(n); // r16
    memset(l, 0, sizeof(Light));
    l->kind = LIGHT_KIND_REFLECTION;
    LightSetDir(n, dir);
    LightSetColor(n, color);
}

void LightSetPos(int n /* r2 */, float* pos /* r16 */) {
    Light* l = LightPointer(n); // r2
    sceVu0CopyVector(l->pos, pos);
}

void LightSetDir(int n /* r2 */, float* dir /* r16 */) {
    Light* l = LightPointer(n); // r2
    if ((dir[0] == 0.0f) && (dir[1] == 0.0f) && (dir[2] == 0.0f)) {
        sceVu0CopyVector(l->dir, unit_fvector_z);
    } else
        sceVu0Normalize(l->dir, dir);
}

void LightSetColor(int n /* r2 */, float* color /* r17 */) {
    Light* l = LightPointer(n); // r2
    sceVu0CopyVector(l->color, color);
    UpdateIntensity(l);
}

void LightSetFalloff(int n /* r2 */, float f_start /* r21 */, float f_end /* r20 */) {
    Light* l   = LightPointer(n); // r2
    l->f_start = f_start;
    l->f_end   = f_end;
    UpdateFParam(l);
}

void LightSetSpread(int n /* r2 */, float s_start /* r21 */, float s_end /* r20 */) {
    Light* l   = LightPointer(n); // r2
    l->s_start = s_start;
    l->s_end   = s_end;
    UpdateSParam(l);
}

static void CalcInfluence(Light* l /* r16 */, float* center /* r2 */, float radius /* r20 */) {
    switch (l->kind) {
        case LIGHT_KIND_NONE:
            l->influence  = 0.0f;
            l->influence2 = 0.0f;
            return;
        case LIGHT_KIND_PARALLEL:
            l->inf_fac = 0.2f * l->color[1];
        case LIGHT_KIND_REFLECTION: /* fallthrough */
            l->influence  = l->intensity;
            l->influence2 = l->intensity2;
            return;

        case LIGHT_KIND_POINT:
        case LIGHT_KIND_3: {
            sceVu0FVECTOR diff; // r29+0x30
            float dist;         // r29+0x40
            float f_inf;        // r20
            sceVu0SubVector(diff, center, l->pos);

            dist = sqrtf(sceVu0InnerProduct(diff, diff)) - radius;

            f_inf = ktClampFloat(l->f_b + l->f_a * dist, 0.0f, 1.0f);

            l->inf_fac = f_inf;

            if (!sh2gfw_Get_ChrClip_FLG() || !sh2gfw_Check_ClipOKChar(UniModelDW_Man.testSubChar)) {

                f_inf = 1.0f;
            }

            if (l->kind == 3) {
                float scale; // @note: not in dwarf
                vec_normalize(diff, diff);
                scale = vec3_dot_product(diff, l->dir);
                l->inf_fac *= float_clamp(l->s_a * scale + l->s_b, 0.0f, 1.0f);
            }

            l->influence  = l->intensity * f_inf;
            l->influence2 = l->intensity2 * f_inf;
            return;
        }
    }
}

static int CompareByIntensity(void* xx /* r2 */, void* yy /* r2 */) {
    Light** xp = xx;  // r2
    Light** yp = yy;  // r2
    Light* x   = *xp; // r2
    Light* y   = *yp; // r3

    return x->intensity < y->intensity ? 1 : x->intensity > y->intensity ? -1
                                                                         : 0;
}

static int CompareByInfluence(void* xx /* r2 */, void* yy /* r2 */) {
    Light** xp = xx;  // r2
    Light** yp = yy;  // r2
    Light* x   = *xp; // r2
    Light* y   = *yp; // r3

    return x->influence < y->influence ? 1 : x->influence > y->influence ? -1
                                                                         : 0;
}

void UpdateViewParams(void) {
    sceVu0FMATRIX wvm; // r29+0x30
    int i;             // r16
    sceVu0CopyMatrix(wvm, VbWvsMatrix.wvm);
    for (i = 0; i < LIGHT_MAX; i++) {
        Light* l = LightPointer(i); // r17

        switch (l->kind) {
            case LIGHT_KIND_PARALLEL:
            case LIGHT_KIND_POINT:
            case LIGHT_KIND_3:
            case LIGHT_KIND_REFLECTION:
            case LIGHT_KIND_5:
            case LIGHT_KIND_6:
                ktVu0ApplyMatrixXYZ1(l->vpos, wvm, l->pos);
                ktVu0ApplyMatrixXYZ0(l->vdir, wvm, l->dir);
                break;
        }
    }
}

void UpdateParallels(void) {
    Light* tmplight[12];   // r29+0x40
    int n_parallels = 0;   // r16
    int matrix_no, offset; // r5, r6
    int i;                 // r17
    Light *plp, *l;        // r2, r7

    light_work.n_valid_parallels         = 0;
    light_work.n_valid_parallel_matrices = 0;
    for (i = 0; i < 2; i++) {
        sceVu0CopyMatrix(light_work.nlms[i], zero_fmatrix);
        sceVu0CopyMatrix(light_work.vnlms[i], zero_fmatrix);
        sceVu0CopyMatrix(light_work.lcms[i], zero_fmatrix);
    }

    for (i = 0; i < LIGHT_MAX; i++) {
        plp = LightPointer(i);
        switch (plp->kind) {
            default:
                break;

            case LIGHT_KIND_PARALLEL:
                tmplight[n_parallels++] = plp;
        }
    }

    sh2gfw_Store_ShadowParallelLight(tmplight, n_parallels);

    matrix_no = 0;
    offset    = 0;
    for (i = 0; i < n_parallels; i++) {
        l = tmplight[i];
        switch (l->kind) {
            case LIGHT_KIND_PARALLEL: {
                if (matrix_no < 2) {
                    sceVu0FVECTOR* nlm  = light_work.nlms[matrix_no];  // r3
                    sceVu0FVECTOR* vnlm = light_work.vnlms[matrix_no]; // r4
                    sceVu0FVECTOR* lcm  = light_work.lcms[matrix_no];  // r8
                    nlm[0][offset]      = l->dir[0];
                    nlm[1][offset]      = l->dir[1];
                    nlm[2][offset]      = l->dir[2];
                    vnlm[0][offset]     = l->vdir[0];
                    vnlm[1][offset]     = l->vdir[1];
                    vnlm[2][offset]     = l->vdir[2];

                    lcm[offset][0] = l->color[0];
                    lcm[offset][1] = l->color[1];
                    lcm[offset][2] = l->color[2];

                    lcm[offset][3] = l->color[3];

                    offset++;
                    if (((offset == 3) && (matrix_no == 0)) || (offset == 4)) {
                        matrix_no++;
                        offset = 0;
                    }
                    light_work.n_valid_parallels++;
                }
            }
        }
    }

    light_work.n_valid_parallel_matrices = (light_work.n_valid_parallels + 4) / 4;
}


void UpdateReflections(void) {
    Light* a[12];          // r29+0x80
    int n_reflections = 0; // r16
    sceVu0FMATRIX wvm;     // r29+0xB0
    sceVu0FMATRIX vwm;     // r29+0xF0
    int i;                 // r17
    Light* l;              // r2
    static float nhm3[4] = {0.5f, 0.5f, 0.0f, 1.0f}; // @ 0x002A9550
    light_work.reflection_brightness = 0.0f;
    sceVu0CopyVector(light_work.reflection_color, zero_fvector);
    sceVu0CopyMatrix(light_work.nhm, zero_fmatrix);

    for (i = 0; i < LIGHT_MAX; i++) {
        l = LightPointer(i);
        switch (l->kind) {
            case LIGHT_KIND_REFLECTION:
                a[n_reflections++] = l;
        }
    }
    if (n_reflections != 0) {
        Light* l;                               // r2
        float* dir_z;                           // r2
        sceVu0FVECTOR hv, vhv;                  // r29+0x130, r29+0x140
        sceVu0FVECTOR *nlm, *vnlm, *nhm, *vnhm; // r3, r2, r16, r17
        float* dir_y;                           // r2
        sceVu0CopyMatrix(wvm, VbWvsMatrix.wvm);

        sceVu0TransposeMatrix(vwm, wvm);
        vwm[1][3] = vwm[2][3] = 0.0f;

        qsort(a, n_reflections, 4, CompareByIntensity);

        l     = a[0];
        dir_z = vwm[2];

        sceVu0AddVector(hv, l->dir, dir_z);
        sceVu0Normalize(hv, hv);
        sceVu0AddVector(vhv, l->vdir, unit_fvector_z);
        sceVu0Normalize(vhv, vhv);

        nlm                              = light_work.nlms[0];
        vnlm                             = light_work.vnlms[0];
        nlm[0][3]                        = hv[0];
        nlm[1][3]                        = hv[1];
        nlm[2][3]                        = hv[2];
        vnlm[0][3]                       = vhv[0];
        vnlm[1][3]                       = vhv[1];
        vnlm[2][3]                       = vhv[2];
        light_work.reflection_brightness = sceVu0InnerProduct(l->color, monochrome_vector);

        nhm   = light_work.nhm;
        vnhm  = light_work.vnhm;
        dir_y = vwm[1];

        if ((hv[0] == 0.0f) && (hv[1] == 0.0f) && (hv[2] == 0.0f)) {
            hv[0] = 1.0f;
        }
        sceVu0OuterProduct(nhm[0], dir_y, hv);
        sceVu0OuterProduct(nhm[1], hv, nhm[0]);
        sceVu0Normalize(nhm[0], nhm[0]);
        sceVu0Normalize(nhm[1], nhm[1]);
        sceVu0CopyVector(nhm[2], hv);
        sceVu0CopyVector(nhm[3], unit_fvector_w);
        sceVu0TransposeMatrix(nhm[0], nhm[0]);
        sceVu0CopyVector(nhm[3], nhm3);

        if ((vhv[0] == 0.0f) && (vhv[1] == 0.0f) && (vhv[2] == 0.0f)) {
            vhv[0] = 1.0f;
        }
        sceVu0OuterProduct(vnhm[0], unit_fvector_y, vhv);
        sceVu0OuterProduct(vnhm[1], vhv, vnhm[0]);
        sceVu0Normalize(vnhm[0], vnhm[0]);
        sceVu0Normalize(vnhm[1], vnhm[1]);
        sceVu0CopyVector(vnhm[2], vhv);
        sceVu0CopyVector(vnhm[3], unit_fvector_w);
        sceVu0TransposeMatrix(vnhm[0], vnhm[0]);
        sceVu0CopyVector(vnhm[3], nhm3);

        sceVu0CopyVector(light_work.reflection_color, l->color);
    }
}

static void UpdateExtras(float* center /* r19 */, float radius /* r20 */) {
    Light* a[12];     // r29+0x60
    int n_extras = 0; // r16
    int i;            // r17

    light_work.n_valid_extras = 0;

    for (i = 0; i < LIGHT_MAX; i++) {
        Light* l = LightPointer(i);
        switch (l->kind) {
            case LIGHT_KIND_POINT:
            case LIGHT_KIND_3:
                CalcInfluence(l, center, radius);
                if (l->influence > 0.0f) {

                    a[n_extras++] = l;
                }
        }
    }
    if (n_extras == 0) {

        if (sh2gfw_Get_NightOrDay())

            if (DramaDemoNumber() == 0) {
                sceVu0FVECTOR ref_color = {1.0f, 1.0f, 1.0f, 1.0f};
                sceVu0ScaleVector(light_work.reflection_color, &ref_color[0], 0.2f);
            }

        return;
    }

    qsort(a, n_extras, 4, CompareByInfluence);
    light_work.n_valid_extras = n_extras < 6 ? n_extras : 6;

    for (i = 0; i < light_work.n_valid_extras; i++) {
        Light* l                   = a[i];
        light_work.valid_extras[i] = l;
    }

    if (Check_IgnoreJmsSpot_for_Shadow() == 0) {

        sh2gfw_Store_ShadowLight(light_work.valid_extras[0]);
    } else {

        for (i = 0; i < light_work.n_valid_extras; i++) {
            if (light_work.valid_extras[i]->DrawEnv_LightData != NULL)
                break;
        }

        if (i < light_work.n_valid_extras) {
            sh2gfw_Store_ShadowLight(light_work.valid_extras[i]);
        }
    }

    if (sh2gfw_Check_DemoRefrectionHightLight())

        if (!DramaDemoNumber()) {
            sceVu0FVECTOR ref_color = {1.0f, 1.0f, 1.0f, 1.0f};
            sceVu0ScaleVector(light_work.reflection_color, ref_color, 1.0f);
        }
}


void LightUpdateInfoByScene(void) {
    UpdateViewParams();
    UpdateParallels();
    UpdateReflections();
}

void LightUpdateInfoByPos(float* center /* r2 */, float radius /* r29+0x10 */) {
    UpdateExtras(center, radius);
}

int LightNValidParallelMatrices(void) {
    return (light_work.n_valid_parallels + 3) / 4;
}

static const char N_LESS_THAN_2_STR[] = "n < 2";
// @hack: rodata is out of order. @todo(keep_section): fix when dead code elimination for sh2 is restored.
#define ASSERT_N_LESS_THAN_2_ON_LINE(line) \
do { \
    if (!(n < 2)) { \
        printf(__FILE__ ":" #line "> assert:(%s)\n", N_LESS_THAN_2_STR); \
        do {} while (1); \
    } \
} while (0)

void LightGetNthViewNLM(sceVu0FVECTOR* nlm /* r2 */, int n /* r2 */) {
    ASSERT_N_LESS_THAN_2_ON_LINE(1013); // @todo(assert): maybe missing macro here.
    sceVu0CopyMatrix(nlm, light_work.vnlms[n]);
}

void LightGetNthLCM(sceVu0FVECTOR* lcm /* r2 */, int n /* r2 */) {
    ASSERT_N_LESS_THAN_2_ON_LINE(1023); // @todo(assert): maybe missing macro here.
    sceVu0CopyMatrix(lcm, light_work.lcms[n]);
}

float LightReflectionBrightness(void) {
    return light_work.reflection_brightness;
}

void LightGetReflectionColor(float* color /* r2 */) {
    sceVu0CopyVector(color, light_work.reflection_color);
}

float* LightReflectionColor(void) {
    return light_work.reflection_color;
}

void LightGetNthViewNHM(sceVu0FVECTOR* nhm /* r2 */, int unused /* @note: not in dwarf */) {
    sceVu0CopyMatrix(nhm, light_work.vnhm);
}

int LightNValidExtras(void) {
    return light_work.n_valid_extras;
}

Light* LightNthValidExtra(int n /* r2 */) {
    ASSERT_ON_LINE((u_int)n < EXTRA_MAX, 1083);

    if (n < light_work.n_valid_extras) {
        return light_work.valid_extras[n];
    }
    return NULL;
}

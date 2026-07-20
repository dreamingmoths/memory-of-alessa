#include "sh2_common.h"
#include "SH2_common/sh_vu0.h"

#include "vec.h"

#include "Event/demoview.h"

#include "Effect/ef_sparks.h"
#include "Effect/ef_smoke.h"
#include "Effect/ef_common.h"
#include "Effect/ef_flame.h"

#include "Effect2/hh_class_wrapper.h"

#include "view/vb_main.h"

static void ClipFlameEffectObject(EFCTVertexData* pVertex);
static void EFCTTinyThreeDWorkFlame(u_int plane_num, EFCTObject* pObj);
static void TinyFlameZSort(/* void */);
static void SetFlameSTValue(EFCTObject* pObj, EFCTFlameObject* flame);
static void CalibrationZVal(int num, EFCTVertexData* pVertex);
static int GetBehindAngelaFlameIndex(u_int index);
static void RenewFlameSize(EFCTObject* pObj, EFCTFlameObject* flame);
static void NextFrame(EFCTObject* pObj, float* wait_time, short* current, float* drawing_time);
static void CountFlameCycleTimer(EFCTFlameObject* flame);
static EFCTFlameObject* GetFlameObject(EFCTObject* pObj);
static int IsFlameValid(EFCTObject* pObj, EFCTFlameObject* flame);
static void TinyFlameZSort2(u_int index, float* new_pos);
static void SetFlameCycleData(u_char kind, EFCTFlamePlane* plane);
static void SetFlameStartPos(u_char kind, float width, float height /* @note not in dwarf */, float* start_pos);
static void SetFlameVertex(u_char kind, float width, float height, float* trans, float* start_pos, float cycle, float w_right_ratio, EFCTVertexData* VertexData);
static void FlameLocalRot(EFCTVertexData* pVertex, float* rot);
static void SetFlameTexKind(u_char kind, EFCTFlamePlane* plane);
static void SetFlameTransParam(u_char kind, float width, float height, float* trans);
static void SetFlameRotParam(u_char kind, float* rot);
static void EnlargeFlameSize(float time, float w_speed, float h_speed, float w_enlarge_time, float h_enlarge_time, float* width, float* height);
static void RenewFlameRGBA(float cycle, int alpha, EFCTVertexData* pVertex);
static int GetBehindAngelaFlameSortIndex(u_int index);
static float GetBehindAngelaFlameLifeTimer(u_int index);

/* @todo: migrate data */
extern /* static */ u_short camera_cut;                      // size: 0x2, address: 0x11D2240
extern /* static */ u_short behind_angela_flame_num;         // size: 0x2, address: 0x11D2248
extern /* static */ u_short behind_angela_flame_start_index; // size: 0x2, address: 0x11D2250
extern float behind_angela_flame_pos_buf[12][4];             // size: 0xC0, address: 0x11D22A0
extern /* struct */ EFCTFlameObject flame_obj[36];           // size: 0x14D00, address: 0x11D2360
extern float behind_angela_flame_life_time_buf[12];          // size: 0x30, address: 0x11D2270

static void SetFlameCycleData(u_char kind /* r2 */, EFCTFlamePlane* plane /* r16 */) {
    float rate;                                 // r29+0x40
    float width, height;                        // r23, r20
    float cycle_max, cycle_min;                 // r29+0x40,  r29+0x40
    float w_cycle_param_max, w_cycle_param_min; // r24, r25
    float h_cycle_param_max, h_cycle_param_min; // r21, r22

    if (kind == 0 || kind == 1) {

        width     = 160.0f;
        height    = 200.0f;
        cycle_max = 1.25f;
        cycle_min = 0.85f;

        w_cycle_param_max = 4.25f;
        w_cycle_param_min = 2.4f;
        h_cycle_param_max = 3.85f;
        h_cycle_param_min = 1.85f;

        plane->w_right_ratio = 0.5f;

    } else {
        if (kind == 3) {

            width             = 150.0f;
            height            = 50.0f;
            cycle_max         = 2.35f;
            cycle_min         = 0.75f;
            w_cycle_param_max = 7.25f;
            w_cycle_param_min = 0.7f;
            h_cycle_param_max = 15.05f;
            h_cycle_param_min = 0.75f;

            plane->w_right_ratio = 0.5f;
        } else {

            width             = 130.0f;
            height            = 100.0f;
            cycle_max         = 2.35f;
            cycle_min         = 0.75f;
            w_cycle_param_max = 3.25f;
            w_cycle_param_min = 0.7f;
            h_cycle_param_max = 4.05f;
            h_cycle_param_min = 0.75f;

            plane->w_right_ratio = 0.5f;
        }
    }

    rate         = cycle_max - cycle_min;
    plane->cycle = rate * shRandF() + cycle_min;

    plane->width_cycle_param  = width * (w_cycle_param_min + ((w_cycle_param_max - w_cycle_param_min) * shRandF()));
    plane->height_cycle_param = height * (h_cycle_param_min + ((h_cycle_param_max - h_cycle_param_min) * shRandF()));
}

static void SetFlameStartPos(u_char kind /* r2 */, float width /* r20 */, float height, float* start_pos /* r16 */) {

    if ((kind == 0) || (kind == 1)) {
        if (camera_cut == 5) {
            *start_pos = shSway1f(10.0f * -width, 10.0f * width);
            return;
        } else if (camera_cut == 0) {
            *start_pos = 20.0f * (width * -shRandF());
            return;
        } else if (camera_cut == 3) {
            *start_pos = shSway1f(10.0f * -width, 10.0f * width);

            return;
        }
    } else {
        *start_pos = shSway1f(0.2f * -width, 0.2f * width);
    }
}

static void SetFlameVertex(u_char kind /* r2 */, float width /* r23 */, float height /* r22 */, float* trans /* r18 */, float* start_pos /* r17 */, float cycle /* r21 */, float w_right_ratio /* r20 */, EFCTVertexData* VertexData /* r16 */) {
    float adjustment[4][4]; // r29+0x60
    float ratio;            // r29+0xA0
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 s_index;
    f32 s_index_2;
    f32 t_index;
    f32 temp_f3;
    s32 temp_s3;
    s32 temp_s3_2;
    s32 temp_s3_3;
    s32 temp_s3_4;
    s32 temp_s3_5;
    s32 temp_s3_6;

    vec_zero(adjustment[0]);
    vec_zero(adjustment[1]);
    vec_zero(adjustment[2]);
    vec_zero(adjustment[3]);

    if ((kind == 0) || (kind == 1)) {
        if (camera_cut == 5) {
            adjustment[2][0] = 0.15f * width;
            adjustment[3][0] = 0.15f * -width;
        } else if (camera_cut == 1 || camera_cut == 2 || camera_cut == 4) {

            if (!(kind & 0xFF)) {
                width *= 0.8f;
            }
            temp_f0          = shSinF(PI * cycle);
            adjustment[0][0] = 0.4f * -width * temp_f0;
            adjustment[0][1] = 0.5f * -height * temp_f0;
            temp_f0_2        = shSinF(PI * (0.5f + cycle));
            adjustment[2][0] = 0.25f * -width * temp_f0_2;
            adjustment[3][0] = 0.35f * -width * temp_f0_2;
        } else if (camera_cut == 3) {
            height *= 0.5f;
            width *= 0.5f;

        } else {

            width *= 0.55f;
            adjustment[0][0] = 0.4f * -width;
            adjustment[1][0] = 0.4f * width;
        }
    } else {

        adjustment[0][0] = (trans[0] * cycle) - trans[0];
        adjustment[1][0] = (trans[0] * cycle) - trans[0];
        adjustment[2][0] = -trans[0];
        adjustment[3][0] = -trans[0];
    }

    VertexData->LocalPos[0] = adjustment[0][0] + (start_pos[0] + (trans[0] + (-width * (1.0f - w_right_ratio))));
    VertexData->LocalPos[1] = adjustment[0][1] + (start_pos[1] + (-height + trans[1]));
    VertexData->LocalPos[2] = adjustment[0][2] + (trans[2] + start_pos[2]);
    VertexData->LocalPos[3] = 1.0f;

    VertexData[1].LocalPos[0] = (adjustment[1][0] + (start_pos[0] + (trans[0] + (width * w_right_ratio))));
    VertexData[1].LocalPos[1] = (adjustment[1][1] + (start_pos[1] + (-height + trans[1])));
    VertexData[1].LocalPos[2] = (adjustment[1][2] + (trans[2] + start_pos[2]));
    VertexData[1].LocalPos[3] = 1.0f;

    VertexData[2].LocalPos[0] = (adjustment[2][0] + (start_pos[0] + (trans[0] + (-width * (1.0f - w_right_ratio)))));
    VertexData[2].LocalPos[1] = adjustment[2][1] + (height * 0.15 + trans[1] + start_pos[1]);
    VertexData[2].LocalPos[2] = (adjustment[2][2] + (trans[2] + start_pos[2]));
    VertexData[2].LocalPos[3] = 1.0f;

    VertexData[3].LocalPos[0] = (adjustment[3][0] + (start_pos[0] + (trans[0] + (width * w_right_ratio))));
    VertexData[3].LocalPos[1] = adjustment[3][1] + (height * 0.15 + trans[1] + start_pos[1]);
    VertexData[3].LocalPos[2] = (adjustment[3][2] + (trans[2] + start_pos[2]));
    VertexData[3].LocalPos[3] = 1.0f;
}

static void FlameLocalRot(EFCTVertexData* pVertex /* r16 */, float* rot /* r17 */) {
    sceVu0FMATRIX mtx; // r29+0x30
    int i;             // r4

    vu0_unit_matrix(mtx);
    shRotMatrixZ(mtx, mtx, rot[2]);
    shRotMatrixY(mtx, mtx, rot[1]);
    shRotMatrixX(mtx, mtx, rot[0]); // @todo: likely inline.

    for (i = 0; i < 4; i++) {
        vu0_transform_vector(pVertex[i].LocalPos, mtx);
    }
}

static void SetFlameTexKind(u_char kind /* r2 */, EFCTFlamePlane* plane /* r16 */) {
    int i; // r4

    if ((kind == 0) || (kind == 1)) {
        do {
            i = shRandI() % 5;
        } while (i == 1);

        plane->s_index = i + 2;
        return;
    }

    plane->s_index = (shRandI() % 4) + 4;
}

static void SetFlameTransParam(u_char kind /* r2 */, float width /* r21 */, float height /* r20 */, float* trans /* r16 */) {

    if ((kind == 0) || (kind == 1)) {

        if (camera_cut == 5) {
            trans[0] = shSway1f(15.5f * -width, 15.5f * width);
        } else if (camera_cut == 0) {
            trans[0] = 30.5f * (-width * shRandF());
        } else if (camera_cut == 4) {
            trans[0] = 30.5f * (-width * shRandF());

        } else if (camera_cut == 3) {
            trans[0] = shSway1f(15.5f * -width, 15.5f * width);
        }
        trans[1] = (-(100.5f * height) * shRandF());
        trans[2] = shSway1f(-25.0f, 25.0f);
        return;
    }

    trans[0] = shSway1f(0.4f * -width, 0.4f * width);
}

static void SetFlameRotParam(u_char kind /* r2 */, float* rot /* r2 */) {
    vec_zero(rot);

    if (camera_cut == 4) {
        if (kind == 0) {
            rot[0] = 0.2617994f;

            rot[1] = -0.2617994f;
        } else if (kind == 1) {
            rot[0] = 0.5235988f;
            rot[1] = -0.5235988f;
        }
    } else if (camera_cut == 1 || camera_cut == 2) {
        rot[1] = 0.2617994f;
    } else if (camera_cut == 3 && kind == 1) {
        rot[0] = 1.0471976f;
        rot[1] = -0.5235988f;
    }

    if (kind == 1) {
        rot[1] += PI;
    }
}

static const char ZERO_STR[] = "0";
// @hack: rodata is out of order? 0x00398550 has the string "0", and the file/line strings follow it.
// it's usually the opposite order?
// i'm guessing it's something with ASSERT(0) / the fact that their ASSERT seems to expand macros...
#define ASSERT_ZERO_ON_LINE(line) \
do { \
    if (!(0)) { \
        printf(__FILE__ ":" #line "> assert:(%s)\n", ZERO_STR); \
        do {} while (1); \
    } \
} while (0)

void DrawFlame(void* task /* r2 */) {
    EFCTTask* pTask;        // r16
    EFCTFlameObject* flame; // r17
    int i;                  // r18

    pTask = task;
    if (pTask == NULL) {
        ASSERT_ZERO_ON_LINE(705);
    }

    flame = GetFlameObject(pTask->pObj);
    if (flame == NULL) {
        ASSERT_ZERO_ON_LINE(712);
    }

    if (flame->index == 0)

        if (demo_status & 1)

            EFCTFlameChangeCamera();

    if (IsFlameValid(pTask->pObj, flame) == 0) {

        SetFlameSmokeValid(flame->index, 0);
        return;
    }

    SetFlameSmokeValid(flame->index, 1);

    for (i = 0; i < flame->plane_num; i++) {

        NextFrame(pTask->pObj,
                  &flame->plane[i].draw_wait,
                  &flame->plane[i].current_frame,
                  &flame->plane[i].drawing_time);
    }

    CountFlameCycleTimer(flame);

    if (flame->kind == 3)
        if (camera_cut == 6) {

            flame->life_timer += EFCTGetPassingTimePerFrame();

            behind_angela_flame_life_time_buf[GetBehindAngelaFlameIndex(flame->index)] = flame->life_timer;
        }

    RenewFlameSize(pTask->pObj, flame);

    if (flame->kind == 3) {

        TinyFlameZSort2(flame->index, pTask->pObj->Pos);
    }

    if (((camera_cut == 4) && (flame->kind == 0)) || (flame->kind == 3) || (flame->kind == 2)) {

        EFCTThreeDWork(pTask->pObj);
        for (i = 0; i < flame->plane_num; i++) {

            ClipFlameEffectObject(&pTask->pObj->pVertex[i * 4]);
        }
    } else {

        EFCTTinyThreeDWorkFlame(flame->plane_num, pTask->pObj);
    }

    if ((flame->kind == 0) || (flame->kind == 1)) {

        CalibrationZVal(pTask->pObj->VertexNum, pTask->pObj->pVertex);
    }

    if (flame->kind == 3) {

        TinyFlameZSort(flame->index, pTask->pObj->VertexNum, pTask->pObj->pVertex);
    }

    SetFlameSTValue(pTask->pObj, flame);

    DrawPrimitive(pTask->pObj);

    DrawSparks(&flame->sparks);
}

static EFCTFlameObject* GetFlameObject(EFCTObject* pObj /* r2 */) {
    int i; // r6

    for (i = 0; i < 0x24; i++) {
        if (flame_obj[i].use == 1 && flame_obj[i].base_obj == pObj) {
            return &flame_obj[i];
        }
    }

    return NULL;
}

static void RenewFlameSize(EFCTObject* pObj /* r18 */, EFCTFlameObject* flame /* r17 */) {
    int i;                        // r16
    float life_timer;             // r29+0x70
    float delta_width;            // r1
    float delta_height;           // r2
    float cycle;                  // r20
    float ratio, ratio2;          // r21, r29+0x70
    float width, height;          // r29+0x68, r29+0x6C
    sceVu0FVECTOR trans = {0.0f}; // r29+0x50
    u8 temp_v1;
    u8 temp_v1_2;
    for (i = 0; i < flame->plane_num; i++) {

        cycle = flame->plane[i].timer / flame->plane[i].cycle;
        ratio = shSinF(PI * cycle);

        width  = pObj->width;
        height = pObj->height;

        if (flame->kind == 3) {

            life_timer = GetBehindAngelaFlameLifeTimer(flame->index);
        } else {

            life_timer = flame->life_timer;
        }

        EnlargeFlameSize(life_timer,
                         flame->plane[i].w_enlarge_speed,
                         flame->plane[i].h_enlarge_speed,
                         flame->plane[i].w_enlarge_time,
                         flame->plane[i].h_enlarge_time,
                         &width,
                         &height);
        if ((flame->plane[i].timer == 0.0f)) {

            SetFlameCycleData(flame->kind, &flame->plane[i]);

            SetFlameStartPos(flame->kind, width, height, flame->plane[i].start_pos);

            SetFlameTransParam(flame->kind, width, height, flame->plane[i].trans);

            SetFlameTexKind(flame->kind, &flame->plane[i]);

            if ((flame->kind == 0) || (flame->kind == 1)) {

                SetFlameRotParam(flame->kind, flame->plane[i].rot);
            }
        }

        if ((flame->kind == 0) || (flame->kind == 1)) {

            trans[0] = flame->plane[i].trans[0] * ratio;
            trans[1] = flame->plane[i].trans[1] * ratio;
            trans[2] = flame->plane[i].trans[2] * ratio;
        } else {

            trans[0] = flame->plane[i].trans[0] * ratio;
            trans[1] = flame->plane[i].trans[1] * ratio;
            ratio2   = shSinF(PI * ((4.0f * flame->plane[i].timer) / flame->plane[i].cycle));
            trans[2] = flame->plane[i].trans[2] * float_abs(ratio2);
        }

        delta_width  = flame->plane[i].width_cycle_param * ratio;
        delta_height = flame->plane[i].height_cycle_param * ratio;

        width += delta_width;
        height += delta_height;

        SetFlameVertex(flame->kind, width, height, &trans[0], flame->plane[i].start_pos, cycle, flame->plane[i].w_right_ratio, &pObj->pVertex[4 * i]);

        FlameLocalRot(&pObj->pVertex[4 * i], flame->plane[i].rot);

        if (flame->kind == 3) {
            RenewFlameRGBA(cycle, 0x80, &pObj->pVertex[4 * i]);
        } else {

            RenewFlameRGBA(cycle, 0x64, &pObj->pVertex[4 * i]);
        }
    }
}

static void EnlargeFlameSize(float time /* r29 */, float w_speed /* r29 */, float h_speed /* r29 */, float w_enlarge_time /* r29 */, float h_enlarge_time /* r29 */, float* width /* r2 */, float* height /* r2 */) {
    if (time <= w_enlarge_time) {

        *width *= 1.0f + ((w_speed - 1.0f) * time);
    } else {

        *width *= 1.0f + ((w_speed - 1.0f) * w_enlarge_time);
    }

    if (time <= h_enlarge_time) {

        *height *= 1.0f + ((h_speed - 1.0f) * time);
        return;
    }

    *height *= 1.0f + ((h_speed - 1.0f) * h_enlarge_time);
}

static void RenewFlameRGBA(float cycle /* r21 */, int alpha /* r17 */, EFCTVertexData* pVertex /* r16 */) {
    float ratio;        // r20
    sceVu0IVECTOR rgba; // r29+0x40

    ratio   = shSinF(QUARTER_TURN);
    rgba[0] = (u_short) (128.0f * ratio);
    rgba[1] = (u_short) (108.0f * ratio);
    rgba[2] = (u_short) (108.0f * ratio);
    ratio   = shSinF(PI * (2.0f * cycle));
    rgba[3] = (u_short) (alpha * ratio);
    EFCTResetRGBA(rgba, pVertex);
}

INCLUDE_ASM("asm/nonmatchings/Effect/ef_flame", EFCTTinyThreeDWorkFlame);

static void SetFlameSTValue(EFCTObject* pObj /* r2 */, EFCTFlameObject* flame /* r2 */) {
    int i;         // r3
    float s_index; // r1
    float t_index; // r2
    f32 temp_f0;
    f32 temp_f4;
    f32 temp_f5;
    s32 temp_t0;

    for (i = 0; i < flame->plane_num; i++) {

        s_index = flame->plane[i].s_index;
        t_index = (f32) flame->plane[i].current_frame;

        pObj->pVertex[4 * i + 0].stq[0] = 0.125f * s_index;
        pObj->pVertex[4 * i + 0].stq[1] = 0.125f * t_index;
        pObj->pVertex[4 * i + 1].stq[0] = 0.125f * (1.0f + s_index);
        pObj->pVertex[4 * i + 1].stq[1] = 0.125f * t_index;
        pObj->pVertex[4 * i + 2].stq[0] = 0.125f * s_index;
        pObj->pVertex[4 * i + 2].stq[1] = 0.125f * (1.0f + t_index);
        pObj->pVertex[4 * i + 3].stq[0] = 0.125f * (1.0f + s_index);
        pObj->pVertex[4 * i + 3].stq[1] = 0.125f * (1.0f + t_index);
    }
}

void InitFlameTexEnv(EFCTTexEnvInfo* pTexInfo /* r2 */) {
    pTexInfo->tfx = 0;

    pTexInfo->transparency = 2;
    pTexInfo->clut_id      = 0;
}

u_short GetFlameEffectLayerNum(void) {
    return 1;
}

static void NextFrame(EFCTObject* pObj /* r2 */, float* wait_time /* r2 */, short* current /* r16 */, float* drawing_time /* r17 */) {
    EFCTAnimationData* pAnim = pObj->pAnimData; // r6

    if (*drawing_time < *wait_time) {

        *drawing_time += EFCTGetPassingTimePerFrame();
    } else {

        *drawing_time = 0.0f;

        if (*current == pAnim->FinishFrameNo) {

            *current = pAnim->StartFrameNo;
        } else

            if (*current < (pAnim->TotalFrame - 1)) {
            *current = *current + 1;
        } else {

            *current = 0;
        }
    }

    if (7 < *current) {
        ASSERT_ZERO_ON_LINE(1198);
    }
}

static void CountFlameCycleTimer(EFCTFlameObject* flame /* r17 */) {
    int i; // r16

    if (flame != NULL) {
        for (i = 0; i < flame->plane_num; i++) {
            flame->plane[i].timer += EFCTGetPassingTimePerFrame();

            if (flame->plane[i].timer / flame->plane[i].cycle > 0.5f) {
                flame->plane[i].timer = 0.0f;
            }
        }
    }
}

static void ClipFlameEffectObject(EFCTVertexData* pVertex /* r18 */) {
    int i;         // r16
    int valid = 0; // r17

    for (i = 0; i < 4; i++) {

        if (EFCTClipVertex(pVertex[i].ScreenPos) == 0) {

            valid = 1;

            break;
        }
    }

    for (i = 0; i < 4; i++) {
        pVertex[i].is_valid = valid;
    }
}

static void CalibrationZVal(int num /* r2 */, EFCTVertexData* pVertex /* r2 */) {
    int z; // r2

    if (camera_cut == 4) {
        z = 0x1388;
    } else if (camera_cut == 1) {
        z = 0xBB8;
    } else if (camera_cut == 6) {
        z = 0xFA;
    } else {

        z = 0x7D0;
    }

    CalibrationZValue(num, z, pVertex);
}

static void TinyFlameZSort(/* void */) {
    /* empty */
}

static int GetBehindAngelaFlameIndex(u_int index /* r2 */) {
    ASSERT_ON_LINE(index >= behind_angela_flame_start_index, 1340);

    return index - behind_angela_flame_start_index;
}

static int GetBehindAngelaFlameSortIndex(u_int index /* r2 */) {
    ASSERT_ON_LINE(index >= behind_angela_flame_start_index, 1349);

    return (behind_angela_flame_num - GetBehindAngelaFlameIndex(index)) - 1;
}

static void TinyFlameZSort2(u_int index /* r2 */, float* new_pos /* r16 */) {
    int new_index;

    new_index = GetBehindAngelaFlameSortIndex(index);

    ASSERT_ON_LINE(new_index >= 0, 1365);

    volatile_vec_copy(new_pos, behind_angela_flame_pos_buf[new_index]);
}

static float GetBehindAngelaFlameLifeTimer(u_int index /* r2 */) {
    int new_index; // r2

    new_index = GetBehindAngelaFlameSortIndex(index);

    ASSERT_ON_LINE(new_index >= 0, 1378);

    return behind_angela_flame_life_time_buf[new_index];
}

void EFCTFlameChangeCamera(void) {
    camera_cut++;
}

static int IsFlameValid(EFCTObject* pObj /* r2 */, EFCTFlameObject* flame /* r2 */) {
    if (camera_cut == 4) {
        if (pObj->Pos[2] <= -76500.0f) {
            return 0;
        }
    } else {
        if (camera_cut == 6) { /* switch 1 */
            if (pObj->Pos[2] <= -78000.0f) {
                return 0;
            }

        } else if (camera_cut == 3) { /* switch 1 */
            if (pObj->Pos[2] > -77000.0f) {
                return 0;
            }
        }
    }

    if (flame->kind == 1) {
        switch (camera_cut) { /* switch 2 */
            case 1:           /* switch 2 */
            case 2:           /* switch 2 */
            case 5:           /* switch 2 */

                return 0;

            case 0: /* switch 2 */
                if (pObj->Pos[2] > -77500.0f) {
                    return 0;
                }

            case 7: /* switch 2 */
                if (pObj->Pos[2] > -77000.0f) {
                    return 0;
                }
            case 6: /* switch 2 */
                if (pObj->Pos[2] > -77500.0f) {
                    return 0;
                }
        }
    }

    return 1;
}

#undef ASSERT_ZERO_ON_LINE

#include "Effect2/hh_class_wrapper.h"

#define PRIMITIVE_X_RANGE 1024.0f
#define PRIMITIVE_Y_RANGE 1024.0f
#define BOUNDING_BOX_X_RANGE 1500.0f
#define BOUNDING_BOX_Y_RANGE 1500.0f
#define BOUNDING_BOX_Z_FAR 200.0f

static void ViewFrustum_Primitive_ClipMatrix_Create(void);
static void ViewFrustum_BoundingBox_ClipMatrix_Create(void);
static void AlwaysFront_WorldView_Matrix_Create(void);

extern float func_001B4100(void);
extern float func_001B4230(void);
extern float func_001B4250(void);
extern float func_001B4170(void);
extern float func_001B41C0(void);

// @note was a pointer in sh2 trial
extern /* static */ HH_Class_Wrapper_Work _pWork;

void ViewFrustum_Primitive_ClipMatrix_Create(void) {    
    if (func_0019B580(5) && func_002D7B30() == 0x41) {
        float clip_mat[4][4];
        float wvm[4][4];
        float vsm[4][4];
        float z_near, z_far;
        float scale;

        z_near = HH_ClassWrapper_ViewingFrustumParamerter_NearZ_Get();
        z_far = HH_ClassWrapper_ViewingFrustumParamerter_FarZ_Get(); // r21
        HH_ClassWrapper_WorldViewMatrix_Get(wvm);
        HH_ClassWrapper_ViewScreenMatrix_Get(vsm);
        sceVu0UnitMatrix(clip_mat);

        scale = float_clamp(func_001B4100() / 1000.0f, 1.0f, 3.5f);
        clip_mat[0][0] = (2.0f * vsm[0][0]) / 4080.0f + (scale * func_001B4170()) * (float_abs(func_001B4230() - 2048.0f)) / 2048.0f;
        clip_mat[1][1] = (2.0f * vsm[1][1]) / 4080.0f + (scale * func_001B41C0()) * (float_abs(func_001B4250() - 2048.0f)) / 2048.0f;
    
        
        clip_mat[2][2] = (z_far + z_near) / (z_far - z_near);
        clip_mat[2][3] = 1.0f;
        clip_mat[3][2] = (-2.0f * (z_far * z_near)) / (z_far - z_near);
        clip_mat[3][3] = 0;
        sceVu0CopyMatrix(_pWork.unk0, clip_mat);
        sceVu0MulMatrix(_pWork.ViewFrustum_Primitive_ClipMatrix, clip_mat, wvm);
    } else {
        float clip_mat[4][4];
        float wvm[4][4];
        float vsm[4][4];
        float x_range, y_range;
        float z_near, z_far;
        z_near = HH_ClassWrapper_ViewingFrustumParamerter_NearZ_Get();
        z_far = HH_ClassWrapper_ViewingFrustumParamerter_FarZ_Get(); // r21
        HH_ClassWrapper_WorldViewMatrix_Get(wvm);
        HH_ClassWrapper_ViewScreenMatrix_Get(vsm);
        x_range = 1024.0f;
        y_range = 1024.0f;
        sceVu0UnitMatrix(clip_mat);
        clip_mat[0][0] = (2.0f * vsm[0][0]) / x_range;
        clip_mat[1][1] = (2.0f * vsm[1][1]) / y_range;
    
        
        clip_mat[2][2] = (z_far + z_near) / (z_far - z_near);
        clip_mat[2][3] = 1.0f;
        clip_mat[3][2] = (-2.0f * (z_far * z_near)) / (z_far - z_near);
        clip_mat[3][3] = 0;
        sceVu0CopyMatrix(_pWork.unk0, clip_mat);
        sceVu0MulMatrix(_pWork.ViewFrustum_Primitive_ClipMatrix, clip_mat, wvm);
    }
}

// @sh3: identical function
void ViewFrustum_BoundingBox_ClipMatrix_Create(void) {
    float clip_mat[4][4]; // r29+0x20
    float wvm[4][4]; // r29+0x60
    float vsm[4][4]; // r29+0xA0
    float x_range, y_range; // r29+0xE0
    float z_near = HH_ClassWrapper_ViewingFrustumParamerter_NearZ_Get(); // r20
    float z_far = HH_ClassWrapper_ViewingFrustumParamerter_FarZ_Get() - BOUNDING_BOX_Z_FAR; // r21


    
    HH_ClassWrapper_WorldViewMatrix_Get(wvm);
    HH_ClassWrapper_ViewScreenMatrix_Get(vsm);
    x_range = BOUNDING_BOX_X_RANGE;
    y_range = BOUNDING_BOX_Y_RANGE;
    sceVu0UnitMatrix(clip_mat);
    clip_mat[0][0] = (2.0f * vsm[0][0]) / x_range;
    clip_mat[1][1] = (2.0f * vsm[1][1]) / y_range;

    
    clip_mat[2][2] = (z_far + z_near) / (z_far - z_near);
    clip_mat[2][3] = 1.0f;
    clip_mat[3][2] = (-2.0f * (z_far * z_near)) / (z_far - z_near);
    clip_mat[3][3] = 0;
    sceVu0MulMatrix(_pWork.ViewFrustum_BoundingBox_ClipMatrix, clip_mat, wvm);
    
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", AlwaysFront_WorldView_Matrix_Create);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", HH_ClassWrapper_RotTrans_PerspectiveProjection_Clip);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142960);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142A00);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", HH_ClassWrapper_Point_Clip_Judge);

void HH_ClassWrapper_Matrix_Group_Update(void) {
    
    ViewFrustum_Primitive_ClipMatrix_Create();
    
    
    ViewFrustum_BoundingBox_ClipMatrix_Create();
    
    
    AlwaysFront_WorldView_Matrix_Create();
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", HH_ClassWrapper_ViewFrustum_Primitive_ClipMatrix_Get);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142B50);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142B60);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", HH_ClassWrapper_WorldViewMatrix_Get);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", HH_ClassWrapper_ViewScreenMatrix_Get);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142B90);


INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", HH_ClassWrapper_ViewingFrustumParamerter_NearZ_Get);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", HH_ClassWrapper_ViewingFrustumParamerter_FarZ_Get);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142BC0);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142BD0);

float HH_ClassWrapper_Float_Clamp(float Src_Value, float Min, float Max) {
    return float_min(float_max(Src_Value, Min), Max);
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142C00);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142C10);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", HH_ClassWrapper_SpotLight_ColorRatio_Calculator);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142D90);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142DA0);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142DE0);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142E30);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142EA0);

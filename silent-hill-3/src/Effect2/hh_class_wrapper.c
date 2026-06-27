#include "Effect2/hh_class_wrapper.h"
#include "Effect2/hh_math_wrapper.h"

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

/* sh3gde? */
extern float func_001B4110(void);
extern float func_001B4130(void);

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
        // @sh3: copies the clip matrix before wvm multiplication?
        sceVu0CopyMatrix(_pWork.ViewFrustum_Primitive_LocalClipMatrix, clip_mat);
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
        sceVu0CopyMatrix(_pWork.ViewFrustum_Primitive_LocalClipMatrix, clip_mat);
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

void AlwaysFront_WorldView_Matrix_Create(void) {
    float wvm[4][4];
    float inv_wvm[4][4];
    HH_ClassWrapper_WorldViewMatrix_Get(wvm);
    
    wvm[3][0] = 0;
    wvm[3][1] = 0;
    wvm[3][2] = 0;
    sceVu0TransposeMatrix(inv_wvm, wvm);
    sceVu0CopyMatrix(_pWork.AlwaysFront_WorldView_Matrix, inv_wvm);
}

/**
    @sh3: minor changes from the sh2 proto
*/
u_int HH_ClassWrapper_RotTrans_PerspectiveProjection_Clip(int* Dst_iVector, float* pReverse_W, sceVu0FMATRIX LocalScreen_Matrix, sceVu0FMATRIX LocalScreen_ClipMatrix, sceVu0FVECTOR Src_fVector) {
    u_int result = 0; // r2
    float reverse_w; // r29
    u_int clip; // r2

    // @sh3: vftoi4.xy -> vftoi4.xyz
    asm ("lqc2 vf24, 0(%3)\n\
          lqc2 vf25, 0x10(%3)\n\
          lqc2 vf26, 0x20(%3)\n\
          lqc2 vf27, 0x30(%3)\n\
          lqc2 vf28, 0(%4)\n\
          lqc2 vf29, 0x10(%4)\n\
          lqc2 vf30, 0x20(%4)\n\
          lqc2 vf31, 0x30(%4)\n\
          lqc2 vf4, 0(%5)\n\
          vmulax.xyzw acc, vf28, vf4x\n\
          vmadday.xyzw acc, vf29, vf4y\n\
          vmaddaz.xyzw acc, vf30, vf4z\n\
          vmaddw.xyzw vf7, vf31, vf0w\n vclipw.xyz vf7, vf7w\n\
          vmulax.xyzw acc, vf24, vf4x\n\
          vmadday.xyzw acc, vf25, vf4y\n\
          vmaddaz.xyzw acc, vf26, vf4z\n\
          vmaddw.xyzw vf5, vf27, vf0w\n\
          vdiv Q, vf0w, vf5w\n\
          vwaitq\n\
          vmulq.xyz vf5, vf5, Q\n\
          vftoi4.xyz vf6, vf5\n\
          sqc2 vf6, 0(%0)\n\
          vaddq.x vf1, vf0, Q\n\
          qmfc2 %1, vf1\n mtc1 %1, %2;\
          cfc2 %1, vi18"
    : "=r"(Dst_iVector), "=r"(clip), "+f"(reverse_w) 
    : "r"(LocalScreen_Matrix), "r"(LocalScreen_ClipMatrix), "r"(Src_fVector));


    if (clip & 0x3f) result = 1;
    if (result) {
        Dst_iVector[3] |= (1 << 15); // @sh3
    }

    *pReverse_W = reverse_w; return result;
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142960);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142A00);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", HH_ClassWrapper_Point_Clip_Judge);

void HH_ClassWrapper_Matrix_Group_Update(void) {
    
    ViewFrustum_Primitive_ClipMatrix_Create();
    
    
    ViewFrustum_BoundingBox_ClipMatrix_Create();
    
    
    AlwaysFront_WorldView_Matrix_Create();
}



void HH_ClassWrapper_ViewFrustum_Primitive_ClipMatrix_Get(sceVu0FMATRIX ViewFrustum_Primitive_ClipMatrix) {
    sceVu0CopyMatrix(ViewFrustum_Primitive_ClipMatrix, _pWork.ViewFrustum_Primitive_LocalClipMatrix);
}

void HH_ClassWrapper_ViewFrustum_ClipMatrix_Get(sceVu0FMATRIX ViewFrustum_Primitive_ClipMatrix) {
    sceVu0CopyMatrix(ViewFrustum_Primitive_ClipMatrix,  _pWork.ViewFrustum_Primitive_ClipMatrix);
}

void HH_ClassWrapper_AlwaysFront_WorldView_Matrix_Get(sceVu0FMATRIX AlwaysFront_WorldView_Matrix) {
    sceVu0CopyMatrix(AlwaysFront_WorldView_Matrix,  _pWork.AlwaysFront_WorldView_Matrix);
}

void HH_ClassWrapper_WorldViewMatrix_Get(sceVu0FMATRIX WorldView_Matrix) {
    sh3gde_getWorldViewMatrix(WorldView_Matrix);
}

void HH_ClassWrapper_ViewScreenMatrix_Get(sceVu0FMATRIX ViewScreen_Matrix) {
    sh3gde_getViewScreenMatrix(ViewScreen_Matrix);
}

void HH_ClassWrapper_WorldScreenMatrix_Get(sceVu0FMATRIX WorldScreen_Matrix) {
    sh3gde_getWorldScreenMatrix(WorldScreen_Matrix);
}

float HH_ClassWrapper_ViewingFrustumParamerter_NearZ_Get(void) {
    return func_001B4130();
}

float HH_ClassWrapper_ViewingFrustumParamerter_FarZ_Get(void) {
    return func_001B4110();
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142BC0);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142BD0);

float HH_ClassWrapper_Float_Clamp(float Src_Value, float Min, float Max) {
    return float_min(float_max(Src_Value, Min), Max);
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142C00);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142C10);

float HH_ClassWrapper_SpotLight_ColorRatio_Calculator(float* Light_Position, float* Light_Direction, float* Vertex, float Cos_Value, float Far_Z) {
    float result = 0.0f; // r20
    float vec[4]; // r29+0x30
    float cos_phai; // r29+0x40
    float vec_volume; // r21

    sceVu0SubVector(vec, Vertex, Light_Position);
    vec_volume = HH_MathWrapper_Sqrtf(sceVu0InnerProduct(vec, vec));

    
    if (vec_volume <= Far_Z) {
        sceVu0Normalize(vec, vec);
        cos_phai = sceVu0InnerProduct(vec, Light_Direction);

        
        if (cos_phai > Cos_Value) {
            float ratio_0 = 1.0f - vec_volume / Far_Z;
            float ratio_1 = (cos_phai - Cos_Value) / (1.0f - Cos_Value);
            result = ratio_0 * ratio_1;
        }
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142D90);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142DA0);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142DE0);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142E30);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", func_00142EA0);

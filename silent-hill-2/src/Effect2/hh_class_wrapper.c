#include "Effect2/hh_class_wrapper.h"
#include "sce/libvu0.h"
#include "GFW/sh2_DrawEnvData.h"
#include "view/vb_main.h"
#include "Event/item.h"
#include "shGs/sh2gfw_GS_NewLoopEnv.h"
#include "hh_math_wrapper.h"

static void ViewFrustum_Primitive_ClipMatrix_Create(void);
static void ViewFrustum_BoundingBox_ClipMatrix_Create(void);
static void AlwaysFront_WorldView_Matrix_Create(void);

extern /* static */ HH_Class_Wrapper_Work * _pWork;

void ViewFrustum_Primitive_ClipMatrix_Create(void) {
    float clip_mat[4][4]; // r29+0x20
    float wvm[4][4]; // r29+0x60
    float vsm[4][4]; // r29+0xA0
    float x_range, y_range; // r29+0xE0
    float z_near = HH_ClassWrapper_ViewingFrustumParamerter_NearZ_Get(); // r20
    float z_far = HH_ClassWrapper_ViewingFrustumParamerter_FarZ_Get(); // r21


    
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
    sceVu0MulMatrix(_pWork->ViewFrustum_Primitive_ClipMatrix, clip_mat, wvm);
    
}

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
    sceVu0MulMatrix(_pWork->ViewFrustum_BoundingBox_ClipMatrix, clip_mat, wvm);
    
}

void AlwaysFront_WorldView_Matrix_Create(void) {
    float wvm[4][4];
    float inv_wvm[4][4];
    HH_ClassWrapper_WorldViewMatrix_Get(wvm);
    
    wvm[3][0] = 0;
    wvm[3][1] = 0;
    wvm[3][2] = 0;
    sceVu0TransposeMatrix(inv_wvm, wvm);
    sceVu0CopyMatrix(_pWork->AlwaysFront_WorldView_Matrix, inv_wvm);
}

u_int HH_ClassWrapper_RotTrans_PerspectiveProjection_Clip(int * Dst_iVector /* r2 */, float * pReverse_W /* r2 */, sceVu0FMATRIX LocalScreen_Matrix /* r2 */, sceVu0FMATRIX LocalScreen_ClipMatrix, sceVu0FVECTOR Src_fVector /* r2 */) {
    u_int result; // r2
    float reverse_w; // r29
    u_int clip; // r2

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
          vftoi4.xy vf6, vf5\n\
          vftoi0.z vf6, vf5\n\
          sqc2 vf6, 0(%0)\n\
          vaddq.x vf1, vf0, Q\n\
          qmfc2 %1, vf1\n mtc1 %1, %2\n\
          cfc2 %1, vi18"
    : "=r"(Dst_iVector), "=r"(clip), "+f"(reverse_w) 
    : "r"(LocalScreen_Matrix), "r"(LocalScreen_ClipMatrix), "r"(Src_fVector));


    
    result = ((u_long) clip & 0x3ffff) ? 1 : 0; *pReverse_W = reverse_w; return result;
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", HH_ClassWrapper_Transform_PerspectiveProjection_Clip_forTriangleStrip);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", HH_ClassWrapper_Transform_PerspectiveProjection_Clip_N);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", HH_ClassWrapper_Point_Clip_Judge);

void HH_ClassWrapper_Matrix_Group_Update(void) {
    
    ViewFrustum_Primitive_ClipMatrix_Create();
    
    
    ViewFrustum_BoundingBox_ClipMatrix_Create();
    
    
    AlwaysFront_WorldView_Matrix_Create();
}

void HH_ClassWrapper_ViewFrustum_Primitive_ClipMatrix_Get(sceVu0FMATRIX ViewFrustum_Primitive_ClipMatrix) {
    sceVu0CopyMatrix(ViewFrustum_Primitive_ClipMatrix, _pWork->ViewFrustum_Primitive_ClipMatrix);
}


void HH_ClassWrapper_ViewFrustum_ClipMatrix_Get(sceVu0FMATRIX ViewFrustum_Primitive_ClipMatrix) {
    sceVu0CopyMatrix(ViewFrustum_Primitive_ClipMatrix,  _pWork->ViewFrustum_Primitive_ClipMatrix);
}

void HH_ClassWrapper_AlwaysFront_WorldView_Matrix_Get(sceVu0FMATRIX AlwaysFront_WorldView_Matrix) {
    sceVu0CopyMatrix(AlwaysFront_WorldView_Matrix,  _pWork->AlwaysFront_WorldView_Matrix);
}

void HH_ClassWrapper_WorldViewMatrix_Get(sceVu0FMATRIX WorldView_Matrix) {
    sceVu0CopyMatrix(WorldView_Matrix, VbWvsMatrix.wvm);
}

void HH_ClassWrapper_ViewScreenMatrix_Get(sceVu0FMATRIX ViewScreen_Matrix) {
    sceVu0CopyMatrix(ViewScreen_Matrix,  cam0.view_screen);
}

void HH_ClassWrapper_WorldScreenMatrix_Get(sceVu0FMATRIX WorldScreen_Matrix) {
    sceVu0CopyMatrix(WorldScreen_Matrix,  cam0.world_screen);
}

void HH_ClassWrapper_ViewDirection_Get(float* View_Direction) {
    sh2gde_getCameraDir(View_Direction);
}

void HH_ClassWrapper_LightDirection_Get(float* Light_Direction) {
    float tmp[4];
    shGetJamesLightPos(&tmp, Light_Direction);
}

float HH_ClassWrapper_ViewingFrustumParamerter_NearZ_Get(void) {
    return Env_ctl.camera_parms[3];
}

float HH_ClassWrapper_ViewingFrustumParamerter_FarZ_Get(void) {
    return Env_ctl.camera_parms2[2];
}

float HH_ClassWrapper_FogParameter_A_Get(void) {
    return (Env_ctl.fogparm.fl32[0] * Env_ctl.fogparm.fl32[2] - Env_ctl.fogparm.fl32[1] * Env_ctl.fogparm.fl32[3]) / (Env_ctl.fogparm.fl32[0] - Env_ctl.fogparm.fl32[1]);
}

float HH_ClassWrapper_FogParameter_B_Get(void) {
    return (Env_ctl.fogparm.fl32[0] * Env_ctl.fogparm.fl32[1] * (Env_ctl.fogparm.fl32[3] - Env_ctl.fogparm.fl32[2])) / (Env_ctl.fogparm.fl32[0] - Env_ctl.fogparm.fl32[1]);
}

float HH_ClassWrapper_Float_Clamp(float Src_Value, float Min, float Max) {
    return float_min(float_max(Src_Value, Min), Max);
}

void HH_ClassWrapper_AmbientColor_Get(float* Ambient_Color) {
    sceVu0ScaleVector(Ambient_Color, Env_ctl.ambient, 2.0f);
}

u_int HH_ClassWrapper_SpotLight_Enable_Check(void) {
    return item.light_switch;
}

void HH_ClassWrapper_SpotLight_EnvironmentParameter_Get(float* Light_Position, float* Light_Direction, float* Light_Color, float* Parameter) {
    float tmp[4];

    sh2gde_getspotKTParams(Light_Position, Light_Direction, Light_Color, tmp, 0);
    
    kari_sh2gde_getspotParams(tmp, tmp, Parameter);
}

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

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", HH_ClassWrapper_SpecularRatio0_Calculator);

void HH_ClassWrapper_SpecularRGBA_Add_BaseRGBA(s32* iRGBA, float* RGBA_Base, float* Specular_RGBA_Base, float Specular_Ratio) {
    asm ("lqc2 $vf30, 0(%1)\n\
          lqc2 $vf31, 0(%2)\n\
          mfc1 t0, %3\n\
          mfc1 t1, %4\n\
          qmtc2.ni t0, $vf29\n\
          ctc2.ni t1, $vi21\n\
          vmulx.xyzw $vf31, $vf31, $vf29x\n\
          vadd.xyzw $vf31, $vf30, $vf31\n\
          vmaxx.xyzw $vf31, $vf31, $vf0x\n\
          vminii.xyzw $vf31, $vf31, I\n\
          vftoi0.xyzw $vf31, $vf31\n\
          sqc2 $vf31, 0(%0)"
    : "=r"(iRGBA) : "r"(RGBA_Base), "r"(Specular_RGBA_Base), "f"(Specular_Ratio), "f"(255.0f) : "t0", "t1");
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", HH_ClassWrapper_MemoryCopy128Align_DesignateCycle);

u_long128* HH_ClassWrapper_GS_EnvironmentRegister_Frame_AlphaMask_Get(void) {
    return sh2gfw_Get_FrameAlphaRegAddr();
}

u_long128* HH_ClassWrapper_GS_EnvironmentRegister_Frame_NoMask_Get(void) {
    return sh2gfw_Get_FrameNormalRegAddr();
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_wrapper", HH_ClassWrapper_Packet_ADC_Flag_OnceMore_Set);

u_int HH_ClassWrapper_JMS_WorldPosition_Get(float* Position) {
    u_int result = 0;
    
    if (sh2jms.player != NULL) {
        sceVu0CopyVector(Position, &sh2jms.player->pos.x);
        result = 1;
    }
    
    return result;
}
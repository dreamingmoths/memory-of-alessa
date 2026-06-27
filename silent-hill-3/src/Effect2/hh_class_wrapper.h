#ifndef HH_CLASS_WRAPPER_H
#define HH_CLASS_WRAPPER_H

#include "common.h"

#define PRIMITIVE_X_RANGE 1024.0f
#define PRIMITIVE_Y_RANGE 1024.0f
#define BOUNDING_BOX_X_RANGE 1500.0f
#define BOUNDING_BOX_Y_RANGE 1500.0f
#define BOUNDING_BOX_Z_FAR 200.0f

typedef struct HH_Class_Wrapper_Work {
    // total size: 0x100
    float ViewFrustum_Primitive_LocalClipMatrix[4][4]; // offset: 0x0, size 0x40, @sh3
    float ViewFrustum_Primitive_ClipMatrix[4][4];      // offset 0x40, size 0x40
    float ViewFrustum_BoundingBox_ClipMatrix[4][4];    // offset 0x80, size 0x40
    float AlwaysFront_WorldView_Matrix[4][4];          // offset 0xC0, size 0x40
} HH_Class_Wrapper_Work;

u_int HH_ClassWrapper_RotTrans_PerspectiveProjection_Clip(int* Dst_iVector, float* pReverse_W, sceVu0FMATRIX LocalScreen_Matrix, sceVu0FMATRIX LocalScreen_ClipMatrix, float* Src_fVector);
void HH_ClassWrapper_Transform_PerspectiveProjection_Clip_forTriangleStrip(int* Dst_iVector, float* STQ_fVector, sceVu0FMATRIX LocalScreen_Matrix, sceVu0FMATRIX LocalScreen_ClipMatrix, float* Src_fVector);
void HH_ClassWrapper_Transform_PerspectiveProjection_Clip_N(int* Dst_iVector, float* STQ_fVector, sceVu0FMATRIX LocalScreen_Matrix, sceVu0FMATRIX LocalScreen_ClipMatrix, float* Src_fVector, u_int Clip_Mask);
u_int HH_ClassWrapper_Point_Clip_Judge(sceVu0FMATRIX LocalScreen_ClipMatrix, sceVu0FMATRIX pSrc_fVector_Array, u_int Array_Max);
void HH_ClassWrapper_Matrix_Group_Update(void);
void HH_ClassWrapper_ViewFrustum_Primitive_ClipMatrix_Get(sceVu0FMATRIX ViewFrustum_Primitive_ClipMatrix);
void HH_ClassWrapper_ViewFrustum_ClipMatrix_Get(sceVu0FMATRIX ViewFrustum_Primitive_ClipMatrix);
void HH_ClassWrapper_AlwaysFront_WorldView_Matrix_Get(sceVu0FMATRIX AlwaysFront_WorldView_Matrix);
void HH_ClassWrapper_WorldViewMatrix_Get(sceVu0FMATRIX WorldView_Matrix);
void HH_ClassWrapper_ViewScreenMatrix_Get(sceVu0FMATRIX ViewScreen_Matrix);
void HH_ClassWrapper_WorldScreenMatrix_Get(sceVu0FMATRIX WorldScreen_Matrix);
void HH_ClassWrapper_ViewDirection_Get(float* View_Direction);
void HH_ClassWrapper_LightDirection_Get(float* Light_Direction);
float HH_ClassWrapper_ViewingFrustumParamerter_NearZ_Get(void);
float HH_ClassWrapper_ViewingFrustumParamerter_FarZ_Get(void);
float HH_ClassWrapper_FogParameter_A_Get(void);
float HH_ClassWrapper_FogParameter_B_Get(void);
float HH_ClassWrapper_Float_Clamp(float Src_Value, float Min, float Max);
void HH_ClassWrapper_AmbientColor_Get(float* Ambient_Color);
u_int HH_ClassWrapper_SpotLight_Enable_Check(void);
void HH_ClassWrapper_SpotLight_EnvironmentParameter_Get(float* Light_Position, float* Light_Direction, float* Light_Color, float* Parameter);
float HH_ClassWrapper_SpotLight_ColorRatio_Calculator(float* Light_Position, float* Light_Direction, float* Vertex, float Cos_Value, float Far_Z);
float HH_ClassWrapper_SpecularRatio0_Calculator(float* View_Direction, float* Light_Direction, float* Normal_Vector, float Cos_Value);
void HH_ClassWrapper_SpecularRGBA_Add_BaseRGBA(int* iRGBA, float* RGBA_Base, float* Specular_RGBA_Base, float Specular_Ratio);
u_int HH_ClassWrapper_MemoryCopy128Align_DesignateCycle(void* pDestination_Address, void* pSource_Address, u_int Cycle_Max, u_int LoadStore_Size, u_int Next_Offset);
u_long128* HH_ClassWrapper_GS_EnvironmentRegister_Frame_AlphaMask_Get(void);
u_long128* HH_ClassWrapper_GS_EnvironmentRegister_Frame_NoMask_Get(void);
void HH_ClassWrapper_Packet_ADC_Flag_OnceMore_Set(u_int* pPacket_End, u_int Mesh_Width, u_int Mesh_Height);
u_int HH_ClassWrapper_JMS_WorldPosition_Get(float* Position);

#endif

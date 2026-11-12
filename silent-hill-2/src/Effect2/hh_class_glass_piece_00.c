#include "sh2_common.h"
#include "sce/libgraph.h"
#include "Effect2/hh_packet.h"
#include "Effect2/hh_math_wrapper.h"
#include "Effect2/hh_effect_object_texture.h"
#include "Effect2/hh_object_vertex_info.h"
#include "Effect2/hh_class_glass_piece_00.h"

#define STQ(x) ((x) / 2048.0f)

static sceVu0FVECTOR _elastic_vec  = {1.0f, -0.8f, 1.0f, 1.0f};
static sceVu0FVECTOR _friction_vec = {0.69999999f, 0.69999999f, 0.69999999f, 1.0f};

static sceVu0FMATRIX _square_00_vertex = {
    {  20.0f,  20.0f, 0.0f, 1.0f },
    {  20.0f, -20.0f, 0.0f, 1.0f },
    { -20.0f,  20.0f, 0.0f, 1.0f },
    { -20.0f, -20.0f, 0.0f, 1.0f },
};
static sceVu0FMATRIX _square_01_vertex = {
    {  20.0f, 0.0f,  20.0f, 1.0f },
    {  20.0f, 0.0f, -20.0f, 1.0f },
    { -20.0f, 0.0f,  20.0f, 1.0f },
    { -20.0f, 0.0f, -20.0f, 1.0f },
};
static sceVu0FMATRIX _square_00_normal = {
    { 0.0f, 0.0f, 1.0f, 1.0f },
    { 0.0f, 0.0f, 1.0f, 1.0f },
    { 0.0f, 0.0f, 1.0f, 1.0f },
    { 0.0f, 0.0f, 1.0f, 1.0f },
};
static sceVu0FMATRIX _square_01_normal = {
    { 0.0f, -1.0f, 0.0f, 1.0f },
    { 0.0f, -1.0f, 0.0f, 1.0f },
    { 0.0f, -1.0f, 0.0f, 1.0f },
    { 0.0f, -1.0f, 0.0f, 1.0f },
};

static sceVu0FMATRIX _square_stq_00 = {
    { 0.0f,         0.0f,         1.0f, 0.0f },
    { 0.0f,         STQ(1240.0f), 1.0f, 0.0f },
    { STQ(1240.0f), 0.0f,         1.0f, 0.0f },
    { STQ(1240.0f), STQ(1240.0f), 1.0f, 0.0f },
};

static sceVu0FMATRIX _square_stq_01 = {
    { 0.0f,         STQ(128.0f), 1.0f, 0.0f },
    { 0.0f,         STQ(252.0f), 1.0f, 0.0f },
    { STQ(1240.0f), STQ(128.0f), 1.0f, 0.0f },
    { STQ(1240.0f), STQ(252.0f), 1.0f, 0.0f },
};
static sceVu0FMATRIX _square_stq_02 = {
    { 0.0f,         STQ(256.0f), 1.0f, 0.0f },
    { 0.0f,         STQ(380.0f), 1.0f, 0.0f },
    { STQ(1240.0f), STQ(256.0f), 1.0f, 0.0f },
    { STQ(1240.0f), STQ(380.0f), 1.0f, 0.0f },
};
static sceVu0FMATRIX _square_stq_10 = {
    { STQ(128.0f), 0.0f,         1.0f, 0.0f },
    { STQ(128.0f), STQ(1240.0f), 1.0f, 0.0f },
    { STQ(252.0f), 0.0f,         1.0f, 0.0f },
    { STQ(252.0f), STQ(1240.0f), 1.0f, 0.0f },
};
static sceVu0FMATRIX _square_stq_11 = {
    { STQ(128.0f), STQ(128.0f), 1.0f, 0.0f },
    { STQ(128.0f), STQ(252.0f), 1.0f, 0.0f },
    { STQ(252.0f), STQ(128.0f), 1.0f, 0.0f },
    { STQ(252.0f), STQ(252.0f), 1.0f, 0.0f },
};
static sceVu0FMATRIX _square_stq_12 = {
    { STQ(128.0f), STQ(256.0f), 1.0f, 0.0f },
    { STQ(128.0f), STQ(380.0f), 1.0f, 0.0f },
    { STQ(252.0f), STQ(256.0f), 1.0f, 0.0f },
    { STQ(252.0f), STQ(380.0f), 1.0f, 0.0f },
};
static sceVu0FMATRIX _square_stq_20 = {
    { STQ(256.0f), 0.0f,         1.0f, 0.0f },
    { STQ(256.0f), STQ(1240.0f), 1.0f, 0.0f },
    { STQ(380.0f), 0.0f,         1.0f, 0.0f },
    { STQ(380.0f), STQ(1240.0f), 1.0f, 0.0f },
};
static sceVu0FMATRIX _square_stq_21 = {
    { STQ(256.0f), STQ(128.0f), 1.0f, 0.0f },
    { STQ(256.0f), STQ(252.0f), 1.0f, 0.0f },
    { STQ(380.0f), STQ(128.0f), 1.0f, 0.0f },
    { STQ(380.0f), STQ(252.0f), 1.0f, 0.0f },
};
static sceVu0FMATRIX _square_stq_22 = {
    { STQ(256.0f), STQ(256.0f), 1.0f, 0.0f },
    { STQ(256.0f), STQ(380.0f), 1.0f, 0.0f },
    { STQ(380.0f), STQ(256.0f), 1.0f, 0.0f },
    { STQ(380.0f), STQ(380.0f), 1.0f, 0.0f },
};

static sceVu0FVECTOR* _stq_list[9] = { 
    _square_stq_00, _square_stq_01, _square_stq_02, 
    _square_stq_10, _square_stq_11, _square_stq_12,
    _square_stq_20, _square_stq_21, _square_stq_22 
};

static Vertex_Infomeation_List _vertex_info_list[2] = {
    {
        /* .pVertexList = */ _square_00_vertex,
        /* .pNormalList = */ _square_00_normal,
        /* .vertexMax = */ 4,
        /* .primitiveType = */ 4,
    },
    {
        /* .pVertexList = */ _square_01_vertex,
        /* .pNormalList = */ _square_01_normal,
        /* .vertexMax = */ 4,
        /* .primitiveType = */ 4,
    }
};

static u_int Object_Initialize( HH_Object_GlassPiece_00* pThis,  ImpactQueue_Element* pElement);

static void ParabolaMotion_Calculator( HH_Object_GlassPiece_00* pThis, ImpactQueue_Element* element, float Time, float* Position) ;

static u_int Object_Draw( HH_Object_GlassPiece_00* pThis,  ImpactQueue_Element* pElement, float* Current_Position);

static float Specular_Calculator(float* Normal_Vector);

static void SpecularRGBA_Calculator(int* iRGBA, float* RGBA_Base, float* RGBA_Specular_Base, float* Normal_Vector);

#line 306
static u_int Object_Initialize(HH_Object_GlassPiece_00* pThis, ImpactQueue_Element* pElement) {
    u_int result = false;
    float* src_direction = pElement->Option.Vector[1];
    float theta, phai;    
    pThis->Timer = 0.0f;
    #line 322
    pThis->Verocity_0[0] = src_direction[0];
    pThis->Verocity_0[1] = src_direction[1];
    pThis->Verocity_0[2] = src_direction[2];
    
    pThis->Verocity_0[3] = 2450.0f;
    
    
    
    if (pElement->Option.Int_Value[0] == 0) {
        
        
        theta = TO_RAD(rand() % 360) - PI;
        phai  = TO_RAD(rand() % 360) - PI;
        
        
        theta *= 15.0f;
        phai  *= 15.0f;
        
        
        
        
        
        
        
        pThis->Rotate[0] = theta;
        pThis->Rotate[1] = phai;
        
        
        
        pThis->Vertex_Kind = rand() % 2U;
        
        pThis->Texture_Kind = rand() % 9U;
    }
    
    return result;
}

#line 372
static void ParabolaMotion_Calculator(HH_Object_GlassPiece_00* pThis, ImpactQueue_Element* element, float Time, float* Position) {
    sceVu0FMATRIX time_mat;


    sceVu0UnitMatrix(time_mat);
    time_mat[0][0] = Time;
    time_mat[1][1] = Time;
    time_mat[2][2] = Time;
    time_mat[3][1] = Time * Time;
    time_mat[3][3] = 0;
    sceVu0ApplyMatrix(Position, time_mat, pThis->Verocity_0);
}

u_int Object_Draw(HH_Object_GlassPiece_00* pThis, ImpactQueue_Element* pElement, float* Current_Position) {
    u_int result = false;
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();
    Vertex_Infomeation_List* pInfo = &_vertex_info_list[pThis->Vertex_Kind];
    sceVu0FVECTOR* pVertex = pInfo->pVertex_List;
    sceVu0FVECTOR* pNormal = pInfo->pNormal_List;
    u_int vertex_num = pInfo->Vertex_Max;
    u_int prim_type = pInfo->Primitive_Type;
    u_int i;
    sceVu0FMATRIX lwm, lsm, clip_mat;
    sceVu0IVECTOR rgba;
    sceVu0FVECTOR normal;
    sceVu0FVECTOR* pStq;
    float time, rot_x, rot_y;
    
    pStq = _stq_list[pThis->Texture_Kind];

    
    
    
    HH_ClassWrapper_WorldScreenMatrix_Get(lsm);
    
    sceVu0UnitMatrix(lwm);

    
    time = pThis->Timer + pElement->Option.Float_Value[0];
    rot_x = shReflexAngle(pThis->Rotate[0] * time);
    rot_y = shReflexAngle(pThis->Rotate[1] * time);
    sceVu0RotMatrixY(lwm, lwm, rot_y);
    sceVu0RotMatrixX(lwm, lwm, rot_x);
    
    sceVu0TransMatrix(lwm, lwm, pElement->Option.Vector[0]);
    sceVu0TransMatrix(lwm, lwm, Current_Position);
    sceVu0MulMatrix(lsm, lsm, lwm);

    
    HH_ClassWrapper_ViewFrustum_Primitive_ClipMatrix_Get(clip_mat);
    sceVu0MulMatrix(clip_mat, clip_mat, lwm);
    
    
    
    
    
    HH_Vif1PacketBuffer_GifTag_Open();
    
    sceVif1PkAddGsAD(pPk, SCE_GS_PRIM, SCE_GS_SET_PRIM(prim_type, 1, 1, 0, 1, 0, 0, 0, 0));
    
    {
    static sceVu0FVECTOR Specular_Rgba = { 128.0f, 128.0f, 128.0f, 128.0f };
    static sceVu0FVECTOR Base_Rgba = { 0.0f, 0.0f, 0.0f, 128.0f };
    
    
    
    
    
    
    
    
    
        lwm[3][0] = 0;
        lwm[3][1] = 0;
        lwm[3][2] = 0;
        sceVu0ApplyMatrix(normal, lwm, pNormal);
        SpecularRGBA_Calculator(rgba, &Base_Rgba, &Specular_Rgba, normal);
    }
    
    for (i = 0; i < vertex_num; i++) {
        sceVu0IVECTOR xyzf;
        float q;
        u_int addr;
        addr = SCE_GS_XYZF2;
        
        if (HH_ClassWrapper_RotTrans_PerspectiveProjection_Clip(xyzf, &q, lsm, clip_mat, pVertex + i)) {
            addr = SCE_GS_XYZF3;
        }
        
        
        
        
        
        
        
        sceVif1PkAddGsAD(pPk, SCE_GS_RGBAQ, SCE_GS_SET_RGBAQ(rgba[0], rgba[1], rgba[2], rgba[3], reinterpret_as_u_int(q)));
        sceVif1PkAddGsAD(pPk, SCE_GS_ST, SCE_GS_SET_ST(reinterpret_as_u_int(pStq[i][0] * q), reinterpret_as_u_int(pStq[i][1] * q)));
        sceVif1PkAddGsAD(pPk, addr, SCE_GS_SET_XYZF(xyzf[0], xyzf[1], xyzf[2] + 10, xyzf[3]));
    }
    
    HH_Vif1PacketBuffer_GifTag_Close();
    
    return result;
}

#line 500
static float Specular_Calculator(float* Normal_Vector) {
    float result;
    float specular_coefficient = 1.0f;
    float input_light_power;
    sceVu0FVECTOR revers_light_dir;
    sceVu0FVECTOR light_dir;
    sceVu0FVECTOR view_dir;
    sceVu0FVECTOR tmp_vec;
    float cos_theta;
    float cos_beta;
    static float cos_beta_min = 0.996194f;

    
    
    HH_ClassWrapper_LightDirection_Get(light_dir);
    
    
    
    
    sceVu0Normalize(light_dir, light_dir);
    HH_ClassWrapper_ViewDirection_Get(view_dir);
    sceVu0Normalize(view_dir, view_dir);
    
    
    cos_theta = sceVu0InnerProduct(light_dir, Normal_Vector);
    if (cos_theta < 0.0f)
        cos_theta = -cos_theta;
    
    sceVu0ScaleVectorXYZ(tmp_vec, Normal_Vector, 2.0f * cos_theta);
    sceVu0SubVector(revers_light_dir, tmp_vec, light_dir);
    sceVu0Normalize(revers_light_dir, revers_light_dir);
   
    cos_beta = sceVu0InnerProduct(revers_light_dir, view_dir);
    if (cos_beta < 0.0f)
        cos_beta = -cos_beta;
    
    
    
    
    
    
    if (cos_beta < cos_beta_min)
        result = 0.0f;

    else
        result = 1.0f - ((1.0f - cos_beta) / (1.0f - cos_beta_min));
    
    
    
    
    
    

    return result * specular_coefficient;


}

#line 569
static void SpecularRGBA_Calculator(sceVu0IVECTOR iRGBA, sceVu0FVECTOR RGBA_Base, sceVu0FVECTOR RGBA_Specular_Base, sceVu0FVECTOR Normal_Vector) {
    float specular = Specular_Calculator(Normal_Vector);
    #line 578
    asm("lqc2 vf30, 0(%1);\
         lqc2 vf31, 0(%2);\
         mfc1 t0, %3;\
         qmtc2.ni t0, vf29;\
         vmulx.w vf31, vf31, vf29x;\
         vadd.xyzw vf31, vf30, vf31;\
         vftoi0.xyzw vf29, vf31;\
         sqc2 vf29, 0(%0);\
    " : "=r"(iRGBA) : "r"(RGBA_Base), "r"(RGBA_Specular_Base), "f"(specular) : "t0", "t1", "memory");
    #line 606
}

#line 624
u_int HH_Class_Prefix_GlassPiece_00(void) {
    u_int result = true;
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();
    u_long tex0;
    
    HH_Vif1PacketBuffer_GifTag_Open();
    
    
    tex0 = HH_Effect_Object_Texture_GS_Register_Tex0_Get(HH_GLASS_PIECE_00_TEX_ID, 0);
    sceVif1PkAddGsAD(pPk, SCE_GS_TEX0_1, tex0);
    
    sceVif1PkAddGsAD(pPk, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP_1(SCE_GS_REGION_REPEAT, SCE_GS_REGION_REPEAT, 511, 0, 511, 0));
    sceVif1PkAddGsAD(pPk, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA_1(0, 1, 0, 1, 128));
    
    
    HH_Vif1PacketBuffer_GifTag_Close();
    
    return result;
}

#line 656
u_int HH_Class_Suffix_GlassPiece_00(void) {
    u_int result = true;
    return result;
}

#line 672
u_int HH_Class_GlassPiece_00(void* pBlock, ImpactQueue_Element* pElement) {
    #line 680
    u_int result = true; 
    HH_Object_GlassPiece_00* pThis = pBlock; 
    
    switch (pThis->Step) {
        case 0:
            Object_Initialize(pThis, pElement);
            pThis->Step++;
            break;
        case 1:
        {
            sceVu0FVECTOR position; 
            float* src_location  = pElement->Option.Vector[0];
            float* src_direction = pElement->Option.Vector[1];
            
            ParabolaMotion_Calculator(pThis, pElement, pThis->Timer, position);
            
            
            
            
            if (position[1] + src_location[1] > 0.0f) {
                sceVu0FVECTOR dir_vec;
                float volume;
                
                
            
                ParabolaMotion_Calculator(pThis, pElement, pThis->Timer - TIME_STEP_30FPS, dir_vec);
                
                sceVu0SubVector(dir_vec, position, dir_vec);
                
                volume = sceVu0InnerProduct(dir_vec, dir_vec);
                
                
                
                
                
                if (volume > 625.0f) {
                    sceVu0FVECTOR reflection_vec, ref_normalize;
                    float ref_xz_volume, tan_value, y;
                    sceVu0FVECTOR verocity_xz;
                    float v_xz_volume;
                    
                    
                    sceVu0AddVector(src_location, src_location, position);
                    src_location[1] = 0.0f;
                    
                    
                    sceVu0MulVector(reflection_vec, dir_vec, _elastic_vec);
                    #line 737
                    sceVu0Normalize(ref_normalize, reflection_vec);
                    ref_xz_volume = ref_normalize[1];
                    ref_normalize[1] = 0.0f;
                    y = sceVu0InnerProduct(ref_normalize, ref_normalize);
                    
                    v_xz_volume = ref_xz_volume / HH_MathWrapper_Sqrtf(y);
                    
                    sceVu0CopyVector(verocity_xz, pThis->Verocity_0);
                    verocity_xz[1] = 0;
                    verocity_xz[3] = 0;
                    tan_value = sceVu0InnerProduct(verocity_xz, verocity_xz);
                    
                    tan_value = HH_MathWrapper_Sqrtf(tan_value);
                    src_direction[1] = v_xz_volume * tan_value;
                    sceVu0MulVector(src_direction, src_direction, _friction_vec);
                    
                    
                    sceVu0CopyVector(position, (sceVu0FVECTOR){});
                    
                    
                    
                    pElement->Option.Int_Value[0] = 1;
                    
                    pElement->Option.Float_Value[0] += pThis->Timer;
                    pThis->Step = 0;
                } 
                
                else {
                    
                    position[1] = -src_location[1];
                    pThis->Step = 2;
                }
            }
            
            Object_Draw(pThis, pElement, position);
            
            pThis->Timer += TIME_STEP_30FPS;
            break;
        }
        case 2:
        {
            sceVu0FVECTOR position;
            float* src_location = pElement->Option.Vector[0];
            
            ParabolaMotion_Calculator(pThis, pElement, pThis->Timer, position);
            position[1] = -src_location[1];
            Object_Draw(pThis, pElement, position);
            
            break;
        }
        case 3: default:
            pThis->Header.Enable = false;
            result = false;
            break;
    }
    return result;
}

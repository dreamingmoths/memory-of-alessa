#include "sh2_common.h"
#include "math.h"
#include "sce/eestruct.h"
#include "sce/libvifpk.h"
#include "Effect2/hh_class_blood_01.h"
#include "Effect2/hh_packet.h"
#include "Effect2/hh_effect_object_texture.h"
#include "Effect2/hh_class_wrapper.h"
#include "Effect2/hh_effect_object_def.h"
#include "Effect2/hh_class_water_pool_00.h"

static u_int Object_Initialize(HH_Object_Water_Pool_00* pThis);
static u_int Object_Motion_00(HH_Object_Water_Pool_00* pThis);
static u_int Object_Draw(HH_Object_Water_Pool_00* pThis, ImpactQueue_Element* pElement);

static sceVu0FMATRIX _square_00_vertex = {
    { 1.0f, 0.0f, 1.0f, 1.0f },
    { 1.0f, 0.0f, -1.0f, 1.0f },
    { -1.0f, 0.0f, 1.0f, 1.0f },
    { -1.0f, 0.0f, -1.0f, 1.0f },
};

sceVu0FMATRIX _square_00_stq = {
    {0.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.24804687f, 1.0f, 0.0f},
    {0.24804687f, 0.0f, 1.0f, 0.0f},
    {0.24804687f, 0.24804687f, 1.0f, 0.0f},
};
sceVu0FMATRIX _square_01_stq = {
    {0.25f, 0.0f, 1.0f, 0.0f},
    {0.25f, 0.24804687f, 1.0f, 0.0f},
    {0.49804687f, 0.0f, 1.0f, 0.0f},
    {0.49804687f, 0.24804687f, 1.0f, 0.0f},
};
sceVu0FMATRIX _square_02_stq = {
    {0.5f, 0.0f, 1.0f, 0.0f},
    {0.5f, 0.24804687f, 1.0f, 0.0f},
    {0.74804687f, 0.0f, 1.0f, 0.0f},
    {0.74804687f, 0.24804687f, 1.0f, 0.0f},
};
sceVu0FMATRIX _square_03_stq = {
    {0.75f, 0.0f, 1.0f, 0.0f},
    {0.75f, 0.24804687f, 1.0f, 0.0f},
    {0.99804687f, 0.0f, 1.0f, 0.0f},
    {0.99804687f, 0.24804687f, 1.0f, 0.0f},
};
sceVu0FMATRIX _square_10_stq = {
    {0.0f, 0.25f, 1.0f, 0.0f},
    {0.0f, 0.49804687f, 1.0f, 0.0f},
    {0.24804687f, 0.25f, 1.0f, 0.0f},
    {0.24804687f, 0.49804687f, 1.0f, 0.0f},
};
sceVu0FMATRIX _square_11_stq = {
    {0.25f, 0.25f, 1.0f, 0.0f},
    {0.25f, 0.49804687f, 1.0f, 0.0f},
    {0.49804687f, 0.25f, 1.0f, 0.0f},
    {0.49804687f, 0.49804687f, 1.0f, 0.0f},
};
sceVu0FMATRIX _square_12_stq = {
    {0.5f, 0.25f, 1.0f, 0.0f},
    {0.5f, 0.49804687f, 1.0f, 0.0f},
    {0.74804687f, 0.25f, 1.0f, 0.0f},
    {0.74804687f, 0.49804687f, 1.0f, 0.0f},
};
sceVu0FMATRIX _square_13_stq = {
    {0.75f, 0.25f, 1.0f, 0.0f},
    {0.75f, 0.49804687f, 1.0f, 0.0f},
    {0.99804687f, 0.25f, 1.0f, 0.0f},
    {0.99804687f, 0.49804687f, 1.0f, 0.0f},
};
sceVu0FMATRIX _square_20_stq = {
    {0.0f, 0.5f, 1.0f, 0.0f},
    {0.0f, 0.74804687f, 1.0f, 0.0f},
    {0.24804687f, 0.5f, 1.0f, 0.0f},
    {0.24804687f, 0.74804687f, 1.0f, 0.0f},
};
sceVu0FMATRIX _square_21_stq = {
    {0.25f, 0.5f, 1.0f, 0.0f},
    {0.25f, 0.74804687f, 1.0f, 0.0f},
    {0.49804687f, 0.5f, 1.0f, 0.0f},
    {0.49804687f, 0.74804687f, 1.0f, 0.0f},
};
sceVu0FMATRIX _square_22_stq = {
    {0.5f, 0.5f, 1.0f, 0.0f},
    {0.5f, 0.74804687f, 1.0f, 0.0f},
    {0.74804687f, 0.5f, 1.0f, 0.0f},
    {0.74804687f, 0.74804687f, 1.0f, 0.0f},
};
sceVu0FMATRIX _square_23_stq = {
    {0.75f, 0.5f, 1.0f, 0.0f},
    {0.75f, 0.74804687f, 1.0f, 0.0f},
    {0.99804687f, 0.5f, 1.0f, 0.0f},
    {0.99804687f, 0.74804687f, 1.0f, 0.0f},
};
sceVu0FMATRIX _square_30_stq = {
    {0.0f, 0.75f, 1.0f, 0.0f},
    {0.0f, 0.99804687f, 1.0f, 0.0f},
    {0.24804687f, 0.75f, 1.0f, 0.0f},
    {0.24804687f, 0.99804687f, 1.0f, 0.0f},
};
sceVu0FMATRIX _square_31_stq = {
    {0.25f, 0.75f, 1.0f, 0.0f},
    {0.25f, 0.99804687f, 1.0f, 0.0f},
    {0.49804687f, 0.75f, 1.0f, 0.0f},
    {0.49804687f, 0.99804687f, 1.0f, 0.0f},
};
sceVu0FMATRIX _square_32_stq = {
    {0.5f, 0.75f, 1.0f, 0.0f},
    {0.5f, 0.99804687f, 1.0f, 0.0f},
    {0.74804687f, 0.75f, 1.0f, 0.0f},
    {0.74804687f, 0.99804687f, 1.0f, 0.0f},
};
sceVu0FMATRIX _square_33_stq = {
    {0.75f, 0.75f, 1.0f, 0.0f},
    {0.75f, 0.99804687f, 1.0f, 0.0f},
    {0.99804687f, 0.75f, 1.0f, 0.0f},
    {0.99804687f, 0.99804687f, 1.0f, 0.0f},
};

static sceVu0FMATRIX* _square_stq_list[16] = {
    _square_00_stq, _square_01_stq, _square_02_stq, _square_03_stq, 
    _square_10_stq, _square_11_stq, _square_12_stq, _square_13_stq, 
    _square_20_stq, _square_21_stq, _square_22_stq, _square_23_stq,
    _square_30_stq, _square_31_stq, _square_32_stq, _square_33_stq 
};

static sceVu0FVECTOR _rgba_start_list[1] = {
    { 255.0f, 255.0f, 255.0f, 255.0f },
};

static sceVu0FVECTOR _rgba_end_list[1] = {
    { 188.0f, 188.0f, 218.0f, 50.0f },
};

static sceVu0FVECTOR _scale_start_list[3] = {
    { 0.0f, 0.0f, 0.0f, 1.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f },
};

static sceVu0FMATRIX _scale_end_list = {
    { 200.0f, 1.0f, 200.0f, 1.0f },
    { 250.0f, 1.0f, 250.0f, 1.0f },
    { 275.0f, 1.0f, 275.0f, 1.0f },
    { 300.0f, 1.0f, 300.0f, 1.0f },
};

static Motion_Table_Infomeation _motion_info[4] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.4f, 0.5f, 0.3f },
    { 0.8f, 0.5f, 0.5f },
    { 1.2f, 0.5f, 0.2f },
};

static inline shColumnScaleXyz(HH_Object_Water_Pool_00* pThis, sceVu0FMATRIX lwm) {
    sceVu0FMATRIX ones; int i;
    sceVu0UnitMatrix(ones);
    
    for (i = 0; i < 3; i++) {
        ones[i][i] *= pThis->Scale[i];
    }
    
    sceVu0MulMatrix(lwm, lwm, ones);
}

#line 314
static u_int Object_Initialize(HH_Object_Water_Pool_00* pThis) {
    u_int result = true;
    float radian;

    
 
    
    
    pThis->Texture_Kind = rand() % 16U;
    pThis->Scale_Kind = rand() % 3U;
    pThis->Rgba_Kind = rand() * 0;
    
    
    
    pThis->Timer = 0.0f;
    
    
    radian = TO_RAD(1) * (rand() % 360);

    pThis->Rotate_Y = shReflexAngle(radian);
    
    
    
    
    pThis->Motion_Step = 0;
    
    return result;
}

#line 354
static u_int Object_Motion_00(HH_Object_Water_Pool_00* pThis) {
    u_int result = false;
    
    float* pRgba_s = _rgba_start_list[pThis->Rgba_Kind];
    float* pRgba_e = _rgba_end_list[pThis->Rgba_Kind];
    float* pScale_s = _scale_start_list[pThis->Scale_Kind];
    float* pScale_e = _scale_end_list[pThis->Scale_Kind];
    
    float local_time_start = 0.0f;
    float local_time_end;
    
    float local_scale_start = 0.0f;
    float local_scale_end;
    
    float local_rgba_start = 0.0f;
    float local_rgba_end;
    
    Motion_Table_Infomeation* pMotion_Info = _motion_info;
    u_int i;
    u_int current_step = pThis->Motion_Step;
    float local_diff_time_current, local_diff_time_max, local_diff_time_ratio;
    float scale_ratio, rgba_ratio;
    if (current_step > 2) 
        current_step = 2;
    
    for (i = 0; i < current_step + 1; i++) {
        local_time_start += pMotion_Info[i].diff_time;
        local_scale_start+= pMotion_Info[i].diff_scale_ratio;
        local_rgba_start+= pMotion_Info[i].diff_rgba_ratio;
    }
    local_time_end = local_time_start + pMotion_Info[i].diff_time;
    local_scale_end = local_scale_start + pMotion_Info[i].diff_scale_ratio;
    local_rgba_end = local_rgba_start + pMotion_Info[i].diff_rgba_ratio;
    
    
    switch (pThis->Motion_Step) {
        case 0:
            if (pThis->Timer > local_time_end) {
                pThis->Motion_Step++;
            }
            break;
        case 1:
            if (pThis->Timer > local_time_end) {
                pThis->Motion_Step++;
            }
            break;
        case 2:
            if (pThis->Timer > local_time_end) {
                pThis->Motion_Step++;
            }
            break;
    }
    
    
    
    
    
    local_diff_time_max = (pThis->Timer - local_time_start);
    local_diff_time_current = (local_time_end-local_time_start);
    
    local_diff_time_ratio = local_diff_time_max / local_diff_time_current;

    
    
    if (local_diff_time_ratio > 1.0f) {
        local_diff_time_ratio = 1.0f;
    }
    
    scale_ratio = local_scale_start + (local_diff_time_ratio * (local_scale_end - local_scale_start));
    rgba_ratio = local_rgba_start + (local_diff_time_ratio * (local_rgba_end - local_rgba_start));
    
    sceVu0InterVectorXYZ(pThis->Scale, pScale_e, pScale_s, scale_ratio);
    
    sceVu0InterVector(pThis->Rgba,pRgba_e, pRgba_s, rgba_ratio);
    
    return result;
}

#line 443
static u_int Object_Draw(HH_Object_Water_Pool_00* pThis, ImpactQueue_Element* pElement) {
    u_int result = false;
    sceVif1Packet *pPk = HH_Vif1Packet_Current_Get();
    sceVu0FVECTOR* pVertex = _square_00_vertex;
    sceVu0FVECTOR* pStq = _square_stq_list[pThis->Texture_Kind];
    u_int vertex_num, prim_type, i;
    sceVu0FMATRIX lwm, lsm, clip_mat;
    sceVu0FVECTOR Rgba, pos, dir;
    sceVu0IVECTOR rgba, xyzf;
    float q;
    u_int addr;
    static float color_scale;
    
    
    
    
    if (HH_ClassWrapper_SpotLight_Enable_Check()) {
        float cos_theta, far_z; // @ weird
        color_scale = HH_ClassWrapper_SpotLight_ColorRatio_Calculator(pos, dir, lwm[3], cos_theta, far_z);
        color_scale = HH_ClassWrapper_Float_Clamp(color_scale, 0.2f, 1.0f);
    } 
    else {
        color_scale = 0.2f;
    }
    
    
    
    HH_ClassWrapper_WorldScreenMatrix_Get(lsm);
    
    sceVu0UnitMatrix(lwm);
    shColumnScaleXyz(pThis, lwm);
    sceVu0RotMatrixY(lwm, lwm, pThis->Rotate_Y);
    
    sceVu0TransMatrix(lwm, lwm, pElement->Option.Vector[0]);
    sceVu0MulMatrix(lsm, lsm, lwm);


    HH_ClassWrapper_ViewFrustum_Primitive_ClipMatrix_Get(clip_mat);
    sceVu0MulMatrix(clip_mat, clip_mat, lwm);
    
    
    HH_Vif1PacketBuffer_GifTag_Open();
    prim_type = SCE_GS_PRIM_TRISTRIP;
    sceVif1PkAddGsAD(pPk, SCE_GS_PRIM, SCE_GS_SET_PRIM(prim_type, 1, 1, 0, 1, 0, 0, 0, 0));
    #line 499
    sceVu0CopyVector(Rgba, pThis->Rgba);
    Rgba[3] *= color_scale;
    
    sceVu0ClampVector(Rgba, Rgba, 0.0f, 255.0f);
    sceVu0FTOI0Vector(rgba, Rgba);

    vertex_num = 4;
    for (i = 0; i < vertex_num; i++) {

        
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

#line 543
u_int HH_Class_Prefix_Water_Pool_00(void) {
    unsigned int result = true;
    sceVif1Packet *pPk = HH_Vif1Packet_Current_Get();
    u_long tex0;

    HH_Vif1PacketBuffer_GifTag_Open();
    
    
    tex0 = HH_Effect_Object_Texture_GS_Register_Tex0_Get(HH_WATER_POOL_00_TEX_ID, 0);
    sceVif1PkAddGsAD(pPk, SCE_GS_TEX0_1, tex0);
    
    sceVif1PkAddGsAD(pPk, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA_1(0, 1, 0, 1, 128));
    
    HH_Vif1PacketBuffer_GifTag_Close();
    
    return result;
}

#line 573
u_int HH_Class_Suffix_Water_Pool_00(void) {
    u_int result = true;
    return result;
}

#line 589
u_int HH_Class_Water_Pool_00(void* pBlock, ImpactQueue_Element* pElement) {
    #line 596
    u_int result = true;
    HH_Object_Water_Pool_00* pThis = pBlock;

    switch (pThis->Step) {
        case HH_EFFECT_STEP_INIT:
            
            Object_Initialize(pThis);
       
            pThis->Step = HH_EFFECT_STEP_DRAW;
            break;
        case HH_EFFECT_STEP_DRAW:
            
            Object_Motion_00(pThis);
            
            if (pThis->Motion_Step > 2) {
            
                pThis->Rgba[3] = 0;
                pThis->Step = 2;
            }
            
            
            
            Object_Draw(pThis, pElement);
            
            pThis->Timer += TIME_STEP_30FPS;
            break;
        default:
        case HH_EFFECT_STEP_OFF:
            pThis->Header.Enable = false;
            result = false;
            break;
    }
    return result;
}

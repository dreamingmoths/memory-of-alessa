#include "sh2_common.h"
#include "sce/libvifpk.h"
#include "Effect2/hh_packet.h"
#include "Effect2/hh_class_wrapper.h"
#include "Effect2/hh_effect_object_texture.h"
#include "Effect2/hh_object_vertex_info.h"
#include "Effect2/hh_class_dust_00.h"

static u_int Object_Initialize(HH_Object_Dust_00* pThis, ImpactQueue_Element* pElement);
static void ParabolaMotion_Calculator(HH_Object_Dust_00* pThis, ImpactQueue_Element* pElement, float Time, float* Position);
static u_int Object_Motion_00(HH_Object_Dust_00* pThis, ImpactQueue_Element* pElement);

static sceVu0FMATRIX _square_00_vertex = {
    { -200.0f, -200.0f, 0.0f, 1.0f },
    { -200.0f, 200.0f, 0.0f, 1.0f },
    { 200.0f, -200.0f, 0.0f, 1.0f },
    { 200.0f, 200.0f, 0.0f, 1.0f }
};

static sceVu0FMATRIX _square_00_normal = {
    { 0.0f, 0.0f, -1.0f, 1.0f },
    { 0.0f, 0.0f, -1.0f, 1.0f },
    { 0.0f, 0.0f, -1.0f, 1.0f },
    { 0.0f, 0.0f, -1.0f, 1.0f }
};

static sceVu0FMATRIX _square_00_stq = {
    { 0.5f, 0.5f, 1.0f, 0.0f },
    { 0.5f, 0.74804688f, 1.0f, 0.0f },
    { 0.74804688f , 0.5f, 1.0f, 0.0f },
    { 0.74804688f , 0.74804688f, 1.0f, 0.0f }
};

static sceVu0FMATRIX _square_01_stq = {
    { 0.75f, 0.5f, 1.0f, 0.0f },
    { 0.75f, 0.74804688f, 1.0f, 0.0f },
    { 0.99804688f, 0.5f, 1.0f, 0.0f },
    { 0.99804688f, 0.74804688f, 1.0f, 0.0f }
};

static sceVu0FMATRIX _square_10_stq = {
    { 0.5f, 0.75f, 1.0f, 0.0f },
    { 0.5f, 0.99804688f, 1.0f, 0.0f },
    { 0.74804688f, 0.75f, 1.0f, 0.0f },
    { 0.74804688f, 0.99804688f, 1.0f, 0.0f }
};

static sceVu0FMATRIX _square_11_stq = {
    { 0.75f, 0.75f, 1.0f, 0.0f },
    { 0.75f, 0.99804688f, 1.0f, 0.0f },
    { 0.99804688f, 0.75f, 1.0f, 0.0f },
    { 0.99804688f, 0.99804688f, 1.0f, 0.0f }
};

static sceVu0FVECTOR* _square_0x_stq_list[4] = { 
    _square_00_stq, _square_01_stq,
    _square_10_stq, _square_11_stq
};

static Vertex_Infomeation_List _vertex_info_list[1] = { _square_00_vertex, _square_00_normal, 4, 4 };
static float _rgba_start_list[1] = { 0.0f }; // size: 0x4, address: 0x36E8B0
static float _rgba_end_list[1] = { 120.0f }; // size: 0x4, address: 0x36E8B8
static float _scale_start_list[1] = { 0.1f }; // size: 0x4, address: 0x36E8C0
static float _scale_end_list[1] = { 1.0f }; // size: 0x4, address: 0x36E8C8
static Motion_Table_Infomeation _motion_info[3] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.6f, 0.8f, 1.0f },
    { 1.5f, 0.8f, -1.0f }
 };


#line 253
static u_int Object_Initialize(HH_Object_Dust_00* pThis, ImpactQueue_Element* pElement) {
    u_int result = false;
    float* src_direction;
    float resist_xz, resist_y0, resist_ya;
    pThis->Timer = 0.0f;
    
    
    pThis->Vertex_Kind = rand() & 3;
    #line 273
    resist_xz = 0.05494505f;
    resist_y0 = 0.16483516f;
    resist_ya = 134.61537f;
    src_direction = pElement->Option.Vector[1];
    
    pThis->Verocity_0[0] = src_direction[0] * resist_xz;
    pThis->Verocity_0[1] = src_direction[1] * resist_y0;
    pThis->Verocity_0[2] = src_direction[2] * resist_xz;
    
    pThis->Verocity_0[3] = resist_ya;
    
    
    return result;
}

#line 301
static void ParabolaMotion_Calculator(HH_Object_Dust_00* pThis, ImpactQueue_Element* pElement, float Time, float* Position) {
    sceVu0FMATRIX time_mat;


    sceVu0UnitMatrix(time_mat);
    time_mat[0][0] = Time;
    time_mat[1][1] = Time;
    time_mat[2][2] = Time;
    time_mat[3][1] = Time * Time;
    time_mat[3][3] = 0;
    sceVu0ApplyMatrix(Position, time_mat, &pThis->Verocity_0);
}

#line 317
static u_int Object_Motion_00(HH_Object_Dust_00* pThis, ImpactQueue_Element* pElement) {
    u_int result = false;
    u_int kind;
    float Rgba_s, Rgba_e;
    float Scale_s, Scale_e; 
    float local_time_start, local_time_end;   
    float local_scale_start, local_scale_end; 
    float local_rgba_start, local_rgba_end;
    Motion_Table_Infomeation* pMotion_Info;
    u_int i;    
    u_int current_step;
    float local_diff_time_current, local_diff_time_max, local_diff_time_ratio;
    float scale_ratio;  
    float rgba_ratio;

    Rgba_s = _rgba_start_list[0];
    Rgba_e = _rgba_end_list[0];
    Scale_s = _scale_start_list[0];
    Scale_e = _scale_end_list[0];
    
    local_time_start = 0.0f;
    
    
    local_scale_start = 0.0f;
    
    
    local_rgba_start = 0.0f;
    
    
    pMotion_Info = _motion_info;
    
    current_step = pThis->Motion_Step;

    
    if (current_step > 2)
        current_step = 2;
        
    for(i = 0; i < current_step + 1; i++) {
        local_time_start += pMotion_Info[i].diff_time;
        local_scale_start += pMotion_Info[i].diff_scale_ratio;
        local_rgba_start += pMotion_Info[i].diff_rgba_ratio;
    }    
    local_time_end = local_time_start + pMotion_Info[i].diff_time;
    local_scale_end = local_scale_start + pMotion_Info[i].diff_scale_ratio;
    local_rgba_end = local_rgba_start + pMotion_Info[i].diff_rgba_ratio;
    
    
    switch (pThis->Motion_Step) {
        case 0:
            if(pThis->Timer > local_time_end){
                pThis->Motion_Step++;
            }
            break;
        case 1:
            if(pThis->Timer > local_time_end){
                pThis->Motion_Step++;
            }
            break;
        case 2:
            if(pThis->Timer > local_time_end){
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
    rgba_ratio =  local_rgba_start + (local_diff_time_ratio * (local_rgba_end - local_rgba_start));

    pThis->Scale = Scale_e * scale_ratio + Scale_s * (1.0f - scale_ratio);
    pThis->Alpha = Rgba_e * rgba_ratio + Rgba_s * (1.0f - rgba_ratio);
    
    return result;
}

#line 419
static u_int Object_Draw(HH_Object_Dust_00* pThis, ImpactQueue_Element* pElement, float* Current_Position) {
    u_int result = false;
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get(); 
    Vertex_Infomeation_List* pInfo = _vertex_info_list;
    sceVu0FVECTOR* pVertex = pInfo->pVertex_List;
    sceVu0FVECTOR* pStq = _square_0x_stq_list[pThis->Vertex_Kind];
    sceVu0FMATRIX lwm, lsm, clip_mat;
    sceVu0IVECTOR xyzf, rgba;
    sceVu0FVECTOR stq_dummy;

    
    
    
    
    HH_ClassWrapper_WorldScreenMatrix_Get(lsm);

    
    HH_ClassWrapper_AlwaysFront_WorldView_Matrix_Get(lwm);

    
    sceVu0ScaleVector(lwm[0], lwm[0], pThis->Scale);
    sceVu0ScaleVector(lwm[1], lwm[1], pThis->Scale);
    sceVu0ScaleVector(lwm[2], lwm[2], pThis->Scale);
    
    sceVu0TransMatrix(lwm, lwm, pElement->Option.Vector[0]);
    sceVu0TransMatrix(lwm, lwm, Current_Position);
    sceVu0MulMatrix(lsm, lsm, lwm);

    
    HH_ClassWrapper_ViewFrustum_Primitive_ClipMatrix_Get(clip_mat);
    sceVu0MulMatrix(clip_mat, clip_mat, lwm);
    
    
    
    {    
        sceVu0FVECTOR Base_Rgba = { 80.0f, 93.0f, 70.0f, pThis->Alpha };
        sceVu0FVECTOR Rgba;
        sceVu0FVECTOR view_dir, pos, dir;
        sceVu0FVECTOR light_color, parameter;
        float color_scale;
            
        color_scale = 0.0f;
        
            
            
        HH_ClassWrapper_ViewDirection_Get(view_dir);
        
        HH_ClassWrapper_SpotLight_EnvironmentParameter_Get(pos, dir, light_color, parameter);
        
        if (HH_ClassWrapper_SpotLight_Enable_Check()) {
            
            color_scale = HH_ClassWrapper_SpotLight_ColorRatio_Calculator(pos, dir, lwm[3], parameter[0], parameter[2]);
            color_scale = HH_ClassWrapper_Float_Clamp(color_scale, 0.0f, 1.0f);
        }
        sceVu0CopyVector(Rgba, Base_Rgba);
        Rgba[3] *= color_scale;
    
        Rgba[3] += 12.0f;
        
        
        
        sceVu0ClampVector(Rgba, Rgba, 0.0f, 255.0f);
        
        sceVu0FTOI0Vector(rgba, Rgba);
    }
        
        
        HH_Vif1PacketBuffer_GifTag_Open();
        
        HH_Vif1Packet_GeneralGifTag_Sprite_Open();
        ((u_long128*)pPk->pCurrent)[0] = *(u_long128*) rgba; 
        
        HH_ClassWrapper_Transform_PerspectiveProjection_Clip_N(xyzf, stq_dummy, lsm, clip_mat, pVertex[0], 0x3F);
        ((u_long128*)pPk->pCurrent)[1] = *(u_long128*) pStq;
        xyzf[2] += sizeof(u_long128) * 10;
        ((u_long128*)pPk->pCurrent)[2] = *(u_long128*) xyzf;
        
        HH_ClassWrapper_Transform_PerspectiveProjection_Clip_N(xyzf, stq_dummy, lsm, clip_mat, pVertex[3], 0x3F);
        ((u_long128*)pPk->pCurrent)[3] = *(u_long128*) pStq[3];
        xyzf[2] += sizeof(u_long128) * 10;
        ((u_long128*)pPk->pCurrent)[4] = *(u_long128*) xyzf;
        ((u_long128*)pPk->pCurrent) += 5;
        sceVif1PkCloseGifTag(pPk);
        
        HH_Vif1PacketBuffer_GifTag_Close();
        
        return 0;
}

#line 525
u_int HH_Class_Prefix_Dust_00(void) {
    u_int result = true;
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();
    u_long tex0;
    
    HH_Vif1PacketBuffer_GifTag_Open();
    
    tex0 = HH_Effect_Object_Texture_GS_Register_Tex0_Get(0, 0);
    sceVif1PkAddGsAD(pPk, HH_CLASS_DUST_00_TEX_ID, tex0);
    
    sceVif1PkAddGsAD(pPk, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA_1(0, 1, 0, 1, 128));
    sceVif1PkCloseGifTag(pPk);
    HH_Vif1PacketBuffer_GifTag_Close();
    
    return result;
}

#line 553
u_int HH_Class_Suffix_Dust_00(void) {
    u_int result = true;
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();
    
    HH_Vif1PacketBuffer_GifTag_Open();
    HH_Vif1Packet_GeneralGifTag_GS_AD_Open();
    sceVif1PkAddGsAD(pPk, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA_1(0, 1, 0, 1, 128));
    HH_Vif1PacketBuffer_GifTag_Close();
    
    return result;
}

#line 576
u_int HH_Class_Dust_00(void* pBlock, ImpactQueue_Element* pElement) {
    u_int result;
    HH_Object_Dust_00* pThis;
    
    
    
    
    
    result = true;
    pThis = pBlock;
    
    switch (pThis->Step) {
    case 0:
        Object_Initialize(pThis, pElement);
        pThis->Step++;
        break;
    case 1:
        {
            float position[4];
            
            ParabolaMotion_Calculator(pThis, pElement, pThis->Timer, position);
            
            Object_Motion_00(pThis, pElement);
            #line 622
            if ((position[1] + pElement->Option.Vector[0][1]) > 0.0f) {
                pThis->Step = 2;
                pThis->Step = 3; // @ bug?
            }
            
            Object_Draw(pThis, pElement, position);
            
            pThis->Timer += TIME_STEP_60FPS;
            break;
        }
    case 2:
        { 
            float position[4];
            
            ParabolaMotion_Calculator(pThis, pElement,pThis->Timer, position);
            position[1] = -pElement->Option.Vector[0][1];
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

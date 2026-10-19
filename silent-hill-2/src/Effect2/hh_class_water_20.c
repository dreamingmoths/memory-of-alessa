#include "Effect2/hh_class_water_20.h"
#include "Effect2/hh_class_water_common.h"
#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_wrapper.h"
#include "Effect2/hh_effect_object_texture.h"
#include "Effect2/hh_object_vertex_info.h"
#include "Effect2/hh_math_wrapper.h"
#include "Effect2/hh_packet.h"
#include "sce/libvifpk.h"

static u_int Object_Initialize(HH_Object_Water_20* pThis, ImpactQueue_Element* pElement);
static void ParabolaMotion_Calculator(HH_Object_Water_20* pThis, ImpactQueue_Element* pElement, float Time, float* Position);
static u_int Object_Motion_00(HH_Object_Water_20* pThis, ImpactQueue_Element* pElement);
static u_int Object_Draw(HH_Object_Water_20* pThis, ImpactQueue_Element* pElement, float* Current_Position );

static sceVu0FMATRIX _square_00_vertex_0x00370200 = {
    { -50.0f, -50.0f, 0.0f, 1.0f },
    { -50.0f,  50.0f, 0.0f, 1.0f },
    {  50.0f, -50.0f, 0.0f, 1.0f },
    {  50.0f,  50.0f, 0.0f, 1.0f }
};

static sceVu0FMATRIX _square_00_normal_0x00370240 = {
    { 0.0f, 0.0f, -1.0f, 1.0f },
    { 0.0f, 0.0f, -1.0f, 1.0f },
    { 0.0f, 0.0f, -1.0f, 1.0f },
    { 0.0f, 0.0f, -1.0f, 1.0f }
};

static sceVu0FMATRIX _square_00_stq_0x00370280 = {
    { 1.0f,       0.0f,        1.0f, 0.0f },
    { 1.0f,       0.99609375f, 1.0f, 0.0f },
    { 1.9960938f, 0.0f,        1.0f, 0.0f },
    { 1.9960938f, 0.99609375f, 1.0f, 0.0f }
};

static sceVu0FMATRIX _square_01_stq_0x003702C0 = {
    { 1.0f,       0.0f,        1.0f, 0.0f },
    { 1.9960938f, 0.0f,        1.0f, 0.0f },
    { 1.0f,       0.99609375f, 1.0f, 0.0f },
    { 1.9960938f, 0.99609375f, 1.0f, 0.0f }
};

static float (*_square_0x_stq_list_0x00370300[2])[4] = {
    _square_00_stq_0x00370280,
    _square_01_stq_0x003702C0
};

static Vertex_Infomeation_List _vertex_info_list_0x00370310[1] = {
    {
        _square_00_vertex_0x00370200,  /* pVertex_List */
        _square_00_normal_0x00370240,  /* pNormal_List */
        4,                             /* Vertex_Max */
        4                              /* Primitive_Type */
    }
};

static float _rgba_start_list_0x00370320[2] = {
    102.0f, 102.0f
};

/* 0x370328 */
static float _rgba_end_list_0x00370328[2] = {
    10.0f, 10.0f
};


static float _scale_start_list_0x00370330[2] = {
    0.1f, 0.1f
};

static float _scale_end_list_0x00370338[2] = {
    3.5f, 4.0f
};

static Motion_Table_Infomeation _motion_info_0x00370340[3] = {
    { 0.0f,  0.0f, 0.0f },
    { 0.05f, 0.5f, 0.89999998f },
    { 0.4f,  0.5f, 0.1f }
};

static u_int Object_Initialize(HH_Object_Water_20* pThis, ImpactQueue_Element* pElement) {
    u_int result = 0;
    float* src_direction;
    float resist_xz, resist_y0, resist_ya;
    pThis->Timer = 0.0f;
    
    pThis->Vertex_Kind = rand() & 1;
    src_direction = pElement->Option.Vector[1];
    
   
    resist_xz = resist_y0 = resist_ya = 0.5494505f;
    pThis->Verocity_0[0] = src_direction[0] * resist_xz;
    pThis->Verocity_0[1] = src_direction[1] * resist_y0;
    pThis->Verocity_0[2] = src_direction[2] * resist_ya;
    
    pThis->Verocity_0[3] = 4038.4612f;
        
    return result;
}

static void ParabolaMotion_Calculator(HH_Object_Water_20* pThis, ImpactQueue_Element* pElement, float Time, float* Position) {
    sceVu0FMATRIX time_mat;

    sceVu0UnitMatrix(time_mat);
    time_mat[0][0] = Time;
    time_mat[1][1] = Time;
    time_mat[2][2] = Time;
    time_mat[3][1] = Time * Time;
    time_mat[3][3] = 0.0f;
    sceVu0ApplyMatrix(Position, time_mat, pThis->Verocity_0);   
}

u_int Object_Motion_00(HH_Object_Water_20* pThis, ImpactQueue_Element* pElement) {
    u_int result = 0; 
    u_int kind;
    float Rgba_s;
    float Rgba_e;
    float Scale_s;
    float Scale_e;
    float local_time_start;
    float local_time_end;
    float local_scale_start;
    float local_scale_end;
    float local_rgba_start; 
    float local_rgba_end; 
    Motion_Table_Infomeation* pMotion_Info;
    u_int i;
    u_int current_step;
    float local_diff_time_current;
    float local_diff_time_max;
    float local_diff_time_ratio;
    float scale_ratio; 
    float rgba_ratio;

    // not present in DWARF
    u_int motion_num; 

    kind = pElement->Option.Int_Value[0];
    Rgba_s = _rgba_start_list_0x00370320[kind];
    Rgba_e = _rgba_end_list_0x00370328[kind];
    Scale_s = _scale_start_list_0x00370330[kind];
    Scale_e = _scale_end_list_0x00370338[kind];
    
    local_time_start = 0.0f;
    
    
    local_scale_start = 0.0f;
    
    
    local_rgba_start = 0.0f;
    
    
    pMotion_Info = _motion_info_0x00370340;

    current_step = pThis->Motion_Step;
    motion_num = 2;
    
    if (motion_num < current_step) {
        current_step = motion_num;
    }    
    for(i = 0; i < current_step + 1; i++) {
        local_time_start += pMotion_Info[i].diff_time;
        local_scale_start+= pMotion_Info[i].diff_scale_ratio;
        local_rgba_start+= pMotion_Info[i].diff_rgba_ratio;
    }
    local_time_end = local_time_start + pMotion_Info[i].diff_time;
    local_scale_end = local_scale_start + pMotion_Info[i].diff_scale_ratio;
    local_rgba_end = local_rgba_start + pMotion_Info[i].diff_rgba_ratio;
    
    
    switch(pThis->Motion_Step) {
        case 0:
            if (pThis->Timer > local_time_end) {
                pThis->Motion_Step++;
            }
            break;
        case 1:
            if(pThis->Timer > local_time_end) {
                pThis->Motion_Step++;
            }
            break;
        case 2:
            if(pThis->Timer > local_time_end) {
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

u_int Object_Draw(HH_Object_Water_20* pThis, ImpactQueue_Element* pElement, float* Current_Position) {
    u_int result = 0;
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();
    Vertex_Infomeation_List* pInfo;
    sceVu0FVECTOR *pVertex = _vertex_info_list_0x00370310->pVertex_List;
    sceVu0FVECTOR *pStq = _square_0x_stq_list_0x00370300[pThis->Vertex_Kind];
    sceVu0FMATRIX lwm;
    sceVu0FMATRIX lsm;
    sceVu0FMATRIX clip_mat;
    sceVu0IVECTOR xyzf;
    sceVu0IVECTOR rgba;
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
    sceVu0FVECTOR Base_Rgba = { 240.0f, 255.0f, 230.0f, pThis->Alpha };
    static float add_a_86 = 12.0f; 
    sceVu0FVECTOR Rgba; sceVu0FVECTOR view_dir;
    sceVu0FVECTOR pos; sceVu0FVECTOR dir;
    sceVu0FVECTOR light_color; sceVu0FVECTOR parameter;
    float color_scale = 0.0f;

    
    HH_ClassWrapper_ViewDirection_Get(view_dir);
    
    HH_ClassWrapper_SpotLight_EnvironmentParameter_Get(pos, dir, light_color,parameter);
    
    if (HH_ClassWrapper_SpotLight_Enable_Check() != 0) {
    
        color_scale = HH_ClassWrapper_SpotLight_ColorRatio_Calculator(pos, dir, lwm[3], parameter[0], parameter[2]);
        color_scale = HH_ClassWrapper_Float_Clamp(color_scale, 0.0f, 1.0f);
    }
    sceVu0CopyVector(Rgba, Base_Rgba);
    Rgba[3] *= color_scale;
    Rgba[3] += add_a_86;
    
        
    sceVu0ClampVector(Rgba, Rgba, 0.0f, 255.0f);
    sceVu0FTOI0Vector(rgba, Rgba);
    }
    
    
    
    
    
    
    
    
    
    
    
    HH_Vif1PacketBuffer_GifTag_Open();
    
    HH_Vif1Packet_GeneralGifTag_Sprite_Open();
    ((u_long128 *)pPk->pCurrent)[0] = *(u_long128 *)(&rgba);
    
    HH_ClassWrapper_Transform_PerspectiveProjection_Clip_N(xyzf, stq_dummy, lsm, clip_mat, pVertex[0], 0x3F);
    ((u_long128 *)pPk->pCurrent)[1] = *(u_long128 *)(&pStq[0]);
    xyzf[2] += 0xA0;
    ((u_long128 *)pPk->pCurrent)[2] = *(u_long128 *)(&xyzf);
    
    HH_ClassWrapper_Transform_PerspectiveProjection_Clip_N(xyzf, stq_dummy, lsm, clip_mat, pVertex[3], 0x3F);
    ((u_long128 *)pPk->pCurrent)[3] = *(u_long128 *)(&pStq[3]);
    xyzf[2] += 0xA0;
    ((u_long128 *)pPk->pCurrent)[4] = *(u_long128 *)(&xyzf);
    pPk->pCurrent += 0x14;
    sceVif1PkCloseGifTag(pPk);
    
    HH_Vif1PacketBuffer_GifTag_Close();
    
    return result;
}


u_int HH_Class_Prefix_Water_20(void) {
    u_long tex0; sceVif1Packet* pPk; u_int result = 1;
    pPk = HH_Vif1Packet_Current_Get();
    
    HH_Vif1PacketBuffer_GifTag_Open();
    
    tex0 = HH_Effect_Object_Texture_GS_Register_Tex0_Get(0,0);
    sceVif1PkAddGsAD(pPk, SCE_GS_TEX0_1, tex0);
    sceVif1PkAddGsAD(pPk, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP(3, 3, 0xFF, 0x100, 0xFF, 0));   
    sceVif1PkAddGsAD(pPk, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(0, 2, 0, 1, 0x80));
    sceVif1PkCloseGifTag(pPk);
    HH_Vif1PacketBuffer_GifTag_Close(); 
    
    return result;
}

u_int HH_Class_Suffix_Water_20(void) {
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();
    u_int result = 1;

    HH_Vif1PacketBuffer_GifTag_Open();
    HH_Vif1Packet_GeneralGifTag_GS_AD_Open();
    sceVif1PkAddGsAD(pPk, 8, 5);
    HH_Vif1PacketBuffer_GifTag_Close();
    return result;
}

u_int HH_Class_Water_20(void* pBlock, ImpactQueue_Element* pElement)
{
    u_int result = 1;
    struct HH_Object_Water_20* pThis = pBlock; 
    sceVu0FVECTOR position;

    switch (pThis->Step) {
        case 0:
            Object_Initialize(pThis, pElement);
            pThis->Step++;
            break;
        
        case 1:
            ParabolaMotion_Calculator(pThis, pElement, pThis->Timer, position);
            Object_Motion_00(pThis, pElement);
            if (pThis->Alpha <= 0.0f) {
                pThis->Alpha = 0.0f;
                pThis->Step = 3;
            }
            if ((position[1] + pElement->Option.Vector[0][1]) > pElement->Option.Float_Value[0]) {
                pThis->Step = 3;
            }
            Object_Draw(pThis, pElement, position);
            pThis->Timer += (TIME_STEP_60FPS);
            break;
        
        default:
        case 3:
            pThis->Header.Enable = 0;
            result = 0;
            break;
    }
    return result;
}

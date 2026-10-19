#include "Effect2/hh_class_blood_05.h"
#include "Effect2/hh_packet.h"
#include "Effect2/hh_class_wrapper.h"
#include "Effect2/hh_effect_object_def.h"
#include "Effect2/hh_effect_object_texture.h"
#include "Effect2/hh_object_vertex_info.h"
#include "Chacter/character.h"
#include "sce/libvifpk.h"

static u_int Object_Initialize(HH_Object_Blood_05* pThis, ImpactQueue_Element* pElement);
static void ParabolaMotion_Calculator(HH_Object_Blood_05* pThis, ImpactQueue_Element* pElement, float Time, float* Position);
static u_int Object_Motion_00(HH_Object_Blood_05* pThis, ImpactQueue_Element* pElement);
static u_int Object_Draw(HH_Object_Blood_05* pThis, ImpactQueue_Element* pElement, float* Current_Position);

static float _suppress_coff_0x0037D1D0 = 2.0f; // size: 0x4, address: 0x37D1D0

static sceVu0FMATRIX _square_00_vertex_0x0037D1E0 = { // size: 0x40, address: 0x37D1E0
    { -25.0f, -25.0f, 0.0f, 1.0f },
    { -25.0f,  25.0f, 0.0f, 1.0f },
    {  25.0f, -25.0f, 0.0f, 1.0f },
    {  25.0f,  25.0f, 0.0f, 1.0f }
};

static sceVu0FMATRIX _square_00_normal_0x0037D220 = { // size: 0x40, address: 0x37D220
    { 0.0f, 0.0f, -1.0f, 1.0f },
    { 0.0f, 0.0f, -1.0f, 1.0f },
    { 0.0f, 0.0f, -1.0f, 1.0f },
    { 0.0f, 0.0f, -1.0f, 1.0f }
};

static sceVu0FMATRIX _square_00_stq_0x0037D260 = { // size: 0x40, address: 0x37D260
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.5f, 1.0f, 0.0f },
    { 0.5f, 0.0f, 1.0f, 0.0f },
    { 0.5f, 0.5f, 1.0f, 0.0f }
};

static sceVu0FMATRIX _square_01_stq_0x0037D2A0 = { // size: 0x40, address: 0x37D2A0
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.5f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.5f, 1.0f, 0.0f },
    { 0.5f, 0.5f, 1.0f, 0.0f }
};

static sceVu0FMATRIX _square_02_stq_0x0037D2E0 = { // size: 0x40, address: 0x37D2E0
    { 0.5f, 0.5f, 1.0f, 0.0f },
    { 0.5f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.5f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f }
};

static sceVu0FMATRIX _square_03_stq_0x0037D320 = { // size: 0x40, address: 0x37D320
    { 0.5f, 0.5f, 1.0f, 0.0f },
    { 0.0f, 0.5f, 1.0f, 0.0f },
    { 0.5f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f }
};

static sceVu0FMATRIX _square_10_stq_0x0037D360 = { // size: 0x40, address: 0x37D360
    { 0.5f, 0.0f, 1.0f, 0.0f },
    { 0.5f, 0.5f, 1.0f, 0.0f },
    { 1.0f, 0.0f, 1.0f, 0.0f },
    { 1.0f, 0.5f, 1.0f, 0.0f }
};

static sceVu0FMATRIX _square_11_stq_0x0037D3A0 = { // size: 0x40, address: 0x37D3A0
    { 0.5f, 0.0f, 1.0f, 0.0f },
    { 1.0f, 0.0f, 1.0f, 0.0f },
    { 0.5f, 0.5f, 1.0f, 0.0f },
    { 1.0f, 0.5f, 1.0f, 0.0f }
};

static sceVu0FMATRIX _square_12_stq_0x0037D3E0 = { // size: 0x40, address: 0x37D3E0
    { 1.0f, 0.5f, 1.0f, 0.0f },
    { 1.0f, 0.0f, 1.0f, 0.0f },
    { 0.5f, 0.5f, 1.0f, 0.0f },
    { 0.5f, 0.0f, 1.0f, 0.0f }
};

static sceVu0FMATRIX _square_13_stq_0x0037D420 = { // size: 0x40, address: 0x37D420
    { 1.0f, 0.5f, 1.0f, 0.0f },
    { 0.5f, 0.5f, 1.0f, 0.0f },
    { 1.0f, 0.0f, 1.0f, 0.0f },
    { 0.5f, 0.0f, 1.0f, 0.0f }
};

static Vertex_Infomeation_List _vertex_info_list_0x0037D460[1] = {
    { _square_00_vertex_0x0037D1E0, _square_00_normal_0x0037D220, 4, 4 }
};

static float (* _stq_list_0x0037D470[8])[4] = {
    _square_00_stq_0x0037D260, _square_01_stq_0x0037D2A0, _square_02_stq_0x0037D2E0, _square_03_stq_0x0037D320,
    _square_10_stq_0x0037D360, _square_11_stq_0x0037D3A0, _square_12_stq_0x0037D3E0, _square_13_stq_0x0037D420
};

static float _rgba_start_list_0x0037D490[2] = { 128.0f, 128.0f };
static float _rgba_end_list_0x0037D498[2] = { 0.0f, 128.0f };
static float _scale_start_list_0x0037D4A0[2] = { 0.8f, 0.8f };
static float _scale_end_list_0x0037D4A8[2] = { 7.0f, 2.0f };

static Motion_Table_Infomeation _motion_info_0_0x0037D4B0[2] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.6f, 1.0f, 1.0f }
};

static Motion_Table_Infomeation _motion_info_1_0x0037D4D0[2] = {
    { 0.0f, 0.0f, 0.0f },
    { 1.0f, 1.0f, 1.0f }
};

static Motion_Table_Infomeation* _motion_info_list_0x0037D4E8[2] = {
    _motion_info_0_0x0037D4B0,
    _motion_info_1_0x0037D4D0
};

static u_int Object_Initialize(HH_Object_Blood_05* pThis, ImpactQueue_Element* pElement) {
    u_int result = 0;
    float* src_direction; 
    float resist_xz, resist_y0 ,resist_ya;  
    pThis->Timer = 0.0f;

    
    resist_ya = 0.5494505f;
    src_direction = pElement->Option.Vector[1];

    pThis->Verocity_0[0] = src_direction[0] * resist_ya;   
    
    resist_y0 = 1.098901f;
    pThis->Verocity_0[1] = src_direction[1] * resist_y0;
      
    resist_xz = 0.5494505f;
    pThis->Verocity_0[2] = src_direction[2] * resist_xz;
    
    pThis->Verocity_0[3] = 2450.0f * _suppress_coff_0x0037D1D0 * resist_y0;
    pElement->Option.Int_Value[1] = rand() & 7;
    
    return result;
}

static void ParabolaMotion_Calculator(HH_Object_Blood_05* pThis, ImpactQueue_Element* pElement, float Time, float* Position) {
    sceVu0FMATRIX time_mat;

    sceVu0UnitMatrix(time_mat);
    time_mat[0][0] = Time;
    time_mat[1][1] = Time;
    time_mat[2][2] = Time;
    time_mat[3][1] = Time * Time;
    time_mat[3][3] = 0.0f;
    sceVu0ApplyMatrix(Position, time_mat, pThis->Verocity_0);
}

static u_int Object_Motion_00(HH_Object_Blood_05* pThis, ImpactQueue_Element* pElement) {
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
    u_int motion_num; 
    u_int i;
    u_int current_step;
    float local_diff_time_current; 
    float local_diff_time_max; 
    float local_diff_time_ratio;
    float scale_ratio;
    float rgba_ratio;
   
    Rgba_s = _rgba_start_list_0x0037D490[pElement->Option.Int_Value[0]];
    Rgba_e = _rgba_end_list_0x0037D498[pElement->Option.Int_Value[0]];
    Scale_s = _scale_start_list_0x0037D4A0[pElement->Option.Int_Value[0]];
    Scale_e = _scale_end_list_0x0037D4A8[pElement->Option.Int_Value[0]];
    
    local_time_start = 0.0f;
    local_scale_start = 0.0f;
    local_rgba_start = 0.0f;
    
    pMotion_Info = _motion_info_list_0x0037D4E8[pElement->Option.Int_Value[0]];
    kind = pThis->Motion_Step;
    
    current_step = pThis->Motion_Step;
    
    motion_num = 1;
    
    if (motion_num < current_step) {
        current_step = motion_num;
    }

    for (i = 0; i < current_step + 1; i++) {
        local_time_start += pMotion_Info[i].diff_time;
        local_scale_start += pMotion_Info[i].diff_scale_ratio;
        local_rgba_start += pMotion_Info[i].diff_rgba_ratio;
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
    }

    local_diff_time_max = (pThis->Timer - local_time_start);
    local_diff_time_current = (local_time_end - local_time_start);
    
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

static u_int Object_Draw(HH_Object_Blood_05* pThis, ImpactQueue_Element* pElement, float* Current_Position) {
    u_int result = 0;
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();
    Vertex_Infomeation_List * pInfo = &_vertex_info_list_0x0037D460[pThis->Vertex_Kind];
    float (* pVertex)[4] = pInfo->pVertex_List;  
    float (* pStq)[4] = _stq_list_0x0037D470[pElement->Option.Int_Value[1]];
    sceVu0FMATRIX lwm; sceVu0FMATRIX lsm;  
    sceVu0FMATRIX clip_mat;  
    sceVu0FVECTOR Base_Rgba = { 40.0f, 255.0f, 230.0f, 0.0f };  
    sceVu0IVECTOR xyzf;
    sceVu0IVECTOR rgba;
    sceVu0FVECTOR stq_dummy;
      
    Base_Rgba[3] = pThis->Alpha;

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
     
    HH_Vif1PacketBuffer_GifTag_Open();
    
    HH_Vif1Packet_GeneralGifTag_Sprite_Open(); 
    sceVu0FTOI0Vector(rgba, Base_Rgba);
    ((u_long128*)pPk->pCurrent)[0] = *(u_long128*)(&rgba);
    
    HH_ClassWrapper_Transform_PerspectiveProjection_Clip_N(xyzf, stq_dummy, lsm, clip_mat, pVertex[0], 0x3F);
    ((u_long128*)pPk->pCurrent)[1] = *(u_long128*)(&pStq[0]);
    xyzf[2] += 0xA0;
    ((u_long128*)pPk->pCurrent)[2] = *(u_long128*)(&xyzf);
    
    HH_ClassWrapper_Transform_PerspectiveProjection_Clip_N(xyzf, stq_dummy, lsm, clip_mat, pVertex[3], 0x3F);
    ((u_long128*)pPk->pCurrent)[3] = *(u_long128*)(&pStq[3]);
    xyzf[2] += 0xA0;
    ((u_long128*)pPk->pCurrent)[4] = *(u_long128*)(&xyzf);
    pPk->pCurrent += 0x14;
    sceVif1PkCloseGifTag(pPk);
    
    HH_Vif1PacketBuffer_GifTag_Close();
    
    return result;
}

u_int HH_Class_Prefix_Blood_05(void) {
    u_long tex0; sceVif1Packet* pPk; u_int result = 1;
    pPk = HH_Vif1Packet_Current_Get();
    
    
    HH_Vif1PacketBuffer_GifTag_Open();
    
    tex0 = HH_Effect_Object_Texture_GS_Register_Tex0_Get(0,0);
    sceVif1PkAddGsAD(pPk, SCE_GS_TEX0_1, tex0);
    
    sceVif1PkAddGsAD(pPk, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(2, 16, 0, 0, 0x80));
    sceVif1PkCloseGifTag(pPk);
    HH_Vif1PacketBuffer_GifTag_Close(); 
    
    return result;
}

u_int HH_Class_Suffix_Blood_05(void) {
    u_int result = 1;
    HH_Vif1Packet_GeneralGifTag_GS_AD_Open();
    return result;
}

u_int HH_Class_Blood_05(void* pBlock, ImpactQueue_Element* pElement) {
    u_int result = 1;
    HH_Object_Blood_05* pThis;
    static sceVu0FVECTOR add_vec_539 = { 0.0f, -100.0f, 0.0f, 0.0f }; // @ 0x0037D500

    pThis = pBlock;

   switch (pThis->Step) {
        case 0:
            Object_Initialize(pThis, pElement);
            
            switch (pElement->Option.Int_Value[0]) { 
                case 0:  
                     pThis->Step = 1;
                    break;
                case 1:
                     pThis->Step = 2;
                    break;
                default:
                     pThis->Step = 3;
                    break;
            }
            break;
        
        case 1:
            {
                sceVu0FVECTOR position;    
                ParabolaMotion_Calculator(pThis, pElement, pThis->Timer, position);                
                Object_Motion_00(pThis, pElement);

                if (pThis->Alpha <= 0.0f) {
                    pThis->Step = 3;
                }
                
                Object_Draw(pThis, pElement, position);
                pThis->Timer += (TIME_STEP_60FPS);
            }
            break;
        
        case 2:
            {                
                sceVu0FVECTOR position;
                CL_VHIT_RESULT hit_result;
                sceVu0FVECTOR e_pos;
                ImpactQueue_Element descriptor;
                
                ParabolaMotion_Calculator(pThis, pElement, pThis->Timer, position);
                Object_Motion_00(pThis, pElement);
                memset(&hit_result, 0, sizeof(hit_result));
                sceVu0AddVector(e_pos, pElement->Option.Vector[0], position);
                e_pos[1] += add_vec_539[1];

                clCheckHitEyesOnlyFloor(&hit_result, 0, pElement->Option.Vector[0], e_pos);
                if (hit_result.kind == 1) {
                    descriptor.hInstance = 0;
                    descriptor.pResultHandle_Address = NULL;
                    sceVu0CopyVector(descriptor.Option.Vector[0], hit_result.hobj.wall.cp);
                    descriptor.Class_Descriptor = 10;
                    HH_Effect_Object_Impact_Post(&descriptor);
                    pThis->Step = 3;
                }
                Object_Draw(pThis, pElement, position);
                pThis->Timer += (TIME_STEP_60FPS);
            }
            break;
            
        default:
        case 3:
            pThis->Header.Enable = 0;
            result = 0;
            break;
    }
    return result;
}

#include "Effect2/hh_class_blood_04.h"
#include "Effect2/hh_packet.h"
#include "Effect2/hh_class_wrapper.h"
#include "Effect2/hh_effect_object_def.h"
#include "Effect2/hh_effect_object_texture.h"
#include "sce/libvifpk.h"

static u_int Object_Initialize(HH_Object_Blood_04* pThis, ImpactQueue_Element* pElement);
static void ParabolaMotion_Calculator(HH_Object_Blood_04* pThis, ImpactQueue_Element* pElement, float Time, float* Position);
static u_int Object_Motion_00(HH_Object_Blood_04* pThis, ImpactQueue_Element* pElement);
static u_int Object_Draw(HH_Object_Blood_04* pThis, ImpactQueue_Element* pElement, float* Current_Position);

static float _visc = 0.000182f; // size: 0x4, address: 0x37B8E0
static float _mass = 0.00000001f; // size: 0x4, address: 0x37B8E8
static float _radius = 0.001f; // size: 0x4, address: 0x37B8F0
static float _suppress_coff_0 = 0.28f; // size: 0x4, address: 0x37B8F8
static float _suppress_coff_1 = 0.05f; // size: 0x4, address: 0x37B900
static float _suppress_coff_xy = 0.4f; // size: 0x4, address: 0x37B908

static sceVu0FMATRIX _square_00_vertex_0x0037B910 = { // size: 0x40, address: 0x37B910
    { -200.0f, -200.0f, 0.0f, 1.0f },
    { -200.0f,  200.0f, 0.0f, 1.0f },
    {  200.0f, -200.0f, 0.0f, 1.0f },
    {  200.0f,  200.0f, 0.0f, 1.0f }
};

static sceVu0FMATRIX _square_00_normal_0x0037B950 = { // size: 0x40, address: 0x37B950
    { 0.0f, 0.0f, -1.0f, 1.0f },
    { 0.0f, 0.0f, -1.0f, 1.0f },
    { 0.0f, 0.0f, -1.0f, 1.0f },
    { 0.0f, 0.0f, -1.0f, 1.0f }
};

static sceVu0FMATRIX _square_00_stq_0x0037B990 = { // size: 0x40, address: 0x37B990
    { 0.5f,        0.5f,        1.0f, 0.0f },
    { 0.5f,        0.74804688f, 1.0f, 0.0f },
    { 0.74804688f, 0.5f,        1.0f, 0.0f },
    { 0.74804688f, 0.74804688f, 1.0f, 0.0f }
};

static sceVu0FMATRIX _square_01_stq_0x0037B9D0 = { // size: 0x40, address: 0x37B9D0
    { 0.75f,       0.5f,        1.0f, 0.0f },
    { 0.75f,       0.74804688f, 1.0f, 0.0f },
    { 0.99804688f, 0.5f,        1.0f, 0.0f },
    { 0.99804688f, 0.74804688f, 1.0f, 0.0f }
};

static sceVu0FMATRIX _square_10_stq_0x0037BA10 = { // size: 0x40, address: 0x37BA10
    { 0.5f,        0.75f,       1.0f, 0.0f },
    { 0.5f,        0.99804688f, 1.0f, 0.0f },
    { 0.74804688f, 0.75f,       1.0f, 0.0f },
    { 0.74804688f, 0.99804688f, 1.0f, 0.0f }
};

static sceVu0FMATRIX _square_11_stq_0x0037BA50 = { // size: 0x40, address: 0x37BA50
    { 0.75f,       0.75f,       1.0f, 0.0f },
    { 0.75f,       0.99804688f, 1.0f, 0.0f },
    { 0.99804688f, 0.75f,       1.0f, 0.0f },
    { 0.99804688f, 0.99804688f, 1.0f, 0.0f }
};

static float (* _square_0x_stq_list_0x0037BA90[4])[4] = { // size: 0x10, address: 0x37BA90
    _square_00_stq_0x0037B990,
    _square_01_stq_0x0037B9D0,
    _square_10_stq_0x0037BA10,
    _square_11_stq_0x0037BA50
};

static Vertex_Infomeation_List _vertex_info_list_0x0037BAA0[1] = { // size: 0x10, address: 0x37BAA0
    { _square_00_vertex_0x0037B910, _square_00_normal_0x0037B950, 4, 4 }
};

static float _rgba_start_list_0x0037BAB0[1] = { 0.0f }; // size: 0x4, address: 0x37BAB0
static float _rgba_end_list_0x0037BAB8[1] = { 120.0f }; // size: 0x4, address: 0x37BAB8
static float _scale_start_list_0x0037BAC0[1] = { 0.1f }; // size: 0x4, address: 0x37BAC0
static float _scale_end_list_0x0037BAC8[1] = { 1.0f }; // size: 0x4, address: 0x37BAC8

static Motion_Table_Infomeation _motion_info_0x0037BAD0[3] = { // size: 0x24, address: 0x37BAD0
    { 0.0f, 0.0f,  0.0f },
    { 3.0f, 0.7f,  1.0f },
    { 5.0f, 0.5f, -1.0f }
};

static u_int Object_Initialize(HH_Object_Blood_04* pThis, ImpactQueue_Element* pElement) {
    u_int result = 0;
    float* src_direction;
    float resist_xz; float resist_y0; float resist_ya;
    pThis->Timer = 0.0f;

    
    pThis->Vertex_Kind = rand() & 3;
    
    
    
    
    
    
        
   
    
    resist_ya = (_mass / (_visc * _radius)); resist_xz = _suppress_coff_xy * resist_ya;
    resist_y0 = _suppress_coff_0 * (3.0f * resist_ya);





    src_direction = pElement->Option.Vector[1];
    pThis->Verocity_0[0] = src_direction[0] * resist_xz;
    pThis->Verocity_0[1] = src_direction[1] * resist_y0;
    pThis->Verocity_0[2] = src_direction[2] * resist_xz;

    pThis->Verocity_0[3] = 2450.0f * _suppress_coff_1 * resist_ya;



    return result;
}

static void ParabolaMotion_Calculator(HH_Object_Blood_04* pThis, ImpactQueue_Element* element, float Time, float* Position) {
    sceVu0FMATRIX time_mat;

    
    sceVu0UnitMatrix(time_mat);
    time_mat[0][0] = Time;
    time_mat[1][1] = Time;
    time_mat[2][2] = Time;
    time_mat[3][1] = Time*Time;
    time_mat[3][3] = 0.0f;
    sceVu0ApplyMatrix(Position, time_mat, pThis->Verocity_0);    
}

static u_int Object_Motion_00(HH_Object_Blood_04* pThis, ImpactQueue_Element* pElement) {
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
    u_int motion_num; // not present in DWARF
    u_int i;    
    u_int current_step;
    float local_diff_time_current;
    float local_diff_time_max;
    float local_diff_time_ratio;  
    float scale_ratio;  
    float rgba_ratio;



    Rgba_s = _rgba_start_list_0x0037BAB0[0];
    Rgba_e = _rgba_end_list_0x0037BAB8[0];
    Scale_s = _scale_start_list_0x0037BAC0[0];
    Scale_e = _scale_end_list_0x0037BAC8[0];
    
    local_time_start = 0.0f;
    
    
    local_scale_start = 0.0f;
    
    
    local_rgba_start = 0.0f;
    
    
    pMotion_Info = _motion_info_0x0037BAD0;
    
    current_step = kind = pThis->Motion_Step;
    motion_num = 2;
    
    if (motion_num < current_step) {
        current_step = motion_num;
    }
    for(i = 0; i < current_step + 1 ; i++) {
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

u_int Object_Draw(HH_Object_Blood_04* pThis, ImpactQueue_Element* pElement, float* Current_Position) {
    u_int result = 0;
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();
    Vertex_Infomeation_List* pInfo = _vertex_info_list_0x0037BAA0;
    float (* pVertex)[4] = pInfo->pVertex_List;
    float (* pStq)[4] = pStq = _square_0x_stq_list_0x0037BA90[pThis->Vertex_Kind];
    sceVu0FMATRIX lwm; sceVu0FMATRIX lsm; sceVu0FMATRIX clip_mat;    
    sceVu0IVECTOR xyzf;
    sceVu0IVECTOR rgba; 
    sceVu0FVECTOR stq_dummy;
    static sceVu0FVECTOR Base_Rgba_84 = {60.0f, 255.0f, 230.0f, 0.0f};

    Base_Rgba_84[3] = pThis->Alpha;
    
    
    
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
    sceVu0FTOI0Vector(rgba, Base_Rgba_84);
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

u_int HH_Class_Prefix_Blood_04(void) {
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

u_int HH_Class_Suffix_Blood_04(void) {
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();
    u_int result = 1;
    
    HH_Vif1PacketBuffer_GifTag_Open();
    HH_Vif1Packet_GeneralGifTag_GS_AD_Open();
    sceVif1PkAddGsAD(pPk, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(0, 1, 0, 1, 0x80));
    HH_Vif1PacketBuffer_GifTag_Close();

    return result;
}

u_int HH_Class_Blood_04(void* pBlock, ImpactQueue_Element* pElement) {
    u_int result = 1;
    HH_Object_Blood_04* pThis = pBlock;

    switch (pThis->Step) {
        case 0:
            Object_Initialize(pThis, pElement);
            pThis->Step++;
            break;
        
        case 1:
            {
                sceVu0FVECTOR position;
    
                ParabolaMotion_Calculator(pThis, pElement, pThis->Timer, position);
                
                Object_Motion_00(pThis, pElement);
                              
                if ((position[1] + pElement->Option.Vector[0][1]) > 0.0f) {
                    pThis->Step = 2;
                    pThis->Step = 3;
                }
                
                Object_Draw(pThis, pElement, &position);
                
                pThis->Timer += (1.0f / 60.0f);
            }
            break;
        
        case 2:
            {                
                sceVu0FVECTOR position;
                ParabolaMotion_Calculator(pThis, pElement, pThis->Timer, position);
                position[1] = -pElement->Option.Vector[0][1];
                Object_Draw(pThis, pElement, &position);
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

#include "hh_class_blood_00.h"
#include "hh_packet.h"
#include "hh_class_wrapper.h"
#include "libvifpk.h"
#include "../Chacter_Draw/sh2gfw_md_spclmapping.h"

extern int rand(void);
extern float fmodf(float, float);

// ToDo Migrate data
static float _square_00_vertex[4][4];
static float _square_01_vertex[4][4];
static float _square_02_vertex[4][4];
static float _square_03_vertex[4][4];
static float _square_04_vertex[4][4];
static float (*_square_vertex_list[5])[4];
static float _square_00_stq[4][4];
static float _rgba_start_list[4][4];
static float _rgba_end_list[4][4];
static float _scale_start_list[5][4];
static float _scale_end_list[8][4];
static Motion_Table_Infomeation _motion_info[4];

static u_int Object_Initialize(HH_Object_Blood_00* pThis) {
    float radian;
    u_int result = 1; 
    float var_f12;

    pThis->Vertex_Kind = rand() % 5U;
    pThis->Scale_Kind = rand() % 5U;
    pThis->Rgba_Kind = rand() % 4U;
    pThis->Timer = 0.0f;
    pThis->Motion_Step = 0;
    var_f12 = TO_RAD(1) * (rand() % 360);

    if(var_f12 > 0.0f){
        radian = fmodf(var_f12, PI*2);
        if(radian > PI){
            radian -= PI*2;
        }
    }
    else{
        radian = fmodf(var_f12, -PI*2);
        if(radian < -PI){
            radian += PI*2;
        }
    }
    pThis->Rotate_Y = radian;

    return result;
}

static u_int Object_Motion_00(HH_Object_Blood_00* pThis) {
    u_int result = 0;
    float* pRgba_s;
    float* pRgba_e;
    float* pScale_s;
    float* pScale_e;
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

    pRgba_s = _rgba_start_list[pThis->Rgba_Kind];
    pRgba_e = _rgba_end_list[pThis->Rgba_Kind];
    pScale_s = _scale_start_list[pThis->Scale_Kind];
    pScale_e = _scale_end_list[pThis->Scale_Kind];
    
    local_time_start = 0.0f;
    local_scale_start = 0.0f;
    local_rgba_start = 0.0f;
    pMotion_Info = _motion_info;
    current_step = pThis->Motion_Step;
    motion_num = 2;
    
    if(motion_num < current_step){
        current_step = motion_num;
    }

    for(i = 0; i < current_step+1 ;i++){
        local_time_start += pMotion_Info[i].diff_time;
        local_scale_start+= pMotion_Info[i].diff_scale_ratio;
        local_rgba_start+= pMotion_Info[i].diff_rgba_ratio;
    }
    
    local_time_end = local_time_start + pMotion_Info[i].diff_time;
    local_scale_end = local_scale_start + pMotion_Info[i].diff_scale_ratio;
    local_rgba_end = local_rgba_start + pMotion_Info[i].diff_rgba_ratio;
    
    switch(pThis->Motion_Step){
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

    if(local_diff_time_ratio > 1.0f){
        local_diff_time_ratio = 1.0f;
    }

    scale_ratio = local_scale_start + (local_diff_time_ratio * (local_scale_end - local_scale_start));
    rgba_ratio = local_rgba_start + (local_diff_time_ratio * (local_rgba_end - local_rgba_start));
    
    sceVu0InterVectorXYZ(pThis->Scale, pScale_e , pScale_s, scale_ratio);
    sceVu0InterVectorXYZ(pThis->Rgba, pRgba_e , pRgba_s, rgba_ratio);
    
    return result;
}


static u_int Object_Draw(HH_Object_Blood_00* pThis, ImpactQueue_Element* pElement) {
    sceVu0FMATRIX lwm;
    sceVu0FMATRIX lsm;
    sceVu0FMATRIX clip_mat;
    float Rgba[4];
    int rgba[4];
    sceVu0FVECTOR stq;
    sceVu0IVECTOR xyzf;
    float ratio;
    u_int result = 0;
    sceVif1Packet* pPk;
    float (*pVertex)[4];
    float (*pStq)[4];
    u_int i; 
    float* vertex; 
    
    pPk = HH_Vif1Packet_Current_Get();
    pVertex = _square_vertex_list[pThis->Vertex_Kind];
    pStq = _square_00_stq;
    HH_ClassWrapper_WorldScreenMatrix_Get(lsm);    
    sceVu0UnitMatrix(lwm);
    lwm[0][0] *= pThis->Scale[0];
    lwm[2][2] *= pThis->Scale[2];
    sceVu0TransMatrix(lwm, lwm, pElement->Option.Vector[0]);
    sceVu0MulMatrix(lsm, lsm, lwm);
    HH_ClassWrapper_ViewFrustum_Primitive_ClipMatrix_Get(clip_mat);
    sceVu0MulMatrix(clip_mat, clip_mat, lwm);
    HH_Vif1Packet_GeneralGifTag_TriangleStrip_Open();

    for(i = 0; i < 4; i++){
        sceVu0CopyVector(stq, pStq[i]);
        vertex = pVertex[i];
        HH_ClassWrapper_Transform_PerspectiveProjection_Clip_forTriangleStrip(xyzf, stq, lsm, clip_mat, vertex);

        if(i == 0){
            ratio = HH_ClassWrapper_FogParameter_A_Get() + (stq[2] * HH_ClassWrapper_FogParameter_B_Get()) ;
            sceVu0ScaleVector(Rgba, pThis->Rgba, HH_ClassWrapper_Float_Clamp(ratio, 0.0f, 255.0f)/ 255.0f);
            sceVu0FTOI0Vector(rgba, Rgba);
        }
        xyzf[2] += 0xA0;
        
        ((u_long128 *)pPk->pCurrent)[0] = *(u_long128 *)(&stq);
        ((u_long128 *)pPk->pCurrent)[1] = *(u_long128 *)(&rgba);
        ((u_long128 *)pPk->pCurrent)[2] = *(u_long128 *)(&xyzf);
 
        pPk->pCurrent += 0xC;
    }

    sceVif1PkCloseGifTag(pPk);
    HH_Vif1PacketBuffer_GifTag_Close();
    
    return result;
}

u_int HH_Class_Prefix_Blood_00() {
    u_long tex0; 
    struct sceVif1Packet* pPk;
    u_int result = 1;

    pPk = HH_Vif1Packet_Current_Get();
    HH_Vif1PacketBuffer_GifTag_Open();
    
    tex0 = sh2_SpecularMappingTEX0();
    sceVif1PkAddGsAD(pPk, SCE_GS_TEX0_1, tex0);
    sceVif1PkAddGsAD(pPk, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(2, 16, 0, 0, 0x80));
    sceVif1PkCloseGifTag(pPk);
    HH_Vif1PacketBuffer_GifTag_Close();
    
    return result;
}

u_int HH_Class_Suffix_Blood_00() {
    u_int result = 1;

    HH_Vif1Packet_GeneralGifTag_GS_AD_Open();
    
    return result;
}
u_int HH_Class_Blood_00(void* pBlock, ImpactQueue_Element* pElement) {
    u_int result = 1;
    HH_Object_Blood_00 * pThis = pBlock;

    switch(pThis->Step){
        case 0:
            Object_Initialize(pThis);
            pThis->Step = 1;
            break;
        case 1:
            Object_Motion_00(pThis);
            Object_Draw(pThis, pElement);
            pThis->Timer += 1.0/30.0;
            
            if(pThis->Timer > 30.0f){
                pThis->Step = 2;
            }
            break;
        case 2:
            Object_Draw(pThis, pElement);
            pThis->Rgba[3] -= 1.0f;

            if(pThis->Rgba[3] <= 0.0f){
                pThis->Rgba[3] = 0.0f;
                pThis->Step = 3;
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


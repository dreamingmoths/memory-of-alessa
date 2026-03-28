#include "hh_class_blood_02.h"
#include "hh_packet.h"
#include "hh_class_wrapper.h"
#include "libvifpk.h"
#include "../Chacter_Draw/sh2gfw_md_spclmapping.h"

static u_int Object_Initialize(HH_Object_Blood_02* pThis, ImpactQueue_Element* pElement);
static u_int Object_Motion_00(HH_Object_Blood_02* pThis);
static u_int Object_Draw(struct HH_Object_Blood_02 * pThis , struct ImpactQueue_Element * pElement);

extern int rand(void);
extern float fmodf(float, float);

// ToDo Migrate data
static shAttackInfo sh2_attack_list[66];
static sceVu0FMATRIX _square_00_vertex;
static sceVu0FMATRIX _square_00_stq;
static sceVu0FVECTOR _circle_00_vertex[10];
static sceVu0FVECTOR _circle_00_stq[10];
static sceVu0FVECTOR _circle_01_vertex[10];
static sceVu0FVECTOR _circle_02_vertex[10];
static Vertex_Infomeation_List _vertex_info_list[4];
static float _rgba_start_list[4][4];
static float _rgba_end_list[4][4];
static float _scale_start_list[5][4];
static float _scale_end_list[5][4];
static Motion_Table_Infomeation _motion_info[4];

static u_int Object_Initialize(HH_Object_Blood_02* pThis, ImpactQueue_Element* pElement){
    float radian;
    u_int result = 1;
    float var_f12;

    if(pElement->Option.Int_Value[1] == 0){
        pThis->Vertex_Kind = rand() % 4U;
        pThis->Scale_Kind = rand() % 5U;
        pThis->Rgba_Kind = rand() % 4U;
        pThis->Timer = 0.0f;
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
    }
    
    pThis->Motion_Step = 0;

    return result;
}

static u_int Object_Motion_00(HH_Object_Blood_02* pThis) {
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
    
    if(2 < current_step){
        current_step = 2;
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

static u_int Object_Draw(struct HH_Object_Blood_02* pThis, struct ImpactQueue_Element* pElement){
    u_int result = 0;
    sceVif1Packet* pPk;
    Vertex_Infomeation_List* pInfo;
    float* vertex;
    float (* pVertex)[4];
    float (* pStq)[4];
    u_int vertex_num;
    u_int i;
    sceVu0FMATRIX lwm;
    sceVu0FMATRIX lsm;
    sceVu0FMATRIX clip_mat;
    sceVu0FVECTOR Rgba;
    sceVu0FVECTOR stq;
    sceVu0IVECTOR xyzf;
    sceVu0IVECTOR rgba;
    float ratio;
    
    pPk = HH_Vif1Packet_Current_Get();
    
    pInfo = &_vertex_info_list[pThis->Vertex_Kind];
    pVertex = pInfo->pVertex_List;
    pStq = pInfo->pStq_List;
    vertex_num = pInfo->Vertex_Max;
    
    HH_ClassWrapper_WorldScreenMatrix_Get(lsm);    
    sceVu0UnitMatrix(lwm);
    lwm[0][0] *= pThis->Scale[0];
    lwm[2][2] *= pThis->Scale[2];
    sceVu0RotMatrixY(lwm, lwm, pThis->Rotate_Y);
    sceVu0TransMatrix(lwm, lwm, pElement->Option.Vector[0]);
    sceVu0MulMatrix(lsm, lsm, lwm);
    HH_ClassWrapper_ViewFrustum_Primitive_ClipMatrix_Get(clip_mat);
    sceVu0MulMatrix(clip_mat, clip_mat, lwm);
    HH_Vif1PacketBuffer_GifTag_Open();
    
    switch(pInfo->Primitive_Type){
        case 4:
            HH_Vif1Packet_GeneralGifTag_TriangleStrip_Open();
            break;
        case 5:
            HH_Vif1Packet_GeneralGifTag_TriangleFan_Open();
            break;
    }

    for(i = 0; i < vertex_num; i++){
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

u_int HH_Class_Prefix_Blood_02(){
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

u_int HH_Class_Suffix_Blood_02(){
    u_int result = 1;

    HH_Vif1Packet_GeneralGifTag_GS_AD_Open();
    
    return result;
}

u_int HH_Class_Blood_02(void* pBlock, ImpactQueue_Element* pElement){
    u_int result = 1;
    HH_Object_Blood_02* pThis = pBlock;

    switch(pThis->Step){
        case 0:
            Object_Initialize(pThis, pElement);
            pThis->Step = 1;
            break;
        case 1:
            Object_Motion_00(pThis);
            Object_Draw(pThis, pElement);
            pThis->Timer += 1.0/30.0;
            break;
        default:
        case 2:
            pThis->Header.Enable = 0;
            result = 0;
            break;
    }
    
    return result;
}

u_int HH_Class_Blood_02_DesignateLocation_CollisionCheck(void* pBlock, ImpactQueue_Element* pElement, float* Target_Location){
    u_int result = 0;
    HH_Object_Blood_02* pThis = pBlock;
    Vertex_Infomeation_List* pInfo;
    float (* pVertex)[4];
    u_int vertex_num;
    float max;
    float min;
    float volume;
    u_int i;
    float vertex[4];
    float target_dir[4];
    float target_volume;
    float inner;

    pInfo = &_vertex_info_list[pThis->Vertex_Kind];
    pVertex = pInfo->pVertex_List;
    vertex_num = pInfo->Vertex_Max;
    
    for(i = 1; i < vertex_num; i++){
        sceVu0MulVector(vertex, pThis->Scale, pVertex[i]);
        inner = sceVu0InnerProduct(vertex, vertex);

        if(i == 1){
            min = inner;
            max = inner;
        }
        if(inner < min){
            min = inner;
        }
        if(inner > max){
            max = inner;
        }
    
    }

    sceVu0SubVector(target_dir, Target_Location, pElement->Option.Vector[0]);

    if(sceVu0InnerProduct(target_dir, target_dir) < (min *= 0.95f)){
        result = 1;
    }
    
    return result;
}

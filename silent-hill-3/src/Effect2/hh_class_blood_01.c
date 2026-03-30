#include "hh_class_blood_01.h"
#include "hh_packet.h"
#include "hh_class_wrapper.h"
#include "hh_effect_object_def.h"
#include "hh_effect_object_texture.h"
#include "libvifpk.h"

extern int rand(void);

static u_int Object_Initialize(HH_Object_Blood_01* pThis, ImpactQueue_Element* pElement );
static void ParabolaMotion_Calculator(HH_Object_Blood_01* pThis, ImpactQueue_Element* element, float Time, float* Position);
static u_int Object_Motion_00(HH_Object_Blood_01* pThis, ImpactQueue_Element* pElement);
static u_int Object_Draw(HH_Object_Blood_01* pThis, ImpactQueue_Element* pElement, float* Current_Position);

/* static symbols */
extern float _mass;
extern float _radius;
extern float _suppress_coff;
extern float _square_00_vertex[4][4];
extern float _square_00_normal[4][4];
extern float _square_00_stq[4][4];
extern float _square_01_stq[4][4];
extern float _square_02_stq[4][4];
extern float _square_03_stq[4][4];
extern float _square_10_stq[4][4];
extern float _square_11_stq[4][4];
extern float _square_12_stq[4][4]; 
extern float _square_13_stq[4][4];
extern Vertex_Infomeation_List _vertex_info_list[1];
extern float (* _stq_list[8])[4];
extern float _rgba_start_list[2];
extern float _rgba_end_list[2];
extern float _scale_start_list[2];
extern float _scale_end_list[2];
extern Motion_Table_Infomeation _motion_info_0[2];
extern Motion_Table_Infomeation _motion_info_1[2];
extern Motion_Table_Infomeation * _motion_info_list[2];

static u_int Object_Initialize(HH_Object_Blood_01* pThis, ImpactQueue_Element* pElement ) {
    u_int result = 0;
    float * src_direction;
    float resist_xz;
    float resist_y0;
    float resist_ya;
 
    pThis->Timer = 0.0f;
    
    resist_ya = 0.5494505f;
    src_direction = pElement->Option.Vector[1];
    
    pThis->Verocity_0[0] = src_direction[0] * resist_ya;
     
    resist_y0 = 1.098901f;
    pThis->Verocity_0[1] = src_direction[1] * resist_y0;
    
    resist_ya = 0.5494505f;
    pThis->Verocity_0[2] = src_direction[2] * resist_ya;

    resist_xz = 2450.0f *  _suppress_coff;
    pThis->Verocity_0[3] = resist_xz * resist_y0;
    
    pElement->Option.Int_Value[1] = rand() % 8U;
    
    return result;
}

static void ParabolaMotion_Calculator(HH_Object_Blood_01* pThis, ImpactQueue_Element* element, float Time, float* Position) {
    sceVu0FMATRIX time_mat;

    sceVu0UnitMatrix(time_mat);
    time_mat[0][0] = Time;
    time_mat[1][1] = Time;
    time_mat[2][2] = Time;
    time_mat[3][1] = Time*Time;
    time_mat[3][3] = 0.0f;
    sceVu0ApplyMatrix(Position, time_mat, pThis->Verocity_0);
}


static u_int Object_Motion_00(HH_Object_Blood_01* pThis, ImpactQueue_Element* pElement) {
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

    kind = pElement->Option.Int_Value[0];
    
    Rgba_s = _rgba_start_list[kind];
    Rgba_e = _rgba_end_list[kind];
    Scale_s = _scale_start_list[kind];
    Scale_e = _scale_end_list[kind];
    
    local_time_start = 0.0f;
    local_scale_start = 0.0f;
    local_rgba_start = 0.0f;
    
    pMotion_Info = _motion_info_list[kind];
    
    current_step = pThis->Motion_Step;
    motion_num = 1;
    
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
    }

    local_diff_time_max = (pThis->Timer - local_time_start);
    local_diff_time_current = (local_time_end-local_time_start);
    
    local_diff_time_ratio = local_diff_time_max / local_diff_time_current;

    if(local_diff_time_ratio > 1.0f){
        local_diff_time_ratio = 1.0f;
    }

    scale_ratio = local_scale_start + (local_diff_time_ratio * (local_scale_end - local_scale_start));
    rgba_ratio =  local_rgba_start + (local_diff_time_ratio * (local_rgba_end - local_rgba_start));

    pThis->Scale = Scale_e*scale_ratio + Scale_s * (1.0f - scale_ratio);
    pThis->Alpha = Rgba_e*rgba_ratio + Rgba_s * (1.0f - rgba_ratio);
    
    return result;
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_blood_01", Object_Draw);

static void func_00210C50() {
    return;
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_blood_01", HH_Class_Prefix_Blood_01);

u_int HH_Class_Suffix_Blood_01() {
    return 1;
}

u_int HH_Class_Blood_01(void* pBlock, ImpactQueue_Element* pElement) {
    u_int result = 1;
    HH_Object_Blood_01 * pThis = pBlock;

    switch(pThis->Step){
        case 0:
            Object_Initialize(pThis, pElement);
            switch(pElement->Option.Int_Value[0]){
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

                if(pThis->Alpha <= 0.0f){
                    pThis->Step = 3;
                }

                Object_Draw(pThis, pElement, position);
                pThis->Timer += 1.0/60.0;
            }
            break;
        case 2:
            {
                sceVu0FVECTOR position;
                ImpactQueue_Element descriptor;

                ParabolaMotion_Calculator(pThis, pElement, pThis->Timer, position);
                Object_Motion_00(pThis, pElement);

                if((position[1] + pElement->Option.Vector[0][1]) > 0.0f){ 
                    descriptor.hInstance = 0;
                    descriptor.pResultHandle_Address = NULL;
                    sceVu0AddVector(descriptor.Option.Vector[0], pElement->Option.Vector[0], position);
                    descriptor.Option.Vector[0][1] = 0;
                    descriptor.Class_Descriptor = 7;
                    HH_Effect_Object_Impact_Post(&descriptor);
                    pThis->Step = 3;
                }

                Object_Draw(pThis, pElement, position);
                pThis->Timer += 1.0/60.0;
            }
            break;
            break;
        default:
        case 3:
            pThis->Header.Enable = 0;
            result = 0;
            break;
    }

    return result;
}

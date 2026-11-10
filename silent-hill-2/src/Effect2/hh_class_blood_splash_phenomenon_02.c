#include "sh2_common.h"

#include "math.h"

#include "Chacter/character.h"

#include "Effect2/hh_math_wrapper.h"
#include "Effect2/hh_effect_object_def.h"
#include "Effect2/hh_class_blood_splash_phenomenon_02.h"

#pragma divbyzerocheck off

static u_int Object_Initialize(HH_Object_Blood_Splash_Phenomenon_02* pThis, ImpactQueue_Element* pElement);
static void Impact_Parameter_Calculator(HH_Object_Blood_Splash_Phenomenon_02* pThis, float* src_location, float* src_direction, u_int Kind);

UNMIGRATED(/* static */ sceVu0FVECTOR _unit_vector_x_0x0037D510);
UNMIGRATED(/* static */ sceVu0FVECTOR _unit_vector_z_0x0037D520);
UNMIGRATED(/* static */ float _discharge_full_number_0x0037D530[2]);
UNMIGRATED(/* static */ float _discharge_time_0x0037D538[2]);

#line 159
static u_int Object_Initialize(HH_Object_Blood_Splash_Phenomenon_02* pThis, ImpactQueue_Element* pElement) {
    u_int result = true; // r2
    float p_y, p_volume; // r29+0x60, r29+0x60
    float* src_direction; // r16

    pThis->Timer = 0.0f;
    
    pThis->Next_Discharge_Time[0] = 0.0f;
    pThis->Next_Discharge_Time[1] = 0.0f;
    
    pThis->Post_Count[0] = 0;
    pThis->Post_Count[1] = 0;
    
    
    
    src_direction = pElement->Option.Vector[1];

    
    p_volume = sceVu0InnerProduct(src_direction, src_direction);
    
    p_volume = HH_MathWrapper_Sqrtf(p_volume);
    
    
    pThis->Verocity_0 = p_volume;

    p_y = src_direction[1];
    
    pThis->Beta = asinf(p_y / p_volume);
    
    
    pThis->Alpha = TO_RAD(10) + 4.0f * pThis->Beta;
    if (pThis->Alpha < 0.0f) {
        pThis->Alpha = -pThis->Alpha;
    }
    
    
    pThis->Gamma = 0.95f * pThis->Beta;
    
    
    pThis->Delta = TO_RAD(22.5f);

    {
        sceVu0FVECTOR p_xz;
        float lambda_1; // r20
        float lambda_2; // r29+0x60
        SubCharacter* pSubChar; // r2
        
        sceVu0CopyVector(p_xz, src_direction);
        p_xz[1] = 0;
        sceVu0Normalize(p_xz, p_xz);
        lambda_1 = sceVu0InnerProduct(p_xz, _unit_vector_z_0x0037D520);
        lambda_2 = sceVu0InnerProduct(p_xz, _unit_vector_x_0x0037D510);
        
        
        
        
        pThis->Lambda = lambda_1;
        if (lambda_2 < QUARTER_TURN) {
            pThis->Lambda = -pThis->Lambda;
        }
        
        
        
        
        // @info: almost same as phenomenon_00, but it stashes these two differences:
        pSubChar = (SubCharacter*) pElement->Option.Int_Value[0];
        
        pElement->Option.Float_Value[0] = pSubChar->pos.y - pSubChar->center_y;
        pElement->Option.Float_Value[1] = pSubChar->pos.y - pElement->Option.Vector[0][1];
    }
    
    return result;
}

static inline float toImpactAngleRange(float x) { return x * 57.295776f; }

#line 244
static void Impact_Parameter_Calculator(HH_Object_Blood_Splash_Phenomenon_02* pThis, float* src_location, float* src_direction, u_int Kind) {
    ImpactQueue_Element descriptor; // r29+0xA0
    u_int phai_range = toImpactAngleRange(pThis->Alpha); // r16
    u_int theta_range = toImpactAngleRange(2.0f * pThis->Delta); // r17
    float v0_range = pThis->Verocity_0; // r20
    float v0_plus = rand() % (u_int) v0_range; // r29+0x120
    float ratio = pThis->Verocity_0 * sinf(pThis->Beta); // r20
    float phai = 0.0f; // r29+0x120
    float theta = 0.0f; // r21
    float* dst_location = descriptor.Option.Vector[0]; // r23
    float* dst_direction = descriptor.Option.Vector[1]; // r18
    sceVu0FMATRIX mat; // r29+0xE0
    if (phai_range != 0.0f)
        phai = TO_RAD(rand() % phai_range) - pThis->Alpha * 0.5f; // r21
    
    if (theta_range != 0.0f)
        theta = TO_RAD(rand() % theta_range) - pThis->Delta; // r22
    


    if (ratio < 0.0f) {
        ratio *= -1.0f;
    }
    
    
    sceVu0CopyVector(descriptor.Option.Vector[0], src_location);

    #line 275
    sceVu0UnitMatrix(mat);
    theta = shReflexAngle(theta);
    phai = shReflexAngle(phai);
    sceVu0RotMatrixX(mat, mat, theta);
    sceVu0RotMatrixY(mat, mat, phai);
    sceVu0CopyVector(&dst_direction[0], src_direction);
    dst_direction[0] += ratio;
    dst_direction[2] += ratio;
    {
        float vx0_range = dst_direction[0]; // r29+0x120
        float vx0_plus = 0.0f; // r21
        float vz0_range = dst_direction[2]; // r20
        float vz0_plus = 0.0f; // r22
        if (vx0_range != 0.0f) {
            if (dst_direction[0] < 0.0f) 
                vx0_range = -vx0_range;
            
            vx0_plus = (rand() % (u_int) vx0_range) - vx0_range * 0.5f;
        }
        if (vz0_range != 0.0f) {
            if (dst_direction[2] < 0.0f) 
                vz0_range = -vz0_range;
            vz0_plus = (rand() % (u_int) vz0_range) - vz0_range * 0.5f;
        }
        
        dst_direction[0] += vx0_plus;
        dst_direction[2] += vz0_plus;
        
        sceVu0ApplyMatrix(dst_direction, mat, dst_direction);
    }
        
    descriptor.Option.Int_Value[0] = Kind;
    descriptor.hInstance = 0;
    descriptor.pResultHandle_Address = NULL;
    descriptor.Class_Descriptor = 15;
    HH_Effect_Object_Impact_Post(&descriptor);
    pThis->Post_Count[Kind]++;
    pThis->Next_Discharge_Time[Kind] += _discharge_time_0x0037D538[Kind];
}

#line 332
u_int HH_Class_Blood_Splash_Phenomenon_02(void* pBlock, ImpactQueue_Element* pElement) {
    #line 339
    u_int result = true; // r23
    HH_Object_Blood_Splash_Phenomenon_02* pThis = pBlock; // r17

    
    switch (pThis->Step) {
        case HH_EFFECT_STEP_INIT:
            Object_Initialize(pThis, pElement);
            pThis->Step++;
            break;

        case HH_EFFECT_STEP_DRAW: {
            u_int j; // r18
            SubCharacter* pSubChar; // r16
            sceVu0FVECTOR def_vec; // r29+0xA0
            float y_ratio; // r29+0xD0
            float current_h; // r20
            pSubChar = (SubCharacter*) pElement->Option.Int_Value[0];

            y_ratio = 0.0f;
            current_h = pSubChar->pos.y - pSubChar->center_y;
            
            if (pElement->Option.Float_Value[0] != 0.0f) {   
                y_ratio = current_h / pElement->Option.Float_Value[0];
                if (y_ratio < 0.0f)
                    y_ratio *= -1.0f;
            }

            sceVu0SubVector(def_vec, (float*) &pSubChar->pos, (float*) &pSubChar->b_pos);
            sceVu0AddVector(pElement->Option.Vector[0], pElement->Option.Vector[0], def_vec);
            
            pElement->Option.Float_Value[1] *= y_ratio;
            pElement->Option.Vector[0][1] = pSubChar->pos.y - pElement->Option.Float_Value[1];
            
            
            pElement->Option.Float_Value[0] = current_h;
            
            
            for (j = 0; j < 2; j++) {
                if (pThis->Timer > pThis->Next_Discharge_Time[j]) {
                    float diff_time = pThis->Timer - pThis->Next_Discharge_Time[j]; // r29+0xD0
                    float count = diff_time / _discharge_time_0x0037D538[j]; // r29+0xD0
                    u_int count_i = count; // r19
                    u_int i; // r16
                    u_int max = 1; // r20
                    u_int free = (u_int) _discharge_full_number_0x0037D530[j] - pThis->Post_Count[j]; // r16
                    sceVu0FVECTOR src_location; // r29+0xB0
                    sceVu0FVECTOR src_direction; // r29+0xC0
                    sceVu0CopyVector(src_location,  pElement->Option.Vector[0]);
                    sceVu0CopyVector(src_direction, pElement->Option.Vector[1]);
                    
                    if (j == 1) {
                        src_direction[0] = 0.0f;
                        src_direction[1] = -500.0f;
                        src_direction[2] = 0.0f;
                    }
                    
                    if (free != 0) {
                        if (free == 0) {
                            max = free;
                        } else if (1 < count_i) {
                            max *= count_i;
                        }

                        for (i = 0; i < max; i++) {
                            Impact_Parameter_Calculator(pThis, src_location, src_direction, j);
                        }
                    }
                }
            }

            if (pThis->Timer > 0.5f) {
                pThis->Step = HH_EFFECT_STEP_OFF;
            }
            break;
        }

        default:
        case HH_EFFECT_STEP_OFF:
            pThis->Header.Enable = false;
            result = false;
            break;
    }

    pThis->Timer += TIME_STEP_60FPS;

    return result;
}

#include "sh2_common.h"
#include "math.h"
#include "Effect2/hh_math_wrapper.h"
#include "Effect2/hh_class_glass_break_phenomenon_00.h"

static sceVu0FVECTOR _unit_vector_x = { 1.0f, 0.0f, 0.0f, 1.0f };
static sceVu0FVECTOR _unit_vector_z = { 0.0f, 0.0f, 1.0f, 1.0f };

static u_int Object_Initialize(HH_Object_Glass_Break_Phenomenon_00* pThis, ImpactQueue_Element* pElement);

#line 126
static u_int Object_Initialize(HH_Object_Glass_Break_Phenomenon_00* pThis, ImpactQueue_Element* pElement) {
    u_int result = true;
    float p_y, p_volume;
    float* src_direction;
    
    pThis->Timer = 0.0f;
    
    pThis->Next_Discharge_Time = 0.0f;
    
    pThis->Post_Count = 0;
    
    
    
    src_direction = pElement->Option.Vector[1];
    
    
    p_volume = sceVu0InnerProduct(src_direction, src_direction);
    
    p_volume = HH_MathWrapper_Sqrtf(p_volume);
    
    pThis->Verocity_0 = p_volume;
    
    p_y = src_direction[1];
    #line 159
    pThis->Beta = asinf(p_y / p_volume);
    

    
    pThis->Alpha = 4.0f * pThis->Beta;
    if (pThis->Alpha < 0.0f)
        pThis->Alpha = -pThis->Alpha;

    
    
    
    pThis->Gamma = 0.95f * pThis->Beta;
    
    
    
    pThis->Delta = TO_RAD(22.5f);

    {
        sceVu0FVECTOR p_xz;
        float lambda_1;
        float lambda_2;
        
    
        
        sceVu0CopyVector(p_xz, src_direction);
        p_xz[1] = 0;
        sceVu0Normalize(p_xz, p_xz);
        lambda_1 = sceVu0InnerProduct(p_xz, &_unit_vector_z);
        lambda_2 = sceVu0InnerProduct(p_xz, &_unit_vector_x);
        
        
        
        
        
        pThis->Lambda = lambda_1;
        if (lambda_2 < QUARTER_TURN) {
            pThis->Lambda = -pThis->Lambda;
        }
    }


    
    
    
    return result;
}

#ifdef NON_MATCHING
static inline float toImpactAngleRange(float x) { return x * 57.295776f; }

#pragma divbyzerocheck off

u_int HH_Class_Glass_Break_Phenomenon_00(void* pBlock, ImpactQueue_Element* pElement) {
    u_int result;
    HH_Object_Glass_Break_Phenomenon_00* pThis;
    
    
    
    
    result = true;
    pThis = pBlock;
    
    switch (pThis->Step) {
        case 0:
            Object_Initialize(pThis, pElement);
            pThis->Step++;
            break;
        
        case 1:
            if (pThis->Timer > pThis->Next_Discharge_Time) {
                float diff_time = pThis->Timer - pThis->Next_Discharge_Time;
                float count = diff_time / 0.006f;
                u_int count_i = count;
                u_int i;
                u_int max = 1;
                u_int free = 50 - pThis->Post_Count;
                
                if (free == 0) {
                    max = free;
                } 
                
                else if (count_i > 1) {    
                    max *= count_i;
                }
                
                for (i = 0; i < max; i++) {
                    ImpactQueue_Element descriptor;
                    u_int phai_range = toImpactAngleRange(pThis->Alpha);
                    u_int theta_range = toImpactAngleRange(2.0f * pThis->Delta);
                    float v0_range = pThis->Verocity_0;
                    float v0_plus = rand() % (u_int) v0_range;
                    float ratio = 0.3f * (pThis->Verocity_0 * sinf(pThis->Beta));
                    float phai = 0.0f;
                    float theta = 0.0f;
                    float* src_location = pElement->Option.Vector[0];
                    float* src_direction = pElement->Option.Vector[1];

                    float* dst_direction = descriptor.Option.Vector[1];
                    sceVu0FMATRIX mat;
                    if (phai_range != 0.0f) {
                         phai = TO_RAD(rand() % phai_range) - pThis->Alpha * 0.5f;
                    }
                    if (theta_range != 0.0f) {
                        theta = TO_RAD(rand() % theta_range) - pThis->Delta;
                    }
                    
                    
                    if (ratio < 0.0f) {
                        ratio *= -1.0f;
                    }

                    
                    sceVu0CopyVector(descriptor.Option.Vector[0], src_location);
                    
                    
                    
                    
                    
                    
                    sceVu0UnitMatrix(mat);

                    theta = shReflexAngle(theta);
                    phai = shReflexAngle(phai);
                    sceVu0RotMatrixX(mat, mat, theta);
                    sceVu0RotMatrixY(mat, mat, phai);
                    sceVu0CopyVector(dst_direction, src_direction);
                    dst_direction[0] += ratio;
                    dst_direction[2] += ratio;
                    {
                        float vx0_range = dst_direction[0];
                        float vx0_plus = 0.0f;
                        float vz0_range = dst_direction[2];
                        float vz0_plus = 0.0f;
                        if (vx0_range != 0.0f) {
                            if (dst_direction[0] < 0.0f) {
                                vx0_range = -vx0_range;
                            }
                            vx0_plus = (rand() % (u_int) vx0_range) - vx0_range * 0.5f;
                        }
                        if (vz0_range != 0.0f) {
                            if (dst_direction[2] < 0.0f) {
                                vz0_range = -vz0_range;
                            }
                            vz0_plus = (rand() % (u_int) vz0_range) - vz0_range * 0.5f;
                        }
                        dst_direction[0] += vx0_plus;
                        dst_direction[2] += vz0_plus;
                        
                        sceVu0ApplyMatrix(dst_direction, mat, dst_direction);
                    }
                    
                    descriptor.hInstance = 0;
                    descriptor.pResultHandle_Address = NULL;
                    descriptor.Class_Descriptor = 21;
                    HH_Effect_Object_Impact_Post(&descriptor);
                    pThis->Post_Count++;
                    pThis->Next_Discharge_Time += 0.006f;
                }
            }
            if (pThis->Timer > 0.3f) {
                pThis->Step++;
            }
            break;
        
        case 2: default:
            pThis->Header.Enable = false;
            result = false;
            printf("Object Discard!! %8.4f\n", pThis->Timer);
            break;
    }
    pThis->Timer += TIME_STEP_30FPS;
    return result;
}

#pragma divbyzerocheck on
#else
INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_glass_break_phenomenon_00", HH_Class_Glass_Break_Phenomenon_00);
RODATA_PAD_TO(0x39A150);
INCLUDE_RODATA("asm/nonmatchings/Effect2/hh_class_glass_break_phenomenon_00", @113_0x0039A150);
#endif

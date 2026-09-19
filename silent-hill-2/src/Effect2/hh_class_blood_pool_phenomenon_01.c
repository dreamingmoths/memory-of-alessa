#include "Effect2/hh_class_blood_pool_phenomenon_01.h"
#include "Effect2/hh_effect_object_def.h"
#include "Effect2/hh_math_wrapper.h"
#include "sce/libvu0.h"

static u_int Object_Initialize(HH_Object_Blood_Pool_Phenomenon_01* pThis, ImpactQueue_Element* pElement);

static u_int Object_Initialize(HH_Object_Blood_Pool_Phenomenon_01* pThis, ImpactQueue_Element* pElement) {
    u_int result = 1;
    float p_y, p_volume, alpha;
    float* src_direction;
    
    pThis->Timer = 0.0f;
    
    
    
    
    
    
    src_direction = pElement->Option.Vector[1];
    

    p_volume = sceVu0InnerProduct(src_direction, src_direction);
    
    p_volume = HH_MathWrapper_Sqrtf(p_volume);
    p_y = src_direction[1];
    alpha = asinf(p_y / p_volume);
    
    if (alpha < 0.0f) {
        alpha = -alpha;
    }
    
    pThis->Alpha = 0.5f * alpha;
    
    
    return result;
}

u_int HH_Class_Blood_Pool_Phenomenon_01(void* pBlock, ImpactQueue_Element* pElement) {
    u_int result = 1;
    HH_Object_Blood_Pool_Phenomenon_01* pThis = pBlock;
    u_int i;
    float* src_direction;
    float p_volume, radian, alpha_randam_range, radius_rand, alpha;
    sceVu0FMATRIX lwm;
    ImpactQueue_Element descriptor;

    
    switch (pThis->Step) {
        case 0:
            Object_Initialize(pThis, pElement);
            pThis->Step = 1;
            break;

        
        
        
        case 1:
            src_direction = pElement->Option.Vector[1];

            p_volume = sceVu0InnerProduct(src_direction, src_direction);
        
            
            p_volume = HH_MathWrapper_Sqrtf(p_volume);


            for (i = 0; i < 6; i++) {
                alpha = TO_RAD(rand() % 360);

                if (alpha > 0.0f) {
                    radian = fmodf(alpha, TAU);

                    if (radian > PI) {
                        radian -= TAU;
                    }
                } else {
                    radian = fmodf(alpha, -TAU);

                    if (radian < -PI) {
                        radian += TAU;
                    }
                }

                alpha_randam_range = (0.017453292f * (rand() % 10)) - 0.08726646f;
                radius_rand = 10.0f + (rand() % 50);

                alpha = pThis->Alpha + alpha_randam_range;

                if (alpha > 0.0f) {
                    alpha_randam_range = fmodf(alpha, TAU);

                    if (alpha_randam_range > PI) {
                        alpha_randam_range -= TAU;
                    }
                } else {
                    alpha_randam_range = fmodf(alpha, -TAU);

                    if (alpha_randam_range < -PI) {
                        alpha_randam_range += TAU;
                    }
                }

                {
                    sceVu0FVECTOR vec = { 0.0f, 0.0f, 0.0f, 1.0f };

                    vec[2] = radius_rand;

                    sceVu0UnitMatrix(lwm);
                    sceVu0RotMatrixY(lwm, lwm, radian);
                    sceVu0TransMatrix(lwm, lwm, pElement->Option.Vector[0]);
                    sceVu0ApplyMatrix(descriptor.Option.Vector[0], lwm, vec);
                }

                {
                    sceVu0FVECTOR vec = { 0.0f, 0.0f, 0.0f, 1.0f };

                    vec[2] = p_volume;

                    if (alpha_randam_range > 0.0f) {
                        alpha_randam_range = fmodf(alpha_randam_range, TAU);

                        if (alpha_randam_range > PI) {
                            alpha_randam_range -= TAU;
                        }
                    } else {
                        alpha_randam_range = fmodf(alpha_randam_range, -TAU);

                        if (alpha_randam_range < -PI) {
                            alpha_randam_range += TAU;
                        }
                    }

                    sceVu0UnitMatrix(lwm);
                    sceVu0RotMatrixX(lwm, lwm, alpha_randam_range);
                    sceVu0RotMatrixY(lwm, lwm, radian);
                    sceVu0ApplyMatrix(descriptor.Option.Vector[1], lwm, vec);
                }

                descriptor.hInstance = 0;
                descriptor.pResultHandle_Address = NULL;
                descriptor.Class_Descriptor = 14;

                HH_Effect_Object_Impact_Post(&descriptor);


            }

            pThis->Step = 2;
            break;

        default:
        case 2:
            pThis->Header.Enable = 0;
            result = 0;
            break;
    }

    pThis->Timer += 1.0 / 30.0;

    return result;
}

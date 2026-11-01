#include "sh2_common.h"

#include "Effect2/hh_math_wrapper.h"
#include "Effect2/hh_effect_object_def.h"
#include "Effect2/hh_class_blood_splash_phenomenon_01.h"

static u_int Object_Initialize(HH_Object_Blood_Splash_Phenomenon_01* pThis, ImpactQueue_Element* pElement);

#line 117
static u_int Object_Initialize(HH_Object_Blood_Splash_Phenomenon_01* pThis, ImpactQueue_Element* pElement) {
    u_int result = true; // r2

    #line 122    
    pThis->Timer = 0.0f;
    
    {
        float p_y, p_volume; // r29+0x30, r29+0x30
        float alpha; // r29+0x30
        float* src_direction;

        src_direction = pElement->Option.Vector[1]; // r16
        
        #line 132
        p_volume = sceVu0InnerProduct(src_direction, src_direction);
        p_volume = HH_MathWrapper_Sqrtf(p_volume);
        
        p_y = src_direction[1];
        alpha = asinf(p_y / p_volume);
        
        if (alpha < 0.0f)
            alpha = -alpha;
    
    
        pThis->Alpha = 0.5f * alpha;
    }
    
    return result;
}

#line 165
u_int HH_Class_Blood_Splash_Phenomenon_01(void* pBlock, ImpactQueue_Element* pElement) {    
    #line 172
    u_int result = true; // r16
    HH_Object_Blood_Splash_Phenomenon_01* pThis = pBlock; // r17

    switch (pThis->Step) {
        case HH_EFFECT_STEP_INIT:
            Object_Initialize(pThis, pElement);
            pThis->Step = HH_EFFECT_STEP_DRAW;
            break;


        
        case HH_EFFECT_STEP_DRAW: {
            u_int i; // r18
            float* src_direction = pElement->Option.Vector[1]; // r2
            float* src_location; // r2
            float p_volume = sceVu0InnerProduct(src_direction, src_direction); // r20
            
            
            p_volume = HH_MathWrapper_Sqrtf(p_volume);
            
            
            for (i = 0; i < 6; i++) {
                float radian = shReflexAngle(TO_RAD(rand() % 360)); // r29+0x100
                float alpha_randam_range = TO_RAD(rand() % 10) - TO_RAD(5); // r22
                float radius_rand = 10.0f + (rand() % 30); // r23
                float alpha = shReflexAngle(pThis->Alpha + alpha_randam_range); // r29+0x100
                sceVu0FMATRIX lwm; // r29+0x60
                ImpactQueue_Element descriptor; // r29+0xA0

                
                {    
                    sceVu0FVECTOR vec = {0.0f, 0.0f, 0.0f, 1.0f};
                    
                    vec[2] = radius_rand;
                    sceVu0UnitMatrix(lwm);
                    sceVu0RotMatrixY(lwm, lwm, radian);
                    sceVu0TransMatrix(lwm, lwm, pElement->Option.Vector[0]);
                    sceVu0ApplyMatrix(descriptor.Option.Vector[0], lwm, vec);
                }
                {
                    sceVu0FVECTOR vec = {0.0f, 0.0f, 0.0f, 1.0f};
                    
                    vec[2] = p_volume;
                    alpha = shReflexAngle(alpha); // @bug this isn't necessary as it was already done above.
                    sceVu0UnitMatrix(lwm);
                    sceVu0RotMatrixX(lwm, lwm, alpha);
                    sceVu0RotMatrixY(lwm, lwm, radian);
                    sceVu0ApplyMatrix(&descriptor.Option.Vector[1][0], lwm, vec);
                }
                descriptor.hInstance = 0;
                descriptor.pResultHandle_Address = NULL;
                descriptor.Class_Descriptor = 13;
                HH_Effect_Object_Impact_Post(&descriptor);
            }

            pThis->Step = HH_EFFECT_STEP_OFF;
            break;
        }
        
        default:
        case HH_EFFECT_STEP_OFF:
            pThis->Header.Enable = false;
            result = false;
            break;
    }

    pThis->Timer += TIME_STEP_30FPS;

    return result;
}


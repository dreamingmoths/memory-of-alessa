#include "sh2_common.h"
#include "sdk.h"
#include "math.h"
#include "Effect2/hh_effect_object_def.h"
#include "Effect2/hh_math_wrapper.h"
#include "Effect2/hh_class_raise_dust_phenomenon_00.h"


static u_int Object_Initialize(HH_Object_Raise_Dust_Phenomenon_00* pThis, ImpactQueue_Element* pElement);


#line 118
static u_int Object_Initialize(HH_Object_Raise_Dust_Phenomenon_00* pThis, ImpactQueue_Element* pElement) {
    u_int result = true;
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

    pThis->Alpha = alpha * 0.5f;


    return result;
}

#line 166
u_int HH_Class_Raise_Dust_Phenomenon_00(void* pBlock, ImpactQueue_Element* pElement) {
    u_int result;
    HH_Object_Raise_Dust_Phenomenon_00* pThis;
    u_int i;
    float* src_direction, *src_location;
    float p_volume;
    
    result = true;
    pThis = pBlock;

    switch (pThis->Step) {
        case HH_EFFECT_STEP_INIT:
            Object_Initialize(pThis, pElement);
            pThis->Step = 1;
            break;
        
        
        
        
        case HH_EFFECT_STEP_DRAW:
            src_direction = pElement->Option.Vector[1];
            
            p_volume = sceVu0InnerProduct(src_direction, src_direction);
            
            
            p_volume = HH_MathWrapper_Sqrtf(p_volume);
            
            
            for (i = 0; i < 3; i++) {
                float radian = shReflexAngle(TO_RAD(rand() % 360));
                float alpha_randam_range = TO_RAD(rand() % 10) - TO_RAD(5);
                float radius_rand = 10.0f + (rand() % 50);
                float alpha = shReflexAngle(pThis->Alpha + alpha_randam_range);
                sceVu0FMATRIX lwm;
                ImpactQueue_Element descriptor;
            
                
                {
                    sceVu0FVECTOR vec = { 0.0f, 0.0f, 0.0f, 1.0f };
                    src_location  = pElement->Option.Vector[0];
                    vec[2] = radius_rand;
                    sceVu0UnitMatrix(lwm);
                    sceVu0RotMatrixY(lwm, lwm, radian);
                    sceVu0TransMatrix(lwm, lwm, src_location);
                    sceVu0ApplyMatrix(descriptor.Option.Vector[0], lwm, vec);
                }                
                {
                    sceVu0FVECTOR vec = { 0.0f, 0.0f, 0.0f, 1.0f };
                    
                    vec[2] = p_volume;
                    alpha = shReflexAngle(alpha); // @bug this isn't necessary as it was already done above.
                    sceVu0UnitMatrix(lwm);
                    sceVu0RotMatrixX(lwm, lwm, alpha);
                    sceVu0RotMatrixY(lwm, lwm, radian);
                    sceVu0ApplyMatrix(descriptor.Option.Vector[1], lwm, vec);
                }
                descriptor.hInstance = 0;
                descriptor.pResultHandle_Address = NULL;
                descriptor.Class_Descriptor = 17;
                HH_Effect_Object_Impact_Post(&descriptor);
            }
            
            pThis->Step = HH_EFFECT_STEP_OFF;
            break;
        default:
        case HH_EFFECT_STEP_OFF:
            pThis->Header.Enable = false;
            result = false;
            break;
    }
    pThis->Timer += TIME_STEP_30FPS;
    return result;
}

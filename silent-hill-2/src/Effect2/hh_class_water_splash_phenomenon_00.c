#include "sh2_common.h"
#include "sce/libvu0.h"
#include "Effect2/hh_class_water_common.h"
#include "Effect2/hh_math_wrapper.h"
#include "Effect2/hh_class_water_splash_phenomenon_00.h"

static u_int Object_Initialize(HH_Object_Water_Splash_Phenomenon_00* pThis, ImpactQueue_Element* pElement);

static u_int Object_Initialize(HH_Object_Water_Splash_Phenomenon_00* pThis, ImpactQueue_Element* pElement) {
    u_int result = 1;     // r2
    float p_y, p_volume;  // r29+0x30
    float alpha;          // r29+0x30
    float* src_direction; // r16
    pThis->Timer = 0.0f;

    src_direction = pElement->Option.Vector[1];

    p_volume = sceVu0InnerProduct(src_direction, src_direction);
    p_volume = HH_MathWrapper_Sqrtf(p_volume);
    p_y = src_direction[1];
    alpha = asinf(p_y / p_volume);

    if (alpha < 0.0f)
        alpha = -alpha;

    pThis->Alpha = 0.5f * alpha;

    return result;
}

u_int HH_Class_Water_Splash_Phenomenon_00(void* pBlock, ImpactQueue_Element* pElement) {
    u_int result = 1;                                     // r16
    HH_Object_Water_Splash_Phenomenon_00* pThis = pBlock; // r17
    u_int i;                                              // r18
    float* src_direction;                                 // r2
    float* src_location;                                  // r2
    float p_volume;                                       // r20
    float radian;                                         // r29+0x100
    float alpha_randam_range;                             // r22
    float radius_rand;                                    // r23
    float alpha;                                          // r29+0x100
    sceVu0FMATRIX lwm;                                    // r29+0x60
    ImpactQueue_Element descriptor;                       // r29+0xA0

    switch (pThis->Step) { /* irregular */
        case 0:
            Object_Initialize(pThis, pElement);
            pThis->Step = 1;
            break;
        case 1:
            src_direction = pElement->Option.Vector[1];
            p_volume = sceVu0InnerProduct(src_direction, src_direction);
            p_volume = HH_MathWrapper_Sqrtf(p_volume);
            for (i = 0; i < 6U; i++) {
                radian = reflex_angle(TO_RAD(rand() % 360));
                alpha_randam_range = (TO_RAD(rand() % 10)) - TO_RAD(5);
                radius_rand = 10.0f + (rand() % 30);
                alpha = pThis->Alpha + alpha_randam_range;
                alpha = reflex_angle(alpha);
                {
                    sceVu0FVECTOR vec = {0.0f, 0.0f, radius_rand, 1.0f}; // r29+0xE0
                    sceVu0UnitMatrix(lwm);
                    sceVu0RotMatrixY(lwm, lwm, radian);
                    sceVu0TransMatrix(lwm, lwm, pElement->Option.Vector[0]);
                    sceVu0ApplyMatrix(descriptor.Option.Vector[0], lwm, vec);
                }

                {
                    sceVu0FVECTOR vec = {0.0f, 0.0f, p_volume, 1.0f}; // r29+0xF0
                    alpha = reflex_angle(alpha);
                    sceVu0UnitMatrix(lwm);
                    sceVu0RotMatrixX(lwm, lwm, alpha);
                    sceVu0RotMatrixY(lwm, lwm, radian);
                    sceVu0ApplyMatrix(descriptor.Option.Vector[1], lwm, vec);
                }

                descriptor.hInstance = 0;
                descriptor.pResultHandle_Address = NULL;
                descriptor.Option.Float_Value[0] = pElement->Option.Float_Value[0];
                descriptor.Option.Int_Value[0] = pElement->Option.Int_Value[0];
                descriptor.Class_Descriptor = 0x13;
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

    pThis->Timer += 1.0f / 30.0f;

    return result;
}

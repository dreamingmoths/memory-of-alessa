#include "hh_class_blood_pool_phenomenon_00.h"
#include "hh_effect_object_def.h"

extern int rand(void);
extern float fmodf(float, float);

static u_int Object_Initialize(HH_Object_Blood_Pool_Phenomenon_00* pThis);

static TimeTable_Infomeation _Time_Table[5];

static u_int Object_Initialize(HH_Object_Blood_Pool_Phenomenon_00* pThis) {
    u_int result = 1;

    pThis->Timer = 0.0f;
    pThis->Time_Table_Index = rand() % 5U;
    pThis->Post_Count = 0;

    return result;
}

u_int HH_Class_Blood_Pool_Phenomenon_00(void* pBlock, ImpactQueue_Element* pElement) {
    u_int result = 1;
    HH_Object_Blood_Pool_Phenomenon_00* pThis = pBlock;
    float radian;
    float radius_rand;
    float var_f0;

    switch(pThis->Step){
        case 0:
            Object_Initialize(pThis);
            pThis->Step = 1;
            break;
        case 1:
            if(pThis->Timer > _Time_Table[pThis->Time_Table_Index].Time[pThis->Post_Count]){
                radius_rand = TO_RAD(1) * (rand() % 360);
                
                if(radius_rand > 0.0f){
                    radian = fmodf(radius_rand, PI*2);
                    
                    if(radian > PI){
                        radian -= PI*2;
                    }
                }
                else{
                    radian = fmodf(radius_rand, -PI*2);
                    if(radian < -PI){
                        radian += PI*2;
                    }
                }

                var_f0 = 50.0f + (rand() % 150);
                {
                    sceVu0FVECTOR vec = {0};
                    sceVu0FMATRIX lwm;
                    ImpactQueue_Element descriptor;
                 
                    vec[0] = var_f0;
                    sceVu0UnitMatrix(lwm);
                    sceVu0RotMatrixY(lwm, lwm, radian);
                    sceVu0TransMatrix(lwm, lwm, pElement->Option.Vector[0]);
                    sceVu0ApplyMatrix(descriptor.Option.Vector[0], lwm, vec);
                    descriptor.hInstance = 0;
                    descriptor.pResultHandle_Address = 0;
                    descriptor.Class_Descriptor = 12;
                    descriptor.Option.Int_Value[0] = pElement->Option.Int_Value[0];
                    descriptor.Option.Int_Value[1] = 0;

                    HH_Effect_Object_Impact_Post(&descriptor);
                }
                
                pThis->Post_Count++;

                if(pThis->Post_Count >= 3){
                    pThis->Step++;
                }
            }
            break;
        default:
        case 2:
            pThis->Header.Enable = 0;
            result = 0;
            break;
    }

    pThis->Timer += 1.0/30.0;
    
    return result;
}

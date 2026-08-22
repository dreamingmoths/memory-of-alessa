#include "sh2_common.h"
#include "sce/libvu0.h"
#include "Effect2/hh_class_plural_phenomenon_00.h"
#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_wrapper.h"
#include "Effect2/hh_effect_object_def.h"
#include "Effect2/hh_class_blood_02.h"

static u_int Object_Initialize(HH_Object_Plural_Phenomenon_00* pThis);
static u_int ObjectInstance_BLOOD_STICK_00_Search_and_Post(ImpactQueue_Element* pElement, u_int Count_Max, float Set_Parameter);

#line 100
static u_int Object_Initialize(HH_Object_Plural_Phenomenon_00* pThis /* r2 */) {
    u_int result = true; // r2
    
    pThis->Timer = 0.0f;
    
    return result;
}

#line 119
static u_int ObjectInstance_BLOOD_STICK_00_Search_and_Post(ImpactQueue_Element* pElement /* r21 */, u_int Count_Max /* r20 */, float Set_Parameter /* r20 */) {
    u_int result = false; // r16
    u_int i; // r17
    Object_Group_Infomeation* pInfo = HH_Effect_Object_Infomeation_Get(); // r18
    
    for (i = 0; i < Count_Max; i++) {
        u_int hInstance = ObjectInstanceHandle_Get_from_ClassDescriptor_and_AttachCount(pInfo, HH_CLASS_DESCRIPTOR_PLURAL_PHENOMENON_00, i); // r19
        ImpactQueue_Element* pElement_Stick_00 = ObjectInstance_Element_Get(pInfo, hInstance); // r2
        
        
        if ((pElement->Option.Int_Value[0] == pElement_Stick_00->Option.Int_Value[0]) && (pElement->Option.Int_Value[1] == pElement_Stick_00->Option.Int_Value[1])) {
            ImpactQueue_Element descriptor; // r29+0x80

            descriptor.hInstance = hInstance;
            descriptor.pResultHandle_Address = NULL;
            descriptor.Class_Descriptor = HH_CLASS_DESCRIPTOR_PLURAL_PHENOMENON_00;
            descriptor.Option = pElement->Option;
            
            descriptor.Option.Float_Value[0] = Set_Parameter;
            HH_Effect_Object_Impact_Post(&descriptor);
            result = true;
            break;
        }
    }
    return result;
}

#line 164
u_int HH_Class_Plural_Phenomenon_00(void* pBlock /* r2 */, ImpactQueue_Element* pElement /* r22 */) {
    static sceVu0FVECTOR direction = { // @ 0x0036ED50
        0.0f,
        -2500.0f,
        0.0f,
        1.0f
    };
    u_int result = true; // r30
    HH_Object_Plural_Phenomenon_00* pThis = (HH_Object_Plural_Phenomenon_00*) pBlock; // r23

    switch (pThis->Step) {
        case HH_PLURAL_PHENOMENON_00_STEP_INIT:
            Object_Initialize(pBlock);
            pThis->Step = 1;
            break;
        
        case HH_PLURAL_PHENOMENON_00_STEP_DRAW: {
            sceVu0FVECTOR center_location; // r29+0xC0
            float* src_location = &pElement->Option, src_direction; // r29+0xA0, r2
            Object_Group_Infomeation* pInfo; // r16
            u_int count_stick_00, count_blood_02, i, collision_check; // r29+0xBC, r17, r18, r19
        
            sceVu0AddVector(center_location, src_location, pElement->Option.Vector[1]);
            sceVu0ScaleVectorXYZ(center_location, center_location, 0.5f);






            
            pInfo = HH_Effect_Object_Infomeation_Get();
            count_stick_00 = ObjectInstance_DesignateClassDescriptorAttach_Count(pInfo, 8);
            count_blood_02 = ObjectInstance_DesignateClassDescriptorAttach_Count(pInfo, 12);
            
            collision_check = false;
            
            
            for (i = 0; i < count_blood_02; i++) {
                u_int hInstance = ObjectInstanceHandle_Get_from_ClassDescriptor_and_AttachCount(pInfo, 12, i); // r20
                ImpactQueue_Element* pElement_Blood_02 = ObjectInstance_Element_Get(pInfo, hInstance);
                void* pBlock_Blood_02 = ObjectInstance_DataBlock_Get(pInfo, hInstance);
                
            
                if (HH_Class_Blood_02_DesignateLocation_CollisionCheck(pBlock_Blood_02, pElement_Blood_02, center_location) != 0) {
                    collision_check = true;
                    break;
                }
            }
            
            if (collision_check) {
            
                
                
                if (ObjectInstance_BLOOD_STICK_00_Search_and_Post(pElement, count_stick_00, 5.0f) == 0) {
                    ImpactQueue_Element descriptor; // r29+0xD0
                
                    
                    descriptor.hInstance = 0;
                    descriptor.pResultHandle_Address = NULL;
                    descriptor.Class_Descriptor = HH_CLASS_DESCRIPTOR_PLURAL_PHENOMENON_00;
                    descriptor.Option = pElement->Option;
                    
                    descriptor.Option.Float_Value[0] = 5.0f;
                    HH_Effect_Object_Impact_Post(&descriptor);
                }

                {    
                    ImpactQueue_Element descriptor; // r29+0x110
                    float* dst_location = descriptor.Option.Vector[0];
                    float* dst_direction = descriptor.Option.Vector[1];
                    
                    
                    descriptor.hInstance = 0;
                    descriptor.pResultHandle_Address = NULL;
                    descriptor.Class_Descriptor = 6;
                    sceVu0CopyVector(dst_location, src_location);
                    sceVu0CopyVector(dst_direction, direction);
                    HH_Effect_Object_Impact_Post(&descriptor);
                }
            } else {



                
                ObjectInstance_BLOOD_STICK_00_Search_and_Post(pElement, count_stick_00, -1.0f);
            }


            
            pThis->Step = 2;
            break;
        }
        default: case HH_PLURAL_PHENOMENON_00_STEP_OFF:
            pThis->Header.Enable = 0;
            result = 0;
            break;
    }
    pThis->Timer += 1.0f / 30.0f;
    return result;
}

#include "Effect2/hh_class_blood_stick_00.h"
#include "Effect2/hh_effect_object_def.h"

#include "sce/libvu0.h"

static u_int Object_Initialize(HH_Object_Blood_Stick_00* pThis /* r2 */, ImpactQueue_Element* pElement /* r2 */);
static u_int Object_Monitor(HH_Object_Blood_Stick_00* pThis /* r17 */, ImpactQueue_Element* pElement /* r16 */);
static u_int Object_Manager(HH_Object_Blood_Stick_00* pThis /* r17 */, ImpactQueue_Element* pElement /* r19 */);

static float _unit_vector_x_0x0036E6F0[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; // size: 0x10, address: 0x36E6F0
static float _unit_vector_z_0x0036E700[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; // size: 0x10, address: 0x36E700

static u_int Object_Initialize(HH_Object_Blood_Stick_00* pThis, ImpactQueue_Element* pElement) {
    u_int result = 1; // r2
    pThis->Timer = 0.0f;
    pThis->FootMark_Kind = pElement->Option.Int_Value[0];
    pThis->Character_ID = pElement->Option.Int_Value[1];
    return result;
}

static u_int Object_Monitor(HH_Object_Blood_Stick_00* pThis, ImpactQueue_Element* pElement) {
    u_int result = 0; // r18
    
    if (pElement->Option.Float_Value[0] != 0.0f) {
        
        if (pElement->Option.Float_Value[0] > 0.0f){
            if (pThis->Leftover < 10) {
                pThis->Leftover += (u_char)pElement->Option.Float_Value[0];
            }
        } 
            
        if (pElement->Option.Float_Value[0] < 0.0f) {
            if (pThis->Leftover > 0) {
                pThis->Leftover--;
                result = 1;
            }
        }
        
        pElement->Option.Float_Value[0] = 0.0f;
    }
    return result;
}


static u_int Object_Manager(HH_Object_Blood_Stick_00* pThis, ImpactQueue_Element* pElement) {
    u_int result = 1;
    float center_location[4] , toe_dir[4]; float cos_theta, cos_phai, rot_y; float* toe_location; float* heel_location; ImpactQueue_Element descriptor;  
    switch (pThis->Monitor_Step) {
        case 0:
            
            if (Object_Monitor(pThis, pElement) == 0) break;
                
                pThis->Monitor_Step = 1;
            
            
        
        
        
        
        
        
        
        
        
        
        case 1:
            toe_location = pElement->Option.Vector[0];
            heel_location = pElement->Option.Vector[1];


            sceVu0AddVector(center_location, toe_location, heel_location);
            sceVu0ScaleVectorXYZ(center_location, center_location, 0.5f);
            center_location[3] = 1.0f;

            sceVu0SubVector(toe_dir, toe_location, heel_location);
            sceVu0Normalize(toe_dir, toe_dir);
            cos_theta = sceVu0InnerProduct(toe_dir, _unit_vector_z_0x0036E700);
            cos_phai  = sceVu0InnerProduct(toe_dir, _unit_vector_x_0x0036E6F0);

            rot_y = acosf(cos_theta);
            if (cos_phai < 0.0f) {
                rot_y = -rot_y;
            }


            

            descriptor.hInstance = 0;
            descriptor.pResultHandle_Address = NULL;
            descriptor.Class_Descriptor = 9;
            sceVu0CopyVector(descriptor.Option.Vector[0], center_location);                        
            (rot_y = reflex_angle(rot_y), descriptor.Option.Float_Value[0] = rot_y);
            
            descriptor.Option.Float_Value[1] = 1.0f;
            descriptor.Option.Int_Value[0] = pThis->FootMark_Kind;
            descriptor.Option.Int_Value[1] = pThis->Character_ID;
            HH_Effect_Object_Impact_Post(&descriptor);
            
            
            pThis->Monitor_Step = 0;
            
            break;
        default:
            result = 0;
            break;
    }
    return result;
}

u_int HH_Class_Blood_Stick_00(void* pBlock, ImpactQueue_Element* pElement) {
    u_int result; // r16
    HH_Object_Blood_Stick_00* pThis;// r17




    result = 1;
    pThis = (HH_Object_Blood_Stick_00*)pBlock;
    
    switch (pThis->Step) {
        
        case 0:
            Object_Initialize(pThis, pElement);
            
            pThis->Step = 1;
            break;
        
        case 1:
            Object_Manager(pThis, pElement);
            
            pThis->Timer += 1.0f / 30.0f;
            
            if (pThis->Leftover <= 0) {
                pThis->Step = 2;
            }
            
            if (pThis->Timer > 120.0f) {
                pThis->Step = 2;
            }
            break;
        default:
        case 2:
            pThis->Header.Enable = 0;
            result = 0;
            break;
    }
    return result;
}

#include "sh2_common.h"
#include "SH2_common/sh2sys.h"
#include "math.h"
#include "Event/demoview.h"
#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_fire_phenomenon_00.h"

UNMIGRATED(/*static*/ Descriptor_Post_Infomeation _post_info_demo[23]); // size: 0x730, address: 0x375DE0
UNMIGRATED(/*static*/ Descriptor_Post_Infomeation _post_info_normal[16]); // size: 0x500, address: 0x376510

static inline float shGetDemoFrame(void) {
    return demo_frame;
}


#line 618
static u_int Object_Initialize(HH_Object_Fire_Phenomenon_00* pThis, ImpactQueue_Element* pElement) {
    u_int result = 1;
    u_int i;

    
    pThis->Timer = 0.0f;
    
    
    
    
    
    for (i = 0; i < sizeof(_post_info_demo) / sizeof(_post_info_demo[0]); i++) {
        Descriptor_Post_Infomeation* pInfo = &_post_info_demo[i];
        
        pInfo->Step = 0;
    } 
    for (i = 0; i < sizeof(_post_info_normal) / sizeof(_post_info_normal[0]); i++) {
        Descriptor_Post_Infomeation* pInfo = &_post_info_normal[i];
        
        pInfo->Step = 0;
    }

    
    return result;
}

#line 661
u_int HH_Class_Fire_Phenomenon_00(void* pBlock, ImpactQueue_Element* pElement) {
    
    
    
    
    
    
    
    u_int result = 1;
    HH_Object_Fire_Phenomenon_00* pThis = pBlock;
    u_int i; ImpactQueue_Element descriptor;
    switch (pThis->Step) {
        case 0:
            Object_Initialize(pThis, pElement);
            pThis->Step = 1;
            break;
        case 1:
            
            if (!((Sh2sys.main_status >> 6) & 1)) {
                break;
            }
            pThis->Step = 2;
            
        
        
        
        
        
        case 2:
            descriptor.hInstance = 0.0f;
            descriptor.Option.Int_Value[1] = 0;
            
            
            for (i = 0; i < sizeof(_post_info_demo) / sizeof(_post_info_demo[0]); i++) {
                Descriptor_Post_Infomeation* pInfo = &_post_info_demo[i];
                
                switch (pInfo->Step) {
                   
                    case 0:
                        if (pInfo->Post_Frame <= shGetDemoFrame()) {
                           
                            descriptor.Option.Float_Value[0] = pInfo->Float_Argument[0];
                            descriptor.Option.Float_Value[1] = pInfo->Float_Argument[1];
                            
                            
                            sceVu0CopyVector(descriptor.Option.Vector[0], pInfo->Location);
                            descriptor.Class_Descriptor = pInfo->Class_Descriptor[0];
                            descriptor.pResultHandle_Address = pInfo->hInstance;
                            descriptor.Option.Int_Value[0] = pInfo->Int_Argument[0];
                            HH_Effect_Object_Impact_Post(&descriptor);
                            
                            
                            sceVu0AddVector(descriptor.Option.Vector[0], pInfo->Location, pInfo->Offset);
                            descriptor.Class_Descriptor = pInfo->Class_Descriptor[1];
                            descriptor.pResultHandle_Address = &pInfo->hInstance[1];
                            descriptor.Option.Int_Value[0] = pInfo->Int_Argument[1];
                            HH_Effect_Object_Impact_Post(&descriptor);
                            
                            pInfo->Step = 1;
                        }
                        break;
                    case 1:
                       
                        if (pInfo->Delete_Frame < shGetDemoFrame()) {
                        
                            HH_Effect_Object_DesignateHandleInstance_Clear(pInfo->hInstance[0]);
                            
                            HH_Effect_Object_DesignateHandleInstance_Clear(pInfo->hInstance[1]);
                            pInfo->Step = 2;
                        }
                        break;
                }
            }
            
            
                
            
            if (!((Sh2sys.main_status >> 6) & 1)) {
                
                HH_Effect_Object_DesignateClassInstance_Clear(43);
                HH_Effect_Object_DesignateClassInstance_Clear(44);
                HH_Effect_Object_DesignateClassInstance_Clear(45);
                HH_Effect_Object_DesignateClassInstance_Clear(47);
                
                
                for (i = 0; i < sizeof(_post_info_normal) / sizeof(_post_info_normal[0]); i++) {
                    Descriptor_Post_Infomeation* pInfo = &_post_info_normal[i];
                    
                    switch (pInfo->Step) {
                        case 0:
                        
                            descriptor.Option.Float_Value[0] = pInfo->Float_Argument[0];
                            descriptor.Option.Float_Value[1] = pInfo->Float_Argument[1];
                            
                            
                            sceVu0CopyVector(descriptor.Option.Vector[0], pInfo->Location);
                            descriptor.Class_Descriptor = pInfo->Class_Descriptor[0];
                            descriptor.pResultHandle_Address = pInfo->hInstance;
                            descriptor.Option.Int_Value[0] = pInfo->Int_Argument[0];
                            HH_Effect_Object_Impact_Post(&descriptor);
                            
                            
                            sceVu0AddVector(descriptor.Option.Vector[0], pInfo->Location, pInfo->Offset);
                            descriptor.Class_Descriptor = pInfo->Class_Descriptor[1];
                            descriptor.pResultHandle_Address = &pInfo->hInstance[1];
                            descriptor.Option.Int_Value[0] = pInfo->Int_Argument[1];
                            HH_Effect_Object_Impact_Post(&descriptor);
                            
                            pInfo->Step = 2;
                            break;
                    }

  
                }
                pThis->Step = 3;
            }
            
            
            pThis->Timer += TIME_STEP_30FPS;
            break;
        default:
        case 3:
            pThis->Header.Enable = 0;
            result = 0;
            break;
    }
    return result;
}

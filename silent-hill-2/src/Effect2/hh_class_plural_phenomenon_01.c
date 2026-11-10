#include "sh2_common.h"
#include "math.h"
#include "sce/libvu0.h"
#include "Chacter/character.h"
#include "Effect2/hh_effect_object_def.h"
#include "Effect2/hh_class_plural_phenomenon_01.h"

static u_int Object_Initialize(HH_Object_Plural_Phenomenon_01* pThis);

#line 105
static u_int Object_Initialize(HH_Object_Plural_Phenomenon_01* pThis) {
    u_int result = true;
    
    pThis->Timer = 0.0f;
    
    return result;
}

#line 130
u_int HH_Class_Plural_Phenomenon_01(void* pBlock, ImpactQueue_Element* pElement) {
    u_int result;
    HH_Object_Plural_Phenomenon_01* pThis;
    int room_name;
    float* src_location;
    float* src_direction;
    ImpactQueue_Element descriptor;
    result = true;
    pThis = pBlock;

    switch (pThis->Step) {
        case 0:
            Object_Initialize(pThis);
            pThis->Step = 1;
            break;

        case 1:
            room_name = RoomNameJms();
            src_location = pElement->Option.Vector[0];

            {
                float* dst_location;
                float* dst_direction;
                u_int check0;
                CL_VHIT_RESULT hit_result;
                sceVu0FVECTOR e_pos;
                { // fix scope
                static float direction[4] = { 0.0f, -2500.0f, 0.0f, 1.0f };
                static float add_vec[4] = { 0.0f, 1000.0f, 0.0f, 0.0f };
                #line 176
                dst_location = descriptor.Option.Vector[0];
                dst_direction = descriptor.Option.Vector[1];
                
                check0 = 1;

                switch (room_name) {
                    case 37:
                    case 38:

                        
                        
                        
                        
                        memset(&hit_result, 0, sizeof(hit_result));
                        
                        sceVu0AddVector(e_pos, pElement->Option.Vector[0], add_vec);
                        
                        clCheckHitEyesOnlyFloor(&hit_result, 0, pElement->Option.Vector[0], e_pos);
                        
                        
                        if (hit_result.hobj.wall.pd == NULL) break;
                        
                        if (hit_result.hobj.wall.pd->material != MATERIAL_TYPE_6) {
                            check0 = 0;
                        }

                        
                        break;
                    default:
                        check0 = 0;
                        break;
                }

                if (check0 != 0) {
                    descriptor.hInstance = 0;
                    descriptor.pResultHandle_Address = NULL;
                    descriptor.Class_Descriptor = 18;

                    sceVu0CopyVector(dst_location, src_location);
                    sceVu0CopyVector(dst_direction, direction);
                    
                    descriptor.Option.Float_Value[0] = 0.0f;
                    descriptor.Option.Int_Value[0] = 1;
                    
                    
                    
                    HH_Effect_Object_Impact_Post(&descriptor);
                }} // fix scope
                {
                    ImpactQueue_Element descriptor;
                    float* dst_location, *dst_direction;
                    u_int check0;
                    static float direction[4] = { 0.0f, -2500.0f, 0.0f, 1.0f };
                    dst_location = descriptor.Option.Vector[0];
                    dst_direction = descriptor.Option.Vector[1];


                    check0 = 1;
                    
                    if ((room_name != 38) && 
                        (room_name != 37) && 
                        (room_name != 98)) {


                        
                        check0 = 0;
                    }

                    
                    if (check0 != 0) { static float local_y = 30.0f;
                        descriptor.hInstance = 0;
                        descriptor.pResultHandle_Address = NULL;
                        descriptor.Class_Descriptor = 41;
                    
                        sceVu0CopyVector(dst_location, src_location);
                        sceVu0CopyVector(dst_direction, direction);
                        dst_location[1] = local_y;
                        HH_Effect_Object_Impact_Post(&descriptor);
                        HH_Effect_Object_Impact_Post(&descriptor);
                        HH_Effect_Object_Impact_Post(&descriptor);
                        HH_Effect_Object_Impact_Post(&descriptor);
                    }
                }


                
                {
                    Object_Group_Infomeation* pInfo = HH_Effect_Object_Infomeation_Get();
                    u_int class_descriptor;  
                    u_int check0 = 1;
                    u_int check0_1 = 1;
                    u_int check1 = 1;
                    u_int splash_flag = 0;
                    u_int i;
                    CL_VHIT_RESULT hit_result;
                    switch (room_name) {
                        case 99:

                            class_descriptor = 24;
                            check1 = 0;
                        
                            
                            {
                                sceVu0FVECTOR e_pos;    
                                static float add_vec[4] = { 0.0f, 1000.0f, 0.0f, 0.0f };
                                memset(&hit_result, 0, sizeof(hit_result));
                                
                                sceVu0AddVector(e_pos, pElement->Option.Vector[0], add_vec);
                                
                                clCheckHitEyesOnlyFloor(&hit_result, 0, pElement->Option.Vector[0], e_pos);
    
                                
                                if (hit_result.hobj.wall.pd == NULL) break;
                                
                                if (hit_result.hobj.wall.pd->material != MATERIAL_TYPE_6) {
                                    check0_1 = 0;
                                }
                            }
                            
                            break;
                        case 98:                                   
                            class_descriptor = 25;
                            check1 = 0;
                            splash_flag = 1;
                            break;
                        case 128:                                  
                            class_descriptor = 26;
                            break;
                        case 133:                                  
                            class_descriptor = 27;
                            break;
                        case 122:                                  
                            class_descriptor = 28;
                            break;
                        case 124:                                  
                            class_descriptor = 29;
                            break;
                        case 126:                                  
                            class_descriptor = 30;
                            break;
                        case 130:                                  
                            class_descriptor = 31;
                            break;
                        case 187:                                  
                            class_descriptor = 32;
                            break;
                        case 182:                                  
                            class_descriptor = 33;
                            break;
                        case 183:                                  
                            class_descriptor = 34;
                            break;
                        case 171:                                  
                            class_descriptor = 35;
                            break;
                        case 184:                                  
                            class_descriptor = 36;
                            break;
                        case 185:                                  
                            class_descriptor = 37;
                            break;
                        case 33:                                   
                            class_descriptor = 38;
                            check0_1 = 0;
                            check1 = 0;
                            break;
                        default:                                    
                            check0 = 0;
                            check1 = 0;
                            break;
                    }

                    
                    if (check0 != 0) {
                        int count_water = ObjectInstance_DesignateClassDescriptorAttach_Count(pInfo, class_descriptor);


                        
                        for (i = 0; i < count_water; i++) {
                            ImpactQueue_Element descriptor;
                            u_int hInstance = ObjectInstanceHandle_Get_from_ClassDescriptor_and_AttachCount(pInfo, class_descriptor, i);
                            
                            descriptor.hInstance = hInstance;
                            descriptor.pResultHandle_Address = NULL;
                            descriptor.Class_Descriptor = class_descriptor;
                            sceVu0CopyVector(descriptor.Option.Vector[0], pElement->Option.Vector[0]);
                            descriptor.Option.Int_Value[0] = 1;
                            HH_Effect_Object_Impact_Post(&descriptor);
                        }

                        
                        
                        if (check0_1 != 0) {
                            ImpactQueue_Element descriptor;
                            float* dst_location = descriptor.Option.Vector[0];
                            float* dst_direction = descriptor.Option.Vector[1];
                            static float direction[4] = { 0.0f, -2500.0f, 0.0f, 1.0f };
                            
                            descriptor.hInstance = 0;
                            descriptor.pResultHandle_Address = NULL;
                            descriptor.Class_Descriptor = 18;
                            sceVu0CopyVector(dst_location, src_location);
                            sceVu0CopyVector(dst_direction, direction);
                            dst_location[1] -= 200.0f;
                    
                            descriptor.Option.Float_Value[0] = 0.0f;
                            descriptor.Option.Int_Value[0] = splash_flag;
                            HH_Effect_Object_Impact_Post(&descriptor);
                        }
                    }

                    
                    if (check1 != 0) {
                        ImpactQueue_Element descriptor;
                        float* dst_location;
                        float* dst_direction;
                        static float direction[4] = { 0.0f, -2500.0f, 0.0f, 1.0f };
                        
                        dst_location = descriptor.Option.Vector[0];
                        dst_direction = descriptor.Option.Vector[1];
                        
                        
                        descriptor.hInstance = 0;
                        descriptor.pResultHandle_Address = NULL;
                        descriptor.Class_Descriptor= 16;
                        sceVu0CopyVector(dst_location, src_location);
                        sceVu0CopyVector(dst_direction, direction);
                        HH_Effect_Object_Impact_Post(&descriptor);
                    }
                }



                
                pThis->Step = 2;
                break;
            }
        case 2: default:
            pThis->Header.Enable = false;
            result = false;
            break;
    }
    pThis->Timer += TIME_STEP_30FPS;
    return result;
}

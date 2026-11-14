#include "sh2_common.h"
#include "SH2_common/sh2sys.h"
#include "math.h"
#include "Event/demoview.h"
#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_fire_phenomenon_00.h"

static Descriptor_Post_Infomeation _post_info_demo[23] = {
    {
        /* .location = */ {-100550.0f, -3600.0f, -74800.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 10000.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {5, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
    /* .location = */ {-100550.0f, -3700.0f, -75600.0f, 0.0f},
    /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
    /* .classDescriptor = */ {43, 47},
    /* .postFrame = */ 0.0f,
    /* .deleteFrame = */ 10000.0f,
    /* .floatArgument = */ {0.0f, 0.0f},
    /* .intArgument = */ {1, 2},
    /* .step = */ 0,
    /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100400.0f, 0.0f, -79400.0f, 0.0f},
        /* .offset = */ {0.0f, -700.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 10000.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {7, 3},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100500.0f, -400.0f, -78700.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 1666.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {0, 0},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100500.0f, -400.0f, -78700.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {45, 47},
        /* .postFrame = */ 1665.0f,
        /* .deleteFrame = */ 2556.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {0, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100500.0f, -400.0f, -78700.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 2555.0f,
        /* .deleteFrame = */ 10000.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {0, 0},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100500.0f, -750.0f, -78450.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 1666.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {0, 0},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100500.0f, -750.0f, -78450.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {45, 47},
        /* .postFrame = */ 1665.0f,
        /* .deleteFrame = */ 2556.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {0, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100500.0f, -750.0f, -78450.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 2555.0f,
        /* .deleteFrame = */ 10000.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {0, 0},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100500.0f, -1200.0f, -78100.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 1666.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {4, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100500.0f, -1200.0f, -77950.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {45, 47},
        /* .postFrame = */ 1665.0f,
        /* .deleteFrame = */ 2556.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {4, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100500.0f, -1200.0f, -78100.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 2555.0f,
        /* .deleteFrame = */ 10000.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {4, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100500.0f, -2500.0f, -76800.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 10000.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {0, 0},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100550.0f, -2000.0f, -76400.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 10000.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {4, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-99500.0f, -2800.0f, -76800.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 10000.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {1, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-99500.0f, -2200.0f, -76100.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 10000.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {5, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-99500.0f, -4000.0f, -74900.0f, 0.0f},
        /* .offset = */ {0.0f, -700.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 10000.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {7, 3},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-99800.0f, -2500.0f, -75700.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 10000.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {6, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100200.0f, -4500.0f, -73700.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 10000.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {2, 1},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-99750.0f, -5600.0f, -72600.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 10000.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {2, 1},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-99500.0f, 0.0f, -78400.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {44, 0},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 10000.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {6, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100300.0f, -910.0f, -77300.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {44, 0},
        /* .postFrame = */ 5000.0f,
        /* .deleteFrame = */ 10000.0f,
        /* .floatArgument = */ {0.0f, 3.5f},
        /* .intArgument = */ {6, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-99850.0f, -900.0f, -77300.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {44, 0},
        /* .postFrame = */ 5000.0f,
        /* .deleteFrame = */ 10000.0f,
        /* .floatArgument = */ {0.0f, 4.0f},
        /* .intArgument = */ {2, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    }
};
static Descriptor_Post_Infomeation _post_info_normal[16] = {
    {
        /* .location = */ {-100550.0f, -3600.0f, -74800.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 0.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {5, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100550.0f, -3700.0f, -75600.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 0.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {1, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100500.0f, -400.0f, -78700.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 0.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {0, 0},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100500.0f, -750.0f, -78450.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 0.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {0, 0},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100500.0f, -1200.0f, -78100.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 0.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {4, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100500.0f, -2500.0f, -76800.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 0.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {0, 0},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100550.0f, -2000.0f, -76400.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 0.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {4, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-99500.0f, -2800.0f, -76800.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 0.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {1, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-99500.0f, -2200.0f, -76100.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 0.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {5, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-99500.0f, -4000.0f, -74900.0f, 0.0f},
        /* .offset = */ {0.0f, -700.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 0.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {7, 3},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-99800.0f, -2500.0f, -75700.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 0.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {6, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100200.0f, -4500.0f, -73700.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 0.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {2, 1},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-99750.0f, -5600.0f, -72600.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 0.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {2, 1},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-99500.0f, 0.0f, -78400.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 0.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {6, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-100300.0f, -910.0f, -77300.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 0.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {6, 2},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    },
    {
        /* .location = */ {-99850.0f, -900.0f, -77300.0f, 0.0f},
        /* .offset = */ {0.0f, -500.0f, 0.0f, 0.0f},
        /* .classDescriptor = */ {43, 47},
        /* .postFrame = */ 0.0f,
        /* .deleteFrame = */ 0.0f,
        /* .floatArgument = */ {0.0f, 0.0f},
        /* .intArgument = */ {2, 1},
        /* .step = */ 0,
        /* .hInstance = */ {0, 0},
    }
};

static u_int Object_Initialize(HH_Object_Fire_Phenomenon_00* pThis, ImpactQueue_Element* pElement);

static inline float shGetDemoFrame(void) {
    return demo_frame;
}

#line 618
static u_int Object_Initialize(HH_Object_Fire_Phenomenon_00* pThis, ImpactQueue_Element* pElement) {
    u_int result = true;
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
    #line 669
    u_int result = true;
    HH_Object_Fire_Phenomenon_00* pThis = pBlock;
    u_int i; ImpactQueue_Element descriptor;
    switch (pThis->Step) {
        case HH_FIRE_STEP_INIT:
            Object_Initialize(pThis, pElement);
            pThis->Step = 1;
            break;
        case HH_FIRE_STEP_PREDRAW:
            
            if (!((Sh2sys.main_status >> 6) & 1)) {
                break;
            }
            pThis->Step = HH_FIRE_STEP_DRAW;
            
        
        
        
        
        
        case HH_FIRE_STEP_DRAW:
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
            
            
                
            
            if (!GET_BIT(Sh2sys.main_status, 6)) {
                
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
                pThis->Step = HH_FIRE_STEP_OFF;
            }
            
            
            pThis->Timer += TIME_STEP_30FPS;
            break;
        default:
        case HH_FIRE_STEP_OFF:
            pThis->Header.Enable = false;
            result = false;
            break;
    }
    return result;
}

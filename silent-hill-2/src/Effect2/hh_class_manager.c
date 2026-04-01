#include "hh_class_manager.h"

#pragma divbyzerocheck off

static u_int ImpactManager(Object_Group_Infomeation* pInfo);
static u_int InstanceManager(Object_Group_Infomeation* pInfo);
static u_int InstanceCreateSuppressEnvironment_Initialize(Object_Group_Infomeation* pInfo);
static void QueueObject_Initialize(ImpactQueue_Object* pQueue);
static u_int QueueObject_enQueue(ImpactQueue_Object* pQueue, ImpactQueue_Element* pElement);
static u_int QueueObject_deQueue(ImpactQueue_Object* pQueue, ImpactQueue_Element* pElement);
static Object_Instance* Instance_Search_from_InstanceHandle(Object_Group_Infomeation* pInfo, u_int hInstance);
static u_int Instance_DesignateClassDescriptorAttach_Count(Object_InstanceTable_Infomeation* pInfo, u_int Class_Descriptor);
static u_int InstanceHandle_Get_from_ClassDescriptor_and_AttachCount(Object_InstanceTable_Infomeation* pInfo, u_int Class_Descriptor, u_int CountIndex);
static u_int Instance_Create(Object_Group_Infomeation* pInfo, ImpactQueue_Element* pElement);
static u_int Instance_OldestEntry_Search(Object_Group_Infomeation* pInfo, u_int Flag, u_int Class_Descriptor);
static u_int FreeInstance_Stack_FreeCheck(Object_InstanceTable_Infomeation* pInfo);
static Object_Instance* FreeInstance_Stack_Pop(Object_InstanceTable_Infomeation* pInfo);
static u_int FreeInstance_Stack_Push(Object_InstanceTable_Infomeation* pInfo, Object_Instance* pInstance);
static u_int InstanceHierarchyTable_Registry(Object_InstanceTable_Infomeation* pInfo, Object_Instance* pInstance);
static u_int InstanceHierarchyTable_Discard(Object_InstanceTable_Infomeation* pInfo, Object_Instance* pInstance);
static u_int InstanceHierarchyTable_DesignateInstance_Initialize(Object_InstanceTable_Infomeation* pInstance_Info, Object_DataPool_Infomeation* pPool_Info, Object_Instance* pInstance);
static u_int FreeDataBlock_Stack_FreeCheck(Object_DataPool_Infomeation* pInfo);
static Object_DataBlock_Header* FreeDataBlock_Stack_Pop(Object_DataPool_Infomeation* pInfo);
static u_int FreeDataBlock_Stack_Push(Object_DataPool_Infomeation* pInfo, Object_DataBlock_Header* pHeader);
static u_int Exception_Handling_Instance_Create(Object_Group_Infomeation* pInfo, u_int Flag, u_int Class_Descriptor);
static u_int ClassAssociation_DataPool_Initialize(Object_Group_Infomeation* pInfo, u_int Class_Descriptor);
static u_int InstanceTable_DesignateClassDescriptorAttach_Initialize(Object_Group_Infomeation* pInfo, u_int Class_Descriptor);
static u_int ClassAssociation_DataPool_All_Initialize(Object_Group_Infomeation* pInfo);
static u_int InstanceTable_All_Initialize(Object_Group_Infomeation* pInfo);

static u_int ImpactManager(Object_Group_Infomeation* pInfo) {
    u_int free_data_block_check; 
    u_int free_instance_check;
    Object_Instance* pInstance; 
    u_int result; 
    Object_InstanceTable_Infomeation* pInstance_Info; 
    ImpactQueue_Element element;

    result = 0;
    pInstance_Info = &pInfo->InstanceTable_Info;
    
    while(QueueObject_deQueue(&pInfo->Queue_Info, &element) != 0){
        if(pInfo->Association_Info.pClass_List[element.Class_Descriptor].Disable == 0){
            if(element.hInstance != 0){
                pInstance = Instance_Search_from_InstanceHandle(pInfo, element.hInstance);
                if(pInstance != NULL){
                    pInstance->Element.Option =  element.Option;
                    result = 1;
                }
            }
            else{
                free_instance_check = FreeInstance_Stack_FreeCheck(pInstance_Info);
                free_data_block_check = FreeDataBlock_Stack_FreeCheck(&pInfo->Association_Info.pDataPool_Info[element.Class_Descriptor]);

                if(free_instance_check == 0 || free_data_block_check == 0){
                    Exception_Handling_Instance_Create(pInfo, 1, element.Class_Descriptor);
                }
                if(Instance_Create(pInfo, &element) != 0){
                    result = 1;
                }
                    
            }
        }
    }
    
    return result;
}

static u_int InstanceManager(Object_Group_Infomeation* pInfo) {
    u_int i; 
    Object_InstanceTable_Infomeation* pInstance_Info; 
    Object_Class* pClass; 
    Object_Instance* pInstance;
    Object_DataPool_Infomeation* pPool_Info;
    void* pBlock_Table;
    Object_Instance* pInstance_Current;
    u_int Block_Index_Max; 
    Object_Class_Association_Infomeation* pClass_Info; 
    u_int result = 0; 

    pInstance_Info = &pInfo->InstanceTable_Info;

    for(i = 0; i < pInfo->Association_Info.Class_Max; i++){
        pClass_Info = &pInfo->Association_Info;
        pClass = &pClass_Info->pClass_List[pClass_Info->pClass_Priority_List[i]];
        pInstance = pInstance_Info->pHierarchyTable[pClass_Info->pClass_Priority_List[i]];
        pPool_Info = &pClass_Info->pDataPool_Info[pClass_Info->pClass_Priority_List[i]];
        pBlock_Table = pPool_Info->pBlock_Table;
        Block_Index_Max = pPool_Info->Block_Index_Max;

        if(pBlock_Table != NULL && pInstance != NULL){
            if(pClass->pPrefix != NULL){
                pClass->pPrefix(pBlock_Table, Block_Index_Max);
            }
            while(pInstance != NULL){
                pInstance_Current = pInstance;
                pInstance = pInstance->pNext;
                pClass->pMain(pInstance_Current->pBlock, &pInstance_Current->Element);
                pInstance_Current->Timer += 0.1/3.0;

                if(*((u_int*)pInstance_Current->pBlock) == 0){
                    InstanceHierarchyTable_DesignateInstance_Initialize(pInstance_Info, pPool_Info, pInstance_Current);
                }
            }
            if(pClass->pSuffix != NULL){
                pClass->pSuffix(pBlock_Table, Block_Index_Max);
            }

            result = 1;
        }
    }
    
    return result;
}


static u_int InstanceCreateSuppressEnvironment_Initialize(Object_Group_Infomeation* pInfo){
    u_int i = 1;
    u_int result = 0; 

    for(i = 1; i < pInfo->Association_Info.Class_Max; i++){
        pInfo->Association_Info.pClass_List[i].Disable = 0;
    }

    pInfo->Association_Info.pClass_List->Disable = 1;
    
    return result;
}

static void QueueObject_Initialize(ImpactQueue_Object* pQueue) {
    pQueue->enQueue = 0;
    pQueue->deQueue = 0;
    pQueue->Length_Current = 0;
}


static u_int QueueObject_enQueue(ImpactQueue_Object* pQueue, ImpactQueue_Element* pElement) {
    u_int result = 0; 

    if(pQueue->Length_Current < pQueue->Length_Max){
        pQueue->pElement[pQueue->enQueue++] =*pElement;
        pQueue->enQueue %= pQueue->Length_Max;
        pQueue->Length_Current++;
        result = 1;
    }

    return result;
}

static u_int QueueObject_deQueue(ImpactQueue_Object* pQueue, ImpactQueue_Element* pElement) {
    u_int result = 0; 

    if(pQueue->Length_Current != 0){
       *pElement = pQueue->pElement[pQueue->deQueue++];
        pQueue->deQueue %= pQueue->Length_Max;
        pQueue->Length_Current--;
        result = 1;
    }

    return result;
}

static Object_Instance* Instance_Search_from_InstanceHandle(Object_Group_Infomeation* pInfo, u_int hInstance){
    Object_Instance* result = NULL; 

    if(((Object_Group_Infomeation*)hInstance)->Queue_Info.pElement != NULL){
        result = (Object_Instance*)hInstance;
    }

    return result;
}

static u_int Instance_DesignateClassDescriptorAttach_Count(Object_InstanceTable_Infomeation* pInfo, u_int Class_Descriptor) {
    u_int result = 0; 
    Object_Instance* pInstance = pInfo->pHierarchyTable[Class_Descriptor];

    while(pInstance != NULL){
        result++;
        pInstance = pInstance->pNext;
    }

    return result;
}


static u_int InstanceHandle_Get_from_ClassDescriptor_and_AttachCount(Object_InstanceTable_Infomeation* pInfo, u_int Class_Descriptor, u_int CountIndex) {
    u_int result = 0; 
    u_int count = 0;
    Object_Instance* pInstance = pInfo->pHierarchyTable[Class_Descriptor];

    while(pInstance != NULL){
        if (CountIndex == count) {
            result = pInstance->hInstance;
            break;
        }
        
        count++;
        pInstance = pInstance->pNext;
    }

    return result;
}

static u_int Instance_Create(Object_Group_Infomeation* pInfo, ImpactQueue_Element* pElement) {
    Object_Instance* pInstance; 
    Object_DataBlock_Header* pHeader;
    u_int result = 0;
    Object_DataPool_Infomeation* pPool_Info = &pInfo->Association_Info.pDataPool_Info[pElement->Class_Descriptor]; 

    if(FreeDataBlock_Stack_FreeCheck(pPool_Info)){
        if((pInstance = FreeInstance_Stack_Pop(&pInfo->InstanceTable_Info)) != NULL){
            pInstance->Enable = 1;
            pInstance->hInstance = (u_int)pInstance;
            pInstance->Element =*pElement;
            pInstance->Element.hInstance = pInstance->hInstance;

            if(pInstance->Element.pResultHandle_Address){
               *pInstance->Element.pResultHandle_Address = pInstance->hInstance;
            }

            pInstance->pBlock = FreeDataBlock_Stack_Pop(pPool_Info);
            pHeader = pInstance->pBlock;
            pHeader->Enable = 1;
            InstanceHierarchyTable_Registry(&pInfo->InstanceTable_Info, pInstance);

            result = 1;
        }
    }

    return result;
}

static u_int Instance_OldestEntry_Search(Object_Group_Infomeation* pInfo, u_int Flag, u_int Class_Descriptor) {
    u_int result = 0; 
    u_int i = 0;
    u_int max = pInfo->Association_Info.Class_Max;
    float old_time = 0.0f;    
    
    Object_Instance* pInstance;

    if(Flag != 0){
        i = Class_Descriptor;
        max = Class_Descriptor +1;
    }

    for(; i < max; i++){
        pInstance = pInfo->InstanceTable_Info.pHierarchyTable[i];

        while(pInstance != NULL){
            if(!(pInstance->Timer <= old_time)){
                old_time = pInstance->Timer;
                result = pInstance->hInstance;
            }

            pInstance = pInstance->pNext; 
        }
    }

    return result;
}

static u_int FreeInstance_Stack_FreeCheck(Object_InstanceTable_Infomeation* pInfo) {
    u_int result = 0; 

    if(pInfo->pFreeTable != NULL){
        result = 1;
    }

    return result;
}
static Object_Instance* FreeInstance_Stack_Pop(Object_InstanceTable_Infomeation* pInfo) {
    Object_Instance* result = NULL; 

    if(pInfo->pFreeTable != NULL){
        result = pInfo->pFreeTable;
        pInfo->pFreeTable = pInfo->pFreeTable->pNext;

        if(pInfo->pFreeTable != NULL){
            pInfo->pFreeTable->pPrev = NULL;
        }

        result->pPrev = NULL;
        result->pNext = NULL;
    }

    return result;
}

static u_int FreeInstance_Stack_Push(Object_InstanceTable_Infomeation* pInfo, Object_Instance* pInstance) {
    u_int result = 1; 

    memset(pInstance, 0, sizeof(Object_Instance));

    if(pInfo->pFreeTable != NULL){
        pInstance->pNext = pInfo->pFreeTable;
        pInfo->pFreeTable->pPrev = pInstance;
        pInfo->pFreeTable = pInstance;
    }
    else{
        pInfo->pFreeTable = pInstance;
    }

    return result;
}

static u_int InstanceHierarchyTable_Registry(Object_InstanceTable_Infomeation* pInfo, Object_Instance* pInstance) {
    Object_Instance** pRegistry_Hierarchy = &pInfo->pHierarchyTable[pInstance->Element.Class_Descriptor];
    u_int result = 1; 

    if(*pRegistry_Hierarchy != NULL){
        pInstance->pPrev = NULL;
        pInstance->pNext =*pRegistry_Hierarchy;
        (*pRegistry_Hierarchy)->pPrev = pInstance;
       *pRegistry_Hierarchy = pInstance;
    }
    else{
       *pRegistry_Hierarchy = pInstance;
        pInstance->pPrev = NULL;
        pInstance->pNext = NULL;
    }

    return result;
}

static u_int InstanceHierarchyTable_Discard(Object_InstanceTable_Infomeation* pInfo, Object_Instance* pInstance) {
    Object_Instance** pRegistry_Hierarchy = &pInfo->pHierarchyTable[pInstance->Element.Class_Descriptor];
    u_int result = 1; 

    if(pInstance->pPrev != NULL){
        pInstance->pPrev->pNext = pInstance->pNext;
    }
    else{
       *pRegistry_Hierarchy = pInstance->pNext;
    }

    if(pInstance->pNext){
        pInstance->pNext->pPrev = pInstance->pPrev;
    }

    return result;
}

static u_int InstanceHierarchyTable_DesignateInstance_Initialize(Object_InstanceTable_Infomeation* pInstance_Info, Object_DataPool_Infomeation* pPool_Info, Object_Instance* pInstance) {
    u_int result = 1; 

    if(pInstance->Element.pResultHandle_Address != NULL){
       *pInstance->Element.pResultHandle_Address = 0;
    }

    FreeDataBlock_Stack_Push(pPool_Info, pInstance->pBlock);
    InstanceHierarchyTable_Discard(pInstance_Info, pInstance);
    FreeInstance_Stack_Push(pInstance_Info, pInstance);
    
    return result;
}

static u_int FreeDataBlock_Stack_FreeCheck(Object_DataPool_Infomeation* pInfo) {
    u_int result = 0; 

    if(pInfo->pFreeBlock_List != NULL){
        result = 1;
    }

    return result;
}

static Object_DataBlock_Header* FreeDataBlock_Stack_Pop(Object_DataPool_Infomeation* pInfo) {
    Object_DataBlock_Header* result = NULL; 

    if(pInfo->pFreeBlock_List != NULL){
        result = pInfo->pFreeBlock_List;
        pInfo->pFreeBlock_List = result->pNext;
        result->pNext = NULL;
    }

    return result;
}

static u_int FreeDataBlock_Stack_Push(Object_DataPool_Infomeation* pInfo, Object_DataBlock_Header* pHeader) {
    u_int result = 1; 

    memset(pHeader, 0, pInfo->Block_Size);

    if(pInfo->pFreeBlock_List != NULL){
        pHeader->pNext = pInfo->pFreeBlock_List;
        pInfo->pFreeBlock_List = pHeader;
    }
    else{
        pInfo->pFreeBlock_List = pHeader;
    }

    return result;
}

static u_int Exception_Handling_Instance_Create(Object_Group_Infomeation* pInfo, u_int Flag, u_int Class_Descriptor) {
    Object_DataPool_Infomeation* pPool_Info; 
    Object_Class_Association_Infomeation* pClass_Info; 
    Object_Instance* pInstance; 
    u_int hInstance; 
    u_int result = 0;

    hInstance = Instance_OldestEntry_Search(pInfo, Flag, Class_Descriptor);

    if(hInstance != 0){
        pInstance = Instance_Search_from_InstanceHandle(pInfo, hInstance);
        pClass_Info = &pInfo->Association_Info;
        pPool_Info = &pClass_Info->pDataPool_Info[Class_Descriptor];
        
        if(pInstance->Element.pResultHandle_Address != NULL){
           *pInstance->Element.pResultHandle_Address = 0;
        }

        FreeDataBlock_Stack_Push(pPool_Info, pInstance->pBlock);
        InstanceHierarchyTable_Discard(&pInfo->InstanceTable_Info, pInstance);
        FreeInstance_Stack_Push(&pInfo->InstanceTable_Info, pInstance);

        result = 1;
    }

    return result;
}

static u_int ClassAssociation_DataPool_Initialize(Object_Group_Infomeation* pInfo, u_int Class_Descriptor) {
    u_int i;
    Object_DataBlock_Header* pHeader;       
    Object_DataPool_Infomeation* pPool_Info; 
    u_int result = 0; 

    if(pInfo != NULL){
        pPool_Info = &pInfo->Association_Info.pDataPool_Info[Class_Descriptor]; 

        if(pPool_Info->pBlock_Table != NULL){
            memset(pPool_Info->pBlock_Table, 0, pPool_Info->Block_Size* pPool_Info->Block_Index_Max);

            
            pHeader = pPool_Info->pBlock_Table;
            
            for(i = 0; i < pPool_Info->Block_Index_Max-1; i++, pHeader = pHeader->pNext){
                pHeader->pNext = (void*) ((u8*)pHeader + pPool_Info->Block_Size);
            }

            pHeader->pNext = NULL;
            pPool_Info->pFreeBlock_List = pPool_Info->pBlock_Table;
            
            result = 1;
        }
    }

    return result;
}

static u_int InstanceTable_DesignateClassDescriptorAttach_Initialize(Object_Group_Infomeation* pInfo, u_int Class_Descriptor) {
    u_int result = 0; 
    Object_Instance* pInstance; 
    Object_DataPool_Infomeation* pPool_Info; 
    Object_Instance* pInstance_Current;

    pInstance = pInfo->InstanceTable_Info.pHierarchyTable[Class_Descriptor];
    pPool_Info = &pInfo->Association_Info.pDataPool_Info[Class_Descriptor];

    while(pInstance != NULL){
        pInstance_Current = pInstance;
        pInstance = pInstance->pNext;

        if(pInstance_Current->Element.pResultHandle_Address != NULL){
           *pInstance_Current->Element.pResultHandle_Address = 0;
        }
        
        FreeDataBlock_Stack_Push(pPool_Info, pInstance_Current->pBlock);
        InstanceHierarchyTable_Discard(&pInfo->InstanceTable_Info, pInstance_Current);
        FreeInstance_Stack_Push(&pInfo->InstanceTable_Info, pInstance_Current);

        result = 1;
    }

    return result;
}

static u_int ClassAssociation_DataPool_All_Initialize(Object_Group_Infomeation* pInfo) {
    u_int i; 
    u_int result = 0; 

    if(pInfo != NULL){
        for(i = 0; i < pInfo->Association_Info.Class_Max; i++){
            ClassAssociation_DataPool_Initialize(pInfo, i);
        }
        
        result = 1;
    }

    return result;
}

static u_int InstanceTable_All_Initialize(Object_Group_Infomeation* pInfo) {
    u_int result = 0; 
    u_int i;
    Object_Instance* pCurrent;
    Object_Instance* pPrev;

    if(pInfo != NULL){
        pInfo->InstanceTable_Info.hInstance_History = 0;
        memset(pInfo->InstanceTable_Info.pInstanceTable, 0, pInfo->InstanceTable_Info.Instance_Max* sizeof(Object_Instance));
        pInfo->InstanceTable_Info.pFreeTable = pInfo->InstanceTable_Info.pInstanceTable;
        memset(pInfo->InstanceTable_Info.pHierarchyTable, 0, pInfo->Association_Info.Class_Max* 4);

        pCurrent = pInfo->InstanceTable_Info.pInstanceTable;
        pPrev = NULL;

        for(i = 0; i < pInfo->InstanceTable_Info.Instance_Max; i++, pCurrent++){
            pCurrent->pPrev = pPrev;
            pCurrent->pNext = pCurrent+1;
            pPrev = pCurrent;
        }

        (pCurrent-1)->pNext = NULL;
        
        result = 1;
    }
    
    return result;
}

u_int ImpactDescriptor_Post(Object_Group_Infomeation* pInfo, ImpactQueue_Element* pDescriptor) {
    u_int result = 0;

    if(pDescriptor->Class_Descriptor >= CLASS_DESCRIPTOR_MAX){
        printf("--------------------Class_Descriptor Over!!");
        while(1);
    }
    if(QueueObject_enQueue(&pInfo->Queue_Info, pDescriptor) != 0){
        result = 1;        
    }

    return result;
}

u_int Object_Group_Manager(Object_Group_Infomeation* pInfo) {
    u_int result = 0; 

    if(pInfo != NULL){
        switch(pInfo->Step){
            case 0:
                InstanceCreateSuppressEnvironment_Initialize(pInfo);
                pInfo->Step = 1;
                result = 1;
                break;
            case 1:
                if(pInfo->Enable != 0){
                    ImpactManager(pInfo);
                    InstanceCreateSuppressEnvironment_Initialize(pInfo);
                    HH_DBG_Wrapper_T0_COUNT_Get();
                    InstanceManager(pInfo);
                    HH_DBG_Wrapper_T0_COUNT_Delta();
                }
                result = 1;
                break;
            default:
                break;
        }
    }
    
    return result;
}

u_int Object_Group_Infomeation_Set(Object_Group_Infomeation* pInfo) {
    u_int result = 0; 

    if(pInfo != NULL){
        result = 1;
        pInfo->Enable = 1;
        pInfo->Step = 0;
    }

    return result;
}

u_int Object_Group_QueueInfomeation_Set(Object_Group_Infomeation* pInfo, ImpactQueue_Element* pElement_Base, u_int Length_Max) {
    u_int result = 0; 
    ImpactQueue_Object* pQueue_Info = pQueue_Info = &pInfo->Queue_Info;

    if(pInfo != NULL && pElement_Base != NULL && Length_Max != 0){
        pQueue_Info->pElement = pElement_Base;
        pQueue_Info->Length_Max = Length_Max;
        QueueObject_Initialize(pQueue_Info);
        result = 1;
    }

    return result;
}

u_int Object_Group_ClassAssociationInfomeation_Set(Object_Group_Infomeation* pInfo, Object_Class* pClass_List, Object_DataPool_Infomeation* pPool_Info_Base, u_int* pClass_Priority_List, u_int Class_Max) {
    u_int result = 0; 

    if(pInfo != NULL && pClass_List != NULL && pPool_Info_Base != NULL && pClass_Priority_List != NULL && Class_Max != 0){
        pInfo->Association_Info.pClass_List = pClass_List;
        pInfo->Association_Info.pDataPool_Info = pPool_Info_Base;
        pInfo->Association_Info.pClass_Priority_List = pClass_Priority_List;
        pInfo->Association_Info.Class_Max = Class_Max;
        result = 1;
    }

    return result;
}

u_int Object_Group_InstanceTableInfomeation_Set(Object_Group_Infomeation* pInfo, Object_Instance* pInstance_Base, Object_Instance** pInstance_HierarchyTable, u_int Instance_Max) {
    u_int result = 0; 

    if(pInfo != NULL && pInstance_Base != NULL && pInstance_HierarchyTable != NULL && Instance_Max != 0){
        pInfo->InstanceTable_Info.hInstance_History = 0;
        pInfo->InstanceTable_Info.Instance_Max = Instance_Max;
        pInfo->InstanceTable_Info.pInstanceTable = pInstance_Base;
        pInfo->InstanceTable_Info.pHierarchyTable = pInstance_HierarchyTable;
        pInfo->InstanceTable_Info.pFreeTable = pInstance_Base;
        result = 1;
    }

    return result;
}

u_int Object_Group_All_Initialize(Object_Group_Infomeation* pInfo) {
    u_int result = 0; 

    if(pInfo != NULL){
        ClassAssociation_DataPool_All_Initialize(pInfo);
        InstanceTable_All_Initialize(pInfo);
        QueueObject_Initialize(&pInfo->Queue_Info);
        result = 1;
    }

    return result;
}

u_int Object_Group_InstanceTable_DesignateClassDescriptorAttach_Initialize(Object_Group_Infomeation* pInfo, u_int Class_Descriptor) {
    return InstanceTable_DesignateClassDescriptorAttach_Initialize(pInfo, Class_Descriptor);
}

u_int Object_Group_InstanceTable_DesignateInstanceHandleAttach_Initialize(Object_Group_Infomeation* pInfo, u_int hInstance) {
    Object_Instance* pInstance; 
    u_int result = 0; 

    if(hInstance != 0){
        pInstance = Instance_Search_from_InstanceHandle(pInfo, hInstance);
        result = InstanceHierarchyTable_DesignateInstance_Initialize(&pInfo->InstanceTable_Info, &pInfo->Association_Info.pDataPool_Info[pInstance->Element.Class_Descriptor], pInstance);
    }
    
    return result;
}

u_int ObjectInstance_DesignateClassDescriptorAttach_Count(Object_Group_Infomeation* pInfo, u_int Class_Descriptor) {
    return Instance_DesignateClassDescriptorAttach_Count(&pInfo->InstanceTable_Info, Class_Descriptor);
}

u_int ObjectInstanceHandle_Get_from_ClassDescriptor_and_AttachCount(Object_Group_Infomeation* pInfo, u_int Class_Descriptor, u_int CountIndex) {
    return InstanceHandle_Get_from_ClassDescriptor_and_AttachCount(&pInfo->InstanceTable_Info, Class_Descriptor, CountIndex);
}

ImpactQueue_Element* ObjectInstance_Element_Get(Object_Group_Infomeation* pInfo, u_int hInstance) {
    Object_Instance* pInstance; 
    ImpactQueue_Element* result = NULL;

    pInstance = Instance_Search_from_InstanceHandle(pInfo, hInstance);

    if(pInstance != NULL){
        result = &pInstance->Element;
    }

    return result;
}

void* ObjectInstance_DataBlock_Get(Object_Group_Infomeation* pInfo, u_int hInstance) {
    Object_Instance* pInstance;
    void* result = NULL;

    pInstance = Instance_Search_from_InstanceHandle(pInfo, hInstance);

    if(pInstance != NULL){
        result = pInstance->pBlock;
    }

    return result;
}

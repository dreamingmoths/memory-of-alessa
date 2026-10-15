#include "Effect2/hh_class_manager.h"

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
static u_int InstanceHierarchyTable_DesignateInstance_Initialize(Object_InstanceTable_Infomeation* pInstance_Info, ImpactQueue_Object* Queue_Info, Object_DataPool_Infomeation* pPool_Info, Object_Instance* pInstance);
static u_int FreeDataBlock_Stack_FreeCheck(Object_DataPool_Infomeation* pInfo);
static Object_DataBlock_Header* FreeDataBlock_Stack_Pop(Object_DataPool_Infomeation* pInfo);
static u_int FreeDataBlock_Stack_Push(Object_DataPool_Infomeation* pInfo, Object_DataBlock_Header* pHeader);
static u_int Exception_Handling_Instance_Create(Object_Group_Infomeation* pInfo, u_int Flag, u_int Class_Descriptor);
static u_int ClassAssociation_DataPool_Initialize(Object_Group_Infomeation* pInfo, u_int Class_Descriptor);
static u_int InstanceTable_DesignateClassDescriptorAttach_Initialize(Object_Group_Infomeation* pInfo, u_int Class_Descriptor);
static u_int ClassAssociation_DataPool_All_Initialize(Object_Group_Infomeation* pInfo);
static u_int InstanceTable_All_Initialize(Object_Group_Infomeation* pInfo);

static void func_001413D0(Object_Group_Infomeation* pInfo, u_int Class_Descriptor, u_int Flag);

static void func_001413F0(Object_Group_Infomeation* pInfo, u_int Class_Descriptor, u_int Flag);

static void func_00141410(Object_Group_Infomeation* pInfo, u_int Flag);

static u_int func_001414D0(ImpactQueue_Object* pQueue, ImpactQueue_Element* pElement);

static u_int ImpactManager(Object_Group_Infomeation* pInfo) {
    u_int result                                     = 0;
    ImpactQueue_Element* element                     = NULL;
    Object_InstanceTable_Infomeation* pInstance_Info = &pInfo->InstanceTable_Info;
    Object_Instance* pInstance;
    u_int free_data_block_check;
    u_int free_instance_check;

    while (func_001415F0(&pInfo->Queue_Info, &element)) {
        if (pInfo->Association_Info.pClass_List[element->Class_Descriptor].Status & 3) {
            func_001414D0(&pInfo->Queue_Info, element);
        } else if (element->hInstance != 0) {
            pInstance = Instance_Search_from_InstanceHandle(pInstance_Info, element->hInstance);
            if (pInstance != NULL) {
                func_001414D0(&pInfo->Queue_Info, pInstance->Element);
                result             = 1;
                pInstance->Element = element;
            } else {
                func_001414D0(&pInfo->Queue_Info, element);
            }
        } else {
            free_instance_check   = FreeInstance_Stack_FreeCheck(pInstance_Info);
            free_data_block_check = FreeDataBlock_Stack_FreeCheck(&pInfo->Association_Info.pDataPool_Info[element->Class_Descriptor]);

            if (free_instance_check == 0 || free_data_block_check == 0) {
                Exception_Handling_Instance_Create(pInfo, 1, element->Class_Descriptor);
            }
            if (Instance_Create(pInfo, element) != 0) {
                result = 1;
            } else {
                func_001414D0(&pInfo->Queue_Info, element);
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

    for (i = 0; i < pInfo->Association_Info.Class_Max; i++) {
        pClass_Info     = &pInfo->Association_Info;
        pClass          = &pClass_Info->pClass_List[pClass_Info->pClass_Priority_List[i]];
        pInstance       = pInstance_Info->pHierarchyTable[pClass_Info->pClass_Priority_List[i]];
        pPool_Info      = &pClass_Info->pDataPool_Info[pClass_Info->pClass_Priority_List[i]];
        pBlock_Table    = pPool_Info->pBlock_Table;
        Block_Index_Max = pPool_Info->Block_Index_Max;

        if (pBlock_Table != NULL && pInstance != NULL && !(pClass->Status & 0xC)) {
            if (pClass->pPrefix != NULL) {
                pClass->pPrefix(pBlock_Table, Block_Index_Max);
            }
            while (pInstance != NULL) {
                pInstance_Current = pInstance;
                pInstance         = pInstance->pNext;
                pClass->pMain(pInstance_Current->pBlock, pInstance_Current->Element);
                pInstance_Current->Timer += 0.1 / 3.0;

                if (*((u_int*) pInstance_Current->pBlock) == 0) {
                    InstanceHierarchyTable_DesignateInstance_Initialize(pInstance_Info, &pInfo->Queue_Info, pPool_Info, pInstance_Current);
                }
            }
            if (pClass->pSuffix != NULL) {
                pClass->pSuffix(pBlock_Table, Block_Index_Max);
            }

            result = 1;
        }
    }

    return result;
}

static void func_001413D0(Object_Group_Infomeation* pInfo, u_int Class_Descriptor, u_int Flag) {
    pInfo->Association_Info.pClass_List[Class_Descriptor].Status |= Flag;
}

static void func_001413F0(Object_Group_Infomeation* pInfo, u_int Class_Descriptor, u_int Flag) {
    pInfo->Association_Info.pClass_List[Class_Descriptor].Status &= ~Flag;
}

static void func_00141410(Object_Group_Infomeation* pInfo, u_int Flag) {
    u_int i = 1;

    for (i = 1; i < pInfo->Association_Info.Class_Max; i++) {
        func_001413F0(pInfo, i, Flag);
    }
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141460);

static u_int func_001414D0(ImpactQueue_Object* pQueue, ImpactQueue_Element* pElement) {
    u_int result = 0;

    if (pQueue->Length_Current < pQueue->Length_Max) {
        pElement->unk0   = pQueue->pElement;
        pQueue->pElement = pElement;
        pQueue->Length_Current++;
        result = 1;
    }

    return result;
}

// ImpactQueue_Element* QueueObject_deQueue(ImpactQueue_Object* pQueue, ImpactQueue_Element* pElement) {
ImpactQueue_Element* func_00141510(ImpactQueue_Object* pQueue, ImpactQueue_Element* pElement) {
    ImpactQueue_Element* queuedElement;
    ImpactQueue_Element* result = NULL;

    if (pQueue->Length_Current != 0) {
        queuedElement = pQueue->pElement;
        if (queuedElement != NULL) {
            result              = queuedElement;
            pQueue->pElement    = queuedElement->unk0;
            queuedElement->unk0 = NULL;
            pQueue->Length_Current--;
        }
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", QueueObject_enQueue);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_001415F0);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141650);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", Instance_Search_from_InstanceHandle);

static u_int Instance_DesignateClassDescriptorAttach_Count(Object_InstanceTable_Infomeation* pInfo, u_int Class_Descriptor) {
    u_int result               = 0;
    Object_Instance* pInstance = pInfo->pHierarchyTable[Class_Descriptor];

    while (pInstance != NULL) {
        result++;
        pInstance = pInstance->pNext;
    }

    return result;
}

static u_int InstanceHandle_Get_from_ClassDescriptor_and_AttachCount(Object_InstanceTable_Infomeation* pInfo, u_int Class_Descriptor, u_int CountIndex) {
    u_int result               = 0;
    u_int count                = 0;
    Object_Instance* pInstance = pInfo->pHierarchyTable[Class_Descriptor];

    while (pInstance != NULL) {
        if (CountIndex == count) {
            result = pInstance->hInstance;
            break;
        }

        count++;
        pInstance = pInstance->pNext;
    }

    return result;
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", Instance_Create);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141820);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", FreeInstance_Stack_FreeCheck);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_001418D0);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141910);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141980);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_001419D0);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", InstanceHierarchyTable_DesignateInstance_Initialize);

static u_int FreeDataBlock_Stack_FreeCheck(Object_DataPool_Infomeation* pInfo) {
    u_int result = 0;

    if (pInfo->pFreeBlock_List != NULL) {
        result = 1;
    }

    return result;
}

static Object_DataBlock_Header* FreeDataBlock_Stack_Pop(Object_DataPool_Infomeation* pInfo) {
    Object_DataBlock_Header* result = NULL;

    if (pInfo->pFreeBlock_List != NULL) {
        result                 = pInfo->pFreeBlock_List;
        pInfo->pFreeBlock_List = result->pNext;
        result->pNext          = NULL;
    }

    return result;
}

static u_int FreeDataBlock_Stack_Push(Object_DataPool_Infomeation* pInfo, Object_DataBlock_Header* pHeader) {
    u_int result = 1;

    memset(pHeader, 0, pInfo->Block_Size);

    if (pInfo->pFreeBlock_List != NULL) {
        pHeader->pNext         = pInfo->pFreeBlock_List;
        pInfo->pFreeBlock_List = pHeader;
    } else {
        pInfo->pFreeBlock_List = pHeader;
    }

    return result;
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", Exception_Handling_Instance_Create);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", ClassAssociation_DataPool_Initialize);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141C80);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141D50);

static u_int InstanceTable_All_Initialize(struct Object_Group_Infomeation* pInfo /* r16 */) {
    u_int result = 0;
    u_int i;
    struct Object_Instance* pCurrent;
    struct Object_Instance* pPrev;

    if (pInfo != NULL) {
        memset(pInfo->InstanceTable_Info.pInstanceTable, 0, pInfo->InstanceTable_Info.Instance_Max * sizeof(struct Object_Instance));
        pInfo->InstanceTable_Info.pFreeTable = pInfo->InstanceTable_Info.pInstanceTable;
        memset(pInfo->InstanceTable_Info.pHierarchyTable, 0, pInfo->Association_Info.Class_Max * 4);

        pCurrent = pInfo->InstanceTable_Info.pInstanceTable;
        pPrev    = NULL;

        for (i = 0; i < pInfo->InstanceTable_Info.Instance_Max; i++, pCurrent++) {
            pCurrent->pPrev = pPrev;
            pCurrent->pNext = pCurrent + 1;
            pPrev           = pCurrent;
        }

        (pCurrent - 1)->pNext = NULL;

        result = 1;
    }

    return result;
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", ImpactDescriptor_Post);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", Object_Group_Manager);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141F70);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141F90);

u_int Object_Group_ClassAssociationInfomeation_Set(Object_Group_Infomeation* pInfo, Object_Class* pClass_List, Object_DataPool_Infomeation* pPool_Info_Base, u_int* pClass_Priority_List, u_int Class_Max) {
    u_int result = 0;

    if (pInfo != NULL && pClass_List != NULL && pPool_Info_Base != NULL && pClass_Priority_List != NULL && Class_Max != 0) {
        pInfo->Association_Info.pClass_List          = pClass_List;
        pInfo->Association_Info.pDataPool_Info       = pPool_Info_Base;
        pInfo->Association_Info.pClass_Priority_List = pClass_Priority_List;
        pInfo->Association_Info.Class_Max            = Class_Max;
        result                                       = 1;
    }

    return result;
}

u_int Object_Group_InstanceTableInfomeation_Set(Object_Group_Infomeation* pInfo, Object_Instance* pInstance_Base, Object_Instance** pInstance_HierarchyTable, u_int Instance_Max) {
    u_int result = 0;

    if (pInfo != NULL && pInstance_Base != NULL && pInstance_HierarchyTable != NULL && Instance_Max != 0) {
        pInfo->InstanceTable_Info.Instance_Max    = Instance_Max;
        pInfo->InstanceTable_Info.pInstanceTable  = pInstance_Base;
        pInfo->InstanceTable_Info.pHierarchyTable = pInstance_HierarchyTable;
        pInfo->InstanceTable_Info.pFreeTable      = pInstance_Base;
        result                                    = 1;
    }

    return result;
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00142070);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_001420C0);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_001420D0);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00142120);

u_int ObjectInstance_DesignateClassDescriptorAttach_Count(Object_Group_Infomeation* pInfo, u_int Class_Descriptor) {
    return Instance_DesignateClassDescriptorAttach_Count(&pInfo->InstanceTable_Info, Class_Descriptor);
}

u_int ObjectInstanceHandle_Get_from_ClassDescriptor_and_AttachCount(Object_Group_Infomeation* pInfo, u_int Class_Descriptor, u_int CountIndex) {
    return InstanceHandle_Get_from_ClassDescriptor_and_AttachCount(&pInfo->InstanceTable_Info, Class_Descriptor, CountIndex);
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00142150);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", ObjectInstance_DataBlock_Get);

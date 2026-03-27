#include "Effect2/hh_class_manager.h"

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", ImpactManager);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141240);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_001413D0);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_001413F0);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141410);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141460);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_001414D0);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141510);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", QueueObject_enQueue);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_001415F0);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141650);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", Instance_Search_from_InstanceHandle);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", Instance_DesignateClassDescriptorAttach_Count);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", InstanceHandle_Get_from_ClassDescriptor_and_AttachCount);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141730);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141820);

static u_int FreeDataBlock_Stack_FreeCheck(Object_DataPool_Infomeation* pInfo) {
    u_int result = 0; 

    if(pInfo->pFreeBlock_List != NULL){
        result = 1;
    }

    return result;
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_001418D0);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141910);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141980);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_001419D0);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141A20);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141A90);


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

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", Exception_Handling_Instance_Create);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", ClassAssociation_DataPool_Initialize);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141C80);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141D50);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", InstanceTable_All_Initialize);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", ImpactDescriptor_Post);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141EE0);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141F70);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", func_00141F90);


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

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_manager", Object_Group_InstanceTableInfomeation_Set);

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

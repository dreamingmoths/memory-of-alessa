#ifndef HH_CLASS_MANAGER_H
#define HH_CLASS_MANAGER_H

#include "common.h"

#define CLASS_DESCRIPTOR_MAX 0x30

typedef struct ImpactQueue_ElementOption {
    float Vector[2][4] __attribute__((aligned(16))); // offset 0x0, size 0x20
    float Float_Value[2]; // offset 0x20, size 0x8
    int Int_Value[2]; // offset 0x28, size 0x8
}ImpactQueue_ElementOption;

typedef struct ImpactQueue_Element {
    u_int Class_Descriptor; // offset 0x0, size 0x4
    u_int hInstance; // offset 0x4, size 0x4
    u_int* pResultHandle_Address; // offset 0x8, size 0x4
    u_int Reserved[1]; // offset 0xC, size 0x4
    ImpactQueue_ElementOption Option; // offset 0x10, size 0x30
}ImpactQueue_Element;

typedef struct Object_Instance {
    ImpactQueue_Element Element; // offset 0x0, size 0x40
    u_int Enable; // offset 0x40, size 0x4
    u_int hInstance; // offset 0x44, size 0x4
    void* pBlock; // offset 0x48, size 0x4
    float Timer; // offset 0x4C, size 0x4
    struct Object_Instance* pPrev; // offset 0x50, size 0x4
    struct Object_Instance* pNext; // offset 0x54, size 0x4
}Object_Instance;

typedef struct Object_DataBlock_Header {
    u_int Enable; // offset 0x0, size 0x4
    struct Object_DataBlock_Header* pNext; // offset 0x4, size 0x4
}__attribute__((aligned(16))) Object_DataBlock_Header;

typedef struct Object_DataPool_Infomeation {
    u_int Block_Size; // offset 0x0, size 0x4
    u_int Block_Index_Max; // offset 0x4, size 0x4
    void* pBlock_Table; // offset 0x8, size 0x4
    Object_DataBlock_Header* pFreeBlock_List; // offset 0xC, size 0x4
}Object_DataPool_Infomeation;


typedef struct Object_InstanceTable_Infomeation {
    Object_Instance* pInstanceTable; // offset 0x0, size 0x4
    u_int Instance_Max; // offset 0x4, size 0x4
    u_int hInstance_History; // offset 0x8, size 0x4
    Object_Instance** pHierarchyTable; // offset 0xC, size 0x4
    Object_Instance* pFreeTable; // offset 0x10, size 0x4
} __attribute__((aligned(16))) Object_InstanceTable_Infomeation;

typedef struct Object_Class {
    u_int (*pPrefix)(void*, u_int); // offset 0x0, size 0x4
    u_int (*pMain)(void*, struct ImpactQueue_Element*); // offset 0x4, size 0x4
    u_int (*pSuffix)(void*, u_int); // offset 0x8, size 0x4
    u_int Disable; // offset 0xC, size 0x4
}Object_Class;

typedef struct ImpactQueue_Object {
    u_int enQueue; // offset 0x0, size 0x4
    u_int deQueue; // offset 0x4, size 0x4
    u_int Length_Current; // offset 0x8, size 0x4
    u_int Length_Max; // offset 0xC, size 0x4
    ImpactQueue_Element* pElement; // offset 0x10, size 0x4
} __attribute__((aligned(16))) ImpactQueue_Object;

typedef struct Object_Class_Association_Infomeation {
    Object_Class* pClass_List; // offset 0x0, size 0x4
    Object_DataPool_Infomeation* pDataPool_Info; // offset 0x4, size 0x4
    u_int* pClass_Priority_List; // offset 0x8, size 0x4
    u_int Class_Max; // offset 0xC, size 0x4
}Object_Class_Association_Infomeation;

typedef struct Object_Group_Infomeation {
    Object_Class_Association_Infomeation Association_Info; // offset 0x0, size 0x10
    Object_InstanceTable_Infomeation InstanceTable_Info; // offset 0x10, size 0x20
    ImpactQueue_Object Queue_Info; // offset 0x30, size 0x20
    u_int Enable; // offset 0x50, size 0x4
    u_int Step; // offset 0x54, size 0x4
}Object_Group_Infomeation;

u_int ImpactDescriptor_Post(Object_Group_Infomeation* pInfo, ImpactQueue_Element* pDescriptor);
u_int Object_Group_Manager(Object_Group_Infomeation* pInfo);
u_int Object_Group_Infomeation_Set(Object_Group_Infomeation* pInfo);
u_int Object_Group_QueueInfomeation_Set(Object_Group_Infomeation* pInfo, ImpactQueue_Element* pElement_Base, u_int Length_Max);
u_int Object_Group_ClassAssociationInfomeation_Set(Object_Group_Infomeation* pInfo, Object_Class* pClass_List, Object_DataPool_Infomeation* pPool_Info_Base, u_int* pClass_Priority_List, u_int Class_Max);
u_int Object_Group_InstanceTableInfomeation_Set(Object_Group_Infomeation* pInfo, Object_Instance* pInstance_Base, Object_Instance** pInstance_HierarchyTable, u_int Instance_Max);
u_int Object_Group_All_Initialize(Object_Group_Infomeation* pInfo);
u_int Object_Group_InstanceTable_DesignateClassDescriptorAttach_Initialize(Object_Group_Infomeation* pInfo, u_int Class_Descriptor);
u_int Object_Group_InstanceTable_DesignateInstanceHandleAttach_Initialize(Object_Group_Infomeation* pInfo, u_int hInstance);
u_int ObjectInstance_DesignateClassDescriptorAttach_Count(Object_Group_Infomeation* pInfo, u_int Class_Descriptor);
u_int ObjectInstanceHandle_Get_from_ClassDescriptor_and_AttachCount(Object_Group_Infomeation* pInfo, u_int Class_Descriptor, u_int CountIndex);
ImpactQueue_Element* ObjectInstance_Element_Get(Object_Group_Infomeation* pInfo, u_int hInstance);
void* ObjectInstance_DataBlock_Get(Object_Group_Infomeation* pInfo, u_int hInstance);

#endif

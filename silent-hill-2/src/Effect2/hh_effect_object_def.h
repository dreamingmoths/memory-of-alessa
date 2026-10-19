#ifndef HH_EFFECT_OBJECT_DEF_H
#define HH_EFFECT_OBJECT_DEF_H

#include "common.h"
#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_memory_manage.h"
#include "SH2_common/pad.h"

// total size: 0x30
typedef struct MemoryPool_AssociationInfomeation {
    // Members
    u_int Existent;                            // offset 0x0, size 0x4
    Object_DataPool_Infomeation DataPool_Info; // offset 0x10, size 0x10
    u_int LinkList_Max;                        // offset 0x20, size 0x4
    int* pLinkList;                            // offset 0x24, size 0x4
} MemoryPool_AssociationInfomeation;

static u_int MemoryPool_AllRelease(Object_DataPool_Infomeation* pPool_Info_Table, MemoryPool_AssociationInfomeation* pAssoci_Info_Table, u_int Class_Kind_Max);

static u_int MemoryPool_Inspect_and_Allocate(Object_DataPool_Infomeation* pPool_Info_Table, MemoryPool_AssociationInfomeation* pAssoci_Info_Table, u_int Class_Kind_Max);

static u_int MemoryPool_AllClear(Object_DataPool_Infomeation* pPool_Info_Table, MemoryPool_AssociationInfomeation* pAssoci_Info_Table, u_int Class_Kind_Max);

static u_int MemoryPool_Controller(Object_DataPool_Infomeation* pPool_Info_Table, MemoryPool_AssociationInfomeation* pAssoci_Info_Table, u_int Class_Kind_Max);

static void Effect_Object_Initialize(void);

void HH_Effect_Object_Impact_Post(ImpactQueue_Element* pElement);

void HH_Effect_Object_DesignateClassInstance_Clear(u_int Class_Descriptor);

void HH_Effect_Object_DesignateHandleInstance_Clear(u_int hInstance);

Object_Group_Infomeation* HH_Effect_Object_Infomeation_Get(void);

void HH_Effect_Object_Manager(void);

u_int HH_Effect_Object_MemoryBlock_Allocate(void);

void HH_Effect_Object_AutoPost(void);

#endif // HH_EFFECT_OBJECT_DEF_H

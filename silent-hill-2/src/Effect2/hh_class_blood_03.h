#ifndef HH_CLASS_BLOOD_03_H
#define HH_CLASS_BLOOD_03_H

#include "common.h"
#include "hh_class_manager.h"

typedef struct HH_Object_Blood_03 {
    Object_DataBlock_Header Header ; // offset 0x0, size 0x10
    u_int Step; // offset 0x10, size 0x4
    u_int Vertex_Kind; // offset 0x14, size 0x4
    float Timer; // offset 0x18, size 0x4
    sceVu0FVECTOR Verocity_0; // offset 0x20, size 0x10
    float Scale; // offset 0x30, size 0x4
    float Alpha; // offset 0x34, size 0x4
    u_int Motion_Step; // offset 0x38, size 0x4
}HH_Object_Blood_03;

typedef struct Motion_Table_Infomeation {
    float diff_time; // offset 0x0, size 0x4
    float diff_scale_ratio; // offset 0x4, size 0x4
    float diff_rgba_ratio; // offset 0x8, size 0x4
}Motion_Table_Infomeation;

typedef struct Vertex_Infomeation_List {
    float (* pVertex_List)[4]; // offset 0x0, size 0x4
    float (* pNormal_List)[4]; // offset 0x4, size 0x4
    u_int Vertex_Max; // offset 0x8, size 0x4
    u_int Primitive_Type; // offset 0xC, size 0x4
}Vertex_Infomeation_List;

u_int HH_Class_Prefix_Blood_01(void);
u_int HH_Class_Suffix_Blood_03(void);
u_int HH_Class_Blood_03(void* pBlock, ImpactQueue_Element* pElement);

#endif

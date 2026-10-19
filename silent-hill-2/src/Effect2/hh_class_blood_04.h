#ifndef HH_CLASS_BLOOD_04_H
#define HH_CLASS_BLOOD_04_H

#include "common.h"
#include "sce/libvu0.h"
#include "Effect2/hh_class_manager.h"

typedef struct HH_Object_Blood_04 {
    // Members
    Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_int Step; // offset 0x10, size 0x4
    u_int Vertex_Kind; // offset 0x14, size 0x4
    float Timer; // offset 0x18, size 0x4
    sceVu0FVECTOR Verocity_0; // offset 0x20, size 0x10
    float Scale; // offset 0x30, size 0x4
    float Alpha; // offset 0x34, size 0x4
    u_int Motion_Step; // offset 0x38, size 0x4
} HH_Object_Blood_04;





u_int HH_Class_Prefix_Blood_04(void);
u_int HH_Class_Suffix_Blood_04(void);
u_int HH_Class_Blood_04(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_BLOOD_04_H

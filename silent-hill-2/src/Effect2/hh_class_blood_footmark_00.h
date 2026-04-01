#ifndef HH_CLASS_BLOOD_FOOTMARK_00_H
#define HH_CLASS_BLOOD_FOOTMARK_00_H

#include "common.h"
#include "hh_class_manager.h"

typedef struct HH_Object_Blood_FootMark_00 {
    Object_DataBlock_Header Header; // offset 0x0, size 0x10
    float Timer; // offset 0x10, size 0x4
    unsigned short Step; // offset 0x14, size 0x2
    unsigned short Vertex_Kind; // offset 0x16, size 0x2
}HH_Object_Blood_FootMark_00;

typedef struct Vertex_Infomeation_List {
    // Members
    float (* pVertex_List)[4]; // offset 0x0, size 0x4
    float (* pRgba_List)[4]; // offset 0x4, size 0x4
    float (* * pStq_List)[4]; // offset 0x8, size 0x4
    unsigned int Vertex_Max; // offset 0xC, size 0x4
    unsigned int Primitive_Type; // offset 0x10, size 0x4
}Vertex_Infomeation_List;

u_int HH_Class_Prefix_Blood_FootMark_00(void);
u_int HH_Class_Suffix_Blood_FootMark_00(void);
u_int HH_Class_Blood_FootMark_00(void* pBlock, ImpactQueue_Element* pElement);

#endif

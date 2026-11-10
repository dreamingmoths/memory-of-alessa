#ifndef HH_CLASS_BLOOD_FOOTMARK_00_H
#define HH_CLASS_BLOOD_FOOTMARK_00_H

#include "common.h"
#include "hh_class_manager.h"

typedef struct HH_Object_Blood_FootMark_00 {
    Object_DataBlock_Header Header; // offset 0x0, size 0x10
    float Timer;                    // offset 0x10, size 0x4
    u_short Step;                   // offset 0x14, size 0x2
    u_short Vertex_Kind;            // offset 0x16, size 0x2
} HH_Object_Blood_FootMark_00;

u_int HH_Class_Prefix_Blood_FootMark_00(void);
u_int HH_Class_Suffix_Blood_FootMark_00(void);
u_int HH_Class_Blood_FootMark_00(void* pBlock, ImpactQueue_Element* pElement);

#endif

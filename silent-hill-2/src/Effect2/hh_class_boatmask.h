#ifndef HH_CLASS_BOATMASK_H
#define HH_CLASS_BOATMASK_H

#include "Effect2/hh_class_manager.h"

typedef struct HH_Object_Boat_Mask {
    Object_DataBlock_Header Header; // offset 0x0, size 0x10
    float Timer; // offset 0x10, size 0x4
    u_short Step; // offset 0x14, size 0x2
    u_short Vertex_Kind; // offset 0x16, size 0x2
} HH_Object_Boat_Mask;

u_int HH_Class_Prefix_Boat_Mask(void);

u_int HH_Class_Suffix_Boat_Mask(void);

u_int HH_Class_Boat_Mask(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_BOATMASK_H

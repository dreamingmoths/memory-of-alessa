#ifndef HH_CLASS_RAISE_DUST_PHENOMENON_00_H
#define HH_CLASS_RAISE_DUST_PHENOMENON_00_H

#include "Effect2/hh_class_manager.h"

typedef struct HH_Object_Raise_Dust_Phenomenon_00 {
    // Members
    Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_int Step; // offset 0x10, size 0x4
    float Alpha; // offset 0x14, size 0x4
    float Timer; // offset 0x18, size 0x4
} HH_Object_Raise_Dust_Phenomenon_00;

u_int HH_Class_Raise_Dust_Phenomenon_00(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_RAISE_DUST_PHENOMENON_00_H

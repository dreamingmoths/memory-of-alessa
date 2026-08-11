#ifndef HH_CLASS_PLURAL_PHENOMENON_00_H
#define HH_CLASS_PLURAL_PHENOMENON_00_H

#include "Effect2/hh_class_manager.h"

#define HH_CLASS_DESCRIPTOR_PLURAL_PHENOMENON_00 8
#define HH_PLURAL_PHENOMENON_00_STEP_INIT        0
#define HH_PLURAL_PHENOMENON_00_STEP_DRAW        1
#define HH_PLURAL_PHENOMENON_00_STEP_OFF         2

typedef struct HH_Object_Plural_Phenomenon_00 {
    // total size: 0x20
    Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_int Step; // offset 0x10, size 0x4
    float Timer; // offset 0x14, size 0x4
} HH_Object_Plural_Phenomenon_00;

u_int HH_Class_Plural_Phenomenon_00(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_PLURAL_PHENOMENON_00_H

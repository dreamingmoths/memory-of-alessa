#ifndef HH_CLASS_BLOOD_POOL_PHENOMENON_01_H
#define HH_CLASS_BLOOD_POOL_PHENOMENON_01_H

#include "sh2_common.h"
#include "Effect2/hh_class_manager.h"

// total size: 0x20
typedef struct HH_Object_Blood_Pool_Phenomenon_01 {
    // Members
    struct Object_DataBlock_Header Header; // offset 0x0, size 0x10
    unsigned int Step; // offset 0x10, size 0x4
    float Alpha; // offset 0x14, size 0x4
    float Timer; // offset 0x18, size 0x4
} HH_Object_Blood_Pool_Phenomenon_01;

u_int HH_Class_Blood_Pool_Phenomenon_01(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_BLOOD_POOL_PHENOMENON_01_H

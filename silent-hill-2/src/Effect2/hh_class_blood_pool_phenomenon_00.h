#ifndef HH_CLASS_BLOOD_POOL_PHENOMENON_H
#define HH_CLASS_BLOOD_POOL_PHENOMENON_H

#include "common.h"
#include "hh_class_manager.h"

typedef struct HH_Object_Blood_Pool_Phenomenon_00 {
    Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_int Step; // offset 0x10, size 0x4
    float Timer; // offset 0x14, size 0x4
    u_short Time_Table_Index; // offset 0x18, size 0x2
    u_short Post_Count; // offset 0x1A, size 0x2
}HH_Object_Blood_Pool_Phenomenon_00;

typedef struct TimeTable_Infomeation {
    float Time[3]; // offset 0x0, size 0xC
}TimeTable_Infomeation;

u_int HH_Class_Blood_Pool_Phenomenon_00(void* pBlock, ImpactQueue_Element* pElement);

#endif

#ifndef HH_CLASS_GLASS_BREAK_PHENOMENON_00_H
#define HH_CLASS_GLASS_BREAK_PHENOMENON_00_H

#include "Effect2/hh_class_manager.h"

typedef struct HH_Object_Glass_Break_Phenomenon_00 {
    Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_int Step; // offset 0x10, size 0x4
    float Timer; // offset 0x14, size 0x4
    float Beta; // offset 0x18, size 0x4
    float Alpha; // offset 0x1C, size 0x4
    float Gamma; // offset 0x20, size 0x4
    float Delta; // offset 0x24, size 0x4
    float Theta; // offset 0x28, size 0x4
    float Phai; // offset 0x2C, size 0x4
    float Lambda; // offset 0x30, size 0x4
    float Verocity_0; // offset 0x34, size 0x4
    float Next_Discharge_Time; // offset 0x38, size 0x4
    u_short Post_Count; // offset 0x3C, size 0x2
} HH_Object_Glass_Break_Phenomenon_00;

u_int HH_Class_Glass_Break_Phenomenon_00(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_GLASS_BREAK_PHENOMENON_00_H

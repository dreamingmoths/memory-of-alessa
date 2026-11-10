#ifndef HH_CLASS_FIRE_PHENOMENON_00_H
#define HH_CLASS_FIRE_PHENOMENON_00_H

#include "Effect2/hh_class_manager.h"

#define HH_FIRE_STEP_INIT        0
#define HH_FIRE_STEP_PREDRAW     1
#define HH_FIRE_STEP_DRAW        2
#define HH_FIRE_STEP_OFF         3

typedef struct Descriptor_Post_Infomeation {
    sceVu0FVECTOR Location; // offset 0x0, size 0x10
    sceVu0FVECTOR Offset; // offset 0x10, size 0x10
    u_int Class_Descriptor[2]; // offset 0x20, size 0x8
    float Post_Frame; // offset 0x28, size 0x4
    float Delete_Frame; // offset 0x2C, size 0x4
    float Float_Argument[2]; // offset 0x30, size 0x8
    u_int Int_Argument[2]; // offset 0x38, size 0x8
    u_int Step; // offset 0x40, size 0x4
    u_int hInstance[2]; // offset 0x44, size 0x8
} Descriptor_Post_Infomeation;

typedef struct HH_Object_Fire_Phenomenon_00 {
    Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_int Step; // offset 0x10, size 0x4
    float Timer; // offset 0x14, size 0x4
} HH_Object_Fire_Phenomenon_00;

u_int HH_Class_Fire_Phenomenon_00(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_FIRE_PHENOMENON_00_H

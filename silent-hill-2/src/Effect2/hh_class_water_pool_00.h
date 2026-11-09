#ifndef HH_CLASS_WATER_POOL_00_H
#define HH_CLASS_WATER_POOL_00_H

#include "Effect2/hh_class_manager.h"

#define HH_WATER_POOL_00_TEX_ID 16

typedef struct HH_Object_Water_Pool_00 {
    Object_DataBlock_Header Header; // offset 0x0, size 0x10
    unsigned short Step; // offset 0x10, size 0x2
    unsigned char Texture_Kind; // offset 0x12, size 0x1
    unsigned char Scale_Kind; // offset 0x13, size 0x1
    unsigned char Rgba_Kind; // offset 0x14, size 0x1
    unsigned char Motion_Step; // offset 0x15, size 0x1
    float Timer; // offset 0x18, size 0x4
    float Rotate_Y; // offset 0x1C, size 0x4
    float Rgba[4]; // offset 0x20, size 0x10
    float Scale[4]; // offset 0x30, size 0x10
} HH_Object_Water_Pool_00;

u_int HH_Class_Prefix_Water_Pool_00(void);

u_int HH_Class_Suffix_Water_Pool_00(void);

u_int HH_Class_Water_Pool_00(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_WATER_POOL_00_H

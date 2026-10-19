#ifndef HH_CLASS_WATER_80_H
#define HH_CLASS_WATER_80_H

#include "Effect2/hh_class_manager.h"

typedef struct HH_Object_Water_80 {
    // total size: 0x2680
    struct Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_char Step; // offset 0x10, size 0x1
    u_char Motion_Step; // offset 0x11, size 0x1
    float Timer; // offset 0x14, size 0x4
    float ST_Defference[4]; // offset 0x20, size 0x10
    float Location_Defference[4]; // offset 0x30, size 0x10
    struct Wave_Element Wave_Info[20]; // offset 0x40, size 0x690
    float Area00_Grid_Y_Value[2025]; // offset 0x6D0, size 0x1FA4
    float* pArea_Grid_Y_Value_Table[1]; // offset 0x2674, size 0x4
    float Area_WavePostTime[1]; // offset 0x2678, size 0x4
    u_int Area_Enable_Table[1]; // offset 0x267C, size 0x4
} HH_Object_Water_80;

u_int HH_Class_Prefix_Water_80(void);
u_int HH_Class_Suffix_Water_80(void);
u_int HH_Class_Water_80(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_WATER_80_H

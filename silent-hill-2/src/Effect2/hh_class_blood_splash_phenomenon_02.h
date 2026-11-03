#ifndef HH_CLASS_BLOOD_SPLASH_PHENOMENON_02_H
#define HH_CLASS_BLOOD_SPLASH_PHENOMENON_02_H

#include "Effect2/hh_class_manager.h"

typedef struct HH_Object_Blood_Splash_Phenomenon_02 {
    // total size: 0x50
    Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_int Step;                     // offset 0x10, size 0x4
    float Timer;                    // offset 0x14, size 0x4
    float Beta;                     // offset 0x18, size 0x4
    float Alpha;                    // offset 0x1C, size 0x4
    float Gamma;                    // offset 0x20, size 0x4
    float Delta;                    // offset 0x24, size 0x4
    float Theta;                    // offset 0x28, size 0x4
    float Phai;                     // offset 0x2C, size 0x4
    float Lambda;                   // offset 0x30, size 0x4
    float Verocity_0;               // offset 0x34, size 0x4
    float Next_Discharge_Time[2];   // offset 0x38, size 0x8
    u_short Post_Count[2];          // offset 0x40, size 0x4
} HH_Object_Blood_Splash_Phenomenon_02;

u_int HH_Class_Blood_Splash_Phenomenon_02(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_BLOOD_SPLASH_PHENOMENON_02_H

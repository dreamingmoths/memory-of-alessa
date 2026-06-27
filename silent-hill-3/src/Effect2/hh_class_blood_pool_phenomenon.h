#ifndef HH_CLASS_BLOOD_POOL_PHENOMENON
#define HH_CLASS_BLOOD_POOL_PHENOMENON

#include "Effect2/hh_class_manager.h"

typedef struct TimeTable_Infomeation {
    float Time[3]; // offset 0x0, size 0xC
} TimeTable_Infomeation;

typedef struct HH_Object_Blood_Pool_Phenomenon {
    Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_int Step;                     // offset 0x10, size 0x4
    float Timer;                    // offset 0x14, size 0x4
    u_short Time_Table_Index;       // offset 0x18, size 0x2
    u_short Post_Count;             // offset 0x1A, size 0x2
} HH_Object_Blood_Pool_Phenomenon;

#endif // HH_CLASS_BLOOD_POOL_PHENOMENON
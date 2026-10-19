#ifndef HH_CLASS_BLOOD_02_H
#define HH_CLASS_BLOOD_02_H

#include "common.h"
#include "hh_class_manager.h"

typedef struct HH_Object_Blood_02 {
    Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_short Step;                   // offset 0x10, size 0x2
    u_char Vertex_Kind;             // offset 0x12, size 0x1
    u_char Scale_Kind;              // offset 0x13, size 0x1
    u_char Rgba_Kind;               // offset 0x14, size 0x1
    u_char Motion_Step;             // offset 0x15, size 0x1
    float Timer;                    // offset 0x18, size 0x4
    float Rotate_Y;                 // offset 0x1C, size 0x4
    float Rgba[4];                  // offset 0x20, size 0x10
    float Scale[4];                 // offset 0x30, size 0x10
} HH_Object_Blood_02;





u_int HH_Class_Prefix_Blood_02(void);
u_int HH_Class_Suffix_Blood_02(void);
u_int HH_Class_Blood_02(void* pBlock, ImpactQueue_Element* pElement);
u_int HH_Class_Blood_02_DesignateLocation_CollisionCheck(void* pBlock, ImpactQueue_Element* pElement, float* Target_Location);

#endif

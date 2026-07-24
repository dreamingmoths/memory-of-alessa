#ifndef HH_CLASS_BLOOD_STICK_00_H
#define HH_CLASS_BLOOD_STICK_00_H

#include "sh2_common.h"
#include "Effect2/hh_class_manager.h"

// total size: 0x20
typedef struct HH_Object_Blood_Stick_00 {
    // Members
    struct Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_short Step; // offset 0x10, size 0x2
    u_char Vertex_Kind; // offset 0x12, size 0x1
    u_char Monitor_Step; // offset 0x13, size 0x1
    float Timer; // offset 0x14, size 0x4
    char Mark_Count; // offset 0x18, size 0x1
    char Leftover; // offset 0x19, size 0x1
    u_char Character_ID; // offset 0x1A, size 0x1
    u_char FootMark_Kind; // offset 0x1B, size 0x1
} HH_Object_Blood_Stick_00;

u_int HH_Class_Blood_Stick_00(void * pBlock /* r2 */, struct ImpactQueue_Element * pElement /* r2 */);

extern float acosf(float); // where is this from?

#endif // HH_CLASS_BLOOD_STICK_00_H

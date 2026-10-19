#ifndef HH_OBJECT_VERTEX_INFO
#define HH_OBJECT_VERTEX_INFO

// @note: this header file is not in the DWARF information, introduced for organizational purposes

#include "types.h"

typedef struct Vertex_Infomeation_List {
    float (*pVertex_List)[4]; // offset 0x0, size 0x4
    float (*pNormal_List)[4]; // offset 0x4, size 0x4
    u_int Vertex_Max;         // offset 0x8, size 0x4
    u_int Primitive_Type;     // offset 0xC, size 0x4
} Vertex_Infomeation_List;

#endif // HH_OBJECT_VERTEX_INFO

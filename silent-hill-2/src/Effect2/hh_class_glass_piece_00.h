#ifndef HH_CLASS_GLASS_PIECE_00_H
#define HH_CLASS_GLASS_PIECE_00_H

#include "Effect2/hh_class_manager.h"

typedef struct HH_Object_GlassPiece_00 {
    Object_DataBlock_Header Header; // offset 0x0, size 0x10
    unsigned int Step; // offset 0x10, size 0x4
    unsigned int Vertex_Kind; // offset 0x14, size 0x4
    unsigned int Texture_Kind; // offset 0x18, size 0x4
    float Timer; // offset 0x1C, size 0x4
    float Verocity_0[4]; // offset 0x20, size 0x10
    float Rotate[4]; // offset 0x30, size 0x10
} HH_Object_GlassPiece_00;

#define HH_GLASS_PIECE_00_TEX_ID 17

u_int HH_Class_Prefix_GlassPiece_00(void);

u_int HH_Class_Suffix_GlassPiece_00(void);

u_int HH_Class_GlassPiece_00(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_GLASS_PIECE_00_H

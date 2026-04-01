#ifndef MODEL3_VU1_N_H
#define MODEL3_VU1_N_H

#include "common.h"
#include "libvifpk.h"
#include "libdma.h"
#include "model_common.h"

typedef struct Part
{
    // total size: 0x90
    unsigned int size;                       // offset 0x0, size 0x4
    unsigned int type;                       // offset 0x4, size 0x4
    unsigned int packet_offset;              // offset 0x8, size 0x4
    unsigned int packet_qwc;                 // offset 0xC, size 0x4
    unsigned int xtop;                       // offset 0x10, size 0x4
    unsigned int n_cluster_data;             // offset 0x14, size 0x4
    unsigned int cluster_data_offset;        // offset 0x18, size 0x4
    unsigned int n_skeletons;                // offset 0x1C, size 0x4
    unsigned int skeletons_offset;           // offset 0x20, size 0x4
    unsigned int n_skeleton_pairs;           // offset 0x24, size 0x4
    unsigned int skeleton_pairs_offset;      // offset 0x28, size 0x4
    unsigned int data_skeletons_offset;      // offset 0x2C, size 0x4
    unsigned int data_skeleton_pairs_offset; // offset 0x30, size 0x4
    unsigned int n_textures;                 // offset 0x34, size 0x4
    unsigned int text_pos_indices_offset;    // offset 0x38, size 0x4
    unsigned int texture_params_offset;      // offset 0x3C, size 0x4
    unsigned char shading_type;              // offset 0x40, size 0x1
    unsigned char specular_pos;              // offset 0x41, size 0x1
    unsigned char equipment_id;              // offset 0x42, size 0x1
    unsigned char hoge;                      // offset 0x43, size 0x1
    unsigned char backclip;                  // offset 0x44, size 0x1
    unsigned char envmap_param;              // offset 0x45, size 0x1
    unsigned char reserved[2];               // offset 0x46, size 0x2
    float phong_param_a;                     // offset 0x48, size 0x4
    float phong_param_b;                     // offset 0x4C, size 0x4
    float blinn_param;                       // offset 0x50, size 0x4
    unsigned int padding[3];                 // offset 0x54, size 0xC
    float diffuse[4];                        // offset 0x60, size 0x10
    float ambient[4];                        // offset 0x70, size 0x10
    float specular[4];                       // offset 0x80, size 0x10
} Part;

typedef struct TextureParam {
    // total size: 0x10
    unsigned long clamp; // offset 0x0, size 0x4
    unsigned long tex1; // offset 0x8, size 0x4
} TextureParam;

typedef struct NDrawData {
    // total size: 0x80
    union Q giftag; // offset 0x0, size 0x10
    union Q waittag; // offset 0x10, size 0x10
    union Q envtag; // offset 0x20, size 0x10
    union Q tex0; // offset 0x30, size 0x10
    union Q tex1; // offset 0x40, size 0x10
    union Q clamp; // offset 0x50, size 0x10
    union Q alpha; // offset 0x60, size 0x10
    union Q fogcol; // offset 0x70, size 0x10
} NDrawData;

typedef struct SprData {
    // total size: 0x200
    struct NDrawData ndraw[2]; // offset 0x0, size 0x100
    struct NDrawData odraw[2]; // offset 0x100, size 0x100
} SprData;

extern u_int D_01EE8088; // fake extern, xitop

extern SprData* spr_data;

extern int all_data; // @todo add the AllData type

#endif


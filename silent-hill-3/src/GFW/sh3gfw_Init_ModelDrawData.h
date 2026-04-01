#ifndef SH3GFW_INIT_MODEL_DRAW_DATA
#define SH3GFW_INIT_MODEL_DRAW_DATA

#include "common.h"

// GFW\sh3gfw_Init_ModelDrawData.c
typedef struct sh_Model
{
    // total size: 0x80
    u_int id;                        // offset 0x0, size 0x4
    u_int revision;                  // offset 0x4, size 0x4
    u_int initial_matrices_offset;   // offset 0x8, size 0x4
    u_int n_skeletons;               // offset 0xC, size 0x4
    u_int skeleton_structure_offset; // offset 0x10, size 0x4
    u_int n_skeleton_pairs;          // offset 0x14, size 0x4
    u_int skeleton_pairs_offset;     // offset 0x18, size 0x4
    u_int default_pcms_offset;       // offset 0x1C, size 0x4
    u_int n_vu1_parts;               // offset 0x20, size 0x4
    u_int vu1_parts_offset;          // offset 0x24, size 0x4
    u_int n_vu0_parts;               // offset 0x28, size 0x4
    u_int vu0_parts_offset;          // offset 0x2C, size 0x4
    u_int n_texture_blocks;          // offset 0x30, size 0x4
    u_int texture_blocks_offset;     // offset 0x34, size 0x4
    u_int n_text_poses;              // offset 0x38, size 0x4
    u_int text_poses_offset;         // offset 0x3C, size 0x4
    u_int text_pos_params_offset;    // offset 0x40, size 0x4
    u_int n_cluster_nodes;           // offset 0x44, size 0x4
    u_int cluster_nodes_offset;      // offset 0x48, size 0x4
    u_int n_clusters;                // offset 0x4C, size 0x4
    u_int clusters_offset;           // offset 0x50, size 0x4
    u_int n_func_data;               // offset 0x54, size 0x4
    u_int func_data_offset;          // offset 0x58, size 0x4
    u_int hit_offset;                // offset 0x5C, size 0x4
    u_int box_offset;                // offset 0x60, size 0x4
    u_int flag;                      // offset 0x64, size 0x4
    u_int relative_matrices_offset;  // offset 0x68, size 0x4
    u_int relative_transes_offset;   // offset 0x6C, size 0x4
    void *pTexMAN[4];                // offset 0x70, size 0x10
} sh_Model;

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

#endif

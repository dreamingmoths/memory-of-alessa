#ifndef MODEL_COMMON_H
#define MODEL_COMMON_H

#include "common.h"

typedef struct TextPosParam
{
    // total size: 0x8
    unsigned long tex0; // offset 0x0, size 0x4
} TextPosParam;

typedef struct ModelCommonWork
{
    // total size: 0xE300
    float skeleton_matrices[128][4][4];      // offset 0x0, size 0x2000
    float envelope_matrices[256][4][4];      // offset 0x2000, size 0x4000
    float cluster_nodes[2048][4];            // offset 0x6000, size 0x8000
    float top_skeleton_matrix[4][4];         // offset 0xE000, size 0x40
    float vsp[2][4];                         // offset 0xE040, size 0x20
    float vcp[2][4];                         // offset 0xE060, size 0x20
    float vcp_gs[2][4];                      // offset 0xE080, size 0x20
    struct TextPosParam text_pos_params[64]; // offset 0xE0A0, size 0x200
    unsigned long specular_mapping_tex0;     // offset 0xE2A0, size 0x4
    unsigned long latitude_mapping_tex0;     // offset 0xE2A8, size 0x4
} ModelCommonWork;

typedef struct Model3Junk
{
    // total size: 0x1C0
    float xyz_min[4];        // offset 0x0, size 0x10
    float xyz_max[4];        // offset 0x10, size 0x10
    float xyz_min_wide[4];   // offset 0x20, size 0x10
    float xyz_max_wide[4];   // offset 0x30, size 0x10
    float rgba_max[4];       // offset 0x40, size 0x10
    float global_ambient[4]; // offset 0x50, size 0x10
    __int128 giftag_0;       // offset 0x60, size 0x10
    __int128 giftag_1;       // offset 0x70, size 0x10
    __int128 giftag_2;       // offset 0x80, size 0x10
    float camera[4];         // offset 0x90, size 0x10
    float wvm[4][4];         // offset 0xA0, size 0x40
    float vsm[4][4];         // offset 0xE0, size 0x40
    float wsm[4][4];         // offset 0x120, size 0x40

    // float vwm[4][4];           // offset 0x160, size 0x40
    char unk[0x38];
    float (*cluster_nodes)[4];
    float (*cluster_nodes2)[4];

    void *vi00;                // offset 0x1A0, size 0x4
    void *xtop;                // offset 0x1A4, size 0x4

    // float (*cluster_nodes)[4]; // offset 0x1A8, size 0x4
    float (*_unknown)[4]; // offset 0x1A8, size 0x4

    u_int fogcol;              // offset 0x1AC, size 0x4
    u_char view_clip_and;      // offset 0x1B0, size 0x1
    u_char view_clip_or;       // offset 0x1B1, size 0x1
    u_char gs_clip_and;        // offset 0x1B2, size 0x1
    u_char gs_clip_or;         // offset 0x1B3, size 0x1
} Model3Junk;

// Chacter_Draw\model3_vu1_n.c
typedef struct Model
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
    u_int reserved_1c;               // offset 0x70, size 0x4
    u_int reserved_1d;               // offset 0x74, size 0x4
    u_int reserved_1e;               // offset 0x78, size 0x4
    u_int reserved_1f;               // offset 0x7C, size 0x4
} Model;

extern ModelCommonWork *model_common_work;

#endif

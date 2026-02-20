#ifndef MODEL_COMMON_H
#define MODEL_COMMON_H

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

ModelCommonWork *model_common_work;

#endif

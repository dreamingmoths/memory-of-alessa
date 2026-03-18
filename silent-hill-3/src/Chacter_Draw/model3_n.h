#ifndef MODEL3_N_H
#define MODEL3_N_H

#include "common.h"
#include "Chacter_Draw/sh3gfw_CharacterOT.h"
#include "Chacter_Draw/model_common.h"

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

// src\Chacter_Draw\model3_n.c
typedef struct HeadEnvPacket
{
    // total size: 0x90
    u_long dmatag_tag; // offset 0x0, size 0x4
    u_int vifcode_0;   // offset 0x8, size 0x4
    u_int vifcode_1;   // offset 0xC, size 0x4
    u_long giftag_tag; // offset 0x10, size 0x4
    u_long giftag_reg; // offset 0x18, size 0x4
    u_long test_d;     // offset 0x20, size 0x4
    u_long test_a;     // offset 0x28, size 0x4
    u_long texa_d;     // offset 0x30, size 0x4
    u_long texa_a;     // offset 0x38, size 0x4
    u_long fba_d;      // offset 0x40, size 0x4
    u_long fba_a;      // offset 0x48, size 0x4
    u_long alpha_d;    // offset 0x50, size 0x4
    u_long alpha_a;    // offset 0x58, size 0x4
    u_long fogcol_d;   // offset 0x60, size 0x4
    u_long fogcol_a;   // offset 0x68, size 0x4

    // maybe?
    u_long unk0x70; // offset 0x70, size 0x4
    u_long unk0x78; // offset 0x78, size 0x4
    u_long unk0x80; // offset 0x80, size 0x4
    u_long unk0x88; // offset 0x88, size 0x4
} HeadEnvPacket;

// src\Chacter_Draw\model3_n.c
typedef struct TailEnvPacket
{
    // total size: 0x30
    u_long dmatag_tag; // offset 0x0, size 0x4
    u_int vifcode_0;   // offset 0x8, size 0x4
    u_int vifcode_1;   // offset 0xC, size 0x4
    u_long giftag_tag; // offset 0x10, size 0x4
    u_long giftag_reg; // offset 0x18, size 0x4
    u_long fba_d;      // offset 0x20, size 0x4
    u_long fba_a;      // offset 0x28, size 0x4
} TailEnvPacket;

// src\Chacter_Draw\model3_n.c
typedef struct EnvPacket
{
    // total size: 0xC0
    struct HeadEnvPacket head_ep; // offset 0x0, size 0x90
    struct TailEnvPacket tail_ep; // offset 0x70, size 0x30
} EnvPacket;

int Model3NSkeletons(void *model_);
s_char *Model3SkeletonStructure(sh_Model *model);
int Model3NClusters(void *model_);
void Model3DrawPre(void);
void sh2_Model_MakeMatrixParams(void);
void SortEnvPrim(void);
int Model3WorkSize(void *model_);
void Model3InitWork(void *model_, void *work_);
struct sceVu0FMATRIX Model3WorkMatrices(void *work_);
float *Model3WorkClusterWeights(void *work_);

// src\Chacter_Draw\model3_n.c
extern Model3Junk model3_junk; // size: 0x1C0

// src\Chacter_Draw\model3_n.c
extern EnvPacket envpacketdata;

/* true externs */
extern int func_001C5C30(void);
extern int func_001CC6F0(void);
extern int func_0025CF20(void);
extern int func_002D7B20(void);
extern int D_00366900;
extern int D_00366908;

#endif

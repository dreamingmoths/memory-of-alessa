#ifndef MODEL3_N_H
#define MODEL3_N_H

#include "sh2_common.h"
#include "model3_vu1_n.h"

typedef struct sh_Model
{
    u_int id;
    u_int revision;
    u_int initial_matrices_offset;
    u_int n_skeletons;
    u_int skeleton_structure_offset;
    u_int n_skeleton_pairs;
    u_int skeleton_pairs_offset;
    u_int default_pcms_offset;
    u_int n_vu1_parts;
    u_int vu1_parts_offset;
    u_int n_vu0_parts;
    u_int vu0_parts_offset;
    u_int n_texture_blocks;
    u_int texture_blocks_offset;
    u_int n_text_poses;
    u_int text_poses_offset;
    u_int text_pos_params_offset;
    u_int n_cluster_nodes;
    u_int cluster_nodes_offset;
    u_int n_clusters;
    u_int clusters_offset;
    u_int n_func_data;
    u_int func_data_offset;
    u_int hit_offset;
    u_int box_offset;
    u_int flag;
    u_int relative_matrices_offset;
    u_int relative_transes_offset;
    void *pTexMAN[4];
} sh_Model;

typedef struct shSkelton
{
    struct shSkelton *next;
    struct shSkelton *parent;
    sceVu0FMATRIX src_m;
    sceVu0FVECTOR src_t;
    sceVu0FMATRIX des_m;
    sceVu0FVECTOR des_t;
    sceVu0FVECTOR axis;
    float theta;
    float xx;
    float yy;
    float zz;
    float xy;
    float yz;
    float zx;
    u_short c_count;
    u_short c_speed;
    char change;
    char reserved;
    char is_key;
    char pad;
    void *untouchable;
} shSkelton;

// E:\work\sh2(CVS全取得)\src\Chacter_Draw\model3_n.c
typedef struct HeadEnvPacket
{
    // total size: 0x70
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
} HeadEnvPacket;

// E:\work\sh2(CVS全取得)\src\Chacter_Draw\model3_n.c
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

// E:\work\sh2(CVS全取得)\src\Chacter_Draw\model3_n.c
typedef struct EnvPacket
{
    // total size: 0xA0
    struct HeadEnvPacket head_ep; // offset 0x0, size 0x70
    struct TailEnvPacket tail_ep; // offset 0x70, size 0x30
} EnvPacket;

// E:\work\sh2(CVS全取得)\src\Chacter_Draw\model3_n.c
struct Model3Junk model3_junk; // size: 0x1C0, address: 0x419DC0
// E:\work\sh2(CVS全取得)\src\Chacter_Draw\model3_n.c
struct EnvPacket envpacketdata; // @ 0x002A9580
// E:\work\sh2(CVS全取得)\src\Chacter_Draw\sh2gfw_CharacterOT.c
__int128 *CharacterOt_RequestPacket(int qwc /* r2 */);
void CharacterOt_Append(u_int depth /* r3 */, __int128 *packet /* r2 */);

s8 *Model3SkeletonStructure(sh_Model *model);
#endif

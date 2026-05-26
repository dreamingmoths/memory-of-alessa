#ifndef SH2GFW_INIT_MODEL_DRAW_DATA_H
#define SH2GFW_INIT_MODEL_DRAW_DATA_H

#include "FilesList/fileslist_bg.h"

typedef struct Part
{
    // total size: 0x90
    u_int size;                              // offset 0x0, size 0x4
    u_int type;                              // offset 0x4, size 0x4
    u_int packet_offset;                     // offset 0x8, size 0x4
    u_int packet_qwc;                        // offset 0xC, size 0x4
    u_int xtop;                              // offset 0x10, size 0x4
    u_int n_cluster_data;                    // offset 0x14, size 0x4
    u_int cluster_data_offset;               // offset 0x18, size 0x4
    u_int n_skeletons;                       // offset 0x1C, size 0x4
    u_int skeletons_offset;                  // offset 0x20, size 0x4
    u_int n_skeleton_pairs;                  // offset 0x24, size 0x4
    u_int skeleton_pairs_offset;             // offset 0x28, size 0x4
    u_int data_skeletons_offset;             // offset 0x2C, size 0x4
    u_int data_skeleton_pairs_offset;        // offset 0x30, size 0x4
    u_int n_textures;                        // offset 0x34, size 0x4
    u_int text_pos_indices_offset;           // offset 0x38, size 0x4
    u_int texture_params_offset;             // offset 0x3C, size 0x4
    u_char shading_type;                     // offset 0x40, size 0x1
    u_char specular_pos;                     // offset 0x41, size 0x1
    u_char equipment_id;                     // offset 0x42, size 0x1
    u_char hoge;                             // offset 0x43, size 0x1
    u_char backclip;                         // offset 0x44, size 0x1
    u_char envmap_param;                     // offset 0x45, size 0x1
    u_char reserved[2];                      // offset 0x46, size 0x2
    float phong_param_a;                     // offset 0x48, size 0x4
    float phong_param_b;                     // offset 0x4C, size 0x4
    float blinn_param;                       // offset 0x50, size 0x4
    u_int padding[3];                        // offset 0x54, size 0xC
    float diffuse[4];                        // offset 0x60, size 0x10
    float ambient[4];                        // offset 0x70, size 0x10
    float specular[4];                       // offset 0x80, size 0x10
} Part;


typedef struct chr_mge_files {
    // total size: 0x14
    fsFileIndex* model_fid; // offset 0x0, size 0x4
    fsFileIndex* anime_fid; // offset 0x4, size 0x4
    fsFileIndex* cluster_fid; // offset 0x8, size 0x4
    fsFileIndex* shadow_fid; // offset 0xC, size 0x4
    int mid; // offset 0x10, size 0x4
} chr_mge_files;

void sh2gfw_srInit_ModelDrawWork(void);

struct sh2gfw_ModelDraw_MAN* sh2gfw_Get_pMD(int chara_id);

int sh2gfw_Check_ModelIsOnMemory(int cid);

int sh2gfw_LoadInit_CharaModelData(chr_mge_files* cdl); // I changed the original DWARF signature 

int sh2gfw_LoadMemorySet_CharaModelData(chr_mge_files* cdl, u_long128** ModelMemBuffer, u_long128** AnimeMemBuffer, u_long128** ClusterMemBuffer, u_long128** Kg1MemBuffer);

int sh2gfw_LOAD_CharaModelData(void);

void sh2gfw_SyncInit_ChacterModelData(void);

int sh2gfw_Cancel_LOADCharaModelData(void);

void sh2gfw_ModelDrawInit_for_BackgroundLoad(int chara_id, void* memhead_model, void* memhead_anime, void* memhead_cluster, void* memhead_kg1);

void* sh2gfw_CreateSubCharacter(int chara_id);

int sh2gfw_Delete_Model_from_CharaID(int chara_id);

void sh2gfw_kari_clear_LM(void);

void sh2gfw_init_CharaModel_TextureData(struct sh2gfw_ModelDraw_MAN* pMD);

#endif

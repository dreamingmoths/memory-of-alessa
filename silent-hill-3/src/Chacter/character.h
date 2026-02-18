/**
 * not a real file, just a place to put all character-related types until we
 * figure out where they go
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "common.h"

struct shBattleArea
{

    float center;
    float radius;
};

struct shClusterAnime
{
    // total size: 0x10
    void *data;           // offset 0x0, size 0x4
    u_char used;          // offset 0x4, size 0x1
    u_char n_clusters;    // offset 0x5, size 0x1
    u_char is_repeat;     // offset 0x6, size 0x1
    u_char frame_updated; // offset 0x7, size 0x1
    int frame_no;         // offset 0x8, size 0x4
    float *weights;       // offset 0xC, size 0x4
};

struct _CL_HITPOLY_HEAD
{
    // total size: 0x10
    u_char kind;    // offset 0x0, size 0x1
    u_char shape;   // offset 0x1, size 0x1
    u_short pad;    // offset 0x2, size 0x2
    u_int weight;   // offset 0x4, size 0x4
    u_int material; // offset 0x8, size 0x4
    int flg;        // offset 0xC, size 0x4
};

struct _CL_VHIT_WALL
{

    float cp[4];
    float nl[4];
    struct _CL_HITPOLY_HEAD *pd;
};

struct _CL_VHIT_CHARA
{

    struct SubCharacter *sc;
    float cp[4];
};

struct _CL_VHIT_RESULT
{

    int kind;
    union /* @anon1 */
    {
        struct _CL_VHIT_WALL wall;
        struct _CL_VHIT_CHARA chara;
    } hobj;
};

struct shBattleInfo
{

    float pos[4];
    float vec[4];
    u_short id;
    u_short kind;
    float dead_timer;
    float damage;
    float shock;
    int atk_result;
    float prev_atk_pos[4];
    struct SubCharacter *target;
    float hp;
    float hp_max;
    float hp_rate;
    u_int status;
    struct shBattleArea look;
    struct shBattleArea feel;
    u_char se;
};

typedef struct _USXY
{
    // total size: 0x4
    u_short x; // offset 0x0, size 0x2
    u_short y; // offset 0x2, size 0x2
} USXY;

typedef struct _SXY
{
    // total size: 0x4
    short x; // offset 0x0, size 0x2
    short y; // offset 0x2, size 0x2
} SXY;

typedef struct _IXY
{
    // total size: 0x8
    int x; // offset 0x0, size 0x4
    int y; // offset 0x4, size 0x4
} IXY;

typedef struct shSkelton
{
    // total size: 0xF0
    struct shSkelton *next;   // offset 0x0, size 0x4
    struct shSkelton *parent; // offset 0x4, size 0x4
    sceVu0FMATRIX src_m;      // offset 0x10, size 0x40
    sceVu0FVECTOR src_t;      // offset 0x50, size 0x10
    sceVu0FMATRIX des_m;      // offset 0x60, size 0x40
    sceVu0FVECTOR des_t;      // offset 0xA0, size 0x10
    sceVu0FVECTOR axis;       // offset 0xB0, size 0x10
    float theta;              // offset 0xC0, size 0x4
    float xx;                 // offset 0xC4, size 0x4
    float yy;                 // offset 0xC8, size 0x4
    float zz;                 // offset 0xCC, size 0x4
    float xy;                 // offset 0xD0, size 0x4
    float yz;                 // offset 0xD4, size 0x4
    float zx;                 // offset 0xD8, size 0x4
    u_short c_count;          // offset 0xDC, size 0x2
    u_short c_speed;          // offset 0xDE, size 0x2
    s_char change;            // offset 0xE0, size 0x1
    char reserved;            // offset 0xE1, size 0x1
    char is_key;              // offset 0xE2, size 0x1
    char pad;                 // offset 0xE3, size 0x1
    void *untouchable;        // offset 0xE4, size 0x4
} shSkelton;

typedef struct _AnimeInfo
{
    // total size: 0xC
    u_short name;  // offset 0x0, size 0x2
    u_short frame; // offset 0x2, size 0x2
    short speed;   // offset 0x4, size 0x2
    u_short start; // offset 0x6, size 0x2
    u_short end;   // offset 0x8, size 0x2
    u_char loop;   // offset 0xA, size 0x1
    char pad;      // offset 0xB, size 0x1
} AnimeInfo;

typedef struct shAnime3d
{
    // total size: 0x90
    struct shSkelton *top;       // offset 0x0, size 0x4
    void *anime;                 // offset 0x4, size 0x4
    void *frame_top;             // offset 0x8, size 0x4
    void *p_anime;               // offset 0xC, size 0x4
    void *p_frame_top;           // offset 0x10, size 0x4
    u_int frame_size;            // offset 0x14, size 0x4
    int total_count;             // offset 0x18, size 0x4
    struct _IXY c_count;         // offset 0x1C, size 0x8
    struct _SXY c_speed;         // offset 0x24, size 0x4
    struct _SXY total_speed;     // offset 0x28, size 0x4
    struct _USXY cur_frame;      // offset 0x2C, size 0x4
    char first_bone_type;        // offset 0x30, size 0x1
    char comp_type;              // offset 0x31, size 0x1
    struct _AnimeInfo *anim_a;   // offset 0x34, size 0x4
    struct _AnimeInfo *anim_b;   // offset 0x38, size 0x4
    sceVu0FVECTOR rot_neck;      // offset 0x40, size 0x10
    sceVu0FVECTOR ot_arms;       // offset 0x50, size 0x10
    sceVu0FVECTOR rot_body_neck; // offset 0x60, size 0x10
    sceVu0FVECTOR rot_body;      // offset 0x70, size 0x10
    float scale;                 // offset 0x80, size 0x4
};

typedef struct
{
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) Vector4;

typedef struct SubCharacter
{

    int index;     // 0x0
    u_int status;  // 0x4
    u_int step;    // 0x8
    u_short kind;  // 0xC
    u_short id;    // 0xE
    u_short unk10; // 0x10
    short unk12;   // 0x12
    u_int sub_st;
    u_int model_type;
    Vector4 pos;
    Vector4 rot;
    Vector4 pos_spd;
    Vector4 rot_spd;
    // struct /* @anon3 */
    // {

    //     float d[4][4];
    // } mat;
    int unk0[8];
    int unk;
    int unk7[7];
    void (*function)(struct SubCharacter *);
    struct shSkelton *sk_top;
    float eye_y;
    float center_y;
    float spd;
    float spd_org;
    struct SubCharacter *pre;
    struct SubCharacter *next;
    float grnd_normal[4];
    float grnd_height;
    Vector4 b_pos;
    Vector4 b_rot;
    int en_first_status;
    int colis_fall_timer;
    struct shBattleInfo battle;
    struct _CL_VHIT_RESULT eye;
    void (*effecter_function)(struct SubCharacter *);
    float spd_y;
    float spd_roty;
    u_char work[4];
    void *enemy_p;
    void *unk_1b0;
    void *unk_1b4;
    void *unk_1bc;
    void *unk_1c0;
    void *unk_1c4;
    void *unk_1c8;
    void *unk_1d0;
    void *unk_1d4;
} SubCharacter;

typedef struct sh3gfw_ModelDraw_MAN
{
    u_int chara_id;
    SubCharacter *testSubChar;
    void *unk0x8;
    void *unk0xc;
    void *Model_Head;
    void *pModel_Header;
    void *sh_Model;
    void *pAnime;
    void *pCluster;
    void *pKg1Work;
    short allnum;
    short nowtex;
    u_short TB_change_VU1num;
    u_short TB_change_VU1now;
    u_short TB_change_VU1[4];
    u_short TB_index_VU1[4];
    u_short TB_change_VU0num;
    u_short TB_change_VU0now;
    u_short TB_change_VU0[2];
    u_short TB_index_VU0[2];
    int chr_slotid[6];
    int chr_cid[6];
    int d1cid;
    int d2c1d;
    void *pTexMAN[6];
} sh3gfw_ModelDraw_MAN;

typedef struct SubCharacterDisp
{
    // total size: 0x340
    struct SubCharacter sc;               // offset 0x0, size 0x1F0
    struct shAnime3d anime2;              // offset 0x1F0, size 0x90
    struct shAnime3d anime;               // offset 0x280, size 0x90
    struct shClusterAnime *cluster_anime; // offset 0x310, size 0x4
    void *models[3];                      // offset 0x314, size 0xC
    void *work;                           // offset 0x320, size 0x4
    void *data;                           // offset 0x324, size 0x4
    u_int model_adr;                      // offset 0x328, size 0x4
    u_int anime_adr;                      // offset 0x32C, size 0x4
    u_int clani_adr;                      // offset 0x330, size 0x4
    void *anime_list;                     // offset 0x334, size 0x4
    void *clani_list;                     // offset 0x338, size 0x4
} SubCharacterDisp;

#endif
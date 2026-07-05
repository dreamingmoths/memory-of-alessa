/**
 * not a real file, just a place to put all character-related types until we
 * figure out where they go
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "common.h"
#include "libvu0.h"
#include "eetypes.h"
#include "shared/Chacter_Draw/clani.h"

typedef struct shBattleArea {

    float center;
    float radius;
} shBattleArea;


typedef struct _CL_HITPOLY_HEAD {
    // total size: 0x10
    u_char kind;    // offset 0x0, size 0x1
    u_char shape;   // offset 0x1, size 0x1
    u_short pad;    // offset 0x2, size 0x2
    u_int weight;   // offset 0x4, size 0x4
    u_int material; // offset 0x8, size 0x4
    int flg;        // offset 0xC, size 0x4
} CL_HITPOLY_HEAD;

typedef struct _CL_VHIT_WALL {

    sceVu0FVECTOR cp;
    sceVu0FVECTOR nl;
    struct _CL_HITPOLY_HEAD* pd;
} CL_VHIT_WALL;

typedef struct _CL_VHIT_CHARA {

    struct SubCharacter* sc;
    float cp[4];
} CL_VHIT_CHARA;

typedef struct _CL_VHIT_RESULT {

    int kind;
    union /* @anon1 */
    {
        CL_VHIT_WALL wall;
        CL_VHIT_CHARA chara;
    } hobj;
} CL_VHIT_RESULT;

/**
 * @sh3: this struct appears to have the same size as its sh2 counterpart.
 * confirmed by function at `0012f030`.
 */

typedef struct shBattleInfo {
    // total size: 0x80
    u_char unk0[0x70];
    int status;
    u_char unk74[0xC];
} shBattleInfo;

/**
 * @sh3 parent & next were swapped since the sh2 proto.
 * also, 0x10 bytes were removed, though it's unclear which ones
 */
typedef struct shSkelton {
    // total size: 0xE0
    struct shSkelton* parent; // offset 0x0, size 0x4
    struct shSkelton* next;   // offset 0x4, size 0x4
    Matrix4 src_m;              // offset 0x10, size 0x40
    Vector4 src_t;              // offset 0x50, size:0x10
    Matrix4 des_m;              // offset 0x60, size:0x40
    Vector4 des_t;              // offset 0xA0, size:0x10
    Vector4 axis;               // offset 0xB0, size:0x10
    float theta;                // offset 0xC0, size 0x4
    float xx;                   // offset 0xC4, size 0x4
    float yy;                   // offset 0xC8, size 0x4
    float zz;                   // offset 0xCC, size 0x4
    int unkD0;                  // offset 0xD0, size 0x4
    void* untouchable;          // offset 0xD4, size 0x4
} shSkelton;

typedef struct shAnime3d {
    // total size: 0x90
    struct shSkelton* top;       // offset 0x0, size 0x4
    void* anime;                 // offset 0x4, size 0x4
    void* frame_top;             // offset 0x8, size 0x4
    void* p_anime;               // offset 0xC, size 0x4
    void* p_frame_top;           // offset 0x10, size 0x4
    u_int frame_size;            // offset 0x14, size 0x4
    int total_count;             // offset 0x18, size 0x4
    struct _IXY c_count;         // offset 0x1C, size 0x8
    struct _SXY c_speed;         // offset 0x24, size 0x4
    struct _SXY total_speed;     // offset 0x28, size 0x4
    struct _USXY cur_frame;      // offset 0x2C, size 0x4
    char first_bone_type;        // offset 0x30, size 0x1
    char comp_type;              // offset 0x31, size 0x1
    struct _AnimeInfo* anim_a;   // offset 0x34, size 0x4
    struct _AnimeInfo* anim_b;   // offset 0x38, size 0x4
    sceVu0FVECTOR rot_neck;      // offset 0x40, size 0x10
    sceVu0FVECTOR ot_arms;       // offset 0x50, size 0x10
    sceVu0FVECTOR rot_body_neck; // offset 0x60, size 0x10
    sceVu0FVECTOR rot_body;      // offset 0x70, size 0x10
    float scale;                 // offset 0x80, size 0x4
} shAnime3d;

/**
 * size confirmed by `shQzero` call by `func_001691c0`.
 */
typedef struct CharaOptions {
    // total size: 0x40
    u_short unk0;
    u_short unk2;
    u_short kind;
    u_short id;
    u_short unk8;
    Vector4 pos_10;
    Vector4 rot_20;
    u_int status_30;
    u_int unk34[0xC];
} CharaOptions;

typedef struct SubCharacter {

    /* 0x0 */   int index;
    /* 0x4 */   u_int status;
    /* 0x8 */   u_int step;
    /* 0xC */   u_short kind;
    /* 0xE */   u_short id;
    /* 0x10 */  u_short unk10;
    /* 0x12 */  short unk12;
    /* 0x14 */  u_int sub_st;
    /* 0x16 */  u_int model_type;
    /* 0x20 */  Vector4 pos;
    /* 0x30 */  Vector4 rot;
    /* 0x40 */  Vector4 pos_spd;
    /* 0x50 */  Vector4 rot_spd;
    /* 0x60 */  int unk60[8];
    /* 0x80 */  shSkelton* sk80;
    /* 0x84 */  int unk84[7];
    /* 0xA0 */  void (*function)(struct SubCharacter*);
    /* 0xA4 */  struct shSkelton* sk_top;
    /* 0xA8 */  int unkA8[4];
    /* 0xB8 */  struct SubCharacter* pre;
    /* 0xBC */  struct SubCharacter* next;
    /* 0xC0 */  float unkC0[4];
    /* 0xD0 */  float unkD0[4];
    /* 0xE0 */  float unkE0[4];
    /* 0xF0 */  float unkF0[4];
    /* 0x100 */ u_char unk100[0x50];
    /* 0x150 */ shBattleInfo battle;
} SubCharacter;

typedef struct sh3gfw_ModelDraw_MAN {
    u_int chara_id;
    SubCharacter* testSubChar;
    void* unk0x8;
    void* unk0xc;
    void* Model_Head;
    void* pModel_Header;
    void* sh_Model;
    void* pAnime;
    void* pCluster;
    void* pKg1Work;
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
    void* pTexMAN[6];
} sh3gfw_ModelDraw_MAN;

typedef struct SubCharacterDisp {
    // total size: 0x320
    struct SubCharacter sc;               // offset 0x0, size 0x1D0
    struct shAnime3d anime2;              // offset 0x1D0, size 0x90
    struct shAnime3d anime;               // offset 0x260, size 0x90
    struct shClusterAnime* cluster_anime; // offset 0x2F0, size 0x4
    void* models[3];                      // offset 0x2F4, size 0xC
    void* work;                           // offset 0x300, size 0x4
    void* data;                           // offset 0x304, size 0x4
    u_int model_adr;                      // offset 0x308, size 0x4
    u_int anime_adr;                      // offset 0x30C, size 0x4
    u_int clani_adr;                      // offset 0x310, size 0x4
    void* anime_list;                     // offset 0x314, size 0x4
    void* clani_list;                     // offset 0x318, size 0x4
    u_char pad[0x4];                      // offset 0x31C, size 0x4
} SubCharacterDisp;

#define SH_CHARACTER_WORK_COUNT 32
/**
 * @sh3: mostly same, however `total` was changed from a char to an int, and the
 * `SubCharacter` struct is 0x20 bytes smaller.
 */
typedef struct shCharacterAll {
    // total size: 0x6410
    SubCharacterDisp work[SH_CHARACTER_WORK_COUNT]; // offset 0x0, size 0x6400
    SubCharacterDisp* free;    // offset 0x6400, size 0x4
    SubCharacter* head;        // offset 0x6404, size 0x4
    SubCharacter* player;      // offset 0x6408, size 0x4
    int total;                 // offset 0x640C, size 0x1
} shCharacterAll;

#endif // CHARACTER_H

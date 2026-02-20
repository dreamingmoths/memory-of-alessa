#ifndef CHARACTER_H
#define CHARACTER_H

#include "sh2_common.h"

typedef struct shBattleArea
{
    // total size: 0x8
    float center; // offset 0x0, size 0x4
    float radius; // offset 0x4, size 0x4
} shBattleArea;

typedef struct _CL_HITPOLY_HEAD
{
    // total size: 0x10
    u_char kind;    // offset 0x0, size 0x1
    u_char shape;   // offset 0x1, size 0x1
    u_short pad;    // offset 0x2, size 0x2
    u_int weight;   // offset 0x4, size 0x4
    u_int material; // offset 0x8, size 0x4
    int flg;        // offset 0xC, size 0x4
} CL_HITPOLY_HEAD;

typedef struct
{
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) Vector4;

typedef struct _CL_VHIT_WALL
{
    // total size: 0x30
    Vector4 cp;                  // offset 0x0, size 0x10
    Vector4 nl;                  // offset 0x10, size 0x10
    struct _CL_HITPOLY_HEAD *pd; // offset 0x20, size 0x4
} CL_VHIT_WALL;

typedef struct _CL_VHIT_CHARA
{
    // total size: 0x20
    struct SubCharacter *sc; // offset 0x0, size 0x4
    float cp[4];             // offset 0x10, size 0x10
} CL_VHIT_CHARA;

typedef struct _CL_VHIT_RESULT
{
    // total size: 0x40
    int kind; // offset 0x0, size 0x4
    union     /* @anon1 */
    {
        struct _CL_VHIT_WALL wall;   // offset 0x0, size 0x30
        struct _CL_VHIT_CHARA chara; // offset 0x0, size 0x20
    } hobj;                          // offset 0x10, size 0x30
} CL_VHIT_RESULT;

typedef struct shBattleInfo
{
    // total size: 0x80
    Vector4 pos;                 // offset 0x0, size 0x10
    Vector4 vec;                 // offset 0x10, size 0x10
    u_short id;                  // offset 0x20, size 0x2
    u_short kind;                // offset 0x22, size 0x2
    float dead_timer;            // offset 0x24, size 0x4
    float damage;                // offset 0x28, size 0x4
    float shock;                 // offset 0x2C, size 0x4
    int atk_result;              // offset 0x30, size 0x4
    Vector4 prev_atk_pos;        // offset 0x40, size 0x10
    struct SubCharacter *target; // offset 0x50, size 0x4
    float hp;                    // offset 0x54, size 0x4
    float hp_max;                // offset 0x58, size 0x4
    float hp_rate;               // offset 0x5C, size 0x4
    u_int status;                // offset 0x60, size 0x4
    struct shBattleArea look;    // offset 0x64, size 0x8
    struct shBattleArea feel;    // offset 0x6C, size 0x8
    u_char se;                   // offset 0x74, size 0x1
} shBattleInfo;

typedef struct SubCharacter
{
    int index;
    u_int status;
    u_int sub_status;
    u_int sub_st;
    short kind;
    short id;
    u_int step;
    u_int model_type;
    Vector4 pos;
    Vector4 rot;
    Vector4 pos_spd;
    Vector4 rot_spd;
    sceVu0FMATRIX mat;
    struct shSkelton *sk_top;
    float eye_y;
    float center_y;
    float spd;
    float spd_org;
    float spd_y;
    float spd_roty;
    Vector4 grnd_normal;
    float grnd_height;
    Vector4 b_pos;
    Vector4 b_rot;
    int en_first_status;
    int colis_fall_timer;
    shBattleInfo battle;
    struct _CL_VHIT_RESULT eye;
    void (*function)(struct SubCharacter *);
    void (*effecter_function)(struct SubCharacter *);
    struct SubCharacter *pre;
    struct SubCharacter *next;
    u_char work[4];
    void *enemy_p;
} SubCharacter;

typedef struct shClusterAnime
{
    // total size: 0x10
    void *data;           // offset 0x0, size 0x4
    u_char used;          // offset 0x4, size 0x1
    u_char n_clusters;    // offset 0x5, size 0x1
    u_char is_repeat;     // offset 0x6, size 0x1
    u_char frame_updated; // offset 0x7, size 0x1
    int frame_no;         // offset 0x8, size 0x4
    float *weights;       // offset 0xC, size 0x4
} shClusterAnime;
typedef struct sh2gfw_ModelDraw_MAN
{
    u_int chara_id;
    SubCharacter *testSubChar;
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
} sh2gfw_ModelDraw_MAN;

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
    Vector4 src_t;            // offset 0x50, size 0x10
    sceVu0FMATRIX des_m;      // offset 0x60, size 0x40
    Vector4 des_t;            // offset 0xA0, size 0x10
    Vector4 axis;             // offset 0xB0, size 0x10
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
    struct shSkelton *top;     // offset 0x0, size 0x4
    void *anime;               // offset 0x4, size 0x4
    void *frame_top;           // offset 0x8, size 0x4
    void *p_anime;             // offset 0xC, size 0x4
    void *p_frame_top;         // offset 0x10, size 0x4
    u_int frame_size;          // offset 0x14, size 0x4
    int total_count;           // offset 0x18, size 0x4
    struct _IXY c_count;       // offset 0x1C, size 0x8
    struct _SXY c_speed;       // offset 0x24, size 0x4
    struct _SXY total_speed;   // offset 0x28, size 0x4
    struct _USXY cur_frame;    // offset 0x2C, size 0x4
    char first_bone_type;      // offset 0x30, size 0x1
    char comp_type;            // offset 0x31, size 0x1
    struct _AnimeInfo *anim_a; // offset 0x34, size 0x4
    struct _AnimeInfo *anim_b; // offset 0x38, size 0x4
    Vector4 rot_neck;          // offset 0x40, size 0x10
    Vector4 ot_arms;           // offset 0x50, size 0x10
    Vector4 rot_body_neck;     // offset 0x60, size 0x10
    Vector4 rot_body;          // offset 0x70, size 0x10
    float scale;               // offset 0x80, size 0x4
};

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

// E:\work\sh2(CVS全取得)\src\Chacter\chara_saveinfo.c
typedef struct shCharacterAll
{
    // total size: 0x6810
    struct SubCharacterDisp work[32]; // offset 0x0, size 0x6800
    struct SubCharacterDisp *free;    // offset 0x6800, size 0x4
    struct SubCharacter *head;        // offset 0x6804, size 0x4
    struct SubCharacter *player;      // offset 0x6808, size 0x4
    char total;                       // offset 0x680C, size 0x1
} shCharacterAll;

// E:\work\sh2(CVS全取得)\src\Chacter\m3_ty23.c
typedef struct EnPATH_DATA
{
    // total size: 0x10
    float angle;     // offset 0x0, size 0x4
    float markangle; // offset 0x4, size 0x4
    float dist;      // offset 0x8, size 0x4
    s_char step;     // offset 0xC, size 0x1
    s_char deadend;  // offset 0xD, size 0x1
    short timer;     // offset 0xE, size 0x2
} EnPATH_DATA;

// E:\work\sh2(CVS全取得)\src\Chacter\m3_ty23.c
typedef struct EnAMBUSH_DATA
{
    // total size: 0x1C
    float pl_x_min; // offset 0x0, size 0x4
    float pl_z_min; // offset 0x4, size 0x4
    float pl_x_max; // offset 0x8, size 0x4
    float pl_z_max; // offset 0xC, size 0x4
    float pos_x;    // offset 0x10, size 0x4
    float pos_z;    // offset 0x14, size 0x4
    float dir;      // offset 0x18, size 0x4
} EnAMBUSH_DATA;

// E:\work\sh2(CVS全取得)\src\Chacter\m3_ty23.c
typedef struct EnSCU_DATA
{
    // total size: 0x30
    float stpos[4];               // offset 0x0, size 0x10
    float target[4];              // offset 0x10, size 0x10
    struct EnAMBUSH_DATA *ambush; // offset 0x20, size 0x4
    int count;                    // offset 0x24, size 0x4
    s_char dc;                    // offset 0x28, size 0x1
    s_char dcm;                   // offset 0x29, size 0x1
} EnSCU_DATA;

// E:\work\sh2(CVS全取得)\src\Chacter\m3_ty23.c
typedef struct EnMKN_DATA
{
    // total size: 0x30
    float stpos[4];  // offset 0x0, size 0x10
    float target[4]; // offset 0x10, size 0x10
    void *tp;        // offset 0x20, size 0x4
    float fall;      // offset 0x24, size 0x4
    short frame;     // offset 0x28, size 0x2
    s_char dc;       // offset 0x2A, size 0x1
    s_char dcm;      // offset 0x2B, size 0x1
} EnMKN_DATA;

// E:\work\sh2(CVS全取得)\src\Chacter\m3_ty23.c
typedef struct EnCOMMUNICATION
{
    // total size: 0x20
    float pos[4]; // offset 0x0, size 0x10
    int kind;     // offset 0x10, size 0x4
    int type;     // offset 0x14, size 0x4
    int time;     // offset 0x18, size 0x4
    float dist;   // offset 0x1C, size 0x4
} EnCOMMUNICATION;

// E:\work\sh2(CVS全取得)\src\Chacter\m3_ty23.c
typedef struct EnTYU_DATA
{
    // total size: 0x20
    float point[4];                // offset 0x0, size 0x10
    struct EnCOMMUNICATION *tcomm; // offset 0x10, size 0x4
    int near_count;                // offset 0x14, size 0x4
    float dist;                    // offset 0x18, size 0x4
    short count;                   // offset 0x1C, size 0x2
    s_char moves;                  // offset 0x1E, size 0x1
} EnTYU_DATA;

// E:\work\sh2(CVS全取得)\src\Chacter\m3_ty23.c
typedef struct EnRED_DATA
{
    // total size: 0xC
    int attack_count; // offset 0x0, size 0x4
    int boss_timer;   // offset 0x4, size 0x4
    void *tp;         // offset 0x8, size 0x4
} EnRED_DATA;

// E:\work\sh2(CVS全取得)\src\Chacter\m3_ty23.c
typedef struct EnONI_DATA
{
    // total size: 0x10
    s_char id;    // offset 0x0, size 0x1
    s_char check; // offset 0x1, size 0x1
    s_char warp;  // offset 0x2, size 0x1
    short timer2; // offset 0x4, size 0x2
    void *other;  // offset 0x8, size 0x4
    void *tp;     // offset 0xC, size 0x4
} EnONI_DATA;

// E:\work\sh2(CVS全取得)\src\Chacter\m3_ty23.c
typedef struct EnNSE_DATA
{
    // total size: 0xC
    float speed;  // offset 0x0, size 0x4
    float tspeed; // offset 0x4, size 0x4
    s_char signs; // offset 0x8, size 0x1
    s_char count; // offset 0x9, size 0x1
    s_char dc;    // offset 0xA, size 0x1
    s_char dcm;   // offset 0xB, size 0x1
} EnNSE_DATA;

// E:\work\sh2(CVS全取得)\src\Chacter\m3_ty23.c
typedef struct EnIKE_DATA
{
    // total size: 0x20
    float handpos[4];  // offset 0x0, size 0x10
    float swing;       // offset 0x10, size 0x4
    int near_count;    // offset 0x14, size 0x4
    float dist;        // offset 0x18, size 0x4
    s_char direc;      // offset 0x1C, size 0x1
    s_char signs;      // offset 0x1D, size 0x1
    s_char count;      // offset 0x1E, size 0x1
    s_char pipe_count; // offset 0x1F, size 0x1
} EnIKE_DATA;

// E:\work\sh2(CVS全取得)\src\Chacter\m3_ty23.c
typedef struct EnPAP_DATA
{
    // total size: 0x20
    float target[4]; // offset 0x0, size 0x10
    s_char dc;       // offset 0x10, size 0x1
    s_char dcm;      // offset 0x11, size 0x1
    s_char signs;    // offset 0x12, size 0x1
    s_char count;    // offset 0x13, size 0x1
} EnPAP_DATA;

// E:\work\sh2(CVS全取得)\src\Chacter\m3_ty23.c
typedef struct EnEDB_DATA
{
    // total size: 0x30
    float target[4]; // offset 0x0, size 0x10
    float rot;       // offset 0x10, size 0x4
    float arot;      // offset 0x14, size 0x4
    float speed;     // offset 0x18, size 0x4
    s_char bullet;   // offset 0x1C, size 0x1
    s_char mark[3];  // offset 0x1D, size 0x3
    s_char mark_n;   // offset 0x20, size 0x1
    s_char turn;     // offset 0x21, size 0x1
    s_char afford;   // offset 0x22, size 0x1
    s_char ccount;   // offset 0x23, size 0x1
    s_char pcount;   // offset 0x24, size 0x1
} EnEDB_DATA;

// E:\work\sh2(CVS全取得)\src\Chacter\m3_ty23.c
typedef struct EnARM_DATA
{
    // total size: 0x30
    float hand_pos[4]; // offset 0x0, size 0x10
    float old_pos[4];  // offset 0x10, size 0x10
    int near_count;    // offset 0x20, size 0x4
    float dist;        // offset 0x24, size 0x4
    s_char arm;        // offset 0x28, size 0x1
    s_char attack;     // offset 0x29, size 0x1
    s_char scount;     // offset 0x2A, size 0x1
    s_char signs;      // offset 0x2B, size 0x1
    s_char count;      // offset 0x2C, size 0x1
    s_char dir;        // offset 0x2D, size 0x1
} EnARM_DATA;

// E:\work\sh2(CVS全取得)\src\Chacter\m3_ty23.c
typedef struct EnBOS_DATA
{
    // total size: 0x40
    float target[4];  // offset 0x0, size 0x10
    void *insect_dp;  // offset 0x10, size 0x4
    int near_count;   // offset 0x14, size 0x4
    float dist;       // offset 0x18, size 0x4
    float move_speed; // offset 0x1C, size 0x4
    float rot_speed;  // offset 0x20, size 0x4
    float rot_add;    // offset 0x24, size 0x4
    float y_speed;    // offset 0x28, size 0x4
    int mode;         // offset 0x2C, size 0x4
    int end_count;    // offset 0x30, size 0x4
    s_char signs;     // offset 0x34, size 0x1
    s_char count;     // offset 0x35, size 0x1
} EnBOS_DATA;

// E:\work\sh2(CVS全取得)\src\Chacter\m3_ty23.c
typedef struct EnNIK_DATA
{
    // total size: 0x20
    float swing[4]; // offset 0x0, size 0x10
    float acc[4];   // offset 0x10, size 0x10
} EnNIK_DATA;

// E:\work\sh2(CVS全取得)\src\Chacter\m3_ty23.c
typedef struct EnINS_DATA
{
    // total size: 0x40
    float view_rot[4]; // offset 0x0, size 0x10
    float rot_add[4];  // offset 0x10, size 0x10
    void *leader;      // offset 0x20, size 0x4
    float def_speed;   // offset 0x24, size 0x4
    float move_speed;  // offset 0x28, size 0x4
    float speed_add;   // offset 0x2C, size 0x4
    float rot_speed;   // offset 0x30, size 0x4
    float y_speed;     // offset 0x34, size 0x4
    float twin_dist;   // offset 0x38, size 0x4
    float dist_add;    // offset 0x3C, size 0x4
} EnINS_DATA;

// E:\work\sh2(CVS全取得)\src\Chacter\m3_ty23.c
typedef struct EnLOCAL_DATA
{
    // total size: 0xE0
    s_char kind;              // offset 0x0, size 0x1
    s_char kind2;             // offset 0x1, size 0x1
    s_char mlv;               // offset 0x2, size 0x1
    s_char slv;               // offset 0x3, size 0x1
    s_char sslv;              // offset 0x4, size 0x1
    s_char type;              // offset 0x5, size 0x1
    u_char weight;            // offset 0x6, size 0x1
    s_char lie;               // offset 0x7, size 0x1
    s_char d_count;           // offset 0x8, size 0x1
    s_char last_atk;          // offset 0x9, size 0x1
    s_char anim;              // offset 0xA, size 0x1
    u_char anim_loop;         // offset 0xB, size 0x1
    short anim_s;             // offset 0xC, size 0x2
    u_int flag;               // offset 0x10, size 0x4
    int anim_n;               // offset 0x14, size 0x4
    int anim_step;            // offset 0x18, size 0x4
    struct SubCharacter *scp; // offset 0x1C, size 0x4
    struct EnPATH_DATA path;  // offset 0x20, size 0x10
    float vec[4];             // offset 0x30, size 0x10
    float endurance;          // offset 0x40, size 0x4
    float endurance_max;      // offset 0x44, size 0x4
    float hb_x;               // offset 0x48, size 0x4
    float hb_z;               // offset 0x4C, size 0x4
    float hb_s;               // offset 0x50, size 0x4
    float tx;                 // offset 0x54, size 0x4
    float tz;                 // offset 0x58, size 0x4
    float tx2;                // offset 0x5C, size 0x4
    float tz2;                // offset 0x60, size 0x4
    float trx;                // offset 0x64, size 0x4
    float trz;                // offset 0x68, size 0x4
    float size;               // offset 0x6C, size 0x4
    float new_size;           // offset 0x70, size 0x4
    float tall;               // offset 0x74, size 0x4
    float new_tall;           // offset 0x78, size 0x4
    float center_y;           // offset 0x7C, size 0x4
    float new_center;         // offset 0x80, size 0x4
    float eye_y;              // offset 0x84, size 0x4
    float new_eye;            // offset 0x88, size 0x4
    float p_dist;             // offset 0x8C, size 0x4
    float radio;              // offset 0x90, size 0x4
    int timer;                // offset 0x94, size 0x4
    int sound_wait;           // offset 0x98, size 0x4
    int randseed;             // offset 0x9C, size 0x4
    union
    {                          // inferred
        struct EnSCU_DATA scu; // offset 0xA0, size 0x30
        struct EnMKN_DATA mkn; // offset 0xA0, size 0x30
        struct EnTYU_DATA tyu; // offset 0xA0, size 0x20
        struct EnRED_DATA red; // offset 0xA0, size 0xC
        struct EnONI_DATA oni; // offset 0xA0, size 0x10
        struct EnNSE_DATA nse; // offset 0xA0, size 0xC
        struct EnIKE_DATA ike; // offset 0xA0, size 0x20
        struct EnPAP_DATA pap; // offset 0xA0, size 0x20
        struct EnEDB_DATA edb; // offset 0xA0, size 0x30
        struct EnARM_DATA arm; // offset 0xA0, size 0x30
        struct EnBOS_DATA bos; // offset 0xA0, size 0x40
        struct EnNIK_DATA nik; // offset 0xA0, size 0x20
        struct EnINS_DATA ins; // offset 0xA0, size 0x40
    };
} EnLOCAL_DATA;

// chara_saveinfo.c
typedef struct _CI_SubCharacter
{
    // total size: 0xA0
    u_int status;         // offset 0x0, size 0x4
    u_int sub_status;     // offset 0x4, size 0x4
    u_int sub_st;         // offset 0x8, size 0x4
    short kind;           // offset 0xC, size 0x2
    short id;             // offset 0xE, size 0x2
    Vector4 pos;          // offset 0x10, size 0x10
    Vector4 rot;          // offset 0x20, size 0x10
    Vector4 pos_spd;      // offset 0x30, size 0x10
    Vector4 ot_spd;       // offset 0x40, size 0x10
    Vector4 b_pos;        // offset 0x50, size 0x10
    Vector4 b_rot;        // offset 0x60, size 0x10
    int en_first_status;  // offset 0x70, size 0x4
    float eye_y;          // offset 0x74, size 0x4
    float center_y;       // offset 0x78, size 0x4
    float spd;            // offset 0x7C, size 0x4
    float spd_org;        // offset 0x80, size 0x4
    float spd_y;          // offset 0x84, size 0x4
    float spd_roty;       // offset 0x88, size 0x4
    float battle_hp;      // offset 0x8C, size 0x4
    float battle_hp_max;  // offset 0x90, size 0x4
    float battle_hp_rate; // offset 0x94, size 0x4
    u_int battle_status;  // offset 0x98, size 0x4
} CI_SubCharacter;

typedef enum _JAMES_LOWER_STATUS
{
    JMS_ST_L_STAND = 0,
    JMS_ST_L_RELAX = 1,
    JMS_ST_L_ALERT = 2,
    JMS_ST_L_TIRED = 3,
    JMS_ST_L_READY = 4,
    JMS_ST_L_READYOFF = 5,
    JMS_ST_L_LROUND = 6,
    JMS_ST_L_RROUND = 7,
    JMS_ST_L_BACK = 8,
    JMS_ST_L_WALK = 9,
    JMS_ST_L_LSWALK = 10,
    JMS_ST_L_RSWALK = 11,
    JMS_ST_L_RUN1 = 12,
    JMS_ST_L_RUN2 = 13,
    JMS_ST_L_RUN3 = 14,
    JMS_ST_L_LSRUN = 15,
    JMS_ST_L_RSRUN = 16,
    JMS_ST_L_WALL_F = 17,
    JMS_ST_L_LTURN = 18,
    JMS_ST_L_RTURN = 19,
    JMS_ST_L_JUMP = 20,
    JMS_ST_L_GUARD = 21,
    JMS_ST_L_LSTEP = 22,
    JMS_ST_L_RSTEP = 23,
    JMS_ST_L_FALL = 24,
    JMS_ST_L_DAMAGE = 25,
    JMS_ST_L_HOLD = 26,
    JMS_ST_L_RELEASE = 27,
    JMS_ST_L_ATTACK = 28,
    JMS_ST_L_KICK = 29,
    JMS_ST_L_TO_STAND = 30,
    JMS_ST_L_EVENT = 31,
} E_JAMES_LOWER_STATUS;

typedef enum _JAMES_UPPER_STATUS
{
    JMS_ST_U_STAND = 0,
    JMS_ST_U_RELAX = 1,
    JMS_ST_U_ALERT = 2,
    JMS_ST_U_TIRED = 3,
    JMS_ST_U_READY = 4,
    JMS_ST_U_READYOFF = 5,
    JMS_ST_U_LROUND = 6,
    JMS_ST_U_RROUND = 7,
    JMS_ST_U_BACK = 8,
    JMS_ST_U_WALK = 9,
    JMS_ST_U_LSWALK = 10,
    JMS_ST_U_RSWALK = 11,
    JMS_ST_U_RUN1 = 12,
    JMS_ST_U_RUN2 = 13,
    JMS_ST_U_RUN3 = 14,
    JMS_ST_U_LSRUN = 15,
    JMS_ST_U_RSRUN = 16,
    JMS_ST_U_WALL_F = 17,
    JMS_ST_U_LTURN = 18,
    JMS_ST_U_RTURN = 19,
    JMS_ST_U_JUMP = 20,
    JMS_ST_U_GUARD = 21,
    JMS_ST_U_LSTEP = 22,
    JMS_ST_U_RSTEP = 23,
    JMS_ST_U_FALL = 24,
    JMS_ST_U_DAMAGE = 25,
    JMS_ST_U_HOLD = 26,
    JMS_ST_U_RELEASE = 27,
    JMS_ST_U_ATTACK = 28,
    JMS_ST_U_KICK = 29,
    JMS_ST_U_TO_STAND = 30,
    JMS_ST_U_EVENT = 31,
} E_JAMES_UPPER_STATUS;

typedef struct _CL_HITPOLY_COLUMN
{
    // total size: 0x30
    u_char kind;    // offset 0x0, size 0x1
    u_char shape;   // offset 0x1, size 0x1
    u_short pad;    // offset 0x2, size 0x2
    u_int weight;   // offset 0x4, size 0x4
    u_int material; // offset 0x8, size 0x4
    int flg;        // offset 0xC, size 0x4
    float p[2][4];  // offset 0x10, size 0x20
} s_CL_HITPOLY_COLUMN;

// E:\work\sh2(CVS全取得)\src\Event\stage\stg_end_dog.c
typedef struct PAD_3D
{
    // total size: 0x6
    s_char round_way; // offset 0x0, size 0x1
    u_char reserved1; // offset 0x1, size 0x1
    u_char lslide;    // offset 0x2, size 0x1
    u_char rslide;    // offset 0x3, size 0x1
    u_char lturn180;  // offset 0x4, size 0x1
    u_char rturn180;  // offset 0x5, size 0x1
} PAD_3D;

// E:\work\sh2(CVS全取得)\src\Event\stage\stg_end_dog.c
typedef struct PAD_2D
{
    // total size: 0x8
    u_char pow;          // offset 0x0, size 0x1
    u_char lower_motion; // offset 0x1, size 0x1
    float dir;           // offset 0x4, size 0x4
} PAD_2D;

// E:\work\sh2(CVS全取得)\src\Event\stage\stg_end_dog.c
typedef struct PAD_INFO
{
    // total size: 0x20
    u_char action;     // offset 0x0, size 0x1
    u_char dash;       // offset 0x1, size 0x1
    u_char attack0;    // offset 0x2, size 0x1
    u_char attack1;    // offset 0x3, size 0x1
    u_char attack2;    // offset 0x4, size 0x1
    u_char menu;       // offset 0x5, size 0x1
    u_char hold;       // offset 0x6, size 0x1
    u_char search;     // offset 0x7, size 0x1
    u_char map;        // offset 0x8, size 0x1
    u_char light_ : 4; // offset 0x9, size 0x1
    u_char light : 4;  // offset 0x9, size 0x1
    u_char l_button;   // offset 0xA, size 0x1
    u_char r_button;   // offset 0xB, size 0x1
    s_char lstickX;    // offset 0xC, size 0x1
    s_char lstickY;    // offset 0xD, size 0x1
    s_char rstickX;    // offset 0xE, size 0x1
    s_char rstickY;    // offset 0xF, size 0x1
    u_char forward;    // offset 0x10, size 0x1
    u_char backward;   // offset 0x11, size 0x1
    u_char lround;     // offset 0x12, size 0x1
    u_char rround;     // offset 0x13, size 0x1
    u_char skip;       // offset 0x14, size 0x1
    u_char pause;      // offset 0x15, size 0x1
    union
    {                        // inferred
        struct PAD_3D pad3d; // offset 0x18, size 0x6
        struct PAD_2D pad2d; // offset 0x18, size 0x8
    };
} PAD_INFO;

// E:\work\sh2(CVS全取得)\src\Event\stage\stg_end_dog.c
typedef struct shPlayerWork
{
    // total size: 0x540
    struct SubCharacter *player;          // offset 0x0, size 0x4
    Vector4 dist_rot;                     // offset 0x10, size 0x10
    Vector4 dist_pos;                     // offset 0x20, size 0x10
    Vector4 pos;                          // offset 0x30, size 0x10
    Vector4 rot;                          // offset 0x40, size 0x10
    float rot_y;                          // offset 0x50, size 0x4
    float inner_to_wall;                  // offset 0x54, size 0x4
    float dist_to_wall;                   // offset 0x58, size 0x4
    float dir_tgt_2d;                     // offset 0x5C, size 0x4
    float dir_now_2d;                     // offset 0x60, size 0x4
    u_char map_mode;                      // offset 0x64, size 0x1
    u_char reserve0;                      // offset 0x65, size 0x1
    u_char step;                          // offset 0x66, size 0x1
    u_char sub_step;                      // offset 0x67, size 0x1
    u_short timer;                        // offset 0x68, size 0x2
    u_short timer2;                       // offset 0x6A, size 0x2
    u_int allbody_now;                    // offset 0x6C, size 0x4
    enum _JAMES_UPPER_STATUS upper_now;   // offset 0x70, size 0x1
    enum _JAMES_LOWER_STATUS lower_now;   // offset 0x71, size 0x1
    u_int allbody_prev;                   // offset 0x74, size 0x4
    enum _JAMES_UPPER_STATUS upper_prev;  // offset 0x78, size 0x1
    enum _JAMES_LOWER_STATUS lower_prev;  // offset 0x79, size 0x1
    u_char event_status_now;              // offset 0x7A, size 0x1
    u_char event_status_prev;             // offset 0x7B, size 0x1
    u_char event_move_mode;               // offset 0x7C, size 0x1
    u_char reserve1;                      // offset 0x7D, size 0x1
    u_int upper_st_flg;                   // offset 0x80, size 0x4
    u_int lower_st_flg;                   // offset 0x84, size 0x4
    u_int u_anime_st_flg;                 // offset 0x88, size 0x4
    u_int l_anime_st_flg;                 // offset 0x8C, size 0x4
    u_int anime_pause;                    // offset 0x90, size 0x4
    u_int act_with_wep;                   // offset 0x94, size 0x4
    float light_vec_inner_rate;           // offset 0x98, size 0x4
    float light_pos_revise[4];            // offset 0xA0, size 0x10
    float light_vec_revise[4];            // offset 0xB0, size 0x10
    float light_pos[4];                   // offset 0xC0, size 0x10
    float light_vec[4];                   // offset 0xD0, size 0x10
    float light_pos_revise_reverse[4];    // offset 0xE0, size 0x10
    float light_vec_revise_reverse[4];    // offset 0xF0, size 0x10
    float light_pos_reverse[4];           // offset 0x100, size 0x10
    float light_vec_reverse[4];           // offset 0x110, size 0x10
    float light_vec_neck[4];              // offset 0x120, size 0x10
    int room_name_prev;                   // offset 0x130, size 0x4
    int room_name_now;                    // offset 0x134, size 0x4
    struct _CL_VHIT_RESULT r_side;        // offset 0x140, size 0x40
    struct _CL_VHIT_RESULT l_side;        // offset 0x180, size 0x40
    struct _CL_VHIT_RESULT foot;          // offset 0x1C0, size 0x40
    struct _CL_VHIT_RESULT ft_floor;      // offset 0x200, size 0x40
    struct _CL_VHIT_RESULT r_foot;        // offset 0x240, size 0x40
    struct _CL_VHIT_RESULT l_foot;        // offset 0x280, size 0x40
    struct _CL_HITPOLY_COLUMN column_mov; // offset 0x2C0, size 0x30
    struct _CL_HITPOLY_COLUMN column_atk; // offset 0x2F0, size 0x30
    float col_mov_z_hosei;                // offset 0x320, size 0x4
    float col_atk_z_hosei;                // offset 0x324, size 0x4
    u_char wep_no_hit_floor;              // offset 0x328, size 0x1
    u_char efct_upper;                    // offset 0x329, size 0x1
    u_char light_reverse;                 // offset 0x32A, size 0x1
    u_char water_road;                    // offset 0x32B, size 0x1
    struct PAD_INFO pad[10];              // offset 0x32C, size 0x140
    float rstick_x;                       // offset 0x46C, size 0x4
    float rstick_y;                       // offset 0x470, size 0x4
    float lstick_x;                       // offset 0x474, size 0x4
    float lstick_y;                       // offset 0x478, size 0x4
    float lstick_p;                       // offset 0x47C, size 0x4
    float cam_rot_y[2];                   // offset 0x480, size 0x8
    u_char now_cam_no;                    // offset 0x488, size 0x1
    u_char cam_chg_flg;                   // offset 0x489, size 0x1
    u_char ctrl_unit;                     // offset 0x48A, size 0x1
    u_char ctrl_inputing;                 // offset 0x48B, size 0x1
    u_char se_upper[4];                   // offset 0x48C, size 0x4
    u_char se_foot[4];                    // offset 0x490, size 0x4
    float csaw_se_vol;                    // offset 0x494, size 0x4
    u_char csaw_se_flg;                   // offset 0x498, size 0x1
    u_char d_shock;                       // offset 0x499, size 0x1
    u_char reserve2;                      // offset 0x49A, size 0x1
    u_char strike_splash_flg;             // offset 0x49B, size 0x1
    int event_anime;                      // offset 0x49C, size 0x4
    Vector4 tgt_body_angle;               // offset 0x4A0, size 0x10
    Vector4 tgt_neck_angle;               // offset 0x4B0, size 0x10
    Vector4 tgt_arms_angle;               // offset 0x4C0, size 0x10
    u_char hold_chg[2];                   // offset 0x4D0, size 0x2
    u_char hold_loop[2];                  // offset 0x4D2, size 0x2
    u_char motion_no;                     // offset 0x4D4, size 0x1
    u_char shotgun_dir;                   // offset 0x4D5, size 0x1
    u_char shotgun_prev;                  // offset 0x4D6, size 0x1
    u_char guard_check;                   // offset 0x4D7, size 0x1
    int parts_light;                      // offset 0x4D8, size 0x4
    int parts_rhand;                      // offset 0x4DC, size 0x4
    int parts_lhand;                      // offset 0x4E0, size 0x4
    struct SubCharacter *target;          // offset 0x4E4, size 0x4
    struct SubCharacter *look_tgt;        // offset 0x4E8, size 0x4
    float non_input;                      // offset 0x4EC, size 0x4
    float hugging_gauge;                  // offset 0x4F0, size 0x4
    float running_time;                   // offset 0x4F4, size 0x4
    float muteki_time;                    // offset 0x4F8, size 0x4
    float hp;                             // offset 0x4FC, size 0x4
    float hp_max;                         // offset 0x500, size 0x4
    float hp_recover;                     // offset 0x504, size 0x4
    float shock;                          // offset 0x508, size 0x4
    float spray_time;                     // offset 0x50C, size 0x4
    int tired;                            // offset 0x510, size 0x4
    int tired_max;                        // offset 0x514, size 0x4
    int spirit;                           // offset 0x518, size 0x4
    struct SubCharacter *enemy_liedown;   // offset 0x51C, size 0x4
    u_char enemy_around;                  // offset 0x520, size 0x1
    u_char enemy_atk_area;                // offset 0x521, size 0x1
    u_char enemy_near;                    // offset 0x522, size 0x1
    u_char lock_on;                       // offset 0x523, size 0x1
    u_char running;                       // offset 0x524, size 0x1
    u_char cannot_run;                    // offset 0x525, size 0x1
    u_char fall_type;                     // offset 0x526, size 0x1
    u_char reload;                        // offset 0x527, size 0x1
    char weapon;                          // offset 0x528, size 0x1
    u_char shoot_val;                     // offset 0x529, size 0x1
    u_char reload_val;                    // offset 0x52A, size 0x1
    u_char atk_type;                      // offset 0x52B, size 0x1
    u_char atk_reserve[2];                // offset 0x52C, size 0x2
    u_char attack_ok;                     // offset 0x52E, size 0x1
    s_char hold_type;                     // offset 0x52F, size 0x1
    u_char dead;                          // offset 0x530, size 0x1
    u_char no_damage;                     // offset 0x531, size 0x1
    u_char atk_count;                     // offset 0x532, size 0x1
    u_char hug_status;                    // offset 0x533, size 0x1
    u_char hug_dir;                       // offset 0x534, size 0x1
    u_char se_on;                         // offset 0x535, size 0x1
    u_char spray_set;                     // offset 0x536, size 0x1
    s_char spray_pow;                     // offset 0x537, size 0x1
    u_short damage_no;                    // offset 0x538, size 0x2
    u_short attack_no;                    // offset 0x53A, size 0x2
} shPlayerWork;

// E:\work\sh2(CVS全取得)\src\Chacter\chara_saveinfo.c
typedef struct _Character_Info
{
    // total size: 0x1430
    float spray_time;                  // offset 0x0, size 0x4
    float running_time;                // offset 0x4, size 0x4
    int tired;                         // offset 0x8, size 0x4
    int tired_max;                     // offset 0xC, size 0x4
    int spirit;                        // offset 0x10, size 0x4
    int weapon;                        // offset 0x14, size 0x4
    u_char spray_set;                  // offset 0x18, size 0x1
    struct _CI_SubCharacter ci_sc[32]; // offset 0x20, size 0x1400
    char total;                        // offset 0x1420, size 0x1
} Character_Info;

// E:\work\sh2(CVS全取得)\src\Chacter\m3_djames.c
struct shPlayerWork sh2jms; // size: 0x540, address: 0x3C7EE0

#endif CHARACTER_H

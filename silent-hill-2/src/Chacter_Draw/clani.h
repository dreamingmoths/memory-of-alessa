#ifndef CLANI_H
#define CLANI_H

#include "sh2_common.h"
#include "Chacter/skelton.h"

typedef float (*CalcFunc)(void *, int, int, short);

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

typedef struct _AnimeInfo {
    // total size: 0xC
    unsigned short name; // offset 0x0, size 0x2
    unsigned short frame; // offset 0x2, size 0x2
    signed short speed; // offset 0x4, size 0x2
    unsigned short start; // offset 0x6, size 0x2
    unsigned short end; // offset 0x8, size 0x2
    unsigned char loop; // offset 0xA, size 0x1
    char pad; // offset 0xB, size 0x1
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
    IXY c_count;       // offset 0x1C, size 0x8
    SXY c_speed;       // offset 0x24, size 0x4
    SXY total_speed;   // offset 0x28, size 0x4
    USXY cur_frame;    // offset 0x2C, size 0x4
    char first_bone_type;      // offset 0x30, size 0x1
    char comp_type;            // offset 0x31, size 0x1
    struct _AnimeInfo *anim_a; // offset 0x34, size 0x4
    struct _AnimeInfo *anim_b; // offset 0x38, size 0x4
    Vector4 rot_neck;          // offset 0x40, size 0x10
    Vector4 ot_arms;           // offset 0x50, size 0x10
    Vector4 rot_body_neck;     // offset 0x60, size 0x10
    Vector4 rot_body;          // offset 0x70, size 0x10
    float scale;               // offset 0x80, size 0x4
} shAnime3d;

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

typedef struct ClusterAnimeWork {
    // total size: 0x200
    struct shClusterAnime ca[32]; // offset 0x0, size 0x200
} ClusterAnimeWork;
ClusterAnimeWork sh2cluster;

extern ClusterAnimeWork sh2cluster;
extern float cluster_weight_data[32][20]; // size: 0xA00, address: 0x418780

void ClusterAnimeExec(shClusterAnime * cap, shAnime3d * ap);

#endif // CLANI_H

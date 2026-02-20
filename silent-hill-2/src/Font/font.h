#ifndef FONT_H
#define FONT_H

#include "sh2_common.h"

extern u16 *msg_station;
#define FONT_STREAM_BUFFER_SIZE 0x4000

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

typedef struct _anon5
{
    float d[4][4];
} _anon5;

typedef struct _anon3
{
    float x;
    float y;
    float z;
    float w;
} _anon3;

typedef struct shSkelton
{
    struct shSkelton *next;
    struct shSkelton *parent;
    _anon5 src_m;
    _anon3 src_t;
    _anon5 des_m;
    _anon3 des_t;
    _anon3 axis;
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

s8 *Model3SkeletonStructure(sh_Model *model);
s8 *func_001D2E80(sh_Model *model_);
u16 fontPrintStrMain(u16 **pstr, int flag);
u16 func_00158D60(u16 **pstr, int flag);
void fontPrintStr(u16 *str, int x, int y);

struct FONT_DATA
{
    // total size: 0x215B0
    /* 0x00000 */ u_int tex_head[12];                 // size 0x30
    /* 0x00030 */ u_int clut_head[12];                // size 0x30
    /* 0x00060 */ u_int clut[8];                      // size 0x20
    /* 0x00080 */ u_char texbuf[131072];              // size 0x20000
    /* 0x20080 */ u_long tex0;                        // size 0x4
    /* 0x20088 */ int fonttype;                       // size 0x4
    /* 0x2008C */ u_int rgb_u;                        // size 0x4
    /* 0x20090 */ u_int rgb_d;                        // size 0x4
    /* 0x20094 */ u_int rgb_s[4];                     // size 0x10
    /* 0x200A4 */ u_int alpha;                        // size 0x4
    /* 0x200A8 */ u_int alpha_base;                   // size 0x4
    /* 0x200AC */ u_int flag;                         // size 0x4
    /* 0x200B0 */ u_short x;                          // size 0x2
    /* 0x200B2 */ u_short y;                          // size 0x2
    /* 0x200B4 */ u_short wide_w;                     // size 0x2
    /* 0x200B6 */ u_short wide_h;                     // size 0x2
    /* 0x200B8 */ u_short right_x;                    // size 0x2
    /* 0x200BA */ u_short right_y;                    // size 0x2
    /* 0x200BC */ u_short wm;                         // size 0x2
    /* 0x200BE */ u_short hm;                         // size 0x2
    /* 0x200C0 */ short wait_count;                   // size 0x2
    /* 0x200C2 */ short wait_type;                    // size 0x2
    /* 0x200C4 */ short page_sound;                   // size 0x2
    /* 0x200C6 */ u_short code[400];                  // size 0x320
    /* 0x203E6 */ short upper[400];                   // size 0x320
    /* 0x20706 */ short lower[400];                   // size 0x320
    /* 0x20A26 */ short top;                          // size 0x2
    /* 0x20A28 */ short bottom;                       // size 0x2
    /* 0x20A2A */ short st_num;                       // size 0x2
    /* 0x20A2C */ short w_st_num;                     // size 0x2
    /* 0x20A2E */ short prl_count;                    // size 0x2
    /* 0x20A30 */ short preload;                      // size 0x2
    /* 0x20A32 */ short shadow_max;                   // size 0x2
    /* 0x20A34 */ short shadow_now;                   // size 0x2
    /* 0x20A36 */ u_short sel_xl;                     // size 0x2
    /* 0x20A38 */ u_short sel_xr;                     // size 0x2
    /* 0x20A3A */ u_short sel_yu[4];                  // size 0x8
    /* 0x20A42 */ u_short sel_yd[4];                  // size 0x8
    /* 0x20A4A */ short sel_max;                      // size 0x2
    /* 0x20A4C */ short sel_now;                      // size 0x2
    /* 0x20A4E */ u_short mes_v[10][64];              // size 0x500
    /* 0x20F50 */ u_short *mes_str_now;               // size 0x4
    /* 0x20F54 */ u_short *mes_str;                   // size 0x4
    /* 0x20F58 */ u_short *prl_str;                   // size 0x4
    /* 0x20F5C */ struct FONT_STREAM_DATA *stream;    // size 0x4
    /* 0x20F60 */ struct WFONT_STREAM_DATA *w_stream; // size 0x4
    /* 0x20F64 */ struct MFONT_STREAM_DATA *m_stream; // size 0x4
    /* 0x20F68 */ u_short stream_max;                 // size 0x2
    /* 0x20F6A */ u_short w_stream_max;               // size 0x2
    /* 0x20F6C */ u_short m_stream_max;               // size 0x2
    /* 0x20F6E */ u_short m_code[256];                // size 0x200
    /* 0x2116E */ short m_upper[256];                 // size 0x200
    /* 0x2136E */ short m_lower[256];                 // size 0x200
    /* 0x2156E */ short m_top;                        // size 0x2
    /* 0x21570 */ short m_bottom;                     // size 0x2
    /* 0x21572 */ short m_st_num;                     // size 0x2
    /* 0x21574 */ int m_base_x;                       // size 0x4
    /* 0x21578 */ int m_base_y;                       // size 0x4
    /* 0x2157C */ int m_base_z;                       // size 0x4
    /* 0x21580 */ u_int m_rgba;                       // size 0x4
    /* 0x21584 */ int m_sx;                           // size 0x4
    /* 0x21588 */ int m_sy;                           // size 0x4
    /* 0x2158C */ int m_w;                            // size 0x4
    /* 0x21590 */ int m_h;                            // size 0x4
    /* 0x21594 */ int m_x;                            // size 0x4
    /* 0x21598 */ int m_y;                            // size 0x4
    /* 0x2159C */ float bar_blink;                    // size 0x4
    /* 0x215A0 */ u_long *pCur;                       // size 0x4
    /* 0x215A4 */ int base_x;                         // size 0x4
    /* 0x215A8 */ int base_y;                         // size 0x4
    /* 0x215AC */ int base_z;                         // size 0x4
};

typedef struct WFONT_STREAM_DATA
{
    // total size: 0x18
    /* 0x00 */ u_short x;   // size 0x2
    /* 0x02 */ u_short y;   // size 0x2
    /* 0x04 */ u_short vw;  // size 0x2
    /* 0x06 */ u_short vh;  // size 0x2
    /* 0x08 */ u_short u;   // size 0x2
    /* 0x0A */ u_short v;   // size 0x2
    /* 0x0C */ u_int rgb_u; // size 0x4
    /* 0x10 */ u_int rgb_d; // size 0x4
    /* 0x14 */ u_short w;   // size 0x2
    /* 0x16 */ u_short h;   // size 0x2
} WFONT_STREAM_DATA;

typedef struct MFONT_STREAM_DATA
{
    // total size: 0x8
    /* 0x0 */ u_short x; // size 0x2
    /* 0x2 */ u_short y; // size 0x2
    /* 0x4 */ u_short u; // size 0x2
    /* 0x6 */ u_short v; // size 0x2
} MFONT_STREAM_DATA;

typedef struct FONT_STREAM_DATA
{
    u_short x;
    u_short y;
    u_short w;
    u_short h;
    u_short u;
    u_short v;
    u_int rgb_u;
    u_int rgb_d;
} FONT_STREAM_DATA;

struct FONT_DATA font;
void fontSetColor(int num);
void fontSetStreamMax(u_short s_max, u_short ws_max, u_short ms_max);
int fjAssert_(const char *file, int line, const char *str) __attribute__((noreturn));
char font_stream_buf[FONT_STREAM_BUFFER_SIZE];

#endif

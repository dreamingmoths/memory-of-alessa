#ifndef SH2GFW_BLOCKMAN_H
#define SH2GFW_BLOCKMAN_H

#include "sh2_common.h"
#include "GFW/sh2gfw_structs.h"

typedef struct sh2gfw_BLOCK_MAN {
    // total size: 0xC90
    struct sh2gfw_AREA_HEAD* pA_H;            // offset 0x0, size 0x4
    struct sh2gfw_BLOCK_HEAD* pB_H;           // offset 0x4, size 0x4
    struct sh2gfw_BLOCKGLOBAL_HEAD* pBG_H;    // offset 0x8, size 0x4
    struct sh2gfw_BLOCKLOCAL_HEAD* pBL_H;     // offset 0xC, size 0x4
    struct sh2gfw_GSREGS_HEAD* pGSREGS_H[4];  // offset 0x10, size 0x10
    struct sh2gfw_GIFTAG_HEAD* pGIF_H[4][16]; // offset 0x20, size 0x100
    u_short idVU_tag[4][16][8];               // offset 0x120, size 0x400
    struct sh2gfw_TEX_HEAD* pLTEX_H[4];       // offset 0x520, size 0x10
    struct sh2gfw_CLUTS_HEAD* pLCLUT_H[4];    // offset 0x530, size 0x10
    u_char gifnum[4];                         // offset 0x540, size 0x4
    u_char vunum[4][16];                      // offset 0x544, size 0x40
    u_char geom_amount[4][16][16];            // offset 0x584, size 0x400
    short texnum;                             // offset 0x984, size 0x2
    short blockid;                            // offset 0x986, size 0x2
    int ObjCondition;                         // offset 0x988, size 0x4
    union Q_WORDDATA* p_Matrices;             // offset 0x98C, size 0x4
    void* pTexMAN[4];                         // offset 0x990, size 0x10
    union Q_WORDDATA* pBlockPack[4];          // offset 0x9A0, size 0x10
    u_int bp_leng[4];                         // offset 0x9B0, size 0x10
    int vif1mark[8];                          // offset 0x9C0, size 0x20
    int slotid[8];                            // offset 0x9E0, size 0x20
    struct sh2gfw_GSREGS_HEAD* pTR_GSREGS_H;  // offset 0xA00, size 0x4
    struct sh2gfw_TEX_HEAD* pTR_LTEX_H;       // offset 0xA04, size 0x4
    struct sh2gfw_CLUTS_HEAD* pTR_LCLUT_H;    // offset 0xA08, size 0x4
    void* pTR_TexMAN;                         // offset 0xA0C, size 0x4
    void* pKT_GTR;                            // offset 0xA10, size 0x4
    void* pKT_LTR;                            // offset 0xA14, size 0x4
    short tr_gbl_gifnum;                      // offset 0xA18, size 0x2
    short tr_gifnum;                          // offset 0xA1A, size 0x2
    u_char tr_gbl_vunum;                      // offset 0xA1C, size 0x1
    u_char tr_vunum;                          // offset 0xA1D, size 0x1
    u_char view_clip_flg;                     // offset 0xA1E, size 0x1
    u_char view_tile;                         // offset 0xA1F, size 0x1
    struct sh2gfw_GIFTAG_HEAD* pTR_GIF_H[16]; // offset 0xA20, size 0x40
    u_char tileViewClipInfo[8][8];            // offset 0xA60, size 0x40
    float Local_World[4][4];                  // offset 0xAA0, size 0x40
    float World_Local[4][4];                  // offset 0xAE0, size 0x40
    union Q_WORDDATA calc_parms[3];           // offset 0xB20, size 0x30
    union Q_WORDDATA bitmsk_data;             // offset 0xB50, size 0x10
    struct /* @anon14 */ {
        // total size: 0x130
        float light_vect[4][4];           // offset 0x0, size 0x40
        float light_col[4][4];            // offset 0x40, size 0x40
        float light_amb[4];               // offset 0x80, size 0x10
        float light_pam[2][4];            // offset 0x90, size 0x20
        union Q_WORDDATA LightPos1;       // offset 0xB0, size 0x10
        union Q_WORDDATA VertexAmbient;   // offset 0xC0, size 0x10
        union Q_WORDDATA BaseVertexColor; // offset 0xD0, size 0x10
        union Q_WORDDATA BaseAmbient;     // offset 0xE0, size 0x10
        union Q_WORDDATA ALPHA_clear;     // offset 0xF0, size 0x10
        float LightRealPos[4];            // offset 0x100, size 0x10
        float LightRealDir[4];            // offset 0x110, size 0x10
        u_int light_type_buf;             // offset 0x120, size 0x4
        u_int light_type_now;             // offset 0x124, size 0x4
        u_int pad1;                       // offset 0x128, size 0x4
        u_int pad2;                       // offset 0x12C, size 0x4
    } blk_LightData;                      // offset 0xB60, size 0x130
} sh2gfw_BLOCK_MAN __attribute__((aligned(16)));

extern sh2gfw_BLOCK_MAN b_man;

#endif // SH2GFW_BLOCKMAN_H

#ifndef SH2GFW_STRUCTS_H
#define SH2GFW_STRUCTS_H

typedef struct sh2gfw_AREA_HEAD {
    // total size: 0x10
    u_int area_id;           // offset 0x0, size 0x4
    u_int toGlobalTexHead;   // offset 0x4, size 0x4
    u_int toGlobalClutsHead; // offset 0x8, size 0x4
    u_int date;              // offset 0xC, size 0x4
} sh2gfw_AREA_HEAD;

typedef struct sh2gfw_BLOCK_HEAD {
    // total size: 0x30
    u_int block_id;            // offset 0x0, size 0x4
    u_int toGlobaldef;         // offset 0x4, size 0x4
    u_int toLocaldef;          // offset 0x8, size 0x4
    u_int toRawblockdataParms; // offset 0xC, size 0x4
    u_int toLocalTex[3];       // offset 0x10, size 0xC
    u_int toLocalcluts[3];     // offset 0x1C, size 0xC
    u_int texnum;              // offset 0x28, size 0x4
    u_char globaltexnum;       // offset 0x2C, size 0x1
    u_char transtexnum;        // offset 0x2D, size 0x1
    u_char divflg;             // offset 0x2E, size 0x1
    u_char padc;               // offset 0x2F, size 0x1
} sh2gfw_BLOCK_HEAD;

typedef struct sh2gfw_BLOCKGLOBAL_HEAD {
    // total size: 0x10
    u_int gsregsamount; // offset 0x0, size 0x4
    u_int transamount;  // offset 0x4, size 0x4
    u_char gtexnum;     // offset 0x8, size 0x1
    u_char gtransnum;   // offset 0x9, size 0x1
    u_short pads;       // offset 0xA, size 0x2
    u_int pad2;         // offset 0xC, size 0x4
} sh2gfw_BLOCKGLOBAL_HEAD;

typedef struct sh2gfw_BLOCKLOCAL_HEAD {
    // total size: 0x10
    u_short gsregsamount[3]; // offset 0x0, size 0x6
    u_short transamount[3];  // offset 0x6, size 0x6
    u_short ltexnum;         // offset 0xC, size 0x2
    u_short pads;            // offset 0xE, size 0x2
} sh2gfw_BLOCKLOCAL_HEAD;

typedef struct sh2gfw_GSREGS_HEAD {
    // total size: 0x30
    u_int clutssize;         // offset 0x0, size 0x4
    u_int toNextDATA;        // offset 0x4, size 0x4
    u_int toTexHead;         // offset 0x8, size 0x4
    u_char clutamount;       // offset 0xC, size 0x1
    u_char transamount;      // offset 0xD, size 0x1
    u_char eop_flg;          // offset 0xE, size 0x1
    u_char tr_flg;           // offset 0xF, size 0x1
    u_char fmt[16];          // offset 0x10, size 0x10
    u_char transparency[16]; // offset 0x20, size 0x10
} sh2gfw_GSREGS_HEAD;

typedef struct sh2gfw_GIFTAG_HEAD {
    // total size: 0x10
    u_short gsregs_amount; // offset 0x0, size 0x2
    u_char trans_flg;      // offset 0x2, size 0x1
    u_char eop_flg;        // offset 0x3, size 0x1
    u_int toNextGIFHEAD;   // offset 0x4, size 0x4
    u_short id;            // offset 0x8, size 0x2
    u_char tcc;            // offset 0xA, size 0x1
    u_char tfx;            // offset 0xB, size 0x1
    u_char abe;            // offset 0xC, size 0x1
    u_char pad1;           // offset 0xD, size 0x1
    u_char pad2;           // offset 0xE, size 0x1
    u_char pad3;           // offset 0xF, size 0x1
} sh2gfw_GIFTAG_HEAD;

typedef struct sh2gfw_TEX_HEAD {
    // total size: 0x30
    u_int texture_no;        // offset 0x0, size 0x4
    u_short x;               // offset 0x4, size 0x2
    u_short y;               // offset 0x6, size 0x2
    u_short w;               // offset 0x8, size 0x2
    u_short h;               // offset 0xA, size 0x2
    u_char color;            // offset 0xC, size 0x1
    u_char padbyte;          // offset 0xD, size 0x1
    u_short importance;      // offset 0xE, size 0x2
    u_int datasize;          // offset 0x10, size 0x4
    u_int allsize;           // offset 0x14, size 0x4
    u_char sendpsm;          // offset 0x18, size 0x1
    u_char drawpsm;          // offset 0x19, size 0x1
    u_char bitshift;         // offset 0x1A, size 0x1
    u_char tagpoint;         // offset 0x1B, size 0x1
    u_char bitw;             // offset 0x1C, size 0x1
    u_char bith;             // offset 0x1D, size 0x1
    u_short check;           // offset 0x1E, size 0x2
    union Q_WORDDATA giftag; // offset 0x20, size 0x10
} sh2gfw_TEX_HEAD;

typedef struct sh2gfw_CLUTS_HEAD {
    // total size: 0x30
    u_int clutssize;         // offset 0x0, size 0x4
    u_int toGSREGS;          // offset 0x4, size 0x4
    u_int toRawClut;         // offset 0x8, size 0x4
    u_char clutamount;       // offset 0xC, size 0x1
    u_char transcluts;       // offset 0xD, size 0x1
    u_char clw;              // offset 0xE, size 0x1
    u_char clh;              // offset 0xF, size 0x1
    u_char fmt[16];          // offset 0x10, size 0x10
    u_char transparency[16]; // offset 0x20, size 0x10
} sh2gfw_CLUTS_HEAD;

typedef struct sh2gfw_Effect_Man {
    // total size: 0x40
    u_short effectid; // offset 0x0, size 0x2
    u_short vifmark; // offset 0x2, size 0x2
    u_short valid_id; // offset 0x4, size 0x2
    u_short pads; // offset 0x6, size 0x2
    int thr_cid; // offset 0x8, size 0x4
    int thr_sid; // offset 0xC, size 0x4
    u_long128 Tex0Data; // offset 0x10, size 0x10
    u_long128 Alpha; // offset 0x20, size 0x10
    void* pTexMAN; // offset 0x30, size 0x4
    void* pTexHead; // offset 0x34, size 0x4
    void* pTop; // offset 0x38, size 0x4
    void* pPad; // offset 0x3C, size 0x4
} sh2gfw_Effect_Man;

// total size: 0x250
typedef struct sh2gfw_TRANS_MAN { // @note: idk if this belongs here
    // Members
    unsigned int blockid; // offset 0x0, size 0x4
    // total size: 0x60
    struct /* @anon5 */ {
        // Members
        unsigned int areaid; // offset 0x0, size 0x4
        unsigned char use_Globalflg[7]; // offset 0x4, size 0x7
        unsigned char use_Transflg[7]; // offset 0xB, size 0x7
        unsigned short block_id[7]; // offset 0x12, size 0xE
        unsigned char * block_man[7]; // offset 0x20, size 0x1C
        struct sh2gfw_AREA_HEAD * pA_H; // offset 0x3C, size 0x4
        struct sh2gfw_TEX_HEAD * global_tex; // offset 0x40, size 0x4
        struct sh2gfw_CLUTS_HEAD * global_clut; // offset 0x44, size 0x4
        struct sh2gfw_TEX_HEAD * global_transtex; // offset 0x48, size 0x4
        struct sh2gfw_CLUTS_HEAD * global_transclut; // offset 0x4C, size 0x4
        struct sh2gfw_TexMAN * gTexMAN; // offset 0x50, size 0x4
        struct sh2gfw_TexMAN * gTranstexMAN; // offset 0x54, size 0x4
        unsigned short gtex_mode; // offset 0x58, size 0x2
        unsigned short gtrans_mode; // offset 0x5A, size 0x2
        unsigned int pad1; // offset 0x5C, size 0x4
    } * pA_M; // offset 0x4, size 0x4
    unsigned short objnum[4]; // offset 0x8, size 0x8
    unsigned int trans_clutnum; // offset 0x10, size 0x4
    unsigned int pad2; // offset 0x14, size 0x4
    unsigned int pad3; // offset 0x18, size 0x4
    unsigned int pad4; // offset 0x1C, size 0x4
    unsigned char * trgehead[4]; // offset 0x20, size 0x10
    struct sh2gfw_GIFTAG_HEAD * pTR_global_GIF_H[4][16]; // offset 0x30, size 0x100
    struct sh2gfw_TEX_HEAD * p_GTexHead; // offset 0x130, size 0x4
    struct sh2gfw_CLUTS_HEAD * p_GClutHead; // offset 0x134, size 0x4
    struct sh2gfw_TexMAN * p_GTexMan; // offset 0x138, size 0x4
    unsigned char used_Ggifnum[4]; // offset 0x13C, size 0x4
    struct sh2gfw_GIFTAG_HEAD * pTR_trans_GIF_H[4][16]; // offset 0x140, size 0x100
    struct sh2gfw_TEX_HEAD * p_TRTexHead; // offset 0x240, size 0x4
    struct sh2gfw_CLUTS_HEAD * p_TRClutHead; // offset 0x244, size 0x4
    struct sh2gfw_TexMAN * p_TRTexMan; // offset 0x248, size 0x4
    unsigned char used_TRgifnum[4]; // offset 0x24C, size 0x4
} sh2gfw_TRANS_MAN;


#endif // SH2GFW_STRUCTS_H

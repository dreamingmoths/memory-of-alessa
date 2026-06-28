#ifndef SH2GFW_ALLTEXMAN_H
#define SH2GFW_ALLTEXMAN_H

typedef struct sh2gfw_TexMAN {
    // total size: 0x510
    u_short check;                      // offset 0x0, size 0x2
    u_short mode;                       // offset 0x2, size 0x2
    u_short kind;                       // offset 0x4, size 0x2
    u_short mark;                       // offset 0x6, size 0x2
    u_short attr;                       // offset 0x8, size 0x2
    u_short delay;                      // offset 0xA, size 0x2
    int commandid;                      // offset 0xC, size 0x4
    int slotid;                         // offset 0x10, size 0x4
    void* Manage;                       // offset 0x14, size 0x4
    struct sh2gfw_TexMAN* pPrev;        // offset 0x18, size 0x4
    struct sh2gfw_TexMAN* pNext;        // offset 0x1C, size 0x4
    void* TexHead;                      // offset 0x20, size 0x4
    void* ClutHead;                     // offset 0x24, size 0x4
    void* tex;                          // offset 0x28, size 0x4
    void* clut;                         // offset 0x2C, size 0x4
    union Q_WORDDATA GIFA_D_REGS;       // offset 0x30, size 0x10
    union Q_WORDDATA GS_TEXFLUSH;       // offset 0x40, size 0x10
    union Q_WORDDATA GS_TEX0_1;         // offset 0x50, size 0x10
    union Q_WORDDATA GS_TEX0_2;         // offset 0x60, size 0x10
    union Q_WORDDATA GS_REG0;           // offset 0x70, size 0x10
    union Q_WORDDATA GS_REG1;           // offset 0x80, size 0x10
    union Q_WORDDATA GS_REG2;           // offset 0x90, size 0x10
    union Q_WORDDATA GS_REG3;           // offset 0xA0, size 0x10
    union Q_WORDDATA GS_REG4;           // offset 0xB0, size 0x10
    union Q_WORDDATA TEX0_for_CLUT[48]; // offset 0xC0, size 0x300
    union Q_WORDDATA DMACNT;            // offset 0x3C0, size 0x10
    union Q_WORDDATA GIFA_D_TEX;        // offset 0x3D0, size 0x10
    union Q_WORDDATA GS_LABEL;          // offset 0x3E0, size 0x10
    union Q_WORDDATA GS_TEX_BITBLT;     // offset 0x3F0, size 0x10
    union Q_WORDDATA GS_TEX_TRXREG;     // offset 0x400, size 0x10
    union Q_WORDDATA GS_TEX_TRXPOS;     // offset 0x410, size 0x10
    union Q_WORDDATA GS_TEX_TRXDIR;     // offset 0x420, size 0x10
    union Q_WORDDATA GIFIMAGE_TEX;      // offset 0x430, size 0x10
    union Q_WORDDATA DMAREF_TEXTRANS;   // offset 0x440, size 0x10
    union Q_WORDDATA DMACNT_CLUT;       // offset 0x450, size 0x10
    union Q_WORDDATA GIFA_D_CLUT;       // offset 0x460, size 0x10
    union Q_WORDDATA GS_CLUT_BITBLT;    // offset 0x470, size 0x10
    union Q_WORDDATA GS_CLUT_TRXREG;    // offset 0x480, size 0x10
    union Q_WORDDATA GS_CLUT_TRXPOS;    // offset 0x490, size 0x10
    union Q_WORDDATA GS_CLUT_TRXDIR;    // offset 0x4A0, size 0x10
    union Q_WORDDATA GIFIMAGE_CLUT;     // offset 0x4B0, size 0x10
    union Q_WORDDATA DMAREF_CLUTTRANS;  // offset 0x4C0, size 0x10
    union Q_WORDDATA DMAREF_DUMLBL;     // offset 0x4D0, size 0x10
    union Q_WORDDATA DMAEND;            // offset 0x4E0, size 0x10
    union Q_WORDDATA GIFA_D_LBLU;       // offset 0x4F0, size 0x10
    union Q_WORDDATA GS_LABELU;         // offset 0x500, size 0x10
} sh2gfw_TexMAN;

typedef struct sh2gfw_ALLTEXSYNC_MAN {
    // total size: 0x1F050
    short g_BG;                      // offset 0x0, size 0x2
    short st_BG;                     // offset 0x2, size 0x2
    short l_BG;                      // offset 0x4, size 0x2
    short bg_CHR;                    // offset 0x6, size 0x2
    short human_CHR;                 // offset 0x8, size 0x2
    short en_CHR;                    // offset 0xA, size 0x2
    short ura_CHR;                   // offset 0xC, size 0x2
    short x_CHR;                     // offset 0xE, size 0x2
    short alltex_CHR;                // offset 0x10, size 0x2
    short oS_CHR;                    // offset 0x12, size 0x2
    short oA_CHR;                    // offset 0x14, size 0x2
    short wp_CHR;                    // offset 0x16, size 0x2
    short alltexnum;                 // offset 0x18, size 0x2
    short alltex_BG;                 // offset 0x1A, size 0x2
    short alltex_EFF;                // offset 0x1C, size 0x2
    u_short trans_NOW_num;           // offset 0x1E, size 0x2
    struct sh2gfw_TexMAN Empty_Head; // offset 0x20, size 0x510
    struct sh2gfw_TexMAN Used_Head;  // offset 0x530, size 0x510
    int dbg_add;                     // offset 0xA40, size 0x4
    int dbg_del;                     // offset 0xA44, size 0x4
    u_short fonttex;                 // offset 0xA48, size 0x2
    u_short pads;                    // offset 0xA4A, size 0x2
    int pad2;                        // offset 0xA4C, size 0x4
    struct sh2gfw_TexMAN TexMan[96]; // offset 0xA50, size 0x1E600
} sh2gfw_ALLTEXSYNC_MAN;

extern sh2gfw_ALLTEXSYNC_MAN AllTexSync_Man;

#endif // SH2GFW_ALLTEXMAN_H

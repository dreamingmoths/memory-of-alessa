#ifndef SH2GFW_ALL_SYSINIT_H
#define SH2GFW_ALL_SYSINIT_H

#include "sh2_common.h"
#include "GFW/sh2gfw_structs.h"

// total size: 0x60
typedef struct sh2gfw_Area_Data_Man { //@note: idk where this belongs to
    // Members
    u_int areaid; // offset 0x0, size 0x4
    u_char use_Globalflg[7]; // offset 0x4, size 0x7
    u_char use_Transflg[7]; // offset 0xB, size 0x7
    u_short block_id[7]; // offset 0x12, size 0xE
    u_char* block_man[7]; // offset 0x20, size 0x1C
    struct sh2gfw_AREA_HEAD* pA_H; // offset 0x3C, size 0x4
    struct sh2gfw_TEX_HEAD* global_tex; // offset 0x40, size 0x4
    struct sh2gfw_CLUTS_HEAD* global_clut; // offset 0x44, size 0x4
    struct sh2gfw_TEX_HEAD* global_transtex; // offset 0x48, size 0x4
    struct sh2gfw_CLUTS_HEAD* global_transclut; // offset 0x4C, size 0x4
    struct sh2gfw_TexMAN* gTexMAN; // offset 0x50, size 0x4
    struct sh2gfw_TexMAN* gTranstexMAN; // offset 0x54, size 0x4
    u_short gtex_mode; // offset 0x58, size 0x2
    u_short gtrans_mode; // offset 0x5A, size 0x2
    u_int pad1; // offset 0x5C, size 0x4
} sh2gfw_Area_Data_Man; // size: 0x60, address: 0xE3C1F0

int Vcallback_test(int ca);
void init_PS2(void);
void step_init_ONE(void);
void step_init_STAGE(void); 
void map_DATA_LOAD(); // @todo: need to check what args this function really takes

extern union Q_WORDDATA mct;
extern sh2gfw_Area_Data_Man Area_Data_Man; //@note: idk where this belongs to

extern sh2gfw_TRANS_MAN sh2_TR_MAN; //@note: idk where this belongs to

#endif // SH2GFW_ALL_SYSINIT_H

#ifndef SH2_GSALLENV_H
#define SH2_GSALLENV_H

/* this header is not found in the symbols */

#include "sh2_common.h"
#include "libgraph.h"

typedef struct shGsLoopEnv {
    // total size: 0xB0
    u_int GsDrawFBPs[3];      // offset 0x0, size 0xC
    u_int GsNowDispFBPs[3];   // offset 0xC, size 0xC
    u_int GsNextDispFBPs[3];  // offset 0x18, size 0xC
    u_int GsTexTBPs[24];      // offset 0x24, size 0x60
    u_int GsShadowFBP[3];     // offset 0x84, size 0xC
    u_int GsShadowWorkFBP[3]; // offset 0x90, size 0xC
    u_short clutsize;         // offset 0x9C, size 0x2
    u_short clutamount;       // offset 0x9E, size 0x2
    u_short GsClutPage[8];    // offset 0xA0, size 0x10
} shGsLoopEnv;

typedef struct shGsDrawEnv {
    // total size: 0x2A0
    struct /* @anon9 */ {
        // total size: 0x10
        u_long NLOOP : 15; // offset 0x0, size 0x4
        u_long EOP : 1;    // offset 0x0, size 0x4
        u_long pad16 : 16; // offset 0x0, size 0x4
        u_long id : 14;    // offset 0x0, size 0x4
        u_long PRE : 1;    // offset 0x0, size 0x4
        u_long PRIM : 11;  // offset 0x0, size 0x4
        u_long FLG : 2;    // offset 0x0, size 0x4
        u_long NREG : 4;   // offset 0x0, size 0x4
        u_long REGS0 : 4;  // offset 0x8, size 0x4
        u_long REGS1 : 4;  // offset 0x8, size 0x4
        u_long REGS2 : 4;  // offset 0x8, size 0x4
        u_long REGS3 : 4;  // offset 0x8, size 0x4
        u_long REGS4 : 4;  // offset 0x8, size 0x4
        u_long REGS5 : 4;  // offset 0x8, size 0x4
        u_long REGS6 : 4;  // offset 0x8, size 0x4
        u_long REGS7 : 4;  // offset 0x8, size 0x4
        u_long REGS8 : 4;  // offset 0x8, size 0x4
        u_long REGS9 : 4;  // offset 0x8, size 0x4
        u_long REGS10 : 4; // offset 0x8, size 0x4
        u_long REGS11 : 4; // offset 0x8, size 0x4
        u_long REGS12 : 4; // offset 0x8, size 0x4
        u_long REGS13 : 4; // offset 0x8, size 0x4
        u_long REGS14 : 4; // offset 0x8, size 0x4
        u_long REGS15 : 4; // offset 0x8, size 0x4
    } giftag;              // offset 0x0, size 0x10
    struct /* @anon1 */ {
        // total size: 0x80
        struct /* @anon3 */ {
            // total size: 0x8
            u_long FBP : 9;    // offset 0x0, size 0x4
            u_long pad09 : 7;  // offset 0x0, size 0x4
            u_long FBW : 6;    // offset 0x0, size 0x4
            u_long pad22 : 2;  // offset 0x0, size 0x4
            u_long PSM : 6;    // offset 0x0, size 0x4
            u_long pad30 : 2;  // offset 0x0, size 0x4
            u_long FBMSK : 32; // offset 0x0, size 0x4
        } frame1;              // offset 0x0, size 0x8
        u_long frame1addr;     // offset 0x8, size 0x4
        struct /* @anon13 */ {
            // total size: 0x8
            u_long ZBP : 9;    // offset 0x0, size 0x4
            u_long pad09 : 15; // offset 0x0, size 0x4
            u_long PSM : 4;    // offset 0x0, size 0x4
            u_long pad28 : 4;  // offset 0x0, size 0x4
            u_long ZMSK : 1;   // offset 0x0, size 0x4
            u_long pad33 : 31; // offset 0x0, size 0x4
        } zbuf1;               // offset 0x10, size 0x8
        long zbuf1addr;        // offset 0x18, size 0x4
        struct /* @anon10 */ {
            // total size: 0x8
            u_long OFX : 16;   // offset 0x0, size 0x4
            u_long pad16 : 16; // offset 0x0, size 0x4
            u_long OFY : 16;   // offset 0x0, size 0x4
            u_long pad48 : 16; // offset 0x0, size 0x4
        } xyoffset1;           // offset 0x20, size 0x8
        long xyoffset1addr;    // offset 0x28, size 0x4
        struct /* @anon23 */ {
            // total size: 0x8
            u_long SCAX0 : 11; // offset 0x0, size 0x4
            u_long pad11 : 5;  // offset 0x0, size 0x4
            u_long SCAX1 : 11; // offset 0x0, size 0x4
            u_long pad27 : 5;  // offset 0x0, size 0x4
            u_long SCAY0 : 11; // offset 0x0, size 0x4
            u_long pad43 : 5;  // offset 0x0, size 0x4
            u_long SCAY1 : 11; // offset 0x0, size 0x4
            u_long pad59 : 5;  // offset 0x0, size 0x4
        } scissor1;            // offset 0x30, size 0x8
        long scissor1addr;     // offset 0x38, size 0x4
        struct /* @anon17 */ {
            // total size: 0x8
            u_long AC : 1;     // offset 0x0, size 0x4
            u_long pad01 : 63; // offset 0x0, size 0x4
        } prmodecont;          // offset 0x40, size 0x8
        long prmodecontaddr;   // offset 0x48, size 0x4
        struct /* @anon8 */ {
            // total size: 0x8
            u_long CLAMP : 1;  // offset 0x0, size 0x4
            u_long pad01 : 63; // offset 0x0, size 0x4
        } colclamp;            // offset 0x50, size 0x8
        long colclampaddr;     // offset 0x58, size 0x4
        struct /* @anon19 */ {
            // total size: 0x8
            u_long DTHE : 1;   // offset 0x0, size 0x4
            u_long pad01 : 63; // offset 0x0, size 0x4
        } dthe;                // offset 0x60, size 0x8
        long dtheaddr;         // offset 0x68, size 0x4
        struct /* @anon5 */ {
            // total size: 0x8
            u_long ATE : 1;     // offset 0x0, size 0x4
            u_long ATST : 3;    // offset 0x0, size 0x4
            u_long AREF : 8;    // offset 0x0, size 0x4
            u_long AFAIL : 2;   // offset 0x0, size 0x4
            u_long DATE : 1;    // offset 0x0, size 0x4
            u_long DATM : 1;    // offset 0x0, size 0x4
            u_long ZTE : 1;     // offset 0x0, size 0x4
            u_long ZTST : 2;    // offset 0x0, size 0x4
            u_long pad19 : 45;  // offset 0x0, size 0x4
        } test1;                // offset 0x70, size 0x8
        long test1addr;         // offset 0x78, size 0x4
    } draw;                     // offset 0x10, size 0x80
    union Q_WORDDATA drawq2[5]; // offset 0x90, size 0x50
    struct /* @anon12 */ {
        // total size: 0x60
        struct /* @anon5 */ {
            // total size: 0x8
            u_long ATE : 1;    // offset 0x0, size 0x4
            u_long ATST : 3;   // offset 0x0, size 0x4
            u_long AREF : 8;   // offset 0x0, size 0x4
            u_long AFAIL : 2;  // offset 0x0, size 0x4
            u_long DATE : 1;   // offset 0x0, size 0x4
            u_long DATM : 1;   // offset 0x0, size 0x4
            u_long ZTE : 1;    // offset 0x0, size 0x4
            u_long ZTST : 2;   // offset 0x0, size 0x4
            u_long pad19 : 45; // offset 0x0, size 0x4
        } testa;               // offset 0x0, size 0x8
        long testaaddr;        // offset 0x8, size 0x4
        struct /* @anon14 */ {
            // total size: 0x8
            u_long PRIM : 3;   // offset 0x0, size 0x4
            u_long IIP : 1;    // offset 0x0, size 0x4
            u_long TME : 1;    // offset 0x0, size 0x4
            u_long FGE : 1;    // offset 0x0, size 0x4
            u_long ABE : 1;    // offset 0x0, size 0x4
            u_long AA1 : 1;    // offset 0x0, size 0x4
            u_long FST : 1;    // offset 0x0, size 0x4
            u_long CTXT : 1;   // offset 0x0, size 0x4
            u_long FIX : 1;    // offset 0x0, size 0x4
            u_long pad11 : 53; // offset 0x0, size 0x4
        } prim;                // offset 0x10, size 0x8
        long primaddr;         // offset 0x18, size 0x4
        struct /* @anon20 */ {
            // total size: 0x8
            u_int R : 8; // offset 0x0, size 0x4
            u_int G : 8; // offset 0x0, size 0x4
            u_int B : 8; // offset 0x0, size 0x4
            u_int A : 8; // offset 0x0, size 0x4
            float Q;     // offset 0x4, size 0x4
        } rgbaq;         // offset 0x20, size 0x8
        long rgbaqaddr;  // offset 0x28, size 0x4
        struct /* @anon11 */ {
            // total size: 0x8
            u_long X : 16; // offset 0x0, size 0x4
            u_long Y : 16; // offset 0x0, size 0x4
            u_long Z : 32; // offset 0x0, size 0x4
        } xyz2a;           // offset 0x30, size 0x8
        long xyz2aaddr;    // offset 0x38, size 0x4
        struct /* @anon11 */ {
            // total size: 0x8
            u_long X : 16; // offset 0x0, size 0x4
            u_long Y : 16; // offset 0x0, size 0x4
            u_long Z : 32; // offset 0x0, size 0x4
        } xyz2b;           // offset 0x40, size 0x8
        long xyz2baddr;    // offset 0x48, size 0x4
        struct /* @anon5 */ {
            // total size: 0x8
            u_long ATE : 1;    // offset 0x0, size 0x4
            u_long ATST : 3;   // offset 0x0, size 0x4
            u_long AREF : 8;   // offset 0x0, size 0x4
            u_long AFAIL : 2;  // offset 0x0, size 0x4
            u_long DATE : 1;   // offset 0x0, size 0x4
            u_long DATM : 1;   // offset 0x0, size 0x4
            u_long ZTE : 1;    // offset 0x0, size 0x4
            u_long ZTST : 2;   // offset 0x0, size 0x4
            u_long pad19 : 45; // offset 0x0, size 0x4
        } testb;               // offset 0x50, size 0x8
        long testbaddr;        // offset 0x58, size 0x4
    } clear;                   // offset 0xE0, size 0x60
    struct /* @anon9 */ {
        // total size: 0x10
        u_long NLOOP : 15; // offset 0x0, size 0x4
        u_long EOP : 1;    // offset 0x0, size 0x4
        u_long pad16 : 16; // offset 0x0, size 0x4
        u_long id : 14;    // offset 0x0, size 0x4
        u_long PRE : 1;    // offset 0x0, size 0x4
        u_long PRIM : 11;  // offset 0x0, size 0x4
        u_long FLG : 2;    // offset 0x0, size 0x4
        u_long NREG : 4;   // offset 0x0, size 0x4
        u_long REGS0 : 4;  // offset 0x8, size 0x4
        u_long REGS1 : 4;  // offset 0x8, size 0x4
        u_long REGS2 : 4;  // offset 0x8, size 0x4
        u_long REGS3 : 4;  // offset 0x8, size 0x4
        u_long REGS4 : 4;  // offset 0x8, size 0x4
        u_long REGS5 : 4;  // offset 0x8, size 0x4
        u_long REGS6 : 4;  // offset 0x8, size 0x4
        u_long REGS7 : 4;  // offset 0x8, size 0x4
        u_long REGS8 : 4;  // offset 0x8, size 0x4
        u_long REGS9 : 4;  // offset 0x8, size 0x4
        u_long REGS10 : 4; // offset 0x8, size 0x4
        u_long REGS11 : 4; // offset 0x8, size 0x4
        u_long REGS12 : 4; // offset 0x8, size 0x4
        u_long REGS13 : 4; // offset 0x8, size 0x4
        u_long REGS14 : 4; // offset 0x8, size 0x4
        u_long REGS15 : 4; // offset 0x8, size 0x4
    } giftag_nc;           // offset 0x140, size 0x10
    struct /* @anon1 */ {
        // total size: 0x80
        struct /* @anon3 */ {
            // total size: 0x8
            u_long FBP : 9;    // offset 0x0, size 0x4
            u_long pad09 : 7;  // offset 0x0, size 0x4
            u_long FBW : 6;    // offset 0x0, size 0x4
            u_long pad22 : 2;  // offset 0x0, size 0x4
            u_long PSM : 6;    // offset 0x0, size 0x4
            u_long pad30 : 2;  // offset 0x0, size 0x4
            u_long FBMSK : 32; // offset 0x0, size 0x4
        } frame1;              // offset 0x0, size 0x8
        u_long frame1addr;     // offset 0x8, size 0x4
        struct /* @anon13 */ {
            // total size: 0x8
            u_long ZBP : 9;    // offset 0x0, size 0x4
            u_long pad09 : 15; // offset 0x0, size 0x4
            u_long PSM : 4;    // offset 0x0, size 0x4
            u_long pad28 : 4;  // offset 0x0, size 0x4
            u_long ZMSK : 1;   // offset 0x0, size 0x4
            u_long pad33 : 31; // offset 0x0, size 0x4
        } zbuf1;               // offset 0x10, size 0x8
        long zbuf1addr;        // offset 0x18, size 0x4
        struct /* @anon10 */ {
            // total size: 0x8
            u_long OFX : 16;   // offset 0x0, size 0x4
            u_long pad16 : 16; // offset 0x0, size 0x4
            u_long OFY : 16;   // offset 0x0, size 0x4
            u_long pad48 : 16; // offset 0x0, size 0x4
        } xyoffset1;           // offset 0x20, size 0x8
        long xyoffset1addr;    // offset 0x28, size 0x4
        struct /* @anon23 */ {
            // total size: 0x8
            u_long SCAX0 : 11; // offset 0x0, size 0x4
            u_long pad11 : 5;  // offset 0x0, size 0x4
            u_long SCAX1 : 11; // offset 0x0, size 0x4
            u_long pad27 : 5;  // offset 0x0, size 0x4
            u_long SCAY0 : 11; // offset 0x0, size 0x4
            u_long pad43 : 5;  // offset 0x0, size 0x4
            u_long SCAY1 : 11; // offset 0x0, size 0x4
            u_long pad59 : 5;  // offset 0x0, size 0x4
        } scissor1;            // offset 0x30, size 0x8
        long scissor1addr;     // offset 0x38, size 0x4
        struct /* @anon17 */ {
            // total size: 0x8
            u_long AC : 1;     // offset 0x0, size 0x4
            u_long pad01 : 63; // offset 0x0, size 0x4
        } prmodecont;          // offset 0x40, size 0x8
        long prmodecontaddr;   // offset 0x48, size 0x4
        struct /* @anon8 */ {
            // total size: 0x8
            u_long CLAMP : 1;  // offset 0x0, size 0x4
            u_long pad01 : 63; // offset 0x0, size 0x4
        } colclamp;            // offset 0x50, size 0x8
        long colclampaddr;     // offset 0x58, size 0x4
        struct /* @anon19 */ {
            // total size: 0x8
            u_long DTHE : 1;   // offset 0x0, size 0x4
            u_long pad01 : 63; // offset 0x0, size 0x4
        } dthe;                // offset 0x60, size 0x8
        long dtheaddr;         // offset 0x68, size 0x4
        struct /* @anon5 */ {
            // total size: 0x8
            u_long ATE : 1;                 // offset 0x0, size 0x4
            u_long ATST : 3;                // offset 0x0, size 0x4
            u_long AREF : 8;                // offset 0x0, size 0x4
            u_long AFAIL : 2;               // offset 0x0, size 0x4
            u_long DATE : 1;                // offset 0x0, size 0x4
            u_long DATM : 1;                // offset 0x0, size 0x4
            u_long ZTE : 1;                 // offset 0x0, size 0x4
            u_long ZTST : 2;                // offset 0x0, size 0x4
            u_long pad19 : 45;              // offset 0x0, size 0x4
        } test1;                            // offset 0x70, size 0x8
        long test1addr;                     // offset 0x78, size 0x4
    } draw_nc;                              // offset 0x150, size 0x80
    union Q_WORDDATA drawq2_nc[5];          // offset 0x1D0, size 0x50
    union Q_WORDDATA gifad_frame_normal;    // offset 0x220, size 0x10
    union Q_WORDDATA frame_normal;          // offset 0x230, size 0x10
    union Q_WORDDATA gifad_frame_mskalpha;  // offset 0x240, size 0x10
    union Q_WORDDATA frame_mskalpha;        // offset 0x250, size 0x10
    union Q_WORDDATA gifad_frame_mskDalpha; // offset 0x260, size 0x10
    union Q_WORDDATA frame_mskDalpha;       // offset 0x270, size 0x10
    union Q_WORDDATA gifad_frame_mskRGB;    // offset 0x280, size 0x10
    union Q_WORDDATA frame_mskRGB;          // offset 0x290, size 0x10
} shGsDrawEnv;

typedef struct shGsStencilDrawEnv {
    // total size: 0x2D0
    struct /* @anon9 */ {
        // total size: 0x10
        u_long NLOOP : 15; // offset 0x0, size 0x4
        u_long EOP : 1;    // offset 0x0, size 0x4
        u_long pad16 : 16; // offset 0x0, size 0x4
        u_long id : 14;    // offset 0x0, size 0x4
        u_long PRE : 1;    // offset 0x0, size 0x4
        u_long PRIM : 11;  // offset 0x0, size 0x4
        u_long FLG : 2;    // offset 0x0, size 0x4
        u_long NREG : 4;   // offset 0x0, size 0x4
        u_long REGS0 : 4;  // offset 0x8, size 0x4
        u_long REGS1 : 4;  // offset 0x8, size 0x4
        u_long REGS2 : 4;  // offset 0x8, size 0x4
        u_long REGS3 : 4;  // offset 0x8, size 0x4
        u_long REGS4 : 4;  // offset 0x8, size 0x4
        u_long REGS5 : 4;  // offset 0x8, size 0x4
        u_long REGS6 : 4;  // offset 0x8, size 0x4
        u_long REGS7 : 4;  // offset 0x8, size 0x4
        u_long REGS8 : 4;  // offset 0x8, size 0x4
        u_long REGS9 : 4;  // offset 0x8, size 0x4
        u_long REGS10 : 4; // offset 0x8, size 0x4
        u_long REGS11 : 4; // offset 0x8, size 0x4
        u_long REGS12 : 4; // offset 0x8, size 0x4
        u_long REGS13 : 4; // offset 0x8, size 0x4
        u_long REGS14 : 4; // offset 0x8, size 0x4
        u_long REGS15 : 4; // offset 0x8, size 0x4
    } giftag;              // offset 0x0, size 0x10
    struct /* @anon1 */ {
        // total size: 0x80
        struct /* @anon3 */ {
            // total size: 0x8
            u_long FBP : 9;    // offset 0x0, size 0x4
            u_long pad09 : 7;  // offset 0x0, size 0x4
            u_long FBW : 6;    // offset 0x0, size 0x4
            u_long pad22 : 2;  // offset 0x0, size 0x4
            u_long PSM : 6;    // offset 0x0, size 0x4
            u_long pad30 : 2;  // offset 0x0, size 0x4
            u_long FBMSK : 32; // offset 0x0, size 0x4
        } frame1;              // offset 0x0, size 0x8
        u_long frame1addr;     // offset 0x8, size 0x4
        struct /* @anon13 */ {
            // total size: 0x8
            u_long ZBP : 9;    // offset 0x0, size 0x4
            u_long pad09 : 15; // offset 0x0, size 0x4
            u_long PSM : 4;    // offset 0x0, size 0x4
            u_long pad28 : 4;  // offset 0x0, size 0x4
            u_long ZMSK : 1;   // offset 0x0, size 0x4
            u_long pad33 : 31; // offset 0x0, size 0x4
        } zbuf1;               // offset 0x10, size 0x8
        long zbuf1addr;        // offset 0x18, size 0x4
        struct /* @anon10 */ {
            // total size: 0x8
            u_long OFX : 16;   // offset 0x0, size 0x4
            u_long pad16 : 16; // offset 0x0, size 0x4
            u_long OFY : 16;   // offset 0x0, size 0x4
            u_long pad48 : 16; // offset 0x0, size 0x4
        } xyoffset1;           // offset 0x20, size 0x8
        long xyoffset1addr;    // offset 0x28, size 0x4
        struct /* @anon23 */ {
            // total size: 0x8
            u_long SCAX0 : 11; // offset 0x0, size 0x4
            u_long pad11 : 5;  // offset 0x0, size 0x4
            u_long SCAX1 : 11; // offset 0x0, size 0x4
            u_long pad27 : 5;  // offset 0x0, size 0x4
            u_long SCAY0 : 11; // offset 0x0, size 0x4
            u_long pad43 : 5;  // offset 0x0, size 0x4
            u_long SCAY1 : 11; // offset 0x0, size 0x4
            u_long pad59 : 5;  // offset 0x0, size 0x4
        } scissor1;            // offset 0x30, size 0x8
        long scissor1addr;     // offset 0x38, size 0x4
        struct /* @anon17 */ {
            // total size: 0x8
            u_long AC : 1;     // offset 0x0, size 0x4
            u_long pad01 : 63; // offset 0x0, size 0x4
        } prmodecont;          // offset 0x40, size 0x8
        long prmodecontaddr;   // offset 0x48, size 0x4
        struct /* @anon8 */ {
            // total size: 0x8
            u_long CLAMP : 1;  // offset 0x0, size 0x4
            u_long pad01 : 63; // offset 0x0, size 0x4
        } colclamp;            // offset 0x50, size 0x8
        long colclampaddr;     // offset 0x58, size 0x4
        struct /* @anon19 */ {
            // total size: 0x8
            u_long DTHE : 1;   // offset 0x0, size 0x4
            u_long pad01 : 63; // offset 0x0, size 0x4
        } dthe;                // offset 0x60, size 0x8
        long dtheaddr;         // offset 0x68, size 0x4
        struct /* @anon5 */ {
            // total size: 0x8
            u_long ATE : 1;     // offset 0x0, size 0x4
            u_long ATST : 3;    // offset 0x0, size 0x4
            u_long AREF : 8;    // offset 0x0, size 0x4
            u_long AFAIL : 2;   // offset 0x0, size 0x4
            u_long DATE : 1;    // offset 0x0, size 0x4
            u_long DATM : 1;    // offset 0x0, size 0x4
            u_long ZTE : 1;     // offset 0x0, size 0x4
            u_long ZTST : 2;    // offset 0x0, size 0x4
            u_long pad19 : 45;  // offset 0x0, size 0x4
        } test1;                // offset 0x70, size 0x8
        long test1addr;         // offset 0x78, size 0x4
    } draw;                     // offset 0x10, size 0x80
    union Q_WORDDATA alpha1;    // offset 0x90, size 0x10
    union Q_WORDDATA drawq2[6]; // offset 0xA0, size 0x60
    struct /* @anon12 */ {
        // total size: 0x60
        struct /* @anon5 */ {
            // total size: 0x8
            u_long ATE : 1;    // offset 0x0, size 0x4
            u_long ATST : 3;   // offset 0x0, size 0x4
            u_long AREF : 8;   // offset 0x0, size 0x4
            u_long AFAIL : 2;  // offset 0x0, size 0x4
            u_long DATE : 1;   // offset 0x0, size 0x4
            u_long DATM : 1;   // offset 0x0, size 0x4
            u_long ZTE : 1;    // offset 0x0, size 0x4
            u_long ZTST : 2;   // offset 0x0, size 0x4
            u_long pad19 : 45; // offset 0x0, size 0x4
        } testa;               // offset 0x0, size 0x8
        long testaaddr;        // offset 0x8, size 0x4
        struct /* @anon14 */ {
            // total size: 0x8
            u_long PRIM : 3;   // offset 0x0, size 0x4
            u_long IIP : 1;    // offset 0x0, size 0x4
            u_long TME : 1;    // offset 0x0, size 0x4
            u_long FGE : 1;    // offset 0x0, size 0x4
            u_long ABE : 1;    // offset 0x0, size 0x4
            u_long AA1 : 1;    // offset 0x0, size 0x4
            u_long FST : 1;    // offset 0x0, size 0x4
            u_long CTXT : 1;   // offset 0x0, size 0x4
            u_long FIX : 1;    // offset 0x0, size 0x4
            u_long pad11 : 53; // offset 0x0, size 0x4
        } prim;                // offset 0x10, size 0x8
        long primaddr;         // offset 0x18, size 0x4
        struct /* @anon20 */ {
            // total size: 0x8
            u_int R : 8; // offset 0x0, size 0x4
            u_int G : 8; // offset 0x0, size 0x4
            u_int B : 8; // offset 0x0, size 0x4
            u_int A : 8; // offset 0x0, size 0x4
            float Q;     // offset 0x4, size 0x4
        } rgbaq;         // offset 0x20, size 0x8
        long rgbaqaddr;  // offset 0x28, size 0x4
        struct /* @anon11 */ {
            // total size: 0x8
            u_long X : 16; // offset 0x0, size 0x4
            u_long Y : 16; // offset 0x0, size 0x4
            u_long Z : 32; // offset 0x0, size 0x4
        } xyz2a;           // offset 0x30, size 0x8
        long xyz2aaddr;    // offset 0x38, size 0x4
        struct /* @anon11 */ {
            // total size: 0x8
            u_long X : 16; // offset 0x0, size 0x4
            u_long Y : 16; // offset 0x0, size 0x4
            u_long Z : 32; // offset 0x0, size 0x4
        } xyz2b;           // offset 0x40, size 0x8
        long xyz2baddr;    // offset 0x48, size 0x4
        struct /* @anon5 */ {
            // total size: 0x8
            u_long ATE : 1;    // offset 0x0, size 0x4
            u_long ATST : 3;   // offset 0x0, size 0x4
            u_long AREF : 8;   // offset 0x0, size 0x4
            u_long AFAIL : 2;  // offset 0x0, size 0x4
            u_long DATE : 1;   // offset 0x0, size 0x4
            u_long DATM : 1;   // offset 0x0, size 0x4
            u_long ZTE : 1;    // offset 0x0, size 0x4
            u_long ZTST : 2;   // offset 0x0, size 0x4
            u_long pad19 : 45; // offset 0x0, size 0x4
        } testb;               // offset 0x50, size 0x8
        long testbaddr;        // offset 0x58, size 0x4
    } clear;                   // offset 0x100, size 0x60
    union Q_WORDDATA frame;    // offset 0x160, size 0x10
    struct /* @anon9 */ {
        // total size: 0x10
        u_long NLOOP : 15; // offset 0x0, size 0x4
        u_long EOP : 1;    // offset 0x0, size 0x4
        u_long pad16 : 16; // offset 0x0, size 0x4
        u_long id : 14;    // offset 0x0, size 0x4
        u_long PRE : 1;    // offset 0x0, size 0x4
        u_long PRIM : 11;  // offset 0x0, size 0x4
        u_long FLG : 2;    // offset 0x0, size 0x4
        u_long NREG : 4;   // offset 0x0, size 0x4
        u_long REGS0 : 4;  // offset 0x8, size 0x4
        u_long REGS1 : 4;  // offset 0x8, size 0x4
        u_long REGS2 : 4;  // offset 0x8, size 0x4
        u_long REGS3 : 4;  // offset 0x8, size 0x4
        u_long REGS4 : 4;  // offset 0x8, size 0x4
        u_long REGS5 : 4;  // offset 0x8, size 0x4
        u_long REGS6 : 4;  // offset 0x8, size 0x4
        u_long REGS7 : 4;  // offset 0x8, size 0x4
        u_long REGS8 : 4;  // offset 0x8, size 0x4
        u_long REGS9 : 4;  // offset 0x8, size 0x4
        u_long REGS10 : 4; // offset 0x8, size 0x4
        u_long REGS11 : 4; // offset 0x8, size 0x4
        u_long REGS12 : 4; // offset 0x8, size 0x4
        u_long REGS13 : 4; // offset 0x8, size 0x4
        u_long REGS14 : 4; // offset 0x8, size 0x4
        u_long REGS15 : 4; // offset 0x8, size 0x4
    } giftag_nc;           // offset 0x170, size 0x10
    struct /* @anon1 */ {
        // total size: 0x80
        struct /* @anon3 */ {
            // total size: 0x8
            u_long FBP : 9;    // offset 0x0, size 0x4
            u_long pad09 : 7;  // offset 0x0, size 0x4
            u_long FBW : 6;    // offset 0x0, size 0x4
            u_long pad22 : 2;  // offset 0x0, size 0x4
            u_long PSM : 6;    // offset 0x0, size 0x4
            u_long pad30 : 2;  // offset 0x0, size 0x4
            u_long FBMSK : 32; // offset 0x0, size 0x4
        } frame1;              // offset 0x0, size 0x8
        u_long frame1addr;     // offset 0x8, size 0x4
        struct /* @anon13 */ {
            // total size: 0x8
            u_long ZBP : 9;    // offset 0x0, size 0x4
            u_long pad09 : 15; // offset 0x0, size 0x4
            u_long PSM : 4;    // offset 0x0, size 0x4
            u_long pad28 : 4;  // offset 0x0, size 0x4
            u_long ZMSK : 1;   // offset 0x0, size 0x4
            u_long pad33 : 31; // offset 0x0, size 0x4
        } zbuf1;               // offset 0x10, size 0x8
        long zbuf1addr;        // offset 0x18, size 0x4
        struct /* @anon10 */ {
            // total size: 0x8
            u_long OFX : 16;   // offset 0x0, size 0x4
            u_long pad16 : 16; // offset 0x0, size 0x4
            u_long OFY : 16;   // offset 0x0, size 0x4
            u_long pad48 : 16; // offset 0x0, size 0x4
        } xyoffset1;           // offset 0x20, size 0x8
        long xyoffset1addr;    // offset 0x28, size 0x4
        struct /* @anon23 */ {
            // total size: 0x8
            u_long SCAX0 : 11; // offset 0x0, size 0x4
            u_long pad11 : 5;  // offset 0x0, size 0x4
            u_long SCAX1 : 11; // offset 0x0, size 0x4
            u_long pad27 : 5;  // offset 0x0, size 0x4
            u_long SCAY0 : 11; // offset 0x0, size 0x4
            u_long pad43 : 5;  // offset 0x0, size 0x4
            u_long SCAY1 : 11; // offset 0x0, size 0x4
            u_long pad59 : 5;  // offset 0x0, size 0x4
        } scissor1;            // offset 0x30, size 0x8
        long scissor1addr;     // offset 0x38, size 0x4
        struct /* @anon17 */ {
            // total size: 0x8
            u_long AC : 1;     // offset 0x0, size 0x4
            u_long pad01 : 63; // offset 0x0, size 0x4
        } prmodecont;          // offset 0x40, size 0x8
        long prmodecontaddr;   // offset 0x48, size 0x4
        struct /* @anon8 */ {
            // total size: 0x8
            u_long CLAMP : 1;  // offset 0x0, size 0x4
            u_long pad01 : 63; // offset 0x0, size 0x4
        } colclamp;            // offset 0x50, size 0x8
        long colclampaddr;     // offset 0x58, size 0x4
        struct /* @anon19 */ {
            // total size: 0x8
            u_long DTHE : 1;   // offset 0x0, size 0x4
            u_long pad01 : 63; // offset 0x0, size 0x4
        } dthe;                // offset 0x60, size 0x8
        long dtheaddr;         // offset 0x68, size 0x4
        struct /* @anon5 */ {
            // total size: 0x8
            u_long ATE : 1;                 // offset 0x0, size 0x4
            u_long ATST : 3;                // offset 0x0, size 0x4
            u_long AREF : 8;                // offset 0x0, size 0x4
            u_long AFAIL : 2;               // offset 0x0, size 0x4
            u_long DATE : 1;                // offset 0x0, size 0x4
            u_long DATM : 1;                // offset 0x0, size 0x4
            u_long ZTE : 1;                 // offset 0x0, size 0x4
            u_long ZTST : 2;                // offset 0x0, size 0x4
            u_long pad19 : 45;              // offset 0x0, size 0x4
        } test1;                            // offset 0x70, size 0x8
        long test1addr;                     // offset 0x78, size 0x4
    } draw_nc;                              // offset 0x180, size 0x80
    union Q_WORDDATA alpha1_nc;             // offset 0x200, size 0x10
    union Q_WORDDATA drawq2_nc[6];          // offset 0x210, size 0x60
    union Q_WORDDATA gifad_frame_normal;    // offset 0x270, size 0x10
    union Q_WORDDATA frame_normal;          // offset 0x280, size 0x10
    union Q_WORDDATA gifad_frame_mskalpha;  // offset 0x290, size 0x10
    union Q_WORDDATA frame_mskalpha;        // offset 0x2A0, size 0x10
    union Q_WORDDATA gifad_frame_mskDalpha; // offset 0x2B0, size 0x10
    union Q_WORDDATA frame_mskDalpha;       // offset 0x2C0, size 0x10
} shGsStencilDrawEnv;

typedef struct shGsTinyDrawEnv {
    // total size: 0xC0
    union Q_WORDDATA giftag;          // offset 0x0, size 0x10
    union Q_WORDDATA frame;           // offset 0x10, size 0x10
    union Q_WORDDATA scissor;         // offset 0x20, size 0x10
    union Q_WORDDATA xyoffset;        // offset 0x30, size 0x10
    union Q_WORDDATA zbuf;            // offset 0x40, size 0x10
    union Q_WORDDATA test;            // offset 0x50, size 0x10
    union Q_WORDDATA gifad_normal;    // offset 0x60, size 0x10
    union Q_WORDDATA frame_normal;    // offset 0x70, size 0x10
    union Q_WORDDATA gifad_mskalpha;  // offset 0x80, size 0x10
    union Q_WORDDATA frame_mskalpha;  // offset 0x90, size 0x10
    union Q_WORDDATA gifad_mskDalpha; // offset 0xA0, size 0x10
    union Q_WORDDATA frame_mskDalpha; // offset 0xB0, size 0x10
} shGsTinyDrawEnv;

typedef struct shGsAllEnv {
    // total size: 0x2030
    u_long loop_counter;        // offset 0x0, size 0x4
    u_int loop;                 // offset 0x8, size 0x4
    u_int loop3;                // offset 0xC, size 0x4
    struct shGsLoopEnv LoopEnv; // offset 0x10, size 0xB0
    sceGsDispEnv DispEnv[3];                  // offset 0xC0, size 0x78
    struct shGsDrawEnv DrawEnv[3];            // offset 0x140, size 0x7E0
    struct shGsStencilDrawEnv StencilBuf[3];  // offset 0x920, size 0x870
    struct shGsTinyDrawEnv StencilWork[6];    // offset 0x1190, size 0x480
    union Q_WORDDATA DefaultEnv[10];          // offset 0x1610, size 0xA0
    union Q_WORDDATA StencilEnv[10];          // offset 0x16B0, size 0xA0
    union Q_WORDDATA CompshadowEnv[10];       // offset 0x1750, size 0xA0
    union Q_WORDDATA Filter_A[10];            // offset 0x17F0, size 0xA0
    union Q_WORDDATA Filter_B[10];            // offset 0x1890, size 0xA0
    union Q_WORDDATA Filter_C[10];            // offset 0x1930, size 0xA0
    union Q_WORDDATA Filter_D[10];            // offset 0x19D0, size 0xA0
    union Q_WORDDATA MoveGTex[8];             // offset 0x1A70, size 0x80
    union Q_WORDDATA GsReg_ALPHA_A[2];        // offset 0x1AF0, size 0x20
    union Q_WORDDATA GsReg_ALPHA_B[2];        // offset 0x1B10, size 0x20
    union Q_WORDDATA GsReg_ALPHA_C[2];        // offset 0x1B30, size 0x20
    union Q_WORDDATA GsReg_ALPHA_D[2];        // offset 0x1B50, size 0x20
    union Q_WORDDATA GsReg_ALPHA_E[2];        // offset 0x1B70, size 0x20
    union Q_WORDDATA GsReg_TEST_A[2];         // offset 0x1B90, size 0x20
    union Q_WORDDATA GsReg_TEST_B[2];         // offset 0x1BB0, size 0x20
    union Q_WORDDATA GsReg_TEST_C[2];         // offset 0x1BD0, size 0x20
    union Q_WORDDATA GsReg_TEST_D[2];         // offset 0x1BF0, size 0x20
    union Q_WORDDATA GsReg_TEXA_A[2];         // offset 0x1C10, size 0x20
    union Q_WORDDATA GsReg_TEXA_B[2];         // offset 0x1C30, size 0x20
    union Q_WORDDATA GsReg_ZBUF_A[2];         // offset 0x1C50, size 0x20
    union Q_WORDDATA GsReg_ZBUF_B[2];         // offset 0x1C70, size 0x20
    union Q_WORDDATA GsReg_PABE_A[2];         // offset 0x1C90, size 0x20
    union Q_WORDDATA GsReg_PABE_B[2];         // offset 0x1CB0, size 0x20
    union Q_WORDDATA GsReg_FBA_A[2];          // offset 0x1CD0, size 0x20
    union Q_WORDDATA GsReg_FBA_B[2];          // offset 0x1CF0, size 0x20
    union Q_WORDDATA GsReg_PRMODECONT_A[2];   // offset 0x1D10, size 0x20
    union Q_WORDDATA GsReg_PRMODECONT_B[2];   // offset 0x1D30, size 0x20
    union Q_WORDDATA GsSync_DummyLABEL[2];    // offset 0x1D50, size 0x20
    union Q_WORDDATA GsSync_DummyTEXFLUSH[2]; // offset 0x1D70, size 0x20
    struct shGsDrawEnv Now_DrawEnv;           // offset 0x1D90, size 0x2A0
} shGsAllEnv;

extern shGsAllEnv shGs_AllEnv;

#endif // SH2_GSALLENV_H

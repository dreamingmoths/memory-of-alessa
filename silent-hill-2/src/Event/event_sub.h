#ifndef EVENT_SUB_H
#define EVENT_SUB_H

#include "common.h"
#include "Chacter/character.h"

union Q_WORDDATA {
    unsigned int ui32[4]; // offset 0x0, size 0x10
    unsigned short us16[8]; // offset 0x0, size 0x10
    float fl32[4]; // offset 0x0, size 0x10
    unsigned char uc8[16]; // offset 0x0, size 0x10
    signed int si32[4]; // offset 0x0, size 0x10
    signed short ss16[8]; // offset 0x0, size 0x10
    char sc8[16]; // offset 0x0, size 0x10
    unsigned long ul64[2]; // offset 0x0, size 0x8
    __int128 ul128; // offset 0x0, size 0x10
};

// total size: 0xB0
struct shGsLoopEnv {
    // Members
    unsigned int GsDrawFBPs[3]; // offset 0x0, size 0xC
    unsigned int GsNowDispFBPs[3]; // offset 0xC, size 0xC
    unsigned int GsNextDispFBPs[3]; // offset 0x18, size 0xC
    unsigned int GsTexTBPs[24]; // offset 0x24, size 0x60
    unsigned int GsShadowFBP[3]; // offset 0x84, size 0xC
    unsigned int GsShadowWorkFBP[3]; // offset 0x90, size 0xC
    unsigned short clutsize; // offset 0x9C, size 0x2
    unsigned short clutamount; // offset 0x9E, size 0x2
    unsigned short GsClutPage[8]; // offset 0xA0, size 0x10
};

// total size: 0xC0
struct shGsTinyDrawEnv {
    // Members
    union Q_WORDDATA giftag; // offset 0x0, size 0x10
    union Q_WORDDATA frame; // offset 0x10, size 0x10
    union Q_WORDDATA scissor; // offset 0x20, size 0x10
    union Q_WORDDATA xyoffset; // offset 0x30, size 0x10
    union Q_WORDDATA zbuf; // offset 0x40, size 0x10
    union Q_WORDDATA test; // offset 0x50, size 0x10
    union Q_WORDDATA gifad_normal; // offset 0x60, size 0x10
    union Q_WORDDATA frame_normal; // offset 0x70, size 0x10
    union Q_WORDDATA gifad_mskalpha; // offset 0x80, size 0x10
    union Q_WORDDATA frame_mskalpha; // offset 0x90, size 0x10
    union Q_WORDDATA gifad_mskDalpha; // offset 0xA0, size 0x10
    union Q_WORDDATA frame_mskDalpha; // offset 0xB0, size 0x10
};
// t

// total size: 0x2D0
struct shGsStencilDrawEnv {
    // Members
    // total size: 0x10
    struct /* @anon0 */ {
        // Members
        unsigned long NLOOP : 15; // offset 0x0, size 0x4
        unsigned long EOP : 1; // offset 0x0, size 0x4
        unsigned long pad16 : 16; // offset 0x0, size 0x4
        unsigned long id : 14; // offset 0x0, size 0x4
        unsigned long PRE : 1; // offset 0x0, size 0x4
        unsigned long PRIM : 11; // offset 0x0, size 0x4
        unsigned long FLG : 2; // offset 0x0, size 0x4
        unsigned long NREG : 4; // offset 0x0, size 0x4
        unsigned long REGS0 : 4; // offset 0x8, size 0x4
        unsigned long REGS1 : 4; // offset 0x8, size 0x4
        unsigned long REGS2 : 4; // offset 0x8, size 0x4
        unsigned long REGS3 : 4; // offset 0x8, size 0x4
        unsigned long REGS4 : 4; // offset 0x8, size 0x4
        unsigned long REGS5 : 4; // offset 0x8, size 0x4
        unsigned long REGS6 : 4; // offset 0x8, size 0x4
        unsigned long REGS7 : 4; // offset 0x8, size 0x4
        unsigned long REGS8 : 4; // offset 0x8, size 0x4
        unsigned long REGS9 : 4; // offset 0x8, size 0x4
        unsigned long REGS10 : 4; // offset 0x8, size 0x4
        unsigned long REGS11 : 4; // offset 0x8, size 0x4
        unsigned long REGS12 : 4; // offset 0x8, size 0x4
        unsigned long REGS13 : 4; // offset 0x8, size 0x4
        unsigned long REGS14 : 4; // offset 0x8, size 0x4
        unsigned long REGS15 : 4; // offset 0x8, size 0x4
    } giftag; // offset 0x0, size 0x10
    // total size: 0x80
    struct /* @anon19 */ {
        // Members
        // total size: 0x8
        struct /* @anon17 */ {
            // Members
            unsigned long FBP : 9; // offset 0x0, size 0x4
            unsigned long pad09 : 7; // offset 0x0, size 0x4
            unsigned long FBW : 6; // offset 0x0, size 0x4
            unsigned long pad22 : 2; // offset 0x0, size 0x4
            unsigned long PSM : 6; // offset 0x0, size 0x4
            unsigned long pad30 : 2; // offset 0x0, size 0x4
            unsigned long FBMSK : 32; // offset 0x0, size 0x4
        } frame1; // offset 0x0, size 0x8
        unsigned long frame1addr; // offset 0x8, size 0x4
        // total size: 0x8
        struct /* @anon10 */ {
            // Members
            unsigned long ZBP : 9; // offset 0x0, size 0x4
            unsigned long pad09 : 15; // offset 0x0, size 0x4
            unsigned long PSM : 4; // offset 0x0, size 0x4
            unsigned long pad28 : 4; // offset 0x0, size 0x4
            unsigned long ZMSK : 1; // offset 0x0, size 0x4
            unsigned long pad33 : 31; // offset 0x0, size 0x4
        } zbuf1; // offset 0x10, size 0x8
        signed long zbuf1addr; // offset 0x18, size 0x4
        // total size: 0x8
        struct /* @anon3 */ {
            // Members
            unsigned long OFX : 16; // offset 0x0, size 0x4
            unsigned long pad16 : 16; // offset 0x0, size 0x4
            unsigned long OFY : 16; // offset 0x0, size 0x4
            unsigned long pad48 : 16; // offset 0x0, size 0x4
        } xyoffset1; // offset 0x20, size 0x8
        signed long xyoffset1addr; // offset 0x28, size 0x4
        // total size: 0x8
        struct /* @anon15 */ {
            // Members
            unsigned long SCAX0 : 11; // offset 0x0, size 0x4
            unsigned long pad11 : 5; // offset 0x0, size 0x4
            unsigned long SCAX1 : 11; // offset 0x0, size 0x4
            unsigned long pad27 : 5; // offset 0x0, size 0x4
            unsigned long SCAY0 : 11; // offset 0x0, size 0x4
            unsigned long pad43 : 5; // offset 0x0, size 0x4
            unsigned long SCAY1 : 11; // offset 0x0, size 0x4
            unsigned long pad59 : 5; // offset 0x0, size 0x4
        } scissor1; // offset 0x30, size 0x8
        signed long scissor1addr; // offset 0x38, size 0x4
        // total size: 0x8
        struct /* @anon13 */ {
            // Members
            unsigned long AC : 1; // offset 0x0, size 0x4
            unsigned long pad01 : 63; // offset 0x0, size 0x4
        } prmodecont; // offset 0x40, size 0x8
        signed long prmodecontaddr; // offset 0x48, size 0x4
        // total size: 0x8
        struct /* @anon1 */ {
            // Members
            unsigned long CLAMP : 1; // offset 0x0, size 0x4
            unsigned long pad01 : 63; // offset 0x0, size 0x4
        } colclamp; // offset 0x50, size 0x8
        signed long colclampaddr; // offset 0x58, size 0x4
        // total size: 0x8
        struct /* @anon12 */ {
            // Members
            unsigned long DTHE : 1; // offset 0x0, size 0x4
            unsigned long pad01 : 63; // offset 0x0, size 0x4
        } dthe; // offset 0x60, size 0x8
        signed long dtheaddr; // offset 0x68, size 0x4
        // total size: 0x8
        struct /* @anon21 */ {
            // Members
            unsigned long ATE : 1; // offset 0x0, size 0x4
            unsigned long ATST : 3; // offset 0x0, size 0x4
            unsigned long AREF : 8; // offset 0x0, size 0x4
            unsigned long AFAIL : 2; // offset 0x0, size 0x4
            unsigned long DATE : 1; // offset 0x0, size 0x4
            unsigned long DATM : 1; // offset 0x0, size 0x4
            unsigned long ZTE : 1; // offset 0x0, size 0x4
            unsigned long ZTST : 2; // offset 0x0, size 0x4
            unsigned long pad19 : 45; // offset 0x0, size 0x4
        } test1; // offset 0x70, size 0x8
        signed long test1addr; // offset 0x78, size 0x4
    } draw; // offset 0x10, size 0x80
    union Q_WORDDATA alpha1; // offset 0x90, size 0x10
    union Q_WORDDATA drawq2[6]; // offset 0xA0, size 0x60
    // total size: 0x60
    struct /* @anon8 */ {
        // Members
        // total size: 0x8
        struct /* @anon21 */ {
            // Members
            unsigned long ATE : 1; // offset 0x0, size 0x4
            unsigned long ATST : 3; // offset 0x0, size 0x4
            unsigned long AREF : 8; // offset 0x0, size 0x4
            unsigned long AFAIL : 2; // offset 0x0, size 0x4
            unsigned long DATE : 1; // offset 0x0, size 0x4
            unsigned long DATM : 1; // offset 0x0, size 0x4
            unsigned long ZTE : 1; // offset 0x0, size 0x4
            unsigned long ZTST : 2; // offset 0x0, size 0x4
            unsigned long pad19 : 45; // offset 0x0, size 0x4
        } testa; // offset 0x0, size 0x8
        signed long testaaddr; // offset 0x8, size 0x4
        // total size: 0x8
        struct /* @anon11 */ {
            // Members
            unsigned long PRIM : 3; // offset 0x0, size 0x4
            unsigned long IIP : 1; // offset 0x0, size 0x4
            unsigned long TME : 1; // offset 0x0, size 0x4
            unsigned long FGE : 1; // offset 0x0, size 0x4
            unsigned long ABE : 1; // offset 0x0, size 0x4
            unsigned long AA1 : 1; // offset 0x0, size 0x4
            unsigned long FST : 1; // offset 0x0, size 0x4
            unsigned long CTXT : 1; // offset 0x0, size 0x4
            unsigned long FIX : 1; // offset 0x0, size 0x4
            unsigned long pad11 : 53; // offset 0x0, size 0x4
        } prim; // offset 0x10, size 0x8
        signed long primaddr; // offset 0x18, size 0x4
        // total size: 0x8
        struct /* @anon14 */ {
            // Members
            unsigned int R : 8; // offset 0x0, size 0x4
            unsigned int G : 8; // offset 0x0, size 0x4
            unsigned int B : 8; // offset 0x0, size 0x4
            unsigned int A : 8; // offset 0x0, size 0x4
            float Q; // offset 0x4, size 0x4
        } rgbaq; // offset 0x20, size 0x8
        signed long rgbaqaddr; // offset 0x28, size 0x4
        // total size: 0x8
        struct /* @anon5 */ {
            // Members
            unsigned long X : 16; // offset 0x0, size 0x4
            unsigned long Y : 16; // offset 0x0, size 0x4
            unsigned long Z : 32; // offset 0x0, size 0x4
        } xyz2a; // offset 0x30, size 0x8
        signed long xyz2aaddr; // offset 0x38, size 0x4
        // total size: 0x8
        struct /* @anon5 */ {
            // Members
            unsigned long X : 16; // offset 0x0, size 0x4
            unsigned long Y : 16; // offset 0x0, size 0x4
            unsigned long Z : 32; // offset 0x0, size 0x4
        } xyz2b; // offset 0x40, size 0x8
        signed long xyz2baddr; // offset 0x48, size 0x4
        // total size: 0x8
        struct /* @anon21 */ {
            // Members
            unsigned long ATE : 1; // offset 0x0, size 0x4
            unsigned long ATST : 3; // offset 0x0, size 0x4
            unsigned long AREF : 8; // offset 0x0, size 0x4
            unsigned long AFAIL : 2; // offset 0x0, size 0x4
            unsigned long DATE : 1; // offset 0x0, size 0x4
            unsigned long DATM : 1; // offset 0x0, size 0x4
            unsigned long ZTE : 1; // offset 0x0, size 0x4
            unsigned long ZTST : 2; // offset 0x0, size 0x4
            unsigned long pad19 : 45; // offset 0x0, size 0x4
        } testb; // offset 0x50, size 0x8
        signed long testbaddr; // offset 0x58, size 0x4
    } clear; // offset 0x100, size 0x60
    union Q_WORDDATA frame; // offset 0x160, size 0x10
    // total size: 0x10
    struct /* @anon0 */ {
        // Members
        unsigned long NLOOP : 15; // offset 0x0, size 0x4
        unsigned long EOP : 1; // offset 0x0, size 0x4
        unsigned long pad16 : 16; // offset 0x0, size 0x4
        unsigned long id : 14; // offset 0x0, size 0x4
        unsigned long PRE : 1; // offset 0x0, size 0x4
        unsigned long PRIM : 11; // offset 0x0, size 0x4
        unsigned long FLG : 2; // offset 0x0, size 0x4
        unsigned long NREG : 4; // offset 0x0, size 0x4
        unsigned long REGS0 : 4; // offset 0x8, size 0x4
        unsigned long REGS1 : 4; // offset 0x8, size 0x4
        unsigned long REGS2 : 4; // offset 0x8, size 0x4
        unsigned long REGS3 : 4; // offset 0x8, size 0x4
        unsigned long REGS4 : 4; // offset 0x8, size 0x4
        unsigned long REGS5 : 4; // offset 0x8, size 0x4
        unsigned long REGS6 : 4; // offset 0x8, size 0x4
        unsigned long REGS7 : 4; // offset 0x8, size 0x4
        unsigned long REGS8 : 4; // offset 0x8, size 0x4
        unsigned long REGS9 : 4; // offset 0x8, size 0x4
        unsigned long REGS10 : 4; // offset 0x8, size 0x4
        unsigned long REGS11 : 4; // offset 0x8, size 0x4
        unsigned long REGS12 : 4; // offset 0x8, size 0x4
        unsigned long REGS13 : 4; // offset 0x8, size 0x4
        unsigned long REGS14 : 4; // offset 0x8, size 0x4
        unsigned long REGS15 : 4; // offset 0x8, size 0x4
    } giftag_nc; // offset 0x170, size 0x10
    // total size: 0x80
    struct /* @anon19 */ {
        // Members
        // total size: 0x8
        struct /* @anon17 */ {
            // Members
            unsigned long FBP : 9; // offset 0x0, size 0x4
            unsigned long pad09 : 7; // offset 0x0, size 0x4
            unsigned long FBW : 6; // offset 0x0, size 0x4
            unsigned long pad22 : 2; // offset 0x0, size 0x4
            unsigned long PSM : 6; // offset 0x0, size 0x4
            unsigned long pad30 : 2; // offset 0x0, size 0x4
            unsigned long FBMSK : 32; // offset 0x0, size 0x4
        } frame1; // offset 0x0, size 0x8
        unsigned long frame1addr; // offset 0x8, size 0x4
        // total size: 0x8
        struct /* @anon10 */ {
            // Members
            unsigned long ZBP : 9; // offset 0x0, size 0x4
            unsigned long pad09 : 15; // offset 0x0, size 0x4
            unsigned long PSM : 4; // offset 0x0, size 0x4
            unsigned long pad28 : 4; // offset 0x0, size 0x4
            unsigned long ZMSK : 1; // offset 0x0, size 0x4
            unsigned long pad33 : 31; // offset 0x0, size 0x4
        } zbuf1; // offset 0x10, size 0x8
        signed long zbuf1addr; // offset 0x18, size 0x4
        // total size: 0x8
        struct /* @anon3 */ {
            // Members
            unsigned long OFX : 16; // offset 0x0, size 0x4
            unsigned long pad16 : 16; // offset 0x0, size 0x4
            unsigned long OFY : 16; // offset 0x0, size 0x4
            unsigned long pad48 : 16; // offset 0x0, size 0x4
        } xyoffset1; // offset 0x20, size 0x8
        signed long xyoffset1addr; // offset 0x28, size 0x4
        // total size: 0x8
        struct /* @anon15 */ {
            // Members
            unsigned long SCAX0 : 11; // offset 0x0, size 0x4
            unsigned long pad11 : 5; // offset 0x0, size 0x4
            unsigned long SCAX1 : 11; // offset 0x0, size 0x4
            unsigned long pad27 : 5; // offset 0x0, size 0x4
            unsigned long SCAY0 : 11; // offset 0x0, size 0x4
            unsigned long pad43 : 5; // offset 0x0, size 0x4
            unsigned long SCAY1 : 11; // offset 0x0, size 0x4
            unsigned long pad59 : 5; // offset 0x0, size 0x4
        } scissor1; // offset 0x30, size 0x8
        signed long scissor1addr; // offset 0x38, size 0x4
        // total size: 0x8
        struct /* @anon13 */ {
            // Members
            unsigned long AC : 1; // offset 0x0, size 0x4
            unsigned long pad01 : 63; // offset 0x0, size 0x4
        } prmodecont; // offset 0x40, size 0x8
        signed long prmodecontaddr; // offset 0x48, size 0x4
        // total size: 0x8
        struct /* @anon1 */ {
            // Members
            unsigned long CLAMP : 1; // offset 0x0, size 0x4
            unsigned long pad01 : 63; // offset 0x0, size 0x4
        } colclamp; // offset 0x50, size 0x8
        signed long colclampaddr; // offset 0x58, size 0x4
        // total size: 0x8
        struct /* @anon12 */ {
            // Members
            unsigned long DTHE : 1; // offset 0x0, size 0x4
            unsigned long pad01 : 63; // offset 0x0, size 0x4
        } dthe; // offset 0x60, size 0x8
        signed long dtheaddr; // offset 0x68, size 0x4
        // total size: 0x8
        struct /* @anon21 */ {
            // Members
            unsigned long ATE : 1; // offset 0x0, size 0x4
            unsigned long ATST : 3; // offset 0x0, size 0x4
            unsigned long AREF : 8; // offset 0x0, size 0x4
            unsigned long AFAIL : 2; // offset 0x0, size 0x4
            unsigned long DATE : 1; // offset 0x0, size 0x4
            unsigned long DATM : 1; // offset 0x0, size 0x4
            unsigned long ZTE : 1; // offset 0x0, size 0x4
            unsigned long ZTST : 2; // offset 0x0, size 0x4
            unsigned long pad19 : 45; // offset 0x0, size 0x4
        } test1; // offset 0x70, size 0x8
        signed long test1addr; // offset 0x78, size 0x4
    } draw_nc; // offset 0x180, size 0x80
    union Q_WORDDATA alpha1_nc; // offset 0x200, size 0x10
    union Q_WORDDATA drawq2_nc[6]; // offset 0x210, size 0x60
    union Q_WORDDATA gifad_frame_normal; // offset 0x270, size 0x10
    union Q_WORDDATA frame_normal; // offset 0x280, size 0x10
    union Q_WORDDATA gifad_frame_mskalpha; // offset 0x290, size 0x10
    union Q_WORDDATA frame_mskalpha; // offset 0x2A0, size 0x10
    union Q_WORDDATA gifad_frame_mskDalpha; // offset 0x2B0, size 0x10
    union Q_WORDDATA frame_mskDalpha; // offset 0x2C0, size 0x10
};

// total size: 0x2A0
struct shGsDrawEnv {
    // Members
    // total size: 0x10
    struct /* @anon0 */ {
        // Members
        unsigned long NLOOP : 15; // offset 0x0, size 0x4
        unsigned long EOP : 1; // offset 0x0, size 0x4
        unsigned long pad16 : 16; // offset 0x0, size 0x4
        unsigned long id : 14; // offset 0x0, size 0x4
        unsigned long PRE : 1; // offset 0x0, size 0x4
        unsigned long PRIM : 11; // offset 0x0, size 0x4
        unsigned long FLG : 2; // offset 0x0, size 0x4
        unsigned long NREG : 4; // offset 0x0, size 0x4
        unsigned long REGS0 : 4; // offset 0x8, size 0x4
        unsigned long REGS1 : 4; // offset 0x8, size 0x4
        unsigned long REGS2 : 4; // offset 0x8, size 0x4
        unsigned long REGS3 : 4; // offset 0x8, size 0x4
        unsigned long REGS4 : 4; // offset 0x8, size 0x4
        unsigned long REGS5 : 4; // offset 0x8, size 0x4
        unsigned long REGS6 : 4; // offset 0x8, size 0x4
        unsigned long REGS7 : 4; // offset 0x8, size 0x4
        unsigned long REGS8 : 4; // offset 0x8, size 0x4
        unsigned long REGS9 : 4; // offset 0x8, size 0x4
        unsigned long REGS10 : 4; // offset 0x8, size 0x4
        unsigned long REGS11 : 4; // offset 0x8, size 0x4
        unsigned long REGS12 : 4; // offset 0x8, size 0x4
        unsigned long REGS13 : 4; // offset 0x8, size 0x4
        unsigned long REGS14 : 4; // offset 0x8, size 0x4
        unsigned long REGS15 : 4; // offset 0x8, size 0x4
    } giftag; // offset 0x0, size 0x10
    // total size: 0x80
    struct /* @anon19 */ {
        // Members
        // total size: 0x8
        struct /* @anon17 */ {
            // Members
            unsigned long FBP : 9; // offset 0x0, size 0x4
            unsigned long pad09 : 7; // offset 0x0, size 0x4
            unsigned long FBW : 6; // offset 0x0, size 0x4
            unsigned long pad22 : 2; // offset 0x0, size 0x4
            unsigned long PSM : 6; // offset 0x0, size 0x4
            unsigned long pad30 : 2; // offset 0x0, size 0x4
            unsigned long FBMSK : 32; // offset 0x0, size 0x4
        } frame1; // offset 0x0, size 0x8
        unsigned long frame1addr; // offset 0x8, size 0x4
        // total size: 0x8
        struct /* @anon10 */ {
            // Members
            unsigned long ZBP : 9; // offset 0x0, size 0x4
            unsigned long pad09 : 15; // offset 0x0, size 0x4
            unsigned long PSM : 4; // offset 0x0, size 0x4
            unsigned long pad28 : 4; // offset 0x0, size 0x4
            unsigned long ZMSK : 1; // offset 0x0, size 0x4
            unsigned long pad33 : 31; // offset 0x0, size 0x4
        } zbuf1; // offset 0x10, size 0x8
        signed long zbuf1addr; // offset 0x18, size 0x4
        // total size: 0x8
        struct /* @anon3 */ {
            // Members
            unsigned long OFX : 16; // offset 0x0, size 0x4
            unsigned long pad16 : 16; // offset 0x0, size 0x4
            unsigned long OFY : 16; // offset 0x0, size 0x4
            unsigned long pad48 : 16; // offset 0x0, size 0x4
        } xyoffset1; // offset 0x20, size 0x8
        signed long xyoffset1addr; // offset 0x28, size 0x4
        // total size: 0x8
        struct /* @anon15 */ {
            // Members
            unsigned long SCAX0 : 11; // offset 0x0, size 0x4
            unsigned long pad11 : 5; // offset 0x0, size 0x4
            unsigned long SCAX1 : 11; // offset 0x0, size 0x4
            unsigned long pad27 : 5; // offset 0x0, size 0x4
            unsigned long SCAY0 : 11; // offset 0x0, size 0x4
            unsigned long pad43 : 5; // offset 0x0, size 0x4
            unsigned long SCAY1 : 11; // offset 0x0, size 0x4
            unsigned long pad59 : 5; // offset 0x0, size 0x4
        } scissor1; // offset 0x30, size 0x8
        signed long scissor1addr; // offset 0x38, size 0x4
        // total size: 0x8
        struct /* @anon13 */ {
            // Members
            unsigned long AC : 1; // offset 0x0, size 0x4
            unsigned long pad01 : 63; // offset 0x0, size 0x4
        } prmodecont; // offset 0x40, size 0x8
        signed long prmodecontaddr; // offset 0x48, size 0x4
        // total size: 0x8
        struct /* @anon1 */ {
            // Members
            unsigned long CLAMP : 1; // offset 0x0, size 0x4
            unsigned long pad01 : 63; // offset 0x0, size 0x4
        } colclamp; // offset 0x50, size 0x8
        signed long colclampaddr; // offset 0x58, size 0x4
        // total size: 0x8
        struct /* @anon12 */ {
            // Members
            unsigned long DTHE : 1; // offset 0x0, size 0x4
            unsigned long pad01 : 63; // offset 0x0, size 0x4
        } dthe; // offset 0x60, size 0x8
        signed long dtheaddr; // offset 0x68, size 0x4
        // total size: 0x8
        struct /* @anon21 */ {
            // Members
            unsigned long ATE : 1; // offset 0x0, size 0x4
            unsigned long ATST : 3; // offset 0x0, size 0x4
            unsigned long AREF : 8; // offset 0x0, size 0x4
            unsigned long AFAIL : 2; // offset 0x0, size 0x4
            unsigned long DATE : 1; // offset 0x0, size 0x4
            unsigned long DATM : 1; // offset 0x0, size 0x4
            unsigned long ZTE : 1; // offset 0x0, size 0x4
            unsigned long ZTST : 2; // offset 0x0, size 0x4
            unsigned long pad19 : 45; // offset 0x0, size 0x4
        } test1; // offset 0x70, size 0x8
        signed long test1addr; // offset 0x78, size 0x4
    } draw; // offset 0x10, size 0x80
    union Q_WORDDATA drawq2[5]; // offset 0x90, size 0x50
    // total size: 0x60
    struct /* @anon8 */ {
        // Members
        // total size: 0x8
        struct /* @anon21 */ {
            // Members
            unsigned long ATE : 1; // offset 0x0, size 0x4
            unsigned long ATST : 3; // offset 0x0, size 0x4
            unsigned long AREF : 8; // offset 0x0, size 0x4
            unsigned long AFAIL : 2; // offset 0x0, size 0x4
            unsigned long DATE : 1; // offset 0x0, size 0x4
            unsigned long DATM : 1; // offset 0x0, size 0x4
            unsigned long ZTE : 1; // offset 0x0, size 0x4
            unsigned long ZTST : 2; // offset 0x0, size 0x4
            unsigned long pad19 : 45; // offset 0x0, size 0x4
        } testa; // offset 0x0, size 0x8
        signed long testaaddr; // offset 0x8, size 0x4
        // total size: 0x8
        struct /* @anon11 */ {
            // Members
            unsigned long PRIM : 3; // offset 0x0, size 0x4
            unsigned long IIP : 1; // offset 0x0, size 0x4
            unsigned long TME : 1; // offset 0x0, size 0x4
            unsigned long FGE : 1; // offset 0x0, size 0x4
            unsigned long ABE : 1; // offset 0x0, size 0x4
            unsigned long AA1 : 1; // offset 0x0, size 0x4
            unsigned long FST : 1; // offset 0x0, size 0x4
            unsigned long CTXT : 1; // offset 0x0, size 0x4
            unsigned long FIX : 1; // offset 0x0, size 0x4
            unsigned long pad11 : 53; // offset 0x0, size 0x4
        } prim; // offset 0x10, size 0x8
        signed long primaddr; // offset 0x18, size 0x4
        // total size: 0x8
        struct /* @anon14 */ {
            // Members
            unsigned int R : 8; // offset 0x0, size 0x4
            unsigned int G : 8; // offset 0x0, size 0x4
            unsigned int B : 8; // offset 0x0, size 0x4
            unsigned int A : 8; // offset 0x0, size 0x4
            float Q; // offset 0x4, size 0x4
        } rgbaq; // offset 0x20, size 0x8
        signed long rgbaqaddr; // offset 0x28, size 0x4
        // total size: 0x8
        struct /* @anon5 */ {
            // Members
            unsigned long X : 16; // offset 0x0, size 0x4
            unsigned long Y : 16; // offset 0x0, size 0x4
            unsigned long Z : 32; // offset 0x0, size 0x4
        } xyz2a; // offset 0x30, size 0x8
        signed long xyz2aaddr; // offset 0x38, size 0x4
        // total size: 0x8
        struct /* @anon5 */ {
            // Members
            unsigned long X : 16; // offset 0x0, size 0x4
            unsigned long Y : 16; // offset 0x0, size 0x4
            unsigned long Z : 32; // offset 0x0, size 0x4
        } xyz2b; // offset 0x40, size 0x8
        signed long xyz2baddr; // offset 0x48, size 0x4
        // total size: 0x8
        struct /* @anon21 */ {
            // Members
            unsigned long ATE : 1; // offset 0x0, size 0x4
            unsigned long ATST : 3; // offset 0x0, size 0x4
            unsigned long AREF : 8; // offset 0x0, size 0x4
            unsigned long AFAIL : 2; // offset 0x0, size 0x4
            unsigned long DATE : 1; // offset 0x0, size 0x4
            unsigned long DATM : 1; // offset 0x0, size 0x4
            unsigned long ZTE : 1; // offset 0x0, size 0x4
            unsigned long ZTST : 2; // offset 0x0, size 0x4
            unsigned long pad19 : 45; // offset 0x0, size 0x4
        } testb; // offset 0x50, size 0x8
        signed long testbaddr; // offset 0x58, size 0x4
    } clear; // offset 0xE0, size 0x60
    // total size: 0x10
    struct /* @anon0 */ {
        // Members
        unsigned long NLOOP : 15; // offset 0x0, size 0x4
        unsigned long EOP : 1; // offset 0x0, size 0x4
        unsigned long pad16 : 16; // offset 0x0, size 0x4
        unsigned long id : 14; // offset 0x0, size 0x4
        unsigned long PRE : 1; // offset 0x0, size 0x4
        unsigned long PRIM : 11; // offset 0x0, size 0x4
        unsigned long FLG : 2; // offset 0x0, size 0x4
        unsigned long NREG : 4; // offset 0x0, size 0x4
        unsigned long REGS0 : 4; // offset 0x8, size 0x4
        unsigned long REGS1 : 4; // offset 0x8, size 0x4
        unsigned long REGS2 : 4; // offset 0x8, size 0x4
        unsigned long REGS3 : 4; // offset 0x8, size 0x4
        unsigned long REGS4 : 4; // offset 0x8, size 0x4
        unsigned long REGS5 : 4; // offset 0x8, size 0x4
        unsigned long REGS6 : 4; // offset 0x8, size 0x4
        unsigned long REGS7 : 4; // offset 0x8, size 0x4
        unsigned long REGS8 : 4; // offset 0x8, size 0x4
        unsigned long REGS9 : 4; // offset 0x8, size 0x4
        unsigned long REGS10 : 4; // offset 0x8, size 0x4
        unsigned long REGS11 : 4; // offset 0x8, size 0x4
        unsigned long REGS12 : 4; // offset 0x8, size 0x4
        unsigned long REGS13 : 4; // offset 0x8, size 0x4
        unsigned long REGS14 : 4; // offset 0x8, size 0x4
        unsigned long REGS15 : 4; // offset 0x8, size 0x4
    } giftag_nc; // offset 0x140, size 0x10
    // total size: 0x80
    struct /* @anon19 */ {
        // Members
        // total size: 0x8
        struct /* @anon17 */ {
            // Members
            unsigned long FBP : 9; // offset 0x0, size 0x4
            unsigned long pad09 : 7; // offset 0x0, size 0x4
            unsigned long FBW : 6; // offset 0x0, size 0x4
            unsigned long pad22 : 2; // offset 0x0, size 0x4
            unsigned long PSM : 6; // offset 0x0, size 0x4
            unsigned long pad30 : 2; // offset 0x0, size 0x4
            unsigned long FBMSK : 32; // offset 0x0, size 0x4
        } frame1; // offset 0x0, size 0x8
        unsigned long frame1addr; // offset 0x8, size 0x4
        // total size: 0x8
        struct /* @anon10 */ {
            // Members
            unsigned long ZBP : 9; // offset 0x0, size 0x4
            unsigned long pad09 : 15; // offset 0x0, size 0x4
            unsigned long PSM : 4; // offset 0x0, size 0x4
            unsigned long pad28 : 4; // offset 0x0, size 0x4
            unsigned long ZMSK : 1; // offset 0x0, size 0x4
            unsigned long pad33 : 31; // offset 0x0, size 0x4
        } zbuf1; // offset 0x10, size 0x8
        signed long zbuf1addr; // offset 0x18, size 0x4
        // total size: 0x8
        struct /* @anon3 */ {
            // Members
            unsigned long OFX : 16; // offset 0x0, size 0x4
            unsigned long pad16 : 16; // offset 0x0, size 0x4
            unsigned long OFY : 16; // offset 0x0, size 0x4
            unsigned long pad48 : 16; // offset 0x0, size 0x4
        } xyoffset1; // offset 0x20, size 0x8
        signed long xyoffset1addr; // offset 0x28, size 0x4
        // total size: 0x8
        struct /* @anon15 */ {
            // Members
            unsigned long SCAX0 : 11; // offset 0x0, size 0x4
            unsigned long pad11 : 5; // offset 0x0, size 0x4
            unsigned long SCAX1 : 11; // offset 0x0, size 0x4
            unsigned long pad27 : 5; // offset 0x0, size 0x4
            unsigned long SCAY0 : 11; // offset 0x0, size 0x4
            unsigned long pad43 : 5; // offset 0x0, size 0x4
            unsigned long SCAY1 : 11; // offset 0x0, size 0x4
            unsigned long pad59 : 5; // offset 0x0, size 0x4
        } scissor1; // offset 0x30, size 0x8
        signed long scissor1addr; // offset 0x38, size 0x4
        // total size: 0x8
        struct /* @anon13 */ {
            // Members
            unsigned long AC : 1; // offset 0x0, size 0x4
            unsigned long pad01 : 63; // offset 0x0, size 0x4
        } prmodecont; // offset 0x40, size 0x8
        signed long prmodecontaddr; // offset 0x48, size 0x4
        // total size: 0x8
        struct /* @anon1 */ {
            // Members
            unsigned long CLAMP : 1; // offset 0x0, size 0x4
            unsigned long pad01 : 63; // offset 0x0, size 0x4
        } colclamp; // offset 0x50, size 0x8
        signed long colclampaddr; // offset 0x58, size 0x4
        // total size: 0x8
        struct /* @anon12 */ {
            // Members
            unsigned long DTHE : 1; // offset 0x0, size 0x4
            unsigned long pad01 : 63; // offset 0x0, size 0x4
        } dthe; // offset 0x60, size 0x8
        signed long dtheaddr; // offset 0x68, size 0x4
        // total size: 0x8
        struct /* @anon21 */ {
            // Members
            unsigned long ATE : 1; // offset 0x0, size 0x4
            unsigned long ATST : 3; // offset 0x0, size 0x4
            unsigned long AREF : 8; // offset 0x0, size 0x4
            unsigned long AFAIL : 2; // offset 0x0, size 0x4
            unsigned long DATE : 1; // offset 0x0, size 0x4
            unsigned long DATM : 1; // offset 0x0, size 0x4
            unsigned long ZTE : 1; // offset 0x0, size 0x4
            unsigned long ZTST : 2; // offset 0x0, size 0x4
            unsigned long pad19 : 45; // offset 0x0, size 0x4
        } test1; // offset 0x70, size 0x8
        signed long test1addr; // offset 0x78, size 0x4
    } draw_nc; // offset 0x150, size 0x80
    union Q_WORDDATA drawq2_nc[5]; // offset 0x1D0, size 0x50
    union Q_WORDDATA gifad_frame_normal; // offset 0x220, size 0x10
    union Q_WORDDATA frame_normal; // offset 0x230, size 0x10
    union Q_WORDDATA gifad_frame_mskalpha; // offset 0x240, size 0x10
    union Q_WORDDATA frame_mskalpha; // offset 0x250, size 0x10
    union Q_WORDDATA gifad_frame_mskDalpha; // offset 0x260, size 0x10
    union Q_WORDDATA frame_mskDalpha; // offset 0x270, size 0x10
    union Q_WORDDATA gifad_frame_mskRGB; // offset 0x280, size 0x10
    union Q_WORDDATA frame_mskRGB; // offset 0x290, size 0x10
};


// total size: 0x2030
struct shGsAllEnv {
    // Members
    unsigned long loop_counter; // offset 0x0, size 0x4
    unsigned int loop; // offset 0x8, size 0x4
    unsigned int loop3; // offset 0xC, size 0x4
    struct shGsLoopEnv LoopEnv; // offset 0x10, size 0xB0
    // total size: 0x28
    struct /* @anon25 */ {
        // Members
        // total size: 0x8
        struct /* @anon20 */ {
            // Members
            unsigned int EN1 : 1; // offset 0x0, size 0x4
            unsigned int EN2 : 1; // offset 0x0, size 0x4
            unsigned int CRTMD : 3; // offset 0x0, size 0x4
            unsigned int MMOD : 1; // offset 0x0, size 0x4
            unsigned int AMOD : 1; // offset 0x0, size 0x4
            unsigned int SLBG : 1; // offset 0x0, size 0x4
            unsigned int ALP : 8; // offset 0x0, size 0x4
            unsigned int p0 : 16; // offset 0x0, size 0x4
            unsigned int p1; // offset 0x4, size 0x4
        } pmode; // offset 0x0, size 0x8
        // total size: 0x8
        struct /* @anon2 */ {
            // Members
            unsigned int INT : 1; // offset 0x0, size 0x4
            unsigned int FFMD : 1; // offset 0x0, size 0x4
            unsigned int DPMS : 2; // offset 0x0, size 0x4
            unsigned int p0 : 28; // offset 0x0, size 0x4
            unsigned int p1; // offset 0x4, size 0x4
        } smode2; // offset 0x8, size 0x8
        // total size: 0x8
        struct /* @anon23 */ {
            // Members
            unsigned int FBP : 9; // offset 0x0, size 0x4
            unsigned int FBW : 6; // offset 0x0, size 0x4
            unsigned int PSM : 5; // offset 0x0, size 0x4
            unsigned int p0 : 12; // offset 0x0, size 0x4
            unsigned int DBX : 11; // offset 0x4, size 0x4
            unsigned int DBY : 11; // offset 0x4, size 0x4
            unsigned int p1 : 10; // offset 0x4, size 0x4
        } dispfb; // offset 0x10, size 0x8
        // total size: 0x8
        struct /* @anon8 */ {
            // Members
            unsigned int DX : 12; // offset 0x0, size 0x4
            unsigned int DY : 11; // offset 0x0, size 0x4
            unsigned int MAGH : 4; // offset 0x0, size 0x4
            unsigned int MAGV : 2; // offset 0x0, size 0x4
            unsigned int p0 : 3; // offset 0x0, size 0x4
            unsigned int DW : 12; // offset 0x4, size 0x4
            unsigned int DH : 11; // offset 0x4, size 0x4
            unsigned int p1 : 9; // offset 0x4, size 0x4
        } display; // offset 0x18, size 0x8
        // total size: 0x8
        struct /* @anon9 */ {
            // Members
            unsigned int R : 8; // offset 0x0, size 0x4
            unsigned int G : 8; // offset 0x0, size 0x4
            unsigned int B : 8; // offset 0x0, size 0x4
            unsigned int p0 : 8; // offset 0x0, size 0x4
            unsigned int p1; // offset 0x4, size 0x4
        } bgcolor; // offset 0x20, size 0x8
    } DispEnv[3]; // offset 0xC0, size 0x78
    struct shGsDrawEnv DrawEnv[3]; // offset 0x140, size 0x7E0
    struct shGsStencilDrawEnv StencilBuf[3]; // offset 0x920, size 0x870
    struct shGsTinyDrawEnv StencilWork[6]; // offset 0x1190, size 0x480
    union Q_WORDDATA DefaultEnv[10]; // offset 0x1610, size 0xA0
    union Q_WORDDATA StencilEnv[10]; // offset 0x16B0, size 0xA0
    union Q_WORDDATA CompshadowEnv[10]; // offset 0x1750, size 0xA0
    union Q_WORDDATA Filter_A[10]; // offset 0x17F0, size 0xA0
    union Q_WORDDATA Filter_B[10]; // offset 0x1890, size 0xA0
    union Q_WORDDATA Filter_C[10]; // offset 0x1930, size 0xA0
    union Q_WORDDATA Filter_D[10]; // offset 0x19D0, size 0xA0
    union Q_WORDDATA MoveGTex[8]; // offset 0x1A70, size 0x80
    union Q_WORDDATA GsReg_ALPHA_A[2]; // offset 0x1AF0, size 0x20
    union Q_WORDDATA GsReg_ALPHA_B[2]; // offset 0x1B10, size 0x20
    union Q_WORDDATA GsReg_ALPHA_C[2]; // offset 0x1B30, size 0x20
    union Q_WORDDATA GsReg_ALPHA_D[2]; // offset 0x1B50, size 0x20
    union Q_WORDDATA GsReg_ALPHA_E[2]; // offset 0x1B70, size 0x20
    union Q_WORDDATA GsReg_TEST_A[2]; // offset 0x1B90, size 0x20
    union Q_WORDDATA GsReg_TEST_B[2]; // offset 0x1BB0, size 0x20
    union Q_WORDDATA GsReg_TEST_C[2]; // offset 0x1BD0, size 0x20
    union Q_WORDDATA GsReg_TEST_D[2]; // offset 0x1BF0, size 0x20
    union Q_WORDDATA GsReg_TEXA_A[2]; // offset 0x1C10, size 0x20
    union Q_WORDDATA GsReg_TEXA_B[2]; // offset 0x1C30, size 0x20
    union Q_WORDDATA GsReg_ZBUF_A[2]; // offset 0x1C50, size 0x20
    union Q_WORDDATA GsReg_ZBUF_B[2]; // offset 0x1C70, size 0x20
    union Q_WORDDATA GsReg_PABE_A[2]; // offset 0x1C90, size 0x20
    union Q_WORDDATA GsReg_PABE_B[2]; // offset 0x1CB0, size 0x20
    union Q_WORDDATA GsReg_FBA_A[2]; // offset 0x1CD0, size 0x20
    union Q_WORDDATA GsReg_FBA_B[2]; // offset 0x1CF0, size 0x20
    union Q_WORDDATA GsReg_PRMODECONT_A[2]; // offset 0x1D10, size 0x20
    union Q_WORDDATA GsReg_PRMODECONT_B[2]; // offset 0x1D30, size 0x20
    union Q_WORDDATA GsSync_DummyLABEL[2]; // offset 0x1D50, size 0x20
    union Q_WORDDATA GsSync_DummyTEXFLUSH[2]; // offset 0x1D70, size 0x20
    struct shGsDrawEnv Now_DrawEnv; // offset 0x1D90, size 0x2A0
};

// total size: 0x44
struct PicDraw_Data {
    // Members
    struct sh2gfw_AREA_HEAD * ap; // offset 0x0, size 0x4
    signed int tex; // offset 0x4, size 0x4
    signed int clut; // offset 0x8, size 0x4
    signed short x0; // offset 0xC, size 0x2
    signed short y0; // offset 0xE, size 0x2
    signed short x1; // offset 0x10, size 0x2
    signed short y1; // offset 0x12, size 0x2
    signed short x2; // offset 0x14, size 0x2
    signed short y2; // offset 0x16, size 0x2
    signed short x3; // offset 0x18, size 0x2
    signed short y3; // offset 0x1A, size 0x2
    signed int us0; // offset 0x1C, size 0x4
    signed int vt0; // offset 0x20, size 0x4
    signed int us1; // offset 0x24, size 0x4
    signed int vt1; // offset 0x28, size 0x4
    unsigned char r; // offset 0x2C, size 0x1
    unsigned char g; // offset 0x2D, size 0x1
    unsigned char b; // offset 0x2E, size 0x1
    unsigned char a; // offset 0x2F, size 0x1
    unsigned char alpha_a; // offset 0x30, size 0x1
    unsigned char alpha_b; // offset 0x31, size 0x1
    unsigned char alpha_c; // offset 0x32, size 0x1
    unsigned char alpha_d; // offset 0x33, size 0x1
    unsigned char alpha_fix; // offset 0x34, size 0x1
    unsigned char test_ate; // offset 0x35, size 0x1
    unsigned char test_atst; // offset 0x36, size 0x1
    unsigned char test_aref; // offset 0x37, size 0x1
    unsigned char test_afail; // offset 0x38, size 0x1
    unsigned char test_date; // offset 0x39, size 0x1
    unsigned char test_datm; // offset 0x3A, size 0x1
    unsigned char test_zte; // offset 0x3B, size 0x1
    unsigned char test_ztst; // offset 0x3C, size 0x1
    unsigned char pad[3]; // offset 0x3D, size 0x3
    signed short otp; // offset 0x40, size 0x2
    signed short status; // offset 0x42, size 0x2
};

// total size: 0x60
struct Pad_KeyConfig {
    // Members
    signed int enter; // offset 0x0, size 0x4
    signed int cancel; // offset 0x4, size 0x4
    signed int skip; // offset 0x8, size 0x4
    signed int front_move; // offset 0xC, size 0x4
    signed int back_move; // offset 0x10, size 0x4
    signed int right_turn; // offset 0x14, size 0x4
    signed int left_turn; // offset 0x18, size 0x4
    signed int right_move; // offset 0x1C, size 0x4
    signed int left_move; // offset 0x20, size 0x4
    signed int action; // offset 0x24, size 0x4
    signed int attack; // offset 0x28, size 0x4
    signed int dash; // offset 0x2C, size 0x4
    signed int light; // offset 0x30, size 0x4
    signed int item; // offset 0x34, size 0x4
    signed int search_view; // offset 0x38, size 0x4
    signed int ready; // offset 0x3C, size 0x4
    signed int pause; // offset 0x40, size 0x4
    signed int map; // offset 0x44, size 0x4
    signed int padding[6]; // offset 0x48, size 0x18
};

// total size: 0x30
typedef struct _SH2_SYS {
    // Members
    unsigned int step[8]; // offset 0x0, size 0x20
    unsigned int pre_playable; // offset 0x20, size 0x4
    signed int main_status; // offset 0x24, size 0x4
    unsigned int soft_reset; // offset 0x28, size 0x4
    unsigned int frame_cnt; // offset 0x2C, size 0x4
} SH2_SYS;

void sh2gfw_Reset_FilterCommand();
int MovieWaitReady();
void sh2gfw_Set_PauseRetain();
int BgIsOut(int glb_crd /* r2 */);
int sh2gfw_FastSet_DispOnOffObj(int mapid /* r2 */, int dispflg /* r2 */);
void sh2gfw_Init_DispOnOffObj();
int sh2gfw_Set_DispOnOffObj(int mapid /* r2 */, int dispflg /* r2 */);
void sh2gfw_Black_Clear();
void PictureDraw(struct PicDraw_Data * pic /* r21 */);
void PictureLoadImage(struct sh2gfw_AREA_HEAD * ap /* r2 */, int otp /* r23 */, int tex_adr /* r22 */, int clut_adr /* r21 */);
int EvSubPictureDisplayOnly();
void EvSubPictureEnd();
void EvSubPictureFilter();
void EvSubPictureInit();
void EvSubPictureStart();
int fcRead(union fsFile * fp /* r17 */, void * buf /* r16 */);
int ScreenEffectFadeCheck();
void ScreenEffectFadeStart(int type /* r2 */, float time /* r29+0x10 */);
int fsSync(int mode /* r17 */, int fid /* r16 */);
int shPadTrigger(int port /* r17 */, int key /* r16 */);
int ItemUse(int kind /* r2 */);
void ItemGet(int kind /* r16 */);
int ItemUseSeTiming(int kind /* r2 */, int boa /* r2 */);
void fontClear();
int fontGetStatus();
void fontMessageNum(u_short * str /* r2 */, u_short num /* r2 */);
void SCNowPlayableEventSwitch(struct SubCharacter * scp /* r2 */, int flag /* r2 */);
int SeCall(int sd_no /* r17 */, float volume /* r20 */, int stereo /* r16 */);
int SeCallPos( int sd_no /* r20 */, float volume /* r20 */, float * pos /* r19 */, int status /* r18 */);
int shCharacter_Manage_Delete(struct SubCharacter * scp /* r2 */, short kind /* r2 */, short id /* r2 */);
void PictureDraw(struct PicDraw_Data * pic /* r21 */);
void PictureLoadImage(struct sh2gfw_AREA_HEAD * ap /* r2 */, int otp /* r23 */, int tex_adr /* r22 */, int clut_adr /* r21 */);
char * get_gp_data_buf_addr();
void shQzero(void *, int);

extern float ev_filter;
extern int ev_filter_on;
extern int ev_cancel;
extern int ev_prog_flag_set;
extern int ev_s_step;
extern char * layer_adr;
extern u_short msg_buffer[];
extern short item_to_chara[75];
extern struct shPlayerWork sh2jms;
extern SH2_SYS Sh2sys;
extern struct Pad_KeyConfig key_config;
extern struct shGsAllEnv shGs_AllEnv;

#endif
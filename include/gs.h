#ifndef SH_GS_H
#define SH_GS_H

/* miscellaneous GS/GIF helpers, with commentary from @Mc-muffin */

#include "sce/eetypes.h"
#include "macros.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Annoyingly, (v << 4) vs (u_int)(v * 16) causes regalloc issues
// Maybe they didn't want fractional coords xd
#define FP16(v) (((u_int)(v) << 4))
#define COORD(v) ((u_int)((v) * 16))

#define X_COORD(x) COORD((2048 - (SCREEN_WIDTH  / 2) + (x)))
#define Y_COORD(y) COORD((2048 - (SCREEN_HEIGHT / 2) + (y)))

// First, let's consider the (64bit) registers where X and Y are in as a either packed short list
// 64              48           32              16            0
//  *----------------------------*----------------------------*
//  |     VV.3     |     VV.2    |      VV.1    |     VV.0    | --> Full 64bit register
//  *----------------------------*----------------------------*

// or... a packed int list
// 64                           32                            0
//  *----------------------------*----------------------------*
//  |            VV.1            |            VV.0            | --> Full 64bit register
//  *----------------------------*----------------------------*

// Then PEXTLH $RD, $RS, $RT will interleave rs and rt shorts into the bigger
// 128bit register, like so:
//                                                           64              48           32              16            0
//                                                            *----------------------------*----------------------------*
//                                   ________________________ |     RD.3     |     RD.2    |      RD.1    |     RD.0    | -> RS
//           _______________________/                          *----------------------------*----------------------------*
//          /                                ______________________________________/               /    __________/
//         /                               /                           ,__________________________/    /
// 128    V        112           96       V     80           64       V      48            32        V    16            0
//  *----------------------------*----------------------------*----------------------------*----------------------------*
//  |     RD.3     |     RT.3    |      RD.3    |     RT.2    |     RD.1     |     RT.1    |      RD.0    |     RT.0    | -> RD
//  *----------------------------*----------------------------*----------------------------*----------------------------*
//                        A                            A________________________.    A___________.                A
//                         \_________________                                    \                \               |
//                                           \________        *----------------------------*----------------------------*
//                                                     \----- |     RT.3     |     RT.2    |      RT.1    |     RT.0    | -> RT
//                                                            *----------------------------*----------------------------*
//                                                           64              48           32              16            0

// Then PEXTLW $RD, $RS, $RT will interleave rs and rt as ints into the bigger
// 128bit register, like so:
//                                                           64                            32                           0
//                                                            *----------------------------*----------------------------*
//                                                            |            RS.1            |              RS.0          | -> RS
//                                                            *----------------------------*----------------------------*
//                  ________________________________________________________/   ___________________________/
//                 /                                                           /
// 128            V              96                           64              V            32                           0
//  *----------------------------*----------------------------*----------------------------*----------------------------*
//  |            RS.1            |            RT.1            |            RS.0            |             RT.0           | -> RD
//  *----------------------------*----------------------------*----------------------------*----------------------------*
//                                              A__________________________.                              A
//                                                                          \                             |
//                                                            *----------------------------*----------------------------*
//                                                            |            RT.1            |              RT.0          | -> RT
//                                                            *----------------------------*----------------------------*
//                                                           64                           32                            0

// As X and Y are 32bit in our version, then we can only pack 2 16bit values
// with the rest being garbage, so in the first operation RD ends up as:
//      / ------------------------------- [garbage top 64bit] ------------------------------- \
// RD  = (Y.as_u16[3] << 112) | (X.as_u16[3] << 96) | (Y.as_u16[2] << 80) | (X.as_u16[2] << 64);

//      / --------------- [garbage] ------------- \
// RD |= (Y.as_u16[1] <<  48) | (X.as_u16[1] << 32) | (Y.as_u16[0] << 16) | (X.as_u16[0] << 00);

// Then PEXTLW comes along to interleave Z:
//      / ------------ [garbage] -------- \
// RD = (Z.as_u32[1] << 96) | (XY[1] << 64) | (Z.as_u32[0] << 32) | (XY[0] << 00);

// Crucially though, the final register is used as a 64bit store, thus the garbage is not
// important, and the 2 instructions are effectively just packing a SCE_GS_SET_XYZ blazingly fast!
static inline long ASM_GS_SET_XYZ(int x, int y, int z) {
    long a;
    asm("pextlh %0, %2, %1;\
         pextlw %0, %3, %0" : "+r"(a) : "r"(x), "r"(y), "r"(z));
    return a;
}

#define PP_NARG(...) \
    PP_NARG_(__VA_ARGS__, PP_RSEQ_N())

#define PP_NARG_(...) \
    PP_ARG_N(__VA_ARGS__)

#define PP_ARG_N( \
     _1,_2,_3,_4,_5,_6,_7,_8,_9,_10, \
    _11,_12,_13,_14,_15,_16,N,...) N

#define PP_RSEQ_N() \
    16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0

#define CAT(a,b) CAT_(a,b)
#define CAT_(a,b) a##b

#define GIF_REGLIST(...) \
    CAT(GIF_REGLIST_, PP_NARG(__VA_ARGS__))(__VA_ARGS__)

#define GIF_REGLIST_1(a0) \
    ((long)(a0) << (0 * 4))

#define GIF_REGLIST_2(a0,a1) \
    ((long)(a0) << (0 * 4)) | \
    ((long)(a1) << (1 * 4))

#define GIF_REGLIST_3(a0,a1,a2) \
    ((long)(a0) << (0 * 4)) | \
    ((long)(a1) << (1 * 4)) | \
    ((long)(a2) << (2 * 4))

#define GIF_REGLIST_4(a0,a1,a2,a3) \
    ((long)(a0) << (0 * 4)) | \
    ((long)(a1) << (1 * 4)) | \
    ((long)(a2) << (2 * 4)) | \
    ((long)(a3) << (3 * 4))

#define GIF_REGLIST_5(a0,a1,a2,a3,a4) \
    ((long)(a0) << (0 * 4)) | \
    ((long)(a1) << (1 * 4)) | \
    ((long)(a2) << (2 * 4)) | \
    ((long)(a3) << (3 * 4)) | \
    ((long)(a4) << (4 * 4))

#define GIF_REGLIST_6(a0,a1,a2,a3,a4,a5) \
    ((long)(a0) << (0 * 4)) | \
    ((long)(a1) << (1 * 4)) | \
    ((long)(a2) << (2 * 4)) | \
    ((long)(a3) << (3 * 4)) | \
    ((long)(a4) << (4 * 4)) | \
    ((long)(a5) << (5 * 4))

#define GIF_REGLIST_7(a0,a1,a2,a3,a4,a5,a6) \
    ((long)(a0) << (0 * 4)) | \
    ((long)(a1) << (1 * 4)) | \
    ((long)(a2) << (2 * 4)) | \
    ((long)(a3) << (3 * 4)) | \
    ((long)(a4) << (4 * 4)) | \
    ((long)(a5) << (5 * 4)) | \
    ((long)(a6) << (6 * 4))

#define GIF_REGLIST_8(a0,a1,a2,a3,a4,a5,a6,a7) \
    ((long)(a0)  << (0  * 4)) | \
    ((long)(a1)  << (1  * 4)) | \
    ((long)(a2)  << (2  * 4)) | \
    ((long)(a3)  << (3  * 4)) | \
    ((long)(a4)  << (4  * 4)) | \
    ((long)(a5)  << (5  * 4)) | \
    ((long)(a6)  << (6  * 4)) | \
    ((long)(a7)  << (7  * 4))

#define GIF_REGLIST_9(a0,a1,a2,a3,a4,a5,a6,a7, \
                 a8) \
    ((long)(a0)  << (0  * 4)) | \
    ((long)(a1)  << (1  * 4)) | \
    ((long)(a2)  << (2  * 4)) | \
    ((long)(a3)  << (3  * 4)) | \
    ((long)(a4)  << (4  * 4)) | \
    ((long)(a5)  << (5  * 4)) | \
    ((long)(a6)  << (6  * 4)) | \
    ((long)(a7)  << (7  * 4)) | \
    ((long)(a8)  << (8  * 4))

#define GIF_REGLIST_10(a0,a1,a2,a3,a4,a5,a6,a7, \
                 a8,a9) \
    ((long)(a0)  << (0  * 4)) | \
    ((long)(a1)  << (1  * 4)) | \
    ((long)(a2)  << (2  * 4)) | \
    ((long)(a3)  << (3  * 4)) | \
    ((long)(a4)  << (4  * 4)) | \
    ((long)(a5)  << (5  * 4)) | \
    ((long)(a6)  << (6  * 4)) | \
    ((long)(a7)  << (7  * 4)) | \
    ((long)(a8)  << (8  * 4)) | \
    ((long)(a9)  << (9  * 4))

#define GIF_REGLIST_11(a0,a1,a2,a3,a4,a5,a6,a7, \
                 a8,a9,a10) \
    ((long)(a0)  << (0  * 4)) | \
    ((long)(a1)  << (1  * 4)) | \
    ((long)(a2)  << (2  * 4)) | \
    ((long)(a3)  << (3  * 4)) | \
    ((long)(a4)  << (4  * 4)) | \
    ((long)(a5)  << (5  * 4)) | \
    ((long)(a6)  << (6  * 4)) | \
    ((long)(a7)  << (7  * 4)) | \
    ((long)(a8)  << (8  * 4)) | \
    ((long)(a9)  << (9  * 4)) | \
    ((long)(a10) << (10 * 4))

#define GIF_REGLIST_12(a0,a1,a2,a3,a4,a5,a6,a7, \
                 a8,a9,a10,a11) \
    ((long)(a0)  << (0  * 4)) | \
    ((long)(a1)  << (1  * 4)) | \
    ((long)(a2)  << (2  * 4)) | \
    ((long)(a3)  << (3  * 4)) | \
    ((long)(a4)  << (4  * 4)) | \
    ((long)(a5)  << (5  * 4)) | \
    ((long)(a6)  << (6  * 4)) | \
    ((long)(a7)  << (7  * 4)) | \
    ((long)(a8)  << (8  * 4)) | \
    ((long)(a9)  << (9  * 4)) | \
    ((long)(a10) << (10 * 4)) | \
    ((long)(a11) << (11 * 4))

#define GIF_REGLIST_13(a0,a1,a2,a3,a4,a5,a6,a7, \
                 a8,a9,a10,a11,a12) \
    ((long)(a0)  << (0  * 4)) | \
    ((long)(a1)  << (1  * 4)) | \
    ((long)(a2)  << (2  * 4)) | \
    ((long)(a3)  << (3  * 4)) | \
    ((long)(a4)  << (4  * 4)) | \
    ((long)(a5)  << (5  * 4)) | \
    ((long)(a6)  << (6  * 4)) | \
    ((long)(a7)  << (7  * 4)) | \
    ((long)(a8)  << (8  * 4)) | \
    ((long)(a9)  << (9  * 4)) | \
    ((long)(a10) << (10 * 4)) | \
    ((long)(a11) << (11 * 4)) | \
    ((long)(a12) << (12 * 4))

#define GIF_REGLIST_14(a0,a1,a2,a3,a4,a5,a6,a7, \
                 a8,a9,a10,a11,a12,a13) \
    ((long)(a0)  << (0  * 4)) | \
    ((long)(a1)  << (1  * 4)) | \
    ((long)(a2)  << (2  * 4)) | \
    ((long)(a3)  << (3  * 4)) | \
    ((long)(a4)  << (4  * 4)) | \
    ((long)(a5)  << (5  * 4)) | \
    ((long)(a6)  << (6  * 4)) | \
    ((long)(a7)  << (7  * 4)) | \
    ((long)(a8)  << (8  * 4)) | \
    ((long)(a9)  << (9  * 4)) | \
    ((long)(a10) << (10 * 4)) | \
    ((long)(a11) << (11 * 4)) | \
    ((long)(a12) << (12 * 4)) | \
    ((long)(a13) << (13 * 4))

#define GIF_REGLIST_15(a0,a1,a2,a3,a4,a5,a6,a7, \
                 a8,a9,a10,a11,a12,a13,a14) \
    ((long)(a0)  << (0  * 4)) | \
    ((long)(a1)  << (1  * 4)) | \
    ((long)(a2)  << (2  * 4)) | \
    ((long)(a3)  << (3  * 4)) | \
    ((long)(a4)  << (4  * 4)) | \
    ((long)(a5)  << (5  * 4)) | \
    ((long)(a6)  << (6  * 4)) | \
    ((long)(a7)  << (7  * 4)) | \
    ((long)(a8)  << (8  * 4)) | \
    ((long)(a9)  << (9  * 4)) | \
    ((long)(a10) << (10 * 4)) | \
    ((long)(a11) << (11 * 4)) | \
    ((long)(a12) << (12 * 4)) | \
    ((long)(a13) << (13 * 4)) | \
    ((long)(a14) << (14 * 4))

#define GIF_REGLIST_16(a0,a1,a2,a3,a4,a5,a6,a7, \
                 a8,a9,a10,a11,a12,a13,a14,a15) \
    ((long)(a0)  << (0  * 4)) | \
    ((long)(a1)  << (1  * 4)) | \
    ((long)(a2)  << (2  * 4)) | \
    ((long)(a3)  << (3  * 4)) | \
    ((long)(a4)  << (4  * 4)) | \
    ((long)(a5)  << (5  * 4)) | \
    ((long)(a6)  << (6  * 4)) | \
    ((long)(a7)  << (7  * 4)) | \
    ((long)(a8)  << (8  * 4)) | \
    ((long)(a9)  << (9  * 4)) | \
    ((long)(a10) << (10 * 4)) | \
    ((long)(a11) << (11 * 4)) | \
    ((long)(a12) << (12 * 4)) | \
    ((long)(a13) << (13 * 4)) | \
    ((long)(a14) << (14 * 4)) | \
    ((long)(a15) << (15 * 4))


#endif // SH_GS_H

#ifndef SH_GS_H
#define SH_GS_H

/* miscellaneous GS/GIF helpers, with commentary from @Mc-muffin */

#include "sce/eetypes.h"

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

#endif // SH_GS_H

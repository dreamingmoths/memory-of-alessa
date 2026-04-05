#include "cl_calc.h"

/*
    p = pl->p;
    vf4 = p[0];
    vf5 = p[1];
    vf6 = p[2];
    vf7 = vf5 - vf4;
    vf5 = vf6 - vf5;
    vf6.w = vf6.w - vf6.w;
    vf6 = cross(vf5, vf7);
    vf4.x = inner(vf6, vf4);
    vf6.w = vf6.w - vf6.w;
    vf6.w -= vf4.x;
    p[0] = vf6;
*/

void clCalcPlaneEquation(CL_HITPOLY_PLANE * pl, float * pparam) {
    sceVu0FMATRIX* p = &pl->p;
    asm ("lqc2            $vf4,    0(%0)   \n\
          lqc2            $vf5, 0x10(%0)   \n\
          lqc2            $vf6, 0x20(%0)   \n\
          vsub.xyzw       $vf7, $vf5, $vf4 \n\
          vsub.xyzw       $vf5, $vf6, $vf5 \n\
          vsub.w          $vf6, $vf6, $vf6 \n\
          vopmula.xyz     $acc, $vf5, $vf7 \n\
          vopmsub.xyz     $vf6, $vf7, $vf5 \n\
          vmul.xyz        $vf4, $vf6, $vf4 \n\
          vaddy.x         $vf4, $vf4, $vf4y\n\
          vaddz.x         $vf4, $vf4, $vf4z\n\
          vsub.w          $vf6, $vf6, $vf6 \n\
          vsubx.w         $vf6, $vf6, $vf4x\n\
          sqc2            $vf6, 0(%1)" : "+r"(p) : "r"(pparam));
}

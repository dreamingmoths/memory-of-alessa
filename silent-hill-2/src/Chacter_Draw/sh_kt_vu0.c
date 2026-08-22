#include "sh2_common.h"
#include "sce/libvu0.h"

/* apply a 4x4 matrix to a vector */
asm void ktVu0ApplyMatrixXYZ1(register float* v0, register sceVu0FMATRIX m0, register float* v1)  {
    lqc2 $vf4, 0x0($a1)
    lqc2 $vf5, 0x10($a1)
    lqc2 $vf6, 0x20($a1)
    lqc2 $vf7, 0x30($a1)
    lqc2 $vf8, 0x0($a2)
    vmulax.xyzw $acc, $vf4, $vf8x
    vmadday.xyzw $acc, $vf5, $vf8y
    vmaddaz.xyzw $acc, $vf6, $vf8z
    vmaddw.xyzw $vf12, $vf7, $vf0w
    sqc2 $vf12, 0x0($a0)

    
    jr ra
    nop
}

/* apply a 3x3 matrix to a vector */
asm void ktVu0ApplyMatrixXYZ0(register float* v0, register sceVu0FMATRIX m0, register float* v1) {
    lqc2 $vf4, 0x0($a1)
    lqc2 $vf5, 0x10($a1)
    lqc2 $vf6, 0x20($a1)
    lqc2 $vf8, 0x0($a2)
    vmulax.xyzw $acc, $vf4, $vf8x
    vmadday.xyzw $acc, $vf5, $vf8y
    vmaddz.xyzw $vf12, $vf6, $vf8z
    sqc2 $vf12, 0x0($a0)
    
    
    jr ra
    nop
}

/* convert float vector to integer */
asm void ktVu0FTOI4VectorXYZ(register int* v0, register float* v1)  {
    lqc2 $vf4, 0x0($a1)
    vftoi4.xyz $vf5, $vf4
    sqc2 $vf5, 0x0($a0)

    
    jr ra
    nop
}

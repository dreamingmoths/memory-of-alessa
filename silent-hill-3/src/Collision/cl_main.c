#include "common.h"
#include "vec.h"

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clAllInitCollisionData);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_0019F820);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCollectCharaPosition);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clSetCharaHitColumn);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_0019FD50);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A04A0);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A05F0);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A0670);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clAddDynamicWall);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clAddDynamicFloor);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A0790);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A07E0);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A08F0);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCollectCharaALL);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A1030);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckBg2Chara);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A1630);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A1830);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A1A50);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clAddWallCollectVector);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckColumn2WallHit);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A2370);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A2460);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A2530);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A2690);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A27A0);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A29F0);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A2A50);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A2AE0);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A31E0);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A3340);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A35A0);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A3890);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A3B20);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A3C80);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A3E10);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A3E80);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A3EB0);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A4070);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A4330);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A45F0);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A48B0);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitThrustSwordVector);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A4D20);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A4D30);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitThrustGunVectorCharacter);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A5270);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A52D0);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A55A0);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", Line2PlaneBoundaryCheckXZ);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckCrossLine2BoxXZ);

int clCheckCrossLine2LineXZ(float * va0, float * va1, float * vb0, float * vb1) {
    float bp[4];
    float p0[4];
    float p1[4];
    float outer0;
    float outer1;
    vec_sub(va1, va0, bp);
    vec_sub(vb0, va0, p0);
    vec_sub(vb1, va0, p1);
    outer0 = bp[0] * p0[2] - bp[2] * p0[0];
    outer1 = bp[0] * p1[2] - bp[2] * p1[0];
    if (outer0 == 0.0f && outer1 == 0.0f) {
        if ((va0[0] <= float_max(vb0[0], vb1[0])  &&
             va0[0] >= float_min(vb0[0], vb1[0])  &&
             va0[2] <= float_max(vb0[2], vb1[2])  &&
             va0[2] >= float_min(vb0[2], vb1[2])) ||
            (va1[0] <= float_max(vb0[0], vb1[0])  &&
             va1[0] >= float_min(vb0[0], vb1[0])  &&
             va1[2] <= float_max(vb0[2], vb1[2])  &&
             va1[2] >= float_min(vb0[2], vb1[2])) ||
            (vb0[0] <= float_max(va0[0], va1[0])  &&
             vb0[0] >= float_min(va0[0], va1[0])  &&
             vb0[2] <= float_max(va0[2], va1[2])  &&
             vb0[2] >= float_min(va0[2], va1[2])) ||
            (vb1[0] <= float_max(va0[0], va1[0])  &&
             vb1[0] >= float_min(va0[0], va1[0])  &&
             vb1[2] <= float_max(va0[2], va1[2])  &&
             vb1[2] >= float_min(va0[2], va1[2]))
        ) {
            return 1;
        }
        return 0;
    }

    if (outer0 * outer1 >= 0.0f) {
        return 0;
    }
    vec_sub(vb1, vb0, bp);
    vec_sub(va0, vb0, p0);
    vec_sub(va1, vb0, p1);
    outer0 = bp[0] * p0[2] - bp[2] * p0[0];
    outer1 = bp[0] * p1[2] - bp[2] * p1[0];
    if (outer0 * outer1 >= 0.0f) {
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A5B60);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clGetHitSectListMOVEOutDoor);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A5DA0);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A5E20);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A6430);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A6480);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A6490);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A64A0);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A64C0);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A6760);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitEyeVectorBGColumn);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitEyeVectorCharacter);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A6D30);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A6F70);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A7120);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A7250);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A7450);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", func_001A7660);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clPermitColumnExpansion);

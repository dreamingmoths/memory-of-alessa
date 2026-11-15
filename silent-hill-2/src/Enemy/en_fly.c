#include "sh2_common.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2dt.h"

#include "vec.h"

#include "Enemy/en_common.h"
#include "Enemy/en_fly.h"

EN_FLY_DATA fly; // size: 0x2D0, address: 0x116E670

#define FLY_INS() ((EnINS_DATA*  ) (&fly.dp.ins ))
#define FLY_SCP() ((SubCharacter*) (&fly.scp    ))
#define FLY_POS() ((Vector4*     ) (&fly.scp.pos))

#line 39
void flyInit(float* pos) {
    // fly! what is it?? i'm not really sure. apparently this spawns in room 0x3A, which in retail is where James gets up in the basement after falling from the third hole in the prison
    shQzero(&fly, sizeof(fly));
    fly.dp.scp = &fly.scp;
    shVectorCopyVu0(&fly.scp.pos, pos);
    fly.scp.rot.y = PI * (shRandF() - 0.5f) * 2.0f;
    fly.dp.flag = 1 << 8;
    enInitPath(&fly.dp.path, fly.scp.rot.y);
    FLY_INS()->view_rot[0] = pos[1];
    FLY_INS()->view_rot[1] = 0.0f;
    FLY_INS()->view_rot[2] = pos[1] - 500.0f;
    FLY_INS()->view_rot[3] = 500.0f + pos[1];
}


#line 54
void flyMove(void) {
    sceVu0FVECTOR vec;
    FLY_INS()->view_rot[1] = 0.95f * ((shSway1f(-25.0f, 0.1f) + FLY_INS()->view_rot[1]) - (FLY_POS()->y - FLY_INS()->view_rot[0]) * 0.01f);
    
    FLY_POS()->y += FLY_INS()->view_rot[1];
    if (FLY_POS()->y < FLY_INS()->view_rot[2]) FLY_POS()->y = FLY_INS()->view_rot[2];
    if (FLY_POS()->y > FLY_INS()->view_rot[3]) FLY_POS()->y = FLY_INS()->view_rot[3];
    FLY_INS()->rot_add[1] = ((FLY_INS()->rot_add[1] + shSway1f(TO_RAD(-2), 0.1f)) - FLY_INS()->rot_add[0] * 0.01f) * 0.95f;
    
    FLY_INS()->rot_add[0] = 0.95f * (FLY_INS()->rot_add[0] + FLY_INS()->rot_add[1]);
    shSinCosV_Scale(vec, fly.scp.rot.y + FLY_INS()->rot_add[0], 500.0f); // ?
    shAddVector(vec, &fly.scp.pos, vec);
    if (enSetPath(&fly.dp, vec, FLY_POS())) {
        fly.dp.path.angle = fly.dp.path.markangle;
        FLY_INS()->rot_add[0] = FLY_INS()->rot_add[1] = 0.0f;
    }
    enMoveAngle(&fly.dp.path, TO_RAD(15));
    shSinCosV_Scale(vec, (fly.scp.rot.y = fly.dp.path.angle), 1500.0f * shGetDT());
    shAddVectorXyz(vec, FLY_POS(), FLY_POS());
    #line 98
}

#line 101
void flyGetPos(float* pos) {
    shVectorCopy(pos, &fly.scp.pos);
}

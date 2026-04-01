#include "vc_play.h"

static inline float vec2_length(float* a, float* b) {
    float result;
    asm volatile("
        lwc1   $f20,0(%1)
        lwc1   $f8,0(%2)
        mula.s $f20, $f20
        madd.s %0, $f8, $f8
        sqrt.s %0, %0"
        : "=f"(result) : "m"(a), "m"(b) : "f20", "f8");
    return result;
}

void vcPreSetCharaDataForCamera(void) {

    struct SubCharacter * sc; // r16
    
    sc = sh2jms.player;
    sys.hero.pos[0] = sc->pos.x;
    sys.hero.pos[1] = sc->pos.y;
    sys.hero.pos[2] = sc->pos.z;
    sys.hero.ang[0] = sc->rot.x;
    sys.hero.ang[1] = sc->rot.y;
    sys.hero.ang[2] = sc->rot.z;
    sys.hero.rot_spd[0] = sc->rot_spd.x;
    sys.hero.rot_spd[1] = sc->rot_spd.y;
    sys.hero.rot_spd[2] = sc->rot_spd.z;
    sys.hero.velo_y = 500.0f * sc->pos_spd.y;
    sys.hero.velo_houi = shAtan2(sc->pos_spd.x, sc->pos_spd.z);
    sys.hero.velo_xz = 500.0f * vec2_length(&sc->pos_spd.x, &sc->pos_spd.z) * shGetFPS();
    vcPreInfo.hero_eye_y = sc->eye_y;
    vcPreInfo.hero_head_ang_x = PlayerGetNeckAngleX();
    vcPreInfo.hero_head_ang_y = PlayerGetNeckAngleY();
    GetPlayerPartsWorldMatrix(vcPreInfo.hero_neck_wm, 8);
    GetPlayerPartsLocalMatrix(vcPreInfo.hero_neck_lm, 8);
    shMulMatrix(vcPreInfo.hero_neck_lwm, vcPreInfo.hero_neck_wm, vcPreInfo.hero_neck_lm);
}

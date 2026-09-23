#include "common.h"

extern float D_0038A3E0;

void func_0023A0B0(float arg) {
    D_0038A3E0 = arg;
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_effect_object_texture", LocalWrapper_TextureTransport_Entry);

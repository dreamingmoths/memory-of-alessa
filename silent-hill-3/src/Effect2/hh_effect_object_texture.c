#include "common.h"

extern f32 D_0038A3E0;

void func_0023A0B0(f32 arg) {
    D_0038A3E0 = arg;
}

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_effect_object_texture", LocalWrapper_TextureTransport_Entry);

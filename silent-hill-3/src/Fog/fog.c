#include "common.h"
#include "Fog/fog.h"

extern FOG_WORK fwork;
extern FOG_PACK_WORK pwork;

extern /* static */ FOG_ASM_DATA_P fog_asm_data_p; // size: 0x20, address: 0x2AB4E0

void fogInit(void) {
    shQzero(&fwork, sizeof fwork);
    func_001E6B90();
    fog_asm_data_p.packet = UNCACHED(&pwork);
    fogSetColor(0x80, 0x80, 0x80, 0x80);
    func_001EB090();
    func_001E74F0();
}


INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001E6B90);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetEnvironment);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001E74F0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001E7520);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogChangeWind);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogInitParticle);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_init_part_sub);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_newpos);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogResetWall);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetWall);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogResetObj);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetObj);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001E8470);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogGetObj);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogMoveParticle);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_load_objdata);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_set_stay);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_wall);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001E91E0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_obj);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_obj2);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_alp);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_clamp);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogMakePacket);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_view_screen_fog);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetColor);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetPartNum);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetProjection);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA580);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA5C0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA5E0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA610);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetWorldPosV);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA670);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA6A0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA6C0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA6D0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetLocalPosV);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA980);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA9A0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA9C0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA9E0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetSpeedLevel);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EAA10);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EAA60);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EAA80);

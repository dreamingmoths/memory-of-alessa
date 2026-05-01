#include "sh2_common.h"
#include "Fog/fog.h"

extern FOG_WORK fwork; // size: 0x15E90, address: 0x56B6D0
extern FOG_PACK_WORK pwork; // size: 0x19010, address: 0x5526C0
extern FOG_WORK2 fwork2; // size: 0x58, address: 0x1202E70

extern /* static */ FOG_ASM_DATA1 fog_asm_data1; // size: 0x70, address: 0x2AB400
extern /* static */ FOG_ASM_DATA2 fog_asm_data2; // size: 0x70, address: 0x2AB470
extern /* static */ FOG_ASM_DATA_P fog_asm_data_p; // size: 0x20, address: 0x2AB4E0
extern /* static */ FOG_ASM_DATA3 fog_asm_data3; // size: 0x10, address: 0x2AB500

void fogInit(void) {
    shQzero(&fwork, sizeof fwork);
    shQzero(&fwork2, sizeof fwork2);
    if (!pwork.pk_env) {
        fog_set_defpacket();
    }
    fog_asm_data_p.packet = UNCACHED(&pwork);
    fogSetAreaEnvironment();
    fogSetCollision();
    fogSetColor(0x80, 0x80, 0x80, 0x80);
    fogInitScreen();
}


INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_set_defpacket);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetEnvironment);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogInitScreen);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogInitWind);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogChangeWind);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogInitParticle);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_init_part_sub);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_newpos);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogResetWall);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetWall);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogResetObj);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetObj);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogMoveObj);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetObj2);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogEraseObj);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetObjSize);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogGetObj);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogMoveParticle);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_load_objdata);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_set_stay);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_wall);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_grid);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_obj);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_obj2);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_alp);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_clamp);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogMakePacket);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_view_screen_fog);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetColor);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetPartNum);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetProjection);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetFloorY);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetWorldScreenM);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetWorldViewM);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetWorldPosV);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetStayPos);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogResetStayPos);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetStayPoint);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogResetStayPoint);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetCameraPosV);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetLocalPosV);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetSpeedLevel);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogTex0Adr);

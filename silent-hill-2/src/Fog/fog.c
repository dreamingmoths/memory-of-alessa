#include "sh2_common.h"
#include "Fog/fog.h"
#include "SH2_common/sh_vu0.h"
#include "Font/fj_man.h"

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

void fogSetEnvironment(FOG_ENV_DATA* edata) {
    float d; // r1
    float m; // r20
    u_char f; // r16
    u_char f2; // r17
    char Double; // r2
    int old; // r2

    if (edata == fwork.EnvNow) {
        if ((fwork.WindTimer -= shGetDF()) <= 0) {
            fogChangeWind(fwork.WindDef);
        }
        return;
    }
    fwork.EnvNow = edata;
    if (!edata) {
        fwork.PartNum = 0;
        fwork.EnvNow = NULL;
        return;
    }
    f = edata->Flag;
    m = edata->MaxPos;
    f2 = 0;
    if (edata->MaxPos > 2000.0f + fwork.MaxPos) f2 = 1;
    fwork.MaxPos = m;
    fog_asm_data1.maxpos = m;

    fog_asm_data1.maxpos_x2 = 2.0f * m;
    fog_asm_data1.screendiv = 4.0f / m;
    fog_asm_data1.r_maxpos = 2.0f / m;
    fog_asm_data3.maxpos = m;
    d = edata->PartSize;
    fwork.PartSize = d;
    fog_asm_data1.part_size = d;
    fog_asm_data1.wall_range = 10.0f + d;
    fog_asm_data2.part_size = d;
    fog_asm_data2.r_part_size = 1.0f / d;
    d = edata->EscapeRange;
    fwork.EscapeRange = d;
    fog_asm_data1.escape_range = d;
    fog_asm_data1.r_escape_range = 1.0f / d;
    d = edata->FloorY;
    fwork.FloorY = d;
    fog_asm_data2.floor_y = d;
    fwork.WaterY = edata->WaterY;
    
    old = fwork.WindDef;
    fwork.WindDef = edata->WindDef;
    if (fwork.WindDef != old) {
        if (fwork.Global == 5) {
            fogInitWind();
        } else {
            fogChangeWind(fwork.WindDef);
        }
    }
    if (f & 1) {
        fwork.LimitY = edata->LimitY;
        fwork.LimitY2 = edata->LimitY - edata->LimitHeight;
        fog_asm_data1.r_height = 1.0f / edata->LimitHeight;
    } else {
        fwork.LimitY = -MAX_FLOAT;
    }
    Double = edata->Double;
    fwork.Double = Double;
    if (1 < Double) {
        d = (1 << (Double - 1));
        fog_asm_data3.r_double = 1.0f / d;
    } else {
        d = 1.0f;
        fog_asm_data3.r_double = 1.0f;
    }
    fog_asm_data1.double_rate = 1 << Double;
    d = m / d;
    fog_asm_data1.higher_y = Double < 2 ? m : d;
    fog_asm_data1.lower_y = Double == 0 ? m : 0.0f;
    fog_asm_data1.y_max = Double == 0 ? 2.0f * m : d;
    fog_asm_data1.higher_y2 = 2.0f * (Double < 2 ? m : d);
    fwork.Alpha = edata->Alpha;
    d = edata->Alpha;
    fog_asm_data1.alpha = d;
    fog_asm_data1.minus_alpha = -d / 32.0f;
    fwork.GridRate = edata->GridRate;
    if (sh2gfw_Get_NightOrDay() && fwork.Global < 5) {
        int v = edata->PartNum >> 1; // not part of dwarf, and nonmatching line numbers
        fogSetPartNum(edata->PartNum < 0 ? ((edata->PartNum + 1) >> 1) : v);
    } else {
        fogSetPartNum(edata->PartNum);
    }
    fwork.Flag = (fwork.Flag & 0xff00) | f;
    if (f2) fogInitParticle();
}

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogInitScreen);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogInitWind);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogChangeWind);

void fogInitParticle(void) {
    int i;
    FOG_PART_DATA* pd = &fwork;
    for (i = fwork.PartNum; i > 0; i--) {
        fog_init_part_sub(pd++);
    }
    *(u_long128*) &fwork.sc_degree = 0;
    fwork.sc_degree[2] = -1.0f;
    fwork.sc_tdx = shRandF();
    fwork.sc_tdy = shRandF();
}

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_init_part_sub);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_newpos);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogResetWall);

#define WALL_MAX 0xBC
void fogSetWall(void* Vector) {
    float (* wv)[4] = Vector; // r16
    FOG_WALL_DATA* wall = &fwork.Wall[fwork.WallNum++]; // r17
    int i; // r3
    float cv[4]; // r29+0x30
    fjAssert(fwork.WallNum <= WALL_MAX, "fog.c", 602);
    shSetMiniMaxN(wall->min, wall->max, wv, 4);
    wall->min[0] -= 10.0f;
    wall->min[2] -= 10.0f;
    wall->max[0] += 10.0f;
    wall->max[2] += 10.0f;
    wall->max[3] = 0.0f, wall->min[3] = 0.0f;
    *(u_long128*) &cv = 0;
    for (i = 0; i < 4; i++) {
        vec_add(cv, wv[i], cv);
    }
    vec_scale(0.25, cv, wall->v0);
    shCreateNormal(wall->normal, wv[0], wv[1], wv[2]);
}

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogResetObj);

#define OBJ_MAX 168
void fogSetObj(u_long ID, void* Center, float Size) {
    FOG_OBJ_DATA* od = fogGetObj(ID);;
    if (!od) {
        fjAssert(fwork.ObjMax < OBJ_MAX, "fog.c", 634);
        od = &fwork.Obj[fwork.ObjMax++];
    }
    vec_copy(od->pos, Center);
    vec_zero(od->mv);
    od->pos[3] = Size;
    od->mv[3] = fwork.EscapeRange;
    od->rer = 1.0f / fwork.EscapeRange;
    od->id = ID;
    od->type = 0;
}

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogMoveObj);

void fogSetObj2(u_long ID, void* Center, float Size) {
    FOG_OBJ_DATA* od = fogGetObj(ID);
    if (!od) {
        fjAssert(fwork.ObjMax < OBJ_MAX, "fog.c", 685);
        od = &fwork.Obj[fwork.ObjMax++];
    }
    vec_copy(od->pos, Center);
    vec_zero(od->mv);
    od->pos[3] = Size;
    od->mv[3] = fwork.EscapeRange;
    od->rer = 1.0f / fwork.EscapeRange;
    od->id = ID;
    od->type = 1;
}

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogEraseObj);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetObjSize);

FOG_OBJ_DATA* fogGetObj(u_long ID) {
    FOG_OBJ_DATA* pObj = fwork.Obj;
    int i;
    for (i = fwork.ObjMax; i > 0; i--) {
        if (pObj->id == ID) {
            return pObj;
        }
        pObj++;
    }
    return NULL;
}

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

#include "sh2_common.h"
#include "shared/Fog/fog.h"
#include "Fog/fog.h"
#include "SH2_common/sh_vu0.h"
#include "Font/fj_man.h"
#include "vec.h"

#pragma fast_fptosi on

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

INCLUDE_RODATA("asm/nonmatchings/Fog/fog", @966_0x0038E910);

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

void fogInitScreen(void) {
    fogInitWind();
    fogInitParticle();
    fogInitParticle2();
}

void fogInitWind(void) {
    vec_zero(fwork.WindV);
    fogChangeWind(fwork.WindDef);
    shFill(&fwork.GridDense, 0x3f800000 /* 1.0f */, 512);
}

void fogChangeWind(int wind) {
    float* Wind;      // r2
    float* Wind2;     // r2
    float WindSpeed;  // r29+0x40
    float WindRandom; // r29+0x40
    float a1;         // r20
    float a2;         // r29+0x40

    Wind = ((ScratchpadFog*) SCRATCHPAD_START)->Wind; // scratchapd+0x3ff0
    Wind2 = ((ScratchpadFog*) SCRATCHPAD_START)->Wind2;
    WindSpeed = 0.4f;
    WindRandom = 0.1f;

    switch (wind) {
        case 1:
        case 3:
            Wind[0] = (shRandF() - 0.5f);
            Wind[1] = 0.0f;
            Wind[2] = (shRandF() - 0.5f);
            break;
        case 2:
            vec_zero(Wind);
            WindRandom = 0.0f;
            break;
        case 17:
            Wind[0] = (shRandF() - 0.5f);
            Wind[1] = 0.0f;
            Wind[2] = (shRandF() - 0.5f);
            WindSpeed = 0.2f;
            WindRandom = 0.0f;
            break;
        case 5:
            shSinCosV(Wind, PI + ((PI * (shRandF() - 0.5f)) / 4.0f));
            Wind[1] = (0.1f * shRandF());
            break;
        case 6:
            shSinCosV(Wind, (PI * (shRandF() - 0.5f)) / 4.0f);
            Wind[1] = (0.1f * shRandF());
            break;
        case 7:
            shSinCosV(Wind, ((PI * (shRandF() - 0.5f)) / 4.0f) - QUARTER_TURN);
            Wind[1] = (0.1f * shRandF());
            break;
        case 8:
            shSinCosV(Wind, QUARTER_TURN + ((PI * (shRandF() - 0.5f)) / 4.0f));
            Wind[1] = (0.1f * shRandF());
            break;
        case 9:
            shSinCosV(Wind, (PI * 0.75f) + ((PI * (shRandF() - 0.5f)) / 4.0f));
            Wind[1] = (0.1f * shRandF());
            break;
        case 10:
            shSinCosV(Wind, (PI / 4) + ((PI * (shRandF() - 0.5f)) / 4.0f));
            Wind[1] = (0.1f * shRandF());
            break;
        case 11:
            shSinCosV(Wind, ((PI * (shRandF() - 0.5f)) / 4.0f) - (PI / 4));
            Wind[1] = (0.1f * shRandF());
            break;
        case 12:
            shSinCosV(Wind, ((PI * (shRandF() - 0.5f)) / 4.0f) - (PI * 0.75f));
            Wind[1] = (0.1f * shRandF());
            break;
        case 4:
            Wind[0] = (shRandF() - (WindSpeed = 0.5f)) * 0.1f;
            Wind[1] = 0.0f;
            Wind[2] = 1.0f;
            WindRandom = 0.0f;
            break;
        case 13:
            Wind[0] = 0.5f;
            Wind[1] = 0.1f;
            Wind[2] = 0.0f;
            WindSpeed = 0.2f;
            break;
        case 14:
            Wind[0] = (-(0.2f * shRandF()) - 0.2f);
            Wind[1] = (0.1f + (0.2f * shRandF()));
            Wind[2] = (0.8f + (0.5f * shRandF()));
            WindSpeed = 1.5f;
            break;
        case 15:
            shSinCosV(Wind, 2.6179938f + (0.08726646f * (shRandF() - 0.5f)));
            Wind[1] = -0.1f;
            WindSpeed = 0.3f;
            WindRandom = 0.0f;
            break;
        case 16:
            Wind[0] = (shRandF() - 0.5f);
            Wind[1] = 0.0f;
            Wind[2] = (shRandF() - 0.5f);
            WindSpeed = 0.1f;
            WindRandom = 0.0f;
            break;
        case 18:
            Wind[0] = (1.0f + shRandF());
            Wind[1] = (0.1f * shRandF());
            Wind[2] = (0.1f + (0.1f * shRandF()));
            WindSpeed = 0.7f;
            break;
        default:
            Wind[0] = (shRandF() - 0.5f);
            Wind[1] = (0.1f * shRandF());
            Wind[2] = (shRandF() - 0.5f);
            break;
    }
    Wind[3] = 0;
    vec_normalize(Wind, Wind);
    vec_scale(WindSpeed, Wind, Wind);
    shRandV_Scale(Wind2, 0.5f);
    vec_normalize(Wind2, Wind2);
    vec_scale(WindRandom, Wind2, Wind2);
    vec_add(Wind, Wind2, Wind);
    if ((fwork.WindV[0] != 0.0f) || (fwork.WindV[1] != 0.0f) || (fwork.WindV[2] != 0.0f)) {
        a1 = shAtanV(&fwork.WindV);
        a2 = shAngleRegulate(a1 - shAtanV(Wind));
        if (float_abs(a2) > (PI / 3)) {
            a1 += ((PI / 3) * float_sign(a2));
            shSinCosV_Scale(Wind2, a1, vec2_length(&Wind[0], &Wind[2]));
            Wind[0] = Wind2[0];
            Wind[2] = Wind2[2];
        }
    }
    volatile_vec_copy(fwork.WindV, Wind);
    fwork.WindTimer += (int) shSway1f(-300.0f, 0.1f);
    if (fwork.WindTimer < 300.0f || fwork.WindTimer > 900.0f) {
        fwork.WindTimer = 600;
    }
}

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

void fog_set_stay(void) {
    float* fv = (float*) (SCRATCHPAD_START | 0x3ff0); // r2
    float* dn = (float*) (SCRATCHPAD_START | 0x800); // r5
    int px; // r6
    int py; // r7
    int pz; // r8
    int tx; // r4
    int ty; // r9
    int tz; // r3
    int i; // r10

    vec_sub_reverse(fwork.LocalPosV, fwork.StayPoint, fv);
    vec_scale(4.0f / fwork.MaxPos, fv, fv);
    if (fwork.Double) {
        fv[1] *= 1 << fwork.Double;
    }
    px = float_floor(fv[0] - 0.5f) & 7;
    py = float_floor(fv[1] - 0.5f) & 7;
    pz = float_floor(fv[2] - 0.5f) & 7;
    for (i = 0; i < 8; i++) {
        tx = px + (i & 1);
        ty = py + ((i >> 1) & 1);
        tz = pz + (i >> 2);
        if ((tx >= 0) && (ty >= 0) && (tz >= 0) && (tx < 8) && (ty < 8) && (tz < 8)) {
            dn[((pz << 6) | (px | (py << 3)))] -= fwork.PartNum;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_wall);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_grid);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_obj);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_obj2);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_alp);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_clamp);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogMakePacket);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_view_screen_fog);

void fogSetColor(u_char r, u_char g, u_char b, u_char a) {
    fwork.Color = COLOR_RGBA(r, g, b, a);
}

/* sh2+3 shared func */
#line 3448
void fogSetPartNum(int PartNum) {
    if (PartNum <= 0) {
        fwork.PartNum = 0;
        return;
    }
    if (PART_MAX < PartNum) PartNum = PART_MAX;
    if (fwork.PartNum < PartNum) {
        int i;
        for (i = fwork.PartNum; i < PartNum; i++) {
            fog_part_newpos(&fwork.Part[i]);
        }
    }
    fwork.PartNum = PartNum;
    fog_asm_data1.gridrate = fwork.GridRate / PartNum;
}

void fogSetProjection(float Projection) {
    fwork.Projection = Projection;
    fog_asm_data2.part_size_proj2 = fwork.PartSize * Projection;
    fog_asm_data2.part_size_proj = fwork.PartSize * Projection;
    fog_asm_data2.proj = Projection;
}

void fogSetFloorY(float FloorY) {
    fwork.FloorY = FloorY;
    fog_asm_data2.floor_y = FloorY;
}

void fogSetWorldScreenM(void* WorldScreenM) {
    mat_copy(fwork.WorldScreenM, WorldScreenM);
}

void fogSetWorldViewM(void* WorldViewM) {
    mat_copy_3x3(fwork.WorldViewM, WorldViewM);
}

void fogSetWorldPosV(void* WorldPosV) {
    if (!(fwork.Flag & 0x40)) {
        vec_copy(fwork.WorldPosV, WorldPosV);
    }
}

void fogSetStayPos(void* WorldPosV) {
    fwork.Flag |= 0x40;
    vec_copy_reverse(WorldPosV, fwork.WorldPosV);
}

void fogResetStayPos(void) {
    fwork.Flag &= ~0x40;
} 

void fogSetStayPoint(void* StayPoint) {
    vec_copy_vu0(fwork.StayPoint, StayPoint);
}

void fogResetStayPoint(void) {
    vec_zero(fwork.StayPoint);
}

void fogSetCameraPosV(void* CameraPosV) {
    vec_copy(fwork.CameraPosV, CameraPosV);
}

void fogSetLocalPosV(void) {
    float * FVector = (float*) (SCRATCHPAD_START | 0x3ff0); // r2
    float * TVector = (float*) (SCRATCHPAD_START | 0x3fe0); // r2
    float d, dx;
    vec_sub_reverse(fwork.CameraPosV, fwork.WorldPosV, FVector);
    d = vec3_length(FVector);
    if (fwork.Flag & 0x20) {
        vec_copy(TVector, fwork.LocalPosV);
        dx = FVector[0] / float_abs(FVector[2]);
    }
    if (d > 2000.0f) {
        vec_scale(2000.0f / d, FVector, FVector);
        vec_add(fwork.CameraPosV, FVector, fwork.LocalPosV);
    } else {
        vec_copy_reverse(fwork.WorldPosV, fwork.LocalPosV);
        if (fwork.Double != 0) fwork.LocalPosV[1] = fwork.FloorY;
    }
    if (fwork.Flag & 0x20) {
        float mp = fwork.MaxPos;
        dx *= TVector[2] - fwork.WorldPosV[2];
        if (dx > mp) dx = mp;
        if (dx < -mp) dx = -mp;
        fwork.LocalPosV[0] += dx;
        fwork.LocalPosV[1] = TVector[1];
        fwork.LocalPosV[2] = TVector[2];
    }
}

void fogSetSpeedLevel(float SpeedLevel) {
    fwork.SpeedLevel = SpeedLevel;
}

u_long* fogTex0Adr(void) {
    return pwork.pk_tex0;
}

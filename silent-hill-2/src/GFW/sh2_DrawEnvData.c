#include "sh2_common.h"

#include "sce/libgraph.h"

#include "connect.h"

#include "Event/event.h"
#include "Event/stg_name.h"

#include "GFW/sh2_DrawEnvData.h"
#include "GFW/sh2gfw_structs.h"

#include "view/camera_dat.h"

#include "GFW/sh2_DrawEnvData_data.h"

NowBlockNo NowJmsMapId; // size: 0x10, address: 0x11EACD0
static DrawEnvData* NowDrawEnvData; // size: 0x4, address: 0x11EACC0

extern sh2gfw_Env_ctl Env_ctl; // size: 0x3F0, address: 0x2AD780
extern sceVu0FVECTOR clip_volume;

#line 53
void* Get_NowDrawEnvData(void) {
    return NowDrawEnvData;
}

#line 70
int Get_NowParallelNum(void) {
    return NowDrawEnvData->parallelLNum;
}

#line 75
int Get_NowFakePointNum(void) {
    return NowDrawEnvData->FakePointNum;
}


#line 81
int Get_NowFakeSpotNum(void) {
    return NowDrawEnvData->FakeSpotNum;
}


#line 87
int Check_NowSpotFakeOrJms(void) {
    return NowDrawEnvData->FakeSpotNum;
}

#line 96
int Get_NowRoomShadowDense(void) {
    return NowDrawEnvData->ShadowDarkNess;
}

#define DEFAULT_SHADOW_COLOR 80
#line 102
int Get_NowRoomShadowColor(void) {
    ASSERT(NowDrawEnvData!=NULL);

    if (NowDrawEnvData->ShadowColor == -1) return DEFAULT_SHADOW_COLOR;
    
    return NowDrawEnvData->ShadowColor;
}

#define SHADOW_FORCE_LIGHT_TYPE() ((NowDrawEnvData->ShadowForceLightNo & 0xFF00) >> 8)
#define SHADOW_FORCE_LIGHT_NUM() ((short) NowDrawEnvData->ShadowForceLightNo & 0xFF)

#line 136
void* Get_NowRoomShadowForceLight(int* ltype) {
    int Type = SHADOW_FORCE_LIGHT_TYPE(); // r3
    int num; // r2
    Q_WORDDATA* qwd; // r2
    *ltype = Type;

    
    if (!(num =  NowDrawEnvData->ShadowForceLightNo > 0u)) {
        return NULL;
    }

    if (Type == 1) qwd = (Q_WORDDATA*) NowDrawEnvData->pLight_Dir0;
    else qwd = (Q_WORDDATA*) NowDrawEnvData->Ld_0;
    
    
    
    
    
    
    qwd += SHADOW_FORCE_LIGHT_NUM() - 1;
    return qwd;
}

#line 168
int Check_IgnoreJmsSpot_for_Shadow(void) {
    int Type = SHADOW_FORCE_LIGHT_TYPE(); // r2
    
    
    return Type == 4;


}

#line 178
int* Get_NowMapId(void) {
    return NowJmsMapId.Map_NowBlockNo;
}

// @weird i think the first argument is incorrectly named.
// i was very confused by this
#line 185
void Get_NowPallarelCol(float* pdir, int nn) {
    PLD* pl; // r3
    
    
    
    
    
    
    DrawEnvData* ded = Get_NowDrawEnvData(); // r2
    pl = (PLD*) &ded->pLight_Dir0;
    pl += nn;
    sceVu0CopyVector(pdir, pl->Col);
}

#line 206
void Set_DrawEnvData(int mapid, int NightOrDay) {
    int mapblock; // r2
    int maparea; // r16
    sceVu0IVECTOR maptmp; // r29+0x50
    int i; // r4
    DrawEnvData* ded; // r17
    void* stg_drawenv_data[17] = { 
        NULL,
        CA_DrawEnvData,
        CB_DrawEnvData,
        CC_DrawEnvData,
        CD_DrawEnvData,
        OB_DrawEnvData,
        ER_DrawEnvData,
        BW_DrawEnvData,
        TH_DrawEnvData,
        AP_DrawEnvData,
        HP_DrawEnvData,
        PS_DrawEnvData,
        RR_DrawEnvData,
        RU_DrawEnvData,
        QP_DrawEnvData,
        QP_DrawEnvData,
        QP_DrawEnvData
    }; // r29+0x60

    
    mapblock = BlockNumber(maptmp, 0, connect_pos[0], connect_pos[2]); // @note unused ?

    mapblock = maptmp[0]; // @todo possible incorrect variable usage? replacing mapid with mapblock makes it match but it doesnt look right
    maparea = (int) (mapblock & 0xFFFF000) >> 16;
    
    for (i = 0; i < 4; i++) NowJmsMapId.Map_NowBlockNo[i] = maptmp[i];

    ded = stg_drawenv_data[maparea];

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    #line 257
    if (maparea - 2u < 2u) { // if ((maparea == 2) || (maparea == 3)) ?
        
        
        if (GET_GAME_FLAG(GAME_FLAG_251)) {
            SetLightMode(1);
            while (ded->map_id_name != -1) ded++;
        } else {
            SetLightMode(0);
            
            while (ded->map_id_name != -2) ded++;
        }
        
    } else if (maparea == 6) {
        
        if (GET_GAME_FLAG(GAME_FLAG_251)) {
            SetLightMode(1);
            while (ded->map_id_name != -1) {
                if (ded->map_id_name == mapblock && ded->NightOrDay == 1)
                    break;
                ded++;
            }
        } else {
            SetLightMode(0);
            
            
            while (ded->map_id_name != -1) {
                if (ded->map_id_name == mapblock && ded->NightOrDay == 0)
                    break;
                ded++;
            }
        }
    } else {



        
        while (ded->map_id_name != -1 && ded->map_id_name != mapblock) ded++;
        SetLightMode(ded->NightOrDay);
    }
    NowDrawEnvData = ded;
    
    
    SetupDrawEnvData(NightOrDay);
    
    
    
    Env_ctl.compo_shadow_col.si32[3] = Get_NowRoomShadowColor();
    
    
    sh2gfw_Set_FilterData(NightOrDay, NULL, &Env_ctl.compo_shadow_col);
    
    
    
    
    
    sh2gfw_Init_DemoLight_Work();
    
    sh2gfw_Set_MicroCode(NightOrDay + 1);
    
    
    
    if (maparea < 5) {
        
        if (!sh2gfw_Get_NightOrDay()) {
            Env_ctl.CharacterLightFactor[0] = 1.3f;
        } else {
            Env_ctl.CharacterLightFactor[0] = 1.05f;
        }
    } else {
        Env_ctl.CharacterLightFactor[0] = 1.05f;
    
    }
}

#ifdef HOLY_CANDLE
#line 332
void SetupDrawEnvData(int NightOrDay) {
    int i; // r16
    DrawEnvData* ded; // r17
    void* ptemp; // r18
    sceVu0FVECTOR vtmp; // r29+0x40
    sceVu0IVECTOR itmp; // r29+0x50

    
    ded = Get_NowDrawEnvData();
    ASSERT(ded!=NULL);
    
    
    
    sceVu0CopyVector(Env_ctl.SpotL0.decayparm.fl32, ded->SpotDecayParm0);
    
    
    
    Env_ctl.SpotL0.decayparm.fl32[1] = cosf(Env_ctl.SpotL0.decayparm.fl32[3]);
    
    sceVu0CopyVector(Env_ctl.SpotL0.color.fl32, ded->SpotCol0);
    
    
    
    
    
    
    sceVu0Normalize(Env_ctl.p_light0, ded->pLight_Dir0);
    
    
    
    sceVu0Normalize(Env_ctl.p_light1, ded->pLight_Dir1);
    
    
    
    sceVu0Normalize(Env_ctl.p_light2, ded->pLight_Dir2);
    
    
    
    if (ded->parallelLNum == 0) {
    
        sceVu0CopyVector(Env_ctl.p_color0, ded->pLight_Col0);
        
        
        sceVu0CopyVector(Env_ctl.p_color1, ded->pLight_Col1);
        
        
        sceVu0CopyVector(Env_ctl.p_color2, ded->pLight_Col2);
    
    
    
    } else if (ded->parallelLNum == 1) {
        
        sceVu0CopyVector(Env_ctl.p_color0, ded->pLight_Col0);
        
        
        
        sceVu0CopyVector(Env_ctl.p_color1, ded->pLight_Col1);
        
        sceVu0ScaleVector(Env_ctl.p_color2, ded->pLight_Col2, 0.0f);
    } else {

        sceVu0CopyVector(Env_ctl.p_color0, ded->pLight_Col0);
        
        
        
        sceVu0ScaleVector(Env_ctl.p_color1, ded->pLight_Col1, 0.0f);
        
        sceVu0ScaleVector(Env_ctl.p_color2, ded->pLight_Col2, 0.0f);
    }
    ptemp = (sh2gfw_POINTL_MATRIX*) ded->Ld_0 + ded->pointLNum;
    for (i = 0; i < ded->spotLNum; i++) {
    
        
        SpotLightData* sld = (SpotLightData*) ptemp + i; // r2
        sceVu0Normalize(sld->Dir, sld->Dir);
    }
    ptemp = (SpotLightData*) ptemp + i;
    ptemp = (sh2gfw_POINTL_MATRIX*) ptemp + ded->FakePointNum;
    for (i = 0; i < ded->FakeSpotNum; i++) {
        
        
        SpotLightData* sld = (SpotLightData*) ptemp + i; // r2
        sceVu0Normalize(sld->Dir, sld->Dir);
    }
    
    
    
    sceVu0CopyVector(Env_ctl.ambient, ded->Ambient);
    
    
    sceVu0CopyVector(Env_ctl.BaseAmbient, ded->BaseAmbient);
    
    
    sceVu0CopyVector(Env_ctl.BaseVertexColor, ded->BaseColor);
    
    
    sceVu0CopyVector(Env_ctl.VertexAmbient, ded->VertexAmbient);
    
    
    
    if (sh2gfw_Get_NightOrDay()) {
        
        
        if (ded->FogParm[0] == 0.0f) {
            Env_ctl.fogparm.fl32[0] = 8000.0f;
            Env_ctl.fogparm.fl32[1] = 3000.0f;
            Env_ctl.fogparm.fl32[2] = 100.0f;
            Env_ctl.fogparm.fl32[3] = 255.0f;
        } else {
            Env_ctl.fogparm.fl32[0] = ded->FogParm[0];
            Env_ctl.fogparm.fl32[1] = ded->FogParm[1];
            Env_ctl.fogparm.fl32[2] = ded->FogParm[2];
            Env_ctl.fogparm.fl32[3] = ded->FogParm[3];
        }
        
        
        
        if (ded->SpotParm[3] == 0.0f) {
            Env_ctl.fogcolor.uc8[0]   = 0;
            Env_ctl.fogcolor.uc8[1]   = 0;
            Env_ctl.fogcolor.uc8[2]   = 0;
            Env_ctl.clearcolor.uc8[0] = 0;
            Env_ctl.clearcolor.uc8[1] = 0;
            Env_ctl.clearcolor.uc8[2] = 0;
            Env_ctl.clearcolor.uc8[3] = 124;
        } else {
            sceVu0ScaleVector(vtmp, ded->MoveFogCol, ded->SpotParm[3]);
            sceVu0FTOI0Vector(itmp, vtmp);
            Env_ctl.fogcolor.uc8[0]   = itmp[0];
            Env_ctl.fogcolor.uc8[1]   = itmp[1];
            Env_ctl.fogcolor.uc8[2]   = itmp[2];
            Env_ctl.clearcolor.uc8[0] = itmp[0];
            Env_ctl.clearcolor.uc8[1] = itmp[1];
            Env_ctl.clearcolor.uc8[2] = itmp[2];
            Env_ctl.clearcolor.uc8[3] = itmp[3];
        }
    
    } else {
    
        if (ded->FogParm[0] == 0.0f) {
        
            Env_ctl.fogparm.fl32[0] = 5500.0f;
            Env_ctl.fogparm.fl32[1] = 3000.0f;
            Env_ctl.fogparm.fl32[2] = 20.0f;
            Env_ctl.fogparm.fl32[3] = 235.0f;
        } else {
            Env_ctl.fogparm.fl32[0] = ded->FogParm[0];
            Env_ctl.fogparm.fl32[1] = ded->FogParm[1];
            Env_ctl.fogparm.fl32[2] = ded->FogParm[2];
            Env_ctl.fogparm.fl32[3] = ded->FogParm[3];
        }

        if (ded->SpotParm[3] == 0.0f) {
            Env_ctl.fogcolor.uc8[0]   = 70;
            Env_ctl.fogcolor.uc8[1]   = 70;
            Env_ctl.fogcolor.uc8[2]   = 70;
            Env_ctl.clearcolor.uc8[0] = 70;
            Env_ctl.clearcolor.uc8[1] = 70;
            Env_ctl.clearcolor.uc8[2] = 70;
            Env_ctl.clearcolor.uc8[3] = 64;
        } else {
            sceVu0ScaleVector(vtmp, ded->MoveFogCol, ded->SpotParm[3]);
            sceVu0FTOI0Vector(itmp, vtmp);
            Env_ctl.fogcolor.uc8[0]   = itmp[0];
            Env_ctl.fogcolor.uc8[1]   = itmp[1];
            Env_ctl.fogcolor.uc8[2]   = itmp[2];
            Env_ctl.clearcolor.uc8[0] = itmp[0];
            Env_ctl.clearcolor.uc8[1] = itmp[1];
            Env_ctl.clearcolor.uc8[2] = itmp[2];
            Env_ctl.clearcolor.uc8[3] = itmp[3];
        }
    }

    if (ded->SpotParm[2] == 0.0f) {
        Env_ctl.camera_parms[3] = 100.0f;
    } else {
        Env_ctl.camera_parms[3] = ded->SpotParm[2];
    }

    #line 516
    Env_ctl.CopyFilterColor.fl32[1] = 0;
    
    
    
    Env_ctl.compo_shadow_alp.ul64[1] = SCE_GS_SET_ALPHA(2, 0, 0, 1, 0); Env_ctl.compo_shadow_alp.ul64[0] = SCE_GS_SET_ALPHA(2, 1, 0, 1, 0);



    
    Env_ctl.compo_shadow_test.ul64[1] = SCE_GS_SET_TEST(SCE_GS_TRUE /* alpha test */, SCE_GS_ALPHA_LEQUAL, 4, 0, 0, 0, SCE_GS_FALSE, SCE_GS_DEPTH_NEVER); Env_ctl.compo_shadow_test.ul64[0] = SCE_GS_SET_TEST(0, SCE_GS_ALPHA_ALWAYS, 0, 0, 0, 0, SCE_GS_TRUE, SCE_GS_DEPTH_ALWAYS);
    Env_ctl.compo_shadow_env.uc8[1] = 0;
    Env_ctl.compo_shadow_env.uc8[0] = 1;

    
    if (ded->SpotParm[1] != 0.0f) {
   
        Env_ctl.camera_parms2[2] = ded->SpotParm[1];
    } else {
        if (((NowJmsMapId.Map_NowBlockNo[0] & 0xFF00) > 0) && ((NowJmsMapId.Map_NowBlockNo[0] & 0xFF00) < 5)) {

            
            Env_ctl.camera_parms2[2] = 7500.0f;
        } else {
            
            Env_ctl.camera_parms2[2] = 7500.0f;
        }
    }
    
    
    if (ded->MoveFogCol[0] != 0.0) { // @bug comparison with double
        sceVu0FTOI0Vector(Env_ctl.MoveFogColor.fl32, ded->MoveFogCol);
        fogSetColor(Env_ctl.MoveFogColor.ui32[0], Env_ctl.MoveFogColor.ui32[1], Env_ctl.MoveFogColor.ui32[2], Env_ctl.MoveFogColor.ui32[3]);
    }
    
    
    
    
    
    
    
    
    sh2gfw_Set_SpecularAlpha();
    
    kari_sh2setGS_clearcolor(Env_ctl.clearcolor.uc8[0], Env_ctl.clearcolor.uc8[1], Env_ctl.clearcolor.uc8[2], Env_ctl.clearcolor.uc8[3]);

    #line 566
    kari_sh2setGS_fogcolor(Env_ctl.fogcolor.uc8[0], Env_ctl.fogcolor.uc8[1], Env_ctl.fogcolor.uc8[2]);
    
    #line 586
    clip_volume[0] = 2047.0f;
    clip_volume[1] = 2047.0f;
    
    sceVu0CopyVector(cam0.clip_volume, &clip_volume);
    
    
    if (!sh2gfw_Check_JmsSpotOnOff()) sh2gfw_Get_NightOrDay();

    #line 599
}
#else
INCLUDE_ASM("asm/nonmatchings/GFW/sh2_DrawEnvData", SetupDrawEnvData);

RODATA_PAD_TO(0x00399BD0);

INCLUDE_RODATA("asm/nonmatchings/GFW/sh2_DrawEnvData", @676);

INCLUDE_RODATA("asm/nonmatchings/GFW/sh2_DrawEnvData", @677);
#endif

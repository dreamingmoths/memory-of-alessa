#include "sh2_common.h"
#include "Chacter/character.h"
#include "Chacter/chara_list.h"
#include "Chacter_Draw/light_n.h"
#include "Chacter_Draw/sh2gfw_model_light.h"
#include "GFW/sh2_DrawEnvData.h"
#include "GFW/sh2gfw_structs.h"

static void Init_FakeLightWork(void);
static void Set_FakeLight(int nn);
static int Get_FakeLightNum(void);
static int Get_FakeLightId(int n);
static void UpdateFake_DirandColor(int no);
static void sh2gfw_Init_ShadowLight(void);
static void Reverse_Light(void);
static void sh2gfw_set_JmsLIGHT(void);
static void sh2gfw_set_OtherOtherLIGHT(void);
static void sh2gfw_set_OtherLIGHT(void);

UNMIGRATED(shShadingParams shLambertEnv); // size: 0x60, address: 0x0
UNMIGRATED(/* static */ int Reverse_Draw); // size: 0x4, address: 0x489740
UNMIGRATED(FakeLight_Work FakeLightWork); // size: 0x10, address: 0x489B80
UNMIGRATED(sh2gfw_ModelDraw_MAN UniModelDW_Man); // size: 0x94, address: 0x616E00
UNMIGRATED(ShadowLight_Work ShadowLightWork); // size: 0x204, address: 0x489970
UNMIGRATED(ShadowLight_Work ShadowParallel_LightWork); // size: 0x204, address: 0x489760
UNMIGRATED(/* static */ sceVu0FVECTOR NormalColor); // size: 0x10, address: 0x0
UNMIGRATED(int OtherLightFlg); // size: 0x4, address: 0x489748
UNMIGRATED(int Chr_ID_Buf); // size: 0x4, address: 0x489B90
UNMIGRATED(sceVu0FVECTOR SpotHilightPos); // size: 0x10, address: 0x489750

#line 146
static void Init_FakeLightWork(void) {
    FakeLightWork.FakeLightNum = 0;
}

#line 151
static void Set_FakeLight(int nn) {
    if (FakeLightWork.FakeLightNum < FAKE_LIGHT_MAX)
        FakeLightWork.UniFakeLightNo[FakeLightWork.FakeLightNum++] = nn;
}


#line 158
static int Get_FakeLightNum(void) {
    return FakeLightWork.FakeLightNum;
}
#line 162
static int Get_FakeLightId(int n) {
    return FakeLightWork.UniFakeLightNo[n];
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_model_light", UpdateFake_DirandColor);

#line 374
int sh2gfw_Check_CharaDarkOrBright(void* SubChara) {
    int i; // r3
    for (i = 0; i < ShadowLightWork.Store_Num; i++) {
        UNLINKED(/* static */ float inf_hosei_1029, 0.1f); // @ 0x002A97F8
        if (ShadowLightWork.ShadowLd[i].SubChara != SubChara) continue;
        
        if (ShadowLightWork.ShadowLd[i].influence_factor - inf_hosei_1029 > 0.0f)
            return true;
        else
            return false;
    }
    return false;
}

#line 395
static void sh2gfw_Init_ShadowLight(void) {
    ShadowLightWork.Store_Num = 0;
    ShadowParallel_LightWork.Store_Num = 0;
    return;
}

#line 424
void sh2gfw_Store_ShadowParallelLight(void* pald, int pnum) {
    Light* pL = (Light*) pald; // r2
    int i = ShadowParallel_LightWork.Store_Num++; // r7

    if (i > 0) return;

    for (; i < pnum; i++) {
         ShadowParallel_LightWork.ShadowLd[i].lightKind = 1;
         ShadowParallel_LightWork.ShadowLd[i].pDed = pL->DrawEnv_LightData;

        pL++;
    }
}

#line 444
void sh2gfw_Store_ShadowLight(void* pl) {
    int ltype; // r29+0x2C
    
    
    
    void* pldata = Get_NowRoomShadowForceLight(&ltype); // r2
    int sn; // r2

    if ((sn = ShadowLightWork.Store_Num) < SHADOW_LIGHT_MAX) {
        
        if (UniModelDW_Man.testSubChar->kind == EN_TYU_CHARA_KIND) return;

        
        
        

        
        
        
        
        
        

        if (pldata == NULL || ltype == 4) {
            Light* pL = (void*) pl; // r2
        
        
                
            ShadowLightWork.ShadowLd[sn].SubChara = UniModelDW_Man.testSubChar;
            
            ShadowLightWork.ShadowLd[sn].pDed = pL->DrawEnv_LightData;
            
            ShadowLightWork.ShadowLd[sn].lightKind = pL->kind;

            
            ShadowLightWork.ShadowLd[sn].influence_factor = pL->influence;
            
            ShadowLightWork.ShadowLd[sn].force_flg = 0;
        
        
        } else {
        
            
            
            ShadowLightWork.ShadowLd[sn].lightKind = ltype;
            ShadowLightWork.ShadowLd[sn].SubChara = UniModelDW_Man.testSubChar;
            
            ShadowLightWork.ShadowLd[sn].pDed = pldata;
            ShadowLightWork.ShadowLd[sn].influence_factor = 1.0f;
            
            ShadowLightWork.ShadowLd[sn].force_flg = 1;
        }
        
        
        
        
        
        
        
        
        
        ShadowLightWork.Store_Num++;
        
        #line 508
        ASSERT(ShadowLightWork.Store_Num<=SHADOW_LIGHT_MAX);
    }
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_model_light", sh2gfw_Get_ShadowLight);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_model_light", sh2gfw_Get_ShadowLightKind);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_model_light", sh2gfw_Get_ShadowLightPointer);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_model_light", Draw_Jms_Shadow);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_model_light", Reverse_Light);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_model_light", sh2gfw_set_JmsLIGHT);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_model_light", sh2gfw_set_OtherOtherLIGHT);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_model_light", sh2gfw_set_OtherLIGHT);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_model_light", sh2gfw_clear_LightChr);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_model_light", sh2gfw_check_LightChr);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_model_light", sh2gfw_change_lights);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_model_light", sh2gfw_set_CommonCharacterLight);

INCLUDE_RODATA("asm/nonmatchings/Chacter_Draw/sh2gfw_model_light", @1576);

INCLUDE_RODATA("asm/nonmatchings/Chacter_Draw/sh2gfw_model_light", @1577);

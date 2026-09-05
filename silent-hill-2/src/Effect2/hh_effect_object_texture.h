#ifndef HH_EFFECT_OBJECT_TEXTURE_H
#define HH_EFFECT_OBJECT_TEXTURE_H

#include "effect2/hh_memory_manage.h"
#include "GFW/sh2gfw_Texpacket.h"
#include "GFW/sh2gfw_structs.h"
#include "fog/spkTexMan.h"
#include "Multi_thr/dma/dma1serv.h"
#include "Multi_thr/dma/dma2tscmd.h"

#include "common.h"

#define ASSERT_TEXTURE(cond, line) \
do { \
        printf("Texture Context Already Regist: Multiple Regist!!\n"); \
        printf(__FILE__ ":" #line "> assert:(%s)\n", #cond); \
        do {} while (1); \
} while (0);

typedef struct HH_Local_TextureInfomeation {
    u_int Register_Texture_ID;
    void* pFileID;
    u_int Entry_Level;
    u_int Transport_Priority;
    u_int LinkList_Max;
    int* pLinkList;
    int (*pException_Judge)();

} __attribute__((aligned(16))) HH_Local_TextureInfomeation;

typedef struct HH_Local_TextureContext {
    u_int Enable;
    int Buffer_Index;
    u_int Entry_Level;
    HH_Local_TextureInfomeation* pTexture_Infomeation;
    sh2gfw_Effect_Man EffectTexture_Management;
} HH_Local_TextureContext;

void LocalWrapper_TextureTransport_Entry(sh2gfw_Effect_Man* pEffectTexture_Management, sh2gfw_TEX_HEAD* pTexture_Header, sh2gfw_CLUTS_HEAD* pCluts_Header, u_int Texture_ID);

u_int LocalWrapper_TextureTransport_Entry_Delete(sh2gfw_Effect_Man* pEffectTexture_Management);

u_int TextureContext_DesignateEntryLevel_EntryCheck(u_int Entry_Level, HH_Local_TextureInfomeation* pTexture_Infomeation);

u_int TextureBinary_DesignateEntryLevel_Load(u_int Entry_Level);

u_int AlwaysTexture_Context_Entry(HH_Local_TextureInfomeation* pTex_Info, HH_Local_TextureContext* pContext, void* pBuffer);

u_int TextureBinary_DesignateTexture_Load_toAlwaysBuffer(HH_Local_TextureInfomeation* pTex_Info);

u_int TextureContext_DesignateEntryLevel_Entry(u_int Entry_Level);

u_int TextureContext_DesignateEntryLevel_AllClear(u_int Entry_Level);

u_int TextureContext_DesignateEntryLevelUnder_AllClear(u_int Entry_Level);

u_int AlwaysTexture_Initialize(HH_Local_TextureInfomeation* pTex_Info);

void Object_SPK_Texture_Post(void);

void Object_Texture_Send(void);

void Object_Texture_Sync(void);

void Object_Texture_Finish(void);

u_long Object_Texture_GS_Register_Tex0_Get(u_int Texture_ID, u_int Clut_ID);

void HH_Effect_Object_Texture_TransportPriority_Initialize(void);

void HH_Effect_Object_SPK_Texture_Post(void);

void HH_Effect_Object_Texture_Send(void);

void HH_Effect_Object_Texture_Sync(void);

void HH_Effect_Object_Texture_Finish(void);

u_long HH_Effect_Object_Texture_GS_Register_Tex0_Get(u_int Texture_ID, u_int Clut_ID);

u_int HH_Effect_Object_Texture_DesignateEntryLevel_Initialize(u_int Entry_Level /* r17 */);

u_int HH_Effect_Object_Texture_DesignateEntryLevel_Discard(u_int Entry_Level /* r2 */);

u_int HH_Effect_Object_Texture_AlwaysTexture_Initialize(void);

#endif

#include "effect2/hh_effect_object_texture.h"

#include "common.h"

#define TEXTURE_BUFFER_BLOCK_MAX 5U
// from shared/lens/kari_lf_draw.h
#define EFF_VALID_ID 0xEF04

extern /* static */ int* _TextureHeader_Table[21];
extern /* static */ HH_Local_TextureInfomeation _TextureInfomeation_Table[21];
extern u_int _texture_buffer_enable[5];
extern HH_Local_TextureContext _TextureContext_Table[21];

extern /* static */ u_int _send_count;
extern /* static */ u_int _sync_count;
extern /* static */ u_int _finish_count;
extern u_int _Transport_Current_Priority;

void LocalWrapper_TextureTransport_Entry(sh2gfw_Effect_Man* pEffectTexture_Management, sh2gfw_TEX_HEAD* pTexture_Header, sh2gfw_CLUTS_HEAD* pCluts_Header, u_int Texture_ID) {
    memset(pEffectTexture_Management, 0, 64);
    pEffectTexture_Management->pTexHead = pTexture_Header;
    pEffectTexture_Management->pTexMAN  = sh2gfw_set_TexToTrasMan(&AllTexSync_Man, pTexture_Header, pCluts_Header, pEffectTexture_Management, Texture_ID | 0xE000);
    pEffectTexture_Management->valid_id = EFF_VALID_ID;
}

u_int LocalWrapper_TextureTransport_Entry_Delete(sh2gfw_Effect_Man* pEffectTexture_Management) {
    u_int result = 0;
    void* temp   = pEffectTexture_Management->pTexMAN;

    if (sh2gfw_del_TexMAN(&AllTexSync_Man, temp)) {
        result = 1;
    }
    return result;
}

// thanks: Amrsatrio
u_int TextureContext_DesignateEntryLevel_EntryCheck(u_int Entry_Level, HH_Local_TextureInfomeation* pTexture_Infomeation) {
    int room_name;
    u_int i;
    u_int result;
    u_int result_inner;
    result = 0;
    // @ note: only "result" is in dwarf
    switch (Entry_Level) {
        case 2:
            switch (pTexture_Infomeation->Entry_Level) {
                case 2:
                case 4:
                    if (pTexture_Infomeation->pException_Judge) {
                        if (pTexture_Infomeation->pException_Judge()) {
                            result = 1;
                        }
                    } else {
                        result = 1;
                    }
                    break;
                case 0:
                case 1:
                    break;
            }
            break;
        case 3:
            switch (pTexture_Infomeation->Entry_Level) {
                case 4:
                    if (pTexture_Infomeation->pException_Judge == NULL || pTexture_Infomeation->pException_Judge()) {
                        break;
                    }
                    // [[fallthrough]]
                case 3:
                    result_inner = 0;
                    room_name    = RoomNameJms();
                    for (i = 0; i < pTexture_Infomeation->LinkList_Max; i++) {
                        if (room_name == pTexture_Infomeation->pLinkList[i]) {
                            result_inner = 1;
                            break;
                        }
                    }
                    if (result_inner) {
                        result = 1;
                    }
                    break;
                case 0:
                case 1:
                    break;
            }
            break;
        case 0:
        case 1:
            break;
    }
    return result;
}

static inline void get_disabled_texture_buffer(int* dst) {
    u_int Buffer_Index;
    *dst = -1;

    for (Buffer_Index = 0; Buffer_Index < 4u; Buffer_Index++) {
        ASSERT_ON_LINE(Buffer_Index < TEXTURE_BUFFER_BLOCK_MAX, 470);
        if (_texture_buffer_enable[Buffer_Index] == 0) {
            *dst = Buffer_Index;
            return;
        }
    }
}

u_int TextureBinary_DesignateEntryLevel_Load(u_int Entry_Level) {
    u_int result = 0;                       // r16
    u_int i;                                // r17
    int fid;                                // r18
    int buffer_index;                       // r2
    void* pBuffer;                          // r19
    HH_Local_TextureInfomeation* pTex_Info; // r2
    HH_Local_TextureContext* pContext;      // r2

    for (i = 0; i < 21; i++) {
        pTex_Info = &_TextureInfomeation_Table[i];
        if (TextureContext_DesignateEntryLevel_EntryCheck(Entry_Level, pTex_Info)) {
            get_disabled_texture_buffer(&buffer_index);

            if (buffer_index == -1)
                goto hand_rolled_assert;

            pContext = &_TextureContext_Table[pTex_Info->Register_Texture_ID];
            if (!pContext->Enable) {

                pBuffer = HH_MemoryManager_AllocateMemoryBlock_Get(2);
                pBuffer = HH_MemoryManager_DesignateSize_Alignment64Address_Calculator(pBuffer, 0x44800, buffer_index);
                fid     = FcRead(pTex_Info->pFileID, pBuffer);

                if (fid != -1) {
                    BLOCK_WHILE(fsSync(0, fid) < 0);

                    result                         = 1;
                    pContext->Enable               = 1;
                    pContext->Buffer_Index         = buffer_index;
                    pContext->Entry_Level          = Entry_Level;
                    pContext->pTexture_Infomeation = pTex_Info;

                    ASSERT_ON_LINE(buffer_index < TEXTURE_BUFFER_BLOCK_MAX, 476);

                    _texture_buffer_enable[buffer_index]                 = 1;
                    _TextureHeader_Table[pTex_Info->Register_Texture_ID] = (int*) pBuffer;
                }
                continue;
            } else {
                ASSERT_TEXTURE(!pContext->Enable, 770);
            }
        hand_rolled_assert:
            printf("hh_effect_object_texture.c:774> assert:(%s)\n", "!pContext->Enable");
            for (;;);
        }
    }
    return result;
}

u_int AlwaysTexture_Context_Entry(HH_Local_TextureInfomeation* pTex_Info, HH_Local_TextureContext* pContext, void* pBuffer) {
    pContext->Enable                                     = 1;
    pContext->Buffer_Index                               = 4;
    pContext->Entry_Level                                = 1;
    pContext->pTexture_Infomeation                       = pTex_Info;
    _texture_buffer_enable[4]                            = 1;
    _TextureHeader_Table[pTex_Info->Register_Texture_ID] = pBuffer;
    return 1;
}

u32 TextureBinary_DesignateTexture_Load_toAlwaysBuffer(HH_Local_TextureInfomeation* pTex_Info) {
    u_int pTex_ID, result = 0;
    void* pBuffer;
    int fid;
    HH_Local_TextureContext* pContext;

    pTex_ID  = pTex_Info->Register_Texture_ID; // @ note: Not in dwarf. Required for matching
    pContext = &_TextureContext_Table[pTex_ID];

    if (!pContext->Enable) {
        pBuffer = HH_MemoryManager_AllocateMemoryBlock_Get(3);
        fid     = FcRead(pTex_Info->pFileID, pBuffer);
        if (fid != -1) {
            BLOCK_WHILE(fsSync(0, fid) < 0);

            AlwaysTexture_Context_Entry(pTex_Info, pContext, pBuffer);
            result = 1;
        }
    } else {
        ASSERT_TEXTURE(!pContext->Enable, 851);
    }
    return result;
}

u_int TextureContext_DesignateEntryLevel_Entry(u_int Entry_Level) {
    sh2gfw_CLUTS_HEAD* pCluts_Header;
    sh2gfw_TEX_HEAD* pTex_Header;
    HH_Local_TextureContext* pContext;
    u_int i, result = 0;

    for (i = 0; i < 21; i++) {
        pContext = &_TextureContext_Table[i];
        if (pContext->Enable && pContext->Entry_Level == Entry_Level) {
            pTex_Header = _TextureHeader_Table[i];
            LocalWrapper_TextureTransport_Entry(
                &pContext->EffectTexture_Management,
                pTex_Header,
                (sh2gfw_CLUTS_HEAD*) ((char*) pTex_Header + pTex_Header->allsize),
                pContext->pTexture_Infomeation->Register_Texture_ID);
            result = 1;
        }
    }
    return result;
}

u_int TextureContext_DesignateEntryLevel_AllClear(u_int Entry_Level) {
    u_int i;
    u_int result = 0;
    HH_Local_TextureContext* pContext;

    for (i = 0; i < 21; i++) {
        pContext = &_TextureContext_Table[i];
        if (pContext->Enable && pContext->Entry_Level == Entry_Level) {
            _TextureHeader_Table[i] = NULL;

            ASSERT_ON_LINE(pContext->Buffer_Index < TEXTURE_BUFFER_BLOCK_MAX, 482);

            _texture_buffer_enable[pContext->Buffer_Index] = 0;
            LocalWrapper_TextureTransport_Entry_Delete(&pContext->EffectTexture_Management);
            memset(pContext, 0, 80);
            result = 1;
        }
    }
    return result;
}

u_int TextureContext_DesignateEntryLevelUnder_AllClear(u_int Entry_Level) {
    u_int i;
    u_int result = 0;

    for (i = Entry_Level; 3u >= i; i++) { //@note: comparison using $at register.
        TextureContext_DesignateEntryLevel_AllClear(i);
        result = 1;
    }
    return result;
}

u_int AlwaysTexture_Initialize(HH_Local_TextureInfomeation* pTex_Info) {
    TextureContext_DesignateEntryLevel_AllClear(1);
    TextureBinary_DesignateTexture_Load_toAlwaysBuffer(pTex_Info);
    TextureContext_DesignateEntryLevel_Entry(1);
    return 1;
}

void Object_SPK_Texture_Post(void) {
    sh2gfw_Effect_Man* pTex_Manage;
    HH_Local_TextureContext* pContext;
    u_int i;

    for (i = 0; i < 21; i++) {
        pContext = &_TextureContext_Table[i];
        if (pContext->Enable && pContext->pTexture_Infomeation->Transport_Priority == 1) {
            pTex_Manage = &pContext->EffectTexture_Management;

            ASSERT_ON_LINE(pTex_Manage->valid_id == EFF_VALID_ID, 1017);

            sh2gfw_EnQue_spkTexture(pTex_Manage->pTexMAN, &pTex_Manage->thr_cid, &pTex_Manage->thr_sid);
        }
    }
}

void Object_Texture_Send(void) {
    HH_Local_TextureContext* pContext;
    sh2gfw_Effect_Man* pTex_Manage;
    u_int i;
    u_int priority;

    priority = _Transport_Current_Priority;
    for (i = 0; i < 21; i++) {
        pContext = &_TextureContext_Table[i];
        if (pContext->Enable && pContext->pTexture_Infomeation->Transport_Priority == priority) {
            pTex_Manage = &pContext->EffectTexture_Management;

            ASSERT_ON_LINE(pTex_Manage->valid_id == EFF_VALID_ID, 1047);

            sh2gfw_Thr_d2TextureSend(pTex_Manage->pTexMAN, 0, &pTex_Manage->thr_cid, &pTex_Manage->thr_sid);
            _send_count++;
        }
    }
}

void Object_Texture_Sync(void) {
    HH_Local_TextureContext* pContext;
    u_int i;
    u_int priority;

    priority = _Transport_Current_Priority;
    for (i = 0; i < 21; i++) {
        pContext = _TextureContext_Table + i;
        if (pContext->Enable && pContext->pTexture_Infomeation->Transport_Priority == priority) {
            d1tscSync(pContext->EffectTexture_Management.thr_cid);
            _sync_count++;
        }
    }
}

void Object_Texture_Finish(void) {
    sh2gfw_Effect_Man* pTex_Manage;
    HH_Local_TextureContext* pContext;
    u_int i;
    u_int priority;

    priority = _Transport_Current_Priority;
    for (i = 0; i < 21; i++) {
        pContext = &_TextureContext_Table[i];
        if (pContext->Enable && pContext->pTexture_Infomeation->Transport_Priority == priority) {
            d1tscFinishToUseSlot(pContext->EffectTexture_Management.thr_sid);
            _finish_count++;
        }
    }
    _Transport_Current_Priority = priority + 1;
}

u_long Object_Texture_GS_Register_Tex0_Get(u_int Texture_ID, u_int Clut_ID) {
    u_long tex0;
    HH_Local_TextureContext* pContext;

    pContext = &_TextureContext_Table[Texture_ID];
    tex0     = 0;
    ASSERT(Clut_ID < 16);
    if (pContext->Enable) {
        tex0 = *(u_long*) sh2gfw_Get_RegTEX0(pContext->EffectTexture_Management.pTexMAN, Clut_ID, 1);
    }
    return tex0;
}

void HH_Effect_Object_Texture_TransportPriority_Initialize(void) {
    _Transport_Current_Priority = 0;
    _send_count                 = 0;
    _sync_count                 = 0;
    _finish_count               = 0;
}

void HH_Effect_Object_SPK_Texture_Post(void) {
    Object_SPK_Texture_Post();
}

void HH_Effect_Object_Texture_Send(void) {
    Object_Texture_Send();
}

void HH_Effect_Object_Texture_Sync(void) {
    Object_Texture_Sync();
}

void HH_Effect_Object_Texture_Finish(void) {
    Object_Texture_Finish();
}

u_long HH_Effect_Object_Texture_GS_Register_Tex0_Get(u_int Texture_ID, u_int Clut_ID) {
    return Object_Texture_GS_Register_Tex0_Get(Texture_ID, Clut_ID);
}

u_int HH_Effect_Object_Texture_DesignateEntryLevel_Initialize(u_int Entry_Level) {
    u_int result = 0;

    if (HH_MemoryManager_AllocateMemoryBlock_Check(MEMORY_BLOCK_TEXTURE_BUFFER)) {
        TextureContext_DesignateEntryLevelUnder_AllClear(Entry_Level);
        TextureBinary_DesignateEntryLevel_Load(Entry_Level);
        TextureContext_DesignateEntryLevel_Entry(Entry_Level);
        result = 1;
    } else if (HH_MemoryManager_MemoryBlock_All_Allocate()) {
        TextureBinary_DesignateEntryLevel_Load(2);
        TextureContext_DesignateEntryLevel_Entry(2);
        TextureBinary_DesignateEntryLevel_Load(3);
        TextureContext_DesignateEntryLevel_Entry(3);
    }
    return result;
}

u_int HH_Effect_Object_Texture_DesignateEntryLevel_Discard(u_int Entry_Level) {
    TextureContext_DesignateEntryLevelUnder_AllClear(Entry_Level);
    return 1;
}

// thanks: piccio, bloodangel, dezgeg
u_int HH_Effect_Object_Texture_AlwaysTexture_Initialize(void) {
    HH_Local_TextureInfomeation* pTex_Info;
    u_int i;

    for (i = 0; i < 21; i++) {
        pTex_Info = &_TextureInfomeation_Table[i];
        if (pTex_Info->Register_Texture_ID == 1) {
            AlwaysTexture_Initialize(pTex_Info);
            break;
        }
    }
    return 1;
}

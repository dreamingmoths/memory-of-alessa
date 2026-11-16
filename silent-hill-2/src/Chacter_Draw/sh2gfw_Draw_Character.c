#include "Chacter_Draw/sh2gfw_Draw_Character.h"
#include "Chacter/character.h"
#include "GFW/sh2gfw_Init_ModelDrawData.h"
#include "GFW/sh2gfw_structs.h"
#include "GFW/sh2gfw_Texpacket.h"
#include "GFW/sh2gfw_globaldef.h"

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_Draw_Character", Init_CheckDrawChara_Work);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_Draw_Character", Check_Draw_Chara);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_Draw_Character", sh2gfw_init_Chara_SyncCid);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_Draw_Character", sh2gfw_set_d1cid);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_Draw_Character", sh2gfw_sync_d1cid);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_Draw_Character", sh2gfw_Draw_Character_Pre);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_Draw_Character", sh2_CharacterDrawOne);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_Draw_Character", sh2gfw_Character_DrawOne);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_Draw_Character", sh2gfw_Exec_AnimeAndCollision);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_Draw_Character", sh2gfw_Exec_Character_Draw);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_Draw_Character", sh2gfw_Exec_Character_Draw_ShadowOnly);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_Draw_Character", sh2_Model_SyncOT);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_Draw_Character", sh2_Model_DummySyncOT);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_Draw_Character", sh2gfw_get_ModelChangeTB);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_Draw_Character", sh2gfw_get_ModelIndexTB);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_Draw_Character", sh2gfw_Thr_Chracter_d1d2SyncKick);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_Draw_Character", sh2gfw_get_Charaid);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_Draw_Character", sh2gfw_get_TBChangeVU1num);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/sh2gfw_Draw_Character", sh2gfw_set_CharaD1CID);

void sh2gfw_SetNoise_CharaTexture(int charaid) {
    int i;  
    sh2gfw_Model_Header* sMH; sh2gfw_ModelDraw_MAN* pMD;
    pMD = sh2gfw_Get_pMD(charaid);
    
    if (pMD != NULL) {
        sMH = pMD->pModel_Header;
        for (i = 0; i < sMH->texnum; i++) {
            
            sh2gfw_Change_TexBody(pMD->pTexMAN[i], CalcTex_buffer);
        }   
    }
}

void sh2gfw_RemoveNoise_CharaTexture(int charaid) {
    int i;  
    sh2gfw_Model_Header* sMH; sh2gfw_ModelDraw_MAN* pMD;
    pMD = sh2gfw_Get_pMD(charaid);
    
    if (pMD != NULL) {
        sMH = pMD->pModel_Header;
        
        for (i = 0; i < sMH->texnum; i++) {            
            
            sh2gfw_Reset_TexBody(pMD->pTexMAN[i]);
        }   
    }
}

#include "Chacter/m3_play_efect.h"
#include "Chacter/m3_play.h"
#include "Chacter/m3_sc.h"

#include "DS_Pad/dsr_data.h"
#include "DS_Pad/ds_sequencer.h"

#include "Effect/ef_cartridge.h"
#include "Effect2/hh_class_object_execute.h"

static void shJamesEffectFoot(int type);

void PlayerCheckEffect(void) {
    
    AnimeInfo* anim_p = shCharacterAnimeGetInfo_(sh2jms.player, 1);
    
    short now_frame = -1;
    
    
    
    short call_frame = shCharacterAnimeFrameGet_(sh2jms.player, 1);  
    int n;    
    switch (sh2jms.upper_now) {
        case JMS_ST_U_ATTACK:
            switch (sh2jms.weapon) {
                case WEAPON_ID(WEAPON_HANDGUN_CHARA_KIND):
                    switch (anim_p->name) {
                        case 0xD0:
                            now_frame = 16;
                            break;
                        case 0xCF:
                            now_frame = 1;
                            break;
                    }
                    break;
                case WEAPON_ID(WEAPON_SHOTGUN_CHARA_KIND):
                    if (anim_p->name != 0x104) {
                        now_frame = 22;
                    }
                    break;
                case WEAPON_ID(WEAPON_RIFLGUN_CHARA_KIND):
                    if (anim_p->name == 0x130) {
                        now_frame = 5;
                    }
                    break;
            }
    } 
    
    
    if (now_frame >= 0) {
        if (call_frame >= now_frame) {
            if (sh2jms.efct_upper == 0) {
                if (sh2jms.weapon == WEAPON_ID(WEAPON_RIFLGUN_CHARA_KIND)) {
                    n = 4;
                } else {
                    n = 1;
                }
                for (;n > 0; n--) 
                    EFCTSetDischargeCartridge(sh2jms.weapon);
            }
            sh2jms.efct_upper = 1;
            return;
        } else sh2jms.efct_upper = 0;
    
    }
}

static void shJamesEffectFoot(int type) {
    sceVu0FMATRIX m_toe; sceVu0FMATRIX m_heel;
    int p_toe; int p_heel;

    if (type != 0) {
        p_toe = 30;
        p_heel = 26;
    } else {
        p_toe = 29;
        p_heel = 25;
    }
    
    GetPlayerPartsWorldMatrix(&m_toe[0], p_toe);
    GetPlayerPartsWorldMatrix(&m_heel[0], p_heel);
    
    HH_Effect_Object_Ground_Impact_Post(m_toe[3], m_heel[3], type, sh2jms.player->id);
}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_efect", shJamesSoundOn);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_efect", PlayerCheckSoundLower);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_efect", PlayerCheckSoundUpper);

void PlayerCheckSound(void) {
    PlayerCheckSoundLower();
    PlayerCheckSoundUpper();
}

#ifdef NON_MATCHING
void PlayerCheckDualShock(void) {
    
    float rate = sh2jms.player->battle.hp_rate; // r20    
    
    
    
    switch (sh2jms.d_shock) {
        case 1:
            DSR_Entry0(__show_weapon_l_00, 0, 1.0f);
            break;
        case 2:
            DSR_Entry0(__show_weapon_l_01, 0, 1.0f);
            break;
        case 3:
            DSR_Entry0(__show_weapon_l_02, 0, 1.0f);
            break;
        case 4:
            DSR_Entry0(__show_weapon_l_03, 0, 1.0f);
            break;
    }
    sh2jms.d_shock = 0;
    
    
    if (rate < 75.0f) {
                
        
        
        switch ((int)(0.053333335f * rate)) {
            case 0:
                DSR_Entry0(__show_kodou_h_03, 0, 1.0f);
                break;
            case 1:
                DSR_Entry0(__show_kodou_h_02, 0, 1.0f);
                break;
            case 2:
                DSR_Entry0(__show_kodou_h_01, 0, 1.0f);
                break;
            case 3:
                DSR_Entry0(__show_kodou_h_00, 0, 1.0f);
                break;
        }
    }

}
#else
INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_efect", PlayerCheckDualShock);
#endif

int PlayerJamesIsInSquare(float* pos0, float* pos1) {
    if ((sh2jms.player->pos.x > pos0[0]) &&
         (sh2jms.player->pos.x < pos1[0]) &&
        (sh2jms.player->pos.z > pos0[2]) &&
         (sh2jms.player->pos.z < pos1[2])) {
            return 1;        
    }
    return 0;
}

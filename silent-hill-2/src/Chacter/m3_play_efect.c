#include "Chacter/m3_play_efect.h"
#include "Chacter/m3_play.h"
#include "Chacter/m3_sc.h"

#include "DS_Pad/dsr_data.h"
#include "DS_Pad/ds_sequencer.h"

#include "Effect/ef_cartridge.h"
#include "Effect2/hh_class_object_execute.h"

#include "SH2_common/sh_vu0.h"
#include "sce/libvu0.h"

#include "sound/sh_sd_call.h"
#include "sound/sh_sound.h"

#define SE_JMS_START 11000
#define SE_JMS_END   19908

static void shJamesEffectFoot(int type);
static int shJamesSoundOn(SubCharacter* this, float vol, int se_name, int idk);
static void PlayerCheckSoundLower(void);
static void PlayerCheckSoundUpper(void);

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

static int shJamesSoundOn(SubCharacter* this, float vol, int se_name, int idk) {
    ASSERT_ON_LINE(se_name >= SE_JMS_START && se_name <= SE_JMS_END, 189);
    SeCallPos(se_name, vol, &this->pos, 0);
    return 0;
}

static void PlayerCheckSoundLower(void) {
    int i; // r21
    u_int material; // r16
    u_short se, se_r, se_l;
    short frame;  
    int pitch; // r2    
    AnimeInfo * a_info; // r20
    sceVu0FVECTOR pos0, pos1;
    JamesSoundInfo se_info[4] = {
        { 0.0f, -1, -1 },
        { 0.0f, -1, -1 },
        { 0.0f, -1, -1 },
        { 0.0f, -1, -1 },
    };
    a_info = shCharacterAnimeGetInfo_(sh2jms.player, 2);
    
    
    
    frame = shCharacterAnimeFrameGet_(sh2jms.player, 2);
    
    
    
    
    
    
    se_info[0].vol = 0.5f;
    se_info[1].vol = 0.5f;

    switch (sh2jms.lower_now) {
        case JMS_ST_L_STAND:
            break;

        
        
        case JMS_ST_L_EVENT:                                        
            switch (a_info->name) {
                case 0x68:                                  
                case 0x6B:                                  
                    se_info[0].frame = 5;
                    se_info[1].frame = 17;
                    break;
                case 0x4E22:                                
                    se_info[0].vol = 0.2f;
                    se_info[1].vol = 0.2f;
                    se_info[2].vol = 0.2f;
                    se_info[0].frame = 26;
                    se_info[1].frame = 44;
                    se_info[2].frame = 56;
                    break;
                case 0x4E23:                                
                    se_info[1].vol = 0.2f;
                    se_info[0].frame = 25;
                    se_info[1].frame = 110;
                    break;
            }
            break;        
        case JMS_ST_L_BACK:       
        case JMS_ST_L_WALK:                                         
        case JMS_ST_L_RSWALK:                                        
        case JMS_ST_L_LSWALK:                                        
        case JMS_ST_L_RUN1:                                        
        case JMS_ST_L_RUN2:                                        
        case JMS_ST_L_RUN3:                                        
        case JMS_ST_L_RSRUN:                                        
        case JMS_ST_L_LSRUN:      
            if (sh2jms.weapon == WEAPON_ID(WEAPON_NATA_CHARA_KIND)) {
                se_info[0].frame = 3;
                se_info[1].frame = 14;
            } else {
                se_info[0].frame = 5;
                se_info[1].frame = 17;
            }
            if (10 < sh2jms.lower_now) {
                se_info[0].vol = 0.8f;
                se_info[1].vol = 0.8f;
            }
            break;        
        case JMS_ST_L_LROUND:                                         
        case JMS_ST_L_RROUND:                                         
            se_info[0].frame = 6;
            se_info[1].frame = 13;
            break;
        
        
        

        
        
        
        
        
                
        case JMS_ST_L_GUARD:
            break;
        case JMS_ST_L_WALL_F:                                        
            se_info[0].frame = 1;
            se_info[1].frame = 3;
            se_info[2].frame = 8;
            se_info[3].frame = 12;
            se_info[0].vol = 0.9f;
            se_info[1].vol = 0.8f;
            se_info[2].vol = 0.6f;
            se_info[3].vol = 0.4f;
            break;
        
        case JMS_ST_L_DAMAGE:                                        
            switch (a_info->name) {                        
                case 0x4E28:                                
                    se_info[0].frame = 3;
                    se_info[1].frame = 6;
                    se_info[2].frame = 8;
                    se_info[3].frame = 11;
                    se_info[0].vol = 0.6f;
                    se_info[1].vol = 0.5f;
                    se_info[2].vol = 0.35f;
                    se_info[3].vol = 0.2f;
                    break;
                case 0x4E29:                                
                    se_info[0].frame = 2;
                    se_info[1].frame = 4;
                    se_info[2].frame = 6;
                    se_info[3].frame = 7;
                    se_info[0].vol = 0.6f;
                    se_info[1].vol = 0.5f;
                    se_info[2].vol = 0.35f;
                    se_info[3].vol = 0.2f;
                    break;
                case 0x4E2A:                                
                    se_info[0].frame = 5;
                    se_info[1].frame = 11;
                    se_info[2].frame = 15;
                    se_info[3].frame = 25;
                    se_info[0].vol = 0.6f;
                    se_info[1].vol = 0.5f;
                    se_info[2].vol = 0.35f;
                    se_info[3].vol = 0.2f;
                    break;
                case 0x4E2B:                                
                    se_info[0].frame = 4;
                    se_info[1].frame = 7;
                    se_info[0].vol = 0.6f;
                    se_info[1].vol = 0.5f;
                    break;
                case 0x4E2E:                                
                    se_info[0].frame = 5;
                    se_info[1].frame = 8;
                    se_info[2].frame = 15;
                    se_info[0].vol = 0.6f;
                    se_info[1].vol = 0.5f;
                    se_info[2].vol = 0.35f;
                    break;
                case 0x4E2F:                                
                    se_info[0].frame = 3;
                    se_info[1].frame = 10;
                    se_info[0].vol = 0.6f;
                    se_info[1].vol = 0.5f;
                    break;
            }
            break;

        default:
        case JMS_ST_L_FALL:
        case JMS_ST_L_KICK: 
            break;
    }

    
    
    
    
    for (i = 0; i < 2; i++) {
        if (i != 0) {
            if (sh2jms.l_foot.kind == 1) 
                material = sh2jms.l_foot.hobj.wall.pd->material;            
        } else if (sh2jms.r_foot.kind == 1) 
            material = sh2jms.r_foot.hobj.wall.pd->material;
                
        
        
        
        switch (material) {                           
            case 12:                                    
                se = 0x2AF9;
                break;
            
            
            
            
            
            
            
            
            
            
            
            case 0:                                     
                se = 0x2AF9;
                
                
                break;
            case 1:                                     
                se = 0x2AFC;
                break;
            case 2:                                     
                se = 0x2AFA;
                break;
            case 3:                                     
                se = 0x2AFF;
                break;
            case 4:                                     
                se = 0x2AFC;
                break;
            case 5:                                     
                switch (sh2jms.room_name_now) {
                    case 0x2A:
                    case 0x46:
                        se = 0x4DC4;
                        
                        
                        
                        
                        break;
                    default:
                        se = 0x2AF8;
                        break;
                }
                break;
            case 6:                                     
                if (PlayerWaterRoadIsOn()) {
                    se = 0x4977;
                } else {
                    se = 0x2AFB;
                }
              
                
                
                
                
                
                
                
                
                
                
                
                
                
                break;
            case 7:                                     
                se = 0x2AFD;
                break;
            case 8:                                     
                switch (sh2jms.room_name_now) { 
                    case 0x92:
                        {
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            sceVu0FVECTOR pos0 = { -20900.0f, 0.0f, 18500.0f, 0.0f };
                            sceVu0FVECTOR pos1 = { -19200.0f, 0.0f, 22740.0f, 0.0f };
                            
                            if (PlayerJamesIsInSquare(&pos0, &pos1)) {
                                
                                se = 0x4DC3;
                            
                            
                            
                            } else {                                                    
                                se = 0x2B01;
                            }
                            
                            break;
                        }
                    case 0x99:
                        {
                            sceVu0FVECTOR pos0 = { -64000.0f, 0.0f, 20730.0f, 0.0f };
                            sceVu0FVECTOR pos1 = { -63000.0f, 0.0f, 22000.0f, 0.0f };
                            
                            if (PlayerJamesIsInSquare(&pos0, &pos1)) {
                            
                                se = 0x4DC3;
                            
                            
                            
                            } else {
                                se = 0x2B01;
                            }
                            
                            break;
                        }
                    case 0xA0:
                        {
                            sceVu0FVECTOR pos0 = { 60000.0f, 0.0f, -19420.0f, 0.0f };
                            sceVu0FVECTOR pos1 = { 62000.0f, 0.0f, -18000.0f, 0.0f };
                            
                            if (PlayerJamesIsInSquare(&pos0, &pos1)) {
                            
                                se = 0x4DC3;
                            
                            
                            
                            } else {
                                se = 0x2B01;
                            }
                            
                            break;
                        }
                    case 0xA3:   
                        {
                            sceVu0FVECTOR pos0 = { 16000.0f, 0.0f, 20000.0f, 0.0f };
                            sceVu0FVECTOR pos1 = { 16800.0f, 0.0f, 21500.0f, 0.0f };                    
                            
                            if (PlayerJamesIsInSquare(&pos0, &pos1)) {
                                
                                se = 0x4DC3;
                            
                            
                            
                            } else {
                                se = 0x2B01;
                            }                            
                            break;
                        }                    
                    case 0x3E:
                        se = 0x2B2E;
                        break;
                    default:
                        se = 0x2B01;
                        break;
                }
                break;
            case 9:                                     
                se = 0x2AFE;
                break;
            case 10:                                    
                se = 0x2B00;
                break;
            case 11:                                    
                se = 0x2AF8;
                break;
            default:                                    
                
                se = 0x2AF9;
                break;
        }
        if (i != 0) {
            se_l = se;
        } else {
            se_r = se;
        }
    }
    
    
    switch (sh2jms.lower_now) {
        case 0:                                         
            se_info[0].domain = 1;     
            break;
        case 31:                                        
            switch (a_info->name) {                        
                case 0x68:                                  
                case 0x6B:                                  
                    se_info[0].domain = 1;
                    se_info[1].domain = 2;
                    break;
                case 0x4E22:                                
                    se_info[0].domain = 1;
                    se_info[1].domain = 2;
                    se_info[2].domain = 1;
                    break;
                case 0x4E23:                                
                    se_info[0].domain = 2;
                    se_info[1].domain = 2;
                    break;
            }
            break;
        case 8: 
        case 9:  
        case 11:
        case 10:
        case 12: 
        case 13:   
        case 14: 
        case 16:   
        case 15: 
        case 7:   
        case 23:                                                                                                                 
            se_info[0].domain = 1;
            se_info[1].domain = 2;
            
            break;
        case 6:                                        
        case 22:                                         
            se_info[0].domain = 2;
            se_info[1].domain = 1;
            break;

        
        
        
        case 17:                                        
            switch (sh2jms.lower_prev) {
                case 12:                                    
                case 13:                                    
                case 14:                                    
                    se_info[0].domain = 1;
                    se_info[1].domain = 2;
                    se_info[2].domain = 1;
                    se_info[3].domain = 2;
                    break;
                case 16:                                    
                    se_info[0].domain = 1;
                    se_info[1].domain = 2;
                    se_info[2].domain = 2;
                    se_info[3].domain = 1;
                    break;
                case 15:                                    
                    se_info[0].domain = 2;
                    se_info[1].domain = 1;
                    se_info[2].domain = 1;
                    se_info[3].domain = 2;
                    break;
                default:                                    
                    ASSERT_ON_LINE(0, 630);
            }
            break;
        
        case 25:                                        
            se_info[0].domain = 1;
            se_info[1].domain = 2;
            se_info[2].domain = 1;
            se_info[3].domain = 2;
            break;
    }

    for (i = 0; i < 4; i++) {
        if (se_info[i].frame >= 0) {
            if (frame >= 0) {                    
                if (frame >= se_info[i].frame) {
                    if (sh2jms.se_foot[i] == 0) {
                        switch (se_info[i].domain) {
                            
                            case 1:
                                shJamesSoundOn(sh2jms.player, se_info[i].vol, se_r, 0);
                                
                                shJamesEffectFoot(1);
                                
                                if (se_info[i].vol >= 0.6f) sh2jms.se_on = 1; 
                                break;
                        
                            case 2:
                                shJamesSoundOn(sh2jms.player, se_info[i].vol, se_l, 0);
                                
                                shJamesEffectFoot(0);
                                
                                if (se_info[i].vol >= 0.6f) sh2jms.se_on = 1;
                                break;
                        }
                    }
                    sh2jms.se_foot[i] = 1;
                } else {
                    sh2jms.se_foot[i] = 0;
                }
            }
        }
    }

}

static void PlayerCheckSoundUpper(void) {
    
    AnimeInfo* anim_p = shCharacterAnimeGetInfo_(sh2jms.player, 1);
    int i; 
    u_short se, se2; 
    u_int material;
    short frame;  
    {
        JamesSoundInfo se_info[4] = {
        { 0.0f, -1, -1 },
        { 0.0f, -1, -1 },
        { 0.0f, -1, -1 },
        { 0.0f, -1, -1 }
        };        
        
        
        frame = shCharacterAnimeFrameGet_(sh2jms.player, 1);
        se = se2 = 0;
        
        
        switch (sh2jms.upper_now) {
            case JMS_ST_U_BACK:
            case JMS_ST_U_WALK:
            case JMS_ST_U_RSWALK:
            case JMS_ST_U_LSWALK:
                if (sh2jms.weapon == WEAPON_ID(WEAPON_NATA_CHARA_KIND)) {
                    se = 0x2B3B;
                    se2 = 0x2B3B;
                }
                break;
            
            case JMS_ST_U_STAND: break;    
            case JMS_ST_U_ATTACK:           
                switch (sh2jms.weapon) {
                    case WEAPON_ID(WEAPON_KAKUZAI_CHARA_KIND):
                        se = 0x2B13;
                        se2 = (!(shRandI() & 1) ? 0x2B0B : 0x2B0A);
                        break;
                    case WEAPON_ID(WEAPON_PIPE_CHARA_KIND):
                        se = 0x2B13;
                        se2 = (!(shRandI() & 1) ? 0x2B0B : 0x2B0A);
                        break;
                    
                        
                        
                                    
                    case WEAPON_ID(WEAPON_NATA_CHARA_KIND):
                        se = 0x2B1F;
                        se2 = (!(shRandI() & 1) ? 0x2B0B : 0x2B0A);
                        break;
                    case WEAPON_ID(WEAPON_HANDGUN_CHARA_KIND):
                        switch (anim_p->name) {
                            case 0xD1:
                            case 0xD2:
                                se = 0x2B15;
                                break;
                        }
                        break;
                    case WEAPON_ID(WEAPON_SHOTGUN_CHARA_KIND):
                        switch (anim_p->name) {
                            case 0x104:
                                se = 0x2B3C;
                                break;
                            default:
                                se = 0x2B2D;
                        }
                        
                        
                        break;
                    case WEAPON_ID(WEAPON_RIFLGUN_CHARA_KIND):
                        if (anim_p->name == 0x130) {
                            se = 0x2B2A;
                        }
                        break;
                    case WEAPON_ID(WEAPON_SP_CHARA_KIND):
                        switch (anim_p->name) {
                            case 0x1FE:
                            case 0x1FF:                        
                                se = se2 = 0x2B2F;
                        }
                }
                
                
                break;
            case JMS_ST_U_LTURN:                                        
            case JMS_ST_U_RTURN:                                        
                if (sh2jms.upper_now == JMS_ST_U_LTURN) {
                    if (sh2jms.l_foot.kind == 1) 
                        material = sh2jms.l_foot.hobj.wall.pd->material;
                }  else if (sh2jms.r_foot.kind == 1)
                    material = sh2jms.r_foot.hobj.wall.pd->material;
                    
    
                
                
                switch (material) {
                    case 12:
                        se = 0x2B02;
                        break;
                    case 0:
                        se = 0x2B02;
                        break;
                    case 1:
                        se = 0x2B08;
                        break;
                    case 2: 
                        se = 0x2B06;
                        break;
                    case 3:
                        se = 0x2B05;
                        break;
                    case 4: 
                        se = 0x2B08;
                        break;
                    case 5: 
                        se = 0x2B03;
                        break;
                    case 6: 
                        switch (sh2jms.room_name_now) {
                            case 0x7A:
                            case 0x7C:
                            case 0x7E:
                            case 0x80:
                                se = 0x4977;
                                break;
                            default:
                                se = 0x2B05;
                        }
                    
                        break;
                    case 7:                                     
                        se = 0x2B02;
                        break;
                    case 8:                                     
                        se = 0x2B07;
                        break;
                    case 9:                                     
                        se = 0x2B03;
                        break;
                    case 10:                                    
                        se = 0x2B04;
                        break;
                    case 11:                                    
                        se = 0x2B03;
                        break;
                    default:                                    
                        se = 0x2B02;
                        break;
                }
                
                break;
            
                case JMS_ST_U_KICK:                                        
                    if (sh2jms.u_anime_st_flg == 0) {
                        se = 0x2B0D;
                    }
                    break;
                
            case JMS_ST_U_WALL_F:                  
                    material = sh2jms.player->eye.hobj.wall.pd->material;
                    switch (material) {                          
                        case 0:                                     
                        case 5:                                     
                        case 12:                                    
                            se = 0x2B1A;
                            break;
                        case 9:                                     
                        case 11:                                    
                            se = 0x2B1C;
                            break;
                        case 7:                                     
                            se = 0x2B1B;
                            break;
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 6:
                        case 8:
                        case 10:
                        default:                                    
                            se = 0x2B1A;
                            break;
                }
                
                break;
            case JMS_ST_U_ALERT:                                         
                if (sh2jms.weapon == 7) {
                    se = 0x2B11;
                }
                break;
            case JMS_ST_U_TIRED:                                         
                se = 0x2B09;
                break;
            case JMS_ST_U_DAMAGE:                                        
                if (sh2jms.dead != 0) {
                    se = 0x2B10;
                    switch (sh2jms.player->battle.id) {
                        case 45:                                
                            se2 = 0x3EF8;
                            break;
                        case 49:
                            se2 = 0x3EFA;
                            break;
                    }
                } else {
                    
                    switch (shRandI() % 3) {                      
                        case 0:                                 
                            se = 0x2B0C;
                            break;
                        case 1:                                 
                            se = 0x2B0D;
                            break;
                        case 2:                                 
                            se = 0x2B0E;
                            break;
                    }
                    switch (sh2jms.player->battle.id) {    
                        case 0x26:
                        case 0x27:  
                        case 0x28:                              
                        case 0x29:                              
                        case 0x2A:                              
                        case 0x2B:                              
                        case 0x3D:                              
                            se2 = 0x2B3D;
                            break;
                        case 0x2C:                              
                            se2 = 0x3EF9;
                            break;
                        case 0x32:                              
                            se2 = 0x3EFB;
                            break;
                        case 0x36:                              
                            se2 = (!(shRandI() & 1) ? 0x484B : 0x484A);
                            break;
                        case 0x3B:                              
                            se2 = (!(shRandI() & 1) ? 0x49A9 : 0x49A8);
                            break;
                    }
                }
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                break;            
            case JMS_ST_U_FALL:
                se = 0x2B0C;
                se2 = 0x2B3E;
                break;
        }
        
        
        switch (sh2jms.upper_now) {
            case JMS_ST_U_BACK:
            case JMS_ST_U_WALK:
            case JMS_ST_U_RSWALK:
            case JMS_ST_U_LSWALK:    
                if (sh2jms.weapon == 8) {
                    se_info[0].frame = 5;
                    se_info[1].frame = 18;
                    se_info[0].vol = 0.3f;
                    se_info[1].vol = 0.3f;
                }
                break;
            
            case JMS_ST_U_ATTACK:
                switch (sh2jms.weapon) { 
                    case WEAPON_ID(WEAPON_HANDGUN_CHARA_KIND):
                        switch (anim_p->name) {
                            case 0xD1:
                                se_info[0].frame = 21;
                                break;
                            case 0xD2: 
                                se_info[0].frame = 26;
                                break;
                            }
                            se_info[0].vol = 0.5f;
                            break;
                    case WEAPON_ID(WEAPON_SHOTGUN_CHARA_KIND):
                        switch (anim_p->name) {
                            case 0x104:
                                se_info[0].frame = 12;
                                se_info[0].vol = 0.5f;
                                break;
                            default:
                                se_info[0].frame = 23;
                                se_info[0].vol = 0.5f;
                        }
                        
                        break;
                    case WEAPON_ID(WEAPON_RIFLGUN_CHARA_KIND):
                        if (anim_p->name == 0x130) {
                            se_info[0].frame = 17;
                            se_info[0].vol = 0.5f;
                        }
                        break;
                    case WEAPON_ID(WEAPON_SP_CHARA_KIND):
                        switch (anim_p->name) {
                            case 0x1FE:
                                se_info[0].frame = 7;
                                se_info[0].vol = 0.5f;
                                se_info[1].frame = 14;
                                se_info[1].vol = 0.5f;
                                break;
                            case 0x1FF:
                                se_info[0].frame = 3;
                                se_info[0].vol = 0.5f;
                                se_info[1].frame = 10;
                                se_info[1].vol = 0.5f;
                                break;
                        }
                        break;
                    case WEAPON_ID(WEAPON_KAKUZAI_CHARA_KIND):
                        if (anim_p->speed > 0) {
                            switch (sh2jms.atk_type) {
                                case 3:                             
                                    if (sh2jms.atk_count != 0) {
                                        se_info[0].frame = 7;
                                        se_info[1].frame = 7;
                                    } else {
                                        se_info[0].frame = 11;
                                        se_info[1].frame = 11;
                                    }
                                    se2++;
                                    break;
                                case 4:                             
                                    if (sh2jms.atk_count != 0) {
                                        se_info[0].frame = 7;
                                        se_info[1].frame = 7;
                                    } else {
                                        se_info[0].frame = 10;
                                        se_info[1].frame = 10;
                                    }
                                    break;
                            }
                            se_info[0].vol = 0.9f;
                            se_info[1].vol = (float)((double)shRandF() * 0.7);
                        }
                        break;
                    case WEAPON_ID(WEAPON_PIPE_CHARA_KIND):
                        if (anim_p->speed > 0) {
                            switch (sh2jms.atk_type) {
                            case 5:
                                se_info[0].frame = 8;
                                se_info[1].frame = 7;
                                se2++;
                                break;
                            case 3:
                                if (sh2jms.atk_count != 0) {
                                    se_info[0].frame = 2;
                                    se_info[1].frame = 2;
                                } else {
                                    se_info[0].frame = 8;
                                    se_info[1].frame = 8;
                                }
                                se2++;
                                break;
                            case 4:
                                if (sh2jms.atk_count != 0) {
                                    se_info[0].frame = 9;
                                    se_info[1].frame = 9;
                                } else {
                                    se_info[0].frame = 15;
                                    se_info[1].frame = 13;
                                }
                                break;
                            }
                            se_info[0].vol = 0.9f;
                            se_info[1].vol = (float)((double)shRandF() * 0.7);
                        }
                        break;
                    case WEAPON_ID(WEAPON_NATA_CHARA_KIND):
                        if (anim_p->speed > 0) {
                            switch (sh2jms.atk_type) {
                                case 3:
                                    if (sh2jms.hold_type == 0) {
                                        se_info[0].frame = 8;
                                        se_info[1].frame = 8;
                                    } else {
                                        se_info[0].frame = 11;
                                        se_info[1].frame = 11;
                                    }
                                    se2++;
                                    break;
                                case 4:
                                    if (sh2jms.hold_type == 0) {
                                        se_info[0].frame = 17;
                                        se_info[1].frame = 17;
                                    } else {
                                        se_info[0].frame = 18;
                                        se_info[1].frame = 18;
                                    }
                                    break;
                            }
                            se_info[0].vol = 0.9f;
                            se_info[1].vol = (float)((double)shRandF() * 0.7);
                        }
                        break;
                }
                break;
            case JMS_ST_U_LTURN:                                        
            case JMS_ST_U_RTURN:                                        
                se_info[0].frame = 1;
                se_info[0].vol = 0.5f;
                break;
            case JMS_ST_U_KICK:                                        
                if (sh2jms.u_anime_st_flg == 0) {
                    switch (sh2jms.atk_type) {               
                        case 7:
                            se_info[0].frame = 4;
                            se_info[0].vol = 0.9f;
                            break;
                        case 6:
                            se_info[0].frame = 8;
                            se_info[0].vol = 0.9f;
                            break;
                    }
                }
                break;
            case JMS_ST_U_WALL_F:                                        
                se_info[0].frame = 4;
                se_info[0].vol = 0.6f;
                break;
            case JMS_ST_U_ALERT:                                         
                if (sh2jms.weapon == 7) {
                    se_info[0].frame = 4;
                    se_info[0].vol = 0.4f;
                }
                break;
            case JMS_ST_U_TIRED:                                         
                se_info[0].frame = 1;
                se_info[0].vol = 0.3f;
                break;
            case JMS_ST_U_DAMAGE:                                        
                se_info[0].frame = 1;
                se_info[0].vol = 0.7f;
                if (se2) {
                    se_info[1].frame = 1;
                    se_info[1].vol = 0.7f;
                }
                break;
            case JMS_ST_U_FALL:
                se_info[0].frame = 1;
                se_info[0].vol = 0.7f;
                se_info[1].frame = 1;
                se_info[1].vol = 0.7f;
                break;
        }

        
        for (i = 0; i < 4; i++) {
            if (se_info[i].frame >= 0) {
                if (frame >= 0) {
                    if (frame >= se_info[i].frame) {
                        if (sh2jms.se_upper[i] == 0) {
                            
                            
                            shJamesSoundOn(sh2jms.player, se_info[i].vol, (i == 1) ? se2 : se, 0); // one more arg?
                            if (se_info[i].vol > 0.6f) 
                                sh2jms.se_on = 1;                            
                        }
                        sh2jms.se_upper[i] = 1;                        
                    } else {
                        sh2jms.se_upper[i] = 0;
                    }
                }
            }
        }
        
        
        
        
        if (sh2jms.weapon == WEAPON_ID(WEAPON_CSAW_CHARA_KIND)) {
            if (sh2jms.hold_type == -1) {
                if (sh2jms.csaw_se_vol) {
                    sh2jms.csaw_se_vol -= 0.07f;
                    SeCallPosChange(0x2B24, sh2jms.csaw_se_vol, &sh2jms.player->pos, 0);
                    
                    SeCallPosChange(0x2B25, sh2jms.csaw_se_vol, &sh2jms.player->pos, 0);
                    
                    if (sh2jms.csaw_se_vol <= 0.0f) 
                        sh2jms.csaw_se_vol = 0.0f;                                        
                } else {
                    shSdSeStop(0x2B24);
                    shSdSeStop(0x2B25);
                }
            }
            
            if (sh2jms.csaw_se_vol > 0.6f) {
                sh2jms.se_on = 1;
            }
        }
        if (sh2jms.weapon == WEAPON_ID(WEAPON_SP_CHARA_KIND)) {
            if ((sh2jms.hold_type == -1) || (sh2jms.shoot_val == 0)) {
                shSdSeStop(0x2B27);
                sh2jms.csaw_se_vol = 0.0f;
            } else {
                SeCallPosChange(0x2B27, (sh2jms.spray_time >= 10.0f) ? 0.5f : 0.1f * (sh2jms.spray_time * 0.5f), &sh2jms.player->pos, 0);
            }    
        }
    }















}

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

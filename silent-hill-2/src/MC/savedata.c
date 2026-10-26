#include "MC/savedata.h"
#include "SH2_common/sh_vu0.h"
#include "sound/sh_sd_call.h"
#include "sound/sh_sound.h"
#include "Chacter/chara_saveinfo.h"
#include "shGs/sh2gfw_GsInit.h"
#include "GFW/sh2_set_drawenv.h"
#include "vec.h"
#include "connect.h"

void SetSavePointName(u_short msg_no) {
    SaveDataAll.d.scene = msg_no;
}

void SetSaveData(void) {
    u_short scene = SaveDataAll.d.scene;
    shQzero(&SaveDataAll, sizeof(SAVE_DATA_ALL));
    SaveDataAll.d.version = 4;
    SaveDataAll.d.scene = scene;
    shVectorCopy(SaveDataAll.d.jms_pos, &sh2jms.player->pos);
    SaveDataAll.d.jms_pos[3] = sh2jms.player->rot.y;
    memcpy(&SaveDataAll.d.playing, &playing, sizeof(Playing_Info));
    memcpy(&SaveDataAll.d.game_flag, &game_flag, sizeof(Game_Flag));
    memcpy(&SaveDataAll.d.item, &item, sizeof(Item));
    memcpy(&SaveDataAll.d.key_config, &key_config, sizeof(Pad_KeyConfig));
    shCharacterSetSaveData(&SaveDataAll.d.chara);
}

void ExtGameData(void) {
    shVectorCopy(connect_pos, SaveDataAll.d.jms_pos);
    memcpy(&playing, &SaveDataAll.d.playing, sizeof(Playing_Info));
    memcpy(&game_flag, &SaveDataAll.d.game_flag, sizeof(Game_Flag));
    memcpy(&item, &SaveDataAll.d.item, sizeof(Item));
    
    if (SaveDataAll.d.version >= 4) 
        
        memcpy(&key_config, &SaveDataAll.d.key_config, sizeof(Pad_KeyConfig));    
    shCharacterExtGameData(&SaveDataAll.d.chara);
    SetGameEnvironment();
}

int CheckSaveData(void) {
    Playing_Info* pi = &SaveDataAll.d.playing;
    u_short* in = item.number;
   
    if (SaveDataAll.d.version != 4) {
            
        if (SaveDataAll.d.version != 3) {
            
            
            
            printf("savedata version error! (%d != %d)\n", SaveDataAll.d.version, 4);
            
            
            return 1;
        }
    }
    
    if (pi->stage >= 0x35) {
    
        printf("stage number error! (%d)\n", pi->stage);
        
        return 1;
    }
    
    if ((pi->time < 0.0f) || (pi->walk_distance < 0.0f) || (pi->run_distance < 0.0f) ||
        (pi->boat_clear_time < 0.0f) || (pi->boat_max_speed < 0.0f) || (pi->rank >= 0x65) ||
        (pi->total_time < 0.0f) || (pi->spray_pow < -1) || (pi->spray_pow >= 3) ||
        (pi->jms_damage_total < 0.0f) || (pi->mar_damage_by_enemy < 0.0f) ||
        (pi->mar_damage_by_jms < 0.0f)) {
        
        printf("resultdata error!\n");
        
        return 1;
    }
        
    if ((pi->battle_level > 4) || (pi->riddle_level >= 4)) { // @todo: new defines? SH2_BATTLE_LEVEL_INVALID?
        
        printf("leveldata error!\n");
        
        return 1;
    }
    
    if ((pi->vibration >= 4) || (pi->auto_load >= 2) || (pi->sound >= 3) ||
        (pi->weapon_control >= 2) || (pi->blood_color >= 4) || (pi->view_control >= 2) ||
        (pi->retreat_turn >= 2) || (pi->walk_run_control >= 2) || (pi->auto_aiming >= 2) ||
        (pi->view_mode >= 2) || (pi->language >= 6) || (pi->subtitles >= 2) || (pi->control_type >= 2)) {
        
        
        
        printf("configdata error!\n");
        
        return 1;
    }
    
    
    if ((in[0] > 0) ||
        (in[1] > 999) ||
        (in[2] > 999) ||
        (in[3] > 999) ||
        (in[4] > 10) ||
        (in[5] > 999) ||
        (in[6] > 6) ||
        (in[7] > 999) ||
        (in[8] > 4) ||
        (in[9] > 999) ||
        (in[10] > 8)) {
        
        printf("item number error!\n");
        
        return 1;
    }
    
    return 0;
}

void SetGameEnvironment(void) {
    
    switch (playing.sound) {
        case 0:
            shSdCall(1005, 0, 0, 0);
            shSdCall(1041, 0, 0, 0);
            break;
        case 1:
            shSdCall(1005, 0, 0, 0);
            shSdCall(1040, 0, 0, 0);
            break;
        default:
            shSdCall(1006, 0, 0, 0);
            shSdCall(1041, 0, 0, 0);
            break;
    }
    
    SeMasterVolumeChange();
    
    sh2gfw_Set_Brightness(playing.brightness_level);
    
    
    shGs_SetDefaultDispArea();
    shGs_TrimDispArea(playing.screen_position_x / 4, playing.screen_position_y / 3);

}

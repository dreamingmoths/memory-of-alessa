#include "sh2_init.h"

#include "eekernel.h"

#include "libmc.h"

#include "gamemain.h"

#include "Chacter/m3_sc.h"
#include "Chacter/m3_maria.h"
#include "Chacter/m3_play.h"
#include "Chacter/skelton.h"
#include "Chacter/sh2_character_manage.h"

#include "Chacter_Draw/sh2gfw_md_spclmapping.h"
#include "Chacter_Draw/clani.h"

#include "DBG/dbflag.h"
#include "DBG/dbfntprint.h"

#include "Enemy/en_common.h"

#include "Event/event.h"
#include "Event/demoview.h"
#include "Event/picture.h"
#include "Event/chara_data_load.h"

#include "Effect/screen_effect.h"

#include "Font/font.h"

#include "Fog/spack.h"

#include "Heap/sh2_ch_malloc.h"

#include "sh2gfw_all_sysinit.h"
#include "sh2gfw_drawloop_main.h"

#include "SH2_common/playing_info.h"
#include "SH2_common/pad.h"
#include "SH2_common/data_load.h"
#include "SH2_common/mem_share.h"
#include "SH2_common/sh2sys.h"

#include "movie/movie_main.h"

#include "MC/mc.h"

#include "Multi_thr/intc/syncv.h"
#include "Multi_thr/sys/init_mt_sys.h"
#include "Multi_thr/scf/sh2_scf.h"
#include "Multi_thr/filesys/fcread.h"
#include "Multi_thr/filesys/fileserv.h"

#include "GFW/gfw_test/kari_probe_draw.h"
#include "GFW/gfw_test/sh2gfw_util.h"
#include "GFW/sh2gfw_Texpacket.h"
#include "GFW/sh2gfw_Init_ModelDrawData.h"

#include "sound/sh_sound.h"
#include "sound/sh_sd_call.h"

#include "data/daily.thu/data_pic_etc.h"

// @todo: migrate bss

extern /* static */ int count_892;

void systemColdInit(void) {
    int fid; // r16
    int sid; // r16

    fid = init_sh2_filesys();
    
    sh2ScfInit();

    
    init_PS2();

    
    DBG_data_loadGS();


    
    mdl_SpecularMappingLoadTexture();
    
    fsSync(0, fid);

    
    fid = init_sh2_devsys();




    
    init_sh2_dmac();







    
    spkInit();
    fontInit();
    
    WaitSema(fid);
    shPadInit();
    sceMcInit();
    PlayingInfoColdInit();
    DataLoadMessage(0);
    
    sh2gfw_util_zeroq(&AllTexSync_Man, 0x1F05); // I tried sizeof(AllTexSync_Man) but it didnt like it
    
    sh2gfw_allinit_TexMANlist(&AllTexSync_Man);
    
    
    sh2gfw_kari_clear_LM();
    
    shCharacter_Manage_Init();
    
    sh2gfw_srInit_ModelDrawWork();
    
    
    
    
    
    
    FcRead(data_pic_etc_carsol_tex, cursor_adr);
    
    CharaDataLoadInit();


    
    for (;;) {
        if ((sid = shSdStat() & 0xF) != 0) {
            
            shSyncVEnd(0);
        } else break;        
    }
    
    MovieInit();
}

int systemHotInit(void) { // not line matched
    int next; // r2
    int ret;  // r16
    int wait; // r17
    int step; // r18

    step = Sh2sys.step[1];
    ret = 0;
    wait = 2;
    if (dbFlag(4)) {
        wait = 100;
    }
    if (step > 0) {
        DrawLopp_Pre();
        dbfntlocate(0x100, 0x100);
        dbfntprintf("Hot Init: %d(%d)", step, count_892);
    } else {
        count_892 = 0;
    }

    if (--count_892 <= 0) {
        switch (step) {
        case 0:
            MemShareWaitRealloc(0);
            step_init_ONE();
            all_Frame_Buffer_Clear();
            ScreenEffectInit();
            break;
        case 1:
            mcInit();
            break;
        case 2:
            sh2gfw_srInit_ModelDrawWork();
            break;
        case 3:
            CharaDataDeleteAll();
            CharaDataLoadItem();
            enInitEnemy();
            break;
        case 4:
            shCharacterInitSubCharacter();
            break;
        case 5:
            shCharacterInitSkeltons();
            break;
        case 6:
            shCharacterInitCluster();
            break;
        case 7:
            kari_ChAlloc_Init();
            break;
        case 8:
            shCharacterPlayerWorkInitAtPowerOn();
            shCharacterPlayerWorkInitAtGameStart();
            shCharacterMariaWorkInit();
            shCharacterMariaWorkInitAtGameStart();
            break;
        case 9:
            EventProgInit();
            break;
        case 10:
            SeCallReset();
            break;
        case 11:
            stage = NULL;
            playing.stage = 0;
            PlayingInfoHotInit();
            break;
        case 12:
            demo_number = 0;
            Sh2sys.main_status &= ~0x40;
            break;
        case 13:
            SeSoundLoad();
            break;
        case 14:
        default:
            if (!(shSdStat() & 0xF) && (fsSync(1, -1) >= 0)) {
                ret = 1;
            }
            break;
        }
        count_892 = wait;
        next = Sh2sys.step[1] + 1;
        Sh2sys.step[1] = next;
        Sh2sys.step[2] = 0;
        Sh2sys.step[3] = 0;
        Sh2sys.step[4] = 0;
        Sh2sys.step[5] = 0;
        Sh2sys.step[6] = 0;
        Sh2sys.step[7] = 0;
    }
    fsSync(0, -1);
    Sh2sys.soft_reset = 0;
    DrawLopp_Post();
    return ret;
}

/* static */ int PlayingInfoColdInit(void) { // @note: DWARF said this returned "void" and not "int" 
    playing.enemy_off = 0;
    playing.voice_off = 0;
    playing.memo_select = 0;
    
    playing.clear_end_kind = 0;
    playing.clear_end_number = 0;

    
    playing.battle_level = 2;
    playing.riddle_level = 1;
    
    playing.control_type = 0;
    
    playing.brightness_level = 3;
    playing.screen_position_x = 0;
    playing.screen_position_y = 0;
    playing.vibration = 2;
    playing.auto_load = 0;
    playing.sound = 0;
    playing.bgm_volume = 15;
    playing.se_volume = 15;
    playing.weapon_control = 0;
    playing.blood_color = 0;
    playing.view_control = 0;
    playing.retreat_turn = 0;
    playing.walk_run_control = 0;
    playing.auto_aiming = 1;
    playing.view_mode = 0;
    playing.bullet_adjust = 1;




    
    playing.language = 1;    
    playing.subtitles = 1;
    PlayingInfoHotInit();


    
}

/* static */ int PlayingInfoHotInit(void) {
    int i;    
    playing.savecount = 0;
    
    playing.item_get = 0;
    playing.kill_by_shot = 0;
    playing.kill_by_fight = 0;
    playing.time = 0.0f;
    playing.walk_distance = 0.0f;
    playing.run_distance = 0.0f;
    playing.boat_clear_time = 0.0f;
    playing.boat_max_speed = 0.0f;
    playing.jms_damage_total = 0.0f;
    playing.mar_damage_by_enemy = 0.0f;
    playing.mar_damage_by_jms = 0.0f;
    playing.rank = 6;
    playing.total_score = 0;
    playing.total_time = 0.0f;
    for (i = 0; i < 7; i++) {
        playing.stage_check_point[i] = 0.0f;
        playing.stage_score[i] = 0;
    }
    
}

#include "sh2_common.h"

#include "SH2_common/mem_share.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/mem_share.h"
#include "SH2_common/sh2dt.h"
#include "SH2_common/pad.h"

#include "logo.h"
#include "pause.h"
#include "gamemain.h"
#include "now_loading.h"

#include "MC/mc.h"
#include "MC/savedata.h"

#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/title.h"

#include "DBG/dbflow.h"
#include "DBG/dbfntprint.h"

#include "sound/sh_sound.h"
#include "sound/snd_select.h"

#include "Effect/screen_effect.h"
#include "Effect/screen_effect.h"

#include "MC/mc_menu.h"

#include "movie/pss_common.h"
#include "movie/movie_main.h"

#include "sh2gfw_drawloop_main.h"
#include "LoadBg/loadbg_common.h"
#include "shGs/sh2gfw_GS_NewLoopEnv.h"

#include "Font/font.h"

#define SH2_GAME_MAIN_MENU             0
#define SH2_GAME_MAIN_FIRST_BOOT       1
#define SH2_GAME_MAIN_LOGO_MC          2
#define SH2_GAME_MAIN_LOGO_1           3
#define SH2_GAME_MAIN_LOGO_2           4
#define SH2_GAME_MAIN_LOGO_3           5
#define SH2_GAME_MAIN_RESET            6
#define SH2_GAME_MAIN_TITLE_7          7
#define SH2_GAME_MAIN_DEMOPLAY_8       8
#define SH2_GAME_MAIN_TITLE_9          9
#define SH2_GAME_MAIN_DEMOPLAY_10      10
#define SH2_GAME_MAIN_TITLE_11         11
#define SH2_GAME_MAIN_OP_MOVIE         12
#define SH2_GAME_MAIN_PLAYABLE_MAIN    13
#define SH2_GAME_MAIN_CONFIG_14        14
#define SH2_GAME_MAIN_CONFIG_15        15
#define SH2_GAME_MAIN_CONFIG_16        16
#define SH2_GAME_MAIN_MC_LOAD          17

#define SH2_PLAYABLE_MAIN_START        0
#define SH2_PLAYABLE_MAIN_CONNECT      1
#define SH2_PLAYABLE_MAIN_CONNECT_WAIT 2
#define SH2_PLAYABLE_MAIN_SOUND_LOAD   3
#define SH2_PLAYABLE_MAIN_PLAYABLE     4
#define SH2_PLAYABLE_MAIN_MAP          5
#define SH2_PLAYABLE_MAIN_ITEM         6
#define SH2_PLAYABLE_MAIN_OPTION       7
#define SH2_PLAYABLE_MAIN_MEMO         8
#define SH2_PLAYABLE_MAIN_MC_SAVE      9
#define SH2_PLAYABLE_MAIN_RESULT       10
#define SH2_PLAYABLE_MAIN_END          11
#define SH2_PLAYABLE_MAIN_GAME_OVER    12
#define SH2_PLAYABLE_MAIN_MOVIE        13
#define SH2_PLAYABLE_MAIN_MOVIE_MAIN   14
#define SH2_PLAYABLE_MAIN_PAUSE        15

static int LoadBgSync(int mode, int nonblock);

char* get_gp_data_buf_addr(void) {
    return MemShare_gp_data_buf;
}

#line 124
int GameMain(void) {
    int synctype = 0, fonton;

    dbFlowSetCheckPointOnLine("pad", 127);
    shPadSet();
    dbFlowSetCheckPointOnLine("snd vol", 129);
    sndVolumeMain();
    dbFlowSetCheckPointOnLine("sound", 131);
    if (!GET_BIT(Sh2sys.main_status, 5)) {
        SeSoundManager();
    }
    
    dbFlowSetCheckPointOnLine("loadbg setinfo", 136);

    
    {
        int glb_crd = 0;
        float px = 0.0f;
        float pz = 0.0f;
        if (sh2jms.player != NULL) {
            // ...
            // ...
            // ...
            px = sh2jms.player->pos.x;
            pz = sh2jms.player->pos.z;
            
            if (stage != NULL) {
                glb_crd = stage->glb_crd;
            }
        }
        loadBgCommon_SetInfo(glb_crd, px, pz);
    }







    
    if ((Sh2sys.step[1] == SH2_GAME_MAIN_PLAYABLE_MAIN) && (Sh2sys.step[2] == SH2_PLAYABLE_MAIN_PLAYABLE)) {
        if (Sh2sys.pre_playable) shSetDF(clamp(3, Get_FrameRate()));
        else shSetDF(2);
        Sh2sys.pre_playable = 1;
    } else {
        shSetDF(2);
        Sh2sys.pre_playable = 0;
    }
    shSetDFreal(Get_FrameRate());

    
    switch (Sh2sys.step[1]) {
    
        case SH2_GAME_MAIN_MENU:
            dbFlowSetCheckPointOnLine("s:menu", 178);
        
            
            
            
            
            
            sh2sys_step_1();

        
        case SH2_GAME_MAIN_FIRST_BOOT:
            dbFlowSetCheckPointOnLine("s:bootfirst", 189);
            sh2sys_step_1();

        
        case SH2_GAME_MAIN_LOGO_MC:
            dbFlowSetCheckPointOnLine("s:logo mc", 194);
            logoCheckingMemcard();
            
            break;
        
        case SH2_GAME_MAIN_LOGO_1:
            dbFlowSetCheckPointOnLine("s:logo 1", 200);
            logoDrawWarningCESA();
            
            break;
        
        case SH2_GAME_MAIN_LOGO_2:
            dbFlowSetCheckPointOnLine("s:logo 2", 206);
            logoDrawWarningSCE();
            
            break;
        
        case SH2_GAME_MAIN_LOGO_3:
            dbFlowSetCheckPointOnLine("s:logo 3", 212);
            logoDrawKonamiLogo();
            
            break;











        case SH2_GAME_MAIN_OP_MOVIE:
            dbFlowSetCheckPointOnLine("s:op movie", 228);

            
            
            
            if (MoviePlayOPMovie() == 0) {
                sh2gfw_ForceSet_MovieDrawLoopCounter();
                MemShareWaitRealloc(0);
                sh2sys_set_1(SH2_GAME_MAIN_TITLE_7);
            }
            synctype = -1;
            break;
        
        case SH2_GAME_MAIN_RESET:
            dbFlowSetCheckPointOnLine("s:reset", 242);
            sh2sys_step_1();

        
        
        case SH2_GAME_MAIN_TITLE_7:
        case SH2_GAME_MAIN_TITLE_9:
        case SH2_GAME_MAIN_TITLE_11:
            dbFlowSetCheckPointOnLine("s:title", 250);
        
            switch (TitleMain()) {
                case 0:

                    break;
                
                case 1:
                    sh2sys_set_1(SH2_GAME_MAIN_MC_LOAD);
                    mcStepInit();
                    break;
                case 2:
                    ExtGameData();
                    Sh2sys.main_status |= 32;
                    sh2sys_set_1(SH2_GAME_MAIN_PLAYABLE_MAIN);
                    sh2sys_set_2(1);
                    mcStepInit();
                    break;
                
                default:
                    sh2sys_set_1(SH2_GAME_MAIN_PLAYABLE_MAIN);
                    mcStepInit();
                    break;
                case 4:
                    switch (Sh2sys.step[1]) {
                        default: case SH2_GAME_MAIN_TITLE_7:
                            sh2sys_set_1(SH2_GAME_MAIN_CONFIG_14); break;
                        case SH2_GAME_MAIN_TITLE_9: sh2sys_set_1(SH2_GAME_MAIN_CONFIG_15); break;
                        case SH2_GAME_MAIN_TITLE_11: sh2sys_set_1(SH2_GAME_MAIN_CONFIG_16); break;
                    }
                    sh2sys_set_2(7);
                    sh2sys_set_3(0);
                    break;




                
                case 5:
                case 6:
                    sh2sys_set_1(SH2_GAME_MAIN_OP_MOVIE);
                
                    break;
            }







            
            break;





        
        case SH2_GAME_MAIN_PLAYABLE_MAIN:
            synctype = PlayableMain();
            fonton = 1;
            break;
        case SH2_GAME_MAIN_DEMOPLAY_8:
        case SH2_GAME_MAIN_DEMOPLAY_10: {
            int cnt;
            dbFlowSetCheckPointOnLine("s:demoplay", 316);
         
            
            
            
            
            cnt = Sh2sys.step[2];
            if (shPadTrigger(0, 4)) {
                cnt = 600;
            }
            if (cnt < 600) {
                dbfntlocate(256, 256);
                dbfntprintf("playdemo:%3d/%3d", cnt, 600);
                sh2sys_step_2();
            } else {
                sh2sys_step_1();
            }
            
            break;
        }
        case SH2_GAME_MAIN_CONFIG_14:
        case SH2_GAME_MAIN_CONFIG_15:
        case SH2_GAME_MAIN_CONFIG_16:
            dbFlowSetCheckPointOnLine("s:config", 339);
            
            
            synctype = PlayableMain();
            fonton = 1;
            
            if (Sh2sys.step[3] == 1) {
                switch (Sh2sys.step[1]) {
                    default: case SH2_GAME_MAIN_CONFIG_14:
                        sh2sys_set_1(SH2_GAME_MAIN_TITLE_7); break;
                    case SH2_GAME_MAIN_CONFIG_15: sh2sys_set_1(SH2_GAME_MAIN_TITLE_9); break;
                    case SH2_GAME_MAIN_CONFIG_16: sh2sys_set_1(SH2_GAME_MAIN_TITLE_11); break;
                }
            }
            break;
        
        case SH2_GAME_MAIN_MC_LOAD:
            dbFlowSetCheckPointOnLine("s:mc load", 356);
            mcLoadMenu();
            break;
    }









    
    WaitSemaPss();
    
    NowLoadingCheck();
    
    if (PauseDisp() == 0) {
        switch (synctype) {
            case 0:
                dbFlowSetCheckPointOnLine("2d sync", 377);
                kari_drawloop_main_2dSYNC();
                break;
            case 1:
                dbFlowSetCheckPointOnLine("3d sync", 381);
                draw_main_3dSYNC();
                break;
            case -1:
                break;
        }
    
        dbFlowSetCheckPointOnLine("screen effect", 388);
        
        ScreenEffectManager();
    }
    
    NowLoadingDraw();
    
    if (fonton) {
        dbFlowSetCheckPointOnLine("font", 396);
        fontEachTurn();
    }
    
    SignalSemaPss();
    return synctype;
}

#line 407
static int LoadBgSync(int mode, int nonblock) {
    int halt;
    int rest;
    int require;
    int loading;
    do {
        halt = 0;
        require = 0;
        loading = 0;
        
        halt += loadBgAll_PrepareAround(&loading, &require);
        switch (mode) {
            case 0:
                break;
            case 2:
                break;
            
            case 1:
                halt = loading;
                break;
        }
        if (halt == 0) {
            
            
            LoadBgCharaLoadSync();
            rest = !LoadBgCharaIsLoad();
            if (rest) require++;
            if (LoadBgCharaIsMapEdge()) {
                rest = 0;
            }
            halt += rest;
        }
        if (halt == 0) {

            
            LoadBgEventLoadSync();
            rest = LoadBgEventLoadCnt();
            if (rest) require += LoadBgEventListCnt();
        }




































































        
        if (ev_p_step != 0) nonblock = 0;

        if (nonblock) break;
    } while (halt != 0);



    
    if (halt != 0) {
    
        dbfntlocate(176, 256);
        dbfntprintf("Now load back ground.\n    Please wait: %d/%d", halt, require);
    }
    return halt;
}

int PlayableMain(void) {
    int halt;
    int synctype = 0;
    int ptype;

    WaitSemaPss();
    RadioNoise();
    
    switch (Sh2sys.step[2]) {
        case SH2_PLAYABLE_MAIN_START: {
            NowLoadingEnable();
            dbFlowSetCheckPointOnLine("g0:start", 567);
            ScreenEffectFadeStart(2, 1.2f);
            FlagInit();
            ItemDataInit();
            sh2sys_step_2();
            break;
        }
        case SH2_PLAYABLE_MAIN_CONNECT: {
            NowLoadingEnable();
            dbFlowSetCheckPointOnLine("g0:connect", 577);
            ScreenEffectFadeStart(2, 1.2f);
            if ((mcAfterLoadMenu() != 0) & (connectMain() != 0)) {
                UNSET_BIT(Sh2sys.main_status, 5);
                sh2sys_step_2();
            }
            break;
        }
        case SH2_PLAYABLE_MAIN_CONNECT_WAIT: {
            NowLoadingEnable();
            dbFlowSetCheckPointOnLine("g0:connect wait", 595);
            halt = LoadBgSync(1, 1);
            if (Sh2sys.step[3] != 3) {
                sh2sys_step_3();
            } else if (!halt) {
                JumpMenuPosNormal();
                PlayerSetHeightConnectWait();
                if (GET_GAME_FLAG(GAME_FLAG_15)) {
                    MariaSetHeightConnectWait();
                }
                sh2sys_step_2();
            }
            break;
        }
        case SH2_PLAYABLE_MAIN_SOUND_LOAD: {
            NowLoadingEnable();
            dbFlowSetCheckPointOnLine("g0:sound load", 617);
            if (!Sh2sys.step[3]) {
                SeSoundLoad();
                sh2sys_step_3();
            }
            if (!(shSdStat() & 0xF) && fsSync(1, -1) >= 0) {
                if (stage->sound_call_after_load) {
                    stage->sound_call_after_load();
                }
                ScreenEffectFadeStart(4, 1.2f);
                sh2sys_step_2();
            }
            break;
        }
        case SH2_PLAYABLE_MAIN_PLAYABLE: {
            int cd_stat;
            dbFlowSetCheckPointOnLine("g0:playable", 631);
            Sh2sys.soft_reset = 1;
            cd_stat = fsGetTrayStat();
            if (cd_stat) {
                switch (cd_stat) {
                    case 1:
                        PauseSetType(5);
                        Sh2sys.step[2] = 15;
                        break;
                    case 2:
                        PauseSetType(7);
                        break;
                    case 3:
                        PauseSetType(6);
                        Sh2sys.step[2] = 15;
                        break;
                    case 4:
                        PauseSetType(8);
                        Sh2sys.step[2] = 15;
                        break;
                }
                synctype = 0;
            } else {
                    if (!ev_p_step && shPadTrigger(0, key_config.pause)) {
                        Sh2sys.step[2] = 15;
                        PauseSetType(2);
                        
                    } else if (LoadBgSync(0, 1)) {
                        PauseSetType(4);
                        synctype = 0;
                    } else {
                        dbFlowSetCheckPointOnLine("g0:playable:event main", 680);
                        EventMain();
                        if (!GET_BIT(Sh2sys.main_status, 0)) {
                            dbFlowSetCheckPointOnLine("g0:playable:draw main", 686);
                            draw_main();
                            synctype = 1;
                        } else {
                            UNSET_BIT(Sh2sys.main_status, 0);
                            clFrameInitCollisionData();
                        }
                        if (!GET_BIT(Sh2sys.main_status, 6)) {
                            GameTimerCountUp();
                        }
                }
            }
            break;
        }
        case SH2_PLAYABLE_MAIN_MAP: {
            dbFlowSetCheckPointOnLine("g0:chizu", 701);
            ChizuMain();
            GameTimerCountUp();
            break;
        }
        case SH2_PLAYABLE_MAIN_ITEM: {
            dbFlowSetCheckPointOnLine("g0:item", 708);
            itemmain();
            d1cSend(spkDmaKick());
            GameTimerCountUp();
            break;
        }
        case SH2_PLAYABLE_MAIN_OPTION: {
            dbFlowSetCheckPointOnLine("g0:option", 716);
            option_main();
            d1cSend(spkDmaKick());
            GameTimerCountUp();
            break;
        }
        case SH2_PLAYABLE_MAIN_MEMO: {
            dbFlowSetCheckPointOnLine("g0:memo", 724);
            MemoMain();
            d1cSend(spkDmaKick());
            GameTimerCountUp();
            break;
        }
        case SH2_PLAYABLE_MAIN_MC_SAVE: {
            dbFlowSetCheckPointOnLine("g0:mc save", 732);
            mcSaveMenu();
            break;
        }
        case SH2_PLAYABLE_MAIN_RESULT: {
            dbFlowSetCheckPointOnLine("g0:result", 738);
            ResultMain();
            break;
        }
        case SH2_PLAYABLE_MAIN_END: {
            dbFlowSetCheckPointOnLine("g0:end", 743);
            Sh2sys.soft_reset = 0;
            if (GameendMain()) {
                sh2sys_set_0(2);
            }
            break;
        }
        case SH2_PLAYABLE_MAIN_GAME_OVER: {
            dbFlowSetCheckPointOnLine("g0:over", 750);
            Sh2sys.soft_reset = 0;
            if (GameoverMain()) {
                sh2sys_set_0(2);
            }
            break;
        }
        case SH2_PLAYABLE_MAIN_MOVIE: {
            dbFlowSetCheckPointOnLine("g0:movie", 756);
            Sh2sys.soft_reset = 0;
            if (MovieWaitReady()) {
                sh2sys_step_2();
            }
            break;
        }
        case SH2_PLAYABLE_MAIN_MOVIE_MAIN: {
            dbFlowSetCheckPointOnLine("g0:movie main", 762);
            Sh2sys.soft_reset = 0;
            HH_Effect_Object_Texture_DesignateEntryLevel_Discard(1);
            MoviePlayFromReady();
            SignalSemaPss();
            if (MovieMain() <= 0) {
                sh2gfw_ForceSet_MovieDrawLoopCounter();
                HH_Effect_Object_Texture_AlwaysTexture_Initialize();
                MemShareWaitRealloc(0);
                sh2sys_set_2(4);
            }
            WaitSemaPss();
            if (!LoadBgSync(0, 1)) {
                shPadSet();
                dbFlowSetCheckPointOnLine("g0:event main after movie", 788);
                EventMain();
                synctype = -1;
            }
            break;
        }
        case SH2_PLAYABLE_MAIN_PAUSE: {
            int cd_stat;
            ptype = 2;
            cd_stat = fsGetTrayStat();
            switch (cd_stat) {
                case 1:
                    ptype = 5;
                    break;
                case 2:
                    ptype = 7;
                    break;
                case 3:
                    ptype = 6;
                    break;
                case 4:
                    ptype = 8;
                    break;
                case 0:
                    break;
            }
            PauseSetType(ptype);
            if (ptype == 2 && shPadTrigger(0, key_config.pause | 0xC)) {
                Sh2sys.step[2] = 4;
            }
            synctype = 0;
            break;
        }
    }
    SignalSemaPss();
    return synctype;
}

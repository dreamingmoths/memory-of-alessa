#include "common.h"
#include "SH2_common/sh2sys.h"
#include "gamemain.h"
#include "Event/event.h"
#include "Event/event_sub.h"
#include "DBG/dbflow.h"
#include "Effect/screen_effect.h"

extern Stage_Data* stage; // size: 0x4, address: 0x1126420

INCLUDE_ASM("asm/nonmatchings/gamemain", get_gp_data_buf_addr);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1030_0x00395CC0);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1031);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1032);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1033);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1034);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1035_0x00395D70);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1036_0x00395D90);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1037_0x00395DB0);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1038_0x00395DD0);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1039_0x00395DF0);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1040_0x00395E10);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1041);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1042);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1043);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1044);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1045);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1046);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1047_0x00395EF0);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1048);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1049_0x00395F30);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1050);

INCLUDE_ASM("asm/nonmatchings/gamemain", GameMain);

INCLUDE_ASM("asm/nonmatchings/gamemain", LoadBgSync);

INCLUDE_RODATA("asm/nonmatchings/gamemain", @1084_0x00395FE0);

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
                if (GET_GAME_FLAG(0, 15)) {
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

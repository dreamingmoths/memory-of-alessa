#include "sh2_common.h"
#include "SH2_common/sh2dt.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/sh2sys.h"

#include "Chacter/m3_sc.h"
#include "Chacter/sh2_battle_list.h"

#include "Chacter_Draw/sh2_JmsSpot_Man.h"

#include "Font/font.h"
#include "sound/sh_sound.h"
#include "GFW/sh2gfw_LightSet.h"
#include "Effect/screen_effect.h"

#include "Event/event.h"
#include "Event/demoview.h"

static void EventMainStandard(int ev_act_on);
static int EventCheckLook(struct Event_List* el);
static int EventListElement(struct Event_List* el, int en);
static int EventCheckIn(struct Event_List* el);
static int ItemCheckLookPoint(struct Item_List* il);
static int ItemListElement(struct Item_List* il, int en);
static int EventCheckLookPoint(float x, float z);
static int EventCheckLookLine(float x0, float z0, float x1, float z1);
static void EventPositionSet(float* pos_v, char* pos_p, int pos_t);
static void EventResultMovePosition(int ev_no);
static void EventExecSubFlagSet(struct Event_List* el);
static int EventExecFlag(void);
static int EventExecMessage(void);
static int EventExecProgram(void);
static int EventExecDoor(void);
static int EventExecItem(void);
static int EventExecMove(void);
static int EventExecSave(void);
static int EventExecChizuFail(void);

extern /* static */ Event_DoorSound door_se[22];

#pragma divbyzerocheck off
#define HANGING_MAN_COUNT 6
#line 209
void FlagInit(void) {
    int shuffle[HANGING_MAN_COUNT]; // r29+0x30
    int work; // r16
    int i; // r17
    
    shQzero(&game_flag, sizeof(Game_Flag));

    
    if (playing.riddle_level == SH2_BATTLE_LEVEL_NORMAL   && 
        playing.clear_end_kind & (1 << CLEAR_END_KIND_5)  && 
        playing.clear_end_kind & (1 << CLEAR_END_KIND_6)  &&
        playing.clear_end_kind & (1 << CLEAR_END_KIND_7)) 
        playing.riddle_level = SH2_RIDDLE_LEVEL_EXTRA;


    
    work = 0;
    for (i = 0; i < 3; i++)
        if (playing.clear_end_kind & (1 << i)) work++;
    if (work < 3 && work < playing.clear_end_number) {
        if (work == 1) {
            if (playing.clear_end_kind & (1 << CLEAR_END_KIND_0)) {
                if (shRandI() & 1) SET_GAME_FLAG(GAME_FLAG_8);
                else SET_GAME_FLAG(GAME_FLAG_9);
            }
            if (playing.clear_end_kind & (1 << CLEAR_END_KIND_1)) {
                if (shRandI() & 1) SET_GAME_FLAG(GAME_FLAG_9);
                else SET_GAME_FLAG(GAME_FLAG_7);
            }
            if (playing.clear_end_kind & (1 << CLEAR_END_KIND_2)) {
                if (shRandI() & 1) SET_GAME_FLAG(GAME_FLAG_7);
                SET_GAME_FLAG(GAME_FLAG_8);
            }
        } else {
            if (!(playing.clear_end_kind & (1 << CLEAR_END_KIND_0)))
                SET_GAME_FLAG(GAME_FLAG_7);
            if (!(playing.clear_end_kind & (1 << CLEAR_END_KIND_1)))
                SET_GAME_FLAG(GAME_FLAG_8);
            if (!(playing.clear_end_kind & (1 << CLEAR_END_KIND_2)))
                SET_GAME_FLAG(GAME_FLAG_9);
        }
    }
    if (work > 0) SET_GAME_FLAG(GAME_FLAG_10);
    if (work == 3 || (playing.clear_end_kind & (1 << CLEAR_END_KIND_3))) {
        SET_GAME_FLAG(GAME_FLAG_11);
    }

    
    game_flag.clock = shRandI() % 660;
    if (520 < game_flag.clock) game_flag.clock += 60;
    game_flag.clock <<= 6;

    
    for (i = 0; i < 4; i++) {
        game_flag.safe[i] = shRandI() % 20;
        if (i > 0 && game_flag.safe[i - 1] == game_flag.safe[i])
            game_flag.safe[i] = (game_flag.safe[i] + 10) % 20;
    }
    work = (game_flag.safe[0] + shRandI() % 19) % 20;
    for (i = 0; i < 5; i++) {
        if ((1 << i) & work) SET_GAME_FLAG(GAME_FLAG_103 + i);
    }
    for (i = 0; i < 4; i++) game_flag.rotate[i] = -1;

    
    for (i = 0; i < 4; i++) {
        game_flag.carbon      = game_flag.carbon * 16 + shRandI() % 9 + 1;
        game_flag.guruguru[i] = shRandI() % 9;
        game_flag.cylinder[i] = 
            (game_flag.guruguru[i] + 1 + (shRandI() % 8)) % 9;
    }

    if (playing.riddle_level < SH2_RIDDLE_LEVEL_EASY) {
        
        if (game_flag.guruguru[0] == game_flag.guruguru[1]) {
            game_flag.guruguru[1]++;
            if (game_flag.guruguru[1] == 9) game_flag.guruguru[1] = 0;
        }
        game_flag.guruguru[2] = game_flag.guruguru[0];
        game_flag.guruguru[3] = game_flag.guruguru[1];
    }

    game_flag.runaway[0] = shRandI() % 9;
    game_flag.runaway[1] = (work = shRandI() % 8);
    if (work >= game_flag.runaway[0]) game_flag.runaway[1]++;
    game_flag.runaway[2] = (work = shRandI() % 7);
    if (work >= game_flag.runaway[0]) game_flag.runaway[2]++;
    if (work >= game_flag.runaway[1]) game_flag.runaway[2]++;
    game_flag.runaway[3] = 0;

    
    for (i = 0; i < HANGING_MAN_COUNT; i++) shuffle[i] = i;
    for (i = 0; i < HANGING_MAN_COUNT; i++) {
        work = shRandI() % (HANGING_MAN_COUNT - i);
        game_flag.hanging = game_flag.hanging * HANGING_MAN_COUNT + shuffle[i + work];
        shuffle[i + work] = shuffle[i];
    }

    
    work = shRandI() % 3 + 1;
    if (work & 1) {
        SET_GAME_FLAG(GAME_FLAG_319);
        SET_GAME_FLAG(GAME_FLAG_323);
    }
    if (work & 2) {
        SET_GAME_FLAG(GAME_FLAG_320);
        SET_GAME_FLAG(GAME_FLAG_324);
    }
    work = shRandI() % 3 + 1;
    if (work & 1) {
        SET_GAME_FLAG(GAME_FLAG_317);
        SET_GAME_FLAG(GAME_FLAG_321);
    }
    if (work & 2) {
        SET_GAME_FLAG(GAME_FLAG_318);
        SET_GAME_FLAG(GAME_FLAG_322);
    }

    
    
    work = shRandI() % 19;
    for (i = 0; i < 5; i++)
        if (work & (1 << i)) SET_GAME_FLAG(GAME_FLAG_406 + i);


    
    if (playing.riddle_level == SH2_RIDDLE_LEVEL_EASY)
        SET_GAME_FLAG(GAME_FLAG_13);




    
    
    if (!(shRandI() & 3)) SET_GAME_FLAG(GAME_FLAG_543);
}

#line 353
void EventProgInit(void) {
    ev_s_step = ev_p_step = ev_e_step = ev_m_step = 0;
    ev_active = -1;
    ev_cancel = 0;
    sbt_msg_no = 0;
    radio.se_call = 0;
    radio.event = 0;
}

#line 367
void EventMain(void) {



    
    
    
    
    
    
    item.ampoule_efficacy = float_max(0.0f, item.ampoule_efficacy - shGetDT());
    
    
    
    if (BgIsOut(0)) ConnectCharaWorkAdminOut(1);


    Sh2sys.main_status &= ~(1 << 6);
    Sh2sys.main_status &= ~(1 << 7);
    demo_number = 0;
    
    if (ev_m_step == 0) {
        if (!PlayerEventJamesDeadly() && !PlayerEventMariaDeadly()) {
            
            if (PlayerEventButtonCheck(1)) {
                sh2sys_set_2(6);
                sh2gfw_Set_CaptureNowFB();
                ScreenEffectFadeStart(1, 1.0f);
            } else if (PlayerEventButtonCheck(3)) {
                if (!sh2gfw_Get_NightOrDay() || LightSpotOnOffCheck() || sh2gfw_Check_CharaDarkOrBright(sh2jms.player)) {
                    
                    
                    sh2sys_set_2(5);
                    sh2sys_set_3(0);
                    ScreenEffectFadeStart(1, 1.0f);
                } else {
                    EV_MAIN_STEP(10);
                    EventMainStandard(0);
                }
            } else {

                
                if (PlayerEventButtonCheck(2)) {
                    item.light_switch ^= 1;
                    LightSpotOnOffSet();
                }
                
                
                EventMainStandard(1);
            }
        }
    } else {
        
        EventMainStandard(0);
    }
    
    ev_cancel = 0;
    
    
    sh2shd_reset_shadow_off_work();
    if (stage->alltime_func) stage->alltime_func();
    
    
    
    
    
    
    
    
    
    
    
    
    
    if (PlayerEventDeadAnimeFinish()) {
        sh2sys_set_2(12);
        ScreenEffectFadeStart(1, 1.0f);
    }
    if (Sh2sys.step[SH2SYS_PLAYABLE_MAIN] != 4) {
        fontClear();
        shSdCall(1012, 0, 0, 0);
    }
}

#line 459
static void EventMainStandard(int ev_act_on) {
    Event_List* el;
    int st;
    int use_item;
    int ret;

    
    
    
    
    
    while (true) {
        if (ev_m_step == 0) {
            
            
            use_item = ItemCombinationUseCheck(item.event_use[0], item.event_use[1], item.event_use[2]);
            
            item.event_use[0] = item.event_use[1] = item.event_use[2] = 0;


            
            if (ev_cancel)
                return;       

            ev_active = (ret = use_item ? EventCheck(0, use_item, 0) : EventCheck(ev_act_on, 0, 0));



            if (ret == -1)
                return;
            if (ret < 1024) {
                el = &stage->ev_list[ret];
                st = EventListElement(el, 13);
                switch (st) {
                    case 1:
                    case 2:  
                        EV_MAIN_STEP(1); break;
                    case 3: 
                        EV_MAIN_STEP(2); break;
                    case 4:
                        EV_MAIN_STEP(5); break;
                    case 5:
                        EV_MAIN_STEP(3); break;
                    case 6:
                        EV_MAIN_STEP(6); break;
                    case 7:
                    case 8:
                    case 9:
                        EV_MAIN_STEP(7); break;
                    case 10:
                        EV_MAIN_STEP(9); break;
                }
            } else {
                EV_MAIN_STEP(8);
            }
        }

        switch (ev_m_step) {
            case 0:          ret = EventExecFlag();      break;
            case 1:          ret = EventExecMessage();   break;
            
            case 2:          ret = EventExecProgram();   break;
            case 3:          ret = EventExecDoor();      break;
            case 5:          ret = EventExecItem();      break;
            
            case 6:          ret = EventExecMove();      break;
            case 7:          ret = EventExecSave();      break;
            case 8:  case 9: ret = EventExecChizuFail(); break;
            case 10: default:
                ASSERT_ON_LINE(0, 528);
        }

        if (ret == 0) return;
        EV_MAIN_STEP(0);
        ev_act_on = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/event", EventCheck);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventCheckLook);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventCheckLookPoint);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventCheckLookLine);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventCheckIn);

static int EventListElement(Event_List* el /* r2 */, int en /* r2 */) {
    switch (en) {
        case 1:
            return (el->flag >> 0x1F) & 1;
        case 2:
            return (el->flag >> 0x1E) & 1;
        case 3:
            return (el->flag >> 0x10) & 0x3FFF;
        case 4:
            return (el->flag >> 0xF) & 1;
        case 5:
            return (el->flag >> 0xE) & 1;
        case 6:
            return el->flag & 0x3FFF;
        case 7:
            return (el->cond >> 0x1C) & 0xF;
        case 8:
            return (el->cond >> 0x10) & 0xFFF;
        case 9:
            return (el->cond >> 0xC) & 0xF;
        case 10:
            return (el->cond >> 4) & 0xFF;
        case 11:
            return (el->cond >> 3) & 1;
        case 12:
            return (el->cond >> 2) & 1;
        case 13:
            return (el->rslt0 >> 0x1C) & 0xF;
        case 14:
            return (el->rslt0 >> 0x10) & 0xFFF;
        case 15:
            return (el->rslt0 >> 0xC) & 0xF;
        case 16:
            return (el->rslt0 >> 5) & 0x7F;
        case 17:
            return (el->rslt0 >> 4) & 1;
        case 18:
            return (el->rslt1 >> 0x16) & 0x3F;
        case 19:
            return (el->rslt1 >> 0xE) & 0x7F;
        case 20:
            return (el->rslt1 >> 0xE) & 0xFF;
        case 21:
            return (el->rslt1 >> 0xE) & 0xFF;
        case 22:
            return el->rslt1 & 0x3FFF;
        default:
            return 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/event", CharToFloat2);

float CharToFloat4(char* cp) {
    char c_work[4];

    c_work[0] = cp[0];
    c_work[1] = cp[1];
    c_work[2] = cp[2];
    c_work[3] = cp[3];
    
    return *(float*)c_work;
}

static int ItemListElement(Item_List* il /* r2 */, int en /* r2 */) {
    switch (en) {
        case 0:
            return (il->st >> 0x1D) & 7;
        case 1:
            return (il->st >> 0x1A) & 7;
        case 2:
            return (il->st >> 0x14) & 0x1F;
        case 3:
            return il->st & 0x3FFF;
        default:
            return 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/event", ItemCheckLookPoint);

static void EventPositionSet(float* pos_v /* r17 */, char* pos_p /* r16 */, int pos_t /* r18 */) {
    pos_v[0] = CharToFloat4(&pos_p[0]);
    pos_v[1] = CharToFloat2(&pos_p[4]);
    pos_v[2] = CharToFloat4(&pos_p[6]);
    switch (pos_t) {
        case 1:
            pos_v[0] += (CharToFloat2(&pos_p[0xA]) / 2.0f);
            break;
        case 2:
            pos_v[0] -= (CharToFloat2(&pos_p[0xA]) / 2.0f);
            break;
        case 3:
            pos_v[2] -= (CharToFloat2(&pos_p[0xA]) / 2.0f);
            break;
        case 4:
            pos_v[2] += (CharToFloat2(&pos_p[0xA]) / 2.0f);
            break;
        case 5:
            pos_v[0] += (CharToFloat2(&pos_p[0xA]) / 2.0f);
            pos_v[2] += (CharToFloat2(&pos_p[0xC]) / 2.0f);
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/event", EventResultMovePosition);

void EventCancel(void) {
    ev_cancel = 1;
}

static void EventExecSubFlagSet(Event_List* el) {
    int flg;

    flg = EventListElement(el, 3);
    if (flg == 0) return;
    if (EventListElement(el, 2) != 0) {
        if (EventListElement(el, 1) != 0) UNSET_GAME_FLAG(flg);            
        else SET_GAME_FLAG(flg);
    }

    flg = EventListElement(el, 6);
    if (flg == 0) return;
    if (EventListElement(el, 5) == 0) return;
    if (EventListElement(el, 4) != 0) UNSET_GAME_FLAG(flg);
    else SET_GAME_FLAG(flg);
}

static int EventExecFlag(void) {    
    Event_List* el; // r2   
    int st; // r6
    int fl; // r2

    el = stage->ev_list + ev_active;
    st = EventListElement(el, 0xD);
    fl = EventListElement(el, 0x16);
    if (st == 1) {
        SET_GAME_FLAG(fl);
    } else {
        UNSET_GAME_FLAG(fl);
    }
    EventExecSubFlagSet(el);
    return 1;
}

static int EventExecMessage(void) {
    Event_List* el; // r16
    int msg; // r2   
    int flg; // r2
    
    if (ev_e_step == 0) {
        el = stage->ev_list + ev_active;
        msg = EventListElement(el, 0x14);
        fontMessageNum(msg_buffer, msg);
        flg = EventListElement(el, 0x16);
        if (flg != 0) {
            game_flag.flag[flg >> 5] |= 1 << (flg & 0x1F);
        }
        EventExecSubFlagSet(el);
        SCNowPlayableEventSwitch(sh2jms.player, 1);
        ev_e_step = 2;
        ev_p_step = 0;
        ev_s_step = 0;
    }
    if (fontGetStatus() == -2 || ev_cancel != 0) {
        fontClear();
        SCNowPlayableEventSwitch(sh2jms.player, 0);
        return 1;
    }
    return 0;
}

static int EventExecProgram(void) {
    Event_List* el; // r16
    int flg; // r2
    int prog; // r2

    el = stage->ev_list + ev_active;
    if (ev_e_step == 0) {
        EventExecSubFlagSet(el);
        ev_prog_flag_set = 1;
        ev_e_step = 2;
        ev_p_step = 0;
        ev_s_step = 0;
    }
    prog = EventListElement(el, 0x13);
    if (stage->ev_prog[prog]() != 0) {
        if (ev_prog_flag_set != 0) {
            flg = EventListElement(el, 0x16);
            if (flg != 0) {
                SET_GAME_FLAG(flg);
            }
        }
        return 1;
    }
    return 0;
}

static int EventExecDoor(void) {
    Event_List* el; // r16
    float pos_v[4]; // r29+0x40    
    char* pos_p; // r6
    int pos_t; // r2
    int st; // r17
    int msg; // r2
    int se; // r18
    int fl; // r2
    
    if (!ev_e_step) {
        el = stage->ev_list + ev_active;
        st = EventListElement(el, 0xD);
        se = EventListElement(el, 0x12);
        pos_p = (char *)(stage->ev_pos + EventListElement(el, 8));
        pos_t = EventListElement(el, 9);
        EventPositionSet(pos_v, pos_p, pos_t);
        pos_v[1] += -500.0f;
        
        if (st == 7) {
            msg = EventListElement(el, 0x14);
            if (msg == 0xFF) {
                fontMessageNum(msg_station, 5);
            } else {
                fontMessageNum(msg_buffer, msg);
            }
            SeCallPos(door_se[se].unlock, 1.0f, pos_v, 0);
        } else if (st == 9) {
            msg = EventListElement(el, 0x14);
            if (msg == 0xFF) {
                fontMessageNum(msg_station, 6);
            } else if (msg == 0xFE) {
                fontMessageNum(msg_station, 7);
            } else {
                fontMessageNum(msg_buffer, msg);
            }
            SeCallPos(door_se[se].jam, 1.0f, pos_v, 0);
        } else {
            fontMessageNum(msg_station, 4);
            SeCallPos(door_se[se].lock, 1.0f, pos_v, 0);
        }
        fl = EventListElement(el, 0x16);
        if (fl != 0) {
            SET_GAME_FLAG(fl);
        }
        EventExecSubFlagSet(el);
        SCNowPlayableEventSwitch(sh2jms.player, 1);
        ev_e_step = 2;
        ev_p_step = 0;
        ev_s_step = 0;
    }

    if (fontGetStatus() == -2 || ev_cancel) {
        fontClear();
        SCNowPlayableEventSwitch(sh2jms.player, 0);
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/event", EventExecItem);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventExecMove);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventExecSave);

int LightSpotOnOffCheck(void) {
    if (!GET_BIT(item.flag[0], 15)) {
        return 0;
    }
    if (!item.light_switch) {
        return 0;
    }
    if (GET_GAME_FLAG(GAME_FLAG_272)) {
        return 0;
    }
    return 1;
}

void LightSpotOnOffSet(void) {
    if ((sh2gfw_Get_NightOrDay() == 0) || !(GET_BIT(item.flag[0], 15))) {
        return;
    }
    if (LightSpotOnOffCheck()) {
        sh2gfw_On_JmsSPOT();
        return;
    }
    sh2gfw_Off_JmsSPOT();
}

static int EventExecChizuFail(void) {
    if (ev_e_step == 0) {
        fontMessageNum(msg_station, 2);
        SCNowPlayableEventSwitch(sh2jms.player, 1);
        ev_e_step = 2;
        ev_p_step = 0;
        ev_s_step = 0;
    }
    if ((fontGetStatus() == -2) || (ev_cancel != 0)) {
        fontClear();
        SCNowPlayableEventSwitch(sh2jms.player, 0);
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/event", EventProgressCheck);

int EventItemConditionCheck(int level, int flag) {
    switch (playing.battle_level) {
        case 1:
            if (level == 2 || level == 3 || level == 6) return 0;
            break;            
        case 2:
            if (level == 1 || level == 3 || level == 5) return 0;
            break;            
        case 3: 
            if (level == 1 || level == 2 || level == 4) return 0;
            break;
    }

    
    switch (flag) {
        case 1:
            if (!GET_GAME_FLAG(GAME_FLAG_251)) return 0;
            break;            
        case 2:
            if (!GET_GAME_FLAG(GAME_FLAG_108)) return 0;
            break;            
        case 3:
            if (!GET_GAME_FLAG(GAME_FLAG_240)) return 0;
            break;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Event/event", RadioNoise);

INCLUDE_RODATA("asm/nonmatchings/Event/event", @2408);

INCLUDE_RODATA("asm/nonmatchings/Event/event", @2409);

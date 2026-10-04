#include "sh2_common.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/sh2sys.h"

#include "SH2_common/sh2dt.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/sh2sys.h"

#include "connect.h"
#include "vec.h"

#include "Chacter/m3_sc.h"
#include "Chacter/sh2_battle_list.h"

#include "Chacter_Draw/sh2_JmsSpot_Man.h"

#include "Font/font.h"
#include "sound/sh_sound.h"
#include "GFW/sh2gfw_LightSet.h"
#include "Effect/screen_effect.h"

#include "Event/event.h"
#include "Event/demoview.h"
#include "Event/stg_overlay.h"

typedef struct /* @anon3 */ {
    // total size: 0x24
    float pos_x; // offset 0x0, size 0x4
    float pos_y; // offset 0x4, size 0x4
    float pos_z; // offset 0x8, size 0x4
    float rot_y; // offset 0xC, size 0x4
    float view_x; // offset 0x10, size 0x4
    float view_z; // offset 0x14, size 0x4
    float rear_x; // offset 0x18, size 0x4
    float rear_z; // offset 0x1C, size 0x4
    float pad; // offset 0x20, size 0x4
} Jms;

typedef struct {
    short item; // offset 0x0, size 0x2
    short msg; // offset 0x2, size 0x2
    int chara_id; // offset 0x4, size 0x4
} EventExecItemData;

static void EventMainStandard(int ev_act_on);
static int EventCheckLook(Event_List* el, Jms jms);
static int EventListElement(Event_List* el, int en);
static int EventCheckIn(Event_List* el);
static int ItemCheckLookPoint(Item_List* il);
static int ItemListElement(Item_List* il, int en);
static int EventCheckLookPoint(float x, float z, Jms jms);
static int EventCheckLookLine(float x0, float z0, float x1, float z1, Jms jms);
static void EventPositionSet(float* pos_v, s_char* pos_p, int pos_t);
static void EventResultMovePosition(int ev_no);
static void EventExecSubFlagSet(Event_List* el);
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

INCLUDE_RODATA("asm/nonmatchings/Event/event", @1420_0x00390EE0);

INCLUDE_RODATA("asm/nonmatchings/Event/event", @1583_0x00390F50);

INCLUDE_RODATA("asm/nonmatchings/Event/event", @1584);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventCheck);

#line 759
static int EventCheckLook(Event_List* el, Jms jms) {
    float p[7][2]; // r29+0xB0
    s_char* pos_p; // r16
    float f_work; // r29+0xF0
    int pos_type; // r17
    int work; // r18
    int i; // r19

    
    int element = EventListElement(el, 8); // @note not in dwarf
    pos_p = (s_char*) &stage->ev_pos[element];
    
    
    f_work = CharToFloat2(pos_p + 4);
    if (f_work < 45000.0f           && 
        f_work > 100.0f + jms.pos_y || f_work < -500.0f + jms.pos_y) {
        return 0;
    }
    pos_type = EventListElement(el, 9);
    
    if (pos_type == 0) {
        return EventCheckLookPoint(CharToFloat4(pos_p), CharToFloat4(pos_p + 6), jms);
    }
    
    
    p[0][0] = CharToFloat4(pos_p);
    p[0][1] = CharToFloat4(pos_p + 6);
    
    switch (pos_type) {
        case 1:
        case 2:
        case 3:
        case 4:
            work = 2;
            p[1][0] = p[0][0];
            p[1][1] = p[0][1];
            switch (pos_type) {
                case 1:
                    p[1][0] += CharToFloat2(pos_p + 10);
                    break;
                case 2:
                    p[1][0] -= CharToFloat2(pos_p + 10);
                    break;
                case 3:
                    p[1][1] -= CharToFloat2(pos_p + 10);
                    break;
                case 4:
                    p[1][1] += CharToFloat2(pos_p + 10);
                    break;
            }
            break;
        
        default:
            work = pos_type - 3;
            for (i = 1; i < work; i++) {
                p[i][0] = p[0][0] + CharToFloat2(pos_p + i * 4 + 6);
                p[i][1] = p[0][1] + CharToFloat2(pos_p + i * 4 + 8);
            }
            break;
    }
    for (i = 0; i < work - 1; i++) {
        if (EventCheckLookLine(p[i + 0][0], p[i + 0][1], p[i + 1][0], p[i + 1][1], jms))
            return true;
    }
    return false;
}

static inline float float_square(float x) {
    return x *= x;
}

static inline float float_add(float a, float b) {
    return b + a;
}

#line 829
static int EventCheckLookPoint(float x, float z, Jms jms) {
    /* static */ float pos_x;
    /* static */ float pos_z;
    float ang; // r29+0x40
    
    pos_x = x - jms.pos_x;
    pos_z = z - jms.pos_z;
    
    
    if (float_abs(pos_x) > 400.0f || float_abs(pos_z) > 400.0f)
        return false;

    
    if (float_add(float_square(pos_z), float_square(pos_x)) > 160000.0f)
        return false;

    
    ang = shAngleRegulate(jms.rot_y - shAtan2(z - jms.rear_z, x - jms.rear_x));
    
    if (float_abs(ang) > TO_RAD(30)) return false;
    
    return true;
}

INCLUDE_ASM("asm/nonmatchings/Event/event", EventCheckLookLine); /* maybe handwritten? */

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
            return (el->flag >> 0x0F) & 1;
        case 5:
            return (el->flag >> 0x0E) & 1;
        case 6:
            return el->flag & 0x3FFF;
        case 7:
            return (el->cond >> 0x1C) & 0xF;
        case 8:
            return (el->cond >> 0x10) & 0xFFF;
        case 9:
            return (el->cond >> 0x0C) & 0xF;
        case 10:
            return (el->cond >> 0x04) & 0xFF;
        case 11:
            return (el->cond >> 0x03) & 1;
        case 12:
            return (el->cond >> 0x02) & 1;
        case 13:
            return (el->rslt0 >> 0x1C) & 0xF;
        case 14:
            return (el->rslt0 >> 0x10) & 0xFFF;
        case 15:
            return (el->rslt0 >> 0x0C) & 0xF;
        case 16:
            return (el->rslt0 >> 0x05) & 0x7F;
        case 17:
            return (el->rslt0 >> 0x04) & 1;
        case 18:
            return (el->rslt1 >> 0x16) & 0x3F;
        case 19:
            return (el->rslt1 >> 0x0E) & 0x7F;
        case 20:
            return (el->rslt1 >> 0x0E) & 0xFF;
        case 21:
            return (el->rslt1 >> 0x0E) & 0xFF;
        case 22:
            return el->rslt1 & 0x3FFF;
        default:
            return 0;
    }
}

/**
 * @see DdsReadFloat2
 */
float CharToFloat2(char* cp /* r2 */) {    
    int coe; // r4    
    int sig; // r2
    int exp; // r2    
    int work; // r29+0xC

    work = 0;
    ((s_char*)&work)[0] = cp[0];
    ((s_char*)&work)[1] = cp[1];

    sig = (work >> 15) & 0b1;
    exp = (work >> 10) & 0b11111;
    coe = work & 0b1111111111;
    exp += 0x70;
    coe <<= 13;
    exp <<= 23;
    
    work = (sig << 31) | exp | coe;
    
    return *(float*)&work;
}


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
            return (il->st >> 0x1D) & 0x07;
        case 1:
            return (il->st >> 0x1A) & 0x07;
        case 2:
            return (il->st >> 0x14) & 0x1F;
        case 3:
            return  il->st & 0x3FFF;
        default:
            return 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/event", ItemCheckLookPoint);

static void EventPositionSet(float* pos_v /* r17 */, s_char* pos_p /* r16 */, int pos_t /* r18 */) {
    pos_v[0] = CharToFloat4(&pos_p[0]);
    pos_v[1] = CharToFloat2(&pos_p[4]);
    pos_v[2] = CharToFloat4(&pos_p[6]);
    switch (pos_t) {
        case 1:
            pos_v[0] += (CharToFloat2(pos_p + 10) / 2.0f);
            break;
        case 2:
            pos_v[0] -= (CharToFloat2(pos_p + 10) / 2.0f);
            break;
        case 3:
            pos_v[2] -= (CharToFloat2(pos_p + 10) / 2.0f);
            break;
        case 4:
            pos_v[2] += (CharToFloat2(pos_p + 10) / 2.0f);
            break;
        case 5:
            pos_v[0] += (CharToFloat2(pos_p + 10) / 2.0f);
            pos_v[2] += (CharToFloat2(pos_p + 12) / 2.0f);
            break;
    }
}

#line 1352
static void EventResultMovePosition(int ev_no /* r2 */) {
    sceVu0FVECTOR mv_pos; // r29+0x40
    Event_List* el; // r2
    s_char* pos; // r16
    int pos_type; // r17
    float f_work; // r29+0x50
    float rot; // r20

    el = &stage->ev_list[ev_no];
    pos = (s_char*) &stage->ev_pos[EventListElement(el, 14)];
    pos_type = EventListElement(el, 15);
    vec_zero_xyz(mv_pos);
    mv_pos[0] = CharToFloat4(pos);
    mv_pos[1] = CharToFloat2(pos + 4);
    mv_pos[2] = CharToFloat4(pos + 6);
    rot = sh2jms.player->rot.y;
    
    switch (pos_type) {
        case 0:
            break;
        case 1:
            mv_pos[0] += CharToFloat2(pos + 10) / 2.0f;
            mv_pos[2] += 250.0f;
            rot = 0.0f;
            break;
        case 2:
            mv_pos[0] -= CharToFloat2(pos + 10) / 2.0f;
            mv_pos[2] -= 250.0f;
            rot = PI;
            break;
        case 3:
            mv_pos[0] += 250.0f;
            mv_pos[2] -= CharToFloat2(pos + 10) / 2.0f;
            rot = QUARTER_TURN;
            break;
        case 4:
            mv_pos[0] -= 250.0f;
            mv_pos[2] += CharToFloat2(pos + 10) / 2.0f;
            rot = -QUARTER_TURN;
            break;
        case 5:
            mv_pos[0] += CharToFloat2(pos + 10) / 2.0f;
            mv_pos[2] += CharToFloat2(pos + 12) / 2.0f;
            rot = shAtan2(CharToFloat2(pos + 12), CharToFloat2(pos + 10)) + -QUARTER_TURN;
            mv_pos[0] += 250.0f * shSinF(rot);
            mv_pos[2] += 250.0f * shCosF(rot);
            break;
    }

    connect_pos[0] = mv_pos[0];
    connect_pos[1] = mv_pos[1];
    connect_pos[2] = mv_pos[2];
    connect_pos[3] = shAngleRegulate(rot);
}

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
    st = EventListElement(el, 13);
    fl = EventListElement(el, 22);
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
        msg = EventListElement(el, 20);
        fontMessageNum(msg_buffer, msg);
        flg = EventListElement(el, 22);
        if (flg) {
            SET_GAME_FLAG(flg);
        }
        EventExecSubFlagSet(el);
        SCNowPlayableEventSwitch(sh2jms.player, 1);
        EV_EXEC_STEP(2);
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

#ifdef HOLY_CANDLE
static int EventExecDoor(void) {
    Event_List* el; // r16
    sceVu0FVECTOR pos_v; // r29+0x40    
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
#else
INCLUDE_ASM("asm/nonmatchings/Event/event", EventExecDoor);
#endif

#define BEND_ANIMATION_HEIGHT_THRESHOLD 100.0f

#define EXEC_ITEM_START  0
#define EXEC_ITEM_GET    1
#define EXEC_ITEM_DELETE 2
#define EXEC_ITEM_PICKUP 4
#define EXEC_ITEM_STAND  5
#define EXEC_ITEM_END    6

#line 1616
static int EventExecItem(void) {
    UNMIGRATED(/* static */ EventExecItemData eei_data[7], {
        {
            /* .msg = */      0,
            /* .chara_id = */ 0,
            /* .item = */     0,
        },
        {
            /* .msg = */      9,
            /* .chara_id = */ ITEM_X_HANDBUL_CHARA_KIND,
            /* .item = */     5,
        },
        {
            /* .msg = */      10,
            /* .chara_id = */ ITEM_X_SHOTBUL_CHARA_KIND,
            /* .item = */     7,
        },
        {
            /* .msg = */      11,
            /* .chara_id = */ ITEM_X_RIFLEBUL_CHARA_KIND,
            /* .item = */     9,
        },
        {
            /* .msg = */      12,
            /* .chara_id = */ ITEM_X_DRINK_CHARA_KIND,
            /* .item = */     1,
        },
        {
            /* .msg = */      13,
            /* .chara_id = */ ITEM_X_FIRSTAID_CHARA_KIND,
            /* .item = */     2,
        },
        {
            /* .msg = */      14,
            /* .chara_id = */ ITEM_X_AMPLE_CHARA_KIND,
            /* .item = */     3
        }
    }); // @ 0x002B97E0
    Item_List* il; // r16
    int kind; // r7

    switch (ev_e_step) {
        case EXEC_ITEM_START:
            il = &stage->gi_list[ev_active - 1024];
            SCNowPlayableEventSwitch(sh2jms.player, true);

            /* if james has to bend over to pick up the item, james does just that */
            if (sh2jms.player->pos.y - CharToFloat2((s_char*) &il->pos_y) < BEND_ANIMATION_HEIGHT_THRESHOLD) {
                PlayerEventAnimeSet(20001);
                EV_EXEC_STEP(EXEC_ITEM_PICKUP);
            } else {
                PlayerEventAnimeSet(101);
                EV_EXEC_STEP(EXEC_ITEM_GET);
            }
            break;

        case EXEC_ITEM_PICKUP:
            if (ev_cancel) {
                EV_EXEC_STEP(EXEC_ITEM_END);
            } else if (PlayerEventAnimeSuccessFrame()) {
                shCharacterAnimePause(sh2jms.player);
                EV_EXEC_STEP(EXEC_ITEM_GET);
            }
            break;

        case EXEC_ITEM_GET:
            il = &stage->gi_list[ev_active - 1024];
            kind = ItemListElement(il, 0);
            SET_GAME_FLAG(ItemListElement(il, 3) + 1);
            ItemGet(eei_data[kind].item);
            fontMessageNum(msg_station, eei_data[kind].msg);
            EV_EXEC_STEP(EXEC_ITEM_DELETE);
            break;

        case EXEC_ITEM_DELETE:
            il = &stage->gi_list[ev_active - 1024];
            if (fontGetStatus() == -2 || ev_cancel) {
                fontClear();
                SeCall(11041, 1.0f, 0);
                shCharacter_Manage_Delete(NULL, eei_data[ItemListElement(il, 0)].chara_id, ItemListElement(il, 3)); // @bug: prototype not included
                EV_EXEC_STEP(6);
                if (sh2jms.player->pos.y - CharToFloat2((s_char*) &il->pos_y) < BEND_ANIMATION_HEIGHT_THRESHOLD) {
                    shCharacterAnimeRestart(sh2jms.player);
                    EV_EXEC_STEP(EXEC_ITEM_STAND);
                }
            }
            break;

        case EXEC_ITEM_STAND:
            if (shCharacterAnimeIsEnd(sh2jms.player) || ev_cancel) {
                EV_EXEC_STEP(EXEC_ITEM_END);
            }
            break;

        case EXEC_ITEM_END:
            SCNowPlayableEventSwitch(sh2jms.player, false);
            return true;
    }

    return false;
}

#ifdef HOLY_CANDLE
#line 1704
static int EventExecMove(void) {
    UNMIGRATED(/* static */ short reset_stage_connect[12][2], {
        { Stg_forest,     Stg_town_east      },
        { Stg_town_east,  Stg_apart_out      },
        { Stg_town_west,  Stg_apart_stair    },
        { Stg_town_west,  Stg_hospital_1f_f  },
        { Stg_town_west,  Stg_hospital_1fe_b },
        { Stg_town_west,  Stg_society        },
        { Stg_delusion_3, Stg_prison_n       },
    });
    
    extern /* static */ short close_se; // @ 0x01126340
    extern /* static */ sceVu0FVECTOR pos_v; // @ 0x01126350
    
    Event_List* el; // r16

    s_char* pos_p; // r6

    int pos_t; // r2
    int se; // r2
    int flg; // r2
    int stg; // r2

    int i; // r4

    switch (ev_e_step) {
        case 0:
            el = &stage->ev_list[ev_active];
            EventExecSubFlagSet(el);
            flg = EventListElement(el, 22);
            if (flg && ev_m_step != 3) SET_GAME_FLAG(flg);
            EventResultMovePosition(ev_active);
            pos_p = (s_char*) stage->ev_pos + EventListElement(el, 8);
            pos_t = EventListElement(el, 9);
            
            
            EventPositionSet(pos_v, pos_p, pos_t);
            pos_v[1] += -500.0f;
            pos_t = EventListElement(el, 18);
            SeCallPos(door_se[pos_t].open, 1.0f, pos_v, 0);
            close_se = door_se[pos_t].close;
            pos_p = (s_char*) stage->ev_pos + EventListElement(el, 14);
            pos_t = EventListElement(el, 15);
            EventPositionSet(pos_v, pos_p, pos_t);
            pos_v[1] += -500.0f;
            SET_BIT(Sh2sys.main_status, 1);
            sh2sys_set_2(1);
            stg = EventListElement(el, 16);
            if (stg) {
                for (i = 0; reset_stage_connect[i][0] != 0; i++) {
                    if ((playing.stage == reset_stage_connect[i][0]              && 
                         stg == reset_stage_connect[i][1])                       || 
                        (playing.stage == reset_stage_connect[i][1]              && 
                         stg == reset_stage_connect[i][0]))
                        SET_BIT(Sh2sys.main_status, 3);
                }
                playing.stage = EventListElement(el, 16);
                sh2sys_set_3(0);
            } else sh2sys_set_3(3);
            if (EventListElement(el, 17)) SET_BIT(Sh2sys.main_status, 2);
            else UNSET_BIT(Sh2sys.main_status, 2);
            SCNowPlayableEventSwitch(sh2jms.player, true);
            EV_EXEC_STEP(3);
            ScreenEffectFadeStart(1, 0.0f);
            break;
        case 3:
            SeCallPos(close_se, 1.0f, pos_v, 0);
            SCNowPlayableEventSwitch(sh2jms.player, false);
            ScreenEffectFadeStart(4, 0.0f);
            if (ev_m_step == 3) {
                EV_MAIN_STEP(4);
                EventExecProgram();
            } else return true;
    }
    
    return false;
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/event", EventExecMove);
#endif

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
    if (!sh2gfw_Get_NightOrDay() || !GET_BIT(item.flag[0], 15)) {
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

#line 1881
int EventProgressCheck(void) {
    int room; // r2

    
    ASSERT_ON_LINE(stage, 1885);
    
    room = RoomNameJms();

    
    if (stage->glb_crd == 6 && !GET_GAME_FLAG(GAME_FLAG_32)) {
        return 1;
    }
    if (stage->glb_crd == 1 && !GET_GAME_FLAG(GAME_FLAG_36) && sh2jms.player->pos.x > -20000.0f && sh2jms.player->pos.z > -20000.0f) {
        return 2;
    }
    if (stage->glb_crd == 2 && !GET_GAME_FLAG(GAME_FLAG_43)) {
        return 3;
    } 
    if (GET_GAME_FLAG(GAME_FLAG_69) && !GET_GAME_FLAG(GAME_FLAG_70)) {
        return 4;
    }
    if (GET_GAME_FLAG(GAME_FLAG_69) && room == 24) {
        return 5;
    }
    if (stage->glb_crd == 3 && !GET_GAME_FLAG(GAME_FLAG_150)) {
        return 6;
    }
    if (GET_GAME_FLAG(GAME_FLAG_150) && !GET_GAME_FLAG(GAME_FLAG_152)) {
        return 7;
    }
    if (stage->glb_crd == 3 && GET_GAME_FLAG(GAME_FLAG_152) && !GET_GAME_FLAG(GAME_FLAG_157)) {
        return 8;
    }
    if (stage->glb_crd == 3 && GET_GAME_FLAG(GAME_FLAG_162) && !GET_GAME_FLAG(GAME_FLAG_163)) {
        return 9;
    }
    if (GET_GAME_FLAG(GAME_FLAG_379) && !GET_GAME_FLAG(GAME_FLAG_380)) {
        return 10;
    }

    return 0;
}

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

#include "Event/event.h"
#include "Chacter/m3_sc.h"
#include "Font/font.h"
#include "sound/sh_sound.h"
#include "GFW/sh2gfw_LightSet.h"
#include "Chacter_Draw/sh2_JmsSpot_Man.h"

static int EventListElement(Event_List* el /* r2 */, int en /* r2 */);
static int ItemListElement(Item_List* il /* r2 */, int en /* r2 */);
static void EventPositionSet(float* pos_v /* r17 */, char* pos_p /* r16 */, int pos_t /* r18 */);
static void EventExecSubFlagSet(Event_List * el /* r2 */);
static int EventExecFlag(void);
static int EventExecMessage(void);
static int EventExecProgram(void);
static int EventExecDoor(void);
static int EventExecChizuFail(void);

extern /* static */ Event_DoorSound door_se[22];

INCLUDE_ASM("asm/nonmatchings/Event/event", FlagInit);

void EventProgInit(void) {
    ev_m_step = 0;
    ev_e_step = 0;
    ev_p_step = 0;
    ev_s_step = 0;
    ev_active = -1;
    ev_cancel = 0;
    sbt_msg_no = 0;
    radio.se_call = 0;
    radio.event = 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/event", EventMain);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventMainStandard);

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

INCLUDE_ASM("asm/nonmatchings/Event/event", EventExecSubFlagSet); // https://decomp.me/scratch/uNvCi 

static int EventExecFlag(void) {    
    Event_List* el; // r2   
    int st; // r6
    int fl; // r2

    el = stage->ev_list + ev_active;
    st = EventListElement(el, 0xD);
    fl = EventListElement(el, 0x16);
    if (st == 1) {
        SET_GAME_FLAG(fl >> 5, fl & 0x1F);
        // SET_FLAG(game_flag.flag, fl); 
    } else {
        UNSET_GAME_FLAG(fl >> 5, fl & 0x1F);
        // UNSET_FLAG(game_flag.flag, fl);
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
                SET_GAME_FLAG(flg >> 5, flg & 0x1F);
                //SET_FLAG(game_flag.flag, flg);
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
            SET_GAME_FLAG(fl >> 5, fl & 0x1F);
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
    if (GET_GAME_FLAG(8, 16)) {
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

INCLUDE_ASM("asm/nonmatchings/Event/event", EventItemConditionCheck);

INCLUDE_ASM("asm/nonmatchings/Event/event", RadioNoise);

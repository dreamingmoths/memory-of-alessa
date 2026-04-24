#include "Event/event.h"
#include "Chacter/m3_sc.h"
#include "Font/font.h"

static int EventListElement(Event_List* el /* r2 */, int en /* r2 */);
static void EventExecSubFlagSet(Event_List * el /* r2 */);
static int EventExecMessage(void);

INCLUDE_ASM("asm/nonmatchings/Event/event", FlagInit);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventProgInit);

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

INCLUDE_ASM("asm/nonmatchings/Event/event", CharToFloat4);

INCLUDE_ASM("asm/nonmatchings/Event/event", ItemListElement);

INCLUDE_ASM("asm/nonmatchings/Event/event", ItemCheckLookPoint);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventPositionSet);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventResultMovePosition);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventCancel);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventExecSubFlagSet);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventExecFlag);

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

INCLUDE_ASM("asm/nonmatchings/Event/event", EventExecProgram);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventExecDoor);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventExecItem);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventExecMove);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventExecSave);

INCLUDE_ASM("asm/nonmatchings/Event/event", LightSpotOnOffCheck);

INCLUDE_ASM("asm/nonmatchings/Event/event", LightSpotOnOffSet);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventExecChizuFail);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventProgressCheck);

INCLUDE_ASM("asm/nonmatchings/Event/event", EventItemConditionCheck);

INCLUDE_ASM("asm/nonmatchings/Event/event", RadioNoise);

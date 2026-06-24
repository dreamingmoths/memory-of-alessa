#include "vc_prio.h"
#include "Event/event.h"
#include "Event/stg_name.h"

#line 36
int vcRetPrioStgEvnt(int glb_crd) {
    int prio_f;

    switch (glb_crd) {
        case 2:
            prio_f = vcRetPrioCbEvnt();
            break;
        case 9:
            prio_f = vcRetPrioApEvnt();
            break;
        case 3:
            prio_f = vcRetPrioCcEvnt();
            break;
    }

    return prio_f;
}

#line 63
int vcRetPrioCbEvnt(void) {
    int blk_no[4];

    BlockNumber(blk_no, 0, sh2jms.player->pos.x, sh2jms.player->pos.z);

    switch (blk_no[0] & 0xFFFF) {
        case 54:
            return GET_GAME_FLAG(GAME_FLAG_43);
        case 18:
            return GET_GAME_FLAG(GAME_FLAG_47);
        case 67:
            return GET_GAME_FLAG(GAME_FLAG_117);
    }

    return 0;
}

#line 86
int vcRetPrioApEvnt(void) {
    int room;

    room = RoomNameJms();

    switch (room) {
        case 23:
            return GET_GAME_FLAG(GAME_FLAG_62);
        case 27:
            return GET_GAME_FLAG(GAME_FLAG_66);
        case 31:
            return GET_GAME_FLAG(GAME_FLAG_67);
        case 24:
            return GET_GAME_FLAG(GAME_FLAG_72);
        case 30:
            return GET_GAME_FLAG(GAME_FLAG_88);
        case 21:
            return GET_GAME_FLAG(GAME_FLAG_95);
        case 33:
            return GET_GAME_FLAG(GAME_FLAG_146);
    }

    return 0;
}

#line 117
int vcRetPrioCcEvnt(void) {
    int blk_no[4];

    BlockNumber(blk_no, 0, sh2jms.player->pos.x, sh2jms.player->pos.z);

    switch (blk_no[0] & 0xFFFF) {
        case 41:
            return GET_GAME_FLAG(GAME_FLAG_168);
    }

    return 0;
}

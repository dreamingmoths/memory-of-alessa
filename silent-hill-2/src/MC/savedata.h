#ifndef SAVEDATA_H
#define SAVEDATA_H

#include "sh2_common.h"
#include "sce/eetypes.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/pad.h"
#include "Event/event.h"
#include "Event/item.h"
#include "Chacter/character.h"

// total size: 0x1A10
typedef struct SAVE_DATA {
    // Members
    u_int version; // offset 0x0, size 0x4
    u_short scene; // offset 0x4, size 0x2
    sceVu0FVECTOR jms_pos; // offset 0x10, size 0x10
    Playing_Info playing; // offset 0x20, size 0x8C
    Game_Flag game_flag; // offset 0xAC, size 0x4A0
    Item item; // offset 0x54C, size 0x34
    Character_Info chara; // offset 0x580, size 0x1430
    Pad_KeyConfig key_config; // offset 0x19B0, size 0x60
} SAVE_DATA;

// total size: 0x1FC0
typedef struct SAVE_DATA_ALL {
    // Members
    SAVE_DATA d; // offset 0x0, size 0x1A10
    s_char pad[1456]; // offset 0x1A10, size 0x5B0
} SAVE_DATA_ALL;

void SetSavePointName(u_short msg_no);
void SetSaveData(void);
void ExtGameData(void);
int CheckSaveData(void);
void SetGameEnvironment(void);

extern SAVE_DATA_ALL SaveDataAll;

#endif // SAVEDATA_H

#ifndef ITEM_SCREEN_OBJ_H
#define ITEM_SCREEN_OBJ_H

#include "common.h"
#include "Chacter/character.h"

// total size: 0x20
typedef struct shItemScreenObjectSettingData {
    // Members
    int chara_id; // offset 0x0, size 0x4
    float scale; // offset 0x4, size 0x4
    Vector4 rot; // offset 0x10, size 0x10
} shItemScreenObjectSettingData;

#endif // ITEM_SCREEN_OBJ_H

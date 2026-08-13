#ifndef M3_PLAY_EFECT_H
#define M3_PLAY_EFECT_H

#include "sh2_common.h"
#include "Chacter/character.h"

// total size: 0x8
typedef struct JamesSoundInfo {
    // Members
    float vol; // offset 0x0, size 0x4
    s_char frame; // offset 0x4, size 0x1
    s_char domain; // offset 0x5, size 0x1
} JamesSoundInfo;

void PlayerCheckEffect(void);
void PlayerCheckSound(void);
void PlayerCheckDualShock(void);
int PlayerJamesIsInSquare(float* pos0, float* pos1);

#endif // M3_PLAY_EFECT_H

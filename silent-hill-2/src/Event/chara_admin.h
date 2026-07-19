#ifndef CHARA_ADMIN_H
#define CHARA_ADMIN_H

#include "Chacter/character.h"
#include "Event/chara_data_load.h"

typedef struct CharaAdmin_RoomDistance {
    // total size: 0x4
    short rm0; // offset 0x0, size 0x2
    short rm1; // offset 0x2, size 0x2
} CharaAdmin_RoomDistance;


void ConnectCharaWorkJamesSet(void);

void ConnectCharaWorkWeapon(void);

void ConnectCharaWorkReset(void);

void ConnectCharaWorkAdminOut(int load_check);

void ConnectCharaWorkAdminIn(void);

void ConnectCharaWorkAdminClear(void);

SubCharacter* CharaWorkCreate(short kind, short id, float* pos, float* rot, u_int status);

int CharaAdminEnemyEntryCheck(Enemy_List* ep, int room);

void CharaAdminPlayableDisplay(int xxx);

SubCharacter* CharaAdminReCreate(int kind, int new_id, int old_id, float* pos, float* rot, int status);

#endif // CHARA_ADMIN_H

#ifndef CHARA_ADMIN_H
#define CHARA_ADMIN_H

#include "Chacter/character.h"
#include "Event/chara_data_load.h"

typedef struct Enemy_List {
    // total size: 0x14
    short kind; // offset 0x0, size 0x2
    short id; // offset 0x2, size 0x2
    int pos_x; // offset 0x4, size 0x4
    int pos_z; // offset 0x8, size 0x4
    short pos_y; // offset 0xC, size 0x2
    short rot_y; // offset 0xE, size 0x2
    short status; // offset 0x10, size 0x2
    u_short condition; // offset 0x12, size 0x2
} Enemy_List;

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

void CharaAdminBackLoadEnemy(CharaData_DemoList* list);


#endif // CHARA_ADMIN_H

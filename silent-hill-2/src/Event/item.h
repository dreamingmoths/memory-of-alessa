#ifndef ITEM_H
#define ITEM_H

#include "sh2_common.h"
#include "Chacter/character.h"

#define HEALTH_DRINK 1
#define FIRST_AID_KIT 2
#define AMPOULE 3

// total size: 0x34
typedef struct Item {
    // Members
    u_int flag[2]; // offset 0x0, size 0x8
    u_short number[11]; // offset 0x8, size 0x16
    u_char light_switch; // offset 0x1E, size 0x1
    u_char radio_switch; // offset 0x1F, size 0x1
    u_char radio_volume; // offset 0x20, size 0x1
    u_char equip; // offset 0x21, size 0x1
    float ampoule_efficacy; // offset 0x24, size 0x4
    u_short event_use[3]; // offset 0x28, size 0x6
    u_short short_pad; // offset 0x2E, size 0x2
    u_char last_cursor; // offset 0x30, size 0x1
} Item;

// src\SH2_common\sh_vu0.c
extern void shQzero(void*, int);

void ItemDataInit(void);
void ItemGet(int kind /* r16 */);
int ItemUse(int kind /* r2 */);
int ItemWeaponShoot(int kind /* r16 */, int use /* r2 */);
int ItemWeaponReload(int kind /* r2 */, int use /* r2 */);
int ItemMedicineUse(int kind /* r16 */);
float ItemAmpolueEfficacy(void);
int ItemEventCheck(int kind_0 /* r2 */, int kind_1 /* r2 */, int kind_2 /* r2 */);
int ItemCombinationUseCheck(int kind_0 /* r2 */, int kind_1 /* r2 */, int kind_2 /* r2 */);
void ItemPutForShelf(void);

extern struct Item item;
extern struct shPlayerWork sh2jms;
extern int cmb_check_1042[11][4];

#endif

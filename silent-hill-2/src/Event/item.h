#ifndef ITEM_H
#define ITEM_H

#include "sh2_common.h"
#include "Chacter/character.h"

#define GET_ITEM_FLAG(index) ((item.flag[(index) >> 5] >> ((index) & 0x1F)) & 1)
#define SET_ITEM_FLAG(index) ((item.flag[(index) >> 5] |= (1 << ((index) & 0x1F))))
#define UNSET_ITEM_FLAG(index) ((item.flag[(index) >> 5] &= ~(1 << ((index) & 0x1F))))

#define HEALTH_DRINK     1
#define FIRST_AID_KIT    2
#define AMPOULE          3
#define SH2_ITEM_04      4
#define SH2_ITEM_05      5
#define SH2_ITEM_06      6
#define SH2_ITEM_07      7
#define SH2_ITEM_08      8
#define SH2_ITEM_09      9
#define SH2_ITEM_10      10
#define WOODEN_PLANK     11
#define SH2_ITEM_12      12
#define SH2_ITEM_13      13
#define CHAINSAW         14
#define SH2_ITEM_15      15
#define SH2_ITEM_RADIO   16
#define SH2_ITEM_17      17
#define SH2_ITEM_18      18
#define SH2_ITEM_19      19
#define SH2_ITEM_20      20
#define SH2_ITEM_21      21
#define SH2_ITEM_22      22
#define APART_GATE_KEY   23
#define APART_202_KEY    24
#define SH2_ITEM_25      25
#define SH2_ITEM_27      27
#define SH2_ITEM_28      28
#define SH2_ITEM_29      29
#define SH2_ITEM_30      30
#define SH2_ITEM_32      32
#define SH2_ITEM_33      33
#define SH2_ITEM_34      34
#define SH2_ITEM_35      35
#define SH2_ITEM_38      38
#define SH2_ITEM_39      39
#define SH2_ITEM_40      40
#define SH2_ITEM_43      43
#define SH2_ITEM_44      44
#define SH2_ITEM_45      45
#define SH2_ITEM_46      46
#define COIN_OF_SNAKE    47
#define SH2_ITEM_48      48
#define SH2_ITEM_49      49
#define SH2_ITEM_50      50
#define SH2_ITEM_NEEDLE  51
#define SH2_ITEM_52      52
#define SH2_ITEM_53      53
#define SH2_ITEM_54      54
#define SH2_ITEM_55      55
#define SH2_ITEM_56      56
#define SH2_ITEM_57      57
#define SH2_ITEM_58      58
#define SH2_ITEM_59      59
#define SH2_ITEM_60      60
#define SH2_ITEM_61      61
#define SH2_ITEM_62      62
#define SH2_ITEM_63      63
#define SH2_ITEM_64      64
#define SH2_ITEM_65      65
#define SH2_ITEM_66      66
#define SH2_ITEM_67      67
#define SH2_ITEM_69      69
#define SH2_ITEM_70      70
#define SH2_ITEM_71      71
#define SH2_ITEM_73      73
#define SH2_ITEM_74      74

// total size: 0x34
typedef struct Item {
    // Members
    u_int flag[2];          // offset 0x0, size 0x8
    u_short number[11];     // offset 0x8, size 0x16
    u_char light_switch;    // offset 0x1E, size 0x1
    u_char radio_switch;    // offset 0x1F, size 0x1
    u_char radio_volume;    // offset 0x20, size 0x1
    u_char equip;           // offset 0x21, size 0x1
    float ampoule_efficacy; // offset 0x24, size 0x4
    u_short event_use[3];   // offset 0x28, size 0x6
    u_short short_pad;      // offset 0x2E, size 0x2
    u_char last_cursor;     // offset 0x30, size 0x1
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

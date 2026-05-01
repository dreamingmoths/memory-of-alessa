// E:\work\sh2(CVS全取得)\src\jump_menu.c
#ifndef JUMP_MENU_H
#define JUMP_MENU_H

#include "common.h"
#include "Event/event.h"

extern int jump_after_data_set;

typedef struct Item
{
    // total size: 0x34
    u_int flag[2];               // offset 0x0, size 0x8
    unsigned short number[11];   // offset 0x8, size 0x16
    u_char light_switch;         // offset 0x1E, size 0x1
    u_char radio_switch;         // offset 0x1F, size 0x1
    u_char radio_volume;         // offset 0x20, size 0x1
    u_char equip;                // offset 0x21, size 0x1
    float ampoule_efficacy;      // offset 0x24, size 0x4
    unsigned short event_use[3]; // offset 0x28, size 0x6
    unsigned short short_pad;    // offset 0x2E, size 0x2
    u_char last_cursor;          // offset 0x30, size 0x1
} Item;

extern struct Item item;                    // size: 0x34, address: 0x11268E0
extern u_char hidden_item_get;       // offset 0x8, size 0x1
extern u_short item_get;             // offset 0xE, size 0x2
extern struct SubCharacter *nearest_item_p; // offset 0xAB8C, size 0x4
extern float nearest_item_xz_dist;          // offset 0xAB90, size 0x4
extern int use_item;                 // r2

int EventCheck(int act_on /* r21 */, int use_item /* r20 */, int check_only /* r19 */);
static signed short item_to_chara[75]; // size: 0x96, address: 0x2B9950
int EvSubItemGet(int kind /* r16 */, int message /* r2 */);
int EvSubItemGetAndAnim(int kind /* r16 */, int message /* r2 */);
void ItemGet(int kind /* r16 */);
struct BootOptItem *keyitem[62]; // r29+0x160
int jump_menu_select;     // size: 0x4, address: 0x11B6990
static float item_size[80];      // size: 0x140, address: 0x0
signed short item_no;            // offset 0x220, size 0x2
signed short item_kind;          // offset 0x222, size 0x2
signed short item_count;         // offset 0x224, size 0x2
signed short use_item_kind;      // offset 0x282, size 0x2
float item_scale;                // offset 0x10, size 0x4
void GameItemGetCountUp(void);
u_int GameCalcRankItemGet(void);
u_int GameCalcRankHiddenItemGet(void);
u_char quiz_get_item; // size: 0x1, address: 0x1F04498
int use_item;         // r16
static struct                /* @anon7 */
{
    // total size: 0x14
    int x;       // offset 0x0, size 0x4
    int z;       // offset 0x4, size 0x4
    int flg;     // offset 0x8, size 0x4
    int trg;     // offset 0xC, size 0x4
    int glb_crd; // offset 0x10, size 0x4
} user_data;

#endif

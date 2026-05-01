#ifndef ITEM_H
#define ITEM_H

#include "sh2_common.h"
#include "Chacter/character.h"

#define HEALTH_DRINK 1
#define FIRST_AID_KIT 2
#define AMPOULE 3

// total size: 0x34
struct Item {
    // Members
    u_int flag[2]; // offset 0x0, size 0x8
    unsigned short number[11]; // offset 0x8, size 0x16
    u_char light_switch; // offset 0x1E, size 0x1
    u_char radio_switch; // offset 0x1F, size 0x1
    u_char radio_volume; // offset 0x20, size 0x1
    u_char equip; // offset 0x21, size 0x1
    float ampoule_efficacy; // offset 0x24, size 0x4
    unsigned short event_use[3]; // offset 0x28, size 0x6
    unsigned short short_pad; // offset 0x2E, size 0x2
    u_char last_cursor; // offset 0x30, size 0x1
};

struct Stage_Data {
    // Members
    struct Event_List * ev_list; // offset 0x0, size 0x4
    u_char * ev_pos; // offset 0x4, size 0x4
    int (* * ev_prog)(); // offset 0x8, size 0x4
    struct Item_List * gi_list; // offset 0xC, size 0x4
    struct Model_List * mdl_list; // offset 0x10, size 0x4
    struct Enemy_List * en_list; // offset 0x14, size 0x4
    void (* stage_init)(); // offset 0x18, size 0x4
    void (* room_init)(); // offset 0x1C, size 0x4
    void (* alltime_func)(); // offset 0x20, size 0x4
    int glb_crd; // offset 0x24, size 0x4
    int pc_model; // offset 0x28, size 0x4
    struct _AnimeInfo * stg_anim_info; // offset 0x2C, size 0x4
    int (* bgm_control)(); // offset 0x30, size 0x4
    // total size: 0x10
    struct /* @anon0 */ {
        // Members
        void (* SpecDraw)(); // offset 0x0, size 0x4
        void (* PreDraw)(); // offset 0x4, size 0x4
        void (* PostDraw)(); // offset 0x8, size 0x4
        void (* CharaDraw_Hook)(); // offset 0xC, size 0x4
    } * gfw_func; // offset 0x34, size 0x4
    int (* chara_data_clear)(); // offset 0x38, size 0x4
    void (* sound_call_after_load)(); // offset 0x3C, size 0x4
    int reserve_11; // offset 0x40, size 0x4
};

// src\Chacter\player_result.c
extern void GameItemGetCountUp(void);

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
extern struct Stage_Data* stage;
extern struct shPlayerWork sh2jms;
extern int cmb_check_1042[11][4];

#endif

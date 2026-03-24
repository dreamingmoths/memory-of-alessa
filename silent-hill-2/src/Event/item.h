#ifndef ITEM_H
#define ITEM_H

#include "common.h"
#include "Chacter/character.h"

#define HEALTH_DRINK 1
#define FIRST_AID_KIT 2
#define AMPOULE 3

// total size: 0x8C
struct Playing_Info {
    // Members
    unsigned char stage; // offset 0x0, size 0x1
    unsigned char enemy_off; // offset 0x1, size 0x1
    unsigned char voice_off; // offset 0x2, size 0x1
    unsigned char memo_select; // offset 0x3, size 0x1
    unsigned char clear_end_kind; // offset 0x4, size 0x1
    unsigned char clear_end_number; // offset 0x5, size 0x1
    unsigned char rank; // offset 0x6, size 0x1
    unsigned char game_stage; // offset 0x7, size 0x1
    unsigned char hidden_item_get; // offset 0x8, size 0x1
    char spray_pow; // offset 0x9, size 0x1
    unsigned short savework; // offset 0xA, size 0x2
    unsigned short clearwork; // offset 0xC, size 0x2
    unsigned short item_get; // offset 0xE, size 0x2
    unsigned short kill_by_shot; // offset 0x10, size 0x2
    unsigned short kill_by_fight; // offset 0x12, size 0x2
    float time; // offset 0x14, size 0x4
    float walk_distance; // offset 0x18, size 0x4
    float run_distance; // offset 0x1C, size 0x4
    float boat_clear_time; // offset 0x20, size 0x4
    float boat_max_speed; // offset 0x24, size 0x4
    float jms_damage_total; // offset 0x28, size 0x4
    float mar_damage_by_enemy; // offset 0x2C, size 0x4
    float mar_damage_by_jms; // offset 0x30, size 0x4
    float stage_check_point[7]; // offset 0x34, size 0x1C
    unsigned int stage_score[7]; // offset 0x50, size 0x1C
    unsigned int total_score; // offset 0x6C, size 0x4
    float total_time; // offset 0x70, size 0x4
    unsigned char battle_level; // offset 0x74, size 0x1
    unsigned char riddle_level; // offset 0x75, size 0x1
    unsigned char brightness_level; // offset 0x76, size 0x1
    char screen_position_x; // offset 0x77, size 0x1
    char screen_position_y; // offset 0x78, size 0x1
    unsigned char vibration; // offset 0x79, size 0x1
    unsigned char auto_load; // offset 0x7A, size 0x1
    unsigned char sound; // offset 0x7B, size 0x1
    unsigned char bgm_volume; // offset 0x7C, size 0x1
    unsigned char se_volume; // offset 0x7D, size 0x1
    unsigned char weapon_control; // offset 0x7E, size 0x1
    unsigned char blood_color; // offset 0x7F, size 0x1
    unsigned char view_control; // offset 0x80, size 0x1
    unsigned char retreat_turn; // offset 0x81, size 0x1
    unsigned char walk_run_control; // offset 0x82, size 0x1
    unsigned char auto_aiming; // offset 0x83, size 0x1
    unsigned char view_mode; // offset 0x84, size 0x1
    unsigned char bullet_adjust; // offset 0x85, size 0x1
    unsigned char language; // offset 0x86, size 0x1
    unsigned char subtitles; // offset 0x87, size 0x1
    unsigned char control_type; // offset 0x88, size 0x1
    unsigned char radar; // offset 0x89, size 0x1
};

// total size: 0x34
struct Item {
    // Members
    unsigned int flag[2]; // offset 0x0, size 0x8
    unsigned short number[11]; // offset 0x8, size 0x16
    unsigned char light_switch; // offset 0x1E, size 0x1
    unsigned char radio_switch; // offset 0x1F, size 0x1
    unsigned char radio_volume; // offset 0x20, size 0x1
    unsigned char equip; // offset 0x21, size 0x1
    float ampoule_efficacy; // offset 0x24, size 0x4
    unsigned short event_use[3]; // offset 0x28, size 0x6
    unsigned short short_pad; // offset 0x2E, size 0x2
    unsigned char last_cursor; // offset 0x30, size 0x1
};


struct Stage_Data {
    // Members
    struct Event_List * ev_list; // offset 0x0, size 0x4
    unsigned char * ev_pos; // offset 0x4, size 0x4
    signed int (* * ev_prog)(); // offset 0x8, size 0x4
    struct Item_List * gi_list; // offset 0xC, size 0x4
    struct Model_List * mdl_list; // offset 0x10, size 0x4
    struct Enemy_List * en_list; // offset 0x14, size 0x4
    void (* stage_init)(); // offset 0x18, size 0x4
    void (* room_init)(); // offset 0x1C, size 0x4
    void (* alltime_func)(); // offset 0x20, size 0x4
    signed int glb_crd; // offset 0x24, size 0x4
    signed int pc_model; // offset 0x28, size 0x4
    struct _AnimeInfo * stg_anim_info; // offset 0x2C, size 0x4
    signed int (* bgm_control)(); // offset 0x30, size 0x4
    // total size: 0x10
    struct /* @anon0 */ {
        // Members
        void (* SpecDraw)(); // offset 0x0, size 0x4
        void (* PreDraw)(); // offset 0x4, size 0x4
        void (* PostDraw)(); // offset 0x8, size 0x4
        void (* CharaDraw_Hook)(); // offset 0xC, size 0x4
    } * gfw_func; // offset 0x34, size 0x4
    signed int (* chara_data_clear)(); // offset 0x38, size 0x4
    void (* sound_call_after_load)(); // offset 0x3C, size 0x4
    signed int reserve_11; // offset 0x40, size 0x4
};

void ItemGet(signed int kind /* r16 */);
int ItemUse(signed int kind /* r2 */);
void GameItemGetCountUp();
void shQzero(void *, int);
extern struct Playing_Info playing;
extern struct Item item;
extern struct Stage_Data* stage;
extern struct shPlayerWork sh2jms;
extern int cmb_check_1042[11][4];

#endif

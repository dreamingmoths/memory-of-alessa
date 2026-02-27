// E:\work\sh2(CVS全取得)\src\jump_menu.c
#ifndef JUMP_MENU_H
#define JUMP_MENU_H

#include "common.h"

extern int jump_after_data_set;

typedef struct Playing_Info
{
    // total size: 0x8C
    unsigned char stage;            // offset 0x0, size 0x1
    unsigned char enemy_off;        // offset 0x1, size 0x1
    unsigned char voice_off;        // offset 0x2, size 0x1
    unsigned char memo_select;      // offset 0x3, size 0x1
    unsigned char clear_end_kind;   // offset 0x4, size 0x1
    unsigned char clear_end_number; // offset 0x5, size 0x1
    unsigned char rank;             // offset 0x6, size 0x1
    unsigned char game_stage;       // offset 0x7, size 0x1
    unsigned char hidden_item_get;  // offset 0x8, size 0x1
    char spray_pow;                 // offset 0x9, size 0x1
    unsigned short savecount;       // offset 0xA, size 0x2
    unsigned short clearcount;      // offset 0xC, size 0x2
    unsigned short item_get;        // offset 0xE, size 0x2
    unsigned short kill_by_shot;    // offset 0x10, size 0x2
    unsigned short kill_by_fight;   // offset 0x12, size 0x2
    float time;                     // offset 0x14, size 0x4
    float walk_distance;            // offset 0x18, size 0x4
    float run_distance;             // offset 0x1C, size 0x4
    float boat_clear_time;          // offset 0x20, size 0x4
    float boat_max_speed;           // offset 0x24, size 0x4
    float jms_damage_total;         // offset 0x28, size 0x4
    float mar_damage_by_enemy;      // offset 0x2C, size 0x4
    float mar_damage_by_jms;        // offset 0x30, size 0x4
    float stage_check_point[7];     // offset 0x34, size 0x1C
    unsigned int stage_score[7];    // offset 0x50, size 0x1C
    unsigned int total_score;       // offset 0x6C, size 0x4
    float total_time;               // offset 0x70, size 0x4
    unsigned char battle_level;     // offset 0x74, size 0x1
    unsigned char riddle_level;     // offset 0x75, size 0x1
    unsigned char brightness_level; // offset 0x76, size 0x1
    char screen_position_x;         // offset 0x77, size 0x1
    char screen_position_y;         // offset 0x78, size 0x1
    unsigned char vibration;        // offset 0x79, size 0x1
    unsigned char auto_load;        // offset 0x7A, size 0x1
    unsigned char sound;            // offset 0x7B, size 0x1
    unsigned char bgm_volume;       // offset 0x7C, size 0x1
    unsigned char se_volume;        // offset 0x7D, size 0x1
    unsigned char weapon_control;   // offset 0x7E, size 0x1
    unsigned char blood_color;      // offset 0x7F, size 0x1
    unsigned char view_control;     // offset 0x80, size 0x1
    unsigned char retreat_turn;     // offset 0x81, size 0x1
    unsigned char walk_run_control; // offset 0x82, size 0x1
    unsigned char auto_aiming;      // offset 0x83, size 0x1
    unsigned char view_mode;        // offset 0x84, size 0x1
    unsigned char bullet_adjust;    // offset 0x85, size 0x1
    unsigned char language;         // offset 0x86, size 0x1
    unsigned char subtitles;        // offset 0x87, size 0x1
    unsigned char control_type;     // offset 0x88, size 0x1
    unsigned char radar;            // offset 0x89, size 0x1
} Playing_Info;

typedef struct Item
{
    // total size: 0x34
    unsigned int flag[2];        // offset 0x0, size 0x8
    unsigned short number[11];   // offset 0x8, size 0x16
    unsigned char light_switch;  // offset 0x1E, size 0x1
    unsigned char radio_switch;  // offset 0x1F, size 0x1
    unsigned char radio_volume;  // offset 0x20, size 0x1
    unsigned char equip;         // offset 0x21, size 0x1
    float ampoule_efficacy;      // offset 0x24, size 0x4
    unsigned short event_use[3]; // offset 0x28, size 0x6
    unsigned short short_pad;    // offset 0x2E, size 0x2
    unsigned char last_cursor;   // offset 0x30, size 0x1
} Item;

struct Item item;                    // size: 0x34, address: 0x11268E0
struct Playing_Info playing;         // size: 0x8C, address: 0x122B310
unsigned char hidden_item_get;       // offset 0x8, size 0x1
unsigned short item_get;             // offset 0xE, size 0x2
struct SubCharacter *nearest_item_p; // offset 0xAB8C, size 0x4
float nearest_item_xz_dist;          // offset 0xAB90, size 0x4
signed int use_item;                 // r2
signed int EventCheck(signed int act_on /* r21 */, signed int use_item /* r20 */, signed int check_only /* r19 */);
static signed short item_to_chara[75]; // size: 0x96, address: 0x2B9950
signed int EvSubItemGet(signed int kind /* r16 */, signed int message /* r2 */);
signed int EvSubItemGetAndAnim(signed int kind /* r16 */, signed int message /* r2 */);
void ItemGet(signed int kind /* r16 */);
struct BootOptItem *keyitem[62]; // r29+0x160
signed int jump_menu_select;     // size: 0x4, address: 0x11B6990
static float item_size[80];      // size: 0x140, address: 0x0
signed short item_no;            // offset 0x220, size 0x2
signed short item_kind;          // offset 0x222, size 0x2
signed short item_count;         // offset 0x224, size 0x2
signed short use_item_kind;      // offset 0x282, size 0x2
float item_scale;                // offset 0x10, size 0x4
void GameItemGetCountUp();
unsigned int GameCalcRankItemGet();
unsigned int GameCalcRankHiddenItemGet();
unsigned char quiz_get_item; // size: 0x1, address: 0x1F04498
signed int use_item;         // r16
static struct                /* @anon7 */
{
    // total size: 0x14
    signed int x;       // offset 0x0, size 0x4
    signed int z;       // offset 0x4, size 0x4
    signed int flg;     // offset 0x8, size 0x4
    signed int trg;     // offset 0xC, size 0x4
    signed int glb_crd; // offset 0x10, size 0x4
} user_data;
struct /* @anon1 */
{
    // total size: 0x4A0
    unsigned int flag[255]; // offset 0x0, size 0x3FC
    float time_deai;        // offset 0x3FC, size 0x4
    unsigned int enemy[32]; // offset 0x400, size 0x80
    unsigned char safe[4];  // offset 0x480, size 0x4
    char rotate[4];         // offset 0x484, size 0x4
    char guruguru[4];       // offset 0x488, size 0x4
    char cylinder[4];       // offset 0x48C, size 0x4
    unsigned short clock;   // offset 0x490, size 0x2
    unsigned short carbon;  // offset 0x492, size 0x2
    char runaway[4];        // offset 0x494, size 0x4
    unsigned short hanging; // offset 0x498, size 0x2
    signed short pad;       // offset 0x49A, size 0x2
    char trunk[4];          // offset 0x49C, size 0x4
} game_flag;                // size: 0x4A0, address: 0x1126430

#endif

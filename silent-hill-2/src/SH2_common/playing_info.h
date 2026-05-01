#ifndef PLAYING_INFO_H
#define PLAYING_INFO_H

#include "sh2_common.h"

typedef struct Playing_Info
{
    // total size: 0x8C
    u_char stage;                   // offset 0x0, size 0x1
    u_char enemy_off;               // offset 0x1, size 0x1
    u_char voice_off;               // offset 0x2, size 0x1
    u_char memo_select;             // offset 0x3, size 0x1
    u_char clear_end_kind;          // offset 0x4, size 0x1
    u_char clear_end_number;        // offset 0x5, size 0x1
    u_char rank;                    // offset 0x6, size 0x1
    u_char game_stage;              // offset 0x7, size 0x1
    u_char hidden_item_get;         // offset 0x8, size 0x1
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
    u_int stage_score[7];           // offset 0x50, size 0x1C
    u_int total_score;              // offset 0x6C, size 0x4
    float total_time;               // offset 0x70, size 0x4
    u_char battle_level;            // offset 0x74, size 0x1
    u_char riddle_level;            // offset 0x75, size 0x1
    u_char brightness_level;        // offset 0x76, size 0x1
    char screen_position_x;         // offset 0x77, size 0x1
    char screen_position_y;         // offset 0x78, size 0x1
    u_char vibration;               // offset 0x79, size 0x1
    u_char auto_load;               // offset 0x7A, size 0x1
    u_char sound;                   // offset 0x7B, size 0x1
    u_char bgm_volume;              // offset 0x7C, size 0x1
    u_char se_volume;               // offset 0x7D, size 0x1
    u_char weapon_control;          // offset 0x7E, size 0x1
    u_char blood_color;             // offset 0x7F, size 0x1
    u_char view_control;            // offset 0x80, size 0x1
    u_char retreat_turn;            // offset 0x81, size 0x1
    u_char walk_run_control;        // offset 0x82, size 0x1
    u_char auto_aiming;             // offset 0x83, size 0x1
    u_char view_mode;               // offset 0x84, size 0x1
    u_char bullet_adjust;           // offset 0x85, size 0x1
    u_char language;                // offset 0x86, size 0x1
    u_char subtitles;               // offset 0x87, size 0x1
    u_char control_type;            // offset 0x88, size 0x1
    u_char radar;                   // offset 0x89, size 0x1
} Playing_Info;
extern struct Playing_Info playing;         // size: 0x8C, address: 0x122B310

#endif // PLAYING_INFO_H

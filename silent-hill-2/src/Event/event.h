#ifndef EVENT_H
#define EVENT_H

#include "common.h"
#include "Chacter/character.h"

// total size: 0x10
typedef struct Event_List {
    // Members
    int flag; // offset 0x0, size 0x4
    int cond; // offset 0x4, size 0x4
    int rslt0; // offset 0x8, size 0x4
    int rslt1; // offset 0xC, size 0x4
} Event_List;

typedef struct Game_Flag {
    // Members
    u_int flag[255]; // offset 0x0, size 0x3FC
    float time_deai; // offset 0x3FC, size 0x4
    u_int enemy[32]; // offset 0x400, size 0x80
    u_char safe[4]; // offset 0x480, size 0x4
    s_char rotate[4]; // offset 0x484, size 0x4
    s_char guruguru[4]; // offset 0x488, size 0x4
    s_char cylinder[4]; // offset 0x48C, size 0x4
    u_short clock; // offset 0x490, size 0x2
    u_short carbon; // offset 0x492, size 0x2
    s_char runaway[4]; // offset 0x494, size 0x4
    u_short hanging; // offset 0x498, size 0x2
    short pad; // offset 0x49A, size 0x2
    s_char trunk[4]; // offset 0x49C, size 0x4
} Game_Flag;

// total size: 0x44
typedef struct Stage_Data {
    // Members
    struct Event_List* ev_list; // offset 0x0, size 0x4
    u_char* ev_pos; // offset 0x4, size 0x4
    signed int (** ev_prog)(void); // offset 0x8, size 0x4
    struct Item_List* gi_list; // offset 0xC, size 0x4
    struct Model_List* mdl_list; // offset 0x10, size 0x4
    struct Enemy_List* en_list; // offset 0x14, size 0x4
    void (* stage_init)(void); // offset 0x18, size 0x4
    void (* room_init)(void); // offset 0x1C, size 0x4
    void (* alltime_func)(void); // offset 0x20, size 0x4
    int glb_crd; // offset 0x24, size 0x4
    int pc_model; // offset 0x28, size 0x4
    struct _AnimeInfo* stg_anim_info; // offset 0x2C, size 0x4
    int (* bgm_control)(void); // offset 0x30, size 0x4
    // total size: 0x10
    struct /* @anon2 */ {
        // Members
        void (* SpecDraw)(void); // offset 0x0, size 0x4
        void (* PreDraw)(void); // offset 0x4, size 0x4
        void (* PostDraw)(void); // offset 0x8, size 0x4
        void (* CharaDraw_Hook)(void); // offset 0xC, size 0x4
    } * gfw_func; // offset 0x34, size 0x4
    int (* chara_data_clear)(void); // offset 0x38, size 0x4
    void (* sound_call_after_load)(void); // offset 0x3C, size 0x4
    int reserve_11; // offset 0x40, size 0x4
} Stage_Data;

extern int ev_active;
extern int ev_cancel;
extern int ev_e_step;
extern int ev_p_step;
extern int ev_s_step;

extern Game_Flag game_flag;
extern u_short msg_buffer[];
extern struct shPlayerWork sh2jms;
extern Stage_Data* stage;

#endif // EVENT_H

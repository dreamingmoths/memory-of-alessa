#ifndef STG_OVERLAY_H
#define STG_OVERLAY_H

#include "sh2_common.h"

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
    unsigned short savecount; // offset 0xA, size 0x2
    unsigned short clearcount; // offset 0xC, size 0x2
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

// total size: 0x10
struct fsMgcFile {
    // Members
    signed int type : 8; // offset 0x0, size 0x4
    signed int padding : 24; // offset 0x0, size 0x4
    union fsFile * parent; // offset 0x4, size 0x4
    char * start; // offset 0x8, size 0x4
    char * end; // offset 0xC, size 0x4
};

// total size: 0x10
struct fsCdFile {
    // Members
    signed int type : 8; // offset 0x0, size 0x4
    signed int number : 24; // offset 0x0, size 0x4
    char * name; // offset 0x4, size 0x4
    signed int lsn; // offset 0x8, size 0x4
    signed int size; // offset 0xC, size 0x4
};

// total size: 0x10
struct fsHdFile {
    // Members
    signed int type : 8; // offset 0x0, size 0x4
    signed int padding : 24; // offset 0x0, size 0x4
    char * name; // offset 0x4, size 0x4
    signed int offset; // offset 0x8, size 0x4
    signed int size; // offset 0xC, size 0x4
};

// total size: 0x10
struct fsMgpFile {
    // Members
    signed int type : 8; // offset 0x0, size 0x4
    signed int padding : 24; // offset 0x0, size 0x4
    union fsFile * file; // offset 0x4, size 0x4
    struct fsMgcFile * start; // offset 0x8, size 0x4
    struct fsMgcFile * end; // offset 0xC, size 0x4
};

// total size: 0x10
struct fsMgfFile {
    // Members
    signed int type : 8; // offset 0x0, size 0x4
    signed int padding : 24; // offset 0x0, size 0x4
    union fsFile * parent; // offset 0x4, size 0x4
    signed int offset; // offset 0x8, size 0x4
    signed int size; // offset 0xC, size 0x4
};

union fsFile {
    // total size: 0x10
    struct /* @anon5 */ {
        // Members
        signed int type : 8; // offset 0x0, size 0x4
        signed int number : 24; // offset 0x0, size 0x4
        signed int pad0; // offset 0x4, size 0x4
        signed int pad1; // offset 0x8, size 0x4
        signed int pad2; // offset 0xC, size 0x4
    } check; // offset 0x0, size 0x10
    __int128 pack; // offset 0x0, size 0x10
    struct fsCdFile cd; // offset 0x0, size 0x10
    struct fsHdFile hd; // offset 0x0, size 0x10
    struct fsMgcFile mgc; // offset 0x0, size 0x10
    struct fsMgfFile mgf; // offset 0x0, size 0x10
    struct fsMgpFile mgp; // offset 0x0, size 0x10
};

union fsFileIndex {
    // total size: 0x8
    struct /* @anon0 */ {
        // Members
        union fsFile * fp; // offset 0x0, size 0x4
        char * name; // offset 0x4, size 0x4
    } index; // offset 0x0, size 0x8
    unsigned long pack; // offset 0x0, size 0x4
};

typedef struct mwOverlayHeader {
    // total size: 0x40
    unsigned char identifier[3]; // offset 0x0, size 0x3
    unsigned char version; // offset 0x3, size 0x1
    unsigned int id; // offset 0x4, size 0x4
    unsigned int address; // offset 0x8, size 0x4
    unsigned int sz_text; // offset 0xC, size 0x4
    unsigned int sz_data; // offset 0x10, size 0x4
    unsigned int sz_bss; // offset 0x14, size 0x4
    unsigned int _static_init; // offset 0x18, size 0x4
    unsigned int _static_init_end; // offset 0x1C, size 0x4
    unsigned char name[32]; // offset 0x20, size 0x20
} mwOverlayHeader;

typedef enum {
    Stg_null = 0x00,
    Stg_tgs_trial = 0x01,
    Stg_toilet = 0x02,
    Stg_observation = 0x03,
    Stg_forest = 0x04,
    Stg_town_east = 0x05,
    Stg_apart_e1f = 0x06,
    Stg_apart_e2f = 0x07,
    Stg_apart_e3fw = 0x08,
    Stg_apart_e3fe = 0x09,
    Stg_apart_w1f = 0x0A,
    Stg_apart_w2f = 0x0B,
    Stg_apart_stair = 0x0C,
    Stg_apart_out = 0x0D,
    Stg_town_west = 0x0E,
    Stg_bowling = 0x0F,
    Stg_to_heaven = 0x10,
    Stg_heaven_night = 0x11,
    Stg_hospital_1f_f = 0x12,
    Stg_hospital_2f_f = 0x13,
    Stg_hospital_3f_f = 0x14,
    Stg_hospital_rf_f = 0x15,
    Stg_hospital_1fw_b = 0x16,
    Stg_hospital_1fe_b = 0x17,
    Stg_hospital_2f_b = 0x18,
    Stg_hospital_3f_b = 0x19,
    Stg_hospital_bf_b = 0x1A,
    Stg_hospital_pass = 0x1B,
    Stg_society = 0x1C,
    Stg_delusion_2 = 0x1D,
    Stg_delusion_3 = 0x1E,
    Stg_prison_n = 0x1F,
    Stg_prison_s = 0x20,
    Stg_prison_bf = 0x21,
    Stg_labyrinth_w = 0x22,
    Stg_labyrinth_e = 0x23,
    Stg_labyrinth_n = 0x24,
    Stg_eddie_boss = 0x25,
    Stg_lake = 0x26,
    Stg_hotel_bf_f = 0x27,
    Stg_hotel_1f_f = 0x28,
    Stg_hotel_2f_f = 0x29,
    Stg_hotel_3f_f = 0x2A,
    Stg_hotel_bf_b = 0x2B,
    Stg_hotel_1f_b = 0x2C,
    Stg_hotel_2f_b = 0x2D,
    Stg_hotel_3f_b = 0x2E,
    Stg_hotel_fire = 0x2F,
    Stg_end_recovery = 0x30,
    Stg_end_maria = 0x31,
    Stg_end_suicide = 0x32,
    Stg_end_rebirth = 0x33,
    Stg_end_dog = 0x34,
    Stg_num = 0x35,
} StgName;

extern union fsFileIndex root_stage_apart_e1f_bin;
extern union fsFileIndex root_stage_apart_e2f_bin;
extern union fsFileIndex root_stage_apart_e3fe_bin;
extern union fsFileIndex root_stage_apart_e3fw_bin;
extern union fsFileIndex root_stage_apart_out_bin;
extern union fsFileIndex root_stage_apart_stair_bin;
extern union fsFileIndex root_stage_apart_w1f_bin;
extern union fsFileIndex root_stage_apart_w2f_bin;
extern union fsFileIndex root_stage_bowling_bin;
extern union fsFileIndex root_stage_delusion_2_bin;
extern union fsFileIndex root_stage_delusion_3_bin;
extern union fsFileIndex root_stage_eddie_boss_bin;
extern union fsFileIndex root_stage_end_dog_bin;
extern union fsFileIndex root_stage_end_maria_bin;
extern union fsFileIndex root_stage_end_rebirth_bin;
extern union fsFileIndex root_stage_end_recovery_bin;
extern union fsFileIndex root_stage_end_suicide_bin;
extern union fsFileIndex root_stage_forest_bin;
extern union fsFileIndex root_stage_heaven_night_bin;
extern union fsFileIndex root_stage_hospital_1f_f_bin;
extern union fsFileIndex root_stage_hospital_1fe_b_bin;
extern union fsFileIndex root_stage_hospital_1fw_b_bin;
extern union fsFileIndex root_stage_hospital_2f_b_bin;
extern union fsFileIndex root_stage_hospital_2f_f_bin;
extern union fsFileIndex root_stage_hospital_3f_b_bin;
extern union fsFileIndex root_stage_hospital_3f_f_bin;
extern union fsFileIndex root_stage_hospital_bf_b_bin;
extern union fsFileIndex root_stage_hospital_pass_bin;
extern union fsFileIndex root_stage_hospital_rf_f_bin;
extern union fsFileIndex root_stage_hotel_1f_b_bin;
extern union fsFileIndex root_stage_hotel_1f_f_bin;
extern union fsFileIndex root_stage_hotel_2f_b_bin;
extern union fsFileIndex root_stage_hotel_2f_f_bin;
extern union fsFileIndex root_stage_hotel_3f_b_bin;
extern union fsFileIndex root_stage_hotel_3f_f_bin;
extern union fsFileIndex root_stage_hotel_bf_b_bin;
extern union fsFileIndex root_stage_hotel_bf_f_bin;
extern union fsFileIndex root_stage_hotel_fire_bin;
extern union fsFileIndex root_stage_labyrinth_e_bin;
extern union fsFileIndex root_stage_labyrinth_n_bin;
extern union fsFileIndex root_stage_labyrinth_w_bin;
extern union fsFileIndex root_stage_lake_bin;
extern union fsFileIndex root_stage_observation_bin;
extern union fsFileIndex root_stage_prison_bf_bin;
extern union fsFileIndex root_stage_prison_n_bin;
extern union fsFileIndex root_stage_prison_s_bin;
extern union fsFileIndex root_stage_society_bin;
extern union fsFileIndex root_stage_to_heaven_bin;
extern union fsFileIndex root_stage_toilet_bin;
extern union fsFileIndex root_stage_town_east_bin;
extern union fsFileIndex root_stage_town_west_bin;

extern struct Stage_Data stage_tgs_trial;
extern struct Stage_Data stage_toilet;
extern struct Stage_Data stage_observation;
extern struct Stage_Data stage_forest;
extern struct Stage_Data stage_town_east;
extern struct Stage_Data stage_apart_e1f;
extern struct Stage_Data stage_apart_e2f;
extern struct Stage_Data stage_apart_e3fe;
extern struct Stage_Data stage_apart_w1f;
extern struct Stage_Data stage_apart_w2f;
extern struct Stage_Data stage_apart_stair;
extern struct Stage_Data stage_apart_out;
extern struct Stage_Data stage_town_west;
extern struct Stage_Data stage_bowling;
extern struct Stage_Data stage_to_heaven;
extern struct Stage_Data stage_heaven_night;
extern struct Stage_Data stage_hospital_1f_f;
extern struct Stage_Data stage_hospital_2f_f;
extern struct Stage_Data stage_hospital_3f_f;
extern struct Stage_Data stage_hospital_rf_f;
extern struct Stage_Data stage_hospital_1fw_b;
extern struct Stage_Data stage_hospital_1fe_b;
extern struct Stage_Data stage_hospital_2f_b;
extern struct Stage_Data stage_hospital_3f_b;
extern struct Stage_Data stage_hospital_bf_b;
extern struct Stage_Data stage_hospital_pass;
extern struct Stage_Data stage_society;
extern struct Stage_Data stage_delusion_2;
extern struct Stage_Data stage_delusion_3;
extern struct Stage_Data stage_prison_n;
extern struct Stage_Data stage_prison_s;
extern struct Stage_Data stage_prison_bf;
extern struct Stage_Data stage_labyrinth_w;
extern struct Stage_Data stage_labyrinth_e;
extern struct Stage_Data stage_labyrinth_n;
extern struct Stage_Data stage_eddie_boss;
extern struct Stage_Data stage_lake;
extern struct Stage_Data stage_hotel_bf_f;
extern struct Stage_Data stage_hotel_1f_f;
extern struct Stage_Data stage_hotel_2f_f;
extern struct Stage_Data stage_hotel_3f_f;
extern struct Stage_Data stage_hotel_bf_b;
extern struct Stage_Data stage_hotel_1f_b;
extern struct Stage_Data stage_hotel_2f_b;
extern struct Stage_Data stage_hotel_3f_b;
extern struct Stage_Data stage_hotel_fire;
extern struct Stage_Data stage_end_recovery;
extern struct Stage_Data stage_end_maria;
extern struct Stage_Data stage_end_suicide;
extern struct Stage_Data stage_end_dog;

int FcRead(union fsFileIndex *id, void *databuf);
void FlushCache(int);
void MWNotifyOverlayLoaded(void *addr);
static union fsFileIndex *StgOverlayGetFileID(StgName stg_name);
static struct Stage_Data *StgOverlayGetStageData(StgName stg_name);
void UtilMemSet(void *addr, int val, int size);
void fsSync(int mode, int fid);
void shSyncVEnd(int mode);
void verbose(int , const char *);
extern u_char D_1F01E00[]; 
extern union fsFileIndex * last_stage_bin;
extern struct Playing_Info playing;
extern struct Stage_Data * stage;

#endif
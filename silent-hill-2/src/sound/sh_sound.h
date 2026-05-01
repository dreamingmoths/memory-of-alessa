#ifndef SH_SOUND_H
#define SH_SOUND_H

#include "common.h"

// total size: 0xC this was an anon
typedef struct Change_List {
    // Members
    int sd_se; // offset 0x0, size 0x4
    int sd_3d; // offset 0x4, size 0x4
    int file; // offset 0x8, size 0x4
} Change_List;

// total size: 0x8
typedef struct Se_TrackBuffer {
    // Members
    u_char status; // offset 0x0, size 0x1
    u_char fade_in_type; // offset 0x1, size 0x1
    u_char fade_out_type; // offset 0x2, size 0x1
    u_char pad; // offset 0x3, size 0x1
    float volume; // offset 0x4, size 0x4
} Se_TrackBuffer;

// total size: 0x4C
typedef struct Se_BgmBuffer {
    // Members
    int current; // offset 0x0, size 0x4
    int next; // offset 0x4, size 0x4
    int read; // offset 0x8, size 0x4
    int sdb_no; // offset 0xC, size 0x4
    float volume; // offset 0x10, size 0x4
    Se_TrackBuffer track[7]; // offset 0x14, size 0x38
} Se_BgmBuffer;

// total size: 0x40
typedef struct Se2D_ManageData {
    // Members
    int sd; // offset 0x0, size 0x4
    float pos[4] __attribute__((aligned(16))); // offset 0x10, size 0x10
    float vol; // offset 0x20, size 0x4
    short room; // offset 0x24, size 0x2
    u_char pos_on; // offset 0x26, size 0x1
    u_char pre_dist; // offset 0x27, size 0x1
    short pre_pan; // offset 0x28, size 0x2
    short status; // offset 0x2A, size 0x2
    float timer; // offset 0x2C, size 0x4
    float base; // offset 0x30, size 0x4
} Se2D_ManageData;

// total size: 0x30
typedef struct Se3D_ChannelData {
    // Members
    int sd; // offset 0x0, size 0x4
    int room; // offset 0x4, size 0x4
    int status; // offset 0x8, size 0x4
    float pos[4] __attribute__((aligned(16))); // offset 0x10, size 0x10
    float vol; // offset 0x20, size 0x4
} Se3D_ChannelData;

// total size: 0x20
typedef struct _SND_ROAD_AREA {
    // Members
    float x0; // offset 0x0, size 0x4
    float z0; // offset 0x4, size 0x4
    float x1; // offset 0x8, size 0x4
    float z1; // offset 0xC, size 0x4
    float x2; // offset 0x10, size 0x4
    float z2; // offset 0x14, size 0x4
    float min_hy; // offset 0x18, size 0x4
    float max_hy; // offset 0x1C, size 0x4
} SND_ROAD_AREA;

// total size: 0x40
typedef struct _SOUND_DATA {
    // Members
    SND_ROAD_AREA lim_sw; // offset 0x0, size 0x20
    int flags; // offset 0x20, size 0x4
    int chanstat[7]; // offset 0x24, size 0x1C
} SOUND_DATA;

// total size: 0x1C
typedef struct _NEAR_SOUND_DATA {
    // Members
    char inVol[7]; // offset 0x0, size 0x7
    char outVol[7]; // offset 0x7, size 0x7
    int errCode; // offset 0x10, size 0x4
    int absIndex; // offset 0x14, size 0x4
    float len; // offset 0x18, size 0x4
} NEAR_SOUND_DATA;

// total size: 0x120
typedef struct _SOUND_WORK {
    // Members
    SOUND_DATA * sound_ary; // offset 0x0, size 0x4
    float chara_pos[4]  __attribute__((aligned(16))); // offset 0x10, size 0x10
    float half_w; // offset 0x20, size 0x4
    int page; // offset 0x24, size 0x4
    int near_sound_num; // offset 0x28, size 0x4
    NEAR_SOUND_DATA near_sound_ary[8]; // offset 0x2C, size 0xE0
    int on_num; // offset 0x10C, size 0x4
    char on_chan[7]; // offset 0x110, size 0x7
    int absNum; // offset 0x118, size 0x4
    int nearindex; // offset 0x11C, size 0x4
} SOUND_WORK;

/*
// total size: 0x8C
typedef struct Playing_Info {
    // Members
    u_char stage; // offset 0x0, size 0x1
    u_char enemy_off; // offset 0x1, size 0x1
    u_char voice_off; // offset 0x2, size 0x1
    u_char memo_select; // offset 0x3, size 0x1
    u_char clear_end_kind; // offset 0x4, size 0x1
    u_char clear_end_number; // offset 0x5, size 0x1
    u_char rank; // offset 0x6, size 0x1
    u_char game_stage; // offset 0x7, size 0x1
    u_char hidden_item_get; // offset 0x8, size 0x1
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
    u_int stage_score[7]; // offset 0x50, size 0x1C
    u_int total_score; // offset 0x6C, size 0x4
    float total_time; // offset 0x70, size 0x4
    u_char battle_level; // offset 0x74, size 0x1
    u_char riddle_level; // offset 0x75, size 0x1
    u_char brightness_level; // offset 0x76, size 0x1
    char screen_position_x; // offset 0x77, size 0x1
    char screen_position_y; // offset 0x78, size 0x1
    u_char vibration; // offset 0x79, size 0x1
    u_char auto_load; // offset 0x7A, size 0x1
    u_char sound; // offset 0x7B, size 0x1
    u_char bgm_volume; // offset 0x7C, size 0x1
    u_char se_volume; // offset 0x7D, size 0x1
    u_char weapon_control; // offset 0x7E, size 0x1
    u_char blood_color; // offset 0x7F, size 0x1
    u_char view_control; // offset 0x80, size 0x1
    u_char retreat_turn; // offset 0x81, size 0x1
    u_char walk_run_control; // offset 0x82, size 0x1
    u_char auto_aiming; // offset 0x83, size 0x1
    u_char view_mode; // offset 0x84, size 0x1
    u_char bullet_adjust; // offset 0x85, size 0x1
    u_char language; // offset 0x86, size 0x1
    u_char subtitles; // offset 0x87, size 0x1
    u_char control_type; // offset 0x88, size 0x1
    u_char radar; // offset 0x89, size 0x1
} Playing_Info;
*/

void SeWait(int wait /* r17 */);
void SeForceWait(void);
void SeCallInit(int sect /* r18 */, int mmode /* r17 */, char* path /* r16 */);
void SeCallReset(void);
int SeCall(int sd_no /* r17 */, float volume /* r20 */, int stereo /* r16 */);
int SeCallPos(int sd_no /* r20 */, float volume /* r20 */, float* pos /* r19 */, int status /* r18 */);
int Se3dPlayCheck(int sd_no /* r2 */);
void SeStop(int sd_no /* r18 */);
void SeBgmChange(void);
void SeSoundLoad(void);
void SeSoundEffect3dLoad(int data /* r16 */);
void SeSoundEffectLoad(int data /* r16 */);
void SeSoundManager(void);
void Se2dManager(void);
void Se2dManageDataVolumeChange(int sd /* r2 */, float vol /* r29+0x10 */);
float Se2dManageDataTimer(int sd /* r2 */, int clear /* r2 */);
void Se3dManager(void);
void SeBgmManager(void);
int Se3dControl(int sd_no /* r17 */, float volume /* r20 */, float* pos /* r16 */);
void SeMasterVolumeChange(void);

extern Se_BgmBuffer bgm;
extern Se2D_ManageData se_2d_manage_data[4];
extern Se3D_ChannelData se_3d_channel_data[8];
extern int se_3d_channel_max;
extern int se_3d_channel_number;
extern int se_3d_load_data;
extern int se_load_data;
extern SOUND_WORK sound_work;
extern Change_List change_list[242]; // size: 0xB58, address: 0x2B8880
//extern Playing_Info playing;

//extern void shQzero(void*, int); // we need to find shQzero proper signature

extern void sd_setpath(char* dp /* r2 */); // M:\select\sound\sd0712\ee\sd_call.c we need to find a home for lil bro

#endif // SH_SOUND_H

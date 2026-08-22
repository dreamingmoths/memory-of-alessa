#ifndef DEMOVIEW_H
#define DEMOVIEW_H

#include "sh2_common.h"
#include "sce/libvu0.h"
#include "Chacter/character.h"

#define DRAMA_DEMO_9  0x9
#define DRAMA_DEMO_D  0xD
#define DRAMA_DEMO_E  0xE
#define DRAMA_DEMO_21 0x21
#define DRAMA_DEMO_26 0x26
#define DRAMA_DEMO_2E 0x2E
#define DRAMA_DEMO_41 0x41
#define DRAMA_DEMO_42 0x42
#define DRAMA_DEMO_4A 0x4A
#define DRAMA_DEMO_4E 0x4E

#define DdsGetFlag(_flag) GET_BIT(demo_status, _flag)
#define DdsSetFlag(_flag) SET_BIT(demo_status, _flag)
#define DdsUnsetFlag(_flag) UNSET_BIT(demo_status, _flag)

#define DDS_FLAG_0                   0
#define DDS_FLAG_FLOAT32             1
#define DDS_FLAG_START               2
#define DDS_FLAG_SUBTITLES_SHOWN     3
#define DDS_FLAG_4                   4
#define DDS_FLAG_5                   5
#define DDS_FLAG_6                   6
#define DDS_FLAG_7                   7
#define DDS_FLAG_8                   8
#define DDS_FLAG_9                   9

#define DDS_PLAY_KEY_BREAK           11
#define DDS_PLAY_KEY_16              16
#define DDS_PLAY_KEY_17              17
#define DDS_PLAY_KEY_18              18
#define DDS_PLAY_KEY_19              19
#define DDS_PLAY_KEY_20              20

#define DDS_PLAY_CAMERA_POSITION     3
#define DDS_PLAY_CAMERA_INTEREST     4
#define DDS_PLAY_CAMERA_ROTATION     5
#define DDS_PLAY_CAMERA_ROLL         6
#define DDS_PLAY_CAMERA_PLANE        7
#define DDS_PLAY_CAMERA_8            8
#define DDS_PLAY_CAMERA_9            9
#define DDS_PLAY_CAMERA_10           10
#define DDS_PLAY_CAMERA_11           11

#define DDS_PLAY_LIGHT_VISIBLE       1
#define DDS_PLAY_LIGHT_INVISIBLE     2
#define DDS_PLAY_LIGHT_POSITION      3
#define DDS_PLAY_LIGHT_INTEREST      4
#define DDS_PLAY_LIGHT_ROTATION      5
#define DDS_PLAY_LIGHT_COLOR         8
#define DDS_PLAY_LIGHT_FALLOFF       9
#define DDS_PLAY_LIGHT_CONE          10
#define DDS_PLAY_LIGHT_11            11

#define DDS_PLAY_CHARACTER_VISIBLE   1
#define DDS_PLAY_CHARACTER_INVISIBLE 2
#define DDS_PLAY_CHARACTER_POSITION  3
#define DDS_PLAY_CHARACTER_11        11

// total size: 0x4
typedef struct DramaDemo_MessageTime {
    // Members
    u_short start; // offset 0x0, size 0x2
    u_short end;   // offset 0x2, size 0x2
} DramaDemo_MessageTime;

// total size: 0x28
typedef struct DramaDemo_PlayInfo {
    // Members
    int demo_no;                         // offset 0x0, size 0x4
    char* adr_dds_top;                   // offset 0x4, size 0x4
    short* adr_anim;                     // offset 0x8, size 0x4
    DramaDemo_MessageTime* adr_msg_time; // offset 0xC, size 0x4
    short msg_start;                     // offset 0x10, size 0x2
    short voice_sd_no;                   // offset 0x12, size 0x2
    int* adr_voice;                      // offset 0x14, size 0x4
    int stream_no;                       // offset 0x18, size 0x4
    float stream_start;                  // offset 0x1C, size 0x4
    float add_pos_x;                     // offset 0x20, size 0x4
    float add_pos_z;                     // offset 0x24, size 0x4
} DramaDemo_PlayInfo;

typedef struct DramaDemo_AnimInfo {
    // total size: 0x28
    char name[32]; // offset 0x0, size 0x20
    short kind;    // offset 0x20, size 0x2
    short id;      // offset 0x22, size 0x2
    short start;   // offset 0x24, size 0x2
    short end;     // offset 0x26, size 0x2
} DramaDemo_AnimInfo;

typedef struct /* @anon6 */ {
    // total size: 0x360
    float frame; // offset 0x0, size 0x4
    struct /* @anon2 */ {
        // total size: 0x30
        sceVu0FVECTOR position; // offset 0x0, size 0x10
        sceVu0FVECTOR interest; // offset 0x10, size 0x10
        float roll;             // offset 0x20, size 0x4
        float plane;            // offset 0x24, size 0x4
    } camera;                   // offset 0x10, size 0x30
    struct /* @anon3 */ {
        // total size: 0x60
        sceVu0FVECTOR position; // offset 0x0, size 0x10
        sceVu0FVECTOR interest; // offset 0x10, size 0x10
        float roll;             // offset 0x20, size 0x4
        sceVu0FVECTOR color;    // offset 0x30, size 0x10
        float falloff[2];       // offset 0x40, size 0x8
        float cone[2];          // offset 0x48, size 0x8
        int visible;            // offset 0x50, size 0x4
    } light[6];                 // offset 0x40, size 0x240
    struct /* @anon4 */ {
        // total size: 0x20
        sceVu0FVECTOR position; // offset 0x0, size 0x10
        int visible;            // offset 0x10, size 0x4
    } character[7];             // offset 0x280, size 0xE0
} DdsFrame;

int DramaDemoMain(DramaDemo_PlayInfo* info);
void DramaDemoSkipLast(DramaDemo_PlayInfo* info);
void DramaDemoFade(void);
// int DramaDemoNumber(void); // @note: uncommenting this gives a mismatch // @todo: find a fix
void SubtitlesExec(DramaDemo_MessageTime* msg_time, int msg_no, int str_no, float timer);
void SubtitlesManager(void);

extern int demo_status;        // size: 0x4, address: 0x1133C28
extern float demo_frame;       // size: 0x4, address: 0x1133C20
extern float total_demo_frame; // size: 0x4, address: 0x1133C18
extern int demo_number;        // size: 0x4, address: 0x1133C10
extern int demo_counter;       // size: 0x4, address: 0x1133C08

extern int sbt_msg_no; // size: 0x4, address: 0x1133C00

extern DdsFrame last;            // size: 0x360, address: 0x11338A0
extern DdsFrame next;            // size: 0x360, address: 0x1133540
extern DdsFrame base;            // size: 0x360, address: 0x11331E0
extern SubCharacter* chara_p[7]; // size: 0x1C, address: 0x11331C0

extern void* adr_dds;        // size: 0x4, address: 0x11331B0
extern short total_light;    // size: 0x2, address: 0x11331A8
extern short point_light;    // size: 0x2, address: 0x11331A0
extern short spot_light;     // size: 0x2, address: 0x1133198
extern short infinite_light; // size: 0x2, address: 0x1133190
extern int character_number; // size: 0x4, address: 0x1133188

extern u_short demo_anim_no;  // size: 0x2, address: 0x1133180
extern u_short demo_msg_no;   // size: 0x2, address: 0x1133178
extern u_short demo_voice_no; // size: 0x2, address: 0x1133170

extern float msg_frame; // size: 0x4, address: 0x1133168

extern DramaDemo_MessageTime* sbt_msg_time; // size: 0x4, address: 0x1133160
extern int sbt_str_no;                      // size: 0x4, address: 0x1133158

#endif // DEMOVIEW_H

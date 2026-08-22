#ifndef SH2SHD_STRUCTS_H
#define SH2SHD_STRUCTS_H

#include "sh2_common.h"
#include "sce/libvu0.h"

#define LIGHT_KIND_NONE -1
#define LIGHT_KIND_0 0x0
#define LIGHT_KIND_1 0x1
#define LIGHT_KIND_2 0x2
#define LIGHT_KIND_3 0x3
#define LIGHT_KIND_4 0x4
#define LIGHT_KIND_5 0x5
#define LIGHT_KIND_6 0x6
#define LIGHT_KIND_7 0x7
#define LIGHT_KIND_8 0x8
#define LIGHT_KIND_9 0x9
#define LIGHT_KIND_A 0xA

typedef struct SHADOW_PACKET_BUF {
    // total size: 0x8
    Q_WORDDATA* head; // offset 0x0, size 0x4
    Q_WORDDATA* curr; // offset 0x4, size 0x4
} SHADOW_PACKET_BUF;

typedef struct SHADOW_SHAPE_FRAME {
    // total size: 0x70
    float local_world[4][4];       // offset 0x0, size 0x40
    float local_light_position[4]; // offset 0x40, size 0x10
    Q_WORDDATA length;             // offset 0x50, size 0x10
    u_int* pRefPacket;             // offset 0x60, size 0x4
    u_int* pRawData;               // offset 0x64, size 0x4
    u_int* pKickAddr;              // offset 0x68, size 0x4
    short obj_id;                  // offset 0x6C, size 0x2
} SHADOW_SHAPE_FRAME;

typedef struct SHADOW_CHAR_MAN {
    // total size: 0xA0
    struct SubCharacter* scp;         // offset 0x0, size 0x4
    u_short kind;                     // offset 0x4, size 0x2
    short id;                         // offset 0x6, size 0x2
    u_char obj_num;                   // offset 0x8, size 0x1
    float spot_cam_angle;             // offset 0xC, size 0x4
    short light_kind;                 // offset 0x10, size 0x2
    sceVu0FVECTOR light_pos;          // offset 0x20, size 0x10
    sceVu0FVECTOR light_dir;          // offset 0x30, size 0x10
    sceVu0FVECTOR light_param;        // offset 0x40, size 0x10
    float drop_shadow_matrix[4][4];   // offset 0x50, size 0x40
    Q_WORDDATA* raw_data;             // offset 0x90, size 0x4
    struct SHADOW_SHAPE_FRAME* shape; // offset 0x94, size 0x4
} SHADOW_CHAR_MAN;

typedef struct SHADOW_OUTDOOR_MAN {
    // total size: 0x50
    u_short kind;                     // offset 0x0, size 0x2
    short map_id;                     // offset 0x2, size 0x2
    u_char lighting_mode;             // offset 0x4, size 0x1
    u_char obj_num;                   // offset 0x5, size 0x1
    short light_kind;                 // offset 0x6, size 0x2
    sceVu0FVECTOR light_pos;          // offset 0x10, size 0x10
    sceVu0FVECTOR light_dir;          // offset 0x20, size 0x10
    sceVu0FVECTOR light_param;        // offset 0x30, size 0x10
    Q_WORDDATA* raw_data;             // offset 0x40, size 0x4
    struct SHADOW_SHAPE_FRAME* shape; // offset 0x44, size 0x4
} SHADOW_OUTDOOR_MAN;

typedef struct SHADOW_MAN {
    // total size: 0x80
    char change_flag;                          // offset 0x0, size 0x1
    short spot_char_num;                       // offset 0x2, size 0x2
    short spot_bg_num;                         // offset 0x4, size 0x2
    short self_num;                            // offset 0x6, size 0x2
    short parallel_char_num;                   // offset 0x8, size 0x2
    short parallel_bg_num;                     // offset 0xA, size 0x2
    short point_char_num;                      // offset 0xC, size 0x2
    short char_man_num;                        // offset 0xE, size 0x2
    short outdoor_man_num;                     // offset 0x10, size 0x2
    short enemy_num;                           // offset 0x12, size 0x2
    short chr_shadow_switch;                   // offset 0x14, size 0x2
    short bg_shadow_switch;                    // offset 0x16, size 0x2
    struct SHADOW_CHAR_MAN* char_man[16];      // offset 0x18, size 0x40
    struct SHADOW_OUTDOOR_MAN* outdoor_man[4]; // offset 0x58, size 0x10
    struct SHADOW_PACKET_BUF reftag_pool;      // offset 0x68, size 0x8
    struct SHADOW_PACKET_BUF kick_packet;      // offset 0x70, size 0x8
} SHADOW_MAN;

typedef struct SHADOW_MICRO_FRAME {
    // total size: 0x220
    float drop_shadow[4][4];   // offset 0x0, size 0x40
    float world_clip[4][4];    // offset 0x40, size 0x40
    float clip_screen[4][4];   // offset 0x80, size 0x40
    Q_WORDDATA color;          // offset 0xC0, size 0x10
    Q_WORDDATA giftag_color;   // offset 0xD0, size 0x10
    Q_WORDDATA giftag_dummy;   // offset 0xE0, size 0x10
    Q_WORDDATA giftag_default; // offset 0xF0, size 0x10
    Q_WORDDATA giftag_3;       // offset 0x100, size 0x10
    Q_WORDDATA giftag_4;       // offset 0x110, size 0x10
    Q_WORDDATA giftag_5;       // offset 0x120, size 0x10
    Q_WORDDATA giftag_6;       // offset 0x130, size 0x10
    Q_WORDDATA giftag_7;       // offset 0x140, size 0x10
    Q_WORDDATA giftag_8;       // offset 0x150, size 0x10
    Q_WORDDATA giftag_9;       // offset 0x160, size 0x10
    Q_WORDDATA giftag_10;      // offset 0x170, size 0x10
    Q_WORDDATA alpha0;         // offset 0x180, size 0x10
    Q_WORDDATA alpha1;         // offset 0x190, size 0x10
    Q_WORDDATA flags;          // offset 0x1A0, size 0x10
    float y_unit[4];           // offset 0x1B0, size 0x10
    float dummy[3][4];         // offset 0x1C0, size 0x30
    float cam_pos[4];          // offset 0x1F0, size 0x10
    float spot_cam_dir[4];     // offset 0x200, size 0x10
    u_int* pKickAddr;          // offset 0x210, size 0x4
    u_int* pRawData;           // offset 0x214, size 0x4
} SHADOW_MICRO_FRAME;

typedef struct SHADOW_OFF_WORK_BG {
    // total size: 0x42
    short map_id;     // offset 0x0, size 0x2
    short obj_id[32]; // offset 0x2, size 0x40
} SHADOW_OFF_WORK_BG;

typedef struct SHADOW_OFF_WORK_CHAR {
    // total size: 0x30
    u_short kind;     // offset 0x0, size 0x2
    short id;         // offset 0x2, size 0x2
    short obj_id[22]; // offset 0x4, size 0x2C
} SHADOW_OFF_WORK_CHAR;

typedef struct JMS_SHADOW_ENV {
    // total size: 0x10
    short light_kind;      // offset 0x0, size 0x2
    float bias;            // offset 0x4, size 0x4
    float height_revision; // offset 0x8, size 0x4
    float scale;           // offset 0xC, size 0x4
} JMS_SHADOW_ENV;

extern struct JMS_SHADOW_ENV jms_shadow_env;

typedef struct SHADOW_CHAR_HEAD {
    // total size: 0x10
    short char_id;  // offset 0x0, size 0x2
    u_short kind;   // offset 0x2, size 0x2
    short obj_num;  // offset 0x4, size 0x2
    short reserve1; // offset 0x6, size 0x2
    short reserve2; // offset 0x8, size 0x2
    short reserve3; // offset 0xA, size 0x2
    short reserve4; // offset 0xC, size 0x2
    short reserve5; // offset 0xE, size 0x2
} SHADOW_CHAR_HEAD;

#endif // SH2SHD_STRUCTS_H

#ifndef FOG_H
#define FOG_H

#include "common.h"

typedef struct FOG_PART_DATA {
    // total size: 0x60
    float pos[4]; // offset 0x0, size 0x10
    float mv[4]; // offset 0x10, size 0x10
    float dd[4]; // offset 0x20, size 0x10
    float degree[4]; // offset 0x30, size 0x10
    float tdx; // offset 0x40, size 0x4
    float tdy; // offset 0x44, size 0x4
    float alp; // offset 0x48, size 0x4
    int dpos; // offset 0x4C, size 0x4
    float alp_now; // offset 0x50, size 0x4
    float alp_add; // offset 0x54, size 0x4
    int bounce; // offset 0x58, size 0x4
    int erase; // offset 0x5C, size 0x4
} FOG_PART_DATA;

typedef struct FOG_ASM_DATA_P {
    // total size: 0x20
    FOG_PART_DATA* part; // offset 0x0, size 0x4
    u_long128* packet; // offset 0x4, size 0x4
    void* asm_data; // offset 0x8, size 0x4
    void* world_screen; // offset 0xC, size 0x4
    void* world_view; // offset 0x10, size 0x4
    void* camera_pos; // offset 0x14, size 0x4
    void* world_pos; // offset 0x18, size 0x4
    void* light_pos; // offset 0x1C, size 0x4
} FOG_ASM_DATA_P;

typedef struct FOG_PACK_WORK {
    // total size: 0x19010
    u_long128 packet[6400]; // offset 0x0, size 0x19000
    u_long128* pk_env; // offset 0x19000, size 0x4
    u_long128* pk_screen; // offset 0x19004, size 0x4
    u_long* pk_tex0; // offset 0x19008, size 0x4
    u_int* pk_vifmark; // offset 0x1900C, size 0x4
} FOG_PACK_WORK;

typedef struct FOG_WALL_DATA {
    // total size: 0x40
    float normal[4]; // offset 0x0, size 0x10
    float v0[4]; // offset 0x10, size 0x10
    float min[4]; // offset 0x20, size 0x10
    float max[4]; // offset 0x30, size 0x10
} FOG_WALL_DATA;

typedef struct FOG_OBJ_DATA {
    // total size: 0x30
    float pos[4]; // offset 0x0, size 0x10
    float mv[4]; // offset 0x10, size 0x10
    int type; // offset 0x20, size 0x4
    float rer; // offset 0x24, size 0x4
    u_long id; // offset 0x28, size 0x4
} FOG_OBJ_DATA;

typedef struct FOG_COLIS_HEAD {
    // total size: 0xC
    u_short wall1; // offset 0x0, size 0x2
    u_short wall2; // offset 0x2, size 0x2
    u_short obj1; // offset 0x4, size 0x2
    u_short obj2; // offset 0x6, size 0x2
    u_short area; // offset 0x8, size 0x2
    u_short env; // offset 0xA, size 0x2
} FOG_COLIS_HEAD;

typedef struct FOG_ENV_DATA {
    // total size: 0x18
    short PartNum; // offset 0x0, size 0x2
    short MaxPos; // offset 0x2, size 0x2
    short PartSize; // offset 0x4, size 0x2
    short EscapeRange; // offset 0x6, size 0x2
    short FloorY; // offset 0x8, size 0x2
    short LimitY; // offset 0xA, size 0x2
    short LimitHeight; // offset 0xC, size 0x2
    short WaterY; // offset 0xE, size 0x2
    u_char WindDef; // offset 0x10, size 0x1
    u_char Flag; // offset 0x11, size 0x1
    u_char Double; // offset 0x12, size 0x1
    u_char Alpha; // offset 0x13, size 0x1
    float GridRate; // offset 0x14, size 0x4
} FOG_ENV_DATA;

typedef struct FOG_WORK {
    // total size: 0x15E90
    struct FOG_PART_DATA Part[700]; // offset 0x0, size 0x10680
    float GridDense[8][8][8]; // offset 0x10680, size 0x800
    struct FOG_WALL_DATA Wall[188]; // offset 0x10E80, size 0x2F00
    struct FOG_OBJ_DATA Obj[168]; // offset 0x13D80, size 0x1F80
    float WorldScreenM[4][4]; // offset 0x15D00, size 0x40
    float WorldViewM[4][4]; // offset 0x15D40, size 0x40
    float CameraPosV[4]; // offset 0x15D80, size 0x10
    float OldCameraV[4]; // offset 0x15D90, size 0x10
    float WorldPosV[4]; // offset 0x15DA0, size 0x10
    float LocalPosV[4]; // offset 0x15DB0, size 0x10
    float MapPosV[4]; // offset 0x15DC0, size 0x10
    float LightPosV[4]; // offset 0x15DD0, size 0x10
    float WindV[4]; // offset 0x15DE0, size 0x10
    float fewdense[4]; // offset 0x15DF0, size 0x10
    float StayPoint[4]; // offset 0x15E00, size 0x10
    float LimitY; // offset 0x15E10, size 0x4
    float LimitY2; // offset 0x15E14, size 0x4
    float WaterY; // offset 0x15E18, size 0x4
    float SpeedLevel; // offset 0x15E1C, size 0x4
    float sc_degree[4]; // offset 0x15E20, size 0x10
    float sc_tdx; // offset 0x15E30, size 0x4
    float sc_tdy; // offset 0x15E34, size 0x4
    float MaxPos; // offset 0x15E38, size 0x4
    float FadePos; // offset 0x15E3C, size 0x4
    float PartSize; // offset 0x15E40, size 0x4
    float Projection; // offset 0x15E44, size 0x4
    float EscapeRange; // offset 0x15E48, size 0x4
    float GridRate; // offset 0x15E4C, size 0x4
    float FloorY; // offset 0x15E50, size 0x4
    short PartNum; // offset 0x15E54, size 0x2
    short WallNum; // offset 0x15E56, size 0x2
    short ObjMax; // offset 0x15E58, size 0x2
    short ObjNum; // offset 0x15E5A, size 0x2
    short ObjNum2; // offset 0x15E5C, size 0x2
    short Alpha; // offset 0x15E5E, size 0x2
    short WindDef; // offset 0x15E60, size 0x2
    char Double; // offset 0x15E62, size 0x1
    char LoadStep; // offset 0x15E63, size 0x1
    char Global; // offset 0x15E64, size 0x1
    u_short AreaMax; // offset 0x15E66, size 0x2
    u_short Flag; // offset 0x15E68, size 0x2
    u_int Color; // offset 0x15E6C, size 0x4
    int SumW; // offset 0x15E70, size 0x4
    int fid; // offset 0x15E74, size 0x4
    int WindTimer; // offset 0x15E78, size 0x4
    struct FOG_COLIS_HEAD* ColisHead; // offset 0x15E7C, size 0x4
    struct FOG_AREA_DATA* AreaTop; // offset 0x15E80, size 0x4
    struct FOG_ENV_DATA* EnvTop; // offset 0x15E84, size 0x4
    struct FOG_ENV_DATA* EnvNow; // offset 0x15E88, size 0x4
} FOG_WORK;

#endif // FOG_H

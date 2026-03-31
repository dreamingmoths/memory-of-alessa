#ifndef CL_MAIN_H
#define CL_MAIN_H

#include "sh2_common.h"
#include "Chacter/character.h"
#include "Chacter/sh_character_battle.h"

struct _CL_CHARA_LIST {
    // total size: 0xE0
    struct _CL_HITPOLY_COLUMN col; // offset 0x0, size 0x30
    struct _CL_HITPOLY_COLUMN wcol; // offset 0x30, size 0x30
    struct SubCharacter * sc; // offset 0x60, size 0x4
    float opos[4]; // offset 0x70, size 0x10
    float pos[4]; // offset 0x80, size 0x10
    float mvec[4]; // offset 0x90, size 0x10
    float wallcv[4]; // offset 0xA0, size 0x10
    float mang; // offset 0xB0, size 0x4
    signed int wflg; // offset 0xB4, size 0x4
    float ccvec[4]; // offset 0xC0, size 0x10
    signed short movflg; // offset 0xD0, size 0x2
    signed short batflg; // offset 0xD2, size 0x2
    void (* heightfunc)(float *); // offset 0xD4, size 0x4
};
typedef struct _CL_SELECT_MAP
{
    // total size: 0x8
    unsigned char *base; // offset 0x0, size 0x4
    unsigned char sect;  // offset 0x4, size 0x1
} CL_SELECT_MAP;
typedef struct _CL_HITPOLY_PLANE
{
    // total size: 0x50
    unsigned char kind;    // offset 0x0, size 0x1
    unsigned char shape;   // offset 0x1, size 0x1
    unsigned short pad;    // offset 0x2, size 0x2
    unsigned int weight;   // offset 0x4, size 0x4
    unsigned int material; // offset 0x8, size 0x4
    signed int flg;        // offset 0xC, size 0x4
    float p[4][4];         // offset 0x10, size 0x40
} CL_HITPOLY_PLANE;
typedef struct _CL_WALLHITDAT
{
    // total size: 0x50
    signed int kind;              // offset 0x0, size 0x4
    sceVu0FVECTOR cv;             // offset 0x10, size 0x10
    struct _CL_HITPOLY_PLANE *pl; // offset 0x20, size 0x4
    sceVu0FVECTOR normal;         // offset 0x30, size 0x10
    float nang;                   // offset 0x40, size 0x4
} CL_WALLHITDAT;
typedef struct _CL_BATTLE_RESULT
{
    // total size: 0x40
    signed int enable;    // offset 0x0, size 0x4
    unsigned int id;      // offset 0x4, size 0x4
    signed int atr;       // offset 0x8, size 0x4
    sceVu0FVECTOR pos;    // offset 0x10, size 0x10
    sceVu0FVECTOR vec;    // offset 0x20, size 0x10
    unsigned short kind;  // offset 0x30, size 0x2
    unsigned short btlid; // offset 0x32, size 0x2
    union                 /* @anon0 */
    {
        struct SubCharacter *en;       // offset 0x0, size 0x4
        struct _CL_HITPOLY_PLANE *pl;  // offset 0x0, size 0x4
        struct _CL_HITPOLY_COLUMN *cl; // offset 0x0, size 0x4
    } obj;                             // offset 0x34, size 0x4
} CL_BATTLE_RESULT;
typedef struct _CL_CLDHEADER
{
    // total size: 0x174
    float sx;             // offset 0x0, size 0x4
    float sz;             // offset 0x4, size 0x4
    signed int b0size;    // offset 0x8, size 0x4
    signed int b1size;    // offset 0xC, size 0x4
    signed int b2size;    // offset 0x10, size 0x4
    signed int b3size;    // offset 0x14, size 0x4
    signed int csize;     // offset 0x18, size 0x4
    signed int disable;   // offset 0x1C, size 0x4
    signed int b0ofs[16]; // offset 0x20, size 0x40
    signed int b1ofs[16]; // offset 0x60, size 0x40
    signed int b2ofs[16]; // offset 0xA0, size 0x40
    signed int b3ofs[16]; // offset 0xE0, size 0x40
    signed int clofs[16]; // offset 0x120, size 0x40
    unsigned int fldofs;  // offset 0x160, size 0x4
    unsigned int wldofs;  // offset 0x164, size 0x4
    unsigned int cedofs;  // offset 0x168, size 0x4
    unsigned int swdofs;  // offset 0x16C, size 0x4
    unsigned int cldofs;  // offset 0x170, size 0x4
} CL_CLDHEADER;

/*
union
{
    typedef struct SubCharacter *en;       // offset 0x0, size 0x4
    struct _CL_HITPOLY_PLANE *pl;  // offset 0x0, size 0x4
    struct _CL_HITPOLY_COLUMN *cl; // offset 0x0, size 0x4
} SubCharacter *en;       // offset 0x0, size 0x4;
union
{
    typedef struct shBattleFight fight; // offset 0x0, size 0xC
    struct shBattleShot shot;   // offset 0x0, size 0xC
} shBattleFight fight; // offset 0x0, size 0xC;
union
{
    typedef struct _CL_VHIT_WALL wall;   // offset 0x0, size 0x30
    struct _CL_VHIT_CHARA chara; // offset 0x0, size 0x20
} CL_VHIT_WALL wall;   // offset 0x0, size 0x30;
*/

typedef struct _CL_BATTLE_QUE
{
    // total size: 0x50
    unsigned short kind;     // offset 0x0, size 0x2
    unsigned short btlid;    // offset 0x2, size 0x2
    struct SubCharacter *sc; // offset 0x4, size 0x4
    sceVu0FVECTOR svs;       // offset 0x10, size 0x10
    sceVu0FVECTOR sve;       // offset 0x20, size 0x10
    sceVu0FVECTOR evs;       // offset 0x30, size 0x10
    sceVu0FVECTOR eve;       // offset 0x40, size 0x10
} CL_BATTLE_QUE;

typedef struct _CL_DYNAMICFLOOR_LIST {
    // total size: 0x44
    signed int use; // offset 0x0, size 0x4
    struct _CL_HITPOLY_PLANE * dw[16]; // offset 0x4, size 0x40
} CL_DYNAMICFLOOR_LIST;

typedef struct _CL_DYNAMICWALL_LIST
{
    // total size: 0x84
    signed int use;                   // offset 0x0, size 0x4
    struct _CL_HITPOLY_PLANE *dw[32]; // offset 0x4, size 0x80
} CL_DYNAMICWALL_LIST;

typedef struct _CL_HITRESULT {
    // total size: 0x40
    signed int chk; // offset 0x0, size 0x4
    sceVu0FVECTOR cp; // offset 0x10, size 0x10
    sceVu0FVECTOR cv; // offset 0x20, size 0x10
    struct _CL_HITPOLY_HEAD * pd; // offset 0x30, size 0x4
} CL_HITRESULT;

#define CL_BATTLE_RESULT_SIZE 65

extern /* static */ struct shAttackInfo sh2_attack_list[66]; // size: 0x948, address: 0x0
extern unsigned char clPermColExpFlg[210]; // size: 0xD2, address: 0x2A9880
extern signed int clCollisionEnable; // size: 0x4, address: 0x4917C0
extern signed int clUseBattleResult; // size: 0x4, address: 0x48ABE0
extern struct _CL_BATTLE_RESULT clBattleResult[CL_BATTLE_RESULT_SIZE]; // size: 0x1040, address: 0x489BA0
extern struct _CL_DYNAMICFLOOR_LIST clDynamicFloorList[2]; // size: 0x88, address: 0x48D010
extern struct _CL_DYNAMICWALL_LIST clDynamicWallList[2]; // size: 0x108, address: 0x48D0A0
extern signed int clCharaListUse[2]; // size: 0x8, address: 0x4917B0
extern signed int clDynamicFloorListAct; // size: 0x4, address: 0x48D098
extern signed int clDynamicWallListAct; // size: 0x4, address: 0x48D1A8
extern signed int clCharaListAct; // size: 0x4, address: 0x4917B8
extern signed int clUseBattleQue; // size: 0x4, address: 0x48BFF0
extern struct _CL_CHARA_LIST clCharaList[2][32]; // size: 0x3800, address: 0x48DFB0
extern struct _CL_WALLHITDAT clWallHitData[32]; // size: 0xA00, address: 0x48D5B0
extern struct _CL_BATTLE_QUE clBattleQue[64]; // size: 0x1400, address: 0x48ABF0
extern signed int clVHitListUse; // size: 0x4, address: 0x48D000
extern struct _CL_VHIT_RESULT clVHitResult[64]; // size: 0x1000, address: 0x48C000
extern float clswPerc[5]; // size: 0x14, address: 0x2A9980
extern struct _CL_SELECT_MAP clSelectMap[128]; // size: 0x400, address: 0x48D1B0

void clAllInitCollisionData(void);

void clFrameInitCollisionData(void);

static void clCheckColumn2WallHit(struct _CL_HITRESULT * cres /* r18 */, struct _CL_HITPOLY_PLANE * pl /* r17 */, struct _CL_HITPOLY_COLUMN * col /* r16 */);

static void clCheckHitWallCollision(struct _CL_HITPOLY_COLUMN * col /* r19 */, signed int * whnum /* r18 */, struct _CL_HITPOLY_PLANE * pl /* r17 */, signed int * ptr /* r16 */);

static void clCheckColumn2ColumnHit(struct _CL_HITPOLY_COLUMN * col /* r19 */, signed int * whnum /* r18 */, struct _CL_HITPOLY_COLUMN * cl /* r17 */, signed int * ptr /* r16 */);

static void clCollectCharaHeightNormal(struct SubCharacter * sc /* r17 */);

void clBattleAddQue(struct _CL_BATTLE_QUE * que /* r2 */);

struct _CL_BATTLE_RESULT * clBattleGetResult(unsigned int id /* r2 */, struct _CL_BATTLE_RESULT * before /* r2 */);

void clAddDynamicWall(struct _CL_HITPOLY_PLANE * pl /* r2 */);

void clAddDynamicFloor(struct _CL_HITPOLY_PLANE * pl /* r2 */);

// nonmatching:

int clCheckSubColumnToColumn(struct _CL_HITRESULT * result /* r2 */, float (* clm0)[4] /* r2 */, float (* clm1)[4] /* r2 */);

void clCheckHitEyesOnlyFloor(struct _CL_VHIT_RESULT * res /* r19 */, int unknown, float * sp /* r18 */, float * ep /* r17 */);

#endif CL_MAIN_H

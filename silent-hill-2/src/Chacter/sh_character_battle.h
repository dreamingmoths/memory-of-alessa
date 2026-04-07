#ifndef SH_CHARACTER_BATTLE_H
#define SH_CHARACTER_BATTLE_H

#include "common.h"
#include "Chacter/character.h"

typedef struct shBattleFight
{
    // total size: 0xC
    float test_a; // offset 0x0, size 0x4
    float test_b; // offset 0x4, size 0x4
    float test_c; // offset 0x8, size 0x4
} shBattleFight;
typedef struct shBattleShot
{
    // total size: 0xC
    float test_a; // offset 0x0, size 0x4
    float test_b; // offset 0x4, size 0x4
    float test_c; // offset 0x8, size 0x4
} shBattleShot;
typedef struct shAttackInfo
{
    // total size: 0x24
    unsigned short id;   // offset 0x0, size 0x2
    unsigned short kind; // offset 0x2, size 0x2
    float ap;            // offset 0x4, size 0x4
    float sp;            // offset 0x8, size 0x4
    float min_range;     // offset 0xC, size 0x4
    float max_range;     // offset 0x10, size 0x4
    union
    {
        struct shBattleFight fight; // offset 0x0, size 0xC
        struct shBattleShot shot;   // offset 0x0, size 0xC
    } hit_check;                    // offset 0x14, size 0xC
    unsigned char atk_start;        // offset 0x20, size 0x1
    unsigned char atk_end;          // offset 0x21, size 0x1
    unsigned char sd;               // offset 0x22, size 0x1
    unsigned char eff;              // offset 0x23, size 0x1
} shAttackInfo;

extern shAttackInfo sh2_attack_list[66];
extern shPlayerWork sh2jms;

#endif

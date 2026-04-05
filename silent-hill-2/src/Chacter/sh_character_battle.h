#ifndef SH_CHARACTER_BATTLE_H
#define SH_CHARACTER_BATTLE_H

#include "common.h"
#include "Chacter/character.h"
//#include "Collision/cl_main.h"

/*
// total size: 0x50
struct _CL_BATTLE_QUE {
    // Members
    unsigned short kind; // offset 0x0, size 0x2
    unsigned short btlid; // offset 0x2, size 0x2
    struct SubCharacter * sc; // offset 0x4, size 0x4
    float svs[4]; // offset 0x10, size 0x10
    float sve[4]; // offset 0x20, size 0x10
    float evs[4]; // offset 0x30, size 0x10
    float eve[4]; // offset 0x40, size 0x10
};

// total size: 0x40
struct _CL_BATTLE_RESULT {
    // Members
    signed int enable; // offset 0x0, size 0x4
    unsigned int id; // offset 0x4, size 0x4
    signed int atr; // offset 0x8, size 0x4
    float pos[4]; // offset 0x10, size 0x10
    float vec[4]; // offset 0x20, size 0x10
    unsigned short kind; // offset 0x30, size 0x2
    unsigned short btlid; // offset 0x32, size 0x2
    union {
        struct SubCharacter * en; // offset 0x0, size 0x4
        struct _CL_HITPOLY_PLANE * pl; // offset 0x0, size 0x4
        struct _CL_HITPOLY_COLUMN * cl; // offset 0x0, size 0x4
    } obj; // offset 0x34, size 0x4
};
*/

struct shBattleFight
{
    // total size: 0xC
    float test_a; // offset 0x0, size 0x4
    float test_b; // offset 0x4, size 0x4
    float test_c; // offset 0x8, size 0x4
};
struct shBattleShot
{
    // total size: 0xC
    float test_a; // offset 0x0, size 0x4
    float test_b; // offset 0x4, size 0x4
    float test_c; // offset 0x8, size 0x4
};
struct shAttackInfo
{
    // total size: 0x24
    unsigned short id;   // offset 0x0, size 0x2
    unsigned short kind; // offset 0x2, size 0x2
    float ap;            // offset 0x4, size 0x4
    float sp;            // offset 0x8, size 0x4
    float min_range;     // offset 0xC, size 0x4
    float max_range;     // offset 0x10, size 0x4
    union                /* @anon0 */
    {
        struct shBattleFight fight; // offset 0x0, size 0xC
        struct shBattleShot shot;   // offset 0x0, size 0xC
    } hit_check;                    // offset 0x14, size 0xC
    unsigned char atk_start;        // offset 0x20, size 0x1
    unsigned char atk_end;          // offset 0x21, size 0x1
    unsigned char sd;               // offset 0x22, size 0x1
    unsigned char eff;              // offset 0x23, size 0x1
};

void HH_Effect_Object_Blood_Splash_Impact_Post(float * Location /* r19 */, float * Direction /* r18 */, u_int Scp_Address /* r17 */, u_int Impact_Kind /* r16 */);

void EFCTSetGunFire(float * pos /* r19 */, float * vec /* r18 */);
void EFCTSetGunSmoke(float * pos);
void sh2gfw_Set_JmsGunLight();
short shCharacterAnimeFrameGet_(struct SubCharacter * scp /* r2 */, u_int type /* r2 */);
void shGetJamesWeaponEndPos(float * pos /* r2 */, float * vec /* r2 */);
int ItemWeaponShoot(int kind /* r16 */, int use /* r2 */);
int PlayerNowItemName(u_char wep /* r2 */);
int SeCallPos(int sd_no /* r20 */, float volume /* r20 */, float * pos /* r19 */, int status /* r18 */); 
//void clBattleAddQue(struct _CL_BATTLE_QUE * que /* r2 */);  

static void shBattleDamageRevise(float *damage, float *shock, struct SubCharacter *scp, struct _CL_BATTLE_RESULT *result);
static void shBattleSetEffectDamage(struct SubCharacter *scp, float *pos, float *vec, u_short atk);
static void shBattleAddEffectAttack(struct SubCharacter *attacker, float *pos, float *vec);
static void shBattleAttackByHumanGunshotTypeA(struct SubCharacter * attacker /* r20 */, u_short atk /* r16 */);

extern struct shAttackInfo sh2_attack_list[66];
extern struct shPlayerWork sh2jms;

#endif

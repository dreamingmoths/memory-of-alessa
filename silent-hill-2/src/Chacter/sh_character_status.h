#ifndef SH_CHARACTER_STATUS_H
#define SH_CHARACTER_STATUS_H

#include "common.h"
#include "Chacter/character.h"

// total size: 0x1
typedef struct shInArea {
    // Members
    u_char look_on : 2;  // offset 0x0, size 0x1
    u_char feel_on : 2;  // offset 0x0, size 0x1
    u_char light_on : 4; // offset 0x0, size 0x1
} shInArea;

// total size: 0xC
typedef struct shInAreaTgtInfo {
    // Members
    union /* @anon4 */ {
        struct SubCharacter* scp; // offset 0x0, size 0x4
    } adr;                        // offset 0x0, size 0x4
    float distance;               // offset 0x4, size 0x4
    struct shInArea in_area;      // offset 0x8, size 0x1
} shInAreaTgtInfo;

shInAreaTgtInfo sh2_target_info[20];
shInAreaTgtInfo sh2_target_info_buf[20]; // size: 0xF0, address: 0x3CEDE0
int rest_tgt; // size: 0x4, address: 0x3CEDD0
int rest_tgt_buf; // size: 0x4, address: 0x3CEDC8
extern struct shCharacterAll sh2chara;
void shBattleCheckTargetMyArea(shInArea* in_area, SubCharacter* scp, SubCharacter* tgt, float* look, float* feel);
int shBattleAroundTargetEnemy(void);
u_int shBattleGetTargetChara(SubCharacter* scp, int kind);
SubCharacter* shCameraGetNearTarget(int i, int type);

SubCharacter* shBattleGetTargetHuman(SubCharacter* scp /* r17 */, u_int type /* r2 */);
int shBattleSeeHumanLight(SubCharacter* scp /* r16 */);
int shBattleListenHumanSound(SubCharacter* scp, SubCharacter* tgt /* r2 */); // DWARF only shows one arg

int shBattleAimedByHuman(SubCharacter* scp /* r2 */);
int shBattleFinishedByHuman(SubCharacter* scp /* r2 */);
int shBattleNoDamageHuman(void);
int shBattleNoDamageHumanJames(void);
int shBattleNoDamageHumanMaria(void);
int shBattleHuggedHuman(void);
void shBattleSetLookArea(SubCharacter* scp, float center, float radius);
void shBattleSetFeelArea(SubCharacter* scp, float center, float radius);
void shBattleInitEnemyCheckWork(void);
void shBattleInit(void);
void shBattleExec(void);


#endif

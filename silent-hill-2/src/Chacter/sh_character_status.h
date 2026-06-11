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

SubCharacter* shBattleGetTargetHuman(SubCharacter* scp /* r17 */, u_int type /* r2 */);
int shBattleSeeHumanLight(SubCharacter* scp /* r16 */);
int shBattleAimedByHuman(SubCharacter* scp /* r2 */);
int shBattleFinishedByHuman(SubCharacter* scp /* r2 */);
int shBattleNoDamageHumanJames(void);
int shBattleNoDamageHumanMaria(void);
int shBattleHuggedHuman(void);
int shBattleListenHumanSound(SubCharacter* scp, SubCharacter* tgt /* r2 */); // DWARF only shows one arg

#endif

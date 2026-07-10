#include "Event/chara_admin.h"
#include "Event/event.h"
#include "Chacter/sh2_character_manage.h"

INCLUDE_ASM("asm/nonmatchings/Event/chara_admin", ConnectCharaWorkJamesSet);

INCLUDE_ASM("asm/nonmatchings/Event/chara_admin", ConnectCharaWorkWeapon);

INCLUDE_ASM("asm/nonmatchings/Event/chara_admin", ConnectCharaWorkReset);

INCLUDE_ASM("asm/nonmatchings/Event/chara_admin", ConnectCharaWorkAdminOut);

INCLUDE_ASM("asm/nonmatchings/Event/chara_admin", ConnectCharaWorkAdminIn);

INCLUDE_ASM("asm/nonmatchings/Event/chara_admin", ConnectCharaWorkAdminClear);

INCLUDE_ASM("asm/nonmatchings/Event/chara_admin", RoomDistance);

INCLUDE_ASM("asm/nonmatchings/Event/chara_admin", RoomDistanceSub);

INCLUDE_ASM("asm/nonmatchings/Event/chara_admin", CharaWorkCreate);

/* static */ void DeleteEnemyWork(void) {
    if ((stage->glb_crd != 4) && (stage->glb_crd != 3) && (stage->glb_crd != 2) && (stage->glb_crd != 1)) {
        DeleteEnemyWorkIn(); return;        
    }

    
    DeleteEnemyWorkOut();
    
}

INCLUDE_ASM("asm/nonmatchings/Event/chara_admin", DeleteEnemyWorkIn);

INCLUDE_ASM("asm/nonmatchings/Event/chara_admin", DeleteEnemyWorkOut);

INCLUDE_ASM("asm/nonmatchings/Event/chara_admin", CharaAdminEnemyEntryCheck);

INCLUDE_ASM("asm/nonmatchings/Event/chara_admin", CharaAdminEnemyEntryCondition);

INCLUDE_ASM("asm/nonmatchings/Event/chara_admin", CharaAdminPlayableDisplay);

SubCharacter* CharaAdminReCreate(int kind, int new_id, int old_id, float* pos, float* rot, int status) {
    shCharacter_Manage_Delete(NULL, kind, old_id);
    return CharaWorkCreate(kind, new_id, pos, rot, status);
}

INCLUDE_ASM("asm/nonmatchings/Event/chara_admin", CharaAdminBackLoadEnemy);

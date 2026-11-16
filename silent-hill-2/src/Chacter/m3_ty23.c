#include "sh2_common.h"
#include "Chacter/character.h"
#include "Enemy/en_common.h"
#include "Chacter/m3_ty23.h"

static int EnemyTY23Init(void);
static void EnemyTY23Function(SubCharacter* this);


#line 39
static int EnemyTY23Init(void) {
    return 0;
}

# line 53
static void EnemyTY23Function(SubCharacter* this) {
    float scale = 1.0f;
    EnLOCAL_DATA* dp;

    switch (this->step) {
        case 0:
            if (this->battle.status & 0x400) {
                
                EnemyTY23Init();
                SCStayModelSwitch(this, true);
                
                shCharacterWorldScreenObjectSetNew(this, scale);
                
                dp = enEntryEnemy(enTransID(this->kind));
                this->enemy_p = dp;
                enInitData(dp, this);
                this->eye_y = this->center_y = this->pos.y - 50.0f;
                
                this->step++;
            }
        /* fallthrough */
        case 1:
            return;
    }
}

#line 93
void shCharacterSetEnemyTY23Low(SubCharacter* scp) {
    shCharacterSetFunction(scp, EnemyTY23Function);
}

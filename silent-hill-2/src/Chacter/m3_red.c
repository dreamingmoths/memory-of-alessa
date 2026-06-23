#include "Chacter/m3_red.h"
#include "Chacter/m3_sc.h"
#include "Chacter_Draw/model3_equip_n.h"
#include "Enemy/en_common.h"
#include "Enemy/en_red.h"
#include "libvu0.h"

extern /* static */ AnimeInfo red_anim[12]; // size: 0x90, address: 0x0
extern /* static */ AnimeInfo d_red_anim[7]; // size: 0x54, address: 0x0

static int EnemyREDInit(SubCharacter* scp); // not sure about the argument here
static void EnemyREDFunction(SubCharacter* scp);

static int EnemyREDInit(SubCharacter* scp) {
    return 0;
}

static void EnemyREDFunction(SubCharacter* scp) {
    sceVu0FVECTOR pos;
    sceVu0FVECTOR rot; // r29+0x30
    EnLOCAL_DATA* dp; // r2    
    switch (scp->step) {
        case 0:
            if (scp->battle.status & 0x400) {


                
                volatile_vec_copy(&pos, &scp->pos);
                volatile_vec_copy(&rot, &scp->rot);
                
                EnemyREDInit(scp);

                
                if (!PlayerNowDemoEventMode()) {
                    
                    SCAnimeTypeSwitch(scp, 1);
                    shCharacterEnemyREDAnimeSetP(scp,
                                                 0x189D,
                                                 1);







            
                    if (scp->status & 0x4) {
                        
                        dp = enEntryEnemy(4);
                        if (dp != NULL) {
                            scp->enemy_p = dp;
                            enInitData(dp, scp);
                        } else {
                            scp->enemy_p = NULL;
                        }
                    }

                    
                    scp->battle.target = shCharacterGetSubCharacter(0x100, -1);
                }
                
                volatile_vec_copy(&scp->pos, &pos);                
                volatile_vec_copy(&scp->rot, &rot);
                
                scp->step++;                
            }


        
        case 1:
            return;
        }
}

void shCharacterSetEnemyREDLow(SubCharacter* scp) {
    shCharacterSetFunction(scp, EnemyREDFunction);
}

void shCharacterSetWeaponRED(SubCharacter* scp, int on_off) {
    sh2gfw_Set_JMSequip(scp, 0, 0, (on_off != 0) ? 3 : 0);
}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_red", shCharacterEnemyREDAnimeSet);

int shCharacterEnemyREDAnimeSetP(SubCharacter* scp /* r17 */, int anime_id /* r18 */, int comp /* r16 */) {
    AnimeInfo* aip; // r18
    
    if (shCharacterGetModelID(scp) == EN_RED_CHARA_ID) {
        aip = &red_anim[anime_id - 0x14B4];
        shCharacterAnimeSet(scp,
                            0,
                            (s_char) ((comp == 1) ? 4 : 2),
                            aip,
                            (int) shCharacterGetAnimeAdrForPlay(scp));

        
        return 0;
    }
    
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_red", shGetEnemyREDAttackPos);
